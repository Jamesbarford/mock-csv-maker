#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <uuid/uuid.h>

const int DATE_BYTES = 80;
const int UUID_BYTES = 37;
char *get_date();
char *get_uuid();
int calc_range(int headers_start, int data_start, int length_start);
void make_csv(int headers_start, int data_start, int length_start, char **argv);

int main(int argc, char **argv)
{
  time_t start, stop;

  time(&start);

  int i;
  int arr[3];

  for (int i = 0; i < argc; i++)
  {
    if (strncmp(argv[i], "-h", 2) == 0)
    {
      arr[0] = i + 1;
    }
    else if (strncmp(argv[i], "-d", 2) == 0)
    {
      arr[1] = i + 1;
    }
    else if (strncmp(argv[i], "-l", 2) == 0)
    {
      arr[2] = i + 1;
    }
  }

  if (arr[0] == 0 || arr[1] == 0 || arr[2] == 0)
  {
    printf("Valid arguments are, for example, column names:'-h header_1 header_2 header_3' data types: '-d string number date' data length: '-l 30' \n");
    return 1;
  }

  make_csv(arr[0], arr[1], arr[2], argv);

  time(&stop);

  printf("Time to execute :: %.2f \n", difftime(stop, start));

  return 0;
}

void make_csv(int headers_start, int data_start, int length_start, char **argv)
{
  printf("Writting file . . . \n");
  // this is constant.
  const int length = atoi(argv[length_start]);
  const int range = calc_range(headers_start, data_start, length_start);
  char src[50], dest[50];
  char *uuid, *filename, *date;

  uuid = get_uuid();

  strcpy(src, uuid);
  free(uuid);
  strcpy(dest, ".csv");
  filename = strcat(src, dest);

  int i = 0, j = 0;

  FILE *file;
  file = fopen(filename, "w+");

  while (i < range)
  {
    if (i == (range - 1))
    {
      fprintf(file, "%s\n", argv[headers_start + i]);
      break;
    }
    else
    {
      fprintf(file, "%s,", argv[headers_start + i]);
    }
    i++;
  }

  while (j < length)
  {
    int k = 0;
    while (k < range)
    {
      char *current = argv[data_start + k];

      if (strcmp(current, "date") == 0)
      {
        date = get_date();
        fprintf(file, "%s", date);
        free(date);
      }
      else if (strcmp(current, "string") == 0)
      {
        uuid = get_uuid();
        fprintf(file, "%s", uuid);
        free(uuid);
      }
      else
      {
        fprintf(file, "%d", j);
      }

      if (k == (range - 1))
      {
        fprintf(file, "%c", '\n');
      }
      else
      {
        fprintf(file, "%c", ',');
      }
      k++;
    }
    j++;
  }

  fclose(file);
}

int calc_range(int headers_start, int data_start, int length_start)
{
  int range;

  // -l -d -h
  if (headers_start > data_start && headers_start > length_start && length_start < data_start)
  {
    range = (headers_start - data_start) - 1;
  }
  // -l -h -d
  else if (headers_start < data_start && headers_start > length_start)
  {
    range = (data_start - headers_start) - 1;
  }
  // -h -d -l
  else if (headers_start < data_start && data_start < length_start)
  {
    range = (data_start - headers_start) - 1;
  }
  // -d -l -h
  else
  {
    range = (headers_start - data_start) - 1;
  }

  return range;
}

char *get_uuid()
{
  uuid_t binuuid;
  char *uuid = malloc(UUID_BYTES);

  uuid_generate_random(binuuid);
  uuid_unparse_lower(binuuid, uuid);

  return uuid;
}

char *get_date()
{
  time_t rawtime;
  struct tm *info;
  char *buffer = malloc(DATE_BYTES);

  time(&rawtime);

  info = localtime(&rawtime);

  strftime(buffer, DATE_BYTES, "%d/%m/%Y", info);

  char *str = buffer;

  return buffer;
}

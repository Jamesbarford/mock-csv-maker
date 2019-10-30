# Mock CSV Maker

A very simple command line csv maker:

## Compile:
e.g: `clang make_csv.c -o make_csv -l uuid`


## Arguments:

```
-h: column names
-d: data types: string, number, date (UK: i.e 25/12/2019)
-l: number of itterations
```

## Usage:
`./make_csv -h foo bar -d string string -l 10`

outputs: `[hash].csv`

```
foo,bar
2c92c04f-122b-40f9-8edd-421ff3204d8f,1
ae0f45be-23f3-4a28-b992-715be04c6864,3
938175d8-c6da-4470-89d0-8c2e6c55ffbc,5
2d0b6bcb-b7fd-4f9a-bc02-f2960202c2ba,7
8d77cd47-08b4-4147-8947-2f7de9fe39a3,9
```

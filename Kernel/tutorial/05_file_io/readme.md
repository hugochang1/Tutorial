# hexdump
- ASCII, decimal, hexadecimal, octal dump
- `$ hexdump -C -n 16 /dev/hugo_dev0`
  - `-C` Display the input offset in hexadecimal
  - `-n` length
````
00000000  61 62 63 20 31 32 33 61  62 63 20 31 32 33 61 62  |abc 123abc 123ab|
00000010
````

# How to run

<i>This program needs to be compiled in order to run</i>

In your terminal, you can enter either

```bash
dec3.exe <inputfile.extension>
```

which will run all mul(x, y) calls from input file

or

```bash
dec3.exe <inputfile.extension> --with-conditional
```

which will run all mul(x, y) calls from input file with the conditional do() and don't() in input file

<i>Note: I don't like the solution during character reading at all, should refactor with less conditionals after eachother. Perhaps refactor pieces into helper functions.</i>

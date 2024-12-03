# How to run

<i>This program needs to be compiled in order to run</i>

In your terminal, you can enter either

```bash
dec2.exe <inputfile.extension>
```

which will calculate number of safe reports

or

```bash
dec2.exe <inputfile.extension> --with-conditional
```

which will calculate number of safe reports, accepting one faulty level

<i>Note: I don't like the solution during character reading at all, should refactor with less conditionals after eachother. Perhaps refactor pieces into helper functions.</i>

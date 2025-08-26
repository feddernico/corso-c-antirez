# argv explained

the first element of the line is the memory address, the second the string saved.
```
1000 askdfdslfkjsdf
1100 dasdlkfjdasfj
1200 dsflajsdflkj
```

every one of these memory addresses can be registered as a char like this:
```c
char *str = 1000;
```

but I want a contiguous array where there are all these pointers, one next to the other

`[1000|1100|1200]`

but argv will be the memory address where is recorded an array of memory addresses (the one just above).

```c
char **argv 
```

So that `argv[0], argv[1], ...` will be a char\* variable.


## the tac.c example

Getting to the example in the `tac.c` script:

```
1000: foo
2000: bar
3000: [1000, 2000]
```

So, the first two are memory addresses where there are char variables stored, hence they are `char*` variables. 

The last one is a memory address that stores the memory addressess where the chars are stored, hence it's a `char**` variable.

# How the implementation of tac2.c (cat command) works

```
one
two
three
```

first iteration: 

```c
head = NULL
@1000 #memory address
{   
    s: "one"
    next: null
}
head = 1000
```

second iteration

```c
@2000 #memory address
{
    s: "two"
    next: 1000
}
head = 2000
```

and so on...

This is in programming theory is called a **linked list**.

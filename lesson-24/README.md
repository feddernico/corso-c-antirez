# Lesson 23: Let's build the interpreter Toy Forth

Let's say we have two programs:

1. `5 5 +`
2. `5 dup +`

The interpreter uses a pile of values called the stack. Starting from the first program, when I encounter `5` that is a literal value, my stack becomes:
`Stack: 5`. The basic stack programs are based on the idea of words, it's a sequence of words, so the program is a list.
Now I go to the second word and there is `5` again, since it's not a function then my stack becomes `Stack: 5 5`. ON the last step I find `+`, which is a function, the two numbers `5 5` are removed from the stack and the function is applied, so the two numbers are summed together `5+5 = 10` and the result is added to the stack.

Looking at the second program, let's execute it starting with an empty stack. The first element in the program is again, a `5`, so it get's added to the stack, and my stack becomes `Stack: 5`. The second element is `dup`, so it's a function. `dup` pops the last value from the stack and puts it in another time in the stack, so my stack now becomes `Stack: 5 5`. Finally it gets a `+` and applies the function as in the previous example.

Now let's have a look at a third program: `"Hello World" strlen print`. In this case the string is inserted as a whole in the stack, so the stack becomes `Stack: "Hello World"`, then, when looking at the function `strlen`, it evaluates how long is the string and removes it from the stack, so the stack becomes `Stack: 11` and then the print gets the last value from the stack and prints it out.
Now, given that all the values can be not just numerical, I can also have a subprogram as a value. For example I can have something like this `[dup *] [dup +] [10 20 <] if`. In this program, I encounter the first value, and I add it to the stack, so it becomes `Stack: [dup *]`, I then encounter the second subprogram, and the stack becomes `Stack [dup *] [dup +]`. Finally it evaluates the last subprogram evaluates it to `true`. So, it then executes the true branch of the if, and stack becomes `Stack: 400`

To make it more readable I can transform the program into something like this: 
```
[10 20 <]
   [dup *]
   [dup +] ifelse
```

And can also have an if only version like this: `[10 20 <] [dup *] if`.

# CSCI 2510: Studio 10 Race Conditions

Race conditions are a common problem of multi-threaded and parallel
programming. Our goal today is to create a race condition and observe
its behavior.

In this studio, you will:

1.  Create a shared global variable
2.  Access this variable from a single thread
3.  Access this variable from multiple threads
4.  Demonstrate a race under parallel execution (simultaneous execution)
5.  Demonstrate a race under sequential execution (concurrent execution)

------------------------------------------------------------------------

Please complete the required exercises below, as well as any optional
enrichment exercises that you wish to complete.

As you work through these exercises, please record your answers in a
text file. When finished, submit your work via the git repository.

------------------------------------------------------------------------

### Required Exercises

1.  Create a new program, and create a global variable of type `int` and
    called `race` at the top of your program (in global scope, not in
    the `main()` function). Then write two functions, called `adder` and
    `subtractor`, which increment and decrement the variable `race` two
    million times each. Each function should perform two million
    additions or subtractions by one. Copy and paste these functions.

2.  What do you think would happen if you executed these functions
    directly in `main()`? Test your hypothesis by doing so. What
    happens?

3.  What do you think will happen if these two functions were executed
    simultaneously by two different threads? What specific value do you
    think the variable `race` would have?

4.  Modify your program so that each function is executed concurrently
    by its own thread via `pthread_create()`. Make sure that you create
    both threads before you wait for either thread. What is the result?
    Copy and paste several executions of your program.

5.  Can you explain the program\'s behavior? What do you think the
    maximum or minimum value could ever be?

6.  Try changing the number of iterations from two million to one
    million, and then from one million to 500,000. Does your program
    still exhibit this behavior? Try your program with 1000 iterations
    and try your program ten or fifteen times. What about now?

7.  Could your race condition still exhibit itself if your machine had
    only one processor core? Why or why not?

8.  Note that the following command requires a Linux-like environment.

    We can simulate this by running your program and only allowing it to
    execute on one processor. Set the number of iterations back to two
    million, and then execute the command:

    `taskset -c 0 ./race_program`

    This restricts the program `race_program` to only execute on
    processor zero. What happens?

9. Modify your program so that each function performs two hundred
    million operations (200,000,000). Run your program on one processor
    core, what happens?

10. Give a reasonable explanation of the behavior in the previous
    exercise.

### Optional Enrichment Exercises

1.  No optional exercises

------------------------------------------------------------------------

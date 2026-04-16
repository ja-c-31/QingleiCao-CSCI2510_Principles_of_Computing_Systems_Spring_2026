# CSCI 2510: Studio 9 - Threads

In this studio, you will:

1.  Create threads using Pthreads
2.  Join with (wait for) threads to finish their work
3.  Create a structure to hold thread parameters
4.  Pass parameters to and from threads using `void*` pointers

------------------------------------------------------------------------

Please complete the required exercises below, as well as any optional
enrichment exercises that you wish to complete.

As you work through these exercises, please record your answers in a
text file. When finished, submit your work via the git repository.

------------------------------------------------------------------------

### Required Exercises

1.  Open up the manual page for `pthread_create()`. The third parameter
    to this function specifies a new thread\'s *entry point*- the
    location at which the new thread begins execution.This parameter
    will look a little unusual, because it\'s a special data type called
    a *function pointer*. The function pointer type is given as:

    ` return_type (* function_name ) ( argument_types )`

    What is the return type and the expected arguments for the thread
    entry function?

2.  Create a new progam. Before writing your main function, write a
    function called `thread_entry` with the signature specified in the
    previous exercise. This function should print a message and then
    return NULL.

3.  Now write your `main()` function and make a call to the function
    `pthread_create()`. For the time being, leave the second and fourth
    parameters of this function `NULL`. Be sure to check the return
    value for errors. Note that this function does not set `errno` and
    you cannot use `perror()`.

    After you make a call to `pthread_create()`, make a call to
    `pthread_join()` to wait for the created thread to finish. The first
    argument of this function needs the value from parameter one of
    `pthread_create()`. The second argument of this function can be left
    NULL.

    In order to compile your program you will need to add the `-pthread`
    option to GCC. Copy and paste your program output.

4.  Now you can create and run code inside a thread, but this really
    isn\'t useful unless you can communicate with the thread. There are
    a variety of ways to pass data between threads, but we will use a
    specific method called `void*` passing. To do this we need to define
    a `struct`, which is a collection of variables that are grouped
    together. The syntax for defining a struct is as follows:

    `struct struct_name{   arg1_type arg1;   arg2_type arg2;   ...   argN_type argN; };`

    And you can then declare a struct for use in your program such:

    `  struct struct_name variable_name   variable_name.arg1 = value1; //direct access   variable_name.arg2 = value2; //direct access`

    Keep in mind that you can also access the values of this struct
    through a pointer to the structure as well. This will be important
    in your thread entry function:\
    `  struct struct_name *struct_ptr = &variable_name;   struct_ptr->arg1 = value1; //pointer access   struct_ptr->arg2 = value2; //pointer access`

    Define a struct with three members: an integer called `arg1`, a
    character buffer called `arg2`, and another integer called `ret`.
    Copy and paste your struct definition.

5.  Now create a struct in your main program and fill it with values.
    Your thread can access this struct by passing a pointer through the
    fourth argument of `pthread_create()`. Create a pointer to your
    struct as illustrated in the last exercise and do so.

    A pointer given to the `pthread_create()` function in this way will
    be available to your thread entry function as the `void*` parameter.
    However, the compiler doesn\'t know how to access the data pointed
    to by a `void*` pointer. To access the data inside the struct we
    need to *cast* the pointer type back to a struct pointer, as so:

    `void* thread_entry( void* args ){   struct struct_name* arg_ptr = (struct struct_name*) args;   printf("thread arg1: %d\n", arg_ptr->arg1);   printf("thread arg2: %s\n", arg_ptr->arg2);   ... }`

    Print out the values of your struct arguments in the newly created
    thread. Copy and paste the program output.

6.  Now use the same structure to return a value to the `main()`
    function. Write a value to the third member of your structure
    somewhere in your thread, and then read that value in `main()`
    function after you have executed `pthread_join()`.

7.  Finally, parameterize your program to create N threads. This means
    you will need to create an array of N `pthread_t` identifiers, and
    an array of N `struct struct_name` structures to pass arguments.
    Then, call `pthread_create()` for N iterations, and then
    `pthread_join()` for N iterations.

    You can easily write multiple, different strings to each thread
    using the `snprintf()` function, which works just like the
    `printf()` function. For example:

    `unsigned bufSize = 100; struct struct_name args[num_threads]; for( i = 0; i < num_threads; i++ ){     snprintf(args[i].arg2, bufSize, "This is thread %d", i); }`

    Copy and paste your program output for five threads when you have
    finished.

8.  Run your prgram (with five threads) several times. What do you
    notice about the output ordering? Why do you think this is?

### Optional Enrichment Exercises

1.  No optional exercises

------------------------------------------------------------------------

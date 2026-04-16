# CSCI 2510: Studio 11 - Mutexes

*Mutual exclusion* is an important concept in concurrent and parallel
programming where different threads of execution cooperate to avoid
causing racy program behavior. This exclusion is encapsulated at a high
level in an object called a *mutex*. A mutex allows for protection of
shared data by allowing cooperating threads to *lock* the mutex and
thereby claim the exclusive use of critical data.

In this studio, you will:

1.  Create a Pthreads mutex
2.  Use a single mutex to coordinate shared access to a variable
3.  Measure the overhead of using a mutex

------------------------------------------------------------------------

Please complete the required exercises below, as well as any optional
enrichment exercises that you wish to complete.

As you work through these exercises, please record your answers in a
text file. When finished, submit your work via the git repository.

------------------------------------------------------------------------

### Required Exercises

1.  First, make a copy of your code from the previous studio where we
    created a race condition. Our goal today is to fix that race
    condition. We will do this by creating a `pthread_mutex_t` object,
    initializing it, and then locking and unlocking this mutex around
    the critical section.

    Create your `pthread_mutex_t` object with the help of the man page
    at `man pthread_mutex_init`. You may intialize your object with the
    static initializer (`PTHREAD_MUTEX_INITIALIZER`) or with the
    `pthread_mutex_init()` function (if you use this second you can
    leave the `pthread_mutexattr_t` pointer NULL). Create this mutex
    inside your `main()` function. Copy and paste your mutex creation
    code.

2.  Now you must pass a mutex pointer from your `main()` function to the
    `adder()` and `subtractor()` functions from last time. Pass these
    pointers through the fourth parameter of `pthread_create()`. Leave
    this answer blank.

3.  Take a moment to consider our goal. Previously, the simultaneous
    accesses to your variable caused some data corruption. What do you
    think the result will be if you synchronize your accesses? What will
    be the numeric value? How will this effect the amount of time your
    program takes to run?

4.  Now, use the functions `pthread_mutex_lock()` and
    `pthread_mutex_unlock()` to synchronize access to the racy variable.
    This means that your threads should not modify this variable unless
    they have successfully locked the mutex, and after modifying the
    variable they should unlock the mutex.

    Run your program many times. Does your program output match your
    expectations? Copy and paste several program outputs.

5.  Now we want to quantify the overhead of using this mutex. Locking
    and unlocking the mutex is not free, but it is the cost we pay for
    correct behavior. Go back to your original racy program from the
    previous studio. Modify the number of iterations each thread
    performs to be twenty million (20,000,000). Take three timings of
    this program with the `time` utility. Copy and paste your program
    output, and calculate the average time.

6.  Go back into your corrected program that uses your mutex. Set the
    number of iterations to be twenty million (20,000,000). You might
    have noticed that there are two possibilites for where you put your
    locking and unlocking code. You can have each thread perform one
    lock and unlock operation in total, or you can have each thread
    perform one lock and unlock operation for each individual increment
    or decrement of the racy variable.

    Modify your program, if necessary, so that each thread locks and
    unlocks the mutex once per increment or decrement (that is, each
    thread should lock and unlock the mutex twenty million times. Take
    three time measurements, copy and paste your output, and compute the
    average. How much longer did this execution take?

7.  Modify your program so that you lock and unlock the mutex just once
    per thread. Repeat your timing experiment and copy/paste the output.
    How does this time compare to the original, racy program?

8.  Speculate about what might cause the results from the previous
    exercise.

10. Think of an example of where the first, per-iteration locking
    strategy might be more appropriate. Where might the second,
    per-thread locking strategy be more appropriate?

### Optional Enrichment Exercises

1.  No optional exercises

------------------------------------------------------------------------

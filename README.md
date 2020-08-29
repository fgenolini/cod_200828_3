# cod_200828_3
Programming experimentations after having completed the third task
in a C codility test on 2020/08/28.

The specific task and test is not really important.
However I have enjoyed the challenge,
and this project contains additional optional work
that could not take place during the limited time available during the test.


## Objectives
Investigation of the performance of qsort (standard C library)
against C++ std::sort,
as well as the performance of searching for a value in a sorted array.

As documented, the C qsort is much slower (such as twice as slow)
than the C++ std::sort.


## Build system
CMake project to build a simple C++ command line application for the console.

The main translation unit is "task3".


## Very large arrays
In order to have observable search times, the number of elements in the
array must be very large.

The size of the array must be comparable to the total amount of memory in the
system.

This project therefore uses very large arrays,
with sizes larger than the size of the stack or the heap.

The arrays are in the "large_array" translation unit.
If placed in the main translation unit, the arrays will be too large and will
cause the compilation to fail.

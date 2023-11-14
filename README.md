# mutexC

This small program demonstrates the use of a mutex in C. What is a mutex? When running multiple threads within a process it is important to be able to control access to global data that may be manipulated. In order to prevent multiple threads from accessing global data without one thread or another having completed its operation, a mutex puts a "lock" around certain operations to ensure global data remains in sync with all other operations. 

This program uses a linked list as the global data to be manipulated. Multithreading is supported vis pthread.h. 

How to run this program:

1)  Compile command:  gcc mutex.c -o mutex
2)  Run: ./mutex

Testing:
If you would like to play with the code to see how mutexing ensures that no operations are lost try the follwoing:

1) On line 12, try changing that NUM_THREADS variable to any number you choose and run the code (the higher the better). The print statement, Node Count, should match this number.

2) Now try commenting out lines 50 and 53 (yes, under the annoyingly large MUTEX ascii art) and running the code again. Lines 51 and 52 are crucial operations for ensuring the linked list head is updated properly. Without the mutex, you will notice that whatever number you choose for NUM_THREADS will more than likely not be returned in the Node Count print statement. 

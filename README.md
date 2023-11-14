# mutexC

This small program demonstrates the use of a mutex in C. What is a mutex? When running multiple threads within a process it is important to be able to control access to global data that may be manipulated. In order to prevent multiple threads from accessing global data without one thread or another having completed its operation, a mutex puts a "lock" around certain operations to ensure global data remains in sync with all other operations. 

This program uses a linked list as the global data to be manipulated. Multithreading is supported vis pthread.h. 

# Multitasking 
### process
  - a process is the instance of a computer program that is being executed by one or many threads
### thread
  - a thread can be created by a process and share the process's resources
### concurrency issues
  - there are two or more threads or processes trying to use the same resource at the same time but the resource can only be accessed by one at the same time
### locks
### mutexes (mutual exclusion)
### semphores
  - is a synchronization primitive: a mechanism that enforces limits on access to a resource when there are many threads of execution.
### monitors
  - The monitor is one of the ways to achieve Process synchronization. The monitor is supported by programming languages to achieve mutual exclusion between processes
  - https://www.geeksforgeeks.org/monitors-in-process-synchronization/
  - Advantages of Monitor
    - making parallel programming easier and less error prone than using techniques such as semaphore
  - Disadvantages of Monitor
    - Monitors have to be implemented as part of the programming language . The compiler must generate code for them. This gives the compiler the additional burden of having to know what operating system facilities are available to control access to critical sections in concurrent processes

# deadlock
### deadlock
  - deadlock is any situation in which no one can proceed because each waits for another's resources
### livelock
  - A livelock is similar to a deadlock, except that the states of the processes involved in the livelock constantly change with regard to one another, none progressing
  - Livelock is a risk with some algorithms that detect and recover from deadlock
### how to avoid them?
  - Deadlock prevention: eliminating any of the four necessary conditions, which are mutual exclusion, hold and wait, no preemption, and circular wait.
  - Deadlock avoidance: Operating system runs an algorithm on requests to check for a safe state. Any request that may result in a deadlock is not granted
  - Deadlock detection & recovery: OS detects deadlock by regularly checking the system state, and recovers to a safe state using recovery techniques

# understand how context switch works
### context switch
  - a context switch is the process of storing the state of a process or thread, so that it can be restored and resume execution at a later point, and then restoring a different, previously saved, state
  - Switching cases
    - Multitasking: within some scheduling scheme, one process must be switched out of the CPU so another process can run
    - Interrupt handling: to handle peripheral I/O signals 
    - User and kernel mode switching

# Storage/Memory
### Access Hierarchy
  - CPU
  - L1/L2/L3 Cache
  - Memory
  - I/O devices (disk, ethernet, ...etc.)
### direct memory access (DMA)
  - no need CPU to do the data transfer between the memory and the device
### access ordering (Memory ordering)
  - Memory ordering describes the order of accesses to computer memory by a CPU
  - memory ordering generated by the compiler during compile time
    - GNU asm volatile("" ::: "memory");
  - memory ordering generated by a CPU during runtime
    - ARMv7
      - Data Memory Barrier (DMB)
      - Data Synchronization Barrier (DSB)
      - Intruction Synchronization Barrier (ISB)
### pointers
### caching

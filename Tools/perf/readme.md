# perf
- It's a Linux performance profiling tool for user space and kernel space in C/C++

### CPU profiling
- Command ``` perf top ```
  - CPU profiling
```
   PerfTop:    1619 irqs/sec  kernel:42.4%  exact:  0.0% lost: 0/0 drop: 0/0 [4000Hz cycles],  (all, 4 CPUs)
-------------------------------------------------------------------------------

    10.16%  [kernel]          [k] arch_counter_get_cntvct
     8.93%  [kernel]          [k] arch_local_irq_enable
     8.50%  emdlogger1        [.] 0x000000000002d8dc
     7.12%  [kernel]          [k] ZSTD_compressBlock_doubleFast
     3.67%  libc.so           [.] memcmp
     1.88%  [kernel]          [k] nfi_wait_ready
     1.52%  [kernel]          [k] arch_local_irq_enable
     1.18%  [kernel]          [k] __raw_spin_unlock_irqrestore
     1.18%  [kernel]          [k] arch_local_irq_enable
     1.08%  [kernel]          [k] __delay
     0.98%  [kernel]          [k] HUF_sort
     0.91%  [kernel]          [k] HUF_compress1X_usingCTable
     0.86%  emdlogger1        [.] 0x000000000000a514
     0.83%  emdlogger1        [.] 0x000000000000a420
     0.80%  emdlogger1        [.] 0x0000000000009f54
     0.76%  emdlogger1        [.] 0x000000000000a3c0
     0.65%  emdlogger1        [.] 0x000000000000a4e0
     0.62%  [kernel]          [k] arch_local_irq_restore
     0.62%  emdlogger1        [.] 0x000000000000a50c
     0.58%  emdlogger1        [.] 0x000000000000a3b0
```

### Call graphs
- Command ``` perf record -g ```
  - Recording call graphs
  - will generate perf.data under the current folder
- Command ``` perf report --call-graph ```
  - read perf.data under the current folder
```
  [[31m  44.97%[[m     0.00%  swapper          [kernel.kallsyms]    [k] cpu_startup_entry
            |
            ---cpu_startup_entry
               |
                --[[31m44.26%[[m--do_idle
                          |
                          |--[[31m34.92%[[m--cpuidle_enter
                          |          |
```

### Flamegraph
- Command ```  perf script > out.perf ```
  - read perf.data and convert to trace output format for generating flame graph
- git clone https://github.com/brendangregg/Flamegraph
  - cd Flamegraph
  - ./stackcollapse-perf.pl ../out.perf > stacks.folded
    - convert stack trace to flamegraph's input
  - ./flamegraph.pl stacks.folded > flamegraph.svg
    - convert to svg file

### Troubleshooting
```
# perf top
```
```
Error:
Access to performance monitoring and observability operations is limited.
Enforced MAC policy settings (SELinux) can limit access to performance
monitoring and observability operations. Inspect system audit records for
more perf_event access control information and adjusting the policy.
Consider adjusting /proc/sys/kernel/perf_event_paranoid setting to open
access to performance monitoring and observability operations for processes
without CAP_PERFMON, CAP_SYS_PTRACE or CAP_SYS_ADMIN Linux capability.
More information can be found at 'Perf events and tool security' document:
https://www.kernel.org/doc/html/latest/admin-guide/perf-security.html
perf_event_paranoid setting is 2:
  -1: Allow use of (almost) all events by all users
      Ignore mlock limit after perf_event_mlock_kb without CAP_IPC_LOCK
>= 0: Disallow raw and ftrace function tracepoint access
>= 1: Disallow CPU event access
>= 2: Disallow kernel profiling
To make the adjusted perf_event_paranoid setting permanent preserve it
in /etc/sysctl.conf (
```
- use ```setenforce 0``` to disable SELinux

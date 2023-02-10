# Kernel preemption
- CONFIG_PREEMPT
  - if CONFIG_PREEMPT=y, spinlock will go to sleep if lock is not acquired

# Big Kernel Lock (BKL)
- lock whole Kernel
- will be phased out

# RCU
- Read Copy Update
- rcu_read_lock()
- rcu_dereference()

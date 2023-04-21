# the concept of spin_lock, spin_lock_irq, and spin_lock_irqsave
- spin_lock, spin_unlock
  - [issue] deadlock happen when normal kernel thread lock first and then interrupt happens and require the same lock
  - [solution] use spin_lock_irq
- spin_lock_irq, spin_unlock_irq
  - [diff with spin_lock] disable its local CPU interrupt
  - [issue] the interrupt could be disabled by somebody for some purpose, but spin_lock_irq and spin_unlock_irq will enable/disable interrupt unconditional
  - [solution] already use spin_lock_irqsave, spin_lock_irqrestore instead
- spin_lock_irqsave, spin_unlock_irqrestore
  - [diff with spin_lock_irq] save irq status before lock and restore irq status when unlock

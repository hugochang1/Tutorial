# Functional Safety
### Wiki
- https://en.wikipedia.org/wiki/ISO_26262
- 1st edition ISO 26262:2011
- 2nd edition ISO 26262:2018
- IEC 61508 (Industrial/General, ISO 26262 is an adaption with minor differences)

### What is ISO 26262 (Synopsis)
- https://www.synopsys.com/automotive/what-is-iso-26262.html

### ASIL Operating Systems
- February 07, 2021 https://www.functionalsafetyfirst.com/2021/02/asil-operating-systems-which-is-your.html
- What ASIL OS we expected
  - High availability and reliability (Guaranteed and correct execution of not only safety components, but also non-safety components)
  - Maximum Performance (minimal latencies for interrupts, events, tasks etc)
  - Guaranteed Isolation of Safety related processes (including its memory and data)
  - Guaranteed freedom from Interference for execution of Safety related tasks/threads and preferably, localized recovery of failed components/processes without affecting the rest of the System
  - Safe and reliable inter-process/inter-task/inter-thread communication
  - Integration of Security into the architecture of the OS
- OS consideration
  - ASIL level
  - compliant to AUTOSAR standards
  - compliant to POSIX standards
  - support Multi-core and Many-core architectures
  - MMU (Memory Management Unit)
  - MPU (Memory Protection Unit)
  - OS Architecture (Nature of Kernel, scheduling policies etc)
  - Freedom from Interference for Memory (i.e., tasks/process memory)
  - detects or prevents Stack corruption/overflow/underflow
  - safe inter-task/inter-process communication
  - Freedom from Interference for Timing and Execution
  - ensures high reliability, availability and performance
  - Microcontrollers supported
  - security

### ELISA (Enabling Linux In Safety Applications)
- https://elisa.tech/

### AGL (Automotive Grade Linux)
- https://www.automotivelinux.org/

### RedHat
- https://www.redhat.com/en/solutions/automotive

### Terms
- RPN (Risk Priority Number)
  - show the probability of potential risk

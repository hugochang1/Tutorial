### Video
#### ISO 26262 – Functional Safety at a Glance
- https://www.youtube.com/watch?v=9wcJuW9E0S8&list=PLO2k6yikLVTlrkQJN8pbznro3G-EhkViG
- ISO 26262
  - Guidelines to protect road users (drivers and pedestrians) from injuries caused by faults in vehicle electronics and software
- Item
  - scope of your development
- HARA (Hazard Analysis and Risk Assessment)
  - judge the risk to human life if your item is faulty
  - define a set of ```Safety Goals``` (high level safety requirements)
- Safety Goals
  - define ```ASIL``` (Automotive Safety Integrity Level)
  - ASIL A (lowest stringent), ASIL B, ASIL C, ASIL D (highest stringent)
  - define ```functional safety concepts``` and ```functional safety requirements```
    - when detecting faulty situation and how to react it
  - define ```technical safety concepts``` and ```technical safety requirements```
  - ```safety mechanism```
    - implementation of safety requirements in system, HW, SW with V-model 
- production, operation, service and decommissioning
  - part 7
- Configuration management (Automotive SPICE)
  - part 8
- for semiconductor
  - part 11
- Summary
  - functional safety prevents people from harm caused by malfunctioning electronics
  - the development steps and efforts depend on the ASIL
  - develop a safety concept with safety requirements
  - implement and test these requirements on all levels
  - perofrm safety analysis
  - have an independent person confirm the results of important development activities
  - provide an argumentation for safety in a safety case
  - functional safety requires appropriate measures to assure functional safety throughout the whole lifetime of vehicles
  - there is no functional safety without safety management

#### ISO 26262 – Concept Phase of Functional Safety
- https://www.youtube.com/watch?v=UPj6rNMPB8Y
- ![image](https://github.com/hugochang1/Tutorial/assets/6143237/aaac8ed4-ec60-41e0-bd0d-0d6be0ab935b)
- Item definition
  - your product
  - there are one or more interacting E/E systems that implement the desired fucntion
  - make available all kinds of requirements for the item
  - define the boundary of the item
- impact analysis
  - shows how you should adjust the safety lifecycle and which safety activities you need
  - the item is either a new development, modification, or the existing item in a modified environment
  - perform an impact analysis to determine the necessary safety activities
  - this one is usually performed by carmaker
- Hazard analysis and risk assessment (HARA)
  - describe operational situations and operating modes
  - determine the hazards in case of faults
  - for relevant harzardous events determine the ASIL with which the item needs to be developed
    - Severity of harm (S)
    - Probability of exposure to the operational situation (E)
    - Controllability to avoid harm (C)
    - ![image](https://github.com/hugochang1/Tutorial/assets/6143237/06b14582-2085-4bd1-8ecd-de31ad793003)
  - Safety Goals
  - perform a hazard analysis and risk assessment to scale the safety activities
  - formulate safety goals
- functional safety concept
  - derive functional safety requirements from safety goals
    - fault avoidance
    - fault detection
    - fault control
    - safe state
    - degraded functionality
    - driver warnings
  - functional safety requirements (FSR)
    - verify the functional safety concept for its ability to mitigate the hazards
    - a. architectural elements
    - b. measures external of the item
    - assign functional safety requirements to systems for implementation
    - describes in a comprehensive way how the hazards should be mitigated

#### ISO 26262 – Functional Safety at the System level
- https://www.youtube.com/watch?v=NhJX6JPI0_8
- TBD

### Wiki
- https://en.wikipedia.org/wiki/ISO_26262
- 1st edition ISO 26262:2011
- 2nd edition ISO 26262:2018
- IEC 61508 (Industrial/General, ISO 26262 is an adaption with minor differences)

### What is ISO 26262 (Synopsis)
- https://www.synopsys.com/automotive/what-is-iso-26262.html
- Scope: SW, HW, Electrics, Optics, Hydraulics, Pneumatics, etc.
- System level - a separate descipline
  - shall define the requirements for each individual technology
  - Shall systematically integrate them
- R&R
  - concept phase: carmaker
  - system phase: tier-1
- System engineer
  - designs this level including mechanisms for error detection and handling
- Safety activites need to be coordinated at a system level
- System level
  - Technical safety concept
    - HW level
    - SW level
  - System and item inegration and testing

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

### Zephyr
- https://www.zephyrproject.org/safety-and-zephyr-rtos/

### Terms
- RPN (Risk Priority Number)
  - show the probability of potential risk

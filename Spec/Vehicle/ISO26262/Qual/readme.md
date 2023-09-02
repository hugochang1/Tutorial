# Qualcomm Presents: How to Achieve SoC FuSa Compliance
- https://www.youtube.com/watch?v=68Y7X0uu3Ig

### SW module selection
- 3 Types
  - SW modules don't directly impact safety-critical modules (ex: libc)
  - security-related SW which is not directly used in safety (ex: switch)
    - use SW qualification (black-box testing) (ISO26262 8-12)
    - use ASIL decomposition
  - others, need to follow complete ISO26262 which take a lot resources

### working across multiple teams
- tailor the components for different teams and the rationale how it is achieved safety requirement
- request most of teams to follow a certain tool
  - few teams cannot use a certain tool, then they need to provide the report
- check the tool qualification
  - tool qualification ISO26262 8-11
- customers want to know how their reuqirements are traced to internal reuqirements
  - and how to trace to test plans and implementation (ex: static analysis, violation code coverage goals)
- present safety case to accessor

### initiation of project
- use Jama as requirement management
- check HW architectural metrics
  - what are the SW assumptions of used data
- use above assumptions as SW safety requirements
- to archieve safety
  - check ASIL decompoition to reduce ASIL if possible
  - add safety mechanisms in the interesting points
- SW safety requirement
  - stack overflow detection, watchdog monitoring, fault and error handling
- customer may request to reduce the overhead of safety mechanism and keep the same level of safety

### Architectural design
- processor vendors
  - how to release SW, review their recommands, static analysis code coverage, design plan
- OS selection to run on specific proprietary processor
  - select OS which is complient with ASIL
- SW usage with no ASIL
  - check performance, power, thermal, dynamic clock, voltage scaling, ...etc.
  - have the scalable SW (configurable for safety and non-safety)
- freedom from interference
  - all of processor (ex: proprietary processor, AP processor, safety processor) need to meet freedom from interference
  - System-level MMU and MMU for each processor
  - scheduling mechanisms

### Integration of 3rd party OS and 3rd party SW
- 3 types
  - 3rd party SEooC SW without any change (ex: QNX OS)
    - they don't change their SW to fix our needs
    - has to use their SW based on their assumptions
  - 3rd party SEooC SW with slight change 
    - need to work closely to them
  - 3rd party SW with QM (ex: open source, compiler, C libraries)
    - may need to buy test suites from other companies for SW qualification
- question to 3rd party SW
  - what they're used for
  - how long they're used for
  - whether it's a SEooC or not

### Tool selection for static analysis
- choose to use Parasoft
- use MISRA C compliance for static analysis
- tool can support multiple compilers, multiple OS
- tools is certified for ASIL D SW development
- can be integrated into our CI

### Tool selection for code coverage
- choose to use Parasoft
- need to support customized simulators
- need tool vendor to work closely for customization

### Static analysis and code coverage goals
- OS is hard to meet MISRA rule, need tailor
- code coverage is 100%, but OS may be around 95% (need to review not cover parts)

### Fault Injection Testing
- the goal is to ensure all faults can be handled correctly
- need FMEA from HW team to decide how to FIT during UT, IT
- provide API to generate faults (ex: corrupt PCIe packets, corrupt camera frame, ...etc.)
- use the special module to test all faults case
- use the debugger and set break point to change the input value or register value
- customer will also need to know how to generate FIT to ensure they can ensure all faults are handled correctly
  - provide the detail FIT and script to customers

### Summary
- Architect design first, don't jump into coding and implementation
- need to have strong evidence and argumentation
- external assessment take ~6 omnths
  - suggest to have consultants for each milestones

# System Design Interview: A Step-By-Step Guide
- https://www.youtube.com/watch?v=i7twT3x5yv8

- 4-step framework
  - step1: understand the problem and establish design scope (5 min)
  - step2: propose high-level design and get buy-in (20 min)
  - step3: design deep dive (15 min)
  - step4: wrap up (5 min)


- step1: understand the problem and establish design scope (5 min)
  - ask questions to fully understand the problems
    - clarify the requirements
      - why to build this system?
      - who are users?
      - what features we need?
        - prioritize the order of each feature and focus on the top few features
        - make sure interviewer agrees to the feature lists
      - ask non-functional requirements
        - major: performance, scale
        - minor: accuracy, security, consistency
  - output of this stage
    - features requirements
    - non-functional requirements


- step2: propose high-level design and get buy-in (20 min)
  - Don't explain to detail in this phase
  - 1. API design
    - define API input parameters and output response
    - what is underlying communication approach
      - ex: socket (TCP, UDP), IPC (file, mmap), http, tls, ...etc.
      - we may explain why we choose this one?
    - call flow
      - 1-way setting or control
      - 1-way data output
      - 2-way communication
  - 2. high level design diagram
    - check whether it can meet all requirements
  - 3. data model and schema
    - data access pattern (ex: database indexing options)
    - read/write ratio
  - 4. review the design whether it can meet the requirements
  - output
    - maintain a list of discussion points for step3
      - database scaling
      - high oncurrency
      - failure scenarios


- step3: design deep dive (15 min)
  - Discuss
    - 1. TODO items in high-level design
    - 2. discuss with interviewer what we should discuss first based on high-level design
    - 3. how to achieve non-functional requirements
    - 4. failure scenarios and recovery flow
    - 5. check with each module and discuss the detail if needed
  - flow
    - articulate the problem
    - come up with at least two solutions
      - which protoocls or algorithms we use and why
    - discuss the trade-offs of the solutions
    - pick a solution and discuss it with the interviewer

- step4: wrap up (5 min)
  - summarize the design
    - end to end flow
    - potential bottleneck
    - trade-off
    - improvement opportunities

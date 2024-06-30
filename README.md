# Deadlock-Detaction-And-recovery
Deadlock is a situation in which two or more competing actions are each waiting for the other to finish, preventing any from proceeding. It typically arises in multitasking and resource allocation scenarios.

## Examples of Deadlock:
Resource Allocation: Processes holding resources and waiting for additional resources held by others.
Synchronization: Multiple processes waiting indefinitely for a lock.
Networking: Two devices waiting for each other to release a resource.
Deadlock Detection
## Algorithm Overview
Resource Allocation Graph (RAG): Models resource allocation and process-to-resource relationships.
Cycle Detection: Checks for cycles in RAG to identify deadlock.
Example
Consider processes P1, P2, P3, and resources R1, R2, R3. If P1 holds R1 and requests R2, P2 holds R2 and requests R1, and P3 holds R3 and requests R2, a deadlock is detected due to the circular dependency.

## Deadlock Prevention
Strategies
Mutual Exclusion: Ensure at least one resource is not shareable.
Hold and Wait: Acquire all necessary resources at once.
No Preemption: Only release resources voluntarily.
Circular Wait: Impose a total ordering of all resource types and require processes to request resources in order.
Example
To prevent the scenario mentioned above:

Use mutual exclusion to ensure P1 and P2 cannot both hold R1 and R2 simultaneously.
Implement a policy where processes request resources in a fixed order, such as R1, R2, R3

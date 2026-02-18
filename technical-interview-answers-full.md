# Technical Interview Answers — Full List (Raytheon / Bloomberg / Accenture style)

**Use this to study.** Each question has a short, say-it-out-loud answer. Grouped by topic so you can cram by bucket.

---

## 1. Object-Oriented Programming (OOP)

### What is OOP? / Briefly describe OOP / Explain OOP to me
**Answer:** Programming organized around **objects** — bundles of data and the behavior that operates on that data. You model the problem with classes and objects instead of just functions and globals.

### What are the four / basic principles of OOP?
**Answer:**  
1. **Encapsulation** — Hide internal state; expose behavior through a clear interface.  
2. **Abstraction** — Expose only what matters; hide implementation details.  
3. **Inheritance** — A child class reuses and extends a parent class (“is-a”).  
4. **Polymorphism** — Same interface, different behavior (e.g. base pointer, derived behavior).

### What is a class? / Explain classes and objects
**Answer:** A **class** is the blueprint (data + methods). An **object** is an instance of that class created at runtime.

### What is inheritance? / Define inheritance and give an example / Explain inheritance (simple)
**Answer:** A derived class reuses and extends a base class. Example: `Dog` inherits from `Animal` and adds `bark()`; `Dog` “is-a” `Animal`.

### What is polymorphism? / Class polymorphism / Define polymorphism and give an example
**Answer:** Same interface, different behavior. Example: `Base* b = new Derived(); b->foo();` — the call to `foo()` runs the derived implementation. Enables writing code against the base type while behavior depends on the actual type.

### What is a virtual function? / Why and how do you use it? / Syntax
**Answer:** A function that enables **runtime polymorphism**. Used so that when you call through a base pointer/reference, the derived implementation runs.  
**Syntax:** `virtual void foo();` in base. Override in derived with `void foo() override;`.

### Can you inherit a static parent method?
**Answer:** The derived class can *call* the static method (e.g. `Base::staticFoo()` or `Derived::staticFoo()` if not hidden), but there’s **no polymorphism** — static methods belong to the class, not to instances, and are not overridden.

### What is an overloaded operator?
**Answer:** Custom behavior for operators (e.g. `+`, `==`, `<<`) for your type. Example: `bool operator==(const MyType& other) const;` so you can write `a == b`.

### Method overloading vs overriding
**Answer:**  
- **Overloading** — Same method name, different parameters (compile-time).  
- **Overriding** — Derived class replaces base implementation of a virtual method (runtime polymorphism).

### Abstract class vs interface / Compare and contrast
**Answer:**  
- **Abstract class** — Can have data members and some implemented methods; at least one pure virtual (`= 0`).  
- **Interface** — Typically only pure virtual methods (no implementation, no data). In C++ we often use an abstract class with all pure virtuals as an “interface.”

### What components are required in an abstract interface?
**Answer:** Pure virtual methods that define the contract — no implementation in the interface, only declarations. Implementations live in concrete classes.

### Can you describe an interface?
**Answer:** A contract: a set of method signatures that implementing classes must provide. In C++ this is usually an abstract class with only pure virtual methods.

### What makes Java or C++ able to create object-oriented programs?
**Answer:** They support **classes**, **inheritance**, **encapsulation**, and **polymorphism** (e.g. virtual functions in C++, method overriding in Java). You can define types that bundle data and behavior and build hierarchies.

### Benefits of using an object-oriented language
**Answer:** Reuse (inheritance, composition), clearer structure (encapsulation), flexibility (polymorphism), and modeling real-world “things” as objects. Easier to maintain and extend large codebases.

### How do you implement inheritance in OOP?
**Answer:** Define a base class with data and methods; define a derived class that inherits (e.g. `class Derived : public Base`) and add or override members. Use `virtual` for methods that should be overridable.

### Give an example of polymorphism in OOP
**Answer:** `Shape* s = new Circle(); s->draw();` — `draw()` is virtual; `Circle::draw()` runs. Same call, different behavior by actual type.

### What is the difference between NULL and void in C++?
**Answer:** **NULL** (or `nullptr`) is a null pointer value — “points to nothing.” **void** is a type meaning “no type” — used for functions that return nothing (`void foo()`) or as a generic pointer type (`void*`).

### What is the difference between a struct and a class in C++?
**Answer:** Only default access: **struct** defaults to `public`, **class** defaults to `private`. Otherwise they’re the same (both can have methods, inheritance, etc.).

### What is the difference between C and C++?
**Answer:** C is procedural; C++ adds OOP (classes, inheritance, polymorphism), templates, RAII, STL, and stricter type checking. C++ is a superset in spirit but not strictly (e.g. `void*` rules differ).

### When would you use Java over C++, and why?
**Answer:** Java when you want portability, a large standard library, managed memory (GC), and faster development; C++ when you need direct control, no runtime overhead, real-time/embedded, or maximum performance.

---

## 2. C/C++ — Language details

### ++i vs i++
**Answer:** **++i** (pre-increment): increment first, then use value. **i++** (post-increment): use current value, then increment. Prefer `++i` when you don’t need the old value (no unnecessary copy for iterators).

### Explain macro expressions
**Answer:** Macros are preprocessor text substitution. `#define SQUARE(x) ((x)*(x))` — every `SQUARE(expr)` is replaced before compile. Pitfalls: no type checking, double evaluation (use parentheses and avoid side effects). Prefer `inline` functions or `constexpr` when possible.

### Create a program related to endianness
**Answer:** Endianness is byte order in memory. Little-endian: LSB first; big-endian: MSB first. Program idea: cast a `uint32_t` to `uint8_t*` and print bytes in order — if the first byte is the LSB, it’s little-endian.

```c
#include <stdint.h>
#include <stdio.h>
int main() {
    uint32_t x = 0x01020304;
    uint8_t *p = (uint8_t*)&x;
    printf("%02x %02x %02x %02x\n", p[0], p[1], p[2], p[3]);
    // Little: 04 03 02 01; Big: 01 02 03 04
    return 0;
}
```

### Do you use the Standard Template Library (STL)?
**Answer:** Yes when I use C++. STL gives containers (vector, map, set), iterators, and algorithms (sort, find). I’ve used `std::vector`, `std::string`, and algorithms. For embedded or very constrained code I might use minimal or no STL.

### Which of C, C++, Java, and Python are strongly typed?
**Answer:** C and C++ are statically typed (types checked at compile time). Java is statically typed. Python is strongly typed at runtime (every object has a type) but dynamically typed (variables can refer to any type). “Strong” often means few implicit conversions — all four have some degree of strong typing; C/C++/Java are static, Python is dynamic.

---

## 3. Memory / Arrays / “Given code” questions

### Given a pointer to a large enough array of bytes, how would you patch the given objects into this single byte array?
**Answer:** Treat the byte array as raw storage. For each object: compute size and alignment, place the object at an offset that respects alignment (e.g. `alignof(T)`), use placement `new` in C++ or `memcpy` in C. Advance the offset by the size (and padding for alignment). Ensure the buffer is large enough and aligned (e.g. `alignas(max_align_t)`).

### What are the logic flaws in the given code?
**Answer:** (Generic) I’d look for: off-by-one or wrong loop bounds, null/dangling pointer use, uninitialized variables, wrong conditions (inverted logic), resource leaks (no free/close), integer overflow, or misuse of types. I’d trace one concrete input and check edge cases.

### Implement a function to find the largest integer value in an int32_t array
**Answer:** One pass, track max. Assume non-empty or handle length 0.

```c
#include <stdint.h>
int32_t max_int32(int32_t *arr, size_t n) {
    if (n == 0) return 0; /* or error */
    int32_t m = arr[0];
    for (size_t i = 1; i < n; i++)
        if (arr[i] > m) m = arr[i];
    return m;
}
```

---

## 4. Algorithms (single pass / no extra structures)

### How would you develop an algorithm to detect if one number in an array of 100 unique integers goes to 0 without extra data structures and only one pass?
**Answer:** You can’t “detect that one number goes to 0” in one pass without knowing which element or having extra state — the problem is under-specified. If they mean “detect if any element is 0”: one pass, compare each element to 0. If they mean “track which element becomes 0 over time,” that implies multiple passes or external state. I’d clarify: “Do you mean ‘is there an element equal to 0?’ — then one linear scan.”

### Can you find a missing number from a list?
**Answer:** If it’s 1..N with one missing: compute expected sum `S = N*(N+1)/2`, sum the array, missing = `S - sum`. Alternative: XOR all 1..N and XOR all array elements; the result is the missing number (works for one missing).

---

## 5. Data structures

### What is a linked list? / Explain how linked lists work and how to connect them
**Answer:** A sequence of nodes; each node holds data and a pointer to the next (and optionally previous). Connection: set `node->next` (and `prev` for doubly linked) to the next node. You maintain a head (and maybe tail) pointer. No contiguous block; insert/delete at a known node is O(1) if you have the node.

### Implement a linked list (C++) / Write code to implement a linked list
**Answer:** Node with `data` and `next`; list class holds `head`, provides insert/delete/search. Example skeleton:

```cpp
struct Node { int data; Node* next; };
class LinkedList {
    Node* head = nullptr;
public:
    void pushFront(int x) {
        Node* n = new Node{x, head};
        head = n;
    }
    // ... delete, find, destructor (walk and delete nodes)
};
```

### Explain how to implement a stack
**Answer:** LIFO. Operations: push (add on top), pop (remove top), peek/top. Implementation: array (with top index) or linked list (push/pop at head). Need to handle full/empty.

```c
/* Array-based stack: top is index of next free slot */
int stack[100], top = 0;
void push(int x) { stack[top++] = x; }
int pop(void)    { return stack[--top]; }
```

### Explain how to delete leaf nodes from a BST under certain conditions
**Answer:** A leaf has no left and no right child. Traverse (e.g. post-order so we can delete children first). At each node, if it’s a leaf and it meets the condition (e.g. value < K), delete it and set the parent’s corresponding pointer to null. Parent is updated when we return from the child.

### Should the parent node be deleted after a leaf node is deleted in the BST?
**Answer:** Not automatically. Delete only the leaf if the condition says so. The parent is deleted only if *it* becomes a leaf after children are removed and *it* meets the same (or your) deletion rule. So: first delete qualifying leaves, then possibly recurse so that parents that become leaves are reconsidered.

### Which data structures did you use in a project? Why?
**Answer:** (Tailor to your project.) Example: “Lists/arrays for sequences, hash maps for lookups by key, trees when I needed ordered traversal. I chose based on access pattern and complexity (e.g. O(1) lookup vs ordered).”

### Can you explain some basic data structures?
**Answer:** **Array** — contiguous, indexable. **Linked list** — nodes and pointers, O(1) insert/delete at known position. **Stack** — LIFO. **Queue** — FIFO. **Hash table** — key→value, O(1) average. **BST** — ordered, O(log n) average for search/insert/delete.

---

## 6. Sorting / recursion

### Give examples of sorting algorithms. Pick an efficient one and explain. Data structure in C++?
**Answer:** Examples: bubble, insertion, merge sort, quicksort. **Quicksort:** pick pivot, partition into smaller and larger, recurse. Average O(n log n); vector or array. In C++ I’d use `std::vector` and `std::sort` (usually introsort).

### Write a program using recursion
**Answer:** Classic: factorial or Fibonacci. Base case stops recursion; each call reduces the problem.

```c
int fact(int n) {
    if (n <= 1) return 1;   /* base case */
    return n * fact(n - 1);   /* recursive case */
}
/* Fibonacci: fib(n) = fib(n-1) + fib(n-2), base fib(0)=0, fib(1)=1 */
```

---

## 7. Operating systems / threading

### Multiprogramming vs multitasking
**Answer:** **Multiprogramming** — multiple programs loaded in memory; one runs while others wait (e.g. I/O). **Multitasking** — CPU time is shared; the system switches between tasks so they appear to run concurrently (time slicing).

### What is a thread? / Explain how threads work
**Answer:** A thread is a lightweight unit of execution within a process. Threads share the process’s memory and resources; each has its own stack and register state. The OS schedules threads; they can run in parallel on multiple cores or be time-sliced on one core.

### What is the difference between a semaphore and a mutex?
**Answer:** **Mutex** — mutual exclusion; one owner; for protecting a critical section. **Semaphore** — counter; can allow N threads (e.g. resource count); no notion of “owner.” A binary semaphore (0/1) can approximate a mutex but mutex is better when you want ownership (e.g. for priority inheritance).

### Explain lock mechanisms in a multi-threaded environment
**Answer:** **Mutex** — lock before critical section, unlock after; only one thread holds it. **Semaphore** — wait (decrement) / signal (increment); can allow N threads. **Spinlock** — busy-wait instead of sleeping; good for very short critical sections. **Condition variables** — wait for a condition; another thread signals when the condition might be true.

### How do you handle process synchronization in operating systems?
**Answer:** Use synchronization primitives: mutexes to protect shared data, semaphores to limit or signal resources, condition variables to wait for events. Design to avoid deadlock (e.g. lock ordering, timeouts) and race conditions (all shared access under a lock or lock-free algorithms).

### Can you describe a scheduling system in the context of operating systems?
**Answer:** The scheduler decides which process/thread runs and for how long. Policies: FCFS, SJF, priority, round-robin (time slice). Goals: fairness, throughput, responsiveness. Context switch: save current state, load another, switch to its context.

---

## 8. Debugging / memory / performance

### How do you debug code that you did not write? / How do you debug? / How do you go about debugging?
**Answer:** 1) Reproduce (same inputs/config). 2) Understand (read code, logs, comments). 3) Isolate (narrow to a function or path). 4) Inspect (logs, breakpoints, prints). 5) Hypothesize (code vs config vs data). 6) Fix and verify (rerun, regression check).

### How do you debug a specific set of code?
**Answer:** Reproduce the failure, then focus on that code path: add logs or breakpoints, check inputs and state at key points, step through, verify assumptions. Compare expected vs actual and fix the root cause.

### How would you debug CPU thrashing?
**Answer:** CPU thrashing = too much time in context switching or paging, little useful work. Fixes: reduce number of runnable threads/processes, increase time slice or adjust scheduling, add memory or reduce working set to avoid page thrashing. Measure with perf/CPU usage and identify what’s switching or paging.

### Explain how you identified and fixed a memory leak. What tools?
**Answer:** Tools: Valgrind (memcheck), AddressSanitizer (ASan), or platform-specific leak detectors. Run the program under the tool; it reports allocations not freed. Correlate with stack traces to find the leaking call sites. Fix by ensuring every allocation has a matching free (or use RAII/smart pointers).

### How do you identify and resolve a stack overflow in a Linux environment?
**Answer:** Causes: very deep recursion or very large stack-allocated data. Identify: crash with “stack overflow” or segfault in a recursive call; use `gdb` backtrace or `ulimit -s` to see stack size. Resolve: reduce recursion depth (iterate instead), move big buffers to heap or make them static, or increase stack limit only if appropriate.

### If you had a private method in a class, how would you test it?
**Answer:** (1) Test via the public API that uses it (preferred). (2) Add a test-only friend or accessor. (3) Use a test subclass that exposes or calls the method. (4) Refactor so the logic is in a testable function (e.g. free function or protected utility). Prefer (1) or (4).

---

## 9. Testing / process / tools

### Which automated testing tools have you used?
**Answer:** JUnit (Java), pytest (Python), Google Test (C++). For C I’ve used simple test runners or assert-based tests. Sometimes CI runs tests (e.g. GitHub Actions).

### Describe your experience with unit testing. New tests or existing?
**Answer:** (Tailor to yourself.) “I’ve written unit tests for new code and added tests for bug fixes. I’ve also maintained and run existing suites. I prefer small, focused tests and clear assertions.”

### Do you have experience with JUnit testing?
**Answer:** (If yes:) “I’ve used JUnit for unit tests in Java — @Test, assertions, setup/teardown.” (If no:) “I haven’t used JUnit; I’ve used similar concepts in other languages (pytest, Google Test).”

### Tell me about the Agile process
**Answer:** Iterative development in short cycles (sprints). Work is in a backlog; team plans a sprint, does standups, demo, retrospective. Emphasizes feedback, adaptability, and delivering working software. I’ve worked in sprint-based teams and used boards (e.g. Jira) for tasks.

### Have you worked with UML? / Have you ever used UML?
**Answer:** (Tailor.) “I’ve used class diagrams, sequence diagrams, and sometimes state diagrams for design or documentation — on paper or in tools. I use them to communicate structure and behavior.”

### How do you handle configuration management?
**Answer:** Version control (Git) for code and, when appropriate, config-as-code. Tagging/releases for known good versions. For secrets, use env vars or a secrets manager, not committed files. Document how to build and run for a given version.

---

## 10. WinForms (if asked)

### How would WinForms benefit development in terms of rapid development and performance?
**Answer:** WinForms gives drag-and-drop UI and a rich control set, so you can build desktop UIs quickly. It’s native to Windows and can be performant for standard forms; for heavy graphics or cross-platform, WPF or other stacks might be considered.

### How does using WinForms improve ergonomics for users?
**Answer:** Familiar Windows look and feel, standard controls and keyboard navigation, resizable windows, accessibility support. Consistent UX with other Windows apps.

### What advantages does WinForms offer for VS debugger and IDE support?
**Answer:** Tight integration with Visual Studio: designer, debugger, IntelliSense, and easy attach-to-process for debugging Windows desktop apps.

---

## 11. Systems / embedded / interfaces

### Have you created software models of hardware before?
**Answer:** (Tailor.) “I’ve written code that simulates or interfaces with hardware — e.g. state machines for device behavior, or drivers that talk to peripherals. I haven’t built full hardware simulators.” Adjust for your experience.

### What types of data interfaces and standards have you worked with?
**Answer:** (Tailor.) Examples: UART, SPI, I2C, TCP/IP, REST, file formats (CSV, JSON). In embedded: UART, NMEA, BLE. In backend: HTTP, config files.

### Describe how embedded systems work
**Answer:** Dedicated systems with a specific function, often real-time and resource-constrained. Software runs on microcontrollers or embedded CPUs, interacts with sensors/actuators, and may use minimal OS or bare metal. Typical concerns: timing, memory, power, reliability.

### How would you detect a false DHCP server?
**Answer:** Rogue DHCP servers can hand out bad IPs. Detection: use DHCP snooping on switches (trust only known ports), or run a tool that compares DHCP replies from different sources. In enterprise, restrict which ports can send DHCP offers and monitor for unexpected servers.

### What AWS services have you utilized previously?
**Answer:** (Tailor.) Examples: EC2, S3, Lambda, RDS, CloudWatch. Say what you’ve actually used; if minimal, say you’re familiar with core concepts and have used [X].

### Can you write a kernel module to display all processes with 3 or more file descriptors open?
**Answer:** Concept: kernel module that iterates over processes (e.g. via task list), for each open file count (e.g. files in `files_struct`), and print or log those with count ≥ 3. Implementation is platform- and kernel-version specific; I’d refer to the kernel API for iterating tasks and file descriptors. “I can outline the approach and would use kernel APIs and existing examples for the exact code.”

### Can you explain how to suspend a task in VxWorks?
**Answer:** VxWorks uses task control: `taskSuspend(taskId)` suspends the given task; `taskResume(taskId)` resumes it. The task must be created (e.g. `taskSpawn`) and identified by its ID.

### What tool would you use to view the status of all tasks in VxWorks?
**Answer:** Shell commands: `i` or `tw` (task show) list tasks and status. In the debugger, task-aware views show state. Exact command set depends on the VxWorks version (e.g. `i` for Wind River).

---

## 12. Design / databases / other

### What are five considerations when developing an online banking application?
**Answer:** Security (auth, encryption, secure sessions), compliance (e.g. regulations), availability and reliability, data integrity (transactions, audit trail), and usability (clear flows, error handling). Can add: fraud detection, scalability.

### What would be an ideal structure of a database for certain types of objects?
**Answer:** (Generic.) Tables map to entity types; primary keys and foreign keys enforce identity and relationships. Normalize to reduce redundancy; denormalize sparingly for read performance. Indexes on common query columns. “For ‘certain types of objects’ I’d need the exact entities and access patterns to propose a schema.”

### What is serialization?
**Answer:** Converting an object or data structure into a byte stream (or string) for storage or transmission. Deserialization reconstructs the object from that form. Examples: JSON, XML, Protocol Buffers, or binary formats.

### Can you develop a tool that will search existing software for specific criteria?
**Answer:** Yes. Approach: walk the codebase (files/dirs), search for patterns (regex or AST if needed), filter by criteria (e.g. function name, string literal). Tools: `grep`/`ripgrep`, `find`, or a small script. For “criteria” like “all call sites of X,” a simple script or IDE search is enough; for complex rules, use or build a lightweight static analysis.

### Can you solve design and coding problems on a whiteboard?
**Answer:** Yes. I’d clarify requirements, outline approach, then write pseudocode or code. I’m comfortable with arrays, pointers, basic data structures, and walking through an example.

---

## 13. Experience / “Tell me about…” (tailor yourself)

### Can you discuss your experience with Python?
**Answer:** (Tailor.) Example: “I’ve used Python for scripting, automation, data processing, and small tools. I’m comfortable with standard library, basic OOP, and common idioms.”

### Can you explain your experience with software methodologies?
**Answer:** (Tailor.) “I’ve worked in Agile/sprint-based teams: backlog, sprints, standups, reviews. I’ve also done more ad-hoc or ticket-driven work. I adapt to the team’s process.”

### Can you provide more detail about the chess AI program you wrote?
**Answer:** (Your project.) Outline: goal, data structures (e.g. board representation, search tree), algorithm (e.g. minimax/alpha-beta), and what you learned.

### What is your experience with databases?
**Answer:** (Tailor.) “I’ve written SQL queries, designed simple schemas, and used [e.g. SQLite, Postgres] in projects. I understand normalization, keys, and basic indexing.”

### Do you have experience programming in NX?
**Answer:** (Tailor.) NX = Siemens NX (CAD/CAM). If you have none: “I don’t have NX experience; I have experience with [related: CAD APIs, geometry, or similar].” If yes, describe what you did.

### What programming languages are you proficient in?
**Answer:** (Tailor.) List languages and level, e.g. “C and C++ for systems and embedded; Python for scripting; some Java/JavaScript from coursework or side projects.”

### Can you explain what a garbage collector is?
**Answer:** A runtime component that automatically reclaims memory that is no longer reachable. It traces live references (e.g. from stack and globals) and frees objects that aren’t referenced. Benefits: no manual free, fewer use-after-free bugs; downsides: pauses, nondeterminism, extra memory. Java, Python, Go use GC; C/C++ do not.

---

## Quick reference table

| Topic | One-line hook |
|--------|----------------|
| **OOP 4 pillars** | Encapsulation, abstraction, inheritance, polymorphism |
| **Virtual function** | Enables runtime polymorphism; override in derived |
| **Overload vs override** | Overload = same name, different params; override = replace virtual |
| **Struct vs class** | Only default access: struct public, class private |
| **++i vs i++** | Pre: increment then use; post: use then increment |
| **Endianness** | Byte order: little = LSB first, big = MSB first |
| **Linked list** | Nodes with next (and prev); head/tail; O(1) insert at known node |
| **Mutex vs semaphore** | Mutex = one owner; semaphore = counter, no owner |
| **Stack overflow** | Deep recursion or huge stack vars; reduce depth or move to heap |
| **Memory leak** | Valgrind/ASan; match every alloc with free or use RAII |
| **CPU thrashing** | Too much context switch/paging; reduce threads or add memory |

---

*End of list. Practice answering out loud; keep answers to 30–90 seconds. For “given code” or “given problem” questions, the interviewer will supply the actual code or problem — use the general approaches above.*

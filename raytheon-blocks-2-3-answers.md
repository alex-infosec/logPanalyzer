# Raytheon Prep — Blocks 2 & 3: C++ and Debugging (Drill Sheet)

**Use this to practice out loud.** Answer in **Concept → Example → Tradeoff** for C++; use the **framework + story** for debugging. Keep answers 30–90 seconds.

---

## Block 2: C++ / Programming Language

### How much C++ have you written? / How well do you know C++? / Where have you used C++ or C?

**Concept:** I’ve used C and C++ in two places: embedded research (UF) and production-style services (Ryder).

**Example:**  
- **UF / research:** C for peripherals on the shear — UART, reading NMEA from the RTK module, building the data structures. C++ for parsing that data and sending it over BLE to the hub. I had to wire C and C++ in the build (CMake, gcc vs g++).  
- **Ryder:** C in long-running Linux daemons — config loading, parsing asset lines, logging. Config structs, string handling with bounded buffers, conditional logic.

**Tradeoff:** I’m not claiming expert-level C++ templates or STL; I’m strong on the level you need for embedded and systems — pointers, memory, parsing, and safe string handling.

---

### Difference between C and C++

**Concept:** C is procedural and close to the hardware; C++ adds OOP and richer abstractions.

**Example:** On the RTK shear I used C for the peripheral layer (UART, reading raw NMEA) and C++ for parsing and data handling. At Ryder it was mostly C — structs, file I/O, string parsing with `strncpy` and bounds checks.

**Tradeoff:** C when you want minimal overhead and direct control; C++ when you want classes, inheritance, or easier data management. For embedded I often mix both and respect the linker (extern "C", etc.).

---

### Difference between C++ and Java / Advantages and disadvantages of Java

**Concept:** C++ gives you direct memory control and no mandatory runtime; Java gives you a managed heap, portability, and a big standard library.

**Example:** In C++ I’ve dealt with stack vs heap, pointer lifetime, and buffer sizes (e.g. `strncpy` with a fixed buffer). I haven’t shipped Java in production, but I’ve seen it in coursework and in our hub’s map/API side.

**Tradeoff:** C++ — more control and performance, more responsibility for memory and safety. Java — easier to get something running, GC and type system help, but less control over layout and latency. For real-time or embedded, C++ (or C) is usually the fit.

---

### What is a null pointer? What happens if you dereference one?

**Concept:** A null pointer is a pointer that doesn’t point to any valid object — often represented as zero. Dereferencing it is undefined behavior.

**Example:** In practice you get a crash — often a segfault. In the code I’ve written we avoid it by checking before use: e.g. `if (ptr != NULL)` before dereferencing, or designing so we never hold an invalid pointer.

**Tradeoff:** Always validate pointers when they come from outside (config, input, allocators) or when you’re not sure; use defensive checks or safe patterns so you never dereference null.

---

### What OOP concepts are you familiar with? / What is inheritance? / When would you use inheritance vs composition?

**Concept:** I’m familiar with encapsulation, inheritance, and composition. Inheritance is an “is-a” relationship (subclass extends base); composition is “has-a” (object contains another).

**Example:** In my C++ on the shear I used structs/classes to hold parsed data and pass it around — more composition than deep inheritance. At Ryder the code was mostly C with structs (e.g. `Config`) passed by pointer.

**Tradeoff (one-line rule):** Prefer composition when you can — “has-a” is easier to change and test. Use inheritance when you truly have a subtype that substitutes for the base and you need polymorphism. In embedded I lean composition and simple structs unless the design clearly calls for a hierarchy.

---

### Buffer overflow / writing past the end of an array — how do you avoid it?

**Concept:** You avoid it by never writing more than the allocated size. That means tracking size and using bounds in every copy or read.

**Example:** In C we use bounded functions and explicit sizes: `strncpy(dest, src, sizeof(dest)-1)` and then null-terminate; when parsing lines we use a `MAX_LINE` buffer and check length before copying. We compare indices and lengths to buffer size before any write.

**Tradeoff:** Safer functions (`strncpy`, `snprintf`) plus a single convention (e.g. always reserve one byte for `\0`) and validating input length before copying. No raw `strcpy` or unbounded reads on untrusted input.

---

### Stack vs heap — when do you use which?

**Concept:** Stack is automatic per function call — local variables, limited size, fast. Heap is manually allocated (e.g. `malloc`/`free` in C, `new`/`delete` in C++) — for data whose size or lifetime isn’t known at compile time.

**Example:** At Ryder most data was fixed-size structs and buffers on the stack or static. In embedded we keep allocations off the heap when we can for predictability; when we need dynamic size we allocate once at init.

**Tradeoff:** Use the stack when size and lifetime are fixed and small enough. Use the heap when you need dynamic size or lifetime beyond the current function. In real-time systems we minimize heap use and avoid allocating in hot paths.

---

## Block 3: Debugging & Problem-Solving

### How do you approach debugging a problem? / How do you find the root cause? / What steps do you take when something doesn’t work?

**Framework (say this, then one example):**

1. **Reproduce** — Get the same failure with the same inputs/config so you have a reliable test.
2. **Capture** — Use logs (e.g. `grep`, `tail`, `journalctl`) to see what the system did and what error or state it reached.
3. **Correlate** — Map that log or crash to a place in the code (e.g. which branch, which function).
4. **Hypothesize** — Decide if it’s a code bug, bad input, or misconfiguration (don’t assume code first — check config and data).
5. **Fix and validate** — Make the change, rerun the same scenario, confirm logs and behavior. Get confirmation from the ticket owner or stakeholder if needed.

**Example:** At Ryder I didn’t rely on GDB day to day; I used log-driven debugging — reproduce with the ticket’s scenario, grep logs for the error, find the code path, fix, then rerun and confirm.

---

### Tell me about a difficult technical problem you solved

**Story (pick one, keep it STAR):**

**Option A — Wrong log message (INC001):**  
Service logged “Debug mode enabled” when config said `mode=normal`, so troubleshooting was misleading. I reproduced with the config, found the inverted conditional in the code (`if (strcmp(cfg.mode, "debug") == 0)` was wrong), fixed it, rebuilt, and validated that logs matched the config. Ticket owner confirmed.

**Option B — Unactionable error (INC002):**  
On parse failure the log only said “Failed to parse asset” with no input. I reproduced with bad input, found the parse-failure path, and added the offending line to the message (truncated for safety). After that, support could trace bad data; ticket closed.

Use the same structure: situation → task → what you did (reproduce, logs, code change, validate) → result.

---

### How do you handle ambiguity in requirements?

**Framework:** I don’t guess — I clarify and document.

**Example:** When a ticket was vague (“something’s wrong with the batch”), I’d look at the description and logs to see what “wrong” meant, then either ask the ticket owner or my manager for expected vs actual behavior. I’d document what I assumed (e.g. “assuming batch_size=0 should be invalid”) and confirm with the owner before closing. Same in research: when the spec was unclear, we’d align with the faculty lead or the CS lead so we weren’t building the wrong thing.

**One-liner:** Clarify with the person who cares (owner, senior, stakeholder), document assumptions, and validate the fix with them.

---

## Quick reference

| Topic | Your hook |
|--------|-----------|
| **C++ / C use** | UF: shear C/C++ (UART, BLE, parsing). Ryder: daemons, config, parsing, logging. |
| **Null pointer** | Points to nothing; dereference = undefined behavior, crash. Check before use. |
| **Stack vs heap** | Stack = automatic, fixed size. Heap = manual, dynamic size/lifetime. |
| **Inheritance vs composition** | Prefer “has-a” (composition); use “is-a” (inheritance) when you need a real subtype. |
| **Buffer safety** | Bounded copies (`strncpy`, size checks), validate length, null-terminate. |
| **Debugging** | Reproduce → logs (grep, tail, journalctl) → correlate to code → fix → validate. |
| **Ambiguity** | Clarify with owner/senior; document assumptions; validate with them. |

Practice each block out loud until you can hit **Concept → Example → Tradeoff** (or framework + story) in under 90 seconds.

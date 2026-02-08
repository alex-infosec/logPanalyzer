# Raytheon SE I — Real Question Set + Your Mapping

**What people in Software Engineer I / early-career embedded / Raytheon-style roles actually get.**  
Cleaned up, deduped, grouped. Map each category → your STAR or framework. Reuse 2–3 projects, 4–5 frameworks, answer calmly.

---

## 1. Project / Experience Anchors (THEY WILL ASK THESE)

- Tell me about a recent project you worked on
- Walk me through a project you're proud of
- Describe your role and exact responsibilities
- What was your contribution specifically?
- What was the hardest part of that project?
- What would you improve if you did it again?
- Tell me about a time you took something from idea to implementation

**→ Your RTK research STAR.** UF embedded: ESP32/RP2040, RTK GNSS, LIS3DH, cut-force + GPS telemetry, Python analysis. Idea → implementation, role, contribution, hardest part, what you’d improve.

---

## 2. C++ / Programming Language Questions

- How much C++ have you written? / How well do you know C++? / Where have you used C++ or C?
- Difference between C++ and Java / Advantages and disadvantages of Java
- Difference between C and C++
- What is a null pointer? What happens if you dereference one?
- What OOP concepts are you familiar with? / What is inheritance? / When would you use inheritance vs composition?

**→ Concept → Example → Tradeoff.** Ryder: daemons, config, parsing, logging (asset_sync, INC001/002/003). UF: firmware, sensors. Pointers, memory (stack/heap), structs, string safety (strncpy, bounds). OOP vs Java / inheritance vs composition = short, clear tradeoffs. Null pointer: undefined behavior, crash; always check or use safe patterns.

---

## 3. Debugging & Problem-Solving

- How do you approach debugging a problem?
- How do you find the root cause of a crash?
- What steps do you take when something doesn't work?
- Tell me about a difficult technical problem you solved
- How do you handle ambiguity in requirements?

**→ Log-driven framework:** Reproduce → logs (grep, tail, journalctl) → correlate to code → fix → validate. **Difficult problem:** Ryder INC001 or INC002 (wrong log message, unactionable error) — full STAR from dossier. **Ambiguity:** Clarify with ticket owner / senior; document assumptions; validate with owner.

---

## 4. Stress, Deadlines, and Pressure

- How do you handle stress?
- Tell me about a time you were under a tight deadline
- What do you do when multiple tasks are due at once?
- Have you ever missed a deadline? What happened?

**→ Framework:** Scope control + communication + prioritization. One story: e.g. multiple tickets due — prioritized by impact/owner need, communicated status in Teams, got review when blocked. If no deadline story: “I prioritize, communicate early if something’s at risk, and don’t let perfect block done.”

---

## 5. Conflict & Teamwork

- Tell me about a conflict with a teammate
- Describe a disagreement and how you resolved it
- What if you disagree with someone more senior than you?
- How do you handle differing technical opinions?
- How do you work in a team environment?

**→ Low drama, judgment.** Ryder: PR feedback, ticket owner confirmation, senior review — aligned on “done” and evidence (logs, behavior). **Framework:** Listen, state your reasoning and evidence, defer to owner/senior when it’s their call; goal is ship and learn. UF: cross-functional, field data, visualization — same idea.

---

## 6. Growth / Learning / Stretch Questions

- Tell me about a time you were assigned something above your experience level
- How do you learn new technologies?
- What do you do when you don't know something?
- How do you ask for help?

**→ RTK + embedded integration.** Picked up RTK GNSS, LIS3DH, telemetry pipeline, Python analysis; asked for help when stuck; docs, experiments, senior/peer input. **Framework:** Read/docs first, try small, ask with context (“here’s what I tried, here’s where I’m stuck”).

---

## 7. Process / Software Engineering Basics

- What does the software development lifecycle look like?
- Have you worked in a team development environment?
- How do you document your work?
- What tools do you use?
- Experience with Linux / Unix?

**→ Ryder:** Design → code → test → PR → review. ServiceNow tickets, Git (branch, commit, PR), senior review, ticket owner confirmation. **Tools:** VS Code, gcc/g++, make, VPN, SSH, grep, tail, journalctl, systemctl, Git. **Linux:** Full workflow — SSH, logs, services, make, build. **Docs:** Comments, commit messages, ticket notes; runbook-style where it helped.

---

## 8. Motivation / Fit (Often at the end)

- Why did you apply here?
- Why this role?
- Where do you want your career to go?
- What are you looking to learn next?

**→ Calm, grounded.** Mission (national security, defense, radar). Fit: real-time embedded (UF) + C/C++ and Linux in production-like env (Ryder) = contribute to requirements, design, code, test, docs on Radar team. Career: grow in real-time embedded and systems; learn from the team. No hype.

---

## 9. “Soft” Conversational (When it’s going well)

- What's your favorite project and why?
- What did you enjoy most about your work?
- What kind of work do you like doing?
- What excites you about engineering?

**→ Authentic.** RTK/embedded: hardware + software, real data, real impact. Ryder: fixing something and seeing logs green and ticket closed. Real-time, systems, things that matter.

---

## Your Reuse Map (One-Page Mental Roadmap)

| You use | For |
|--------|-----|
| **UF RTK / embedded** | Project anchors, real-time/embedded, growth/learning, favorite project, idea→implementation |
| **Ryder INC001 / INC002** | Technical problem solved, debugging in practice, C/C++ in production |
| **Ryder INC003** | Mistake/failure, config vs code, observability |
| **Log-driven debugging** | How you debug, root cause, steps when something doesn’t work |
| **Ryder process** | Team, SDLC, tools, Linux, documentation |
| **C/C++ from asset_sync** | Language depth, pointers, memory, parsing, tradeoffs |
| **Mission + fit** | Why Raytheon, why this role, career, what you want to learn |

You’re not missing content. You’re learning how to access it under pressure.

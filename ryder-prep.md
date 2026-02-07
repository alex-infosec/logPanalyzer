# Ryder Systems Internship — Interview Prep

**Your one-sentence elevator pitch:**
> I worked as an IT / Systems Intern in Ryder's IT Operations organization, supporting Linux-based backend services for internal logistics and fleet systems by analyzing logs, making small C/C++ fixes, validating behavior on Linux servers, and resolving ServiceNow tickets in collaboration with senior engineers.

---

## Quick Reference

| Item | Answer |
|------|--------|
| **Company** | Ryder System |
| **Title** | IT / Systems Intern |
| **Org** | IT Operations (Enterprise / Fleet Systems) |
| **Location** | Chambersburg, PA distribution center (onsite) |
| **Reporting to** | IT Manager / Systems Manager |
| **Team** | Systems / IT Systems |
| **Systems touched** | IATS (asset/transaction tracking), IFMS (fleet/maintenance data) |

---

## The 4-Sentence Template (Use for Any "Tell me about your work" Question)

1. **Summary** — "At a high level, I worked on ___ in a ___ environment."
2. **Your role** — "My responsibility was ___."
3. **What you did** — "I mainly focused on ___."
4. **Outcome** — "That helped ___."

---

## STAR-Ready Answers

### Situation + Task
- ServiceNow tickets, ad hoc, ticket-driven
- Linux-based backend services for logistics and fleet systems
- C/C++ code in long-running daemons
- Worked with IATS and IFMS; you did not architect or own these systems

### Action
- Analyzed logs (`tail`, `grep`, `journalctl`)
- Made small C/C++ bug fixes (conditional logic, parsing, config handling, logging)
- Validated on Linux servers via VPN/SSH
- Used Git, PRs, senior review
- Collaborated via Teams and ticket owners

### Result
- Logs showed normal behavior
- Service stopped erroring
- Ticket owner confirmed resolution

---

## One Real Failure (Use for "Tell me about a failure" / "Mistake you made")

**Setup:** Thought an issue was a code bug.  
**Root cause:** Configuration mismatch.  
**What you did:**
- Updated code to handle the config safely
- Improved logging so the issue would be visible next time
- Confirmed the fix with the ticket owner

**Takeaway:** You learned to verify config before assuming code failure, and you made the system more observable for future debugging.

---

## Technical Environment

**Local:** VS Code, terminal, gcc/g++, make  
**Remote:** VPN → SSH → Linux servers  
**Tools:** `cd`, `ls`, `grep`, `tail`, `systemctl`, `journalctl`, `ps`, `top`  
**Workflow:** Log-driven debugging, not heavy interactive debugging  
**Version control:** Git — `status`, `pull`, `checkout -b`, `add`, `commit`, PRs, senior review

---

## What a Fix Was "Done"

1. Logs showed normal behavior  
2. Service stopped erroring  
3. Ticket owner confirmed resolution  

---

## Hard Boundaries (Stay Honest — Intern-Level)

- ❌ Did not design system architecture  
- ❌ Did not deploy to production alone  
- ❌ Did not own services end-to-end  
- ✅ Supported, fixed, validated, and learned

---

## Practice Prompts

1. **"Tell me about your role at Ryder."** → Use the 4-sentence template + elevator pitch.
2. **"Describe a technical problem you solved."** → Ticket → logs → C/C++ fix → validation → confirmation.
3. **"Tell me about a time you made a mistake."** → Config mismatch story.
4. **"What tools did you use?"** → ServiceNow, Teams, Linux (grep, tail, systemctl, journalctl), Git, VS Code.
5. **"How did you validate your fixes?"** → Logs, service behavior, ticket owner confirmation.
6. **"What systems did you work with?"** → IATS, IFMS — supported C/C++ components, didn't architect.

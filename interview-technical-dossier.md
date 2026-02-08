# Ryder IT/Systems Intern — Technical Interview Dossier

**Absolute reference: debugging, process, C/C++, integration. Use for STAR answers and study.**

---

## 1. Quick Reference

| Item | Answer |
|------|--------|
| **Company** | Ryder System |
| **Title** | IT / Systems Intern |
| **Org** | IT Operations (Enterprise / Fleet Systems) |
| **Location** | Chambersburg, PA distribution center (onsite) |
| **Reporting to** | IT Manager / Systems Manager |
| **Team** | Systems / IT Systems |
| **Systems** | IATS (asset/transaction tracking), IFMS (fleet/maintenance data) |
| **Work intake** | ServiceNow tickets, Teams messages |
| **Code form** | Long-running Linux services / daemons (C/C++) |

**One-sentence elevator pitch:**  
*"I worked as an IT/Systems Intern in Ryder's IT Operations, supporting Linux-based backend services for internal logistics and fleet systems by analyzing logs, making small C/C++ fixes, validating behavior on Linux servers, and resolving ServiceNow tickets with senior engineers."*

---

## 2. STAR — Full Answers

### 2.1 "Tell me about your work" / "Describe your role"

- **Situation:** ServiceNow-driven work; Linux-based backend services for logistics and fleet (IATS, IFMS); C/C++ in long-running daemons. I did not architect or own these systems end-to-end.
- **Task:** Support and fix issues: incorrect behavior, misleading logs, config problems. Validate on Linux servers and close tickets with owner confirmation.
- **Action:** Analyzed logs (`tail`, `grep`, `journalctl`); made small C/C++ fixes (conditionals, parsing, config handling, logging); validated via VPN/SSH; used Git, PRs, senior review; collaborated via Teams and ticket owners.
- **Result:** Logs showed normal behavior, services stopped erroring, ticket owners confirmed resolution.

---

### 2.2 "Describe a technical problem you solved" (Use INC001 or INC002)

**Option A — Wrong log message (INC001)**  
- **Situation:** Asset sync (IATS) was logging "Debug mode enabled" when config said `mode=normal`; misleading during troubleshooting.  
- **Task:** Fix so logs match config: "Normal mode" for normal, "Debug mode enabled" only for debug.  
- **Action:** Reproduced with `./bin/asset_sync < /dev/null`, checked logs; found inverted conditional in `asset_sync.c` (logic was backwards). Fixed the `if (strcmp(cfg.mode, "debug") == 0)` block; rebuilt with `make`; validated logs.  
- **Result:** Logs correctly showed "Normal mode" for normal and "Debug mode enabled" for debug; ticket owner confirmed.

**Option B — Unactionable error message (INC002)**  
- **Situation:** When parse failed, log said only "Failed to parse asset" with no input context; support couldn’t trace bad data.  
- **Task:** Make the failure message actionable so we could see the problematic line.  
- **Action:** Reproduced with `echo "ASSET,ID123" | ./bin/asset_sync`; located the parse-failure `printf` in `asset_sync.c`; added the offending line to the message (with truncation for safety); rebuilt and validated.  
- **Result:** Logs included the bad input; support could debug and trace back to source; ticket closed.

---

### 2.3 "Tell me about a failure" / "Mistake you made" (Use INC003)

- **Situation:** A deployment failed at startup with "Invalid batch_size"; operators first assumed a code bug.
- **Task:** Find root cause and fix so the service is robust and easier to diagnose next time.
- **Action:** Traced through logs; realized logic was fine — root cause was **configuration mismatch** (`batch_size=0` in config), not a code defect. Updated C code to validate config at startup, use a safe default (e.g. 10) when invalid, and log a **WARN** so the issue is visible. Restarted, confirmed logs.
- **Result:** Service ran with safe default; logs showed the warning; operators could see it was config, not code.  
**Takeaway:** Verify config before assuming code failure; make the system observable for future debugging.

---

## 3. Debugging — Full Reference

### 3.1 Environment

- **Local:** Laptop, VS Code, terminal, `gcc`/`g++`, `make`, Git.
- **Remote:** VPN → SSH → Linux servers; services managed with `systemctl`; logs in `journalctl` or log files.

### 3.2 Tools (Commands to Know)

| Tool | Purpose |
|------|--------|
| `grep` | Search log output or files for patterns (e.g. ERROR, WARN, asset ID). |
| `tail` | View last lines of a log file (e.g. `tail -f` to follow). |
| `journalctl` | Query systemd logs for a service (e.g. `journalctl -u service-name -f`). |
| `ps` | List processes (confirm service is running). |
| `top` | Monitor processes/CPU/memory. |
| `cd` / `ls` | Navigate and list (config dirs, `src/`, logs). |
| `./bin/asset_sync` | Run the service (with optional config path and stdin). |

### 3.3 Workflow: Log-Driven Debugging

1. **Reproduce** — Run the service with the same config/input as in the ticket (e.g. bad config file, malformed stdin).
2. **Capture logs** — Use `tail`, `grep`, or `journalctl` to see what the service printed.
3. **Correlate** — Match log lines to code paths (e.g. "Debug mode enabled" → conditional in `asset_sync.c`).
4. **Hypothesize** — Code bug vs config/data issue (INC003: config mismatch, not logic).
5. **Fix** — Change code (or config); rebuild with `make`.
6. **Validate** — Run again; confirm logs show expected behavior; ticket owner confirms.

### 3.4 How Each Incident Was Debugged

- **INC001:** Reproduced → saw "Debug mode enabled" with `mode=normal` → grep/locate conditional in source → found inverted `if` → fix and validate logs.
- **INC002:** Reproduced with malformed input → saw "Failed to parse asset" with no context → found `printf` at parse failure → added input to message (truncated) → validate.
- **INC003:** Service exited on bad config → checked logs → saw invalid `batch_size` → confirmed config file (not code) → added validation, default, and WARN log → validate.

---

## 4. Process — Full Reference

### 4.1 Ticket Flow

1. **Intake** — ServiceNow ticket (or Teams) assigned; read description, steps to reproduce, expected vs actual.
2. **Reproduce** — Run service with same conditions; capture logs.
3. **Fix** — Edit code (or config); rebuild; run again.
4. **Validate** — Logs normal, service no longer errors.
5. **Close** — Ticket owner confirms; ticket resolved.

### 4.2 Definition of "Done" for a Fix

1. Logs show normal (or expected) behavior.  
2. Service has stopped erroring (or exiting unexpectedly).  
3. Ticket owner has confirmed resolution.

### 4.3 Git / Version Control

- **Commands:** `git status`, `git pull`, `git checkout -b <branch>`, `git add`, `git commit`, push and open PR.
- **Process:** Branch per ticket or small set of changes; commit; PR; senior review; then merge.

### 4.4 Collaboration

- **Ticket owner** — Confirms reproduction and resolution.
- **Senior engineers** — Code review (PRs), guidance.
- **Teams** — Questions, updates, handoffs.

### 4.5 Hard Boundaries (Stay Honest — Intern-Level)

- Did not design system architecture.  
- Did not deploy to production alone.  
- Did not own services end-to-end.  
- Did support, fix, validate, and learn.

---

## 5. C/C++ & Integration — Full Reference

### 5.1 Systems Context

- **IATS** — Asset/transaction tracking; pipeline that processes asset data; `asset_sync` is a component that reads config, reads asset lines (e.g. from stdin or a stream), parses them, and logs.
- **IFMS** — Fleet/maintenance data; integration point (you supported components that feed or align with fleet data, not the whole system).

### 5.2 Concepts in Your Code (`asset_sync.c`)

| Concept | In this code |
|--------|----------------|
| **Config loading** | Read file (`fopen`, `fgets`); parse key=value lines; skip `#` and blank; set `batch_size`, `timeout_sec`, `mode`. |
| **Config validation** | Check `batch_size > 0`; if not, use default and log WARN. |
| **Conditional logic** | `if (strcmp(cfg.mode, "debug") == 0)` for mode-dependent logging; easy to invert by mistake (INC001). |
| **Parsing** | Line format `ASSET,ID,status`; find first comma, then second; extract ID between them; use `strncpy` and null-terminate. |
| **Error handling** | On parse failure, return -1; in caller, log and include context (INC002). |
| **Logging** | `printf` for [INFO], WARNING, ERROR; consistent prefixes help grep and journalctl. |
| **Safe defaults** | When config is missing or invalid, use defaults (e.g. batch_size=10, mode=normal) so service keeps running. |
| **Struct** | `Config` holds `batch_size`, `timeout_sec`, `mode`; passed to `load_config()`. |
| **String handling** | `strncmp`, `strchr`, `strncpy`, `strcspn`; bounded buffers (`MAX_LINE`, `sizeof(cfg.mode)-1`) to avoid overrun. |

### 5.3 Integration Points (What to Say)

- **IATS:** Asset sync is part of the IATS pipeline; it consumes asset transaction data (e.g. streamed or piped), parses it, and supports downstream steps. You fixed bugs and improved logging in this component.
- **IFMS:** Fleet/maintenance systems consume or align with data from these pipelines; you supported the C/C++ components that feed into that integration, not the full IFMS design.

---

## 6. Full Study List — Everything to Review

### 6.1 Role & Company

- [ ] Ryder System — what they do (logistics, fleet).
- [ ] IT Operations — Enterprise / Fleet Systems.
- [ ] Chambersburg, PA — distribution center, onsite.
- [ ] IT/Systems Intern — support, fix, validate; not architect or sole deployer.
- [ ] Elevator pitch (one sentence) — memorize.
- [ ] 4-sentence template: Summary → Role → What you did → Outcome.

### 6.2 Systems & Acronyms

- [ ] IATS — asset/transaction tracking; pipeline; asset_sync component.
- [ ] IFMS — fleet/maintenance data; integration.
- [ ] ServiceNow — ticket system.
- [ ] Asset sync — long-running Linux service; config, parse, log.

### 6.3 Debugging

- [ ] Log-driven debugging — reproduce → capture logs → correlate to code → fix → validate.
- [ ] `grep` — search logs/files.
- [ ] `tail` / `tail -f` — last lines / follow.
- [ ] `journalctl` — systemd logs for a service.
- [ ] `ps`, `top` — processes and resource use.
- [ ] How you reproduced INC001, INC002, INC003.
- [ ] Why INC003 was config mismatch, not code bug — and how you verified.

### 6.4 Process

- [ ] Ticket flow: intake → reproduce → fix → validate → close.
- [ ] Definition of done: logs normal, service not erroring, owner confirmed.
- [ ] Git: status, pull, checkout -b, add, commit, PR, review.
- [ ] Who you worked with: ticket owner, senior engineers, Teams.

### 6.5 C/C++

- [ ] Reading config file: fopen, fgets, skip # and blank, parse key=value.
- [ ] Config validation and safe defaults (e.g. batch_size).
- [ ] Conditional logic bugs (e.g. inverted if for debug mode).
- [ ] Parsing a CSV-like line: strchr, strncpy, bounds.
- [ ] Actionable error messages — include context (e.g. bad line) in log.
- [ ] Struct for config; passing pointers to load_config.
- [ ] String safety: strncpy, null termination, buffer size.

### 6.6 STAR Scenarios

- [ ] Full STAR for "Tell me about your work."
- [ ] Full STAR for one technical fix (INC001 or INC002).
- [ ] Full STAR for failure/mistake (INC003 — config, not code; what you did and takeaway).

### 6.7 Practice Questions (Answer Out Loud)

- [ ] "Tell me about your role at Ryder."
- [ ] "Describe a technical problem you solved."
- [ ] "Tell me about a time you made a mistake."
- [ ] "What tools did you use?"
- [ ] "How did you validate your fixes?"
- [ ] "What systems did you work with?"
- [ ] "How do you debug a service that’s misbehaving?"
- [ ] "What’s the difference between a config issue and a code bug? How do you tell?"

### 6.8 One-Liners to Remember

- **Fix = done when:** Logs normal, service stopped erroring, ticket owner confirmed.
- **Failure takeaway:** Verify config before assuming code failure; improve logging so the issue is visible next time.
- **Workflow:** Log-driven debugging — not heavy interactive debugging; grep, tail, journalctl.
- **Scope:** Supported C/C++ components for IATS/IFMS; did not architect or own end-to-end.

---

*End of dossier. Use this as your single reference for technical interview prep and STAR answers.*

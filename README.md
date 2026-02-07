# Ryder IT / Systems Intern — Technical Review

**IT Operations | Enterprise / Fleet Systems | Chambersburg, PA**

This repository simulates the Ryder internship environment: Linux-based backend services, ServiceNow tickets, C/C++ bug fixes, log analysis, and validation. Use it to review iteratively what you did at Ryder and how to speak about it technically.

---

## Environment (What "Linux-Based" Meant at Ryder)

- **Dev layer:** Laptop, VS Code, terminal, `gcc`/`g++`, `make`, Git
- **Runtime layer:** Linux servers (accessed via VPN + SSH), services, logs, `systemctl`, `journalctl`
- **Systems touched:** IATS (asset/transaction tracking), IFMS (fleet/maintenance data)
- **Workflow:** ServiceNow tickets, 2–4 at a time, ad hoc, no daily standup, weekly/bi-weekly manager check-in
- **No:** Docker, Kubernetes, containerization, full CI/CD pipelines — controlled, ops-focused workflow

---

## Iterative Learning Map

Follow this path to review what you did at Ryder step by step. Do not skip steps. Each step builds on the previous.

### Phase 1 — Setup and Context

1. **Read this README** — Understand the environment and workflow
2. **Build the service** — `make` (you compiled locally with gcc/make)
3. **Inspect the layout** — `src/`, `config/`, `logs/`, `tickets/` — mirrors how code lived at Ryder

### Phase 2 — First Ticket (INC001)

**Goal:** Fix incorrect conditional logic — the most common bug type at Ryder.

1. Open `tickets/INC001.md` — simulate opening ServiceNow
2. Reproduce: `./bin/asset_sync < /dev/null` — observe the wrong log message
3. Use `grep` or `tail` on logs — log-driven debugging, not heavy interactive debugging
4. Edit `src/asset_sync.c` — fix the inverted `if` in the debug-mode block
5. Rebuild: `make`
6. Validate: run again, confirm logs show "Normal mode" when `mode=normal`
7. **Done when:** Logs show normal behavior; you can explain what you fixed

**What you learned:** Incorrect conditional logic, log analysis, small logic-block fix.

### Phase 3 — Second Ticket (INC002)

**Goal:** Improve logging — missing or misleading logs were common issues.

1. Open `tickets/INC002.md`
2. Reproduce: `echo "ASSET,ID123" | ./bin/asset_sync` — parse fails with no context
3. Edit `src/asset_sync.c` — add the problematic input to the parse-failure message
4. Rebuild and validate
5. **Done when:** Logs include the offending line so support could debug next time

**What you learned:** Logging, parsing, actionable error messages.

### Phase 4 — Third Ticket (INC003)

**Goal:** Handle configuration mismatch — the real failure story you use in interviews.

1. Open `tickets/INC003.md`
2. Reproduce: `./bin/asset_sync config/sync_bad.conf < /dev/null` — service exits on invalid config
3. Root cause: `batch_size=0` in config — config mismatch, not a code bug
4. Edit `src/asset_sync.c` — validate config, use safe default, log a warning
5. Rebuild and validate — service should run, logs should show the warning
6. **Done when:** Service handles bad config safely; logs make the issue visible next time

**What you learned:** Config validation, defensive coding, improved logging, the failure story.

### Phase 5 — Integration

1. Run all three fixes together — verify no regressions
2. **Git workflow:** `git status`, `git add`, `git commit`, `git checkout -b` — simulate PR/review
3. **One-sentence summary:** Practice saying what you did: "I analyzed logs, fixed C/C++ bugs in a Linux service supporting IATS, validated behavior, and closed ServiceNow tickets."

---

## Directory Layout

```
├── README.md           # This file — learning map and context
├── Makefile            # Build (gcc, make)
├── src/
│   └── asset_sync.c    # IATS asset sync service (long-running daemon-style)
├── config/
│   ├── sync.conf       # Normal config
│   └── sync_bad.conf   # Misconfigured (INC003)
├── logs/
│   └── sample_error.log
├── tickets/            # ServiceNow-style incidents
│   ├── INC001.md
│   ├── INC002.md
│   └── INC003.md
```

---

## Quick Reference — What You Did at Ryder

| Item | Answer |
|------|--------|
| **Title** | IT / Systems Intern |
| **Org** | IT Operations (Enterprise / Fleet Systems) |
| **Location** | Chambersburg, PA distribution center (onsite) |
| **Work intake** | ServiceNow tickets, Teams messages |
| **Type of work** | Bug fixes in C/C++, log analysis, validation |
| **Code form** | Long-running Linux services / daemons |
| **Typical change** | Small logic block, occasionally a function, often a few lines |
| **Tools** | VS Code, terminal, gcc/g++, make, Git, grep, tail, systemctl, journalctl |
| **Fix = done when** | Logs normal, service stopped erroring, ticket owner confirmed |
| **Systems** | IATS, IFMS — you supported components, did not architect |

---

## Failure Story (Use in Interviews)

*"In one case, a Linux service supporting the IATS pipeline was intermittently failing at startup, which initially looked like a code defect. I traced the behavior through the service logs and realized the logic was fine, but the root cause was a configuration mismatch between environments. A required config value was missing in that deployment.*

*I updated the C++ startup logic to validate the configuration, added a safe default when the value wasn't present, and improved the logging so the loaded configuration was clearly visible. After restarting the service and confirming the logs were clean, the issue was resolved and much easier to diagnose if it occurred again."*

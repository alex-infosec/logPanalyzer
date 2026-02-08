# Raytheon / RTX — Software Engineer I (MA) — Interview Prep

**Role:** 2026 Full-time Software Engineer I — Onsite (Marlborough or Tewksbury, MA)  
**Team:** Radar Product Line — real-time embedded software, application software, tools  
**Status:** Application Under Review

---

## How Your Prep Fits This Role

| They want | You have (where to point) |
|-----------|---------------------------|
| C++, C, Java | **Ryder:** C/C++ in Linux daemons (asset_sync, IATS/IFMS). **UF:** Embedded C/C++ on ESP32/RP2040. |
| Real-time embedded | **UF Research:** Embedded firmware, ESP32/RP2040, RTK GNSS, LIS3DH, telemetry — real-time data collection and processing. |
| Unix/Linux | **Ryder:** Full workflow — VPN, SSH, grep, tail, journalctl, systemctl, Git, make. |
| Data structures, algorithms, SDLC | **Ryder:** Design → code → test → PR → review; config, parsing, logging. **UF:** Data processing, Python analysis. |
| Problem-solving, communication | **Ryder:** Ticket-driven debugging, ticket owner confirmation, Teams. **UF:** Cross-functional, field data, visualization. |
| Agile/SCRUM, team-based dev | **Ryder:** PRs, senior review, ticket flow. |

Your **Ryder prep** (ryder-prep.md, interview-technical-dossier.md) is still your main content — same STAR stories, same C/C++ and debugging answers. This doc is the **bridge** so you frame them for Raytheon.

---

## One-Sentence Pitch (Raytheon Version)

> I'm a Computer Engineering student at UF with embedded experience on real-time telemetry and GNSS at school, and C/C++ and Linux debugging experience from my systems internship at Ryder — I'm looking to bring that combination to real-time embedded work on the Radar team.

---

## Which Story for Which Question

| Question | Primary story | Backup |
|----------|----------------|--------|
| "Tell me about yourself" / "Walk me through your background" | UF (embedded, telemetry) → Ryder (C/C++, Linux, debugging) → why Raytheon/radar | — |
| "Describe your experience with C/C++" | Ryder: daemons, config, parsing, logging, INC001/INC002/INC003 | UF: firmware, sensors |
| "Real-time or embedded experience?" | **UF Research:** ESP32/RP2040, RTK GNSS, LIS3DH, cut-force + GPS telemetry, Python analysis | Ryder: long-running services |
| "Technical problem you solved" | Ryder INC001 or INC002 (wrong log message, unactionable error) | UF: integration, data pipeline |
| "Mistake / failure" | Ryder INC003 (config mismatch, assumed code bug, added validation + logging) | — |
| "How do you debug?" | Log-driven: reproduce → logs (grep, tail, journalctl) → correlate to code → fix → validate | — |
| "Linux experience?" | Ryder: VPN, SSH, systemctl, journalctl, make, Git | UF: toolchain, build |
| "Team / process?" | Ryder: ServiceNow tickets, PRs, senior review, ticket owner confirmation | — |

---

## Raytheon-Specific Talking Points (Short)

- **Mission:** "I want to work on problems that matter for national security and defense — radar and real-time systems are exactly that."
- **Fit:** Real-time embedded (UF) + C/C++ and Linux in a production-like environment (Ryder) = ready to contribute to requirements, design, code, test, and documentation on the Radar team.
- **Clearance:** Job says *active Secret required on day 1*. If you have it or are in process, say so. If not, they may still talk to you; be ready to answer honestly about citizenship and clearance status.

---

## Verbal Rep List (Same Gears, Slightly Different Labels)

1. **Tell me about yourself** — UF embedded → Ryder C/C++/Linux → why Raytheon.
2. **STAR – technical problem** — Ryder INC001 or INC002 (log message or parse error).
3. **STAR – failure** — Ryder INC003 (config vs code, validation, logging).
4. **Project / code** — Ryder: asset_sync, IATS, tickets. UF: ESP32/RP2040, RTK, telemetry, Python.
5. **C/C++** — Pointers, memory (stack/heap), config/parsing/strings (from asset_sync), OOP vs Java if they ask.
6. **Real-time / embedded** — UF: firmware, sensors, telemetry, real-time data collection.
7. **Why Raytheon / why this role** — Mission, radar, real-time embedded, want to grow here.

Use **ryder-prep.md** and **interview-technical-dossier.md** for the actual wording and technical depth; use this file to know *which* story to pull for Raytheon and how to open/close.

---

## Full Question Set + Mapping

**raytheon-questions.md** — Consolidated “what people actually get” list (all 9 categories) with each category mapped to your STAR stories and frameworks. Use it as the one-page mental roadmap under pressure.

---

*Nervous is how you prepare. You've got the content; now it's verbal reps. Good luck.*

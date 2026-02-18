# EEL4712 Midterm 1 — Crash Study Plan

**Time:** Today + part of tomorrow  
**Exam:** 8:30–9:20 (arrive 8:10 for 20 extra min)  
**Format:** 5 questions × 20 pts, formula sheet provided, no other aids

---

## Exam Breakdown

| Question | Topic | Weight |
|----------|-------|--------|
| 1 | Combinational logic | 20 pt |
| 2 | Sequential logic | 20 pt |
| 3 | FSM | 20 pt |
| 4 | FSM+D | 20 pt |
| 5 | Brief / MC / T–F | 20 pt |

---

## Priority Order (for time crunch)

### 1. FSM+D (highest impact)
- Most complex, easy to lose points
- Know: datapath blocks → FSM states → VHDL
- Practice: **Sum of odd numbers** (slides Ex), **find max of n inputs** (slides Ex), **door lock** (slides Ex)

### 2. FSM
- Draw FSM from text spec
- Translate FSM to VHDL (1-, 2-, 3-process models)
- Practice: **vending machine** (slides Ex)

### 3. Sequential logic
- Flip-flops, counters, datapaths
- Review Labs 2–4

### 4. Combinational logic
- Modeling styles, signal vs variable, avoiding latches
- Basic combinational circuits, `numeric_std`
- Review Lab 1

### 5. Brief / MC / T–F
- General concepts from slides and labs

---

## Today (focus)

| Block | Time | Focus |
|-------|------|--------|
| 1 | 2–3 hr | Lecture slides: FSM + FSM+D sections |
| 2 | 2 hr | FSM+D: Sum of odd numbers, find max — draw datapath + FSM by hand |
| 3 | 1.5 hr | FSM: Vending machine — spec → FSM diagram → 3-process VHDL |
| 4 | 1 hr | Labs 3–4 (sequential, datapath) |

---

## Tomorrow AM (before exam)

| Block | Time | Focus |
|-------|------|--------|
| 1 | 1 hr | Combinational + sequential (lecture + Labs 1–2) |
| 2 | 1 hr | Write short FSM and FSM+D VHDL by hand (no IDE) |
| 3 | 30 min | Brief concepts, MC/TF-style review |

---

## Key Concepts to Memorize

### Combinational
- **Signal vs variable:** signal = concurrent, variable = sequential (inside process)
- **Avoiding latches:** every branch must assign all outputs; use `else` / `others`
- **numeric_std:** `unsigned`, `signed`, `+`, `-`, `resize`

### Sequential
- FF: register element with clock and possibly async reset
- Counters: state or dedicated counter register
- Datapath: registers + muxes + ALU/adders

### FSM
- States, transitions, outputs (Mealy vs Moore if mentioned)
- 1-process: all logic in one `process(clk, reset)`
- 2-process: one for state, one for outputs
- 3-process: state reg, next-state, outputs

### FSM+D
1. Datapath: registers, muxes, operators, control inputs
2. FSM: states and outputs that drive datapath control
3. VHDL: instantiate datapath, FSM drives control

---

## Professor’s Advice
- Go over lecture slides
- Go over labs 1–4
- **Practice writing VHDL by hand** ← critical

---

## Quick Reference (use formula sheet in exam)
- Formula sheet has VHDL reference — know how to use it
- Review your labs for actual syntax you’ve used

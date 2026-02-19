# VHDL Sequential Logic — Practice

**Topics:** Define FFs • Counters • Datapaths

---

## 1. Define FFs (Flip-Flops)

**A) Basic D flip-flop** — samples `d` on rising clock edge:

```vhdl
PROCESS (clk, d)  -- FILL: sensitivity list for sequential (clock, maybe reset)
BEGIN
    IF rising_edge(clk) THEN
        q <= d;  -- FILL: what does D-FF store?
    END IF;
END PROCESS;
```

**B) D-FF with async reset** (reset happens immediately, no clock needed):

```vhdl
PROCESS (clk, reset)
BEGIN
    IF reset = '1' THEN
        q <= '0';           -- reset takes priority
    ELSIF rising_edge(clk) THEN
        q <= d;
    END IF;
END PROCESS;
```

**C) D-FF with sync reset** (reset only on clock edge):

```vhdl
PROCESS (clk)
BEGIN
    IF rising_edge(clk) THEN
        IF reset = '1' THEN
            q <= '0';
        ELSE
            q <= d;  -- FILL
        END IF;
    END IF;
END PROCESS;
```

**D) Register (multi-bit FF)** — 8-bit register that loads `d` on clock:

```vhdl
PROCESS (clk)
BEGIN
    IF rising_edge(clk) THEN
        reg <= d;  -- FILL: assign input to register
    END IF;
END PROCESS;
```

---

## 2. Counters

**A) Up counter (0, 1, 2, 3, … wrap at max)**

```vhdl
SIGNAL count : UNSIGNED(3 DOWNTO 0) := (OTHERS => '0');  -- 0 to 15

PROCESS (clk, reset)
BEGIN
    IF reset = '1' THEN
        count <= (OTHERS => '0');
    ELSIF rising_edge(clk) THEN
        count <= count + 1;  -- FILL: increment
    END IF;
END PROCESS;
```

**B) Counter with enable** — only counts when `en = '1'`:

```vhdl
PROCESS (clk, reset)
BEGIN
    IF reset = '1' THEN
        count <= (OTHERS => '0');
    ELSIF rising_edge(clk) THEN
        IF en = '1' THEN
            count <= count + 1;
        END IF;
        -- when en='0', count holds (no ELSE needed)
    END IF;
END PROCESS;
```

**C) Counter with load** — when `load = '1'`, load `data`; else increment:

```vhdl
PROCESS (clk, reset)
BEGIN
    IF reset = '1' THEN
        count <= (OTHERS => '0');
    ELSIF rising_edge(clk) THEN
        IF load = '1' THEN
            count <= data;  -- FILL
        ELSE
            count <= count + 1;
        END IF;
    END IF;
END PROCESS;
```

**D) Modulo-N counter** (e.g. count 0–4, then wrap to 0):

```vhdl
SIGNAL count : UNSIGNED (3 downto 0) := (OTHERS => '0');
PROCESS (clk, reset)
BEGIN
    IF reset = '1' THEN
        count <= (OTHERS => '0');
    ELSIF rising_edge(clk) THEN
        IF count = 4 THEN
            count <= (OTHERS => '0');
        ELSE
            count <= count + 1;
        END IF;
    END IF;
END PROCESS;
```

---

## 3. Datapaths

**Datapath = registers + muxes + combinational logic.** Registers load on clock; muxes choose what goes in.

**A) Register with muxed input** — load `a` when `sel = '0'`, else load `b`:

```vhdl
PROCESS (clk)
BEGIN
    IF rising_edge(clk) THEN
        IF sel = '0' THEN
            reg <= a;
        ELSE
            reg <= b;  -- FILL
        END IF;
    END IF;
END PROCESS;
```

**B) Accumulator** — `acc <= acc + x` on each clock when `en = '1'`:

```vhdl
SIGNAL acc : UNSIGNED(7 DOWNTO 0) := (OTHERS => '0');

PROCESS (clk, reset)
BEGIN
    IF reset = '1' THEN
        acc <= (OTHERS => '0');
    ELSIF rising_edge(clk) THEN
        IF en = '1' THEN
            acc <= acc + x;  -- FILL
        END IF;
    END IF;
END PROCESS;
```

**C) Shift register** — shift left, LSB gets `shift_in`:

```vhdl
SIGNAL sr : STD_LOGIC_VECTOR(7 DOWNTO 0) := (OTHERS => '0');

PROCESS (clk)
BEGIN
    IF rising_edge(clk) THEN
        sr <= sr(6 DOWNTO 0) & shift_in;  -- FILL: shift left
    END IF;
END PROCESS;
-- Hint: left shift = drop leftmost, append new on right
```

**D) What’s the difference?**

- **FF/register:** stores 1 bit or N bits, updates on clock
- **Counter:** register that increments (or loads) on clock
- **Datapath:** registers + logic (mux, adder, etc.) — data flows through, registers hold state

---

## Quick Answers

| 1A sens | clk (or clk, reset if async reset) |
| 1A q   | d |
| 1C     | d |
| 1D     | d |
| 2A     | count + 1 |
| 2C     | data |
| 3A     | b |
| 3B     | acc + x |
| 3C     | 6, 0 — sr(6 DOWNTO 0) & shift_in (drop MSB, append right) |

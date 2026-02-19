# VHDL Combinational Logic — Practice (Based on Your Reference Sheet)

Your formula sheet has these building blocks. Use them to fill in the blanks.

---

## Reference Sheet Quick Map

| What you need | Reference sheet pattern |
|---------------|-------------------------|
| Entity + ports | `ENTITY ... IS PORT(...) END` |
| Architecture | `ARCHITECTURE a OF ... IS SIGNAL ... BEGIN ... END` |
| Conditional (concurrent) | `__signal <= __expr WHEN __bool ELSE __expr;` |
| Selected (concurrent) | `WITH __expr SELECT __signal <= __expr WHEN __const, __expr WHEN __const;` |
| Process (behavioral) | `IF ... THEN ... ELSIF ... ELSE ... END IF;` or `CASE ... WHEN ... END CASE` |
| Component instantiation | `instance: component_name PORT MAP (port => connect, ...);` |

---

## 1. Modeling Styles

**A) Conditional signal assignment** (from ref: `__signal <= __expr WHEN __bool ELSE __expr`)

Complete this 2-to-1 mux — one line, no process:

```vhdl
ENTITY mux2 IS
PORT(a, b, sel : IN STD_LOGIC;
     y         : OUT STD_LOGIC);
END mux2;

ARCHITECTURE dataflow OF mux2 IS
BEGIN
    y <= a WHEN sel='0' ELSE b;
END dataflow;
```

**B) Process with IF** (from ref: `IF ... THEN ... ELSIF ... ELSE ... END IF`)

Same mux, behavioral:

```vhdl
ARCHITECTURE behavioral OF mux2 IS
BEGIN
    PROCESS (a, b, sel)  -- FILL: every input you read
    BEGIN
        IF sel = '0' THEN
            y <= a;
        ELSE
            y <= b;
        END IF;
    END PROCESS;
END behavioral;
```

**C) Selected signal assignment** (from ref: `WITH __expr SELECT __signal <= ... WHEN ...`)

Same mux with WITH/SELECT:

```vhdl
ARCHITECTURE selected OF mux2 IS
BEGIN
    WITH sel SELECT
    y <= a WHEN '0',
         b WHEN '1',
         '0' WHEN OTHERS;  -- FILL: what for default?
END selected;
```

**D) Structural** (from ref: `instance: component PORT MAP (...)`)

What's missing? The architecture declares a component but never **instantiates** it. You need:
- `label: component_name PORT MAP (component_port => signal, ...);`

---

## 2. Signal vs Variable

**Predict:** Variable updates **immediately**. Signal updates at **end of process** (next delta / next cycle).

```vhdl
PROCESS (clk)
    VARIABLE v : STD_LOGIC := '0';
    SIGNAL s   : STD_LOGIC := '0';
BEGIN
    IF rising_edge(clk) THEN
        v := d;   -- v gets d now
        s <= d;   -- s gets d at end of process
        v := v;   -- v already = d
        s <= s;   -- s still OLD value here
    END IF;
END PROCESS;
```

Variable `v` = ______  (d, same cycle)  
Signal `s` = ______    (delayed 1 cycle)

**Count 1s in vec(3 downto 0)** — use VARIABLE for read-modify-write in same process:

```vhdl
PROCESS (vec)
    VARIABLE count : INTEGER RANGE 0 TO 4 := 0;
BEGIN
    count := 0;
    FOR i IN 0 TO 3 LOOP
        IF vec(i) = '1' THEN
            count := count + 1;
        END IF;
    END LOOP;
    num_ones <= count;
END PROCESS;
```

---

## 3. Avoiding Latches

**Latch =** output not assigned in every branch. Fix:

```vhdl
PROCESS (a, b, sel)
BEGIN
    IF sel = '0' THEN
        y <= a;
    ELSE y <= b;
    END IF;
    -- BUG: no ELSE → y holds when sel='1'
END PROCESS;
```

Fix: add `ELSE y <= b; END IF;`

**CASE must cover all cases** (or use `WHEN OTHERS`):

```vhdl
CASE sel IS
    WHEN "00" => y <= a;
    WHEN "01" => y <= b;
    WHEN "10" => y <= c;
    WHEN OTHERS => y <= d;  -- FILL: needed!
END CASE;
```

**Sensitivity list** — every signal you READ must be in the list:

```vhdl
PROCESS (a, b, sel)  -- BUG: a, b missing
BEGIN
    y <= a WHEN sel = '0' ELSE b;
END PROCESS;
```

Correct: `PROCESS (a, b, sel)`

---

## 4. Basic Combinational

**4-bit priority encoder** (highest 1 wins):

```vhdl
PROCESS (d)
BEGIN
    enc   <= "00";
    valid <= '0';
    IF d(3) = '1' THEN
        enc <= "11"; valid <= '1';
    ELSIF d(2) = '1' THEN
        enc <= "10"; valid <= '1';
    ELSIF d(1) = '1' THEN
        enc <= "01"; valid <= '1';   -- FILL
    ELSIF d(0) = '1' THEN
        enc <= "00"; valid <= '1';   -- FILL
    END IF;
END PROCESS;
```

**3-to-8 decoder** with CASE:

```vhdl
CASE a IS
    WHEN "000" => y <= "00000001";
    WHEN "001" => y <= "00000010";
    WHEN "010" => y <= "00000100";  -- FILL
    WHEN "011" => y <= "00001000";
    WHEN "100" => y <= "00010000";
    WHEN "101" => y <= "00100000";
    WHEN "110" => y <= "01000000";
    WHEN "111" => y <= "10000000";
    WHEN OTHERS => y <= (OTHERS => '0');
END CASE;
```

---

## 5. Arithmetic / numeric_std

`USE ieee.numeric_std.ALL;`

```vhdl
SIGNAL a, b   : UNSIGNED(7 DOWNTO 0);
SIGNAL sum    : UNSIGNED(8 DOWNTO 0);
SIGNAL diff   : UNSIGNED(7 DOWNTO 0);
SIGNAL prod   : UNSIGNED(7 DOWNTO 0);
SIGNAL borrow : STD_LOGIC;
```

Add: `sum <= resize(a, 9) + resize(b, 9);`  
Subtract: `diff <= a - b;`  
Borrow: `borrow <= '1' WHEN a < b ELSE '0';`  
Multiply (4×4→8): `prod <= x * y;`  (result width = sum of operand widths)

---

## Quick Answers

| 1A | `a`, `sel = '0'`, `b` |
| 1B | `a, b, sel` |
| 1C | `'0'` or `'-'` (or one of a/b) for OTHERS |
| 2 Variable | `count + 1` |
| 2 v | d (immediate) |
| 2 s | 1 cycle delayed |
| 3 CASE | e.g. `d` for WHEN OTHERS |
| 4 Encoder | `"01"`, `"00"` |
| 4 Decoder | `"00000100"` |

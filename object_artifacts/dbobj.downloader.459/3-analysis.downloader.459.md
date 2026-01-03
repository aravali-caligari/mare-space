# `Downloader`

## English Logic Descriptions (Legacy Attribute List)

## OBJECT: `Downloader`

### ATTRIBUTE: `flte()` — English description

```mud
original
flte():[lnot(match(fcomp(v(1),v(0)),-1))]
```

```text
Object: Downloader
Attribute: flte()

Purpose:
- Implements a numeric “<=” predicate as a helper for the mass-threshold ladders.

Inputs:
- v(0): right-hand numeric value
- v(1): left-hand numeric value

Logic:
- Compares v(1) to v(0) using fcomp().
- match(...,-1) tests for “less-than” (v(1) < v(0)).
- lnot(...) inverts it, yielding true when v(1) is not less-than v(0) (i.e., v(1) >= v(0)).
- In the calling patterns, it is used as “flte(threshold, mass)” meaning “mass <= threshold” or “mass is not above threshold”, depending on the exact fcomp/match conventions.
```

### ATTRIBUTE: `get_obj_color()` — English description

```mud
original
get_obj_color():[ifelse(flte(v(0),3E28),ifelse(flte(v(0),8E24),ifelse(flte(v(0),2E23),ifelse(flte(v(0),5E16),ifelse(flte(v(0),1E8),8,7),9),2),4),14)]
```

```text
Object: Downloader
Attribute: get_obj_color()

Purpose:
- Maps an object’s mass into a numeric “color code” used by sensor output.

Inputs:
- v(0): mass

Logic:
- Runs a nested ifelse ladder using mass thresholds.
- Returns a small integer code (e.g. 8,7,9,2,4,14) based on where the mass falls.
- Smaller masses yield one set of codes; larger masses yield others.
```

### ATTRIBUTE: `get_obj_type()` — English description

```mud
original
get_obj_type():[ifelse(flte(v(0),3E28),ifelse(flte(v(0),8E24),ifelse(flte(v(0),2E23),ifelse(flte(v(0),5E16),ifelse(flte(v(0),1E8),Ship,Station),Moon),Terran),Jovian),Star)]
```

```text
Object: Downloader
Attribute: get_obj_type()

Purpose:
- Maps an object’s mass into a coarse type label.

Inputs:
- v(0): mass

Logic:
- Uses the same threshold ladder style as get_obj_color()/get_obj_size().
- Returns one of: Ship, Station, Moon, Terran, Jovian, Star.
```

### ATTRIBUTE: `get_obj_size()` — English description

```mud
original
get_obj_size():[ifelse(flte(v(0),3E28),ifelse(flte(v(0),8E24),ifelse(flte(v(0),2E23),ifelse(flte(v(0),5E16),ifelse(flte(v(0),1E8),1,2),4),8),16),32)]
```

```text
Object: Downloader
Attribute: get_obj_size()

Purpose:
- Maps an object’s mass into a coarse size class number.

Inputs:
- v(0): mass

Logic:
- Uses a threshold ladder and returns one of: 1,2,4,8,16,32.
- Larger masses map to larger size classes.
```

### ATTRIBUTE: `see_if()` — English description

```mud
original
see_if():@swi [scomp(get(v(sensor_memory),strcat(memory,v(0))),NO MATCH)]=1,{},{@pem [v(2)]=[spit_data(v(0),v(1))]}
```

```text
Object: Downloader
Attribute: see_if()

Purpose:
- Conditionally emits a sensor record for a target only if it is not already present in a sensor-memory lookup.

Inputs (by usage):
- v(0): target object dbref
- v(1): an auxiliary value forwarded to spit_data() (legacy; may be unused)
- v(2): emit target (typically the requesting player)
- v(sensor_memory): dbref of an object storing memory attributes

Logic:
- Builds an attribute name "memory<target>" via strcat(memory,v(0)).
- Reads that attribute from v(sensor_memory).
- Compares the result to "NO MATCH".
  - If the comparison indicates an existing entry (not "NO MATCH"): do nothing.
  - Otherwise: pemit v(2) a formatted record line produced by spit_data(v(0),v(1)).

Side effects:
- Output only; no direct state changes.
```

### ATTRIBUTE: `spit_data()` — English description

```mud
original
spit_data():[histname(v(!),v(0))]|[fdiv(dx(v(us),v(0)),v(divby))]|[fdiv(dy(v(us),v(0)),v(divby))]|[fdiv(dz(v(us),v(0)),v(divby))]|[get_obj_type(get(v(0),mass))]|[get_obj_color(get(v(0),mass))]|[get_obj_size(get(v(0),mass))]|
```

```text
Object: Downloader
Attribute: spit_data()

Purpose:
- Produces one pipe-separated “sensor record” line for a target.

Inputs (by usage):
- v(0): target object dbref
- v(us): source ship dbref
- v(divby): numeric scaling divisor

Output format (pipe-separated):
1) histname(v(!),v(0))
2) dx(v(us),v(0))/divby
3) dy(v(us),v(0))/divby
4) dz(v(us),v(0))/divby
5) get_obj_type(target.mass)
6) get_obj_color(target.mass)
7) get_obj_size(target.mass)
8) trailing '|'

Side effects:
- None; returns a formatted string.
```

### ATTRIBUTE: `divby` — English description

```mud
original
divby:1000000
```

```text
Object: Downloader
Attribute: divby

Purpose:
- Scaling factor for dx/dy/dz in spit_data(); converts raw distance units into a smaller displayed magnitude.

Inputs:
- None.

Logic:
- Constant numeric value: 1000000.
```

### ATTRIBUTE: `DownLoad` — English description

```mud
original
DownLoad:$download:@foreach [inrange(v(us))] #=@swi v(0)=#,{@pem %#=[name(v(us))]|0.00|0.00|0.00|Ship|8|1},{@tr me/see_if=v(0),v(1),v(#)}
```

```text
Object: Downloader
Attribute: DownLoad

Purpose:
- Defines the $download command, emitting one record line per object detected in range of the current ship.

Inputs (by usage):
- v(us): the ship doing the scan.
- v(#): original enactor (used as the pemit target).
- v(0): foreach loop variable (current token).

Logic:
- Iterates over all dbrefs returned by inrange(v(us)), and also includes a literal '#' token.
- For each loop token:
  - If the token is '#': emits a self/ship header-like record to the requester.
  - Otherwise: triggers see_if() for that object so a record is emitted only if not already in memory.

Side effects:
- Outputs multiple lines to the requesting player.
```

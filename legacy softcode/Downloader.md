# Downloader

## Name

Downloader - Data Downloader Console

## Purpose

This is the Downloader legacy console object, used in older versions of the game to provide data downloading capabilities for spacecraft. It allows players to download sensor data about nearby objects and celestial bodies.

## Meta data

```mud
Downloader(#459h)
Type:	Thing
Owner:	Ptah
Flags:	Halted
Bytes:	2128
Children:	2
Created:	Mon Dec 5 03:57:57 1994
Modified:	Thu Dec 25 18:14:52 2025
Location:	Helm Equipment Room(#11848R)
Home:	Ptah's Chambers(#10586R)
```

## Object Definition

### Attribute Definitions

```mud
divby: inherit program
see_if(): inherit function
get_obj_size(): inherit function
get_obj_type(): inherit function
flte(): inherit function
get_obj_color(): inherit function
spit_data(): inherit function
DownLoad: inherit program
```

### Attribute list

```mud
&flte() Downloader=[lnot(match(fcomp(v(1),v(0)),-1))]
&get_obj_color() Downloader=[ifelse(flte(v(0),3E28),ifelse(flte(v(0),8E24),ifelse(flte(v(0),2E23),ifelse(flte(v(0),5E16),ifelse(flte(v(0),1E8),8,7),9),2),4),14)]
&get_obj_type() Downloader=[ifelse(flte(v(0),3E28),ifelse(flte(v(0),8E24),ifelse(flte(v(0),2E23),ifelse(flte(v(0),5E16),ifelse(flte(v(0),1E8),Ship,Station),Moon),Terran),Jovian),Star)]
&get_obj_size() Downloader=[ifelse(flte(v(0),3E28),ifelse(flte(v(0),8E24),ifelse(flte(v(0),2E23),ifelse(flte(v(0),5E16),ifelse(flte(v(0),1E8),1,2),4),8),16),32)]
&see_if() Downloader=@swi [scomp(get(v(sensor_memory),strcat(memory,v(0))),NO MATCH)]=1,{},{@pem [v(2)]=[spit_data(v(0),v(1))]}
&spit_data() Downloader=[histname(v(!),v(0))]|[fdiv(dx(v(us),v(0)),v(divby))]|[fdiv(dy(v(us),v(0)),v(divby))]|[fdiv(dz(v(us),v(0)),v(divby))]|[get_obj_type(get(v(0),mass))]|[get_obj_color(get(v(0),mass))]|[get_obj_size(get(v(0),mass))]|
&divby Downloader=1000000
&DownLoad Downloader=$download:@foreach [inrange(v(us))] #=@swi v
(0)=#,{@pem %#=[name(v(us))]|0.00|0.00|0.00|Ship|8|1},{@tr me/see_if=v(0),v(1),v(#)}
```

## English Logic Descriptions (Legacy Attribute List)

### `flte()` — English description

```text
Attribute: flte()

Purpose:
- Acts like a floating-point “<=” helper used by the other classification functions.

Inputs (by usage):
- v(0): left value
- v(1): right value

Logic:
- Performs a float compare fcomp(v(1),v(0)).
- If the compare returns -1 (meaning v(1) < v(0)), then flte returns false.
- Otherwise returns true.
Practical effect in this file:
- flte(x,THRESH) is used as “x <= THRESH” to walk mass thresholds.
```

### `get_obj_color()` — English description

```text
Attribute: get_obj_color()

Purpose:
- Maps an object’s mass into a numeric “color code” bucket for display.

Inputs:
- v(0): mass

Logic:
- Compares mass against decreasing thresholds (3E28,8E24,2E23,5E16,1E8)
- Returns a numeric code (14,4,2,9,7,8) depending on the bucket.
Notes:
- Exact numeric meanings (ANSI color index vs palette) are external; this attribute only categorizes.
```

### `get_obj_type()` — English description

```text
Attribute: get_obj_type()

Purpose:
- Maps an object’s mass into a type label.

Inputs:
- v(0): mass

Logic:
- Uses the same mass threshold ladder as get_obj_color().
- Returns one of: Ship,Station,Moon,Terran,Jovian,Star.
```

### `get_obj_size()` — English description

```text
Attribute: get_obj_size()

Purpose:
- Maps an object’s mass into a coarse size class number.

Inputs:
- v(0): mass

Logic:
- Uses the same mass threshold ladder as get_obj_color()/get_obj_type().
- Returns one of: 1,2,4,8,16,32 (bigger mass => bigger size class).
```

### `divby` — English description

```text
Attribute: divby

Purpose:
- Scaling constant used to reduce large position deltas into smaller numbers.

Value:
- 1000000

Usage:
- spit_data divides dx/dy/dz by divby before outputting.
```

### `spit_data()` — English description

```text
Attribute: spit_data()

Purpose:
- Produces a single “record line” of sensor data for one target object.

Inputs (by usage):
- v(0): target object dbref
- v(us): the ship (source of sensor position)

Output format (pipe-separated):
1) histname(v(!),v(0))     (a display name/history name for the target)
2) dx(v(us),v(0))/divby    (scaled relative X)
3) dy(v(us),v(0))/divby    (scaled relative Y)
4) dz(v(us),v(0))/divby    (scaled relative Z)
5) get_obj_type(mass)      (type label derived from target mass)
6) get_obj_color(mass)     (color code derived from target mass)
7) get_obj_size(mass)      (size class derived from target mass)
8) trailing '|' (legacy formatting convenience)

Side effects:
- None; it only returns formatted text.
```

### `see_if()` — English description

```text
Attribute: see_if()

Purpose:
- Conditional output helper used during download iteration; prints data only if target passes a memory filter.

Inputs (by usage):
- v(0): target object dbref
- v(1): (passed through) an extra value from the foreach loop; not used directly in the condition here
- v(2): destination/recipient for @pem (legacy pemit variant)

Logic:
1) Looks up a “memory slot” keyed by "memory<dbref>" on v(sensor_memory):
   get(v(sensor_memory),strcat(memory,v(0)))
2) If that value string-compares to "NO MATCH":
   - do nothing
3) Else:
   - @pem v(2)=spit_data(v(0),v(1)) (send the formatted record)

Notes:
- This is effectively “only show objects that are recognized/allowed by sensor_memory”.
```

### `DownLoad` — English description

```text
Attribute: DownLoad

Player command (legacy pattern):
- download
- Iterates over inrange(v(us)) (objects within sensor range of the ship)

High-level logic:
1) For each object returned by inrange(v(us)):
   - If the object is the ship itself (#):
     - pemit the caller a “self record”:
       name(v(us))|0.00|0.00|0.00|Ship|8|1
   - Else:
     - call/trigger see_if with (target,loopvalue,player) so see_if can decide whether to emit spit_data.

Side effects:
- Emits multiple lines to the player (and/or other destinations via @pem), one per qualifying target.
```

## MARE 2.0 Converted Softcode (from Legacy Attribute list)

```mud
&flte Downloader=[lnot(match(fcomp(v(1),v(0)),-1))]

&get_obj_color Downloader=[ifelse(flte(v(0),3E28),ifelse(flte(v(0),8E24),ifelse(flte(v(0),2E23),ifelse(flte(v(0),5E16),ifelse(flte(v(0),1E8),8,7),9),2),4),14)]

&get_obj_type Downloader=[ifelse(flte(v(0),3E28),ifelse(flte(v(0),8E24),ifelse(flte(v(0),2E23),ifelse(flte(v(0),5E16),ifelse(flte(v(0),1E8),Ship,Station),Moon),Terran),Jovian),Star)]

&get_obj_size Downloader=[ifelse(flte(v(0),3E28),ifelse(flte(v(0),8E24),ifelse(flte(v(0),2E23),ifelse(flte(v(0),5E16),ifelse(flte(v(0),1E8),1,2),4),8),16),32)]

&see_if Downloader=
@@ Legacy: @swi [scomp(get(v(sensor_memory),strcat(memory,v(0))),NO MATCH)]=1,{},{@pem [v(2)]=[spit_data(v(0),v(1))]}
switch scomp(get(v(sensor_memory),strcat(memory,v(0))),NO MATCH)
    case 1
        @@ NO MATCH: do nothing
    default
        @pem [v(2)]=[spit_data(v(0),v(1))]
endswitch

&spit_data Downloader=[histname(v(!),v(0))]|[fdiv(dx(v(us),v(0)),v(divby))]|[fdiv(dy(v(us),v(0)),v(divby))]|[fdiv(dz(v(us),v(0)),v(divby))]|[get_obj_type(get(v(0),mass))]|[get_obj_color(get(v(0),mass))]|[get_obj_size(get(v(0),mass))]|

&divby Downloader=1000000

&DownLoad Downloader=:0$download:
@@ Legacy: @foreach [inrange(v(us))] #=...
for =[sensorlist(v(us))] xx
    @@ print [name(v(us))]
    switch [v(word_)]
        case xx
            print [name(v(us))]|0.00|0.00|0.00|Ship|8|1
            break
        default
            call me/see_if=[v(word_)],[v(us)],[v(#)]
    endswitch
done
```



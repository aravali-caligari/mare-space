# Purpose of this README: Example of how to format and write english logic descriptions when asked to 'Analyze' legacy softcode attribute lists.

#
# Template for English Logic Descriptions follows here
#

## English Logic Descriptions (Legacy Attribute List)

### `<name of attribute>` — English description

```text
Attribute: <attribute name>

Purpose:
- <Purpose of the attribute/program>

Inputs (by usage):
- <names of inputs and their purpose>
- ...

Logic:
- <Description of the logic flow, conditions, loops, etc>
- ...
```

### `<another attribute name>` — English description

...

#
# End of English Logic Descriptions template
#

#
# Example of a completed English Logic Description follows here
#

## English Logic Descriptions (Legacy Attribute List)

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

#
# End of English Logic Description example
#

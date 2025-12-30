# Space Projection Functions

## Name

Space Projection Functions

## Purpose

This file contains a collection of functions used for space projection calculations within the MARE-Space simulation. These functions handle various tasks such as validating space exits, determining if an object is a ship, and calculating positional and velocity components in three-dimensional space.

## Metadata

```mud
Space Projection Functions(#46101)
Type:	Thing
Owner:	Ptah
Bytes:	1584
Children:	2
Location:	Door Equipment Room(#28607R)
Home:	Door Equipment Room(#28607R)
```

## Object Definition

### Attribute Definitions

```mud
is_valid_space_exit(): inherit function
isship(): inherit function
zvel(): inherit function
yvel(): inherit function
xvel(): inherit function
zpos(): inherit function
ypos(): inherit function
xpos(): inherit function
```

### Attribute List

```mud
is_valid_space_exit():	[1
isship():	[land(lnot(scomp(owner(v(0)),owner(me))),lnot(scomp(get(s(%0/type)),SS)))]
zvel():	[fadd(get(s(%0/linvelz)),distz(v(1),s([get(s(%0/angposx))] [get(s(%0/angposy))])))]
yvel():	[fadd(get(s(%0/linvely)),disty(v(1),s([get(s(%0/angposx))] [get(s(%0/angposy))])))]
xvel():	[fadd(get(s(%0/linvelx)),distx(v(1),s([get(s(%0/angposx))] [get(s(%0/angposy))])))]
xpos():	[fadd(get(s(%0/linposx)),distx(fadd(v(2),fadd(get(s(%0/radius)),get(s(%1/radius)))),s([get(s(%0/angposx))] [get(s(%0/angposy))])))]
ypos():	[fadd(get(s(%0/linposy)),disty(fadd(v(2),fadd(get(s(%0/radius)),get(s(%1/radius)))),s([get(s(%0/angposx))] [get(s(%0/angposy))])))]
zpos():	[fadd(get(s(%0/linposz)),distz(fadd(v(2),fadd(get(s(%0/radius)),get(s(%1/radius)))),s([get(s(%0/angposx))] [get(s(%0/angposy))])))]
```

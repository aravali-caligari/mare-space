# Legacy Console: OMS

## Name

OMS - Orbital Maneuvering System Console

## Purpose

This is the OMS legacy console object, used in older versions of the game to provide orbital maneuvering capabilities for spacecraft. It allows players to control the linear movements of their spacecraft using the Orbital Maneuvering System (OMS).

## Meta data

## Object Definition

### Attribute definitions

```mud
OMS: inherit program
MaxL: inherit program
```

### Attribute list

```mud
OMS:	$oms *=*:/[get(s(me/Nav_man))]/@swi truth(fadd(fcomp(get(s(me/MaxL)),fabs(v(1))),1)) = 0,{@pemit %#=The OMS for this ship cannot manage that much velocity.},1,{[switch(v(0),x,{@emit Firing Chi OMS.;@LinaccX get(me/us)=v(1)},y,{@emit Firing Upsilon OMS.;@LinaccY get(me/us)=v(1)},z,{@emit Firing Zeta OMS.;@LinaccZ get(me/us)=v(1)},{@pemit %#=Not a valid OMS.})]}
MaxL:	1
```

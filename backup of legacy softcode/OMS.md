# Legacy Console: OMS

## Name

OMS - Orbital Maneuvering System Console

## Purpose

This is the OMS legacy console object, used in older versions of the game to provide orbital maneuvering capabilities for spacecraft. It allows players to control the linear movements of their spacecraft using the Orbital Maneuvering System (OMS).

## Meta data

```mud
OMS(#33251h)
Type:	Thing
Owner:	Ptah
Flags:	Halted[0]
Bytes:	1084
Children:	1
Modified:	Wed Nov 12 23:20:04 2025
Location:	Engine Equipment Room(#53396R)
Home:	Engine Equipment Room(#53396R)
```

## Object Definition

### Attribute definitions

```mud
OMS: inherit program
MaxL: inherit
```

### Attribute list

```mud
OMS:	$oms *=*:/[get(s(me/Nav_man))]/@swi truth(fadd(fcomp(get(s(me/MaxL)),fabs(v(1))),1)) = 0,{@pemit %#=The OMS for this ship cannot manage that much velocity.},1,{[switch(v(0),x,{@emit Firing Chi OMS.;@LinaccX get(me/us)=v(1)},y,{@emit Firing Upsilon OMS.;@LinaccY get(me/us)=v(1)},z,{@emit Firing Zeta OMS.;@LinaccZ get(me/us)=v(1)},{@pemit %#=Not a valid OMS.})]}
MaxL:	1
```

### Converted MARE 2.0 Code syntax

```mud
@tel me=#53396

&OMS oms=:/[v(nav_man)]/2$oms:
if [truth(fadd(fcomp(v(MaxL)),fabs(%1)),1))]
 print The OMS for this spacecraft cannot manage that much acceleration.
else
 switch %0
  case xyz
   @emit Firing OMS.
   @Linburn v(us)=%1
   break
  case x
   @emit Firing Chi OMS.
   @Linburn v(us)=%1 [mid(get(v(us),linburnacc),2,3)]
   break
  case y
   @emit Firing Upsilon OMS.
   @Linburn v(us)=[mid(get(v(us),linburnacc),1,1)] %1 [mid(get(v(us),linburnacc),3,3)]
   break
  case z
   @emit Firing Zeta OMS.
   @Linburn v(us)=[mid(get(v(us),linburn),1,2)] %1
   break
  default
   print Not a valid OMS.
   break
 endswitch
endif
exit

&MaxL oms=1
```

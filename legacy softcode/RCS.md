# Legacy Console: RCS

## Name

RCS - Reaction Control System Console

## Purpose

This is the RCS legacy console object, used in older versions of the game to provide reaction control capabilities for spacecraft. It allows players to control the rotational movements of their spacecraft using the Reaction Control System (RCS).

## Meta data

## Object Definition

### Attribute definitions

```mud
rcscheck(): inherit function
rcsfake: inherit program
RCS: inherit program
MaxA: inherit program
```

### Attribute list

```mud
MaxA:	30
RCS:	$rcs *=*:/[v(Nav_man)]/@swi rcscheck(v(0),v(1))=0,{@pemit %#=The RCS for this ship cannot handle that quick of a turn.},!,{@pemit %#=Not a valid RCS.},X,{@emit Firing Theta RCS.;@angaccx v(us)=v(1)},Y,{@emit Firing Phi RCS.;@angaccy v(us)=v(1)},Z,{@emit Firing Psi RCS.;@angaccz v(us)=v(1)}
rcscheck():	[ifelse(truth(fadd(fcomp(get(s(me/MaxA)),fabs(v(1))),1)),ifelse(match(v(0),X),X,ifelse(match(v(0),Y),Y,ifelse(match(v(0),Z),Z,!))),0)]
rcsfake:	@swi truth(fadd(fcomp(get(s(me/MaxA)),fabs(v(1))),1))=0,{@pemit v(nav_man)=The RCS for this ship cannot handle that quick of a turn.},1,{[switch(v(0),x,{@emit Firing Theta RCS.;@AngaccX get(me/us)=v(1)},y,{@emit Firing Phi RCS.;@AngaccY get(me/us)=v(1)},z,{@emit Firing Psi RCS.;@AngaccZ get(me/us)=v(1)},{@pemit v(nav_man)=Not a valid RCS.})]}
```

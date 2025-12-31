# Airlock Exterior Hatch Parent

## Name

Airlock Exterior Hatch Parent - Exterior Airlock Hatch

## Purpose

This is an exterior airlock hatch object for a ship. It provides a look-through porthole description, blocks egress when the ship airlock is sealed, and when unsealed it cycles a player out through the airlock and (when applicable) launches them into space with suit/space-vector initialization.

## Metadata

```mud
Airlock Exterior Hatch Parent(#52044h)
Type:	Thing
Owner:	Ptah
Flags:	Halted
Bytes:	2160
Parents:	Space Projection Functions(#46101)
Children:	1
Location:	Door Equipment Room(#28607R)
Home:	Door Equipment Room(#28607R)
```

## Object Definition

### Attribute definitions

```mud
ejectobject: inherit program
launchsuit: inherit program
```

### Attribute list

```mud
OLook: looks out the exterior airlock hatch porthole.
OnFail: @swi get([link(me)]/airlock)=#-1*,{@fo get([link(me)]/helm)=@emit {The [name(get(s([link(me)]/helm)))] reports the attempted egress of '%N' through the sealed airlock.};@pemit %#=The exterior airlock door is sealed.},{@tr me/ejectobject=%#;@tr me/[if(land(isship(v(#)),hasflag(loc(link(me)),Z)),launchsuit)]=%#}
launchsuit: @thrust %0=0;@linposx %0=xpos([link(me)],%0,1.0);@linposy %0=ypos([link(me)],%0,1.0);@linposz %0=zpos([link(me)],%0,1.0);@linvelx %0=xvel([link(me)],0.0);@linvely %0=yvel([link(me)],0.0);@linvelz %0=zvel([link(me)],0.0);@angposx %0=get(s([link(me)]/angposx));@angposy %0=get(s([link(me)]/angposy));@angposz %0=get(s([link(me)]/angposz));@angvelz %0=get(s([link(me)]/angvelz));!enter %0;@pemit %0=The all-encompasing darkness engulfs you as you leave [name(link(me))] behind.
ejectobject: @pemit %0=You cycle out through the external airlock hatch.;@oemit %0={%[name(v(0))] cycles out through the external airlock hatch.};@fo link(me)=@emit {%%%[name(v(0))] cycles out from the airlock of the [name(link(me))].};@fo get([link(me)]/helm)=@emit {The [name(get(s([link(me)]/helm)))] reports the egress of '%%%[name(v(0))]' through the airlock.};@fo me=@tel %0=loc(link(me))
Fail: You press the open patch on the external airlock hatch.
OFail: presses the open patch on the external airlock hatch.
Desc: This is a heavy duty exterior hatch designed to protect the ship from the vacuum of space. The light above the hatch is [ifelse(lnot(first(get(s([link(me)]/airlock)))),red,green)]. Looking through the hatch's porthole you see '[name(loc(link(me)))]'.
```

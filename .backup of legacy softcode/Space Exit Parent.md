# Space Exit Parent

## Name

Space Exit Parent

## Purpose

This is the Space Exit Parent object, which serves as a template for space exit functionalities in the MARE-Space simulation. It provides the necessary attributes and behaviors for objects that allow players to exit spacecraft into the void of space, ensuring safe transitions and appropriate handling of ship movement and positioning during space exits.

## Metadata

```mud
Space Exit Parent(#25980h)
Type:	Thing
Owner:	Ptah
Flags:	Halted[0]
Bytes:	1420
Parents:	Space Projection Functions(#46101)
Location:	Door Equipment Room(#28607R)
Home:	Cyberion City Spaceport(#13034R)
```

## Object Definition

### Attribute Definitions

```mud
@@ None listed in this examine output.
```

### Attribute List

```mud
OSucc:	fires up %p engines and blasts out into the void with a tremendous roar.
OFail:	contemplates suicide by stepping into the void, but then %s decides not to.
Fail:	You would die if you stepped out there, you decide not to.
Desc:	You see a hangar door that leads out into Space.
OnSucc:	@thrust %#=0;@linposx %#=xpos([link(me)],%#,5);@linposy %#=ypos([link(me)],%#,5);@linposz %#=zpos([link(me)],%#,5);@linvelx %#=xvel([link(me)],1);@linvely %#=yvel([link(me)],1);@linvelz %#=zvel([link(me)],1);@angposx %#=get(s([link(me)]/angposx));@angposy %#=get(s([link(me)]/angposy));@angposz %#=get(s([link(me)]/angposz));@angvelz %#=get(s([link(me)]/angvelz));!enter %#;@tel %#=loc(link(me));@zlink %#=zone(loc(link(me)));@zemit get(s(%#/#44444.Zone))=The ship engines roar and the ship lurches forward into space.;@remit loc(get(s(%#/#44444.Helm)))=The all-encompasing darkness engulfs your ship as you leave [name(link(me))] behind.;@remit loc(get([link(me)]/helm))=Ship '%n' has just departed the Ship Bay.;@tr here/del_docked_ship=v(#)
```

## Attribute list (English description)

```markdown
### OSucc
- The “others see” success message when someone uses the exit successfully: describes engines firing and the ship blasting into space.

### OFail
- The “others see” failure message when someone tries to use the exit but fails: describes them considering stepping into the void, then deciding not to.

### Fail
- The message shown to the player on failure: warns they would die stepping out there.

### Desc
- The description text shown when looking at the exit: indicates it’s a hangar door leading to space.

### OnSucc
- Runs when the exit is successfully used; it transitions the ship/player from a docked/hangar context into space and initializes space-sim state:
  - Sets the ship’s thrust to 0.
  - Sets the ship’s linear position (`linposx/linposy/linposz`) using the inherited projection functions `xpos/ypos/zpos` based on the linked “source” object and the exiting ship, with an offset (5).
  - Sets the ship’s linear velocity (`linvelx/linvely/linvelz`) using `xvel/yvel/zvel` based on the linked “source” object and a direction/selector value (1).
  - Copies angular position and angular velocity values (`angposx/angposy/angposz/angvelz`) from the linked “source” object onto the exiting ship.
  - Executes the space-sim enter action (`!enter %#`).
  - Teleports the ship to the location of the linked object (the destination space room), sets zone linkage, and emits notifications:
    - Zone emit about engines roaring and lurching into space.
    - Room emits to helm-related locations about leaving the bay / departing.
  - Triggers `here/del_docked_ship` (passing `v(#)`) to remove this ship from whatever “docked ships” tracking exists at the origin.
```

## Attribute list (MARE2 conversion)

```mud
@teleport me=#28607

&OSucc Space Exit Parent=fires up %p engines and blasts out into the void with a tremendous roar.

@@@@@@@@

&OFail Space Exit Parent=contemplates suicide by stepping into the void,but then %s decides not to.

@@@@@@@@

&Fail Space Exit Parent=You would die if you stepped out there,you decide not to.

@@@@@@@@

&Desc Space Exit Parent=You see a hangar door that leads out into Space.

@@@@@@@@

@defattr Space Exit Parent/OnSucc=program
&OnSucc Space Exit Parent=
@thrust %#=0
@linposx %#=xpos([link(me)],%#,5)
@linposy %#=ypos([link(me)],%#,5)
@linposz %#=zpos([link(me)],%#,5)
@linvelx %#=xvel([link(me)],1)
@linvely %#=yvel([link(me)],1)
@linvelz %#=zvel([link(me)],1)
@angposx %#=get(link(me),angposx)
@angposy %#=get(link(me),angposy)
@angposz %#=get(link(me),angposz)
@angvelz %#=get(link(me),angvelz)
!enter %#
@tel %#=loc(link(me))
@zlink %#=zone(loc(link(me)))
@zemit get(%#,#44444.Zone)=The ship engines roar and the ship lurches forward into space.
@remit loc(get(%#,#44444.Helm))=The all-encompasing darkness engulfs your ship as you leave [name(link(me))] behind.
@remit loc(get(link(me),helm))=Ship '%n' has just departed the Ship Bay.
call here/del_docked_ship=v(#)
```


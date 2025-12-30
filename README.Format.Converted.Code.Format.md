# Purpose of this README:
# A general format template for legacy softcode that has converted to MARE2

Use the format examples below for writing converted MARE2 code when asked to 'Convert' legacy softcode attribute lists.

# MARE2 Conversion Template follows here

## Attribute list (MARE2 conversion template)

```mud
@@@@@@@@ Teleport to <Location Name> @@@@@@@@
@teleport me=#<dbref>

@@@@@@@@ Converted <Object Name>/<attribute name> @@@@@@@@

@defattr <Object Name>/<attribute name>=<flags>

&<attribute name> <Object Name>=<converted attribute value>

@@@@@@@@ Converted <Object Name>/<next attribute name> @@@@@@@@
@defattr <Object Name>/<next attribute name>=<flags>

&<next attribute name> <Object Name>=<converted attribute value>

... additional converted attributes ...
```

# End of MARE2 conversion template

# Example of a completed MARE2 conversion follows here

## Attribute list (MARE2 conversion example)

```mud
@@@@@@@@ Teleport to Space Exit Parent location @@@@@@@@
@teleport me=#28607

@@@@@@@@ Converted Space Exit Parent/OSucc @@@@@@@@

@defattr Space Exit Parent/OSucc=inherit program

&OSucc Space Exit Parent=fires up %p engines and blasts out into the void with a tremendous roar.

@@@@@@@@ Converted Space Exit Parent/OFail @@@@@@@@

@defattr Space Exit Parent/OFail=inherit program

&OFail Space Exit Parent=contemplates suicide by stepping into the void,but then %s decides not to.

@@@@@@@@ Converted Space Exit Parent/Fail @@@@@@@@

@defattr Space Exit Parent/Fail

&Fail Space Exit Parent=You would die if you stepped out there,you decide not to.

@@@@@@@@ Converted Space Exit Parent/Desc @@@@@@@@

@defattr Space Exit Parent/desc

&Desc Space Exit Parent=You see a hangar door that leads out into Space.

@@@@@@@@ Converted Space Exit Parent/OnSucc @@@@@@@@

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

... more attributes ...
```

# End of MARE2 conversion example

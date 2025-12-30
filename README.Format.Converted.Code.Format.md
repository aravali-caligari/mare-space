# Purpose of this README:
# A general format template for legacy softcode that has converted to MARE2
# Some attributes may be 'built-in' and not need to be defined with @defattr, if it is missing from the legacy metadata attribute definitions section.

#
# MARE2 Conversion Template follows here
#

## Attribute list (MARE2 conversion template)

```mud

@@ -----------------------------
@@ OBJECT: <Object Name>
@@ LOCATION: <Location Name>
@@ -----------------------------

---cut---
@teleport me=<location dbref>
---cut---

@@ ATTRIBUTE: <Object Name>/<attribute name>
@@ -----------------------------

---cut---
( @defattr <Object Name>/<attribute name>=<flags> )
or 
( @@ Built-in attribute, no need to define ) if the attribute is built-in and has no flags.
---cut---
&<attribute name> <Object Name>=<converted attribute value>
---cut---

@@ ATTRIBUTE: <Object Name>/<next attribute name>
@@ -----------------------------

---cut---
( @defattr <Object Name>/<next attribute name>=<flags> )
or 
( @@ Built-in attribute, no need to define ) if the attribute is built-in and has no flags.
---cut---
&<next attribute name> <Object Name>=<converted attribute value>
---cut---

... additional converted attributes ...
```

#
# End of MARE2 conversion template
#

#
# Example of a completed MARE2 conversion follows here
#

## Attribute list (MARE2 conversion example)

```mud
@@ -----------------------------
@@ OBJECT: Space Exit Parent
@@ LOCATION: Door Equipment Room
@@ -----------------------------

---cut---
@teleport me=#28607

---cut---

@@ ATTRIBUTE: Space Exit Parent/OSucc
@@ ----------------------------------

---cut---
@@ Built-in attribute, no need to define
---cut---
&OSucc Space Exit Parent=fires up %p engines and blasts out into the void with a tremendous roar.
---cut---

@@ ATTRIBUTE: Space Exit Parent/eject
@@ ----------------------------------

---cut---
@defattr Space Exit Parent/eject=inherit program
---cut---
&eject Space Exit Parent=call me/OnSucc
---cut---

@@ ATTRIBUTE: Space Exit Parent/OFail
@@ ----------------------------------

---cut---
@@ Built-in attribute, no need to define
---cut---
&OFail Space Exit Parent=contemplates suicide by stepping into the void,but then %s decides not to.
---cut---

@@ ATTRIBUTE: Space Exit Parent/Fail 
@@ ---------------------------------

---cut---
@@ Built-in attribute, no need to define
---cut---
&Fail Space Exit Parent=You would die if you stepped out there,you decide not to.
---cut---

@@ ATTRIBUTE: Space Exit Parent/desc
@@ ---------------------------------

---cut---
@@ Built-in attribute, no need to define
---cut---
&Desc Space Exit Parent=You see a hangar door that leads out into Space.
---cut---

@@ ATTRIBUTE: Space Exit Parent/OnSucc
@@ -----------------------------------

---cut---
@@ Built-in attribute, no need to define
---cut---
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
---cut---

... additional converted attributes ...
```

#
# End of MARE2 conversion example
#
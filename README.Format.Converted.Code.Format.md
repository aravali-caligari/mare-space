# Purpose of this README:
# A general format template for legacy softcode that has converted to MARE2

#
# MARE2 Conversion Template follows here
#

# `<Object Name>`

## Attribute list (MARE2 conversion template)

```mud

@@ -----------------------------
@@ OBJECT: <Object Name>(#dbref)
@@ LOCATION: <Location Name>(#dbref)
@@ -----------------------------

---cut---
@teleport me=<location dbref>
---cut---

@@ ATTRIBUTE: <Object Name>/<attribute name>
@@ -----------------------------

---cut---
( @defattr <Object dbref>/<attribute name>=<flags> )
or
( @defattr <Object dbref>/<attribute name> ) if there are no flags and its a user-defined attribute listed in the attribute definitions section.
or 
( @@ Built-in attribute, no need to define ) if the attribute is built-in.
---cut---
( &<attribute name> <Object dbref>=<converted attribute value> )
( @@ No value to convert, skip this attribute ) if there is no value to convert for this attribute.
---cut---

@@ ATTRIBUTE: <Object Name>/<next attribute name>
@@ -----------------------------

---cut---
( @defattr <Object dbref>/<next attribute name>=<flags> )
or
( @defattr <Object dbref>/<attribute name> ) if there are no flags and its a user-defined attribute listed in the attribute definitions section.
or 
( @@ Built-in attribute, no need to define ) if the attribute is built-in.
---cut---
( &<next attribute name> <Object dbref>=<converted attribute value> )
or
( @@ No value to convert, skip this attribute ) if there is no value to convert for this attribute.
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
@@ OBJECT: Space Exit Parent(#25980)
@@ LOCATION: Door Equipment Room(#28607)
@@ -----------------------------

---cut---
@teleport me=#28607

---cut---

@@ ATTRIBUTE: Space Exit Parent/OSucc
@@ ----------------------------------

---cut---
@@ Built-in attribute, no need to define
---cut---
&OSucc #25980=fires up %p engines and blasts out into the void with a tremendous roar.
---cut---

@@ ATTRIBUTE: Space Exit Parent/eject
@@ ----------------------------------

---cut---
@defattr #25980/eject=inherit program
---cut---
&eject #25980=call me/OnSucc
---cut---

@@ ATTRIBUTE: Space Exit Parent/OFail
@@ ----------------------------------

---cut---
@@ Built-in attribute, no need to define
---cut---
&OFail #25980=contemplates suicide by stepping into the void,but then %s decides not to.
---cut---

@@ ATTRIBUTE: Space Exit Parent/Fail 
@@ ---------------------------------

---cut---
@@ Built-in attribute, no need to define
---cut---
&Fail #25980=You would die if you stepped out there,you decide not to.
---cut---

@@ ATTRIBUTE: Space Exit Parent/desc
@@ ---------------------------------

---cut---
@@ Built-in attribute, no need to define
---cut---
&Desc #25980=You see a hangar door that leads out into Space.
---cut---

@@ ATTRIBUTE: Space Exit Parent/OnSucc
@@ -----------------------------------

---cut---
@@ Built-in attribute, no need to define
---cut---
&OnSucc #25980=
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
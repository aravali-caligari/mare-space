# `Airlock Exterior Hatch Parent`

## Attribute list (MARE2 conversion)

```mud
@@ -----------------------------
@@ OBJECT: Airlock Exterior Hatch Parent(#52044)
@@ LOCATION: Door Equipment Room(#28607)
@@ -----------------------------

---cut---
@@ Teleport to object location as a convenience
@teleport me=#28607
---cut---

@@ ATTRIBUTE: Airlock Exterior Hatch Parent/OLook
@@ --------------------------------------------

---cut---
@@ Built-in attribute, no need to @defattr
---cut---
&OLook #52044=looks out the exterior airlock hatch porthole.
---cut---

@@ ATTRIBUTE: Airlock Exterior Hatch Parent/OnFail
@@ ---------------------------------------------

---cut---
@@ Built-in attribute, no need to @defattr
---cut---
&OnFail #52044=
if [get([link(me)]/airlock)]=#-1*
  @fo get([link(me)]/helm)=@emit {The [name(get(s([link(me)]/helm)))] reports the attempted egress of '%N' through the sealed airlock.}
  print The exterior airlock door is sealed.
else
  call me/ejectobject=%#
  if land(isship(v(#)),hasflag(loc(link(me)),Z))
    call me/launchsuit=%#
  endif
endif
---cut---

@@ ATTRIBUTE: Airlock Exterior Hatch Parent/launchsuit
@@ -------------------------------------------------

---cut---
@defattr #52044/launchsuit=inherit program
---cut---
&launchsuit #52044=
@thrust %0=0
@linposx %0=xpos([link(me)],%0,1.0)
@linposy %0=ypos([link(me)],%0,1.0)
@linposz %0=zpos([link(me)],%0,1.0)
@linvelx %0=xvel([link(me)],0.0)
@linvely %0=yvel([link(me)],0.0)
@linvelz %0=zvel([link(me)],0.0)
@angposx %0=get(s([link(me)]/angposx))
@angposy %0=get(s([link(me)]/angposy))
@angposz %0=get(s([link(me)]/angposz))
@angvelz %0=get(s([link(me)]/angvelz))
!enter %0
@pemit %0=The all-encompasing darkness engulfs you as you leave [name(link(me))] behind.
---cut---

@@ ATTRIBUTE: Airlock Exterior Hatch Parent/ejectobject
@@ --------------------------------------------------

---cut---
@defattr #52044/ejectobject=inherit program
---cut---
&ejectobject #52044=
@pemit %0=You cycle out through the external airlock hatch.
@oemit %0={%[name(v(0))] cycles out through the external airlock hatch.}
@fo link(me)=@emit {%%%[name(v(0))] cycles out from the airlock of the [name(link(me))].}
@fo get([link(me)]/helm)=@emit {The [name(get(s([link(me)]/helm)))] reports the egress of '%%%[name(v(0))]' through the airlock.}
@fo me=@tel %0=loc(link(me))
---cut---

@@ ATTRIBUTE: Airlock Exterior Hatch Parent/Fail
@@ --------------------------------------------

---cut---
@@ Built-in attribute, no need to @defattr
---cut---
&Fail #52044=You press the open patch on the external airlock hatch.
---cut---

@@ ATTRIBUTE: Airlock Exterior Hatch Parent/OFail
@@ ---------------------------------------------

---cut---
@@ Built-in attribute, no need to @defattr
---cut---
&OFail #52044=presses the open patch on the external airlock hatch.
---cut---

@@ ATTRIBUTE: Airlock Exterior Hatch Parent/Desc
@@ --------------------------------------------

---cut---
@@ Built-in attribute, no need to @defattr
---cut---
&Desc #52044=This is a heavy duty exterior hatch designed to protect the ship from the vacuum of space. The light above the hatch is [ifelse(lnot(first(get(s([link(me)]/airlock)))),red,green)]. Looking through the hatch's porthole you see '[name(loc(link(me)))]'.
---cut---
```

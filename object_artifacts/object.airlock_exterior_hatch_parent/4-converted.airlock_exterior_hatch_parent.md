# `Airlock Exterior Hatch Parent`

## Attribute list (MARE2 conversion)

```mud

@@ -----------------------------
@@ OBJECT: Airlock Exterior Hatch Parent(#52044h)
@@ LOCATION: Door Equipment Room(#28607R)
@@ -----------------------------

---cut---
@@ Move to location so next commands are targeted on the right object.
@teleport me=#28607
---cut---

@@ ATTRIBUTE: Airlock Exterior Hatch Parent/OLook
@@ -----------------------------

---cut---
@@ Built-in attribute, no need to define
---cut---
&OLook #52044h=looks out the exterior airlock hatch porthole.
---cut---

@@ ATTRIBUTE: Airlock Exterior Hatch Parent/OnFail
@@ -----------------------------

---cut---
@@ Built-in attribute, no need to define
---cut---
&OnFail #52044h=
switch get(s([link(me)]/airlock))
  case #-1*
    @fo get([link(me)]/helm)=@emit {The [name(get(s([link(me)]/helm)))] reports the attempted egress of '%N' through the sealed airlock.}
    print The exterior airlock door is sealed.
    break
  default
    call me/ejectobject=%#
    if land(isship(v(#)),hasflag(loc(link(me)),Z))!=0
      call me/launchsuit=%#
    endif
endswitch
---cut---

@@ ATTRIBUTE: Airlock Exterior Hatch Parent/launchsuit
@@ -----------------------------

---cut---
@defattr #52044h/launchsuit=inherit program
---cut---
&launchsuit #52044h=
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
@@ -----------------------------

---cut---
@defattr #52044h/ejectobject=inherit program
---cut---
&ejectobject #52044h=
@pemit %0=You cycle out through the external airlock hatch.
@oemit %0={%[name(v(0))] cycles out through the external airlock hatch.}
@fo link(me)=@emit {%%%[name(v(0))] cycles out from the airlock of the [name(link(me))].}
@fo get([link(me)]/helm)=@emit {The [name(get(s([link(me)]/helm)))] reports the egress of '%%%[name(v(0))]' through the airlock.}
@fo me=@tel %0=loc(link(me))
---cut---

@@ ATTRIBUTE: Airlock Exterior Hatch Parent/Fail
@@ -----------------------------

---cut---
@@ Built-in attribute, no need to define
---cut---
&Fail #52044h=You press the open patch on the external airlock hatch.
---cut---

@@ ATTRIBUTE: Airlock Exterior Hatch Parent/OFail
@@ -----------------------------

---cut---
@@ Built-in attribute, no need to define
---cut---
&OFail #52044h=presses the open patch on the external airlock hatch.
---cut---

@@ ATTRIBUTE: Airlock Exterior Hatch Parent/Desc
@@ -----------------------------

---cut---
@@ Built-in attribute, no need to define
---cut---
&Desc #52044h=This is a heavy duty exterior hatch designed to protect the ship from the vacuum of space. The light above the hatch is [ifelse(lnot(first(get(s([link(me)]/airlock)))),red,green)]. Looking through the hatch's porthole you see '[name(loc(link(me)))]'.
---cut---

```

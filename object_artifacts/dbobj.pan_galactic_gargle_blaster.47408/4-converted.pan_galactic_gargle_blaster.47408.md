# `Pan-galactic Gargle Blaster`

## Attribute list (MARE2 conversion)

```mud
@@ -----------------------------
@@ OBJECT: Pan-galactic Gargle Blaster(#47408)
@@ LOCATION: Store Room(#36281)
@@ -----------------------------

---cut---
@@ Teleport to object location as a convenience
@teleport me=#36281
---cut---

@@ ATTRIBUTE: Pan-galactic Gargle Blaster/user
@@ ------------------------------------------

---cut---
@defattr #47408/user=inherit program
---cut---
@@ No value to convert, skip this attribute
---cut---

@@ ATTRIBUTE: Pan-galactic Gargle Blaster/drink_cmd
@@ -----------------------------------------------

---cut---
@defattr #47408/drink_cmd=inherit program
---cut---
&drink_cmd #47408=@@ Converted by AI
  :1$drink*:

  &user me=%#

  @@ Preserve legacy typos (Thorwing)
  @oemit %#=Thorwing caution to the wind, %N drinks a pan-galactic gargle blaster, and walks into a wall.
  @pemit %#=Thorwing caution to the wind, you drink a pan-galactic gargle blaster, and walk into a wall.

  @@ Legacy nested @wait blocks are a sequential delay chain
  sleep 1
  @name me=Empty Glass
  @ulock me=me

  sleep 1
  @force #36224=:smashes [name(v(user))]'s brains out.

  sleep 1
  leave

  sleep 1
  @plane [v(user)]=10
  @teleport [v(user)]=tank

  sleep 1
  @name me=Comatose [name(v(user))]
  @desc me=Well, it looks like [name(v(user))], but it's not moving.

  sleep 1
  @caption me=feels the effects of a pan-galactic gargle blaster
  @color me=[get(v(user),color)]
  @cname me=[get(v(user),cname)]

  sleep 3
  @plane [v(user)]=0

  @@ NOTE: The legacy dump ends here (truncated); any remaining logic could not be converted.
---cut---

@@ ATTRIBUTE: Pan-galactic Gargle Blaster/OnDrop
@@ --------------------------------------------

---cut---
@@ Built-in attribute, no need to @defattr
---cut---
&OnDrop #47408=@@ Converted by AI
  if match(num(me),#47408)=1
    @cemit _immortal=%N %# just activated odrop on Pan-galactic Gargle Blaster Parent [num(me)]
  else
    switch name(me)
      case Empty Glass
        :joins the rest of the empties on the floor.
        @@ Preserve legacy non-blocking wait via queued force
        @force me=sleep 2;@oemit me=The [name(#36173)] scurries over and cleans up the empty glasses.
        @lock me=me
        break
      default
        :eats a hole through the floor and disappears.
        @force me=sleep 1;@destroy me
        break
    endswitch
  endif
---cut---

@@ ATTRIBUTE: Pan-galactic Gargle Blaster/Desc
@@ ------------------------------------------

---cut---
@@ Built-in attribute, no need to @defattr
---cut---
&Desc #47408=[s(switch(name(me),Empty Glass,{A dirty tulip glass, with traces of green vapour wafting noxiously up from its surface.},{A [lgreen(bright green bubbling liquid)] in an elegant tulip glass. Steam, or some other vapour, wafts gracefully up from its surface, even though it is served at room temperature.}))]
---cut---

@@ ATTRIBUTE: Pan-galactic Gargle Blaster/_ColorName
@@ -----------------------------------------------

---cut---
@defattr #47408/_ColorName=inherit
---cut---
&_ColorName #47408=[switch(name(me),Empty Glass,{7},{9:3,10:19})]
---cut---
```

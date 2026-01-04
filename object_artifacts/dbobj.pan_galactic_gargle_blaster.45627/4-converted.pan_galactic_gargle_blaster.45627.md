# `Pan-galactic Gargle Blaster`

## Attribute list (MARE2 conversion)

```mud
@@ -----------------------------
@@ OBJECT: Pan-galactic Gargle Blaster(#45627)
@@ LOCATION: mark(#9616P)
@@ -----------------------------

---cut---
@@ Location is a player inventory (P); no teleport convenience block.
---cut---

@@ ATTRIBUTE: Pan-galactic Gargle Blaster/Vb
@@ ----------------------------------------

---cut---
@defattr #45627/Vb=inherit program
---cut---
&Vb #45627=@@ Converted by AI
  @@ Legacy began with `@va me` (no explicit value). This is treated as clearing Va so the drink command cannot be reused.
  &Va me=

  @force #36224=:smashes %0's brains out.

  @create Comatose %0
  @desc Comatose %0=Well, it looks like %0, but it's not moving.
  @lock Comatose %0=Comatose %0
  @fail Comatose %0=Comatose %0 slips out of your grasp and slumps to the floor.

  @@ Give the comatose dummy a wipeout self-cleanup command
  &Va Comatose %0=:1$wipeout:
    @tel me=me
  &Vb Comatose %0=:1$wipeout:
    @force me=sleep 1;@destroy me

  &Vz me=num(Comatose %0)

  call me/Vc=%0

  @desc me=[v(Vy)]
---cut---

@@ ATTRIBUTE: Pan-galactic Gargle Blaster/OnDrop
@@ --------------------------------------------

---cut---
@@ Built-in attribute, no need to @defattr
---cut---
&OnDrop #45627=@@ Converted by AI
  :eats a hole through the floor and disappears.
  @tel me=me
  @force me=sleep 1;@destroy me
---cut---

@@ ATTRIBUTE: Pan-galactic Gargle Blaster/Vy
@@ ----------------------------------------

---cut---
@defattr #45627/Vy=inherit program
---cut---
&Vy #45627=A dirty tulip glass, with traces of green vapour wafting noxiously up from its surface.
---cut---

@@ ATTRIBUTE: Pan-galactic Gargle Blaster/Desc
@@ ------------------------------------------

---cut---
@@ Built-in attribute, no need to @defattr
---cut---
&Desc #45627=A bright green bubbling liquid in an elegant tulip glass. Steam, or some other vapour, wafts gracefully up from its surface, even though it is served at room temperature.
---cut---

@@ ATTRIBUTE: Pan-galactic Gargle Blaster/Vd
@@ ----------------------------------------

---cut---
@defattr #45627/Vd=inherit program
---cut---
&Vd #45627=@@ Converted by AI
  leave

  @@ Legacy queued independent waits; preserve non-blocking delays via forced queued programs
  @force me=sleep 1;@teleport %0=tank
  @force me=sleep 4;@force #36223=:offers %0 a tablet to chew on.
---cut---

@@ ATTRIBUTE: Pan-galactic Gargle Blaster/Vc
@@ ----------------------------------------

---cut---
@defattr #45627/Vc=inherit program
---cut---
&Vc #45627=@@ Converted by AI
  @force [v(Vz)]=leave
  @force [v(Vz)]=leave
  call me/Vd=%0
---cut---

@@ ATTRIBUTE: Pan-galactic Gargle Blaster/Va
@@ ----------------------------------------

---cut---
@defattr #45627/Va=inherit program
---cut---
&Va #45627=@@ Converted by AI
  :1$drink*:
  @name me=Throwing caution to the wind, %N drinks
  :a pan-galactic gargle blaster, and walks into a wall.
  @name me=Empty Glass
  @adrop me=:joins the rest of the empties on the floor.

  call me/Vb=%N

  @@ Legacy used @wait (non-blocking); preserve with a queued delayed force
  @force me=sleep 3;@force #36173=lemondesc %# %N
---cut---
```

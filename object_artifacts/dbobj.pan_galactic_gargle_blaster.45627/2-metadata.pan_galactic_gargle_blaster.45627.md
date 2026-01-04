# Pan-galactic Gargle Blaster

## Name

Pan-galactic Gargle Blaster - A dangerous bright-green drink

## Purpose

A drinkable prop that (on `drink`) temporarily spoof-narrates the action, turns into an "Empty Glass", and triggers a sequence that effectively knocks the drinker out by creating a matching comatose dummy object and forcing the drinker through a small scripted recovery sequence (teleporting them to `tank` and having an NPC offer them a tablet).

## Metadata

```mud
Pan-galactic Gargle Blaster(#45627)
Type:	Thing
Owner:	Moulton
Bytes:	1848
Location:	mark(#9616P)
Home:	Bar(#36207R)
```

## Object Definition

### Attribute definitions

```mud
Vb: inherit program
Vy: inherit program
Vd: inherit program
Vc: inherit program
Va: inherit program
```

### Attribute list

```mud
Vb: @va me ; @force #36224 = :smashes %0's brains out. ; @create Comatose %0 ; @desc Comatose %0 = Well, it looks like %0, but it's not moving. ; @lock Comatose %0 = Comatose %0 ; @fail Comatose %0 = Comatose %0 slips out of your grasp and slumps to the floor. ; @va Comatose %0 = $wipeout: @tel me = me ; @vb Comatose %0 = $wipeout: @wait 1 = @destroy me ; @vz me = num(Comatose %0) ; @tr me/vc = %0 ; @desc me = %VY
OnDrop: :eats a hole through the floor and disappears.;@wait 1 = @destroy me ; @tel me = me
Vy: A dirty tulip glass, with traces of green vapour wafting noxiously up from its surface.
Desc: A bright green bubbling liquid in an elegant tulip glass. Steam, or some other vapour, wafts gracefully up from its surface, even though it is served at room temperature.
Vd: leave ; @wait 1 = @teleport %0 = tank ; @wait 4 = @force #36223 = :offers %0 a tablet to chew on.
Vc: @force %VZ = leave ; @force %VZ = leave ; @tr me/vd = %0
Va: $drink*: @name me = Throwing caution to the wind, %N drinks ; :a pan-galactic gargle blaster, and walks into a wall. ; @name me = Empty Glass; @adrop me = :joins the rest of the empties on the floor. ; @tr me/vb = %N ; @wait 3 = @force #36173 = lemondesc %# %N
```

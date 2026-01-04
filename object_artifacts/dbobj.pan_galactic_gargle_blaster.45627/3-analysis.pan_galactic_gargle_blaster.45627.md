# `Pan-galactic Gargle Blaster`

## English Logic Descriptions (Legacy Attribute List)

## OBJECT: `Pan-galactic Gargle Blaster`

### ATTRIBUTE: `Va` — Drink command entrypoint

```mud
original
$drink*: @name me = Throwing caution to the wind, %N drinks ; :a pan-galactic gargle blaster, and walks into a wall. ; @name me = Empty Glass; @adrop me = :joins the rest of the empties on the floor. ; @tr me/vb = %N ; @wait 3 = @force #36173 = lemondesc %# %N
```

```text
Object: Pan-galactic Gargle Blaster
Attribute: Va

Purpose:
- Implements the player-facing `drink` command for the item.
- Spoofs a narrative action, then converts the object into an "Empty Glass".
- Kicks off the knock-out / aftermath sequence by triggering `Vb`.

Inputs (by usage):
- %N: the player's name (used for narrative and passed into Vb).
- %#: the player's dbref (passed to `lemondesc`).

Logic:
- Temporarily renames the object to a phrase so that the subsequent pose (`:`) emits as a stylized narrative line.
- Poses that the drink is consumed and the drinker walks into a wall.
- Renames the object to "Empty Glass" and sets its drop message to join other empties.
- Triggers `Vb` with the drinker's name.
- Schedules an NPC/object (#36173) to run `lemondesc` against the actor after a short delay.
```

### ATTRIBUTE: `Vb` — Knock-out / comatose dummy creation

```mud
original
@va me ; @force #36224 = :smashes %0's brains out. ; @create Comatose %0 ; @desc Comatose %0 = Well, it looks like %0, but it's not moving. ; @lock Comatose %0 = Comatose %0 ; @fail Comatose %0 = Comatose %0 slips out of your grasp and slumps to the floor. ; @va Comatose %0 = $wipeout: @tel me = me ; @vb Comatose %0 = $wipeout: @wait 1 = @destroy me ; @vz me = num(Comatose %0) ; @tr me/vc = %0 ; @desc me = %VY
```

```text
Object: Pan-galactic Gargle Blaster
Attribute: Vb

Purpose:
- Disables further drinking from the same glass.
- Creates a comatose dummy object named after the drinker.
- Records the dummy dbref into VZ and triggers follow-up logic.
- Updates this glass's description after use.

Inputs (by usage):
- %0: drinker's name (passed in from Va).

Logic:
- Clears/empties the drink command attribute on this object (legacy uses `@va me` without an explicit value).
- Forces object #36224 to emote that it smashes the drinker's brains out.
- Creates `Comatose <name>` and sets its description to a "looks like <name>" message.
- Locks the comatose object in a way that prevents taking it, with a failure message that it slumps away.
- Gives the comatose object a `wipeout` command that teleports it to itself and then self-destructs after a short delay.
- Stores the comatose object's dbref into this object's `VZ` attribute.
- Triggers `Vc` with the drinker name for additional sequencing.
- Updates this object's description to the "dirty glass" text stored in `Vy`.
```

### ATTRIBUTE: `Vc` — Drive recovery sequence via comatose object

```mud
original
@force %VZ = leave ; @force %VZ = leave ; @tr me/vd = %0
```

```text
Object: Pan-galactic Gargle Blaster
Attribute: Vc

Purpose:
- Uses the stored comatose dummy (VZ) to run `leave` actions (twice) and then continues the sequence via `Vd`.

Inputs (by usage):
- %0: drinker's name (passed through from Vb).
- VZ: dbref of the comatose object created by Vb.

Logic:
- Forces the comatose dummy object to execute `leave` twice (likely to ensure it exits/disengages from some state).
- Triggers `Vd` with the drinker's name to continue the aftermath.
```

### ATTRIBUTE: `Vd` — Aftermath: move drinker to tank; offer tablet

```mud
original
leave ; @wait 1 = @teleport %0 = tank ; @wait 4 = @force #36223 = :offers %0 a tablet to chew on.
```

```text
Object: Pan-galactic Gargle Blaster
Attribute: Vd

Purpose:
- Applies immediate and delayed consequences to the drinker after the knock-out.

Inputs (by usage):
- %0: drinker's name.

Logic:
- Executes `leave` immediately (context-dependent; likely forces the actor out of a current state/room).
- After a short delay, teleports the named player to `tank`.
- After a longer delay, forces #36223 to pose offering the player a tablet.
- Note: legacy schedules both delays independently via `@wait`.
```

### ATTRIBUTE: `OnDrop` — Cleanup when dropped

```mud
original
:eats a hole through the floor and disappears.;@wait 1 = @destroy me ; @tel me = me
```

```text
Object: Pan-galactic Gargle Blaster
Attribute: OnDrop

Purpose:
- Prevents the item from persisting after being dropped.

Logic:
- Emits a disappearance pose.
- Teleports itself (likely to detach from room inventory stack / move home).
- Schedules itself for destruction shortly afterwards.
```

### ATTRIBUTE: `Vy` — Post-use description text

```mud
original
A dirty tulip glass, with traces of green vapour wafting noxiously up from its surface.
```

```text
Object: Pan-galactic Gargle Blaster
Attribute: Vy

Purpose:
- Stores the "empty/used" glass description text.

Logic:
- No logic; it is static text used by Vb when updating the object's description.
```

### ATTRIBUTE: `Desc` — Initial description text

```mud
original
A bright green bubbling liquid in an elegant tulip glass. Steam, or some other vapour, wafts gracefully up from its surface, even though it is served at room temperature.
```

```text
Object: Pan-galactic Gargle Blaster
Attribute: Desc

Purpose:
- Describes the object before it is used.

Logic:
- No logic; it is static descriptive text.
```

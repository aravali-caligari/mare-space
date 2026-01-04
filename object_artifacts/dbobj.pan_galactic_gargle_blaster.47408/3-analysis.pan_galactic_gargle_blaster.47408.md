# `Pan-galactic Gargle Blaster`

## English Logic Descriptions (Legacy Attribute List)

## OBJECT: `Pan-galactic Gargle Blaster`

### ATTRIBUTE: `drink_cmd` — Drink command (template version)

```mud
original
$drink*:@user me=%#;@oemit %#=Thorwing caution to the wind, %N drinks a pan-galactic gargle blaster, and walks into a wall.;@pe %#=Thorwing caution to the wind, you drink a pan-galactic gargle blaster, and walk into a wall.;@wait 1={@name me=Empty Glass;@ulock me=me;@wait 1={@force #36224=:smashes [name(v(user))]'s brains out.;@wait 1={leave;@wait 1={@plane [v(user)]=10;@teleport [v(user)]=tank;@wait 1={@name me=Comatose [name(v(user))];@desc me=Well, it looks like [name(v(user))], but it's not moving.;@wait 1={@caption me=feels the effects of a pan-galactic gargle blaster;@color me=[get(v(user),color)];@cname me=[get(v(user),cname)];@wait 3={@plane [v(user)]=0
```

```text
Object: Pan-galactic Gargle Blaster
Attribute: drink_cmd

Purpose:
- Defines the `$drink*` command.
- Records the actor dbref in `user`.
- Emits a narrative line to the room and a first-person line to the actor.
- Then performs a delayed chain of effects: turns into Empty Glass, locks it, plays an emote via #36224, makes the actor "leave", moves the actor to `tank` (changing plane), and converts the object into a matching comatose dummy with copied color/name metadata.

Inputs (by usage):
- %#: actor dbref.
- %N: actor name.
- v(user): stored actor dbref.

Logic:
- Sets `user` to the actor dbref.
- Emits two messages (room + actor).
- Runs a nested sequence of `@wait` blocks to do timed effects.
- IMPORTANT: The legacy dump appears truncated mid-program (it ends right after `@plane [v(user)]=0` with no closing braces / follow-on actions). Downstream logic may be missing from the dump.
```

### ATTRIBUTE: `OnDrop` — Conditional cleanup

```mud
original
@switch [match(num(me),#47408)]=1,{@cemit _immortal=%N %# just activated odrop on Pan-galactic Gargle Blaster Parent [num(me)]},{@switch [name(me)]=Empty Glass,{:joins the rest of the empties on the floor.;@wait 2=@oemit me=The [name(#36173)] scurries over and cleans up the empty glasses.;@lock me=me},{:eats a hole through the floor and disappears.;@wait 1=@destroy me}}
```

```text
Object: Pan-galactic Gargle Blaster
Attribute: OnDrop

Purpose:
- When dropped, either logs a debug message (if this is the parent/template), or performs cleanup behavior depending on whether the object is an Empty Glass.

Logic:
- If `match(num(me),#47408)=1` (i.e., the template object itself), emit a staff/debug message to `_immortal`.
- Else, switch on `name(me)`:
  - If `Empty Glass`: pose that it joins other empties; after 2s emit a cleanup message; then lock the object to itself.
  - Otherwise: pose that it disappears; after 1s destroy the object.
```

### ATTRIBUTE: `Desc` — Dynamic description

```mud
original
[s(switch(name(me),Empty Glass,{A dirty tulip glass, with traces of green vapour wafting noxiously up from its surface.},{A [lgreen(bright green bubbling liquid)] in an elegant tulip glass. Steam, or some other vapour, wafts gracefully up from its surface, even though it is served at room temperature.}))]
```

```text
Object: Pan-galactic Gargle Blaster
Attribute: Desc

Purpose:
- Provides a description that changes depending on whether the object has been consumed/renamed to Empty Glass.

Logic:
- If `name(me)` is `Empty Glass`, return the "dirty tulip glass" description.
- Otherwise, return the "bright green bubbling liquid" description (with color formatting).
```

### ATTRIBUTE: `_ColorName` — Dynamic color name

```mud
original
[switch(name(me),Empty Glass,{7},{9:3,10:19})]
```

```text
Object: Pan-galactic Gargle Blaster
Attribute: _ColorName

Purpose:
- Provides a color-name selector dependent on whether this is an Empty Glass.

Logic:
- If name is `Empty Glass`, return `7`.
- Otherwise return `9:3,10:19`.
```

# `Pan-galactic Gargle Blaster`

This file explains the TinyMARE II conversion in
`4-converted.pan_galactic_gargle_blaster.47408.md`, and how it preserves the
behavior described in `3-analysis.pan_galactic_gargle_blaster.47408.md`.

## Prelude: convenience teleport

This prelude is not part of the object’s logic; it just moves you to the object’s
recorded location in the dump to make manual testing easier.

```mud
original
@@ Teleport to object location as a convenience
@teleport me=#36281
```

## ATTRIBUTE: `user`

This attribute is declared but had no value in the conversion output, so there
is nothing to explain beyond intent.

```mud
original
@defattr #47408/user=inherit program
@@ No value to convert, skip this attribute
```

Behavior preserved:
- The legacy code stores the actor dbref into `user` before running delayed
  effects. In the converted version, `user` is written by the `drink_cmd`
  program (see below).

## ATTRIBUTE: `drink_cmd`

```mud
original
@defattr #47408/drink_cmd=inherit program
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
```

Why this preserves behavior:
- Actor tracking: the legacy `$drink*` command begins with `@user me=%#`.
  The conversion does the equivalent with `&user me=%#`, storing the actor dbref
  on the drink object.
- Messaging: legacy emits a room message (`@oemit %#=...`) and a first-person
  message to the actor (`@pe %#=...`). The conversion keeps the same text and
  keeps the original typo (“Thorwing”), using `@pemit` for the actor message.
- Timed effect chain: the legacy code is a deeply nested `@wait 1={...}` chain.
  The conversion converts this to sequential `sleep N` statements followed by
  the same commands, which is the simplest equivalent model for “do X, then 1s
  later do Y, then 1s later do Z…”.
- Empty glass transition: `@name me=Empty Glass` and `@ulock me=me` preserve the
  legacy “turn into empty glass and lock it” step.
- Dramatic emote: `@force #36224=:smashes ...` preserves the legacy forced pose
  on `#36224`, and uses `name(v(user))` to resolve the actor’s name.
- Movement + plane changes: `@plane [v(user)]=10` / `@teleport [v(user)]=tank`
  preserve moving the actor to `tank` while temporarily changing plane, then
  returning them to plane `0` at the end.
- Comatose dummy + metadata copy: the conversion renames and describes the drink
  object into a “Comatose <player>” shell and copies `color` and `cname` from the
  actor, matching the legacy behavior.

Important caveat (matches the analysis):
- The legacy dump appears truncated mid-program (it ends immediately after the
  `@plane ...=0` line without closing braces). The conversion explicitly calls
  this out and cannot safely recreate missing post-truncation behavior.

## ATTRIBUTE: `OnDrop`

```mud
original
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
```

Why this preserves behavior:
- Parent/template guard: the legacy code checks `match(num(me),#47408)` to
  distinguish the parent/template object from its clones; the conversion keeps
  that and routes to the `_immortal` debug message when true.
- Empty-glass cleanup path: the legacy did `:joins...;@wait 2=@oemit ...;@lock`.
  The conversion keeps the pose line and lock, and uses `@force me=sleep 2;...`
  to implement a delayed, non-blocking emit.
- Default cleanup path: the legacy posed a disappearance and did `@wait 1=@destroy`.
  The conversion keeps the pose and delays destruction by queuing `sleep 1` via
  `@force me=...`.
- Structured control flow: the inline legacy `@switch` becomes a structured
  `switch/case/default`, preserving behavior while improving readability.

## ATTRIBUTE: `Desc`

```mud
original
&Desc #47408=[s(switch(name(me),Empty Glass,{A dirty tulip glass, with traces of green vapour wafting noxiously up from its surface.},{A [lgreen(bright green bubbling liquid)] in an elegant tulip glass. Steam, or some other vapour, wafts gracefully up from its surface, even though it is served at room temperature.}))]
```

Why this preserves behavior:
- This is already in function form in the legacy dump, so the conversion largely
  preserves it as-is.
- The `switch(name(me),Empty Glass,{...},{...})` continues to select the “empty
  glass” description vs. the “full drink” description.
- The `lgreen(...)` formatting is preserved.

## ATTRIBUTE: `_ColorName`

```mud
original
@defattr #47408/_ColorName=inherit
&_ColorName #47408=[switch(name(me),Empty Glass,{7},{9:3,10:19})]
```

Why this preserves behavior:
- The legacy expression is already a pure `switch(...)` function, so it can be
  carried over directly.
- It preserves the same selectors (`7` for `Empty Glass`, otherwise `9:3,10:19`).

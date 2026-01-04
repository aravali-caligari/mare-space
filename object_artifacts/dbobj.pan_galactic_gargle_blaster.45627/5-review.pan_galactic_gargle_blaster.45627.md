# Review: Pan-galactic Gargle Blaster(#45627)

## Scope

Converted a single legacy Thing with a `drink` command into TinyMARE II / Mare2 softcode, preserving the original behavior (narrative spoofing, comatose dummy creation, delayed teleport/offer, and drop cleanup).

## Key correctness notes

- `$drink*:` was converted to a TinyMARE II command header `:1$drink*:` within the existing `Va` attribute so the runtime code that clears `Va` continues to work.
- Legacy `@wait` usage was converted to `sleep`, but where legacy scheduled multiple independent waits or relied on non-blocking behavior, the conversion preserves that by queueing delayed actions via `@force me=sleep N;...`.
- Legacy `@tr` triggers were converted to `call me/<attr>=...`.
- `%VZ` / `%VY` were mapped to `v(Vz)` / `v(Vy)` lookups.

## Potential behavior risks (verify in-game)

- The legacy `@va me` token at the start of `Vb` had no explicit `=` value; the conversion interprets it as clearing `Va` (disabling the drink command). If this was meant to *display* `Va` instead, behavior would differ (but that would be unusual inside an action program).
- The object names `Comatose %0` assume the created object's name is unique enough for `num(Comatose %0)` to resolve to the newly created object as in legacy.

## Suggested quick tests

- Run `drink` on the object and confirm:
  - you see the narrative line and the item becomes `Empty Glass` with the updated drop message,
  - a `Comatose <name>` object appears with the correct description and cannot be picked up,
  - after ~1s you are teleported to `tank`, and after ~4s the tablet offer message appears,
  - dropping the glass causes it to disappear/cleanup.

# Review: Airlock Exterior Hatch Parent (#52044)

## Behavior preservation

- `OnFail` still blocks egress when `get(link(me)/airlock)` matches `#-1*`, reports to helm, and notifies the player.
- The “success” branch still calls `ejectobject` and conditionally calls `launchsuit` when `land(isship(v(#)),hasflag(loc(link(me)),Z))` is true.
- Messaging strings and emitted report text were preserved verbatim (except `@pemit %#=` → `print`).

## Conversion notes

- Converted legacy `@swi` into structured `switch`/`case`/`default`/`endswitch` and removed the legacy “call attribute name possibly empty” pattern by rewriting it as an explicit `if` guarding `launchsuit`.
- Converted legacy SpaceMUSE per-axis state updates (`@linposx/@linvelx/@angposx/...`) into SpaceMARE2 vector/euler forms using `@pos`, `@vel`, `@attpos`, `@attvel` per the SpaceMUSE→SpaceMARE2 guidance.
- Replaced legacy `@fo` with `@force` for clarity; if TinyMARE II retains `@fo` alias only, this is the one place that might need reverting.

## Potential follow-ups / risks

- The EVA offset previously computed via legacy `xpos/ypos/zpos(...,1.0)` is approximated as `@pos = ship_pos + (e2v(ship_attpos) * 1.0)`.
  - This assumes `e2v()` returns a suitable forward-direction vector for the ship attitude and that `@attpos` exists on the linked ship.
  - If the intended direction/offset differs, adjust the offset vector calculation (e.g., rotate a base vector with `vrotate()` if needed).
- This conversion assumes ship state is stored in `link(me)/@pos`, `link(me)/@vel`, `link(me)/@attpos`, `link(me)/@attvel` and is readable via `get()`.

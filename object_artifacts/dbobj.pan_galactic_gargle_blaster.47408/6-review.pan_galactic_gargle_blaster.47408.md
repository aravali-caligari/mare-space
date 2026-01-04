# `Pan-galactic Gargle Blaster` — Review (`#47408`)

Scope: review the conversion in `4-converted.pan_galactic_gargle_blaster.47408.md`
using the intent captured in `3-analysis.pan_galactic_gargle_blaster.47408.md`.

## Behavior preservation

Passes (high confidence):
- **OnDrop behavior** matches the legacy intent:
  - Parent/template check (`match(num(me),#47408)=1`) emits a debug message.
  - Non-parent clones: `Empty Glass` path queues a 2s delayed cleanup emit and
    locks the object; default path queues a 1s delayed destroy.
- **Desc** and **_ColorName** are direct functional translations from the legacy
  expressions and should behave identically.
- **Drink effect timing model** is preserved: nested `@wait 1={...}` chains become
  sequential `sleep 1` steps, which is the closest straightforward equivalent.

Known limitation (in source dump):
- The legacy `$drink*` program is truncated mid-body (as noted in the analysis).
  The conversion explicitly stops where the dump stops, so any missing legacy
  tail behavior cannot be validated or preserved.

## Correctness risks / follow-ups

Potential command-hook mismatch:
- The legacy defines the player command as `$drink*:`.
- The conversion stores everything in `&drink_cmd #47408=...` and includes a line
  `:1$drink*:` at the top of the program.
- If the intent is “define a `1$drink*` command attribute”, that line likely does
  not accomplish it by itself (it looks like a pose command containing the text
  `1$drink*:`). If the engine expects command patterns to be implemented as
  attributes like `&1$drink* #47408=...`, this should be revisited.

`v(user)` usage is acceptable:
- The conversion uses `&user me=%#` (sets the `user` attribute on the object).
- Later reads use `v(user)`, which in this codebase resolves a local variable if
  set, otherwise reads the `user` attribute on the current object; that matches
  the storage choice.

Formatting / markdown correctness:
- `4-converted.pan_galactic_gargle_blaster.47408.md` appears to end with an extra
  dangling Markdown code fence (an empty ``` block). That’s harmless to runtime
  but makes the artifact harder to read.

## Style / conversion conventions

Aligned with repo guidelines:
- Uses structured `switch/case/default/break/endswitch` for `OnDrop`.
- Converts `@wait N=...` to `sleep N` and (where non-blocking was desired) uses
  `@force me=sleep N;...`.
- Preserves legacy text verbatim (including the “Thorwing” typo), which is
  consistent with “preserve behavior”.

## Recommendation

- If the command binding is expected to be a real `$drink*`/`1$drink*` attribute
  (rather than a program called by another dispatcher), adjust the conversion so
  the engine will actually register the command.
- Optionally fix the trailing Markdown fence in the `4-converted` artifact for
  readability (no gameplay impact).

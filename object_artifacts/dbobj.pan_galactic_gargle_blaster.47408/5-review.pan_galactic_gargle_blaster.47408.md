# Review: Pan-galactic Gargle Blaster(#47408)

## Scope

Converted the parent/template Pan-galactic Gargle Blaster object into Mare2/TinyMARE II syntax.

## Key correctness notes

- `drink_cmd` is converted as a TinyMARE II command attribute using `:1$drink*:` with a structured, sequential `sleep` chain to replace nested legacy `@wait` blocks.
- `OnDrop` legacy `@switch` logic is mapped to `if` + `switch` with `@force me=sleep N;...` for non-blocking delayed emits/destroys.
- `Desc` and `_ColorName` are preserved as functional expressions, since they are already in function-call form.

## Known blocker

- The legacy dump for `drink_cmd` is truncated (it ends after `@plane [v(user)]=0` with missing closing braces and any subsequent actions). The conversion stops at that point and includes a note in the converted attribute.

## Suggested quick tests

- Trigger `drink` and verify the delayed chain executes through the plane reset.
- Drop as `Empty Glass` and confirm the cleanup message and lock behavior.
- Drop as non-empty and confirm it disappears/destroys.

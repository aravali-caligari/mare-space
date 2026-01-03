# Review: Downloader (#459)

## Behavior preservation

- Pure helper functions (`flte()`, `get_obj_color()`, `get_obj_type()`, `get_obj_size()`) were preserved as expression-returning functions.
- `spit_data()` still outputs the same pipe-delimited record and uses `dx/dy/dz` scaled by `divby`, with type/color/size derived from target mass.
- `see_if()` still suppresses output when sensor-memory indicates a stored entry (non-`NO MATCH`), and otherwise emits a record line to the requested recipient.
- `$download` still iterates over `inrange(v(us))` and also a literal `#` sentinel to emit the “self/ship” record.

## Conversion notes

- Multi-line wrapped legacy attribute values were normalized to single-line before conversion.
- Converted `@swi` to structured `if`/`switch` blocks.
- Converted legacy `$download:@foreach ...` to TinyMARE II `for` loop form per the repo’s common conversion guidance.
- Converted `@pem %#=` (enactor-only) to `print ...`.

## Potential risks / assumptions

- Assumes TinyMARE II supports `for`/`set`/`done` with the loop variable usable via `v(i__)` and that `set 0=...` sets `v(0)`.
- `see_if()` uses `@pemit [v(2)]=...` because the target is not always `%#` (matches legacy intent).
- The `Location` dbref suffix `#5745PDo` was normalized to `#5745` in the conversion header/teleport.

# `Frontier Storm Door Master` — Review

## Summary

This conversion preserves the legacy door behavior: panel interaction routing via `OnFail`, state display via `OnLook`, passage messaging + teleport via `Passthrough`/`Godoor`, delayed close via `AutoClose`, and XOR-style sibling locking via `XORList` + parent-child scanning.

## Correctness notes

- `@pemit %#=...` was converted to `print ...` per project mechanical rules; targeted `@pemit %0=...` remains unchanged.
- Legacy `@wait N=...` blocks were converted to `sleep N` with structured blocks.
- Legacy `@tr` triggers were converted to `call`.
- Legacy `@foreach` patterns were converted to TinyMARE II `for` loops using environment variables (`8` and `9`) to avoid clobbering `%0`/`%#` arguments.
- `get(obj/attr)` patterns were normalized to `get(obj,attr)` and `get(s(obj),attr)` forms.

## Notable behavior/edge cases

- `AutoOpen` semaphore logic is under-specified in this single-object dump because `semaphore` has no body here (likely inherited from the parent). The conversion keeps the same high-level ordering: queue → choose `Godoor` vs `Passthrough` based on the last queue entry → delay → force the semaphore handler.
- The legacy `Godoor` line contained extra `)` characters in `@pemit`/`@oemit`; the converted form drops the stray parentheses while keeping the same message sources.
- The legacy `lookthrough` contained `@pemit s(%0)=...` which appears to be a typo; the conversion uses `@pemit %0=...` to preserve the intended “show succ text” behavior.

## Formatting / style

- Uses 2-space indentation for blocks.
- Uses `switch`/`case`/`default`/`endswitch` and avoids “call attribute name possibly empty” patterns in `OnLook`.

## Suggested quick in-game smoke tests

- `look <door>` when ACTIVE/LOCKED/OPEN/WINDOW flags vary (verifies panel lights + `lookthrough`).
- Use/open button when door closed and when open (verifies `OnFail` routing).
- Trigger `AutoOpen` and confirm both sides become OPEN and you pass through.
- Verify XOR lock/unlock effects on sibling doors with matching `ID` patterns.

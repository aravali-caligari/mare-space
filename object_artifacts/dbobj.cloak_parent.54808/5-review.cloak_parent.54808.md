# Review: Cloak Parent (#54808)

## Behavior preservation

- Commands preserved:
  - `cloak on passkey=<passkey>`: refuses if already cloaked; validates passkey; sets `vismult` to `-1`; emits engaged.
  - `cloak off`: refuses if already off; sets `vismult` to `1`; emits disengaged.
  - `cloak passkey <old>=<new>`: validates old passkey; sets new passkey.
  - `initial passkey=<passkey>`: sets passkey only when blank.
  - `cloakhelp`: prints the same help text.
- The permission lock `:/[v(eng_man)]/` is preserved at the command entrypoints.

## Conversion notes

- Legacy multi-word `$` commands were converted into TinyMARE II single-word command dispatchers:
  - `3$cloak` handles `on passkey`, `off`, and `passkey <old>=<new>`.
  - `3$initial` handles `passkey=<passkey>`.
  - `1$cloakhelp` remains a single-word command.
- Legacy `@swi` was converted to structured `if` blocks for readability.
- `@pemit %#=` was converted to `print` in all user-facing outputs.

## Potential follow-ups / risks

- Dispatcher parsing relies on `first()` and `rest()` for `cloak passkey <old>=<new>`.
  - If `rest()` is not available or behaves differently in TinyMARE II, this dispatch branch may need adjustment (e.g., use a different string/list split helper).
- This keeps legacy `vismult` / `@vismult` behavior intact.
  - The MARE:Space2 conversion cheat sheet notes `VisMult` may not have a modern equivalent; if `@vismult` is removed in your current MARE:Space2 build, this will need redesign.
- `@passkey me=...` is preserved as a legacy setter for the passkey attribute.
  - If `@passkey` is not a valid command in TinyMARE II, replace it with the appropriate attribute-setter syntax used in your codebase.

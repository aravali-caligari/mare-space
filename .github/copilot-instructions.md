---
applyTo: "*.md"
---

# mare-space: SpaceMARE softcode + conversions

This repo is documentation + softcode source control for the SpaceMARE simulation used in TinyMARE II. The *server/engine C code* lives in a separate repo (see the link in `README.md`).

## Where to look

- `legacy softcode/*.md`: per-object legacy softcode dumps (look for **Attribute Definitions** + **Attribute list** sections and fenced `mud` blocks).
- `TinyMARE II help documentation.md`: authoritative MARE2/TinyMARE programming syntax (`print`, `if/else/endif`, `switch/endswitch`, `call`, `wait`, `for ... done`, etc).
- `README.legacy.conversions.md`: SpaceMUSE → SpaceMARE naming/function conversions and data model changes.
- `README.softcode.manual.md`: SpaceMARE-specific `@` commands and datatypes.
- `legacy_MARE_helptext.html`: legacy MARE command/function help.

## How to handle softcode conversion tasks

- Treat fenced `mud` blocks as **legacy** MARE/MUSE/MUSH-style softcode. Parse:
  - substitutions: `[ ... ]`, variables `%0-%9` / `v(0)-v(9)`
  - locks: `:/[ ... ]/` (lock failure prevents execution)
  - multi-command lines: `;` splits commands (unless inside `{ ... }`)
- If asked to **analyze**: produce an English description of each attribute/program (include the original attribute name) inside a fenced `markdown` block.
- If asked to **convert**: output the converted code inside a fenced `mud` block; preserve behavior exactly.

## Common mechanical conversions (use these patterns)

- `@pemit %#=...` → `print ...` (no quotes).
- `@tr <obj>/<attr>[=<args>]` → `call <obj>/<attr>[=<args>]`.
- `@swi/@switch cond,{...},{...}` → structured `switch cond` with `case`, `default`, `break`, `endswitch`.
- `@wait N=...` → `wait N` then the block.
- `@foreach v(list)=...` → `for word__=v(list)` ... `done`.
- `$command` definitions: move them behind the lock and convert to `:/[lock]/N$command:` where `N` matches TinyMARE II command arg patterns (1/2/3).
- Rename attribute names containing `?` or `+` to `_` and update all references.

## Formatting expectations for converted snippets

- Use indentation for blocks; use `else`/`endif` (do not use `{}` for `if` blocks).
- No spaces around `=` and no spaces after commas in argument lists.
- If attribute flags are known, emit them explicitly: `@defattr <obj>/<attr>=<flags>` then `&<attr> <obj>=...`.
- If a markdown object file has metadata with `Location: ...(#<id>R)`, start conversion with `@teleport me=#<id>`.
- Separate converted attributes with: blank line, a line containing `@@@@@@@@`, blank line.


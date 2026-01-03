---
applyTo: "*.md,*.html,*.txt"
---

# mare-space: SpaceMARE softcode conversions

This repo is documentation + softcode source control for the SpaceMARE simulation used in TinyMARE II. The server/engine C code lives in a separate repo (see `README.md`).

## Inputs and outputs

- Ignore `.backup of legacy softcode/` (reference only).
- Raw legacy dumps: `legacy_examine_dumps/incoming/` (may contain multiple objects per file).
- After *all requested steps* are complete: move dumps to `legacy_examine_dumps/processed/`.
- Per-object artifacts live in `object_artifacts/dbobj.<object_name>.<id>/` (see `README.Template.Folder.File.Structure.md`).
- Space conversion quick reference: `README.AI.Space.legacy.conversions.md`.
- SpaceMARE2 commands/datatypes quick reference: `README.AI.Space.softcode.manual.md`.

## Workflow (always in order)

When asked to do multiple steps, do: **parse → analyze → convert → review**. Do not move a dump to `processed/` until the requested steps are done.

### Parse

- For each object found in each dump in `legacy_examine_dumps/incoming/`:
  - Create `object_artifacts/dbobj.<object_name>.<id>/`.
  - Normalize `<object_name>` for filenames: lower-case, underscores, no spaces/punct.
  - Write `1-examine.<object_name>.<id>.txt` using `README.Format.Examine.md`.
  - If any attribute value is split over multiple lines in the raw dump, join lines with spaces so each attribute value becomes a single line.
  - Convert to `2-metadata.<object_name>.<id>.md` using `README.Format.Metadata.md`.

### Analyze

- For each `2-metadata...md` missing `3-analysis...md`:
  - Create `3-analysis.<object_name>.<id>.md` using `README.Format.Analysis.English.Description.md`.
  - For every attribute/program in the `### Attribute list` section, write an English logic description.
  - Include an `original` fenced block containing the original legacy code for that attribute near the top of each attribute section.

### Convert

- For each `3-analysis...md` missing `4-converted...md`:
  - Create `4-converted.<object_name>.<id>.md` using `README.Format.Converted.Code.md`.
  - Reference the legacy softcode documentation in `README.AI.legacy_MARE_helptext.html` for how to understand legacy constructs, functions, and commands.
  - Preserve behavior; use TinyMARE II syntax (see `README.AI.TinyMARE.II.Helptext.Programming.html` and `README.AI.TinyMARE.II.Helptext.html`).
  - Respect any manual edits/clarifications in `3-analysis...md`.
  - Built-in attributes: if present in the `### Attribute list` section but missing from `### Attribute definitions`, do not `@defattr` them.
  - You may add helper attributes for dispatch/state; `@defattr #<id>/<newattr>=inherit program` before use.
  - For SpaceMARE-specific code, consult `README.AI.Space.legacy.conversions.md` and `README.AI.Space.softcode.manual.md`.
  - For `@swi` commands, prefer structured `switch`/`case`/`default`/`break`/`endswitch` over inline forms.
  - `v(name)` returns local 'name' variable if set; otherwise it reads the 'name' attribute on the current object.
  - `for 0=list` loops over list items, setting `v(0)`/`%0` to each item in turn.

### Review

- Create `5-review.<object_name>.<id>.md` reviewing correctness, formatting expectations, and behavior preservation.

## Common mechanical conversions

- Substitutions: `[ ... ]`, variables `%0-%9` / `v(0)-v(9)`.
- Locks: `:/[ ... ]/` (lock failure prevents execution).
- Multi-command lines: `;` splits commands (unless inside `{ ... }`).
- `@pemit %#=...` → `print ...` 
- `@pemit obj=...` (non-`%#`) → preserve as-is.
- If a display command starts with a function call, wrap that call in `[...]`.
- `@defattr #<id>/<attr>=<flags>` → `&<attr> #<id>=<flags>`.
- `@if cond=...` → `if cond` ... `endif`.
- `@tr <obj>/<attr>[=<args>]` → `call <obj>/<attr>[=<args>]`.
- `@swi/@switch cond,{...},{...}` → structured `switch cond` / `case` / `default` / `break` / `endswitch`.
- `@wait N=...` → `sleep N` ... body.
- `@foreach v(list)=...` → `for 0=v(list)` ... `done`.
- `get(obj/attr)` → `get(obj,attr)`.
- `get([func()]/attr)` → `get(func(),attr)`.
- `get(s([func()]/attr))` → `get(s(func()),attr)`.
- `get(s(me/attr))` → `get(me,attr)`.


### `$command` definitions

- Converted `$command` names are a single word; legacy multi-word subcommands usually require a `3$<cmd>` dispatcher.
- Follow `README.How.Command.Args.Work.md` for `1$`/`2$`/`3$` patterns, locks, player-locks (`P`), and ignore-unhandled (`~`).

## Formatting expectations (converted snippets)

- Use indentation for blocks (2-spaces) ; use `else`/`endif` (do not use `{}` for `if` blocks).
- No spaces around `=` in code unless its part of a message; no spaces after commas in argument lists.
- Inside `{ ... }`, preserve original spacing and keep as single line.
- If attribute flags are known: `@defattr #<id>/<attr>=<flags>` then `&<attr> #<id>=...`.
  - Use numeric dbref (no `R`/`h` suffix).
- If metadata has `Location: ...(#<id>R)`, start conversion with:
  - `@@ Teleport to object location as a convenience`
  - `@teleport me=#<id>`
- Preserve comments starting with `@@` and `---cut---` separators.
- Generated Comments cannot have `;` (conflicts with command separator).
- If an attribute body looks like code, then insert `@@ Converted by AI` directly at the end of the `&<attr> #<id>=` line.
- If an attribute body is just a message (e.g. `You see ...`) without any beginning command, do not insert `@@ Converted by AI` (to reduce clutter).
- If a user-defined attribute is just a message (no commands), remove `program` flag from its `@defattr` line.




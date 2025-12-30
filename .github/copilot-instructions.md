---
applyTo: "*.md"
---

# mare-space: SpaceMARE softcode + conversions

This repo is documentation + softcode source control for the SpaceMARE simulation used in TinyMARE II. The *server/engine C code* lives in a separate repo (see the link in `README.md`).

## Where to look

- `legacy softcode/*.md`: per-object legacy softcode dumps (look for **Attribute Definitions** + **Attribute list** sections and fenced `mud` blocks).
- `legacy_examine_dumps/`: Folders and files containing raw legacy softcode dumps (if any) used as sources for parsing. May contain multiple objects per file.
  - `Incoming/`: Individual raw examine dumps as text files that may contain multiple objects per file.
  - `Processed/`: The same raw examine dump files after they are parsed, and moved from 'Incoming/' to this folder.
- `object_artifacts/`: area to store artifacts like the parsed object metadata, english analysis descriptions, converted MARE2 softcode. Subfolders per object. Read `README.Template.Folder.File.Structure.md` for details.
- `TinyMARE II help documentation.md`: authoritative MARE2/TinyMARE programming syntax (`print`, `if/else/endif`, `switch/endswitch`, `call`, `wait`, `for ... done`, etc).
- `README.Format.of.Examine.md`: struture + example for the incoming object 'examine' structure before converting the object to legacy markdown format.
- `README.Format.Legacy.Markdown.md`: template + example for legacy softcode dumps in markdown format
- `README.Format.English.Description.md`: template + example for writing English logic descriptions when asked to 'Analyze' legacy softcode attribute lists.
- `README.Format.Converted.Code.Format.md`: template + example for writing converted MARE2 code when asked to 'Convert' legacy softcode attribute lists.
- `README.Template.Folder.File.Structure.md`: recommended folder + file structure for the repo. Describes where to parse legacy code from, what folders to create, for the parsed objects, and where to place english analysis and converted code files.
- `README.legacy.conversions.md`: SpaceMUSE → SpaceMARE naming/function conversions and data model changes.
- `README.softcode.manual.md`: SpaceMARE-specific `@` commands and datatypes.
- `legacyspacesim/`: legacy Space Sim C source files (reference only for understanding legacy space functions and commands used by softcode).
- `legacy_MARE_helptext.html`: legacy MARE1 command/function help.

## How to handle softcode conversion tasks

- If asked to **parse**: Examine all text files inside the `legacy_examine_dumps/Incoming/` folder. For each object found in the file, create a subfolder inside `object_artifacts/` named `Object.<Object_Name>/` and create an `examine.<object_name>.md` file inside it with the structure described in `README.Format.of.Examine.md`. Convert the object names to file names using traditional filename conventions (no spaces, no punctuation, no special symbols, only underscores). Then convert that 'examine' file to a legacy markdown format file named `metadata.<object_name>.md` inside the object folder, following the template in `README.Format.Legacy.Markdown.md`. Then move the processed raw examine dump file from `legacy_examine_dumps/Incoming/` to `legacy_examine_dumps/Processed/`.
- Treat fenced `mud` blocks as **legacy** MARE/MUSE/MUSH-style softcode. Parse:
  - substitutions: `[ ... ]`, variables `%0-%9` / `v(0)-v(9)`
  - locks: `:/[ ... ]/` (lock failure prevents execution)
  - multi-command lines: `;` splits commands (unless inside `{ ... }`)
- If asked to **analyze**: Examine all `object_artifacts/Object.<Object_Name>/metadata.<object_name>.md` files that don't have a corresponding `analysis.<object_name>.md` file. For each attribute/program found in the **Attribute list** section, translate the attribute list legacy code to an English description of the logic for each attribute/program (include the original attribute name). Use the format described in `README.Format.English.Description.md`. Save the resulting english analysis output as a file named `analysis.<object_name>.md` inside the object folder.
- If asked to **convert**: Examine all `object_artifacts/Object.<Object_Name>/analysis.<object_name>.md` files that don't have a corresponding `converted.<object_name>.md` file. Using the `metadata.<object_name>.md` file, convert and output softcode into a file `converted.<object_name>.md`. Preserve behavior exactly as much as possible, using TinyMARE II syntax and conventions and taking account into any changes to the English description (`analysis.<object_name>.md`) that may have been editted by a programmer. Use the format described in `README.Format.Converted.Code.Format.md`.

## Common mechanical conversions (use these patterns)

- `@pemit %#=...` → `print ...` (no quotes).
- `@tr <obj>/<attr>[=<args>]` → `call <obj>/<attr>[=<args>]`.
- `@swi/@switch cond,{...},{...}` → structured `switch cond` with `case`, `default`, `break`, `endswitch`.
- `@wait N=...` → `wait N` then the block.
- `@foreach v(list)=...` → `for i__=v(list)` ... `done`.
- `$command` definitions: move them behind the lock and convert to `:/[lock]/N$command:` where `N` matches TinyMARE II command arg patterns (1/2/3).
- Rename attribute names containing `?` or `+` to `_` and update all references.
- Any attribute names that begin with a number should be prefixed with 'N_' and all references updated accordingly.

## Formatting expectations for converted snippets

- Use indentation for blocks; use `else`/`endif` (do not use `{}` for `if` blocks).
- No spaces around `=` and no spaces after commas in argument lists.
- If attribute flags are known, emit them explicitly: `@defattr <obj>/<attr>=<flags>` then `&<attr> <obj>=...`.
- If a new attribute to handle a dispatch or state is needed, define it with `@defattr <obj>/<newattr>=inherit program` before use.
- If a markdown object file has metadata with `Location: ...(#<id>R)`, start conversion with `@@ Move to location so next commands are targeted on the right object.`
`@teleport me=#<id>`.
- Separate converted attributes with: blank line, a line containing `@@@@@@@@ NEXT ATTRIBUTE @@@@@@@@`, blank line.


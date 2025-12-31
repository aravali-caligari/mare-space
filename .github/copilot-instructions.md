---
applyTo: "*.md,*.html,*.txt"
---

# mare-space: SpaceMARE softcode + conversions

This repo is documentation + softcode source control for the SpaceMARE simulation used in TinyMARE II. The *server/engine hardcode C code* lives in a separate repo (see the link in `README.md`).
This file describes how to handle legacy softcode parsing, analysis, and conversion tasks, including where to look for source material, how to interpret legacy code patterns, and how to format converted code.

## Where to look

- Ignore anything in the `backup of legacy softcode` folder. This is just legacy reference material and not to be used by the instructions below.
- `legacy_examine_dumps/`: Folders and files containing raw legacy softcode dumps (if any) used as sources for parsing. May contain multiple objects per file.
  - `incoming/`: Individual raw examine dumps as text files that may contain multiple objects per file.
  - `processed/`: The same raw examine dump files after they are parsed, and moved from `incoming/` to this folder.
- `object_artifacts/`: area to store artifacts like the parsed object metadata, english analysis descriptions, converted MARE2 softcode. Subfolders per object. Read `README.Template.Folder.File.Structure.md` for details.
- `README.legacy_MARE1_helptext.html`: legacy MARE1 command/function help.
- `README.TinyMARE.II.Helptext.Programming.html` - Authoritative MARE2/TinyMARE programming syntax. (`print`, `if/else/endif`, `switch/endswitch`, `call`, `wait`, `for ... done`, etc).
- `README.TinyMARE.II.Helptext.html` - General TinyMARE II helptext including commands and functions.
- `README.Format.Examine.md`: struture + example for the incoming object 'examine' structure before converting the object to legacy markdown format.
- `README.Format.Metadatamd`: template + example for legacy softcode dumps in markdown format
- `README.Format.Analysis.English.Description.md`: template + example for writing English logic descriptions when asked to 'Analyze' legacy softcode attribute lists.
- `README.Format.Converted.Code.md`: template + example for writing converted MARE2 code when asked to 'Convert' legacy softcode attribute lists.
- `README.Template.Folder.File.Structure.md`: recommended folder + file structure for the repo. Describes where to parse legacy code from, what folders to create, for the parsed objects, and where to place english analysis and converted code files.
- `README.Space.legacy.conversions.md`: SpaceMUSE → SpaceMARE naming/function conversions and data model changes.
- `README.Space.softcode.manual.md`: SpaceMARE-specific `@` commands and datatypes.
- `legacy.space.hardcode/`: legacy Space Sim C source files (reference only for understanding legacy space functions and commands used by softcode).

## How to handle softcode conversion tasks

- If asked to **parse**: Examine all text files inside the `legacy_examine_dumps/incoming/` folder. For each object found in the file, create a subfolder inside `object_artifacts/` named `object.<object_name>/` and create an `1-examine.<object_name>.txt` file inside it with the structure described in `README.Format.Examine.md`. Convert the object names to file names using traditional filename conventions (no spaces, no punctuation, lower-case, no special symbols, only underscores). Then convert that 'examine' file to a legacy markdown metadata format file named `2-metadata.<object_name>.md` inside the object folder, following the template in `README.Format.Metadata.md`.
- If asked to **analyze**: Examine all `object_artifacts/object.<object_name>/2-metadata.<object_name>.md` files that don't have a corresponding `3-analysis.<object_name>.md` file. For each attribute/program found in the **Attribute list** section, translate the attribute list legacy code to an English description of the logic for each attribute/program (include the original attribute name). Use the format described in `README.Format.English.Description.md`. Save the resulting english analysis output as a file named `3-analysis.<object_name>.md` inside the object folder.
- If asked to **convert**: Examine all `object_artifacts/object.<object_name>/3-analysis.<object_name>.md` files that don't have a corresponding `4-converted.<object_name>.md` file. Using the `2-metadata.<object_name>.md` file, convert and output softcode into a file `4-converted.<object_name>.md`. Preserve behavior exactly as much as possible, using TinyMARE II syntax and conventions and taking account into any changes to the English description (`3-analysis.<object_name>.md`) that may have been editted by a programmer. Use the format described in `README.Format.Converted.Code.Format.md`. Some attributes may be 'built-in' if they exist in the Attribute List section but are missing from the Attribute Definitions section. In that case, do not define them with `@defattr`.
- If asked to **review**: Examine all `object_artifacts/object.<object_name>/4-converted.<object_name>.md` files. Review the converted code for correctness, adherence to formatting expectations, and preservation of original behavior. Suggest improvements or corrections as needed.
- If asked to perform multiple steps, follow the steps in order: parse → analyze → convert → review, and only move files to processed folders or mark them as complete after all requested steps are done.

## Meaning of special terms

- **Legacy softcode**: Original MARE/MUSE-style softcode from the legacy Space Sim system, often using older syntax and conventions.
- **Converted MARE2 code**: Softcode that has been translated into TinyMARE II syntax and conventions, suitable for use in the MARE-Space simulation engine.
- **```mud** blocks**: Fenced code blocks in markdown files that contain legacy MARE/MUSE-style softcode or converted MARE2 code, depending on the context of the file they are in.

## Common mechanical conversions (use these patterns)

- substitutions: `[ ... ]`, variables `%0-%9` / `v(0)-v(9)`
- locks: `:/[ ... ]/` (lock failure prevents execution)
- multi-command lines: `;` splits commands (unless inside `{ ... }`)
- `@pemit %#=...` → `print ...` (no quotes).
- `@tr <obj>/<attr>[=<args>]` → `call <obj>/<attr>[=<args>]`.
- `@swi/@switch cond,{...},{...}` → structured `switch cond` with `case`, `default`, `break`, `endswitch`.
- `@wait N=...` → `wait N` then the block.
- `@foreach v(list)=...` → `for i__=v(list)` ... body with `set 0=v(i__)` ... `done`.
- `$command` definitions: Read `README.How.Command.Args.Work.md` for details on understanding and converting `$command` attributes with different argument patterns (`1$`, `2$`, `3$`), locks, player locks, and ignore unhandled signals.

## Formatting expectations for converted snippets

- Use indentation for blocks; use `else`/`endif` (do not use `{}` for `if` blocks).
- No spaces around `=` in code and no spaces after commas in argument lists.
- If attribute flags are known, emit them explicitly: `@defattr <obj>/<attr>=<flags>` then `&<attr> <obj>=...`.
- If an attribute definition exists but is missing from the Attribute List section, define it with `@defattr` with any converted code.
- If a new attribute to handle a dispatch or state is needed, define it with `@defattr <obj>/<newattr>=inherit program` before use.
- If a markdown object file has metadata with `Location: ...(#<id>R)`, start conversion with `@@ Move to location so next commands are targeted on the right object.`
`@teleport me=#<dbref>`.
- Preserve comments starting with `@@` and `---cut---` lines to separate attribute sections.

## Additional resources

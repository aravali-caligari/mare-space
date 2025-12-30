---
applyTo: "*.md"
---

# mare-space: SpaceMARE softcode + conversions

This repo is documentation + softcode source control for the SpaceMARE simulation used in TinyMARE II. The *server/engine C code* lives in a separate repo (see the link in `README.md`).

## Where to look

- Ignore anything in the `backup of legacy softcode`. This is just legacy reference material and not to be used by the instructions below.
- `legacy softcode/*.md`: per-object legacy softcode dumps (look for **Attribute Definitions** + **Attribute list** sections and fenced `mud` blocks).
- `legacy_examine_dumps/`: Folders and files containing raw legacy softcode dumps (if any) used as sources for parsing. May contain multiple objects per file.
  - `Incoming/`: Individual raw examine dumps as text files that may contain multiple objects per file.
  - `Processed/`: The same raw examine dump files after they are parsed, and moved from 'Incoming/' to this folder.
- `object_artifacts/`: area to store artifacts like the parsed object metadata, english analysis descriptions, converted MARE2 softcode. Subfolders per object. Read `README.Template.Folder.File.Structure.md` for details.
- `TinyMARE II Helptext - Programming.html` - Authoritative MARE2/TinyMARE programming syntax. (`print`, `if/else/endif`, `switch/endswitch`, `call`, `wait`, `for ... done`, etc).
- `TinyMARE II Helptext.html` - General TinyMARE II helptext including commands and functions.
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

- If asked to **parse**: Examine all text files inside the `legacy_examine_dumps/incoming/` folder. For each object found in the file, create a subfolder inside `object_artifacts/` named `object.<object_name>/` and create an `examine.<object_name>.txt` file inside it with the structure described in `README.Format.of.Examine.md`. Convert the object names to file names using traditional filename conventions (no spaces, no punctuation, lower-case, no special symbols, only underscores). Then convert that 'examine' file to a legacy markdown format file named `metadata.<object_name>.md` inside the object folder, following the template in `README.Format.Legacy.Markdown.md`. Then move the processed raw examine dump file from `legacy_examine_dumps/incoming/` to `legacy_examine_dumps/processed/` unless more steps were asked for.
- Treat fenced `mud` blocks as **legacy** MARE/MUSE/MUSH-style softcode. Parse:
  - substitutions: `[ ... ]`, variables `%0-%9` / `v(0)-v(9)`
  - locks: `:/[ ... ]/` (lock failure prevents execution)
  - multi-command lines: `;` splits commands (unless inside `{ ... }`)
- If asked to **analyze**: Examine all `object_artifacts/object.<object_name>/metadata.<object_name>.md` files that don't have a corresponding `analysis.<object_name>.md` file. For each attribute/program found in the **Attribute list** section, translate the attribute list legacy code to an English description of the logic for each attribute/program (include the original attribute name). Use the format described in `README.Format.English.Description.md`. Save the resulting english analysis output as a file named `analysis.<object_name>.md` inside the object folder.
- If asked to **convert**: Examine all `object_artifacts/object.<object_name>/analysis.<object_name>.md` files that don't have a corresponding `converted.<object_name>.md` file. Using the `metadata.<object_name>.md` file, convert and output softcode into a file `converted.<object_name>.md`. Preserve behavior exactly as much as possible, using TinyMARE II syntax and conventions and taking account into any changes to the English description (`analysis.<object_name>.md`) that may have been editted by a programmer. Use the format described in `README.Format.Converted.Code.Format.md`. Some attributes may be 'built-in' if they exist in the Attribute List section but are missing from the Attribute Definitions section. In that case, do not define them with `@defattr`.
- If asked to **review**: Examine all `object_artifacts/object.<object_name>/converted.<object_name>.md` files. Review the converted code for correctness, adherence to formatting expectations, and preservation of original behavior. Suggest improvements or corrections as needed.
- If asked to perform multiple steps, follow the steps in order: parse → analyze → convert → review, and only move files to processed folders or mark them as complete after all requested steps are done.

## Common mechanical conversions (use these patterns)

- `@pemit %#=...` → `print ...` (no quotes).
- `@tr <obj>/<attr>[=<args>]` → `call <obj>/<attr>[=<args>]`.
- `@swi/@switch cond,{...},{...}` → structured `switch cond` with `case`, `default`, `break`, `endswitch`.
- `@wait N=...` → `wait N` then the block.
- `@foreach v(list)=...` → `for i__=v(list)` ... `done`.
- `$command` definitions: move them behind the lock and convert to `:/[lock]/N$command:` where `N` matches TinyMARE II command arg patterns listed here:
  - 1=No or 1 args (e.g. `$command` or `$command *`)
  - 2=Two args in the pattern *=* (e.g. `$command *=*`)
  - 3=Three or more args in the pattern `*=*,*,...` (e.g. `$command *=*,*`) or it has extra static args before the first `*` (e.g. `$command static *=*`)
- Command definitions in TinyMARE II only support one static command word followed by args. Therefore:
- If a command definition has extra static args then define a new attribute to handle dispatching based on those subcommand static args.
  - e.g., `origattrib: $command static *=*` becomes a new dispatch attribute `&newattrib object=:3$command:<Dispatch switch code>` that checks the static args and calls the appropriate original attribute, passing along the remaining args.
  - Name the new dispatch attribute something meaningful related to the command being dispatched.
  - e.g. for `$airlock open *=*` and `$airlock close *=*`, create a new attribute `&airlock_control object=:3$airlock:<dispatch code>`. 
- Any attribute names that begin with a number should be prefixed with 'N_' and all references updated accordingly.
- Any attributes 

## Formatting expectations for converted snippets

- Use indentation for blocks; use `else`/`endif` (do not use `{}` for `if` blocks).
- No spaces around `=` and no spaces after commas in argument lists.
- If attribute flags are known, emit them explicitly: `@defattr <obj>/<attr>=<flags>` then `&<attr> <obj>=...`.
- If an attribute definition exists but is missing from the Attribute List section, define it with `@defattr` with any converted code.
- If a new attribute to handle a dispatch or state is needed, define it with `@defattr <obj>/<newattr>=inherit program` before use.
- If a markdown object file has metadata with `Location: ...(#<id>R)`, start conversion with `@@ Move to location so next commands are targeted on the right object.`
`@teleport me=#<id>`.
- Preserve comments starting with `@@` and `---cut---` lines to separate attribute sections.

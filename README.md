# mare-space softcode

TinyMARE II (MUD) Space-related softcode and documentation for the MARE-Space simulation engine used in MicroMARE.

## Contributors:

- Aravali / Carrie Gram 
- Ardhen
- Klynastor / Gandalf

## Repo Links

- [This Repo](https://github.com/aravali-caligari/mare-space)
- [TinyMARE II with MARE-Space engine / C Code](https://github.com/klynastor/tinymare2/tree/spacedev)

## Other links

## Description

Any softcode used in the operation of MARE-Space should be placed here to allow for source control and version tracking and easier updates.

The softcode runs inside a TinyMARE II server running and integrated with the MARE-Space simulation engine.

For legacy softcode analysis/conversion guidelines, see `.github/copilot-instructions.md`.

## Folder structure

- `backup of legacy softcode/` - (BECOMING OBSOLETE SOON) Per-object legacy softcode dumps (Markdown) used as conversion/reference sources.

- `legacy_examine_dumps/` - Text files containing raw legacy softcode dumps (if any) used as sources for parsing. May contain multiple objects per file.
- `object_artifacts/` - Parsed objects from the legacy examine dumps, with subfolders per object containing:
  - `examine.<object_name>.txt` - Incoming object 'examine' structure before converting the object to legacy markdown format.
  - `metadata.<object_name>.md` - Legacy object in metadata markdown format.
  - `analysis.<object_name>.md` - English logic description of the legacy attribute list.
  - `converted.<object_name>.md` - Converted MARE2 code.

- `.github/` - Repo automation + AI agent instructions.

- `legacyspacesim/` - Legacy Space Sim C sources (reference only for understanding legacy space functions and commands used by softcode).

- `README.*.md` - Various documentation, templates, and examples.

- `TinyMARE II Helptext - Programming.html` - Authoritative MARE2/TinyMARE programming syntax.
- `TinyMARE II Helptext.html` - General TinyMARE II helptext including commands and functions.
- `README.softcode.manual.md` - SpaceMARE-specific `@` commands and datatypes.
- `legacy_MARE_helptext.html` - Legacy MARE I command/function help.
- `README.legacy.conversions.md` - SpaceMUSE → SpaceMARE naming/function conversions and data model changes.
- `README.Template.Folder.File.Structure.md` - Recommended folder + file structure for the repo. Describes where to parse legacy code from, what folders to create, for the parsed objects, and where to place english analysis and converted code files.
- `README.Format.of.Examine.md` - Struture + example for the incoming object 'examine' structure before converting the object to legacy markdown format.
- `README.Format.Legacy.Markdown.md` - Template + example for legacy softcode dumps in markdown format.
- `README.Format.English.Description.md` - Template + example for writing English logic descriptions when asked to 'Analyze' legacy softcode attribute lists.
- `README.Format.Converted.Code.Format.md` - Template + example for writing converted MARE2 code when asked to 'Convert' legacy softcode attribute lists.

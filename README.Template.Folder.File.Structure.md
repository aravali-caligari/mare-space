# Structure of folders and files for incoming and outgoing files in the mare-space repo for parsing, analysis, and conversion

## Recommended folder + file structure

- `legacy_examine_dumps/`
  - `incoming/`: Folder for incoming files containing raw legacy softcode dumps (if any) used as sources for parsing. May contain multiple objects per file.
    - `<legacy_dump_file_1>.txt`
    - `<legacy_dump_file_2>.txt`
    - ... more legacy examine dump files ...
  - `processed/`: Folder for the same raw examine dump files after it has completed all steps, including 'review', and moved from `incoming/` to this folder.
    - `<legacy_dump_file_1>.txt`
    - `<legacy_dump_file_2>.txt`
    - ... more processed legacy examine dump files ...

- `object_artifacts/`: Folder for parsed objects from the legacy examine dumps.
  - `object.<Object_Name>/`: folder for each object being converted
    - `1-examine.<object_name>.txt`: incoming object 'examine' structure before converting the object to legacy markdown format (see `README.Format.of.Examine.md` for structure + example)
    - `2-metadata.<object_name>.md`: legacy object in metadata markdown format (see `README.Format.Legacy.Markdown.md` for template + example)
    - `3-analysis.<object_name>.md`: English logic description of the legacy attribute list (see `README.Format.English.Description.md` for template + example)
    - `4-converted.<object_name>.md`: converted MARE2 code (see `README.Format.Converted.Code.Format.md` for template + example)
  - ... more objects ...

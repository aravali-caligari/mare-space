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
  - `dbobj.<Object_Name>.<id>/`: folder for each object being converted
    - `1-examine.<object_name>.<id>.txt`: incoming object 'examine' structure before converting the object to legacy markdown format (see `README.Format.Examine.md` for structure + example)
    - `2-metadata.<object_name>.<id>.md`: legacy object in metadata markdown format (see `README.Format.Metadata.md` for template + example)
    - `3-analysis.<object_name>.<id>.md`: English logic description of the legacy attribute list (see `README.Format.Analysis.English.Description.md` for template + example)
    - `4-converted.<object_name>.<id>.md`: converted MARE2 code (see `README.Format.Converted.Code.md` for template + example)
    - `5-review.<object_name>.<id>.md`: review comments on the converted code (if any)
  - ... more objects ...

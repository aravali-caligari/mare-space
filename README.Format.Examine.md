# Purpose of this README: Shows an example of 'examine' output from MARE before its converted to Legacy Markdown format

Some attributes may be 'built-in' and missing from the Attribute definitions section but still present in the Attribute list.
Attribute names and attribute values must be on a single line each.
Any multi-line attribute values in the raw dump must be joined with spaces so each attribute value becomes a single line.

## Example of the 'examine' output structure follows here

```
<Object Name>(#<dbref>)
Type: <type>
Owner: <owner>
Flags: <flags>
Parents: <parent objects>
Modified: <date stamp>
... more attributes shown in examine output ...
Attribute definitions:
  <attribute name>: <attribute flags>
  <attribute name without flags>
  ... more attributes ...
Attribute list:
<attribute name>:<attribute value on a single line>
Location: <location object>
Home: <home object>
```

## Example of an output 'examine' file

```mud
Cloak Parent(#54808h)
Owner: Ptah
Type: Thing  Flags: Haven
Bytes: 1500
Plane: 0
Created: Sun Nov 27 05:53:55 1994
Modified: Sun Dec 11 18:01:51 1994
Attribute definitions:
  cloakhelp: inherit program
  passkey
  set_passkey1: inherit program
  set_passkey2: inherit program
  cloak_on: inherit program
  cloak_off: inherit program
Attribute list:
cloak_on:$cloak on passkey=*:/[v(eng_man)]/@swi [get(s([v(us)]/vismult))]=-1,{@pemit %#=Cloaking device already on.},{@swi [v(passkey)]=00[v(0)],{@vismult [v(us)]=-1;@emit Cloaking device engaged.},{@pemit %#=Invalid cloak passkey.}}
set_passkey1:$cloak passkey *=*:/[v(eng_man)]/@swi [v(passkey)]=00[v(0)],{@passkey me=00[v(1)];@pemit %#=Cloaking device passkey - Set.},{@pemit %#=Cloaking device passkey - Invalid.}
cloakhelp:$cloakhelp:/[v(eng_man)]/@pemit %#=CLOAK ON PASSKEY=<passkey> : Activates the cloaking device.;@pemit %#=INITIAL  PASSKEY=<passkey> : Set the initial cloaking device passkey.;@pemit %#=CLOAK PASSKEY <old passkey>=<new passkey> : Changes the passkey.;@pemit %#=CLOAK OFF : Turns the cloaking device off.;@pemit %#=WARNING: The cloaking device will consume power faster than the ship can produce it. If allowed to remain on it will drain the Life Support of its power and kill everyone on board.
Location: PCS Equipment Room(#50723R)
Home: Helm Equipment Room(#11848R)
```

## Example of a dump file that incorrectly includes multi-line attribute values

```mud
Cloak Parent(#54808h)
Owner: Ptah
Type: Thing  Flags: Haven
Bytes: 1500
Plane: 0
Created: Sun Nov 27 05:53:55 1994
Modified: Sun Dec 11 18:01:51 1994
Attribute definitions:
  passkey
  set_passkey1: inherit program
  set_passkey2: inherit program
Attribute list:
set_passkey1:$cloak passkey *=*:/[v(eng_man)]/@swi [v(passkey)]=00[v(0)],{@passkey me=00[v(1)];@pemit %#=Cloaking device passkey - Set.},{@pemit 
%#=Cloaking device passkey - Invalid.};@wait 1=print This is a
multi-line
set_passkey1:print This is the next single line.
```

## Example with the multi-line attribute values being joined into single-lines

```mud
Cloak Parent(#54808h)
Owner: Ptah
Type: Thing  Flags: Haven
Bytes: 1500
Plane: 0
Created: Sun Nov 27 05:53:55 1994
Modified: Sun Dec 11 18:01:51 1994
Attribute definitions:
  passkey
  set_passkey1: inherit program
Attribute list:
set_passkey1:$cloak passkey *=*:/[v(eng_man)]/@swi [v(passkey)]=00[v(0)],{@passkey me=00[v(1)];@pemit %#=Cloaking device passkey - Set.},{@pemit %#=Cloaking device passkey - Invalid.};@wait 1=print This was a multi-line
set_passkey1:print This is the next single line.
```

## End of 'examine' output example

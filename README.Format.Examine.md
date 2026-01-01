# Purpose of this README: Shows an example of 'examine' output from MARE before its converted to Legacy Markdown format

Some attributes may be 'built-in' and missing from the Attribute definitions section but still present in the Attribute list.

#
# Example of the 'examine' output structure follows here
#

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

# 
# Example of a completed 'examine' output from MARE before its converted to Legacy Markdown format follows here
#

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
cloak_on:$cloak on passkey=*:/[v(eng_man)]/@swi
[get(s([v(us)]/vismult))]=-1,{@pemit %#=Cloaking device already on.},{@swi [v(passkey)]=00[v(0)],{@vismult [v(us)]=-1;@emit Cloaking device engaged.},{@pemit %#=Invalid cloak passkey.}}
set_passkey1:$cloak passkey *=*:/[v(eng_man)]/@swi [v(passkey)]=00[v(0)],{@passkey me=00[v(1)];@pemit %#=Cloaking device passkey - Set.},{@pemit %#=Cloaking device passkey - Invalid.}
set_passkey2:$initial passkey=*:/[v(eng_man)]/@swi [v(passkey)]=,{@passkey me=00[v(0)];@pemit %#=Cloaking device passkey - Set.},{@pemit %#=Cloaking device passkey - Invalid.}
cloak_off:$cloak off:/[v(eng_man)]/@swi [get(s([v(us)]/vismult))]=1,{@pemit %#=Cloaking device already off.},{@vismult [v(us)]=1;@emit Cloaking device disengaged.}
cloakhelp:$cloakhelp:/[v(eng_man)]/@pemit %#=CLOAK ON PASSKEY=<passkey> : Activates the cloaking device.;@pemit %#=INITIAL  PASSKEY=<passkey> : Set the initial cloaking device passkey.;@pemit %#=CLOAK PASSKEY <old passkey>=<new passkey> : Changes the passkey.;@pemit %#=CLOAK OFF : Turns the cloaking device off.;@pemit %#=WARNING: The cloaking device will consume power faster than the ship can produce it. If allowed to remain on it will drain the Life Support of its power and kill everyone on board.
Location: PCS Equipment Room(#50723R)
Home: Helm Equipment Room(#11848R)

--- 
## Example of 'examine' output that incorrectly includes multi-line attribute values (this is NOT the expected format). Change newlines to spaces to convert to single-line values in the 'examine' output file

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
cloak_on:$cloak on passkey=*:/[v(eng_man)]/@swi
[get(s([v(us)]/vismult))]=-1,{@pemit %#=Cloaking device
already on.},{@swi [v(passkey)]=00[v(0)],{@vismult [v(us)]=-1;@emit
Cloaking device engaged.},{@pemit %#=Invalid cloak passkey.}}
set_passkey1:$cloak passkey *=*:/[v(eng_man)]/@swi [v(passkey)]=00[v(0)],{@passkey me=00[v(1)];@pemit %#=Cloaking device passkey - Set.},{@pemit 
%#=Cloaking device passkey - Invalid.}
set_passkey2:$initial passkey=*:/[v(eng_man)]/print reached here

---
# End of 'examine' output example
#
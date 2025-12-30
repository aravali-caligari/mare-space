# Cloak Parent

## Name

Cloak Parent - Cloaking Device Console

## Purpose

This is the Cloaking Device console object, used in the game to provide players with the ability to cloak their spacecraft. It allows players to activate and deactivate the cloaking device, as well as manage passkeys for security.

## Meta data

```mud
Cloak Parent(#54808h)
Type:	Thing
Owner:	Ptah
Flags:	Halted
Bytes:	2440
Children:	5
Created:	Sun Nov 27 05:53:55 1994
Modified:	Sun Dec 28 02:44:00 2025
Location:	Helm Equipment Room(#11848R)
Home:	Helm Equipment Room(#11848R)
```

## Object Definition

### Attribute definitions

```mud
cloakhelp: inherit program
passkey: 
set_passkey1: inherit program
set_passkey2: inherit program
cloak_on: inherit program
cloak_off: inherit program
```

### Attribute list

```mud
&cloak_on cloak parent=$cloak on passkey=*:/[v(eng_man)]/@swi [get(s([v(us)]/vismult))]=-1,{@pemit %#=Cloaking device already on.},{@swi [v(passkey)]=00[v(0)],{@vismult [v(us)]=-1;@emit Cloaking device engaged.},{@pemit %#=Invalid cloak passkey.}}
&set_passkey1 cloak parent=$cloak change passkey=*:/[v(eng_man)]/@swi [v(passkey)]=00[v(0)],{@passkey me=00[v(1)];@pemit %#=Cloaking device passkey - Set.},{@pemit %#=Cloaking device passkey - Invalid.}
&set_passkey2 cloak parent=$cloak set passkey=*:/[v(eng_man)]/@swi [v(passkey)]=,{@passkey me=00[v(0)];@pemit %#=Cloaking device passkey - Set.},{@pemit %#=Cloaking device passkey - Invalid.}
&cloak_off cloak parent=$cloak off:/[v(eng_man)]/@swi [get(s([v(us)]/vismult))]=1,{@pemit %#=Cloaking device already off.},{@vismult [v(us)]=1;@emit Cloaking device disengaged.}
&cloakhelp cloak parent=$cloak help:/[v(eng_man)]/@pemit %#=CLOAK ON PASSKEY=<passkey> : Activates the cloaking device.;@pemit %#=CLOAK SET PASSKEY=<passkey> : Set the initial cloaking device passkey.;@pemit %#=CLOAK CHANGE PASSKEY=<old passkey>,<new passkey> : Changes the passkey.;@pemit %#=CLOAK OFF : Turns the cloaking device off.;@pemit %#=WARNING: The cloaking device will consume power faster than the ship can produce it. If allowed to remain on it will drain the Life Support of its power and kill everyone on board.
```


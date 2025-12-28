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

## Attribute list (English description)

```markdown
<!-- filepath: /home/bivansc/spacesim/github.com/aravali-caligari/mare-space/legacy softcode/Cloak Parent.md -->
### &cloak_on
- Player command: `cloak on passkey=<passkey>` (locked to `v(eng_man)`).
- Checks whether the ship is already cloaked by reading the ship’s visibility multiplier (`get(s([v(us)]/vismult))`):
  - If `-1`, prints “Cloaking device already on.”
  - Otherwise validates the provided passkey by comparing `v(passkey)` to `00<enteredPasskey>`.
    - If valid: sets ship `vismult` to `-1` (cloak engaged) and emits “Cloaking device engaged.”
    - If invalid: prints “Invalid cloak passkey.”

### &set_passkey1
- Player command: `cloak change passkey=<old>,<new>` (locked to `v(eng_man)`).
- Verifies the old passkey matches the stored passkey (stored format is `00<passkey>`):
  - If match: sets `me/passkey` to `00<new>` and prints “Cloaking device passkey - Set.”
  - If not: prints “Cloaking device passkey - Invalid.”

### &set_passkey2
- Player command: `cloak set passkey=<passkey>` (locked to `v(eng_man)`).
- Only allows initial passkey setup when no passkey is currently set (`v(passkey)` is empty):
  - If empty: sets `me/passkey` to `00<passkey>` and prints “Cloaking device passkey - Set.”
  - Else: prints “Cloaking device passkey - Invalid.” (refuses overwrite via this path).

### &cloak_off
- Player command: `cloak off` (locked to `v(eng_man)`).
- Checks whether the ship is already uncloaked (`get(s([v(us)]/vismult))=1`):
  - If `1`, prints “Cloaking device already off.”
  - Otherwise: sets ship `vismult` to `1` (cloak disengaged) and emits “Cloaking device disengaged.”

### &cloakhelp
- Player command: `cloak help` (locked to `v(eng_man)`).
- Prints usage for cloak commands and a warning that leaving the cloak on will drain power/life support.
````

## Attribute list (MARE2 conversion)

```mud
@@ Converted from legacy Attribute list to MARE2 style.
@teleport me=#11848

@defattr Cloak Parent/cloak_combined=inherit program
&cloak_combined Cloak Parent=:/[v(eng_man)]/3$cloak:
@@ Route: cloak on passkey=<x>, cloak off, cloak help, cloak set passkey=<x>, cloak change passkey=<old>,<new>
switch v(0)
  case on passkey
    call me/cloak_on=v(1)
    break
  case off
    call me/cloak_off
    break
  case help
    call me/cloakhelp
    break
  case set passkey
    call me/set_passkey2=v(1)
    break
  case change passkey
    call me/set_passkey1=v(1),v(2)
    break
  default
    print Invalid cloak command. Use: cloak help
endswitch
exit

@@@@@@@@

@defattr Cloak Parent/cloak_on=inherit program
&cloak_on Cloak Parent=
@@ v(0)=entered passkey
if get(v(us),vismult)=-1
  print Cloaking device already on.
  exit
endif

if get(v(me),passkey)=00[v(0)]
  @vismult v(us)=-1
  @emit Cloaking device engaged.
else
  print Invalid cloak passkey.
endif

@@@@@@@@

@defattr Cloak Parent/set_passkey1=inherit program
&set_passkey1 Cloak Parent=
@@ v(0)=old passkey,v(1)=new passkey
if get(v(me),passkey)=00[v(0)]
  @passkey me=00[v(1)]
  print Cloaking device passkey - Set.
else
  print Cloaking device passkey - Invalid.
endif

@@@@@@@@

@defattr Cloak Parent/set_passkey2=inherit program
&set_passkey2 Cloak Parent=
@@ v(0)=initial passkey
if get(v(me),passkey)=
  @passkey me=00[v(0)]
  print Cloaking device passkey - Set.
else
  print Cloaking device passkey - Invalid.
endif

@@@@@@@@

@defattr Cloak Parent/cloak_off=inherit program
&cloak_off Cloak Parent=
if get(v(us),vismult)=1
  print Cloaking device already off.
  exit
endif

@vismult v(us)=1
@emit Cloaking device disengaged.

@@@@@@@@

@defattr Cloak Parent/cloakhelp=inherit program
&cloakhelp Cloak Parent=
print CLOAK ON PASSKEY=<passkey> : Activates the cloaking device.
print CLOAK SET PASSKEY=<passkey> : Set the initial cloaking device passkey.
print CLOAK CHANGE PASSKEY=<old passkey>,<new passkey> : Changes the passkey.
print CLOAK OFF : Turns the cloaking device off.
print WARNING: The cloaking device will consume power faster than the ship can produce it. If allowed to remain on it will drain the Life Support of its power and kill everyone on board.

@@@@@@@@

@defattr Cloak Parent/passkey=program
&passkey Cloak Parent=@@ storage attribute (value like 00<passkey>)
```





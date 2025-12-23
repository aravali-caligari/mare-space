# Cloak Parent

## Name

Cloak Parent - Cloaking Device Console

## Purpose

This is the Cloaking Device console object, used in the game to provide players with the ability to cloak their spacecraft. It allows players to activate and deactivate the cloaking device, as well as manage passkeys for security.

## Meta data

## Object Definition

### Attribute definitions

```mud
cloakhelp: inherit program
passkey: program
set_passkey1: inherit program
set_passkey2: inherit program
cloak_on: inherit program
cloak_off: inherit program
```

### Attribute list

```mud
cloak_on:	$cloak on passkey=*:/[v(eng_man)]/@swi [get(s([v(us)]/vismult))]=-1,{@pemit %#=Cloaking device already on.},{@swi [v(passkey)]=00[v(0)],{@vismult [v(us)]=-1;@emit Cloaking device engaged.},{@pemit %#=Invalid cloak passkey.}}
set_passkey1:	$cloak passkey *=*:/[v(eng_man)]/@swi [v(passkey)]=00[v(0)],{@passkey me=00[v(1)];@pemit %#=Cloaking device passkey - Set.},{@pemit %#=Cloaking device passkey - Invalid.}
set_passkey2:	$initial passkey=*:/[v(eng_man)]/@swi [v(passkey)]=,{@passkey me=00[v(0)];@pemit %#=Cloaking device passkey - Set.},{@pemit %#=Cloaking device passkey - Invalid.}
cloak_off:	$cloak off:/[v(eng_man)]/@swi [get(s([v(us)]/vismult))]=1,{@pemit %#=Cloaking device already off.},{@vismult [v(us)]=1;@emit Cloaking device disengaged.}
cloakhelp:	$cloakhelp:/[v(eng_man)]/@pemit %#=CLOAK ON PASSKEY=<passkey> : Activates the cloaking device.;@pemit %#=INITIAL PASSKEY=<passkey> : Set the initial cloaking device passkey.;@pemit %#=CLOAK PASSKEY <old passkey>=<new passkey> : Changes the passkey.;@pemit %#=CLOAK OFF : Turns the cloaking device off.;@pemit %#=WARNING: The cloaking device will consume power faster than the ship can produce it. If allowed to remain on it will drain the Life Support of its power and kill everyone on board.
```

## Logic Descriptions

### cloak_on attribute on the Cloak Parent.md file that refers to the logic to activate the spacecraft's cloaking device.


**Command Pattern:** `cloak on passkey=<passkey>`

**Access Control:** Requires a person object reference that is 'manning' the engineering console.( eng_man lock)

**Logic Flow:**
1. Check if the spacecraft's visibility multiplier (vismult) is already set to -1 (cloaked state)
   - If already -1: Send message to player "Cloaking device already on."
   - If not -1: Proceed to passkey validation
2. Validate the provided passkey by comparing it with the stored passkey (prepended with "00")
   - If passkey matches:
     - Set the spacecraft's visibility multiplier to -1 (engage cloaking)
     - Emit message to all in location "Cloaking device engaged."
   - If passkey does not match:
     - Send message to player "Invalid cloak passkey."

**References:**
- `v(us)` - The spacecraft object associated with this console
- `v(eng_man)` - Engineering console attribute with the object reference to the person or object manning the engineering console.
- `v(passkey)` - Stored passkey attribute on this console
- `v(0)` or `%0` - First parameter (the passkey entered by player)

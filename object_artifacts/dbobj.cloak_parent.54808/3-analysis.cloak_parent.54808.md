# `Cloak Parent`

## English Logic Descriptions (Legacy Attribute List)

## OBJECT: `Cloak Parent`

### ATTRIBUTE: `cloak_on` — English description

```text
Object: Cloak Parent
Attribute: cloak_on

Purpose:
- Implements the “cloak on” command with a required passkey.
- If valid, enables cloaking on the current ship (v(us)) and emits a confirmation.

Inputs (by usage):
- v(us): the ship whose cloak state is being controlled.
- v(0): the passkey argument provided by the user.
- v(passkey): stored passkey on this object (expected to be prefixed with 00).
- v(eng_man): lock expression gate for engineering management permissions.

Logic:
- Enforces a permission lock via :/[v(eng_man)]/.
- Switches on get(s(v(us)/vismult)):
  - If -1: cloaking already on → notify user.
  - Else:
    - Switches on whether v(passkey) matches 00 + v(0).
      - If match: sets v(us) vismult to -1 and emits “Cloaking device engaged.”
      - Else: notify user the passkey is invalid.

Side effects:
- Modifies v(us)/vismult.
- Emits to the environment.
```

```mud
original
cloak_on:$cloak on passkey=*:/[v(eng_man)]/@swi [get(s([v(us)]/vismult))]=-1,{@pemit %#=Cloaking device already on.},{@swi [v(passkey)]=00[v(0)],{@vismult [v(us)]=-1;@emit Cloaking device engaged.},{@pemit %#=Invalid cloak passkey.}}
```

### ATTRIBUTE: `set_passkey1` — English description

```text
Object: Cloak Parent
Attribute: set_passkey1

Purpose:
- Changes the cloaking device passkey, requiring the current (old) passkey.

Inputs (by usage):
- v(0): old passkey provided by user.
- v(1): new passkey provided by user.
- v(passkey): stored passkey on this object.
- v(eng_man): lock expression gate for engineering management permissions.

Logic:
- Enforces a permission lock via :/[v(eng_man)]/.
- Verifies the stored passkey equals 00 + v(0).
  - If valid: sets this object’s passkey to 00 + v(1) and notifies user.
  - Else: notifies user the old passkey was invalid.

Side effects:
- Modifies this object’s passkey.
```

```mud
original
set_passkey1:$cloak passkey *=*:/[v(eng_man)]/@swi [v(passkey)]=00[v(0)],{@passkey me=00[v(1)];@pemit %#=Cloaking device passkey - Set.},{@pemit %#=Cloaking device passkey - Invalid.}
```

### ATTRIBUTE: `set_passkey2` — English description

```text
Object: Cloak Parent
Attribute: set_passkey2

Purpose:
- Sets the initial cloaking passkey when none is currently set.

Inputs (by usage):
- v(0): initial passkey provided by user.
- v(passkey): stored passkey on this object.
- v(eng_man): lock expression gate for engineering management permissions.

Logic:
- Enforces a permission lock via :/[v(eng_man)]/.
- Checks whether v(passkey) is empty.
  - If empty: sets passkey to 00 + v(0) and notifies user.
  - Else: rejects the change as invalid.

Side effects:
- Modifies this object’s passkey (only when it was blank).
```

```mud
original
set_passkey2:$initial passkey=*:/[v(eng_man)]/@swi [v(passkey)]=,{@passkey me=00[v(0)];@pemit %#=Cloaking device passkey - Set.},{@pemit %#=Cloaking device passkey - Invalid.}
```

### ATTRIBUTE: `cloak_off` — English description

```text
Object: Cloak Parent
Attribute: cloak_off

Purpose:
- Implements the “cloak off” command.

Inputs (by usage):
- v(us): the ship whose cloak state is being controlled.
- v(eng_man): lock expression gate for engineering management permissions.

Logic:
- Enforces a permission lock via :/[v(eng_man)]/.
- Switches on get(s(v(us)/vismult)):
  - If 1: cloaking already off → notify user.
  - Else: sets v(us) vismult to 1 and emits “Cloaking device disengaged.”

Side effects:
- Modifies v(us)/vismult.
- Emits to the environment.
```

```mud
original
cloak_off:$cloak off:/[v(eng_man)]/@swi [get(s([v(us)]/vismult))]=1,{@pemit %#=Cloaking device already off.},{@vismult [v(us)]=1;@emit Cloaking device disengaged.}
```

### ATTRIBUTE: `cloakhelp` — English description

```text
Object: Cloak Parent
Attribute: cloakhelp

Purpose:
- Prints usage help for cloak-related commands.

Inputs (by usage):
- v(eng_man): lock expression gate for engineering management permissions.

Logic:
- Enforces a permission lock via :/[v(eng_man)]/.
- Prints several help lines describing supported cloak commands.
- Includes a warning about increased power consumption.

Side effects:
- User-visible output only.
```

```mud
original
cloakhelp:$cloakhelp:/[v(eng_man)]/@pemit %#=CLOAK ON PASSKEY=<passkey> : Activates the cloaking device.;@pemit %#=INITIAL PASSKEY=<passkey> : Set the initial cloaking device passkey.;@pemit %#=CLOAK PASSKEY <old passkey>=<new passkey> : Changes the passkey.;@pemit %#=CLOAK OFF : Turns the cloaking device off.;@pemit %#=WARNING: The cloaking device will consume power faster than the ship can produce it. If allowed to remain on it will drain the Life Support of its power and kill everyone on board.
```

# `Cloak Parent`

## English Logic Descriptions (Legacy Attribute List)

## OBJECT: `Cloak Parent`

### ATTRIBUTE: `cloak_on` — English description

```text
Object: Cloak Parent
Attribute: cloak_on

Purpose:
- Implements the “cloak on” command.
- If already cloaked, informs the actor.
- Otherwise validates a passkey and enables cloaking by setting the ship’s visibility multiplier to -1.

Inputs (by usage):
- v(0): passkey provided by the player.
- v(us): the current ship (or ship context for this console).
- v(passkey): stored cloaking device passkey (attribute on this console).
- get(s([v(us)]/vismult)): current visibility multiplier.

Logic:
- Checks whether the ship’s vismult is already -1.
  - If yes: tells the actor “Cloaking device already on.”
  - Else: compares stored passkey to "00" + the provided passkey.
    - If match: sets ship vismult to -1 and emits “Cloaking device engaged.”
    - Else: tells the actor “Invalid cloak passkey.”
```

### ATTRIBUTE: `set_passkey1` — English description

```text
Object: Cloak Parent
Attribute: set_passkey1

Purpose:
- Implements the “change passkey” command.
- Validates the current passkey, then updates it to a new passkey.

Inputs (by usage):
- v(0): old passkey provided by the player.
- v(1): new passkey provided by the player.
- v(passkey): stored passkey attribute.

Logic:
- Compares stored passkey to "00" + v(0).
  - If match: sets passkey attribute to "00" + v(1) and tells actor “Cloaking device passkey - Set.”
  - Else: tells actor “Cloaking device passkey - Invalid.”
```

### ATTRIBUTE: `set_passkey2` — English description

```text
Object: Cloak Parent
Attribute: set_passkey2

Purpose:
- Implements the “initial passkey” command.
- Allows setting the passkey only if it is currently blank.

Inputs (by usage):
- v(0): new passkey provided by the player.
- v(passkey): stored passkey attribute.

Logic:
- If the stored passkey is blank:
  - Sets passkey to "00" + v(0) and tells actor “Cloaking device passkey - Set.”
- Else:
  - Tells actor “Cloaking device passkey - Invalid.”
```

### ATTRIBUTE: `cloak_off` — English description

```text
Object: Cloak Parent
Attribute: cloak_off

Purpose:
- Implements the “cloak off” command.
- If already uncloaked, informs the actor.
- Otherwise disables cloaking by setting ship vismult to 1.

Inputs (by usage):
- v(us): the current ship context.
- get(s([v(us)]/vismult)): current visibility multiplier.

Logic:
- If ship vismult is 1:
  - Tells actor “Cloaking device already off.”
- Else:
  - Sets ship vismult to 1 and emits “Cloaking device disengaged.”
```

### ATTRIBUTE: `cloakhelp` — English description

```text
Object: Cloak Parent
Attribute: cloakhelp

Purpose:
- Displays help text describing available cloak commands and warnings.

Inputs (by usage):
- None.

Logic:
- Prints several help lines to the actor describing:
  - CLOAK ON PASSKEY=<passkey>
  - INITIAL PASSKEY=<passkey>
  - CLOAK PASSKEY <old passkey>=<new passkey>
  - CLOAK OFF
  - Warning about high power consumption.
```

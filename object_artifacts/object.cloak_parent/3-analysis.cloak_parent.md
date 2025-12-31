# `Cloak Parent`

## English Logic Descriptions (Legacy Attribute List)

## OBJECT: `Cloak Parent`

### ATTRIBUTE: `cloak_on` — English description

```text
Object: Cloak Parent
Attribute: cloak_on

Purpose:
- Implements the `$cloak on passkey=*` command.
- Validates that the cloak is currently off, then validates the passkey, then enables cloaking.

Inputs:
- v(us): the ship running the cloak logic (context object)
- v(0): passkey argument provided by the player
- v(passkey): stored passkey value
- get(s([v(us)]/vismult)): current visibility multiplier/state

Logic:
- Enforces an engineering/management lock via `:/[v(eng_man)]/`.
- Switches on the ship’s `vismult`:
  - If it is `-1` (already cloaked): notify the caller that it is already on.
  - Otherwise: switch on passkey equality:
    - If stored passkey matches `00` + the provided passkey: set `vismult` to `-1`, emit “engaged”.
    - Else: notify the caller that the passkey is invalid.
```

### ATTRIBUTE: `set_passkey1` — English description

```text
Object: Cloak Parent
Attribute: set_passkey1

Purpose:
- Implements the `$cloak passkey *=*` command.
- Changes the cloaking device passkey if the old passkey matches.

Inputs:
- v(0): old passkey argument
- v(1): new passkey argument
- v(passkey): stored passkey

Logic:
- Enforces an engineering/management lock via `:/[v(eng_man)]/`.
- Switches on whether the stored passkey matches `00` + v(0):
  - If it matches: sets passkey to `00` + v(1) and informs the caller.
  - Else: informs the caller that the old passkey was invalid.
```

### ATTRIBUTE: `set_passkey2` — English description

```text
Object: Cloak Parent
Attribute: set_passkey2

Purpose:
- Implements the `$initial passkey=*` command.
- Sets the initial passkey only if the passkey is currently unset/empty.

Inputs:
- v(0): new passkey argument
- v(passkey): stored passkey

Logic:
- Enforces an engineering/management lock via `:/[v(eng_man)]/`.
- Switches on whether `v(passkey)` is empty:
  - If empty: sets passkey to `00` + v(0) and informs the caller.
  - Else: informs the caller that the passkey change is invalid.
```

### ATTRIBUTE: `cloak_off` — English description

```text
Object: Cloak Parent
Attribute: cloak_off

Purpose:
- Implements the `$cloak off` command.
- Validates that the cloak is currently on, then disables cloaking.

Inputs:
- v(us): the ship
- get(s([v(us)]/vismult)): visibility multiplier/state

Logic:
- Enforces an engineering/management lock via `:/[v(eng_man)]/`.
- Switches on the ship’s `vismult`:
  - If it is `1` (already uncloaked): notify the caller it is already off.
  - Otherwise: sets `vismult` to `1` and emits “disengaged”.
```

### ATTRIBUTE: `cloakhelp` — English description

```text
Object: Cloak Parent
Attribute: cloakhelp

Purpose:
- Implements the `$cloakhelp` command.
- Prints usage help and a warning about power drain.

Inputs:
- None.

Logic:
- Enforces an engineering/management lock via `:/[v(eng_man)]/`.
- Sends several help lines to the caller, describing:
  - how to turn cloak on
  - how to set initial passkey
  - how to change passkey
  - how to turn cloak off
  - a warning about power consumption draining life support
```

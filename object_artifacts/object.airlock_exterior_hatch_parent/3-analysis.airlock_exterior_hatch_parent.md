# `Airlock Exterior Hatch Parent`

## English Logic Descriptions (Legacy Attribute List)

## OBJECT: `Airlock Exterior Hatch Parent`

### ATTRIBUTE: `OLook` — English description

```text
Object: Airlock Exterior Hatch Parent
Attribute: OLook

Purpose:
- Provides the “other look” text when someone looks out the airlock hatch porthole.

Inputs (by usage):
- None.

Logic:
- Returns a fixed short description: "looks out the exterior airlock hatch porthole.".
```

### ATTRIBUTE: `OnFail` — English description

```text
Object: Airlock Exterior Hatch Parent
Attribute: OnFail

Purpose:
- Handles a failed “use/open” attempt on the airlock hatch.
- If the airlock is sealed, notifies the helm and informs the actor.
- If the airlock is unsealed, cycles the actor out through the airlock, and if conditions indicate space egress, also “launches suit” (space state setup).

Inputs (by usage):
- %#: the actor attempting to open/use the hatch.
- link(me): the ship/body object this hatch is linked to.
- get([link(me)]/airlock): airlock state indicator.
- get([link(me)]/helm): helm object reference.

Logic:
- Switches on the ship’s airlock attribute value.
- If it matches "#-1*" (sealed):
  - Forces an @emit on the ship’s helm to report the attempted egress of %N through the sealed airlock.
  - Sends the actor: "The exterior airlock door is sealed.".
- Else (unsealed):
  - Triggers `me/ejectobject` with the actor as argument.
  - Conditionally triggers `me/launchsuit` with the actor as argument if:
    - The enactor is a ship (`isship(v(#))`) AND
    - The location of the linked ship has the Z flag (`hasflag(loc(link(me)),Z)`), i.e. it’s a space-like zone.
```

### ATTRIBUTE: `launchsuit` — English description

```text
Object: Airlock Exterior Hatch Parent
Attribute: launchsuit

Purpose:
- Initializes the actor’s space-flight state upon egress, copying position/velocity/attitude values from the linked ship.
- Puts the actor into space (enter) and prints a “darkness engulfs you” message.

Inputs (by usage):
- v(0) / %0: the object (player/suit) being launched.
- link(me): linked ship/body object.

Logic:
- Sets thrust of the launched object to 0.
- Sets linear position X/Y/Z to values derived from the linked ship (offset parameter 1.0).
- Sets linear velocity X/Y/Z from the linked ship (0.0 passed as parameter).
- Sets angular position X/Y/Z from the linked ship’s stored angular position attributes.
- Sets angular velocity Z from the linked ship’s stored angular velocity attribute.
- Executes `!enter` for the launched object.
- Sends the launched object: "The all-encompasing darkness engulfs you as you leave [name(link(me))] behind.".
```

### ATTRIBUTE: `ejectobject` — English description

```text
Object: Airlock Exterior Hatch Parent
Attribute: ejectobject

Purpose:
- Performs the in-ship “cycle out” messaging for someone exiting via the airlock.
- Logs/report the egress to the ship and to the helm.
- Moves the actor to the ship’s location (outside the ship).

Inputs (by usage):
- v(0) / %0: the object being ejected.
- link(me): linked ship/body object.
- get([link(me)]/helm): helm object reference.

Logic:
- Sends the actor: "You cycle out through the external airlock hatch.".
- Sends others (excluding the actor) in the current location: "<name> cycles out through the external airlock hatch.".
- Forces an @emit on the linked ship, announcing the actor cycles out from the ship’s airlock.
- Forces an @emit on the ship’s helm reporting the egress of the actor through the airlock.
- Forces a teleport of the actor to `loc(link(me))`.
```

### ATTRIBUTE: `Fail` — English description

```text
Object: Airlock Exterior Hatch Parent
Attribute: Fail

Purpose:
- Provides the failure message seen by the actor when they press/open the hatch.

Inputs (by usage):
- None.

Logic:
- Returns: "You press the open patch on the external airlock hatch.".
```

### ATTRIBUTE: `OFail` — English description

```text
Object: Airlock Exterior Hatch Parent
Attribute: OFail

Purpose:
- Provides the “others see” failure message corresponding to Fail.

Inputs (by usage):
- None.

Logic:
- Returns: "presses the open patch on the external airlock hatch.".
```

### ATTRIBUTE: `Desc` — English description

```text
Object: Airlock Exterior Hatch Parent
Attribute: Desc

Purpose:
- Provides the hatch description, including a status indicator light that reflects whether the airlock is sealed.

Inputs (by usage):
- link(me): linked ship/body object.
- get(s([link(me)]/airlock)): airlock status attribute string.
- loc(link(me)): location outside the ship.

Logic:
- Displays a heavy-duty hatch description.
- Computes a light color:
  - If the ship airlock attribute is blank/false (after first(get(...)) and lnot()), the light is red.
  - Otherwise, the light is green.
- Shows the outside location name via: "[name(loc(link(me)))]".
```

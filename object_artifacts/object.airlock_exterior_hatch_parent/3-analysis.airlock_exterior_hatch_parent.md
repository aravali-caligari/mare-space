# `Airlock Exterior Hatch Parent`

## English Logic Descriptions (Legacy Attribute List)

## OBJECT: `Airlock Exterior Hatch Parent`

### ATTRIBUTE: `OLook` — English description

```text
Object: Airlock Exterior Hatch Parent
Attribute: OLook

Purpose:
- Provides the “others see” message when someone looks at/through the exterior hatch porthole.

Inputs:
- None.

Logic:
- Returns a short third-person description: the actor looks out the porthole.
```

### ATTRIBUTE: `OnFail` — English description

```text
Object: Airlock Exterior Hatch Parent
Attribute: OnFail

Purpose:
- Handles the “open patch” / egress attempt for the exterior airlock hatch.
- If the airlock is sealed, it blocks and reports.
- If the airlock is unsealed, it cycles the actor out, and may also initialize suit/space state.

Inputs (by usage):
- %# : the actor attempting to egress
- link(me): the ship object this hatch is linked to
- get([link(me)]/airlock): airlock state indicator
- get([link(me)]/helm): helm object (used for reporting)
- v(#): (legacy) context variable used by isship()/land()/etc

Logic:
- Performs a switch on the ship’s `airlock` attribute:
  - If it matches `#-1*` (sealed/unavailable):
    - Emits a report to the helm about the attempted egress.
    - Notifies the actor that the exterior airlock door is sealed.
  - Otherwise (airlock available):
    - Triggers `me/ejectobject` with argument `%#` to handle messaging + teleporting the actor out.
    - Conditionally triggers `me/launchsuit` with argument `%#` if the context indicates a ship and the ship is in a Z-flagged space location.
```

### ATTRIBUTE: `launchsuit` — English description

```text
Object: Airlock Exterior Hatch Parent
Attribute: launchsuit

Purpose:
- Initializes the exiting actor’s space movement state (position/velocity/orientation) based on the ship’s current space state.
- Moves the actor into “space” context and prints a departure message.

Inputs:
- %0: the exiting actor
- link(me): the ship object

Logic:
- Sets the actor’s thrust to 0.
- Copies the ship’s position into the actor’s linear position using xpos/ypos/zpos with a small scale.
- Copies the ship’s velocity into the actor’s linear velocity using xvel/yvel/zvel with 0.0 scale.
- Copies ship angular position/velocity attributes into the actor.
- Forces the actor to “enter” (space engine / simulation) via `!enter`.
- Sends the actor a pemit about leaving the ship behind.
```

### ATTRIBUTE: `ejectobject` — English description

```text
Object: Airlock Exterior Hatch Parent
Attribute: ejectobject

Purpose:
- Performs messaging and relocation for a successful airlock egress.

Inputs:
- %0: the exiting actor
- v(0): appears to be the exiting actor as well (used for name formatting)
- link(me): the ship object
- get([link(me)]/helm): helm object (used for reporting)

Logic:
- Sends the actor a message that they cycle out through the hatch.
- Sends the room an oemit describing the actor cycling out.
- Emits to the ship (via `@fo link(me)=@emit`) that the actor cycles out from the ship’s airlock.
- Emits to the helm that the actor egressed through the airlock.
- Teleports the actor to `loc(link(me))` (the ship’s current location).
```

### ATTRIBUTE: `Fail` — English description

```text
Object: Airlock Exterior Hatch Parent
Attribute: Fail

Purpose:
- Provides the “you see” failure message when attempting to use the hatch.

Inputs:
- None.

Logic:
- Returns a short second-person message about pressing the open patch.
```

### ATTRIBUTE: `OFail` — English description

```text
Object: Airlock Exterior Hatch Parent
Attribute: OFail

Purpose:
- Provides the “others see” failure message when someone attempts to use the hatch.

Inputs:
- None.

Logic:
- Returns a short third-person message about pressing the open patch.
```

### ATTRIBUTE: `Desc` — English description

```text
Object: Airlock Exterior Hatch Parent
Attribute: Desc

Purpose:
- Describes the exterior airlock hatch, including whether the airlock is sealed and what is visible outside.

Inputs:
- link(me): the ship
- get(s([link(me)]/airlock)): ship airlock attribute (used to decide indicator light color)
- loc(link(me)): what’s “outside” (ship’s current location)

Logic:
- Returns a textual description of the hatch and a status light.
- Computes the light color:
  - If `first(get(s([link(me)]/airlock)))` is falsy/empty -> red
  - Else -> green
- Includes the name of the ship’s current location as the view through the porthole.
```

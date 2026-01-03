# `Airlock Exterior Hatch Parent`

## English Logic Descriptions (Legacy Attribute List)

## OBJECT: `Airlock Exterior Hatch Parent`

### ATTRIBUTE: `OLook` — English description

```text
Object: Airlock Exterior Hatch Parent
Attribute: OLook

Purpose:
- Provides the room “other people see” message when someone looks out / interacts with the exterior hatch.

Inputs (by usage):
- None.

Logic:
- Returns a short descriptive action line.
```

```mud
original
OLook:	looks out the exterior airlock hatch porthole.
```

### ATTRIBUTE: `OnFail` — English description

```text
Object: Airlock Exterior Hatch Parent
Attribute: OnFail

Purpose:
- Handles a player attempting to use/open the exterior airlock hatch.
- Blocks egress when the airlock is sealed; otherwise cycles the player out and may initialize EVA/space-state.

Inputs (by usage):
- %#: the player attempting egress.
- %N: the player’s name (used in an emitted report message).
- link(me): the ship/body object associated with this hatch.
- link(me)/airlock: an attribute used as the “airlock sealed/unsealed” indicator.
- link(me)/helm: an attribute holding a helm object dbref (used for reporting).

Logic:
- Switches on the value of get(link(me)/airlock).
  - If it matches #-1* (airlock appears sealed/unavailable):
    - Forces the helm object to emit a report that the player attempted egress through a sealed airlock.
    - Notifies the player that the exterior airlock door is sealed.
  - Otherwise (airlock appears usable):
    - Triggers this object’s ejectobject program with argument %#.
    - If the player is a ship and the ship is located in a Z-flagged location (legacy zero-g check), triggers launchsuit with argument %#.

Side effects:
- Emits messages to helm/ship.
- Calls other programs that may teleport the player and/or alter their space-state.
```

```mud
original
OnFail:	@swi get([link(me)]/airlock)=#-1*,{@fo get([link(me)]/helm)=@emit {The [name(get(s([link(me)]/helm)))] reports the attempted egress of '%N' through the sealed airlock.};@pemit %#=The exterior airlock door is sealed.},{@tr me/ejectobject=%#;@tr me/[if(land(isship(v(#)),hasflag(loc(link(me)),Z)),launchsuit)]=%#}
```

### ATTRIBUTE: `launchsuit` — English description

```text
Object: Airlock Exterior Hatch Parent
Attribute: launchsuit

Purpose:
- Initializes EVA/space-state for the target, positioning them at the ship and matching the ship’s motion/attitude.

Inputs (by usage):
- %0: the target being “launched” (typically the player).
- link(me): the ship/body object.

Logic:
- Sets the target’s thrust to 0.
- Sets the target’s linear position (X/Y/Z) using legacy helper functions xpos/ypos/zpos relative to the ship and an offset of 1.0.
- Sets the target’s linear velocity (X/Y/Z) using legacy helper functions xvel/yvel/zvel relative to the ship.
- Copies the ship’s angular position (X/Y/Z) and angular velocity Z into the target.
- Executes !enter on the target (legacy mechanic for entering EVA/space context).
- Sends a message to the target describing leaving the ship behind.

Side effects:
- Modifies the target’s space movement/state attributes.
```

```mud
original
launchsuit:	@thrust %0=0;@linposx %0=xpos([link(me)],%0,1.0);@linposy %0=ypos([link(me)],%0,1.0);@linposz %0=zpos([link(me)],%0,1.0);@linvelx %0=xvel([link(me)],0.0);@linvely %0=yvel([link(me)],0.0);@linvelz %0=zvel([link(me)],0.0);@angposx %0=get(s([link(me)]/angposx));@angposy %0=get(s([link(me)]/angposy));@angposz %0=get(s([link(me)]/angposz));@angvelz %0=get(s([link(me)]/angvelz));!enter %0;@pemit %0=The all-encompasing darkness engulfs you as you leave [name(link(me))] behind.
```

### ATTRIBUTE: `ejectobject` — English description

```text
Object: Airlock Exterior Hatch Parent
Attribute: ejectobject

Purpose:
- Performs the “cycle out the airlock” messaging and moves the target to the ship’s external location.

Inputs (by usage):
- %0 / v(0): the target being ejected (typically the player).
- link(me): the ship/body object.
- link(me)/helm: helm object dbref (for reporting).

Logic:
- Notifies the target that they cycle out through the hatch.
- Emits to the target’s surroundings a message indicating they cycle out.
- Forces the ship (link(me)) to emit a message that the target cycles out from the ship’s airlock.
- Forces the helm object to emit a report that the target egressed through the airlock.
- Forces this object (me) to teleport the target to loc(link(me)) (the ship’s external location).

Side effects:
- Emits multiple messages.
- Teleports the target.
```

```mud
original
ejectobject:	@pemit %0=You cycle out through the external airlock hatch.;@oemit %0={%[name(v(0))] cycles out through the external airlock hatch.};@fo link(me)=@emit {%%%[name(v(0))] cycles out from the airlock of the [name(link(me))].};@fo get([link(me)]/helm)=@emit {The [name(get(s([link(me)]/helm)))] reports the egress of '%%%[name(v(0))]' through the airlock.};@fo me=@tel %0=loc(link(me))
```

### ATTRIBUTE: `Fail` — English description

```text
Object: Airlock Exterior Hatch Parent
Attribute: Fail

Purpose:
- Provides the player-facing failure/interaction message when using the hatch.

Inputs:
- None.

Logic:
- Returns a short sentence describing pressing the open patch.
```

```mud
original
Fail:	You press the open patch on the external airlock hatch.
```

### ATTRIBUTE: `OFail` — English description

```text
Object: Airlock Exterior Hatch Parent
Attribute: OFail

Purpose:
- Provides the “others see” failure/interaction message when someone uses the hatch.

Inputs:
- None.

Logic:
- Returns a short action line.
```

```mud
original
OFail:	presses the open patch on the external airlock hatch.
```

### ATTRIBUTE: `Desc` — English description

```text
Object: Airlock Exterior Hatch Parent
Attribute: Desc

Purpose:
- Describes the hatch, including an indicator light and what can be seen through the porthole.

Inputs (by usage):
- link(me)/airlock: used to decide the light color.
- loc(link(me)): used to name what is “outside” the hatch.

Logic:
- Describes a heavy exterior hatch.
- Computes an indicator color:
  - Reads link(me)/airlock, takes first(...), and applies lnot(...).
  - If the result is true: uses red; otherwise green.
- Includes the name of loc(link(me)) as the visible external scene.
```

```mud
original
Desc:	This is a heavy duty exterior hatch designed to protect the ship from the vacuum of space. The light above the hatch is [ifelse(lnot(first(get(s([link(me)]/airlock)))),red,green)]. Looking through the hatch's porthole you see '[name(loc(link(me)))]'.
```

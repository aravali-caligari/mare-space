# `Frontier Storm Door Master`

## English Logic Descriptions (Legacy Attribute List)

## OBJECT: `Frontier Storm Door Master`

### ATTRIBUTE: `Passthrough` — English description

```text
Object: Frontier Storm Door Master
Attribute: Passthrough

Purpose:
- Handles a player passing through an already-open door, with a short delay.
- Sends the standard success message to the player, emits “player goes through” on the origin side, emits “player comes in” on the far side, then teleports the player through the door.

Inputs (by usage):
- %0: the player (or object) moving through the door.
- v(0): also used as the moving object for name() calls (legacy pattern).
- v(succ): the local success text (typically the built-in Succ attribute).
- v(leading): a text label for the door’s “side” / direction (used in messages).
- v(otherside): dbref of the opposite-side door/master object.
- link(me): the destination location/room (door link).

Logic:
- Waits 1 second.
- Sends the player the success message (v(succ)).
- Emits to others in the origin room that the player went through the open door.
- Forces the opposite side object to emit that the player came in through the open door, using the opposite side’s leading label.
- Teleports the player to link(me).

Side effects:
- Emits messages and teleports %0.
```

```mud
original
Passthrough:	@wait 1={@pemit %0=v(succ);@oemit %0=You see [name(v(0))] go through the open door %%%[v(leading)].;@fo v(otherside)=@emit You see [name(v(0))] come in through the open door [get(s([v(otherside)]/leading))].;@fo me=@tel %0=link(me)}
```

### ATTRIBUTE: `OnFail` — English description

```text
Object: Frontier Storm Door Master
Attribute: OnFail

Purpose:
- Handles the player interaction when “using” the door panel (pressing the open button).
- If the door is currently closed, it routes the interaction to one of: locked / autoopen / noentry / nonactive.
- If the door is already open, it routes the interaction to Passthrough.

Inputs (by usage):
- %#: the cause/player pressing the button.
- %o: pronoun/secondary argument passed through to downstream handlers (used by noentry).
- v(flags): door state flags (e.g., OPEN, ACTIVE, LOCKED, AUTOCLOSE).
- v(level): numeric access/security level threshold.
- v(roster): a list used to look up a caller’s clearance/permission.
- owner(v(#)): owner of the current cause object reference (legacy).
- v(#): legacy “cause dbref” environment reference.

Logic:
- Checks whether the door is OPEN.
  - If not OPEN (door closed):
    - Emits to others that the player pressed the open button on the door.
    - If door is ACTIVE:
      - If door is LOCKED: triggers locked with args %#,%o.
      - Else runs a clearance check using v(level) and v(roster):
        - If the clearance check passes: triggers autoopen with args %#,%o.
        - Else: triggers noentry with args %#,%o.
    - Else (not ACTIVE): triggers nonactive with args %#,%o.
  - If OPEN: triggers passthrough with args %#,%o.

Side effects:
- Emits messages.
- Calls other programs that may open the door and/or move the player.
```

```mud
original
OnFail:	@swi wmatch(v(flags),OPEN)=0,{@oemit %#=You see %n press the open button on the door %[v(leading)].;@tr me/[ifelse(wmatch(v(flags),ACTIVE),ifelse(wmatch(v(flags),LOCKED),locked,ifelse(scomp(sgn(add(v(level),extract(v(roster),add(wmatch(v(roster),owner(v(#))),1),1))),-1),autoopen,noentry)),nonactive)]=%#,%o},{@tr me/passthrough=%#,%o}
```

### ATTRIBUTE: `AutoOpen` — English description

```text
Object: Frontier Storm Door Master
Attribute: AutoOpen

Purpose:
- Implements an “auto open and pass through” action.
- Ensures both sides of the door are marked OPEN.
- Queues the actor into a semaphore list and attempts to serialize passage.

Inputs (by usage):
- %0: the player/object attempting to go through.
- v(flags): this side’s door state flags.
- v(otherside): dbref of the opposite-side door/master object.
- v(semaphore): a space-separated queue list of dbrefs.

Logic:
- Ensures OPEN is present in this side’s flags.
- Ensures OPEN is present in the other side’s flags.
- Prepends/appends the actor (%0) into v(semaphore).
- Switches on the last word in v(semaphore):
  - If it matches %0: triggers godoor=%0.
  - Otherwise: triggers passthrough=%0.
- Waits 3 seconds, then forces this object twice and then forces execution of the semaphore program.
  - (Legacy intent appears to be “advance / clear the semaphore queue” after a short delay.)

Side effects:
- Modifies door flags on this and the other side.
- Updates the semaphore queue.
- Calls other programs that may teleport the actor.
```

```mud
original
AutoOpen:	@flags me=ifelse(wmatch(v(flags),OPEN),v(flags),strcat(strcat(OPEN,spc(1)),v(flags)));@flags v(otherside)=ifelse(wmatch(get([v(otherside)]/flags),OPEN),get([v(otherside)]/flags),strcat(strcat(OPEN,spc(1)),get([v(otherside)]/flags)));@semaphore me=strcat(strcat(v(0),spc(1)),v(semaphore));@swi extract(v(semaphore),wcount(v(semaphore)),1)=%0,@tr me/godoor=%0,@tr me/passthrough=%0;@wait 3=@fo me=@fo me=@semaphore me
```

### ATTRIBUTE: `OnLook` — English description

```text
Object: Frontier Storm Door Master
Attribute: OnLook

Purpose:
- Displays door panel status and door state to the viewer.
- If the door is open or has a window, provides a “look through” view into the linked room.

Inputs (by usage):
- %#: the viewer.
- get(me/flags): door state flags.
- get(me/id): a door identifier string/number.
- get(me/leading): a label used in the descriptive text.
- link(me): the linked destination room.

Logic:
- Prints a panel light status based on flags:
  - If ACTIVE:
    - If LOCKED: red triangle.
    - Else: green circle.
  - Else: panel lights appear off.
- Prints the door ID.
- Prints whether the door is open, closed-with-window, or closed-without-window.
- If the door is OPEN or WINDOW is set:
  - Triggers lookthrough with argument %#.

Side effects:
- Emits output to the viewer.
- May call lookthrough.
```

```mud
original
OnLook:	@pemit %#=[ifelse(wmatch(get(me/flags),ACTIVE),ifelse(wmatch(get(me/flags),LOCKED),On the door panel you see a red triangle lit.,On the door panel you see a green circle lit.),The lights on the door panel seem to be turned off.)] The door panel has the ID #[get(me/id)]. [ifelse(wmatch(get(me/flags),OPEN),The door is currently open and you can see into the next room.,ifelse(wmatch(get(me/flags),WINDOW),The door is closed but there is a window on the door that allows you to see into the next room.,The door is closed tight and has no window on it.))];@tr me/[if(lor(wmatch(get(me/flags),OPEN),wmatch(get(me/flags),WINDOW)),lookthrough)]=%#
```

### ATTRIBUTE: `Godoor` — English description

```text
Object: Frontier Storm Door Master
Attribute: Godoor

Purpose:
- Executes the “go through the door” action when the door is being used as a passage.
- Sends messages on both sides and teleports the actor.
- Optionally starts auto-close behavior.
- Applies XOR locking behavior to related doors.

Inputs (by usage):
- %0: the actor moving through the door.
- v(doorsucc): player-facing success message.
- v(doorosucc): “others see” success message.
- v(doorodrop): arrival message emitted on the far side.
- v(otherside): opposite-side object dbref.
- v(flags): this side’s flags (used to check AUTOCLOSE).
- v(XORList): list of door ID patterns used to lock/unlock related doors.
- parents(me): parent object(s) used to find sibling door objects.

Logic:
- Sends the actor the success message from doorsucc.
- Emits to others that the actor went through (doorosucc).
- Forces the opposite side object to emit the arrival message (doorodrop).
- Teleports the actor to link(me).
- If AUTOCLOSE flag is set, triggers autoclose.
- For each entry in XORList:
  - For each child of the parents(me) object(s):
    - If the child’s ID matches the XOR entry pattern, triggers that child’s lockup program.

Side effects:
- Emits messages, teleports actor, and may lock other doors.
```

```mud
original
Godoor:	@pemit %0=s(v(doorsucc)));@oemit %0=s(v(doorosucc)));@fo v(otherside)=@emit {[s(v(doorodrop))]};@fo me=@tel %0=link(me);@tr me/[if(wmatch(v(flags),AUTOCLOSE),autoclose)];@foreach v(XORList)=@foreach children(parents(me))=@tr %%%%0/%%%[if(match(get(s(%%%%0/ID)),%%0*),lockup)]
```

### ATTRIBUTE: `AutoClose` — English description

```text
Object: Frontier Storm Door Master
Attribute: AutoClose

Purpose:
- Automatically closes this door and its opposite side after a delay.

Inputs (by usage):
- get(me/flags): used to check OPEN.
- get(me/otherside): dbref of the opposite side object.

Logic:
- Waits 15 seconds.
- If this side is OPEN, triggers closedoor on this object.
- Also triggers closedoor on the other side.

Side effects:
- Calls close programs on both sides.
```

```mud
original
AutoClose:	@wait 15={@tr me/%[if(wmatch(get(me/flags),OPEN),closedoor)];@tr [get(me/otherside)]/%[if(wmatch(get(me/flags),OPEN),closedoor)]}
```

### ATTRIBUTE: `Closedoor` — English description

```text
Object: Frontier Storm Door Master
Attribute: Closedoor

Purpose:
- Closes the door (removes OPEN from flags) and emits the “slides shut” message.
- Clears XOR locks on related doors by triggering unlock.

Inputs (by usage):
- get(me/flags): current flag string.
- get(me/leading): label used in the close message.
- get(me/XORList): list of XOR patterns.
- children(parents(me)): sibling doors under the same parent.

Logic:
- If OPEN is present in flags, removes it.
- Emits: The door <leading> slides shut.
- For each XORList entry, for each related sibling door whose ID matches, triggers unlock.

Side effects:
- Updates flags and triggers unlock on sibling doors.
```

```mud
original
Closedoor:	@flags me=ifelse(wmatch(get(me/flags),OPEN),remove(get(me/flags),wmatch(get(me/flags),OPEN),1),get(me/flags));@emit The door %[get(me/leading)%] slides shut.;@foreach get(me/XORList)=@foreach children(parents(me))=@tr %%%%0/%%%[if(match(get(s(%%%%0/ID)),%%0*),unlock)]
```

### ATTRIBUTE: `Opendoor` — English description

```text
Object: Frontier Storm Door Master
Attribute: Opendoor

Purpose:
- Opens the door (adds OPEN to flags) and emits the “slides open” message.
- Sets XOR locks on related doors by triggering lockup.

Inputs (by usage):
- get(me/flags): current flag string.
- get(me/sp): spacing string inserted between OPEN and other flags.
- get(me/leading): label used in the open message.
- get(me/XORList): list of XOR patterns.

Logic:
- If OPEN is not present, adds OPEN plus spacing plus existing flags.
- Emits: The door <leading> slides open.
- For each XORList entry, for each related sibling door whose ID matches, triggers lockup.

Side effects:
- Updates flags and triggers lockup on sibling doors.
```

```mud
original
Opendoor:	@flags me=ifelse(wmatch(get(me/flags),OPEN),get(me/flags),strcat(strcat(OPEN,get(me/sp)),get(me/flags)));@emit The door %[get(me/leading)%] slides open.;@foreach get(me/XORList)=@foreach children(parents(me))=@tr %%%%0/%%%[if(match(get(s(%%%%0/ID)),%%0*),lockup)]
```

### ATTRIBUTE: `doorodrop` — English description

```text
Object: Frontier Storm Door Master
Attribute: doorodrop

Purpose:
- A message template used on the far side when someone arrives through the door.

Inputs (by usage):
- get(me/otherside): used to reference the other side’s leading label.
- v(0): the arriving object.

Logic:
- Returns a sentence describing the other door sliding open and the actor coming in.

Side effects:
- None (message-only attribute).
```

```mud
original
doorodrop:	The door [get(s([get(me/otherside)]/leading))] slides open and [name(v(0))] comes in.
```

### ATTRIBUTE: `doorosucc` — English description

```text
Object: Frontier Storm Door Master
Attribute: doorosucc

Purpose:
- A message template emitted to others when someone goes through the door.

Inputs (by usage):
- get(me/leading): door label.
- v(0): the actor.

Logic:
- Returns a sentence describing the door sliding open and the actor going through.

Side effects:
- None (message-only attribute).
```

```mud
original
doorosucc:	The door [get(me/leading)] slides open and [name(v(0))] goes through.
```

### ATTRIBUTE: `Locked` — English description

```text
Object: Frontier Storm Door Master
Attribute: Locked

Purpose:
- Notifies the actor (and others) that the door refused to open because it is locked.

Inputs (by usage):
- %0: the actor.
- v(0): used for name(v(0)) in the oemit.

Logic:
- Sends the actor a message about the red light.
- Emits to others that the actor noticed the red light.

Side effects:
- Emits messages.
```

```mud
original
Locked:	@pemit %0=The door refuses to open and you notice that the door panel has a red light on instead of a green light.;@oemit %0=The door refuses to open and [name(v(0))] notices that there is a red light on the door panel instead of a green light.
```

### ATTRIBUTE: `Nonactive` — English description

```text
Object: Frontier Storm Door Master
Attribute: Nonactive

Purpose:
- Notifies the actor (and others) that the door did not open because the panel is inactive.

Inputs (by usage):
- %0: the actor.
- v(0): used for name(v(0)) in the oemit.

Logic:
- Sends the actor a message about the panel lights being off.
- Emits to others that the actor noticed the panel lights are off.

Side effects:
- Emits messages.
```

```mud
original
Nonactive:	@pemit %0=The door doesn't open and you notice that the lights on the door panel are turned off.;@oemit %0=The door doesn't open and [name(v(0))] notices that the lights on the door panel are turned off.
```

### ATTRIBUTE: `Desc` — English description

```text
Object: Frontier Storm Door Master
Attribute: Desc

Purpose:
- Provides the object description shown when looking at the door.

Inputs:
- None.

Logic:
- Returns a single descriptive sentence.

Side effects:
- None (message-only attribute).
```

```mud
original
Desc:	You see a large metal sliding door in the shape of an elongated octagon.
```

### ATTRIBUTE: `doorsucc` — English description

```text
Object: Frontier Storm Door Master
Attribute: doorsucc

Purpose:
- A message template shown to the actor when they successfully go through the door.

Inputs (by usage):
- get(me/leading): door label.

Logic:
- Returns a sentence describing the door sliding open and the actor going through.

Side effects:
- None (message-only attribute).
```

```mud
original
doorsucc:	The door [get(me/leading)] slides open and you go through.
```

### ATTRIBUTE: `Fail` — English description

```text
Object: Frontier Storm Door Master
Attribute: Fail

Purpose:
- Provides the standard “you attempt to use the door” message.

Inputs:
- None.

Logic:
- Returns a short sentence.

Side effects:
- None (message-only attribute).
```

```mud
original
Fail:	You walk up to the door.
```

### ATTRIBUTE: `sp` — English description

```text
Object: Frontier Storm Door Master
Attribute: sp

Purpose:
- Stores a spacing string used when concatenating flags (e.g., between OPEN and other flag words).

Inputs:
- None.

Logic:
- This attribute is empty in this dump.

Side effects:
- None.
```

```mud
original
sp:	
```

### ATTRIBUTE: `lookthrough` — English description

```text
Object: Frontier Storm Door Master
Attribute: lookthrough

Purpose:
- Provides a “look through” view into the linked room: name, description, optional succ text, and contents.

Inputs (by usage):
- %0: the viewer.
- link(me): destination room.
- con(link(me)): container reference used to list contents.

Logic:
- Sends the viewer the name of link(me).
- Sends the viewer the description of link(me).
- If link(me) has a succ text, sends that too.
- If link(me) has contents:
  - Prints a “Contents:” header.
  - Iterates through the objects in the room and prints each object name, skipping objects with the Dark flag.

Side effects:
- Emits multiple lines to the viewer.
```

```mud
original
lookthrough:	@pemit %0=name(link(me));@pemit %0=get(s([link(me)]/desc));[if(wcount(get(s([link(me)]/succ))),@pemit s(%0)=get(s([link(me)]/succ)))];@fo me={[if(con(link(me)),s({@pemit %0=Contents:;@foreach objlist(con(link(me)))=@swi flags(v(0))=*D*,,@pemit %0=name(v(0))}))]}
```

### ATTRIBUTE: `lockup` — English description

```text
Object: Frontier Storm Door Master
Attribute: lockup

Purpose:
- Applies the LOCKED state to this door, optionally emitting a message when transitioning from unlocked to locked.

Inputs (by usage):
- v(flags): current flags string.

Logic:
- If the door is not already LOCKED:
  - Emits a “click” message and changes the panel description from green to red.
- Ensures LOCKED is present in v(flags), adding it if missing.

Side effects:
- Emits a message (only when newly locking).
- Updates v(flags) to include LOCKED.
```

```mud
original
lockup:	@swi v(flags)=*LOCKED*,,{@emit The door %[get(me/leading)%] goes *click* and the green circle on the door panel changes to a red triangle.};@flags me=ifelse(wmatch(v(flags),LOCKED),v(flags),strcat(strcat(LOCKED,spc(1)),v(flags)))
```

### ATTRIBUTE: `noentry` — English description

```text
Object: Frontier Storm Door Master
Attribute: noentry

Purpose:
- Notifies the actor (and others) that they do not have permission to open the door.

Inputs (by usage):
- %0: the actor.
- %1: a pronoun/secondary string (passed in as %o by OnFail).
- v(0): used for name(v(0)) in the oemit.

Logic:
- Sends the actor a buzzing refusal message.
- Emits to others that the door refused to open for the actor and buzzed at them.

Side effects:
- Emits messages.
```

```mud
original
noentry:	@pemit %0=The door refuses to open and just buzzes at you.;@oemit %0=The door refuses to open for [name(v(0))] and just buzzes at %1.
```

### ATTRIBUTE: `unlock` — English description

```text
Object: Frontier Storm Door Master
Attribute: unlock

Purpose:
- Removes the LOCKED state from this door, optionally emitting a message when transitioning from locked to unlocked.

Inputs (by usage):
- v(flags): current flags string.

Logic:
- If the door is currently LOCKED:
  - Emits a “click” message and changes the panel description from red to green.
- Ensures LOCKED is removed from v(flags), if present.

Side effects:
- Emits a message (only when unlocking).
- Updates v(flags) to remove LOCKED.
```

```mud
original
unlock:	@swi v(flags)=*LOCKED*,{@emit The door %[get(me/leading)%] goes *click* and the red triangle on the door panel changes to a green circle.};@flags me=ifelse(wmatch(v(flags),LOCKED),remove(v(flags),wmatch(v(flags),LOCKED),1),v(flags))
```

### ATTRIBUTE: `Succ` — English description

```text
Object: Frontier Storm Door Master
Attribute: Succ

Purpose:
- Provides the built-in success message when passing through an already-open door.

Inputs:
- None.

Logic:
- Returns a short sentence.

Side effects:
- None (message-only attribute).
```

```mud
original
Succ:	You go through the open door.
```

### ATTRIBUTE: `OnSucc` — English description

```text
Object: Frontier Storm Door Master
Attribute: OnSucc

Purpose:
- Provides “others see” messages when a player successfully goes through the open door.

Inputs (by usage):
- %#: the actor.
- get(me/otherside): dbref of the opposite-side object.
- get(me/leading): this side’s door label.

Logic:
- Forces the other side object to oemit to the actor’s location that the actor came in through the open door.
- Emits locally that the actor went through the open door.

Side effects:
- Emits messages on both sides.
```

```mud
original
OnSucc:	@fo get(me/otherside)=@oemit %#=You see %n come in through the open door [get(s([get(me/otherside)]/leading))].;@emit You see %n go through the open door [get(me/leading)].
```

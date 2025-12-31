# Airlock Interior Hatch Parent

## Name

Airlock Interior Hatch Parent

## Purpose

This is the Airlock Interior Hatch Parent object, used in older versions of the game to provide interior airlock hatch functionalities for spacecraft. It allows players to safely enter and exit the spacecraft through the interior airlock hatch, ensuring proper pressurization and depressurization procedures are followed to maintain the integrity of the ship's atmosphere.

## Metadata

```mud
Airlock Interior Hatch Parent(#9124h)
Type:	Thing
Owner:	Ptah
Flags:	Halted[0]
Bytes:	6140
Children:	1
Modified:	Tue Nov 9 19:03:43 2004
Location:	Door Equipment Room(#28607R)
Home:	Ptah's Chambers(#10586R)
```

## Object Definition

### Attribute Definitions

```mud
islocked: program
lastfun(): inherit function
pressurize: inherit program
depressurize: inherit program
int_open: inherit program
int_close: inherit program
ext_open: inherit program
ext_close: inherit program
disaster: inherit program
dualemit: inherit program
mirror(): inherit function
whereisit(): inherit function
whatisit(): inherit function
findairlock(): inherit function
```

### Attribute List

```mud
OnFail:	@swi [get(me/islocked)]=1,{@pemit %#=The door is still sealed.},{@pemit %#=You walk through.;@oemit %#=[name(v(#))] walks through the interior airlock door.;@fo [mirror()]={@emit [name(v(#))] walks through the interior airlock door.;@tel [v(#)]=here}}
OFail:	presses the open patch on the external airlock hatch.
Fail:	You press the open patch on the internal airlock hatch.
lastfun():	[extract(whatisit(),wcount(whatisit()),1)]
depressurize:	$depressurize:@swi [whereisit()]=0,{@pemit %#=*Duh* the airlock is already depressurized.},{@emit [name(v(#))] presses the 'depressurize' button.;@swi [hasflag(loc(findairlock()),Z)]=0,{@emit Nothing seems to be happening...},{@swi [get(me/islocked)]=1,{@tr me/dualemit=The airlock starts to depressurize.;@wait 4={@tr me/dualemit=The airlock has completed depressurization.;@airlock_pres [findairlock()]=0;@tr [findairlock()]/check_airlock;@slock [findairlock()]=[owner(me)]}},{@tr me/dualemit=The airlock cannot depressurize because the interior hatch is open.}}
dualemit:	@fo me={@emit [v(0)]};@fo [mirror()]={@emit [v(0)]}
mirror():	[extract(entrances(here),wmatch(foreach(entrances(here),[loc(v(0))]),link(me)),1)
whereisit():	[ifelse(stringeq(NO MATCH,get(here/airlock_pres)),get(s([link(me)]/airlock_pres)),get(here/airlock_pres))]
whatisit():	[ifelse(stringeq(NO MATCH,get(here/airlock)),get(s([link(me)]/airlock)),get(here/airlock))]
findairlock():	[ifelse(hasflag(here,R),link(me),num(here))]
pressurize:	$pressurize:@swi [whereisit()]=1,{@pemit %#=*Bonk* it is already pressurized.},{@emit [name(v(#))] presses the 'pressurize' button.;@swi [whatisit()]=#-1*,{@tr me/dualemit=The airlock starts to pressurize.;@wait 4={@tr me/dualemit=The airlock is now fully pressurized.;@airlock_pres [findairlock()]=1;@slock [findairlock()]}},{@tr me/dualemit=The airlock cannot pressurize as the air is just escaping out the open exterior hatch!}}
OnLook:	@pemit %#=Airlock Commands:;@pemit %#=+---------------+;@pemit %#=Unseal Interior;@pemit %#=Seal Interior;@pemit %#=Pressurize;@pemit %#=Depressurize;@pemit %#=Unseal Exterior;@pemit %#=Seal Exterior;@pemit %#
Desc:	This is a heavy duty internal airlock hatch designed to keep the vacuum of space outside the ship. The light above the hatch is [ifelse(get(me/islocked),red,green)]. Next to the airlock hatch is a small pannel:
disaster:	@remit [link(me)]=The airlock has blown and the interior hatch is still open, the room is depressurizing!!!;@foreach objlist(con(link(me)))]=@swi %[get(s(%%0/type))]=*SS*,{@fo %[v(0)]={f;f}},{@pemit %[v(0)]=You are blown through the airlock and out into space!;@oemit %[v(0)]=%[name(v(0))] is sucked into the airlock.;@tel %[v(0)]=[loc(here)]};@wait 4={@remit [link(me)]=The airlock emergency shutout is activated and the hatch locks.;@lock me=[owner(me)];@lock [mirror()]=[owner(me)];@remit here=The interior hatch slams shut!}
OLook:	looks over the airlock controls.
ext_open:	$unseal ext*:@swi [get(s([findairlock()]/lairlock))]=1,{ @pemit %#=The exterior hatch controls are frozen from the bridge.},{@swi [whatisit()]=#-1*,{@emit [name(v(#))] presses the 'unseal exterior' button.;@swi [ifelse(lxor(whereisit(),hasflag(loc(findairlock()),Z)),1,0)]=1,{@wait 2={@tr me/dualemit=The light on the exterior airlock hatch lights green.;@airlock [findairlock()]=[lastfun(whatisit())];@elock [findairlock()];@fo [findairlock()]=@emit The airlock hatch on the [name(findairlock())] swings open.}},{@wait 2={@tr me/dualemit=The airlock blows open!;@elock [findairlock()];@airlock [findairlock()]=[lastfun(whatisit())];@tr [findairlock()]/blownairlock;@swi [get(me/islocked)]=1,{},{@tr me/disaster}}}},{@pemit %#=It is already unsealed.}}
ext_close:	$seal ext*:@swi [get(s([findairlock()]/lairlock))]=1,{@pemit %#=The exterior hatch controls are frozen from the bridge.},{@swi [whatisit()]=#-1*,{@pemit %#=It is already sealed.},{@emit [name(v(#))] pushes the 'seal exterior' button.;@wait 2={@tr me/dualemit=The light on the exterior airlock hatch lights red.;@airlock [findairlock()]=#-1 [whatisit()];@elock [findairlock()]=[owner(me)];@fo [findairlock()]=@emit The airlock hatch on the [name(findairlock())] swings shut.}}}
int_close:	$seal int*:@swi [get(me/islocked)]=1,{@pemit %#=It is already sealed.},{@emit [name(v(#))] pushes the 'seal interior' button.;@tr me/dualemit=The light on the interior airlock hatch lights red.;@islocked me=1;@islocked [mirror()]=1}
int_open:	$unseal int*:@swi [get(me/islocked)]=1,{@emit [name(v(#))] pushes the 'unseal interior' button.;@swi [whereisit()]=0,{@tr me/dualemit=The interior airlock hatch tries to open but is held shut by the vacuum in the room.},{@tr me/dualemit=The light on the interior airlock hatch lights green.;@islocked me;@islocked [mirror()]}},{@pemit %#=The hatch is already unsealed.}
```

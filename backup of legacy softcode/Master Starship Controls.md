# Master Starship Controls

# Name

Master Starship Controls - Central control system for starships

## Purpose

This is the Master Starship Controls object, which serves as the central control system for starships in the game. It integrates various subsystems such as navigation, engineering, tactical operations, and science functions to provide a comprehensive interface for managing starship operations.

## Meta data

```mud
Master Starship Controls(#31212h)
Type:	Thing
Owner:	Ptah
Flags:	Opaque[0] Halted[0]
Bytes:	2524
Parents:	Downloader(#459h), SCI2(#520h), SCI1(#469h), Variables(#43778h), TAC(#15511h), Star Chart(#9382h), View Screen(#3490hV), INFO(#25387h), Probe Launcher(#46410), Internal Space Functions(#52323), COM(#2409h), Memory System(#13943h), NAV(#30412h), ENG(#31236h), OMS(#33251h), RCS(#33976h), SRP(#33502h)
Children:	20
Modified:	Thu Jun 20 00:46:51 1996
Location:	Helm Equipment Room(#11848R)
Home:	Helm Equipment Room(#11848R)
```

## Object Definition

### Attribute Definitions

```mud
mag: inherit program
maxrange: inherit program
Vt: inherit program
_Listen: inherit
_IDesc: inherit
```

### Attribute list

```mud
Vt:	$history list:@pemit %#=Temporarily not available.
#43778.history:	#35832 Neptune #36802 Uranus #35725 Saturn #37478 Mars #37515 Venus #37141 Mercury #36855 Jupiter #37635 Luna #49127 Terra #36610 Pluto #44086 CCII #51991 Sol
mag:	1
maxrange:	50000000
Lock:	Ptah(#5745P)
#33502.MaxRet:	50000
#31236.MaxAux:	201
Desc:	This is comprised of the various stations used to control the ship. They are all seemingly complex stations. There is 'info' for each station.
Fail:	That is part of the room.
OLook:	looks over the starship controls.
_Listen:	* has *.
_IDesc:	You are inside the ships control station. There are various types of curcuitry around you.
OEnter:	removes an access panel on the controls and squeezes inside.
OFail:	tries to remove the ship controls and fails.
Succ:	You pick up the controls.
OSucc:	removes the ship's controls!
Enter:	You remove an access panel and squeeze inside.
Leave:	You squeeze out of the controls.
OLeave:	squeezes out of a small access panel in the ship controls.
OEnterFail:	can't seem to find the access panel on the starship controls.
EnterFail:	You can't seem to find the access panel.
#33502.man_check?():	[ifelse(wmatch(v(man_list),v(0)),abs(-1),ifelse(match(man_sname(v(1)),xxx),x,ifelse(truth(v(s([man_sname(v(1))]_man))),0,1)))]
```

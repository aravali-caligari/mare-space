# Info Softcode

## Name

Info Softcode - Spacecraft Information Consoles

## Purpose

This is the Info legacy console object, used in older versions of the game to provide information display capabilities for spacecraft. It includes various functions such as displaying information for different ship consoles including engineering, science, communications, navigation, and general ship information.

## Meta data

## Object Definition

### Attribute List

```mud
FYI2: program
FYI: program
tac_info: inherit program
com_info: inherit program
eng_info: inherit program
sci_info: inherit program
gen_info: inherit program
nav_info: inherit program
```

### Attribute definitions

```mud
eng_info:	$info:/[get(me/Eng_Man)]/@wait 1=@spittext %#=space=starship console eng
sci_info:	$info:/[get(me/Sci_Man)]/@wait 1=@spittext %#=space=starship console sci
com_info:	$info:/[get(me/com_man)]/@wait 1=@spittext %#=space=starship console com
nav_info:	$info:/[get(me/nav_man)]|[con(me)]/@wait 1=@spittext %#=space=starship console nav
gen_info:	$info:@spittext %#=space=starship console general
FYI:	This is the spittext comand on the UZ -> $@spittext *=*=*:/[gt(rank(owner(v(#))),1)]/@swi controls(v(#),v(0),spoof)=0,@npe v(0)=Spittext from [unparse(v(#))]:;@force v(0)=@text v(1)=v(2)
FYI2:	gen_info needs to wind up before the rest of the *_info, otherwise they will be shown first. I don't want to have to add any waits. Usually if you enter gen_info first it will wind up at the top.
tac_info:	$info:/[get(me/Tac_Man)]/@pemit %#=NOTE: The tactical station is non-functional on MicroMUSE.;@wait 1=@spittext %#=space=starship console tac
```

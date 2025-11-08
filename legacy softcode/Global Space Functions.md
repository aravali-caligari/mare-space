# Global Space Functions

## Name

Global Space Functions - Shared functions for MARE-Space

## Purpose

This file contains a collection of global functions used throughout the MARE-Space softcode. These functions provide common calculations and utilities needed for space simulation, such as coordinate conversions, distance calculations, and health management.

## Meta data

## Object Definition

### Attribute Definitions

```mush
C(): inherit function
shipzone: inherit program
dec(): inherit function
inc(): inherit function
ascii: inherit program
lld2xyz(): inherit function
dec2deg(): inherit function
ras2deg(): inherit function
by_space_exit(): inherit dark function
Space(): inherit function
space_room(): inherit function
Health: inherit program
Limbo: inherit program
Distz(): inherit function
Disty(): inherit function
Distx(): inherit function
```

### Attribute list

```mush
dec():	[mid(v(ascii),sub(pos(v(0),v(ascii)),2),1)]
inc():	[mid(v(ascii),pos(v(0),v(ascii)),1)]
ascii:	!"#$%&'()*+,-./0123456789:;<=>?@ABCDEFGHIJKLMNOPQRSTUVWXYZ[\]^_`abcdefghijklmnopqrstuvwxyz{|}
lld2xyz():	[strcat(strcat(strcat(strcat(fmul(fmul(cos(v(1)),cos(v(0))),v(2)),spc(1)),fmul(fmul(sin(v(1)),cos(v(0))),v(2))),spc(1)),fmul(sin(v(0)),v(2)))]
dec2deg():	[fadd(fmul(23.45,sin(v(0))),v(1))]
ras2deg():	[fadd(fadd(fmul(v(0),15),fdiv(v(1),60)),fdiv(v(2),3600))]
Space():	#2001
by_space_exit():	[ifelse(stringeq(NO MATCH,get(s([exit(loc(v(0)))]/is_valid_space_exit))),0,1)]
Limbo:	$@limbo *=*:/#5745/@pemit v(1)=[get(s(%0/kill))];@fo v(0)={@oemit v(1)=[name(s(v(0)))] [get(s(%0/okill))];:dies.};@#44931.LifeLevel v(0)=0;@wait 1={@tel v(0)=#50707;@tr #50707/vb={v(0)},{v(1)}}
Health:	$health:@swi parents(%#)=*#44931*,{@pemit %#=Your Health: [get(s(%#/#44931.LifeLevel))]},{@npemit %#=Huh? % % %(Type "help" for help.)}
Distz():	[fmul(v(0),sin(fdiv(fmul(pi(),rest(v(1))),180)))]
Disty():	[fmul(v(0),fmul(sin(fdiv(fmul(pi(),first(v(1))),180)),cos(fdiv(fmul(pi(),rest(v(1))),180))))]
Distx():	[fmul(v(0),fmul(cos(fdiv(fmul(pi(),first(v(1))),180)),cos(fdiv(fmul(pi(),rest(v(1))),180))))]
space_room():	#2001
shipzone:	$shipzone:@pemit %#=Howdy y'all, PA here. We are trying to cut down on some of the MicroMUSE memory. One of the things we have noticed that uses *alot* of memory is the ship zone, another thing we have noticed is that they all have _basically_ the same commands. So we are going to create a zone parent for ship zones that will take care of things like crew rosters, ship's who, etc. The idea is to make it customizable by each ship captain while the 'meat' of the parent contains the memory. Frnkzk will be be heading the project up and he is looking for help, if you are a good zone coder please contact him and volunteer your services and/or opinions. Thank you for your help.
C():	1079252849
```

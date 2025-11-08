# Star Chart

## Name

Star Chart - Star Chart Console

## Purpose

This is the Star Chart console object, used in the game to provide players with information about known stars in the galaxy. It allows players to view a formatted list of stars, including their names, types, distances, and headings relative to the player's current position.

## Meta data

## Object Definition

### Attribute Definitions

```mush
dump_output: inherit program
chart_cmd: inherit program
format_output(): inherit function
Known_Stars: inherit program
```

### Attribute list

```mush
dump_output:	@swi [inspace(v(0))]=0,,1,@pemit %1=format_output(v(0))
format_output():	Star: [ljust(name(v(0)),10)] Type: [ljust(get(s(%0/Star)),12)] Dist: [rjust(first(km2ly(3d(v(0),get(me/us)))),7)] ly % Head: [velhdg(dx(v(0),get(me/us)),dy(v(0),get(me/us)),dz(v(0),get(me/us)))]
Known_Stars:	#51991 #40472 #40475 #43811 #11025 #11024 #11023 #11013 #11011 #11010 #11009 #11008 #10999 #10853 #9823 #41152 ||||
chart_cmd:	$chart:/[get(me/nav_man)]/@swi [HS()]=1,{@pe %#=Non-operational.},{@pemit %#=Star Chart --;@foreach [get(me/known_stars)]=%%%[ifelse(match(v(0),||||),{@pe v(#)=End.},if(inspace(v(0)),{@pe v(#)=format_output(v(0))}))]}
```

# NAV

## Name

NAV - Spacecraft Navigation Console

## Purpose

This is the NAV legacy console object, used in older versions of the game to provide navigation capabilities for spacecraft. It includes various functions such as calculating distances, relative velocities, orbital parameters, and storing navigation data in memory.

## Meta data

```mud
NAV(#30412h)
Type:	Thing
Owner:	Ptah
Flags:	Halted[0]
Bytes:	3228
Children:	1
Modified:	Fri Nov 25 23:32:45 1994
Location:	Helm Equipment Room(#11848R)
Home:	Helm Equipment Room(#11848R)
```

## Object Definition

### Attribute definitions

```mud
navdist(): inherit function
navapproach(): inherit function
diff(): inherit function
relative_math: inherit program
relative_cmd: inherit program
helm: program
nav_memory: program
ecc(): inherit function
relvel(): inherit function
grav(): inherit function
relang(): inherit function
orbitenergy(): inherit function
hasenergy?(): inherit function
```

### Attribute list

```mud
orbitenergy():	[fsub(fdiv(pow(relvel(v(0),v(1)),2),2),fdiv(grav(v(1)),3d(v(0),v(1))))]
hasenergy?():	[first(dist3d(get(s(%0/linposx)),get(s(%0/linposy)),get(s(%0/linposz)),get(s(%1/linposx)),get(s(%1/linposy)),get(s(%1/linposz))))]
relang():	[relphi(fsub(get(s(%1/linposx)),get(s(%0/linposx))),fsub(get(s(%1/linposy)),get(s(%0/linposy))),fsub(get(s(%1/linposz)),get(s(%0/linposz))),fsub(get(s(%1/linvelx)),get(s(%0/linvelx))),fsub(get(s(%1/linvely)),get(s(%0/linvely))),fsub(get(s(%1/linvelz)),get(s(%0/linvelz))))]
relvel():	[pow(fadd(fadd(pow(fsub(get(s(%0/linvelx)),get(s(%1/linvelx))),2),pow(fsub(get(s(%0/linvely)),get(s(%1/linvely))),2)),pow(fsub(get(s(%0/linvelz)),get(s(%1/linvelz))),2)),.5)]
grav():	[fmul(get(s(%0/mass)),6.67e-18)]
ecc():	[pow(fadd(1,fdiv(fmul(2,fmul(orbitenergy(v(0),v(1)),pow(fmul(fmul(3d(v(0),v(1)),relvel(v(0),v(1))),cos(fmul(3.1415926,fdiv(fsub(relang(v(0),v(1)),90),180)))),2)),pow(grav(v(1)),2)))),.5)]
relative_math:	@swi NO MEMORY=%1,{@pemit %3=Memory '%4' does not exist},%2,{@pemit %3=Memory '%5' does not exist},{@swi %0=Null,{@pemit %3=Name '%6' is invalid. Must begin with 'nav'.},{@tr me/write_memory=%0,[word(v(1),1)] [navdist(v(1),v(2))] [diff(v(1),v(2),3)] [diff(v(1),v(2),4)] [diff(v(1),v(2),5)] [diff(v(1),v(2),6)] [diff(v(1),v(2),7)] [diff(v(1),v(2),8)] [navapproach(v(1),v(2))] [velhdg(diff(v(2),v(1),3),diff(v(2),v(1),4),diff(v(2),v(1),5))] [word(v(1),12)] [word(v(1),13)],nav,[get(me/helm)]
diff():	[simp(fsub(word(v(0),v(2)),word(v(1),v(2))))]
navapproach():	[relphi(diff(v(0),v(1),3),diff(v(0),v(1),4),diff(v(0),v(1),5),diff(v(0),v(1),6),diff(v(0),v(1),7),diff(v(0),v(1),8))]
navdist():	[simp(velmag(diff(v(0),v(1)),diff(v(0),v(1)),diff(v(0),v(1))))]
relative_cmd:	$relative * to * > *:@tr me/relative_math=[ifelse(match(v(2),nav*),v(2),Null)],[ifelse(scomp(read_memory(v(0),nav,get(me/helm)),NO MEMORY),read_memory(v(0),nav,get(me/helm)),read_memory(v(0),sensor,get(me/helm)))],[ifelse(scomp(read_memory(v(1),nav,get(me/helm)),NO MEMORY),read_memory(v(1),nav,get(me/helm)),read_memory(v(1),sensor,get(me/helm)))],%#,%0,%1,%2
```

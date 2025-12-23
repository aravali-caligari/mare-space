# Sensorbot

## Name

Sensorbot - Sensor Bot Console

## Purpose

This is the Sensor Bot console object, used in the game to provide players with sensor bot capabilities for spacecraft. It allows players to manage sensor bots, including setting targets, reading sensor data, and controlling sensor bot operations.

## Meta data

## Object Definition

### Attribute definitions

```mud
maxone(): inherit function
setlead: inherit program
shipmass: inherit program
phaselist: inherit program
haltbot: inherit program
setphase: inherit program
setacc: inherit program
settarget: inherit program
absphi: program
abstheta: program
target: program
leaddistance: program
abs: program
xivel: program
zetavel: program
upsilonvel: program
chivel: program
dist: program
approach: program
acc: program
phase: program
stationkeeping: inherit program
accelphase: inherit program
turnphase: inherit program
brakephase: inherit program
readradius: inherit program
readabs: inherit program
readzeta: inherit program
readupsilon: inherit program
readchi: inherit program
readxi: inherit program
readapproach: inherit program
_Startup: inherit program
```

### Attribute list

```mud
absphi:	those unidentifieds and at what range?"
abstheta:	are
maxone():	[ifelse(add(1,fcomp(1,fabs(v(0)))),v(0),fsgn(v(0)))]
dist:	1839047
xivel:	326.74
shipmass:	100000
settarget:	$settarget *:@swi v(0)=$*,,!*,,{@target me=v(0);@pemit %#=Target set.}
setacc:	$setacc *:@acc me=fadd(0,v(0));@pemit %#=Acc set.
phaselist:	brakephase turnphase accelphase stationkeeping
haltbot:	$halt sensorbot:@halt me
setphase:	$setphase *:@swi wmatch(v(phaselist),v(0))=0,{@pemit %#={That phase is not available, use the following: %%%[v(phaselist)]}},{@phase me=v(0);@pemit %#=Phase set.}
_Startup:	@swi v(phase)=,,{clear sci;@wait 10={man sci;@wait 20=sense [v(target)]}}
leaddistance:	100000
readapproach:	!*Approach * *:@approach me=v(2)
readxi:	!*Xi | * | * |*:@xivel me=v(2);@dist me=v(1)
readchi:	!*Chi | * | * |*:@chivel me=v(2)
readupsilon:	!*Upsilon | * | * |*:@upsilonvel me=v(2)
readzeta:	!*Zeta | * | * |*:@zetavel me=v(2)
readabs:	!*Abs. * * *:@abstheta me=v(2);@absphi me=v(3)
readradius:	!*Radius* *km *:@radius me=v(2);"%[v(target)] Distance: %[v(dist)]km Abs. Bearing: %[v(abstheta)] %[v(absphi)] Approach: %[v(approach)] Velhdg: %[velhdg(v(chivel),v(upsilonvel),v(zetavel))] Xi Vel: %[v(xivel)] Current Phase: %[v(phase)];@tr me/[v(phase)]
turnphase:	@swi fsub(v(dist),fadd(fdiv(fmul(v(acc),pow(fdiv(v(xivel),v(acc)),2)),-2),fmul(v(xivel),fdiv(v(xivel),v(acc)))))=<[v(leaddistance)],{@fo autopilot=burn [fmul(v(shipmass),v(acc))];@phase me=brakingphase;@wait 10=sense [v(target)]},{@wait 10=sense [v(target)]}
accelphase:	@turntime me=
acc:	10
chivel:	88.93
upsilonvel:	314.28
zetavel:	8.85
stationkeeping:	@swi first(v(xivel))=0,{@phase me;"Completed Station Keeping at [time()]},{@fo autopilot={oms x=[fsub(0,maxone(v(chivel)))];oms y=[fsub(0,maxone(v(upsilonvel)))];oms z=[fsub(0,maxone(v(zetavel)))]};@wait sync(1)=sense [v(target)]}
brakephase:	@swi v(approach)=>360,{@fo autopilot=burn 0;@phase me=stationkeeping;@wait 15=sense [v(target)]},{@swi first(v(xivel))=<20,{@fo autopilot=burn 0;@phase me=stationkeeping;@wait 15=sense [v(target)]},{@swi first(v(xivel))=<200,{@wait 10=sense [v(target)]},{@wait fmul(8,fdiv(first(v(xivel)),v(acc)))=sense [v(target)]}}}
target:	jupiter
approach:	is it's relative position to the ship's heading."
```

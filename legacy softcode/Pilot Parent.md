# Pilot Parent

## Name

Pilot Parent - Autopilot Console

## Purpose

This is the Autopilot console object, used in the game to provide players with autopilot capabilities for spacecraft. It allows players to set targets, manage turnarounds, and handle hyperspace jumps automatically.

## Meta data

## Object Definition

### Attribute definitions

```mud
autohelp2: inherit program
autohalt: inherit program
train_Cmd: inherit program
helm: program
_attrdef4(): inherit function
man_station: inherit program
hyperfinish: inherit program
timeleft_cmd0: inherit program
timeleft_cmd: inherit program
timeleft_cmd2: inherit program
timeleft_cmd1: inherit program
zeroburn_wait(): inherit function
_attrdef12(): inherit function
zeroburn_loop: inherit program
zeroburn_cmd: inherit program
zerotime: program
hypertime: inherit program
hyperloop: inherit program
hyperupdates: program
hyperstart: inherit program
hyperformula: inherit program
hypertemp: program
shipmass: inherit program
burnrate_cmd: inherit program
burnrate: inherit program
autohelp: inherit program
settarget: inherit program
doneturn: inherit program
turns: program
turncmd: inherit program
listenphi: inherit program
listentheta: inherit program
turnloop: inherit program
anglename(): inherit function
donetheta: inherit program
donephi: inherit program
turnmsg(): inherit function
deltaphi: program
deltatheta: program
timeturn(): inherit function
targetphi: program
targettheta: program
angletheta: program
anglephi: program
reman: inherit program
delaywait: inherit program
delayburn: inherit program
Vg: inherit program
Vc: inherit program
Va: inherit program
Vs: inherit program
Vb: inherit program
Vj: inherit program
Vp: inherit program
Vn: inherit program
Vm: inherit program
Vh: inherit program
_Startup: inherit program
cloak_on: inherit program
```

### Attribute list

```mud
autohalt:	$autohalt:@emit [name(me)] has been halted.;@fo me=@halt
_attrdef4():	[ifelse(wmatch(get(v(helm),man_list),v(!)),ifelse(match(get(v(helm),s(%1_man)),v(!)),2,-1),ifelse(get(v(helm),s(%1_man)),1,0))]
train_Cmd:	$train autopilot:@helm me=;@foreach lcon(here)=@swi get(v(0),official_helm)=Yes,{@helm me=v(0)};@wait 10=@swi v(helm)=,{:does not recognize an official starship helm as being in this room to train on.},{:recognizes the starship helm.}
man_station:	@swi manned?(v(!),v(0))=-1,{clear %[v(0)];unman;@wait 5=man %[v(0)]},0,{man %[v(0)]},1,{clear %[v(0)];@wait 5=man %[v(0)]};@wait 10=@tr me/[v(1)]=v(2),v(3),v(4),v(5),v(6),v(7),v(8),v(9)
Vg:	burn [v(burnrate)];@vz me;@vr me=add(updates(),fdiv(v(vw),fdiv(v(burnrate),v(shipmass))));@emit Shut Off Time will be in %[fdiv(v(vw),fdiv(v(burnrate),v(shipmass)))] updates. Estimated time: %[time(D,add(xtime(),v(vw)))];@tr me/vs
shipmass:	100000
burnrate:	1000000
burnrate_cmd:	$burnrate *:@burnrate me=add(0,v(0));@pemit %#=Burn Rate set.
settarget:	$settarget *:@vt me=first(%0);@pemit %#=Target set.
Desc:	Its an autopilot for handling turnarounds and braking maneuvers for long space journeys. A little name plaque on its side says 'NavBot-1'. To display commands, use 'autohelp'.
turnloop:	@emit turnmsg(v(0),v(1));@wait sync(0)={rcs %1=[fdiv(v(0),timeturn(v(0)))];@wait sync(sub(timeturn(v(0)),1))={rcs %1=[fdiv(fmul(-1,v(0)),timeturn(v(0)))];@wait sync(0)={srp;@wait 15={@swi fsgn(v(delta[anglename(v(1))]))=0,{@tr me/doneturn=v(1)},{@tr me/turnloop=v(delta[anglename(v(1))]),v(1)}}}}}
doneturn:	:completed [anglename(v(0))] to [v(s(target[anglename(v(0))]))] at [time()]
timeturn():	[ifelse(fsgn(fsub(fdiv(fabs(v(0)),30),div(fabs(v(0)),30))),add(1,div(fabs(v(0)),30)),div(fabs(v(0)),30))]
turncmd:	$autoturn * to *:@turns me;@swi v(0)=theta,{@turns me=x;@targettheta me=fadd(0,v(1))},phi,{@turns me=y;@targetphi me=fadd(0,v(1))},both,{@targettheta me=fadd(0,first(v(1)));@targetphi me=fadd(0,rest(v(1)));@turns me=x y};clear nav;unman;@wait 10=man nav;@wait 18=srp;@wait 25={@foreach v(turns)=@tr me/turnloop=v(delta%%%[anglename(v(0))]),v(0)}
listentheta:	!*Theta | *:@angletheta me=fadd(0,first(v(1)));@deltatheta me=fsub(v(targettheta),v(angletheta));:read Theta at [fadd(0,first(v(1)))]
listenphi:	!*Phi | *:@anglephi me=fadd(0,first(v(1)));@deltaphi me=fsub(v(targetphi),v(anglephi));:read Phi at [fadd(0,first(v(1)))]
turnmsg():	Executing [anglename(v(1))] turn of [fdiv(v(0),timeturn(v(0)))] for [timeturn(v(0))] updates.
anglename():	[ifelse(match(v(0),X*),theta,ifelse(match(v(0),Y*),phi,psi))]
Vc:	clear nav;clear sci;unman;@wait 10=man sci;@wait 20=sense %vt;@wait 40=unman;@wait 50=man nav;@wait 60={burn 0;yrcs 30 for 6 then 30;@wait 80=@tr me/vg}
delaywait:	@swi updates()=>%1,{burn %0},{@wait fmul(8,sub(v(1),updates()))=@tr me/delaywait=v(0),v(1)}
Va:	$turnaround at *:@vz me=add(updates(),v(0));@emit Turn set to occur in %[v(0)] updates, estimated to occur at: %[time(D,add(xtime(),mul(11,v(0))))];@tr me/vb
Vs:	@swi updates()=>%vr,{clear nav;@wait 10=man nav;@wait 25={burn 0;@wait 10=unman};@fo [owner(me)]=+mail [name(owner(me))]=Completed Shutoff at [time()];@vr me},{@wait fmul(8,fsub(v(vr),updates()))=@tr me/vs}
Vb:	@swi updates()=>%vz,{@tr me/vc},{@wait fmul(8,fsub(v(vz),updates()))=@tr me/vb}
Vj:	@emit Turn completed to [v(vu)] at [time()].;@vl me
Vp:	!*Xi * | * |*:@vw me=%2;@emit Read Xi Vel: %2
Vn:	!*Upsilon * | * |*:@emit Read Upsilon Vel: %2;@vy me=%2
Vm:	!*Chi * | * |*:@emit Read Chi Vel: %2;@vx me=%2
Vh:	$plottime * acc * with *:@pemit %#=Updates to turnaround:[fsub(fsqrt(fadd(fdiv(v(0),v(1)),pow(fdiv(v(2),v(1)),2))),fdiv(v(2),v(1)))]
Lock:	Carrie_Gram(#42921P)
delayburn:	$delayed burn * at *:clear nav;@wait 10=man nav;:executes delayed burn of %%0 in %%1 updates.;@tr me/delaywait={[add(v(0),0)]},{[add(updates(),v(1))]}
reman:	$reman autopilot:unman;clear nav;@wait 15=man nav
hypertemp:	43562.603553
hyperstart:	$start hyperspace process:@hyperupdates me=[add(get(me/hypertemp),updates())];@tr me/hyperloop;@pemit %#=Hyperdrive process started, 'check HS time' to see time remaining.
hyperloop:	@swi [gte(updates(),v(hyperupdates))]=1,{@tr me/hyperfinish},{@wait fmul(8,fsub(v(hyperupdates),updates()))=@tr me/hyperloop}
hypertime:	$check HS time:@pemit %#=Time left to Hyperspace exit: [ifelse(gteq(fdiv(sub(v(hyperupdates),updates()),360),24),strcat(simp(fdiv(sub(v(hyperupdates),updates()),8640)),days.),ifelse(gt(fdiv(sub(v(hyperupdates),updates()),6),59),strcat(simp(fdiv(sub(v(hyperupdates),updates()),360)),hrs.),strcat(simp(fdiv(sub(v(hyperupdates),updates()),6)),mins.)))]
_Startup:	@wait 15={@swi v(vz)=,,@tr me/vb;@swi v(vr)=,,@tr me/vs;@swi v(hyperupdates)=,,@tr me/hyperloop}
_attrdef12():	[switch(sgn(zerotime_wait()),-1,-1,0,-1,ifelse(sub(sgn(fsub(zerotime_wait(),100)),1),0,1))]
zeroburn_wait():	[fsub(updates(),fdiv(v(vw),fdiv(v(burnrate),v(shipmass))))]
zeroburn_cmd:	$zeroburn:unman;clear sci;@wait 10=man sci;@wait 20={sense %vt};@wait 40={@tr me/zeroburn_loop}
zeroburn_loop:	@swi zeroburn?(v(vw))=0,{@wait fsub(fmul(zerotime_wait(),9),20)=@tr me/zeroburn_loop},-1,{unman;clear nav;@wait 10=man nav;@wait 20=burn 0;@fo [owner(me)]=+mail [name(owner(me))]=Completed zeroburn shutoff at [time()];@zerotime me},1,{unman;clear sci;@wait 10=man sci;@wait 20={sense %vt};@wait 30={@wait fsub(fmul(zerotime_wait(),9),20)=@tr me/zeroburn_loop}}
timeleft_cmd1:	@pemit %0=Time left to turnaround: [ifelse(gt(fdiv(sub(v(vz),updates()),6),59),strcat(fdiv(sub(v(vz),updates()),360),hrs.),strcat(fdiv(sub(v(vz),updates()),6),mins.))]
timeleft_cmd2:	@pemit %0=Time left to shutoff: [ifelse(gt(fdiv(sub(v(vr),updates()),6),59),strcat(fdiv(sub(v(vr),updates()),360),hrs.),strcat(fdiv(sub(v(vr),updates()),6),mins.))]
timeleft_cmd:	$timeleft:@swi v(vz)=,{@tr me/timeleft_cmd0=%#},{@tr me/timeleft_cmd1=%#}
timeleft_cmd0:	@swi v(vr)=,{@pemit %0=Not programmed.},{@tr me/timeleft_cmd2=%0}
hyperfinish:	clear nav;@wait 10=man nav;@wait 25={hyperjump;@wait 10=unman};@fo [owner(me)]=+mail [name(owner(me))]=Hyperdrive shutoff occured at [time()];@hyperupdates me
hyperformula:	$hyperset *ly with *kpu:@hypertemp me=simp(fdiv(ly2km(v(0)),fmul(365,v(1))));@pemit %#=Hyperspace computation complete, 'START HYPERSPACE PROCESS' to activate.
autohelp:	$autohelp:@pemit %#=NavBot-1 list of commands:;@pemit %#=SETTARGET <name>: Set autopilot turnarounds to watch <name> on sensors;@pemit %#=DELAYED BURN <thrust> AT <updates>;@pemit %#=AUTOTURN <direction> TO <angle>:Direction being theta, phi, or psi.;@pemit %#=PLOTTIME <distance> ACC <accel> WITH <approach velocity>: Plot time in turnarounds until a turnaround needs to be performed to arrive at destination.;@pemit %#=REMAN AUTOPILOT:Make it man navigation again after being booted;@pemit %#=BURNRATE <thrust level>:Set the burn rate the autopilot will use after performing any turnarounds. Default is 1000000.;@pemit %#=TURNAROUND AT <updates>:Set autopilot to perform turnaround at a certain time;@pemit %#=TIMELEFT:Shows time left to either turnaround or shutoff.;@pemit %#=ZEROBURN:Inoperational;@pemit %#=HYPERSET <dist>LY WITH <velocity>KPU:Dist in light years and velocity is pre-jump speed.;@pemit %#=CHECK HS TIME:Show time to hyperdrive shutdown. ;@tr me/autohelp2=%#
autohelp2:	@pemit %0=AUTOHALT:Emergency halt of autopilot functions.
cloak_on:	$cloak_on PASSKEY=*:@ifelse(eq(v(eng_man),name()),@ifelse(eq(get(v(us),vismult),-1),emit(Cloaking device already on.),@ifelse(eq(v(passkey),concat(00,%0)),set(get(v(us),vismult),-1);emit(Cloaking device engaged.),emit(Invalid cloak passkey.)),emit(You are not the current engineering console operator.))
```

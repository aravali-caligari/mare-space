# Legacy Console: ENG

## Name

ENG - Engineering Console

## Purpose

This is the ENG legacy console object, used in older versions of the game to provide engineering capabilities for spacecraft. It includes various engineering functions such as power management, fuel monitoring, system diagnostics, and repairs.

## Meta data

## Object Definition

### Attribute definitions

```mush
initfuel_cmd: inherit program
fuel_start: program
fuel_date: program
DrnSense: inherit program
MaxSense: inherit program
AllSense: inherit program
PwrSense: program
PwrRead2: inherit program
wormjump2(): inherit function
wormjump(): inherit function
worm_cmd: inherit program
airlockstatus: inherit program
unlockairlock: inherit program
lockairlock: inherit program
Hyper_cmd: inherit program
fueltotal(): inherit function
Generate_Cmd: inherit program
AllScrn: inherit program
DrnComm: inherit program
DrnBatt: inherit program
DrnWeap: inherit program
DrnShld: inherit program
DrnBeac: inherit program
DrnScrn: inherit program
DrnRep: inherit program
DrnScan: inherit program
AllComm: inherit program
MaxComm: inherit program
pwrcomm: program
shield_cmd: inherit program
Engine_cmd: inherit program
evalfuel(): inherit function
fuelcon(): inherit function
Fuel_Cmd: inherit program
MaxThr: program
MinThr: program
Engine: program
DrnAux: inherit program
MaxAux: inherit program
AllAux: inherit program
PwrAux: program
MaxShld: inherit program
Allocate: inherit program
PwrScan: program
AllScan: inherit program
MaxScan: inherit program
AllBatt: inherit program
PwrBatt: program
AllWeap: inherit program
PwrWeap: program
MaxBatt: inherit program
MaxWeap: inherit program
AllRep: inherit program
PwrRep: program
MaxRep: inherit program
AllShld: inherit program
PwrShld: program
AllBeac: inherit program
PwrBeac: program
MaxBeac: inherit program
PwrRead: inherit program
Drain: inherit program
```

### Attribute list

```mush
Engine_cmd:	$engine:/[get(me/eng_man)]/@swi truth(get(me/engine))=1,{@pemit %#;@pemit %#=Type: [name(get(me/engine))];@pemit %#=Rated at: [get(s(%/us//rating))]:1;@npemit %#=Operating at: [add(get(s(%/us//efficiency)),1)]%%%% max eff.;@pemit %#=Thrust Range: [get(me/MinThr)]-[get(me/MaxThr)];@pemit %#},{@pemit %#=Engine is disengaged.}
worm_cmd:	$wormjump:/[v(nav_man)]/@swi is_a(v(engine),#24225)=1,{[wormjump(first(foreach(indist(v(us),50000),[if(is_a(v(0),#23318),v(0))])))]},{@pe %#=How do you expect to use a worm hole without a worm drive engaged?}
AllBatt:	@swi get(me/PwrBatt)=*Damaged*,{@pemit %0=Batteries are damaged.},*Destroyed*,{@pemit %0=Batteries are destroyed.},{@swi %[comp(sub(get(me/MaxBatt),1),add(get(me/PwrBatt),abs(%1)))%]=-1,{@pemit %0=Batteries cannot be charged to that potential.},{@pwrbatt me=add(get(me/pwrbatt),abs(%1));@pwrgen [get(me/us)]=sub(get(s([get(me/us)]/pwrgen)),abs(%1));@pemit %0=Power Allocated to Batteries.}
AllScrn:	@swi get(me/PwrScrn)=*Damaged*,{@pemit %0=Screens is damaged.},*Destroyed*,{@pemit %0=Screens is destroyed.},{@swi %[comp(sub(get(me/MaxScrn),1),add(get(me/PwrScrn),abs(%1)))%]=-1,{@pemit %0=Screens cannot be charged to that potential.},{@pwrScrn me=add(get(me/pwrScrn),abs(%1));@pwrgen [get(me/us)]=sub(get(s([get(me/us)]/pwrgen)),abs(%1));@pemit %0=Power Allocated to Screens.}
DrnComm:	@pwrgen [get(me/us)]=add(get(me/PwrComm),get(s([get(me/us)]/PwrGen)));@pwrComm me=0;@pemit %0=Power drained from Communications.
DrnWeap:	@pwrgen [get(me/us)]=add(get(me/PwrWeap),get(s([get(me/us)]/PwrGen)));@pwrWeap me=0;@pemit %0=Power drained from Weapons.
DrnShld:	@pwrgen [get(me/us)]=add(get(me/PwrAux),get(s([get(me/us)]/PwrGen)));@pwrShld me=0;@pemit %0=Power drained from Shields.
DrnScrn:	@pwrgen [get(me/us)]=add(get(me/PwrScrn),get(s([get(me/us)]/PwrGen)));@pwrScrn me=0;@pemit %0=Power drained from Screens.
DrnRep:	@pwrgen [get(me/us)]=add(get(me/PwrRep),get(s([get(me/us)]/PwrGen)));@pwrRep me=0;@pemit %0=Power drained from Repairs.
DrnBeac:	@pwrgen [get(me/us)]=add(get(me/PwrBeac),get(s([get(me/us)]/PwrGen)));@pwrBeac me=0;@pemit %0=Power drained from Beacon.
DrnScan:	@pwrgen [get(me/us)]=add(get(me/PwrScan),get(s([get(me/us)]/PwrGen)));@pwrScan me=0;@pemit %0=Power drained from Scanners.
DrnBatt:	@pwrgen [get(me/us)]=add(get(me/PwrBatt),get(s([get(me/us)]/PwrGen)));@pwrBatt me=0;@pemit %0=Power drained from Batteries.
evalfuel():	[ifelse(gte(5000,v(4)),fadd(fuelcon(v(0),v(1),v(2)),v(3)),fuelcon(v(0),v(1),v(2)))]
fuelcon():	[fdiv(abs(v(0)),fmul(v(1),fdiv(v(2),1)))]
MaxScan:	501
DrnAux:	@pwrgen [get(me/us)]=add(get(me/PwrAux),get(s([get(me/us)]/PwrGen)));@pwraux me=0;@pemit %0=Power drained from Auxillary.
MaxAux:	201
AllAux:	@swi get(me/PwrAux)=*Damaged*,{@pemit %0=Auxillary is damaged.},*Destroyed*,{@pemit %0=Auxillary is destroyed.},{@swi %[comp(sub(get(me/MaxAux),1),add(get(me/PwrAux),abs(%1)))%]=-1,{@pemit %0=Auxillary cannot be charged to that potential.},{@pwrAux me=add(get(me/pwrAux),abs(%1));@pwrgen [get(me/us)]=sub(get(s([get(me/us)]/pwrgen)),abs(%1));@pemit %0=Power Allocated to Auxillary.}
MaxBeac:	51
MaxWeap:	0
PwrWeap:	0
MaxShld:	801
PwrBatt:	1000
MaxBatt:	2001
MaxRep:	101
AllBeac:	@swi get(me/PwrBeac)=*Damaged*,{@pemit %0=Beacon Emitter are damaged.},*Destroyed*,{@pemit %0=Beacon Emitter are destroyed.},{@swi %[comp(sub(get(me/MaxBeac),1),add(get(me/PwrBeac),abs(%1)))%]=-1,{@pemit %0=Beacon Emitter cannot be charged to that potential.},{@pwrBeac me=add(get(me/pwrBeac),abs(%1));@pwrgen [get(me/us)]=sub(get(s([get(me/us)]/pwrgen)),abs(%1));@pemit %0=Power Allocated to Beacon Emitter.}
AllRep:	@swi get(me/PwrRep)=*Damaged*,{@pemit %0=Repairs are damaged.},*Destroyed*,{@pemit %0=Repairs are destroyed.},{@swi %[comp(sub(get(me/MaxRep),1),add(get(me/PwrRep),abs(%1)))%]=-1,{@pemit %0=Repairs cannot be charged to that potential.},{@pwrRep me=add(get(me/pwrRep),abs(%1));@pwrgen [get(me/us)]=sub(get(s([get(me/us)]/pwrgen)),abs(%1));@pemit %0=Power Allocated to Repairs.}
AllWeap:	@swi get(me/PwrWeap)=*Damaged*,{@pemit %0=Weapons Grid are damaged.},*Destroyed*,{@pemit %0=Weapons Grid are destroyed.},{@swi %[comp(sub(get(me/MaxWeap),1),add(get(me/PwrWeap),abs(%1)))%]=-1,{@pemit %0=Weapons Grid cannot be charged to that potential.},{@pwrWeap me=add(get(me/pwrWeap),abs(%1));@pwrgen [get(me/us)]=sub(get(s([get(me/us)]/pwrgen)),abs(%1));@pemit %0=Power Allocated to Weapons Grid.}
AllShld:	@swi get(me/PwrShld)=*Damaged*,{@pemit %0=Shield Array are damaged.},*Destroyed*,{@pemit %0=Shield Array are destroyed.},{@swi %[comp(sub(get(me/MaxShld),1),add(get(me/PwrShld),abs(%1)))%]=-1,{@pemit %0=Shield Array cannot be charged to that potential.},{@pwrShld me=add(get(me/pwrShld),abs(%1));@pwrgen [get(me/us)]=sub(get(s([get(me/us)]/pwrgen)),abs(%1));@pemit %0=Power Allocated to Shield Array.}
AllScan:	@swi get(me/PwrScan)=*Damaged*,{@pemit %0=Scanners are damaged.},*Destroyed*,{@pemit %0=Scanners are destroyed.},{@swi %[comp(sub(get(me/MaxScan),1),add(get(me/PwrScan),abs(%1)))%]=-1,{@pemit %0=Scanners cannot be charged to that potential.},{@pwrscan me=add(get(me/pwrscan),abs(%1));@pwrgen [get(me/us)]=sub(get(s([get(me/us)]/pwrgen)),abs(%1));@pemit %0=Power Allocated to Scanners.}
MaxComm:	1001
AllComm:	@swi get(me/PwrComm)=*Damaged*,{@pemit %0=Communications are damaged.},*Destroyed*,{@pemit %0=Communications are destroyed.},{@swi %[comp(sub(get(me/MaxComm),1),add(get(me/PwrComm),abs(%1)))%]=-1,{@pemit %0=Communications cannot be charged to that potential.},{@pwrcomm me=add(get(me/pwrcomm),abs(%1));@pwrgen [get(me/us)]=sub(get(s([get(me/us)]/pwrgen)),abs(%1));@pemit %0=Power Allocated to Communications.}
Generate_Cmd:	$generate *:/[get(me/eng_man)]/@swi comp(add(0,abs(v(0))),500)=1,{@pemit %#=Generators are unable to convert more than 500 kiloliters per update into energy.},{@pwrfuel v(us)=add(0,abs(v(0)));@pemit %#=Generators now converting [add(0,abs(v(0)))] kiloliters of fuel per update into energy.}
fueltotal():	[simp(ifelse(hs(),fadd(evalfuel(v(0),v(1),v(2),v(3),v(4)),2000),evalfuel(v(0),v(1),v(2),v(3),v(4))))]
Hyper_cmd:	$hyperjump:/[get(me/nav_man)]/@swi [HS()]=1,{@tr %/Engine//Hyperoff;@pemit %#=Disengaging hyperspace envelope.},{@tr %/Engine//Hypertest}
unlockairlock:	$unlock airlock:/[v(eng_man)]/@swi get([v(us)]/airlock)=,{@pemit %#=This ship has no airlock.},#-1*,{@swi get([v(us)]/lairlock=,{@pemit %#=The airlock is already unlocked.},{@lairlock v(us);@pemit %#=The airlock is now unlocked for use.}}
lockairlock:	$lock airlock:/[v(eng_man)]/@swi get([v(us)]/airlock)=,{@pemit %#=This ship has no airlock.},#-1*,{@swi get([v(us)]/lairlock)=1,{@pemit %#=Airlock is already locked.},{@lairlock v(us)=1;@pemit %#=Airlock is now locked in position.}}
wormjump2():	!worm [v(us)]=[fsub(get(v(1),linposx),fsub(get(v(0),linposx),get(v(us),linposx)))],[fsub(get(v(1),linposy),fsub(get(v(0),linposy),get(v(us),linposy)))],[fsub(get(v(1),linposz),fsub(get(v(0),linposz),get(v(us),linposz)))];@zemit get([v(us)]/zone)=The ship shudders once more as it re-enters at the other end of the worm hole.
wormjump():	@zemit get([v(us)]/zone)=A shudder runs through the ship as the worm drive is engaged. A flash of green light is seen.;[ifelse(v(0),wormjump2(v(0),get(v(0),otherside)),s({[owner(me)] @fore zwho(get([v(us)]/zone))=@limbo %%%%%%%%0=%%%%%%%%0;@pe %#=There is no wormhole present!;!exit [v(us)];@tel [v(us)]=#12135;@zemit get([v(us)]/zone)=The ship is ripped apart and scattered across time and space.}))]
PwrRead:	$power:/[v(eng_man)]/@pemit %#=System Power Readout:;@pemit %#=--------------------;@pemit %#;@pemit %#=Generator Status--;@pemit %#=Power Avail: [get(s([v(us)]/pwrgen))] Max: <5000.00>;@pemit %#=Fuel Use: [get(s([get(me/us)]/pwrfuel))] Max: <500>;@pemit %#;@pemit %#=Systems Status--;@pemit %#=Batteries: [get(me/PwrBatt)] <[sub(get(me/MaxBatt),1)]>;@pemit %#=Sensors: [get(me/PwrSense)] <[sub(get(me/MaxSense),1)]>];@pemit %#=Scanners: [get(me/PwrScan)] <[sub(get(me/MaxScan),1)]>;@tr me/PwrRead2=%#
MaxSense:	101
DrnSense:	@pwrgen [get(me/us)]=add(get(me/PwrSense),get(s([get(me/us)]/PwrGen)));@pwrSense me=0;@pemit %0=Power drained from Sensors.
AllSense:	@swi get(me/PwrSense)=*Damaged*,{@pemit %0=Sensors are damaged.},*Destroyed*,{@pemit %0=Sensors are destroyed.},{@swi %[comp(sub(get(me/MaxSense),1),add(get(me/PwrSense),abs(%1)))%]=-1,{@pemit %0=Sensors cannot be charged to that potential.},{@pwrSense me=add(get(me/pwrSense),abs(%1));@pwrgen [get(me/us)]=sub(get(s([get(me/us)]/pwrgen)),abs(%1));@pemit %0=Power Allocated to Sensors.}
PwrRead2:	@pemit %0=Repairs: [get(me/PwrRep)] <[sub(get(me/MaxRep),1)]>;@pemit %0=Beacon: [get(me/PwrBeac)] <[sub(get(me/MaxBeac),1)]>;@pemit %0=Communications: [get(me/PwrComm)] <[sub(get(me/MaxComm),1)]>;@pemit %0=Shield Array: [get(me/PwrShld)] <[sub(get(me/MaxShld),1)]>;@pemit %0=Auxillary: [get(me/PwrAux)] <[sub(get(me/MaxAux),1)]>;@swi get(me/maxweap)=0,{@pemit %0},{@pemit %0=Weapons Grid: [get(me/pwrweap)] <[sub(get(me/maxweap),1)]>;@pemit %0}
Drain:	$Drain *:/[get(s(me/Eng_man))]/@swi %0=*Batter*,{@tr me/DrnBatt=%#},*Comm*,{@tr me/DrnComm=%#},*Sensor*,{@tr me/DrnSense=%#},*Scanner*,{@tr me/DrnScan=%#},*Weapon*,{@tr me/DrnWeap=%#},*Repair*,{@tr me/DrnRep=%#},*Shield*,{@tr me/DrnShld=%#},*Screen*,{@tr me/DrnScrn=%#},*Beacon*,{@tr me/DrnBeac=%#},*Aux*,{@tr me/DrnAux=%#},{@pemit %#=Invalid System.}
Allocate:	$allocate *=*:/[get(s(me/Eng_man))]/@swi %0=*Batter*,{@tr me/AllBatt=%#,%1},*Comm*,{@tr me/AllComm=%#,%1},*Sensor*,{@tr me/AllSense=%#,%1},*Scanner*,{@tr me/AllScan=%#,%1},*Weapon*,{@tr me/AllWeap=%#,%1},*Repair*,{@tr me/AllRep=%#,%1},*Shield*,{@tr me/AllShld=%#,%1},*Screen*,{@tr me/AllScrn=%#,%1},*Beacon*,{@tr me/AllBeac=%#,%1},*Aux*,{@tr me/AllAux=%#,%1},{@pemit %#=Invalid System.}
initfuel_cmd:	$init fuel:/[get(me/eng_man)]/@fuel_start me=get(s(%/us//fuel));@fuel_date me=date();@pemit %#=Fuel Report Initialized.
Fuel_Cmd:	$fuel:/[get(me/eng_man)]/@pemit %#;@pemit %#=Fuel Status --;@pemit %#=Supply: [get(s(%/us//fuel))];@swi [inspace(get(me/us))]=1,{@pemit %#=Usage: [fueltotal(get(s(%/us//thrust)),get(s(%/us//Rating)),get(s(%/us//Efficiency)),get(s(%/us//PwrFuel)),get(s(%/us//PwrGen)))]},{@pemit %#=Usage: None};@wait 1={@pemit %#;@pemit %#=Fuel Report --;@swi [get(me/fuel_date)]=,{@pemit %#=Start Date: Not Initialized;@pemit %#=Consumption: Not Initialized},{@pemit %#=Start Date: [get(me/fuel_date)];@pemit %#=Consumption: [sub(get(me/fuel_start),get(s(%/us//fuel)))]};@pemit %#
airlockstatus:	$airlock status:/[v(eng_man)]/@swi [get([v(us)]/airlock)]=,{@pemit %#=This ship has no airlock.},{@pemit %#=The airlock is %[ifelse(eq(wcount(get([v(us)]/airlock)),1),unsealed,sealed)], %[ifelse(get([v(us)]/lairlock),locked,unlocked)], and %[ifelse(get([v(us)]/airlock_pres),pressurized,depressurized)].}
```

# Legacy Console: ENG

## Name

ENG - Engineering Console

## Purpose

This is the ENG legacy console object, used in older versions of the game to provide engineering capabilities for spacecraft. It includes various engineering functions such as power management, fuel monitoring, system diagnostics, and repairs.

## Meta data

## Object Definition

### Attribute definitions

```mud
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

```mud
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
evalfuel():	[ifelse(gte(5000,v(4)),fadd(fuelcon(v(0),v(1),v(2)),v(3)),fuelcon(v(0),v(1),v(2))]
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
````markdown
# Legacy Console: ENG

## Name

ENG - Engineering Console

## Purpose

This is the ENG legacy console object, used in older versions of the game to provide engineering capabilities for spacecraft. It includes various engineering functions such as power management, fuel monitoring, system diagnostics, and repairs.

## Meta data

## Object Definition

### Attribute definitions

```mud
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

```mud
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
evalfuel():	[ifelse(gte(5000,v(4)),fadd(fuelcon(v(0),v(1),v(2)),v(3)),fuelcon(v(0),v(1),v(2))]
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
````markdown

## English Logic Descriptions (Legacy Attribute List)

### `Engine_cmd` — English description

```text
Attribute: Engine_cmd

Player command (legacy pattern):
- engine
- Access lock: /[get(me/eng_man)]/

Logic:
1) If the console has an engine object set (truth(get(me/engine))=1):
   - Print a multi-line status block showing:
     - Engine object name
     - Ship engine rating (from ship via me/us)
     - Current operating efficiency (efficiency + 1) as a percentage
     - Thrust range (MinThr..MaxThr) stored on the console
2) Else:
   - Print "Engine is disengaged."
```

### `Generate_Cmd` — English description

```text
Attribute: Generate_Cmd

Player command (legacy pattern):
- generate <kiloliters>
- Access lock: /[get(me/eng_man)]/

Logic:
1) Takes an absolute value of the requested fuel conversion rate.
2) If requested rate > 500:
   - Print an error: cannot convert more than 500 kL per update.
3) Else:
   - Set ship pwrfuel (fuel converted per update) to that requested rate.
   - Print confirmation of the new conversion rate.
```

### `PwrRead` / `PwrRead2` — English description

```text
Attribute: PwrRead

Player command (legacy pattern):
- power
- Access lock: /[v(eng_man)]/

Logic:
1) Print a "System Power Readout" header.
2) Print generator status:
   - current ship power generation (pwrgen) and max (5000)
   - current ship fuel conversion rate (pwrfuel) and max (500)
3) Print partial systems status (batteries/sensors/scanners with their current power and max-1).
4) Trigger PwrRead2 to print the remaining systems lines (repairs/beacon/comms/shields/aux, and weapons if installed).

Attribute: PwrRead2
- Emits the remaining system power lines to the same recipient passed in as %0.
- If maxweap=0, omits weapon reporting.
```

### `Allocate` — English description

```text
Attribute: Allocate

Player command (legacy pattern):
- allocate <System>=<Amount>
- Access lock: /[get(s(me/Eng_man))]/

Logic:
1) Pattern-matches the System name against keywords (Batter,Comm,Sensor,Scanner,Weapon,Repair,Shield,Screen,Beacon,Aux).
2) Based on the match, triggers the corresponding All<System> program on this console:
   - @tr me/AllBatt=%#,%1, etc.
3) If no keyword matches:
   - Print "Invalid System."
Notes:
- The All<System> programs implement the real allocation logic (see below).
```

### `Drain` — English description

```text
Attribute: Drain

Player command (legacy pattern):
- Drain <System>
- Access lock: /[get(s(me/Eng_man))]/

Logic:
1) Pattern-matches the System name against the same keyword set as Allocate.
2) Triggers the corresponding Drn<System> program to reclaim allocated power back into ship generation.
3) If no keyword matches:
   - Print "Invalid System."
```

### `All<Subsystem>` family (e.g. `AllBatt`, `AllComm`, `AllScan`, `AllShld`, `AllAux`, etc.) — English description

```text
Attributes: AllBatt,AllComm,AllSense,AllScan,AllRep,AllBeac,AllScrn,AllAux,AllShld,AllWeap

Invocation context:
- Called by Allocate with (player,amount) parameters.

Shared logic pattern:
1) Check subsystem current status string (e.g., get(me/PwrBatt)):
   - If contains "Damaged": print "<Subsystem> are damaged." and stop.
   - If contains "Destroyed": print "<Subsystem> are destroyed." and stop.
2) Capacity check:
   - If adding abs(amount) to current subsystem power would exceed (MaxSubsystem-1):
     print "<Subsystem> cannot be charged to that potential." and stop.
3) Otherwise allocate power:
   - Increase subsystem power on the console by abs(amount).
   - Decrease ship pwrgen by the same amount (pulling from available generation).
   - Print "Power Allocated to <Subsystem>."
Notes:
- These attributes are effectively "charge subsystem from generator" with safety checks.
```

### `Drn<Subsystem>` family (e.g. `DrnBatt`, `DrnComm`, `DrnScan`, etc.) — English description

```text
Attributes: DrnBatt,DrnComm,DrnSense,DrnScan,DrnWeap,DrnRep,DrnShld,DrnScrn,DrnBeac,DrnAux

Invocation context:
- Called by Drain with (player) parameter.

Shared logic pattern:
1) Add the console’s currently allocated subsystem power back into the ship’s pwrgen.
2) Set the console’s subsystem power to 0.
3) Print "Power drained from <Subsystem>."
Notes:
- This is the inverse of allocation: return allocated power to the generator pool.
```

### `fuelcon()` / `evalfuel()` / `fueltotal()` — English description

```text
Attribute: fuelcon()
- Computes a per-update fuel usage rate from:
  abs(thrust) / (rating * efficiency)

Attribute: evalfuel()
- Computes baseline consumption using fuelcon(...).
- If v(4) indicates a high generator state (gte(5000,v(4))):
  adds an additional +v(3) term (generator fuel usage contribution).

Attribute: fueltotal()
- Wraps evalfuel and formats it.
- If HS() (hyperspace) is active, adds an additional 2000 to the reported usage.
```

### `initfuel_cmd` / `Fuel_Cmd` — English description

```text
Attribute: initfuel_cmd

Player command (legacy pattern):
- init fuel
- Access lock: /[get(me/eng_man)]/

Logic:
1) Save a starting fuel snapshot from the ship’s fuel attribute into fuel_start.
2) Save the current date into fuel_date.
3) Print "Fuel Report Initialized."

Attribute: Fuel_Cmd

Player command (legacy pattern):
- fuel
- Access lock: /[get(me/eng_man)]/

Logic:
1) Print current ship fuel supply.
2) If the ship is in space:
   - Print computed fuel usage (fueltotal(...)).
   Else:
   - Print "Usage: None"
3) After a short delay (@wait 1), print a Fuel Report:
   - If fuel_date is unset: report "Not Initialized"
   - Else: show start date and consumption (fuel_start - current fuel).
```

### `Hyper_cmd` — English description

```text
Attribute: Hyper_cmd

Player command (legacy pattern):
- hyperjump
- Access lock: /[get(me/nav_man)]/

Logic:
1) If HS() indicates hyperspace is currently engaged:
   - Trigger Engine/Hyperoff and print disengaging message.
2) Else:
   - Trigger Engine/Hypertest (presumably validates/initiates hyperspace).
```

### `airlockstatus` / `unlockairlock` / `lockairlock` — English description

```text
Attribute: airlockstatus
- Player command: airlock status
- Access lock: /[v(eng_man)]/
- If the ship has no airlock attribute: print "This ship has no airlock."
- Else print a human-readable state summary:
  - sealed vs unsealed
  - locked vs unlocked (lairlock)
  - pressurized vs depressurized (airlock_pres)

Attribute: unlockairlock
- Player command: unlock airlock
- Access lock: /[v(eng_man)]/
- If no airlock: print error.
- Else if already unlocked: print already unlocked.
- Else unlock (clear lairlock) and print success.

Attribute: lockairlock
- Player command: lock airlock
- Access lock: /[v(eng_man)]/
- If no airlock: print error.
- Else if already locked: print already locked.
- Else set lairlock=1 and print success.
```

### `worm_cmd` / `wormjump()` / `wormjump2()` — English description

```text
Attribute: worm_cmd
- Player command: wormjump
- Access lock: /[v(nav_man)]/
- Requires a specific engine type to be engaged (is_a(v(engine),#24225)=1).
- If present, finds a nearby wormhole object (is_a(...,#23318) within 50000) and calls wormjump(target_wormhole).
- Else prints an error about needing a worm drive.

Attribute: wormjump()
1) Emit zone text indicating worm drive engagement.
2) If a wormhole target is present:
   - Call wormjump2(wormhole,otherside).
3) Else:
   - Runs a failure sequence: informs, forces exit/tel/limbo behavior, and emits destruction text.

Attribute: wormjump2()
- Performs a !worm reposition using linear position deltas between wormhole endpoints and the ship.
- Emits zone text about re-entering at the other end.
````markdown

## MARE 2.0 Converted Softcode (from Legacy Attribute list)

```mud
@@ --------------------
@@ Commands
@@ --------------------

&Engine_cmd ENG=:/[get(me,eng_man)]/0$engine:
switch truth(get(me,engine))
  case 1
    print
    print Type: [name(get(me,engine))]
    print Rated at: [get(v(us),rating)]:1
    print Operating at: [add(get(v(us),efficiency),1)]%%%% max eff.
    print Thrust Range: [get(me,MinThr)]-[get(me,MaxThr)]
    print
  default
    print Engine is disengaged.
endswitch


&worm_cmd ENG=:/[v(nav_man)]/0$wormjump:
switch is_a(v(engine),#24225)
  case 1
    @@ Preserve legacy “evaluate function for side effects”
    [wormjump(first(foreach(indist(v(us),50000),[if(is_a(v(0),#23318),v(0))])))]
  default
    print How do you expect to use a worm hole without a worm drive engaged?
endswitch


&Generate_Cmd ENG=:/[get(me,eng_man)]/1$generate:
switch comp(add(0,abs(v(0))),500)
  case 1
    print Generators are unable to convert more than 500 kiloliters per update into energy.
  default
    @pwrfuel v(us)=add(0,abs(v(0)))
    print Generators now converting [add(0,abs(v(0)))] kiloliters of fuel per update into energy.
endswitch


&Hyper_cmd ENG=:/[get(me,nav_man)]/0$hyperjump:
switch HS()
  case 1
    call %/Engine//Hyperoff
    print Disengaging hyperspace envelope.
  default
    call %/Engine//Hypertest
endswitch


&unlockairlock ENG=:/[v(eng_man)]/0$unlock airlock:
switch get(v(us),airlock)=
  case 1
    print This ship has no airlock.
  default
    @@ Legacy had malformed lairlock test; interpret as “already unlocked if lairlock is empty/0”
    switch get(v(us),lairlock)=
      case 1
        print The airlock is already unlocked.
      default
        @lairlock v(us)
        print The airlock is now unlocked for use.
    endswitch
endswitch


&lockairlock ENG=:/[v(eng_man)]/0$lock airlock:
switch get(v(us),airlock)=
  case 1
    print This ship has no airlock.
  default
    switch get(v(us),lairlock)
      case 1
        print Airlock is already locked.
      default
        @lairlock v(us)=1
        print Airlock is now locked in position.
    endswitch
endswitch


&PwrRead ENG=:/[v(eng_man)]/0$power:
print System Power Readout:
print --------------------
print
print Generator Status--
print Power Avail: [get(v(us),pwrgen)] Max: <5000.00>
print Fuel Use: [get(v(us),pwrfuel)] Max: <500>
print
print Systems Status--
print Batteries: [get(me,PwrBatt)] <[sub(get(me,MaxBatt),1)]>
print Sensors: [get(me,PwrSense)] <[sub(get(me,MaxSense),1)]>
print Scanners: [get(me,PwrScan)] <[sub(get(me,MaxScan),1)]>
call me/PwrRead2=%#


&Fuel_Cmd ENG=:/[get(me,eng_man)]/0$fuel:
print
print Fuel Status --
print Supply: [get(v(us),fuel)]
switch inspace(get(me,us))
  case 1
    print Usage: [fueltotal(get(v(us),thrust),get(v(us),Rating),get(v(us),Efficiency),get(v(us),PwrFuel),get(v(us),PwrGen))]
  default
    print Usage: None
endswitch
wait 1
print
print Fuel Report --
switch get(me,fuel_date)=
  case 1
    print Start Date: Not Initialized
    print Consumption: Not Initialized
  default
    print Start Date: [get(me,fuel_date)]
    print Consumption: [sub(get(me,fuel_start),get(v(us),fuel))]
endswitch
print %#


&initfuel_cmd ENG=:/[get(me,eng_man)]/0$init fuel:
@fuel_start me=get(v(us),fuel)
@fuel_date me=date()
print Fuel Report Initialized.


&airlockstatus ENG=:/[v(eng_man)]/0$airlock status:
switch get(v(us),airlock)=
  case 1
    print This ship has no airlock.
  default
    print The airlock is %[ifelse(eq(wcount(get(v(us),airlock)),1),unsealed,sealed)],%[ifelse(get(v(us),lairlock),locked,unlocked)],and%[ifelse(get(v(us),airlock_pres),pressurized,depressurized)].
endswitch


&Drain ENG=:/[get(s(me),Eng_man)]/1$Drain:
switch v(0)
  case *Batter*
    call me/DrnBatt=%#
  case *Comm*
    call me/DrnComm=%#
  case *Sensor*
    call me/DrnSense=%#
  case *Scanner*
    call me/DrnScan=%#
  case *Weapon*
    call me/DrnWeap=%#
  case *Repair*
    call me/DrnRep=%#
  case *Shield*
    call me/DrnShld=%#
  case *Screen*
    call me/DrnScrn=%#
  case *Beacon*
    call me/DrnBeac=%#
  case *Aux*
    call me/DrnAux=%#
  default
    print Invalid System.
endswitch


&Allocate ENG=:/[get(s(me),Eng_man)]/2$allocate:
switch v(0)
  case *Batter*
    call me/AllBatt=%#,[v(1)]
  case *Comm*
    call me/AllComm=%#,[v(1)]
  case *Sensor*
    call me/AllSense=%#,[v(1)]
  case *Scanner*
    call me/AllScan=%#,[v(1)]
  case *Weapon*
    call me/AllWeap=%#,[v(1)]
  case *Repair*
    call me/AllRep=%#,[v(1)]
  case *Shield*
    call me/AllShld=%#,[v(1)]
  case *Screen*
    call me/AllScrn=%#,[v(1)]
  case *Beacon*
    call me/AllBeac=%#,[v(1)]
  case *Aux*
    call me/AllAux=%#,[v(1)]
  default
    print Invalid System.
endswitch


@@ --------------------
@@ Allocation helpers (All*) and Drain helpers (Drn*)
@@ --------------------

&AllBatt ENG=
switch get(me,PwrBatt)
  case *Damaged*
    @pemit v(0)=Batteries are damaged.
  case *Destroyed*
    @pemit v(0)=Batteries are destroyed.
  default
    switch comp(sub(get(me,MaxBatt),1),add(get(me,PwrBatt),abs(v(1))))
      case -1
        @pemit v(0)=Batteries cannot be charged to that potential.
      default
        @pwrbatt me=add(get(me,PwrBatt),abs(v(1)))
        @pwrgen v(us)=sub(get(v(us),pwrgen),abs(v(1)))
        @pemit v(0)=Power Allocated to Batteries.
    endswitch
endswitch


&AllScrn ENG=
switch get(me,PwrScrn)
  case *Damaged*
    @pemit v(0)=Screens is damaged.
  case *Destroyed*
    @pemit v(0)=Screens is destroyed.
  default
    switch comp(sub(get(me,MaxScrn),1),add(get(me,PwrScrn),abs(v(1))))
      case -1
        @pemit v(0)=Screens cannot be charged to that potential.
      default
        @pwrScrn me=add(get(me,PwrScrn),abs(v(1)))
        @pwrgen v(us)=sub(get(v(us),pwrgen),abs(v(1)))
        @pemit v(0)=Power Allocated to Screens.
    endswitch
endswitch


&AllAux ENG=
switch get(me,PwrAux)
  case *Damaged*
    @pemit v(0)=Auxillary is damaged.
  case *Destroyed*
    @pemit v(0)=Auxillary is destroyed.
  default
    switch comp(sub(get(me,MaxAux),1),add(get(me,PwrAux),abs(v(1))))
      case -1
        @pemit v(0)=Auxillary cannot be charged to that potential.
      default
        @pwrAux me=add(get(me,PwrAux),abs(v(1)))
        @pwrgen v(us)=sub(get(v(us),pwrgen),abs(v(1)))
        @pemit v(0)=Power Allocated to Auxillary.
    endswitch
endswitch


&AllBeac ENG=
switch get(me,PwrBeac)
  case *Damaged*
    @pemit v(0)=Beacon Emitter are damaged.
  case *Destroyed*
    @pemit v(0)=Beacon Emitter are destroyed.
  default
    switch comp(sub(get(me,MaxBeac),1),add(get(me,PwrBeac),abs(v(1))))
      case -1
        @pemit v(0)=Beacon Emitter cannot be charged to that potential.
      default
        @pwrBeac me=add(get(me,PwrBeac),abs(v(1)))
        @pwrgen v(us)=sub(get(v(us),pwrgen),abs(v(1)))
        @pemit v(0)=Power Allocated to Beacon Emitter.
    endswitch
endswitch


&AllRep ENG=
switch get(me,PwrRep)
  case *Damaged*
    @pemit v(0)=Repairs are damaged.
  case *Destroyed*
    @pemit v(0)=Repairs are destroyed.
  default
    switch comp(sub(get(me,MaxRep),1),add(get(me,PwrRep),abs(v(1))))
      case -1
        @pemit v(0)=Repairs cannot be charged to that potential.
      default
        @pwrRep me=add(get(me,PwrRep),abs(v(1)))
        @pwrgen v(us)=sub(get(v(us),pwrgen),abs(v(1)))
        @pemit v(0)=Power Allocated to Repairs.
    endswitch
endswitch


&AllWeap ENG=
switch get(me,PwrWeap)
  case *Damaged*
    @pemit v(0)=Weapons Grid are damaged.
  case *Destroyed*
    @pemit v(0)=Weapons Grid are destroyed.
  default
    switch comp(sub(get(me,MaxWeap),1),add(get(me,PwrWeap),abs(v(1))))
      case -1
        @pemit v(0)=Weapons Grid cannot be charged to that potential.
      default
        @pwrWeap me=add(get(me,PwrWeap),abs(v(1)))
        @pwrgen v(us)=sub(get(v(us),pwrgen),abs(v(1)))
        @pemit v(0)=Power Allocated to Weapons Grid.
    endswitch
endswitch


&AllShld ENG=
switch get(me,PwrShld)
  case *Damaged*
    @pemit v(0)=Shield Array are damaged.
  case *Destroyed*
    @pemit v(0)=Shield Array are destroyed.
  default
    switch comp(sub(get(me,MaxShld),1),add(get(me,PwrShld),abs(v(1))))
      case -1
        @pemit v(0)=Shield Array cannot be charged to that potential.
      default
        @pwrShld me=add(get(me,PwrShld),abs(v(1)))
        @pwrgen v(us)=sub(get(v(us),pwrgen),abs(v(1)))
        @pemit v(0)=Power Allocated to Shield Array.
    endswitch
endswitch


&AllScan ENG=
switch get(me,PwrScan)
  case *Damaged*
    @pemit v(0)=Scanners are damaged.
  case *Destroyed*
    @pemit v(0)=Scanners are destroyed.
  default
    switch comp(sub(get(me,MaxScan),1),add(get(me,PwrScan),abs(v(1))))
      case -1
        @pemit v(0)=Scanners cannot be charged to that potential.
      default
        @pwrscan me=add(get(me,PwrScan),abs(v(1)))
        @pwrgen v(us)=sub(get(v(us),pwrgen),abs(v(1)))
        @pemit v(0)=Power Allocated to Scanners.
    endswitch
endswitch


&AllComm ENG=
switch get(me,PwrComm)
  case *Damaged*
    @pemit v(0)=Communications are damaged.
  case *Destroyed*
    @pemit v(0)=Communications are destroyed.
  default
    switch comp(sub(get(me,MaxComm),1),add(get(me,PwrComm),abs(v(1))))
      case -1
        @pemit v(0)=Communications cannot be charged to that potential.
      default
        @pwrcomm me=add(get(me,PwrComm),abs(v(1)))
        @pwrgen v(us)=sub(get(v(us),pwrgen),abs(v(1)))
        @pemit v(0)=Power Allocated to Communications.
    endswitch
endswitch


&AllSense ENG=
switch get(me,PwrSense)
  case *Damaged*
    @pemit v(0)=Sensors are damaged.
  case *Destroyed*
    @pemit v(0)=Sensors are destroyed.
  default
    switch comp(sub(get(me,MaxSense),1),add(get(me,PwrSense),abs(v(1))))
      case -1
        @pemit v(0)=Sensors cannot be charged to that potential.
      default
        @pwrSense me=add(get(me,PwrSense),abs(v(1)))
        @pwrgen v(us)=sub(get(v(us),pwrgen),abs(v(1)))
        @pemit v(0)=Power Allocated to Sensors.
    endswitch
endswitch


&DrnComm ENG=
@pwrgen v(us)=add(get(me,PwrComm),get(v(us),PwrGen))
@pwrComm me=0
@pemit v(0)=Power drained from Communications.


&DrnWeap ENG=
@pwrgen v(us)=add(get(me,PwrWeap),get(v(us),PwrGen))
@pwrWeap me=0
@pemit v(0)=Power drained from Weapons.


&DrnShld ENG=
@@ Legacy bug preserved: drains PwrAux into pwrgen, then clears PwrShld
@pwrgen v(us)=add(get(me,PwrAux),get(v(us),PwrGen))
@pwrShld me=0
@pemit v(0)=Power drained from Shields.


&DrnScrn ENG=
@pwrgen v(us)=add(get(me,PwrScrn),get(v(us),PwrGen))
@pwrScrn me=0
@pemit v(0)=Power drained from Screens.


&DrnRep ENG=
@pwrgen v(us)=add(get(me,PwrRep),get(v(us),PwrGen))
@pwrRep me=0
@pemit v(0)=Power drained from Repairs.


&DrnBeac ENG=
@pwrgen v(us)=add(get(me,PwrBeac),get(v(us),PwrGen))
@pwrBeac me=0
@pemit v(0)=Power drained from Beacon.


&DrnScan ENG=
@pwrgen v(us)=add(get(me,PwrScan),get(v(us),PwrGen))
@pwrScan me=0
@pemit v(0)=Power drained from Scanners.


&DrnBatt ENG=
@pwrgen v(us)=add(get(me,PwrBatt),get(v(us),PwrGen))
@pwrBatt me=0
@pemit v(0)=Power drained from Batteries.


&DrnAux ENG=
@pwrgen v(us)=add(get(me,PwrAux),get(v(us),PwrGen))
@pwraux me=0
@pemit v(0)=Power drained from Auxillary.


&DrnSense ENG=
@pwrgen v(us)=add(get(me,PwrSense),get(v(us),PwrGen))
@pwrSense me=0
@pemit v(0)=Power drained from Sensors.


@@ --------------------
@@ Misc programs / functions / constants from the legacy list
@@ --------------------

&PwrRead2 ENG=
@pemit v(0)=Repairs: [get(me,PwrRep)] <[sub(get(me,MaxRep),1)]>
@pemit v(0)=Beacon: [get(me,PwrBeac)] <[sub(get(me,MaxBeac),1)]>
@pemit v(0)=Communications: [get(me,PwrComm)] <[sub(get(me,MaxComm),1)]>
@pemit v(0)=Shield Array: [get(me,PwrShld)] <[sub(get(me,MaxShld),1)]>
@pemit v(0)=Auxillary: [get(me,PwrAux)] <[sub(get(me,MaxAux),1)]>
switch get(me,maxweap)
  case 0
    @pemit v(0)
  default
    @pemit v(0)=Weapons Grid: [get(me,pwrweap)] <[sub(get(me,maxweap),1)]>
    @pemit v(0)
endswitch


&fuelcon() ENG=[fdiv(abs(v(0)),fmul(v(1),fdiv(v(2),1)))]

&evalfuel() ENG=[ifelse(gte(5000,v(4)),fadd(fuelcon(v(0),v(1),v(2)),v(3)),fuelcon(v(0),v(1),v(2)))]

&fueltotal() ENG=[simp(ifelse(hs(),fadd(evalfuel(v(0),v(1),v(2),v(3),v(4)),2000),evalfuel(v(0),v(1),v(2),v(3),v(4))))]


&wormjump2() ENG=
!worm [v(us)]=[fsub(get(v(1),linposx),fsub(get(v(0),linposx),get(v(us),linposx)))],[fsub(get(v(1),linposy),fsub(get(v(0),linposy),get(v(us),linposy)))],[fsub(get(v(1),linposz),fsub(get(v(0),linposz),get(v(us),linposz)))]
@zemit get(v(us),zone)=The ship shudders once more as it re-enters at the other end of the worm hole.


&wormjump() ENG=
@zemit get(v(us),zone)=A shudder runs through the ship as the worm drive is engaged. A flash of green light is seen.
[ifelse(v(0),wormjump2(v(0),get(v(0),otherside)),s({[owner(me)] @fore zwho(get(v(us),zone))=@limbo %%%%%%%%0=%%%%%%%%0;@pe %#=There is no wormhole present!;!exit [v(us)];@tel [v(us)]=#12135;@zemit get(v(us),zone)=The ship is ripped apart and scattered across time and space.}))]


&MaxScan ENG=501
&MaxAux ENG=201
&MaxBeac ENG=51
&MaxWeap ENG=0
&PwrWeap ENG=0
&MaxShld ENG=801
&PwrBatt ENG=1000
&MaxBatt ENG=2001
&MaxRep ENG=101
&MaxComm ENG=1001
&MaxSense ENG=101
```





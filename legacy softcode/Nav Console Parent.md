# Nav Console Parent

## Name

Nav Console Parent - Navigation Console

## Purpose

This is the Navigation Console parent object, used in the game to provide players with navigation capabilities for spacecraft. It allows players to manage ship speed, set targets, and monitor distances to other objects in space.

## Meta data

Parents:	Coords Parent(#1100h)

## Object Definition

### Attribute definitions

```mud
ship_obj: inherit program
ship_speed(): inherit function
set_speed: inherit program
target_dbref: inherit program
plane_check: inherit program
target_plane: inherit program
timer: inherit program
notes: inherit program
cKMPH: inherit program
last_dist: inherit program
update_dist: inherit program
check_dist: inherit program
check_plane: inherit program
target_dist(): inherit function
ship_dist(): inherit function
speed_cmd(): inherit function
KperMin(): inherit function
KperSec(): inherit function
list_ships: inherit program
vi_desc: program
nonvi_desc: program
ship_plane(): inherit function
burn: inherit program
burn_rate: inherit program
burn_start: inherit program
burn_end: inherit program
burn_check: inherit program
nav_help: inherit program
nav_settings: inherit program
settings_info: inherit program
VelX: inherit program
VelY: inherit program
VelZ: inherit program
consumption(): inherit function
nav_consumption(): inherit function
ship_sector(): inherit function
launch_cmd: inherit program
Vt: inherit program
```

### Attribute list

```mud
notes:	All speeds are kmph for for shortness.
cKMPH:	107900000
KperSec():	[fdiv(kpermin(),60)]
KperMin():	[fdiv(v(ship_speed),60)]
ship_dist():	[s(dist3d(get(ship_sector(),Linposx),get(ship_sector(),linposy),get(ship_sector(),linposz),get(v(0),linposx),get(v(0),linposy),get(v(0),linposz)))]
target_dist():	[s(dist3d(get(ship_sector(),Linposx),get(ship_sector(),linposy),get(ship_sector(),linposz),get(v(target_dbref),linposx),get(v(target_dbref),linposy),get(v(target_dbref),linposz)))]
set_speed:	$set speed:@pe %#=Possible Options. NULL to turn Engines off. Any number under C in KMPHs%R;@input %#=me/speed_cmd: Type in your entry now:
speed_cmd():	@switch 1=[gteq(v(0),107900000)],{@pe %#=Sorry No setting over C.},[isword(v(0))],{@pe %#=Very Naughty},{@ship_speed me=[v(0)];@pe %#=[name(me)] chirps, "Acknowledged %N!"%R[name(me)] chirps, "Speed set to [v(0)] KMPH."}
Desc:	[white(Current Navigation Settings for:)]%R[white(Starship)] : [cname(v(ship_obj)]%R[yellow(Name Of Target)] : [cname(v(target_dbref))]%R[yellow(Distance to target)] : [lcyan(ljust(round(fsub(target_dist(),ship_dist(v(ship_obj))),4),30))]%R[yellow(Targ Dist 2 Star)] : [ljust(round(target_dist(),4),15)]%R[yellow(Dist 2 Star)] : [dgray(ljust(round(ship_dist(v(ship_obj)),4),15))]%R[yellow(Target X Coords)] : [lgreen(ljust(get(v(target_dbref),Linposx),15))]%R[yellow(Current X Vector)] : [yellow(ljust(get(v(ship_obj),Linposx),15))]%R[yellow(Offset X)] : [lred(ljust(fsub(get(v(target_dbref),Linposx),get(v(ship_obj),Linposx)),15))]%R[yellow(Time at X Vel)] : [lpurple(ljust(fdiv(fsub(get(v(target_dbref),Linposx),get(v(ship_obj),Linposx)),get(v(ship_obj),linvelx)),15))]%R[yellow(Target Y Coords)] : [lgreen(ljust(get(v(target_dbref),linposy),15))]%R[yellow(Current Y Vector)] : [yellow(ljust(get(v(ship_obj),linposy),15))]%R[yellow(Offset Y)] : [lred(ljust(fsub(get(v(target_dbref),Linposy),get(v(ship_obj),Linposy)),15))]%R[yellow(Time at Y Vel)] : [lpurple(ljust(fdiv(fsub(get(v(target_dbref),Linposy),get(v(ship_obj),Linposy)),get(v(ship_obj),linvely)),15))]%R[yellow(Target Z Coords)] : [lgreen(ljust(get(v(target_dbref),linposz),15))]%R[yellow(Current Z Vector)] : [yellow(ljust(get(v(ship_obj),linposz),15))]%R[yellow(Offset Z)] : [lred(ljust(fsub(get(v(target_dbref),Linposz),get(v(ship_obj),Linposz)),15))]%R[yellow(Time at Z Vel)] : [lpurple(ljust(fdiv(fsub(get(v(target_dbref),Linposz),get(v(ship_obj),Linposz)),get(v(ship_obj),linvelz)),15))]%R[yellow(Arrival At Cruise)] : [green(s(abs(round(fdiv(fsub(ship_dist(v(ship_obj)),target_dist()),ship_speed()),2)))] Hrs. 24h Conv [s(abs(round(fdiv(fdiv(fsub(ship_dist(v(ship_obj)),target_dist()),ship_speed(),24),2))))] %R[yellow(Current Speed in C)] : [lcyan(round(fmul(fdiv(ship_speed(),v(cKMPH)),100),4))] %% of C.%R[yellow(Current Speed KMPH)] : [cyan(ship_speed())] KM per Hour.%R[yellow(Current X Velocity)] : [lblue(get(v(ship_obj),Linvelx))]%R[yellow(Current Y Velocity)] : [lpurple(get(v(ship_obj),linvely))]%R[yellow(Current Z Velocity)] : [yellow(get(v(ship_obj),linvelz))]%R
target_dbref:	#44086
OnMinute:	@tr me/burn_check
#1100.system():	[name(loc(v(ship_obj)))]
ship_plane():	[plane(v(ship_obj)]
burn_start:	$burn *=*:@switch [lor(v(0),x,y)]=1,{@burn me=[v(0)];@burn_rate me=[v(1)];@pe %#=Burn Rate Set to: [ucstr(v(0))] at [v(1)] Per Min},{@pe %#=Sorry Burn must be in X/Y=number where number represents per min adjustment.}
burn_end:	$burn end:@burn me=0;@pe %#=Burn Off
Vt:	Optimum-burn_check:@switch [v(burn)]=0,{},{@[v(burn)]_coord [v(ship_obj)]=[get(v(ship_obj),%[get(me,burn)]_coord)],[v(burn_rate))]}
burn:	0
OnLook:	@pe %#=Type '[white(nav help)]' for valid commands.
nav_help:	$nav help:@pe %#=[white(Navigation Help:)]%Rvel * value : Set burn per minute direction x/y/z number.%Rlist coords : List of valid targets%Rlist ships : List of ships in system%R
nav_settings:	$settings:@switch [immortal(v(#))]=1,{@pe %#=[v(settings_info)]},{@pe %#=Caspian looked at you.}
settings_info:	[lcyan(Settings for:)] [cname(me)] ([num(me)])%R@ship_obj [num(me)]=[v(ship_obj)] : Set this to Dbref# of ship hull.%R[red(---Set by Child--- Provided for Debug only :)]%R@ship_speed [num(me)]=[v(ship_speed)] : Speed in KPMH%R@last_dist [num(me)]=[v(last_dist)] : Distance to Star%R@target_dbref [num(me)]=[v(target_dbref)] : Dbref of Traget Object%R@burn [num(me)]=[v(burn)] : Should be set to X/Y/Z or 0 only%R@burn_rate [num(me)]=[v(burn_rate)] : Any numeric value or 0%R
last_dist:	5756770.592118554
VelX:	$vel x *:@Linvelx [v(ship_obj)]=[secure(v(0))]
VelY:	$vel y *:@Linvely [v(ship_obj)]=[secure(v(0))]
VelZ:	$vel z *:@Linvelz [v(ship_obj)]=[secure(v(0))]
burn_check:	@Linposx [v(ship_obj)]=[s(fadd(get(v(ship_obj),Linposx),get(v(ship_obj),Linvelx))];@Linposy [v(ship_obj)]=[s(fadd(get(v(ship_obj),Linposy),get(v(ship_obj),Linvely))];@Linposz [v(ship_obj)]=[s(fadd(get(v(ship_obj),Linposz),get(v(ship_obj),Linvelz))];@switch [plane(v(ship_obj))]=[s(round(fmul(dist3d(get(#51991,Linposx),get(#51991,linposy),get(#51991,linposz),get(v(ship_obj),linposx),get(v(ship_obj),linposy),get(v(ship_obj),linposz)),.00001),0))],{},{@plane [v(ship_obj)]=[s(round(fmul(dist3d(get(#51991,Linposx),get(#51991,linposy),get(#51991,linposz),get(v(ship_obj),linposx),get(v(ship_obj),linposy),get(v(ship_obj),linposz)),.00001),0))]}
consumption():	[s(fmul(fadd(fadd(get(v(ship_obj),Linvelx),abs(get(v(ship_obj),linvely))),abs(get(v(ship_obj),linvelz))),.00001)]
ship_speed():	[s(fadd(fadd(abs(get(v(ship_obj),Linvelx)),abs(get(v(ship_obj),linvely))),abs(get(v(ship_obj),linvelz)))]
nav_consumption():	[s(fmul(fadd(fadd(get(v(ship_obj),Linvelx),abs(get(v(ship_obj),linvely))),abs(get(v(ship_obj),linvelz))),.00001)]
ship_sector():	[get(loc(v(ship_obj)),star)]
launch_cmd:	$launch:@fo [v(ship_obj)]=launch
```

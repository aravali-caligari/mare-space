# Legacy Console: SRP

## Name

SRP - Spacecraft 

## Purpose

This is the SRP legacy console object, used in older versions of the game to provide remote programming capabilities for spacecraft. It includes various functions such as navigation, science, engineering, communications, and tactical operations.

## Meta data

## Object Definition

### Attribute definitions

```mud
official_helm: inherit program
setoffset_cmd: inherit program
setoffset: inherit program
offsetobj: inherit program
offsetvel: inherit program
offsetpos: inherit program
by_space_exit(): inherit function
unman_check(): inherit function
man_lname(): inherit function
man_sname(): inherit function
_attrdef16(): inherit function
olddock_cmd: program
MaxRet: inherit program
retrorange(): inherit function
burn_fun: inherit program
ThrustRange(): inherit function
Emote: inherit program
Land: program
launch: inherit program
Burn_cmd: inherit program
Nav_man: program
Sci_man: program
Eng_man: program
Com_man: program
Tac_man: program
Man_cmd: inherit program
Add_list: inherit program
Man_list: program
Unman_cmd: inherit program
Stations_cmd: inherit program
Unman_fun: inherit program
Nav_srp_cmd: inherit program
Nav_srp_1: inherit program
Nav_srp_2: inherit program
Nav_srp_3: inherit program
Nav_srp_4: inherit program
Nav_srp_5: inherit program
NBurn_cmd: inherit program
Nav_srp_h: inherit program
Clear: inherit program
Dock_cmd: inherit program
Nav_srp_6a: inherit program
Nav_srp_6b: inherit program
Retro_cmd: inherit program
nav_srp_7: inherit program
_OnHear: inherit program
srpvel(): inherit function
srppos(): inherit function
srptarget
srpdata
testcmd: inherit program
```

### Attribute list

```mud
official_helm:	Yes
Nav_srp_6b:	Deacceleration: [fabs(get(s([get(me/us)]/mainburnacc)))]km/s^2 % Retro: [abs(get(s([get(me/us)]/mainburn)))]% N % Mass: [get(get(me/us),mass)]kg
Nav_srp_6a:	Acceleration: [get(s([get(me/us)]/mainburnacc))]km/s^2 % Thrust: [abs(get(s([get(me/us)]/mainburn)))]N % Mass: [get(get(me/us),mass)]kg
nav_srp_7:	% % % % % Xi |[vmag(srppos())][mid(vmag(srpvel()),1,12)] % % 0.000 % % Rho | [v2e(srpvel())]
Nav_srp_1:	% % % % % % % % % % % % % % % % % % Position % % % Velocity % % % % Acl % % % % % % % % % % % % Pos % % % % Vel % % % % Acl
Nav_srp_2:	% % % % % % % % o------------------------------------- % % % % % % o------------------------
Nav_srp_3:	% % % % Chi |[rjust(extract(srppos(),1,1),17)] [rjust(extract(srpvel(),1,1),11)] [rjust(extract(get(s([get(me/us)]/acc)),1,1),7)] Theta | [rjust(extract(get(s([get(me/us)]/attpos)),1,1),7)] [rjust(extract(get(s([get(me/us)]/attvel)),1,1),7)] [rjust(extract(get(s([get(me/us)]/attacc)),1,1),7)]
Nav_srp_4:	Upsilon | [rjust(extract(srppos(),2,1),17)] [rjust(extract(srpvel(),2,1),11)] [rjust(extract(get(s([get(me/us)]/acc)),2,1),7)] % % Phi | [rjust(extract(get(s([get(me/us)]/attpos)),2,1),7)] [rjust(extract(get(s([get(me/us)]/attvel)),2,1),7)] [rjust(extract(get(s([get(me/us)]/attacc)),2,1),7)]
Nav_srp_5:	% % % Zeta |[rjust(extract(srppos(),1,1),17)] [rjust(extract(srpvel(),3,1),11)] [rjust(extract(get(s([get(me/us)]/acc)),3,1),7)] % % Psi | [rjust(extract(get(s([get(me/us)]/attpos)),3,1),7)] [rjust(extract(get(s([get(me/us)]/attvel)),3,1),7)] [rjust(extract(get(s([get(me/us)]/attacc)),3,1),7)]
Nav_srp_cmd:	:$srp:/[get(s(me/Nav_man))]/@pe %#=Stellar Reference Position From [histname(v(!),v(offsetobj))];@pe %#;@pe %#=get(me/Nav_srp_h);@pe %#=get(me/Nav_srp_1);@pe %#=get(me/Nav_srp_2);@pe %#=get(me/Nav_srp_3);@pe %#=get(me/Nav_srp_4);@pe %#=get(me/Nav_srp_5);@pe %#=get(me/Nav_srp_7);@pe %#;@pe %#=ifelse(add(1,sgn(get([v(us)]/mainburn))),v(Nav_srp_6a),v(Nav_srp_6b));@pe %#
offsetobj:	#51991
offsetvel:	0.00 0.03 0.00
offsetpos:	180 21989 198
setoffset:	@srpdata me=[relstate(get(me/us),%0)];@offsetpos=[getkey(v(srpdata),:)]; @offsetvel=[getkey(v(srpdata),vel,:)];@offsetobj me=v(0);@pemit v(nav_man)={SRP centered now off of [histname(v(!),v(0))]}
setoffset_cmd:	$srp from *:/[v(nav_man)]/@swi [histnum(v(!),v(0))]|[if(issensed(v(us),histnum(v(!),v(0)),y)]=#*|y,{@tr me/setoffset=[histnum(v(!),v(0))]},#*|,{@pemit %#={'%0' is currently out of sensor range.}},{@pemit %#={'%0' does not exist as a sensor contact.}}
Unman_cmd:	:$unman:
@pemit %#=Ok.
@foreach [unman_check(v(#))]={@%%0_man me;@emit {%n unmans the %[man_lname(v(0))] Station.}}
@ed me/man_list=%#
unman_check():	[if(match(v(nav_man),v(0)),Nav)] [if(match(v(sci_man),v(0)),Sci)] [if(match(v(com_man),v(0)),Com)] [if(match(v(eng_man),v(0)),Eng)] [if(match(v(tac_man),v(0)),Tac)]
Man_cmd:	:$man:
switch [man_check?(v(#),v(0))]
 -1: @pemit %#=You are already manning a station.
 0: @pemit %#=That station is already being manned by %[name(v(s(%[man_sname(v(0))]_man)))].
 x: @pemit %#=That is not a valid station.
default:
 @%[man_sname(v(0))]_man me=%#
 @emit %n mans the %[man_lname(v(0))] Station.
 @man_list me=join(v(man_list),v(#))}
endswitch
_attrdef16():	[ifelse(wmatch(v(man_list),v(0)),-1,ifelse(match(man_sname(v(1)),xxx),x,ifelse(truth(v(s([man_sname(v(1))]_man))),0,1)))]
man_lname():	[ifelse(match(v(0),S*),Science,ifelse(match(v(0),N*),Navigation,ifelse(match(v(0),E*),Engineering,ifelse(match(v(0),C*),Communication,ifelse(match(v(0),T*),Tactical,XXX)))))]
man_sname():	[ifelse(match(v(0),S*),Sci,ifelse(match(v(0),N*),Nav,ifelse(match(v(0),E*),Eng,ifelse(match(v(0),C*),Com,ifelse(match(v(0),T*),Tac,XXX)))))]
Dock_cmd:	$dock *:@swi histnum(v(!),v(0))=#-1,{@nemit %#=There is no such contact as '%%0'},{@pemit %#=Attempting dock with '[histname(v(!),histnum(v(!),v(0)))]'.;@sppark [v(us)]=[histnum(v(!),v(0))],DockedInHangar}
olddock_cmd:	$dock *:@swi histnum(v(!),v(0))=#-1,{@nemit %#=There is no such contact as '%%0'},{@pemit %#=Attempting dock with '[histname(v(!),histnum(v(!),v(0)))]'.;!dock [v(us)]=[histnum(v(!),v(0))]}
burn_fun:	@mainburn get(me/us)=%0;@efficiency get(me/us)=fsub(get(s(%/us//efficiency)),.2);@burntimer get(me/us)=-1
ThrustRange():	[land(lor(gt(v(MaxThr),v(0)),match(v(MaxThr),v(0))),lor(lt(v(MinThr),v(0)),match(v(MinThr),v(0))))]
Unman_fun:	@foreach [unman_check(v(0))]={@%%0_man me;@emit {[name(v(0))] unmans the %[man_lname(v(0))] Station.}};@ed me/man_list=%0,
Nav_srp_h:	Linear: % % % % % % % % % % % % % % % % % % % % % % % % % % % % % % % % % % % % % % % Angular:
_OnHear:	@swi %1=disconnected,@tr me/unman_fun=%#,left,@tr me/unman_fun=%#
Stations_cmd:	:$stations:
@pemit %#
@pemit %#=Stations currently manned:
@pemit %#;@pemit %#=Nav: [name(get(me/nav_man))]
@pemit %#=Sci: [name(get(me/sci_man))]
@pemit %#=Eng: [name(get(me/eng_man))]
@pemit %#=Com: [name(get(me/com_man))]
@pemit %#=Tac: [name(get(me/tac_man))]
@pemit %#
Add_list:	@Man_list me=[get(s(me/Man_list))] [v(0)]
Emote:	switch %0=*nav*
 @pemit [get(me/nav_man)]=v(1)}
*sci*
 @pemit [get(me/sci_man)]=v(1)},
*eng*
{@pemit [get(me/eng_man)]=v(1)},
*com*,
{@pemit [get(me/com_man)]=v(1)},
*tac*
{@pemit [get(me/tac_man)]=v(1)}
default
 {@pemit #5745=Emote ERROR on [num(me)].
endswitch
retrorange():	[land(lor(gt(v(MaxRet),v(0)),match(v(MaxRet),v(0))),lt(0,v(0)))]
Retro_cmd:	:/[v(nav_man)]/$retro:
if [v(mainburn)]=>0
 @pemit %#=The Main Engines need to be shut down first.
else
 if [truth(%0)]=0
  @emit Shutting off Retro Rockets.
 else
  @mainburn get(me/us)=0
  @burntimer get(me/us)=-1
 endif
 if [retrorange(%0)]=0
  @pemit %#=Out of retro range.
 else
  @emit Firing Retro Rockets at [v(0)]npu.
  @mainburn v(us)=-%0
  @burntimer v(us)=-1
 endif
endif
Burn_cmd:	«program»
Clear:	:$clear:
if [man_sname(v(0))]=xxx
 @pemit %#=That is not a valid station
else
 @emit %n rudely boots %[name(v([man_sname(v(0))]_man))] out of the [man_lname(v(0))] Station.
 @tr me/unman_fun={%[ifelse(v([man_sname(v(0))]_man),v([man_sname(v(0))]_man),#-1)]}
endif
launch:	:/[v(nav_man)]/$launch:
if instation(v(us))=0
 print You have to be parked to launch.
else
 print Launching ship...standby.
 sleep 5
 @force v(us)=@spunpark [v(us)]
endif
MaxRet:	100000
srppos():	[ifelse(InFTL(v(us)),?,simp(vsub(get(v(us),pos),v(offsetpos))))]
srpvel():	[ifelse(InFTL(v(us)),?,simp(vsub(get(v(us),vel),v(offsetvel))))]
```

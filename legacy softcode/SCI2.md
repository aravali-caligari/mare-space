# Legacy Console: SCI2

## Name

SCI2 - Advanced Science and Scanning Console

## Purpose

This is the SCI2 legacy console object, used in older versions of the game to provide advanced scanning capabilities for spacecraft. It includes various scanning functions such as navigation scans, engineering scans, tactical scans, and memory sensing.

## Meta data

```mud
Name: SCI2
Type:	Thing
```

## Object Definition

### Attribute definitions

```mud
sciscan: inherit program
sciscan_cmd: inherit program
generalscan: inherit program
scanarea: inherit program
Scanrange(): inherit function
memorysense: inherit program
memorybasic_readout(): inherit function
memorysense_header(): inherit function
memorysense_line1(): inherit function
memorysense_line2(): inherit function
memorysense_line3(): inherit function
memorysense_line4(): inherit function
memoryextra_sense_info(): inherit function
memoryapproach(): inherit function
scan_extra1(): inherit function
scan_extra2(): inherit function
scan_extra3(): inherit function
scan_velocity(): inherit function
scan_relative(): inherit function
navscan: inherit program
navscan_cmd: inherit program
engscan1(): inherit function
engscan2(): inherit function
engscan3(): inherit function
engscan4(): inherit function
engscan: inherit program
engscan_cmd: inherit program
memorysense_line5(): inherit function
memorysense_orbit1(): inherit function
memorysense_orbit2(): inherit function
sensor_event: inherit program
visual_event: inherit program
scancost: inherit program
memorysense_age(): inherit function
tacscan(): inherit function
tacscan_cmd: inherit program
```

### Attribute list

```mud
scan_extra1():	<-------- Theta --------+--------- Phi -----------+--------- Psi --------->
scan_extra2():	Pos Vel Acl | Pos Vel Acl | Pos Vel Acl
navscan:	@tr me/scancost=%0,%1,%2;@pe %2=basic_readout(v(us),v(0),v(1));@pe %2;@pe %2=join(sense_header(),scan_relative(v(us),v(0),v(1)));@pe %2=sense_line1(v(us),v(0),v(1));@pe %2=join(sense_line2(v(us),v(0),v(1)),scan_velocity(v(us),v(0),v(1)));@pe %2=sense_line3(v(us),v(0),v(1));@pe %2=sense_line4(v(us),v(0),v(1));@pe %2=sense_line5(v(us),v(0),v(1));@pe %2=scan_extra1();@pe %2=scan_extra2(v(us),v(0),v(1));@pe %2=scan_extra3(v(us),v(0),v(1));@pe %2=scan_extra1()
scan_extra3():	[rjust(get(s(%1/angposx)),7)] [rjust(get(s(%1/angvelx)),8)] [rjust(get(s(%1/angaccx)),8)]|[rjust(get(s(%1/angposy)),7)] [rjust(get(s(%1/angvely)),8)] [rjust(get(s(%1/angaccy)),8)]|[rjust(get(s(%1/angposz)),7)] [rjust(get(s(%1/angvelz)),8)] [rjust(get(s(%1/angaccz)),8)]
scanarea:	$scan area:/[get(me/sci_man)]/@swi comp(100,get(me/pwrscan))=1,{@pemit %#=There is not enough power available to scanners.},{@pwrscan me=add(get(me/pwrscan),-100);@pemit %#=Initiating Area Scan.;@foreach [indist(v(us),get(me/maxrange))] #=@swi v(0)=#,{@fo me=@fo me=@fo me=@fo me=@fo me=@fo me={@pemit %#=Area Scan Completed.;!senevent Scanner Sweep=[mul(get(me/maxrange),2)],[get(s([v(us)]/linposx))],[get(s([v(us)]/linposy))],[get(s([v(us)]/linposz))]}},{@tr me/check_history=v(0),v(#)}
visual_event:	[switch(v(0),{Weaponfire #*},if(lnot(match(rest(v(0)),v(us))),{@emit Weapon fire}),{Weapondie #*},{@emit Weapon explosion},{Died #*},if(lnot(match(rest(v(0)),v(us))),{@emit Ship explosion}),{})] detected, heading: [velhdg(dx(rest(v(0)),v(us)),dy(rest(v(0)),v(us)),dz(rest(v(0)),v(us)))]
memoryextra_sense_info():	Radius:[rjust(word(v(1),13),10)]km VisualSize: [first(velhdg(word(v(1),2),word(v(1),13),0))]Deg % Mass:[word(v(1),12)]kg Gravity: [simp(fdiv(fmul(6.67e-18,word(v(1),12)),pow(word(v(1),2),2)))]
tacscan():	@tr me/scancost=%0,%1,%2;@pe %2=basic_readout([v(us)],%0,%1);@pe %2;@pe %2=Onboard Weaponry: [ifelse(stringeq(get(get(v(0),helm),tac_weaponlist1),NO MATCH),None,namelist(get(get(v(0),helm),tac_weaponlist1)))];@pe %2;@pe %2=engscan3([v(us)],%0,%1);@pe %2=engscan4([v(us)],%0,%1);;@pe %2;@pe %2=extra_sense_info([v(us)],%0,%1)
tacscan_cmd:	$scan tac=*:/[get(me/sci_man)]/@swi get(v(sensor_memory),strcat(name,v(0)))=NO MATCH,{@pemit %#='%0' does not exist as a sensor contact.},{@swi wmatch(indist(v(us),v(maxrange)),histnum(v(!),v(0)))=0,{@pemit %#='%0' is currently out of Scanner Range.},{@swi hasenergy?(v(!),pwrscan,10)=0,{@pemit %#=There is no power available for a scan. Allocate power to scanners.},{[tacscan(histnum(v(!),v(0)),histname(v(!),histnum(v(!),v(0))),v(#))]}}
engscan_cmd:	$scan eng=*:/[get(me/sci_man)]/@swi get(v(sensor_memory),strcat(name,v(0)))=NO MATCH,{@pemit %#='%0' does not exist as a sensor contact.},{@swi wmatch(indist(v(us),v(maxrange)),histnum(v(!),v(0)))=0,{@pemit %#='%0' is currently out of Scanner Range.},{@swi hasenergy?(v(!),pwrscan,10)=0,{@pemit %#=There is no power available for a scan. Allocate power to scanners.},{@tr me/engscan=[histnum(v(!),v(0))],[histname(v(!),histnum(v(!),v(0)))],%#}}
navscan_cmd:	$scan nav=*:/[get(me/sci_man)]/@swi get(v(sensor_memory),strcat(name,v(0)))=NO MATCH,{@pemit %#='%0' does not exist as a sensor contact.},{@swi wmatch(indist(v(us),v(maxrange)),histnum(v(!),v(0)))=0,{@pemit %#='%0' is currently out of Scanner Range.},{@swi hasenergy?(v(!),pwrscan,10)=0,{@pemit %#=There is no power available for a scan. Allocate power to scanners.},{@tr me/navscan=[histnum(v(!),v(0))],[histname(v(!),histnum(v(!),v(0)))],%#}}
sensor_event:	@swi v(0)=Scan #*,{@swi rest(v(0))=v(us),,{%[ifelse(truth(v(sci_man)),{@pemit v(sci_man)=*BEEP* Active scan coming from:},{@emit An indicator light beeps on the Science console, indicating an active scan coming from:})] %[velhdg(dx(rest(v(0)),v(us)),dy(rest(v(0)),v(us)),dz(rest(v(0)),v(us)))]}},xxx,{xx2},xx3,{xx4}
scancost:	@tr me/write_memory=%0,[sensor_record(v(us),v(0))],%2,sensor;@pwrscan me=add(v(pwrscan),-10);!senevent Scan [v(us)]=[mul(v(maxrange),2)],[get(s([v(us)]/linposx))],[get(s([v(us)]/linposy))],[get(s([v(us)]/linposz))]
memorysense_line5():	Rho [rjust(join(word(v(1),10),word(v(1),11))15)] |[rjust(velhdg(word(v(1),6),word(v(1),7),word(v(1),8))15)] | Tangent Velocity: [velmag(fmul(sin(dg2rd(memoryapproach(v(0),v(1)))),velmag(word(v(1),6),word(v(1),7),word(v(1),8))),0,0)]kpu
memorysense_orbit1():	Energy Apogee Perigee Eccen. Period
memorysense_orbit2():	Orbital Parameters: [orbit(word(v(1),12),word(v(1),2),velmag(word(v(1),6),word(v(1),7),word(v(1),8)),memoryapproach(v(0),v(1)))]
memorysense_line4():	Xi [rjust(word(v(1),2),15)] |[rjust(simp(velmag(word(v(1),6),word(v(1),7),word(v(1),8))),15)] | Closing Velocity:[ifelse(add(fsgn(cos(dg2rd(memoryapproach(v(0),v(1))))),1),+,-)][velmag(fmul(cos(dg2rd(memoryapproach(v(0),v(1)))),velmag(word(v(1),6),word(v(1),7),word(v(1),8))),0,0)]kpu
memorysense_line1():	Chi [rjust(word(v(1),3),15)] |[rjust(word(v(1),6),15)] | Approach Bearing: [memoryapproach(v(0),v(1))]
memorybasic_readout():	Memory: [ljust(histname(v(!),v(0)),15)] Distance:[rjust(word(v(1),2),12)] km Abs. Bearing: [word(v(1),10)] [word(v(1),11)]
memoryapproach():	[relphi(word(v(1),3),word(v(1),4),word(v(1),5),word(v(1),6),word(v(1),7),word(v(1),8))]
memorysense_line3():	Zeta [rjust(word(v(1),5),15)] |[rjust(word(v(1),8),15)] |
memorysense_line2():	Upsilon [rjust(word(v(1),4),15)] |[rjust(word(v(1),7),15)] |
Scanrange():	[land(lnot(wmatch(v(0),v(1))),bnot(comp(get(me/maxrange),dist3d(get(s(%1/linposx)),get(s(%1/linposy)),get(s(%1/linposz)),get(s(%0/linposx)),get(s(%0/linposy)),get(s(%0/linposz))))))]
scan_velocity():	Velocity Heading: [velhdg(get(s(%1/linvelx)),get(s(%1/linvely)),get(s(%1/linvelz)))]
scan_relative():	Relative Bearing: [relhead(v(0),get(s(%1/linposx)),get(s(%1/linposy)),get(s(%1/linposz)))]
engscan1():	Energy Output: [get(s(%1/energy))]kj Acceleration: [get(s(%1/acceleration))]kpu/pu
engscan3():	Shield Output S0:[rjust(get(s(%1/s0)),5)] S1:[rjust(get(s(%1/s1)),5)] S2:[rjust(get(s(%1/s2)),5)] S3:[rjust(get(s(%1/s3)),5)] S4:[rjust(get(s(%1/s4)),5)]
engscan4():	S5:[rjust(get(s(%1/s5)),5)] S6:[rjust(get(s(%1/s6)),5)] S7:[rjust(get(s(%1/s7)),5)] S8:[rjust(get(s(%1/s8)),5)] S9:[rjust(get(s(%1/s9)),5)]
engscan2():	Active Engine Type: [ifelse(truth(get(s([get(s(%1/helm))]/engine))),name(get(s([get(s(%1/helm))]/engine))),N/A)]
engscan:	@tr me/scancost=%0,%1,%2;@pemit %2=basic_readout(v(us),v(0),v(1));@pemit %2;@pemit %2=engscan1(v(us),v(0),v(1));@pemit %2=engscan2(v(us),v(0),v(1));@pemit %2=engscan3(v(us),v(0),v(1));@pemit %2=engscan4(v(us),v(0),v(1));@pemit %2;@pemit %2=extra_sense_info(v(us),v(0),v(1))
memorysense:	@pemit %2=memorybasic_readout(v(0),v(1));@pemit %2=memorysense_age(v(0),v(1));@pemit %2=memorysense_header(v(0),v(1));@pemit %2=memorysense_line1(v(0),v(1));@pemit %2=memorysense_line2(v(0),v(1));@pemit %2=memorysense_line3(v(0),v(1));@pemit %2=memorysense_line4(v(0),v(1));@pemit %2=memorysense_line5(v(0),v(1));@pemit %2=memorysense_orbit1(v(0),v(1));@pemit %2=memorysense_orbit2(v(0),v(1));@pemit %2=memoryextra_sense_info(v(0),v(1))
memorysense_header():	Relative % Position km | Velocity kpu | Date: [time(D,first(v(1)))] EST
memorysense_age():	% % % % % Age: [tms(fsub(xtime(),first(v(1))))]
sciscan_cmd:	$scan sci=*:/[get(me/sci_man)]/@swi get(v(sensor_memory),strcat(name,v(0)))=NO MATCH,{@npe %#='%0' does not exist as a sensor contact.},{[ifelse(wmatch(indist(v(us),v(maxrange)),histnum(v(!),v(0))),ifelse(hasenergy?(v(!),pwrscan,10),s({@tr me/sciscan=[histnum(v(!),v(0))],[histname(v(!),histnum(v(!),v(0)))],%#}),{@npe %#=There is no power available for a scan. Allocate power to scanners.}),{@npe %#='%0' is currently out of Scanner Range.})]}
sciscan:	@tr me/scancost=%0,%1,%2;@pe %2=basic_readout([v(us)],%0,%1);@pe %2;@pe %2=Total living beings: [round(fmul(fdiv(add(90,rand(21)),100),wcount(zwho(get(v(0),zone)))))]%[spc(10)]Conscious living beings: [round(fmul(fdiv(add(90,rand(21)),100),wcount(foreach(zwho(get(v(0),zone)),{[if(hasflag(v(0),c),1)]}))))]
```


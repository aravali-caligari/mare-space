# Legacy Console: SCI1

## Name

SCI1 - Advanced Science and Scanning Console

## Purpose

This is the SCI1 legacy console object, used in older versions of the game to provide basic scanning capabilities for spacecraft. It includes various scanning functions such as general sensing, specific sensing, and sensor memory recall.

## Meta data

```mud
SCI1(#469h)
Type:	Thing
Owner:	Ptah
Flags:	Halted[0]
Bytes:	9836
Children:	1
Created:	Fri Nov 25 22:27:57 1994
Modified:	Fri Jun 30 22:38:45 1995
Location: Helm Equipment Room(#11848R)
Home:	Helm Equipment Room(#11848R)
```

## Commands

## Object Definition

### Attribute definitions

```mud
sense2(): inherit function
check_history(): inherit function
specificview: inherit program
G: inherit program
extrasense: inherit program
alphabet: inherit program
sp: inherit program
newname: inherit program
name: inherit program
specificsense: inherit program
generalsense(): inherit function
sense: inherit program
sweep: inherit program
X(): inherit function
Y(): inherit function
Z(): inherit function
history_list: inherit program
history_read: inherit program
basic_readout(): inherit function
sense_header(): inherit function
sense_line1(): inherit function
sense_line2(): inherit function
sense_line3(): inherit function
sense_line4(): inherit function
extra_sense_info(): inherit function
get_word(): inherit function
sensor_record(): inherit function
approach(): inherit function
Sensor_Recall: inherit program
recall_list_cmd: inherit program
sense_line5(): inherit function
sense_orbit1(): inherit function
sense_orbit2(): inherit function
relsense: inherit program
newname2(): inherit function
name2(): inherit function
NameList(): inherit function

### Attribute list

```mud
sense_line5():	Rho [rjust(velhdg(dx(v(1),v(0)),dy(v(1),v(0)),dz(v(1),v(0))),15)] |[rjust(velhdg(dvx(v(0),v(1)),dvy(v(0),v(1)),dvz(v(0),v(1))),15)] | Tangent Velocity: [velmag(fmul(sin(dg2rd(approach(v(0),v(1)))),velmag(dvx(v(0),v(1)),dvy(v(0),v(1)),dvz(v(0),v(1)))),0,0)]kpu
sense2():	[ifelse(wmatch(inrange(v(us)),v(0)),specificsense(v(0),histname(v(!),v(0)),v(#),v(us)),{@pe %#='%0' is currently out of sensor range.})]
check_history():	[ifelse(scomp(get(v(sensor_memory),strcat(memory,v(0))),NO MATCH),generalsense(v(0),histname(v(!),v(0)),v(1)),s({@tr me/newname=%0,generalsense,%1}))]
sweep:	$sweep:/[get(me/sci_man)]/@swi comp(1,get(me/pwrsense))=1,{@pemit %#=There is not enough power available to sensors.},{@pwrsense me=add(get(me/pwrsense),-1);@pemit %#=Initiating Sensor Sweep;@foreach [inrange(get(me/us))] #={%%%[ifelse(match(v(0),#),{@fo me=@fo me=@fo me=@fo me=@fo me=@fo me=@pemit %#=Sensor Sweep Completed},check_history(v(0),v(#)))]}
newname2():	@swi get([v(sensor_memory)]/name%3)=NO MATCH,{[if(gt(wcount(lattrdef(con(v(sensor_memory)))),70),{@fo v(sensor_memory)={@create Memory Cell;@add me=con(me)}})];@def strcat(con(v(sensor_memory)),/name%3);@name%3 [v(sensor_memory)]=join(%0,con(v(sensor_memory)));@def strcat(con(v(sensor_memory)),/memory%0);@memory%0 [v(sensor_memory)]=0 0 0 0 0 0 0 0 0 0 0 0 0 %3;@pe %2=New sensor contact has been assigned the name of '%3'.;@tr me/%1=%0,%3,%2},{@tr me/newname=%0,%1,%2}
extra_sense_info():	Radius:[rjust(simp(fadd(0,get(s(%1/radius)))),10)]km VisualSize: [first(velhdg(3d(v(0),v(1)),get(s(%1/radius)),0))]Deg % Mass:[get(s(%1/mass))]kg Gravity: [simp(fdiv(grav(v(1)),pow(3d(v(0),v(1)),2)))]
NameList():	[ifelse(gt(wcount(v(0)),1),spstrcat(foreach(remove(v(0),wcount(v(0)),1),{[name(v(0))],}),name(extract(v(0),wcount(v(0)),1))),name(v(0)))]
Sensor_Recall:	$recall *:@swi get(v(sensor_memory),strcat(name,v(0)))=NO MATCH,{@pemit %#=No such name as '%0' stored in sensor memory.},{@tr me/memorysense=[histnum(v(!),v(0))],[read_memory(histnum(v(!),v(0)),sensor)],%#}
name2():	@name%0 [v(sensor_memory)];@undef [extract(v(3),2,1)]/name%0;@def [extract(v(3),2,1)]/name%1;@name%1 [v(sensor_memory)]=[v(3)];@memory[extract(v(3),1,1)] [v(sensor_memory)]=[extract(get(v(sensor_memory),strcat(memory, extract(v(3),1,1))),1,13)] %1;@pe %2=Name of sensor contact '%0' has been changed to '%1'.}
name:	$name *=*:/[v(sci_man)]/@swi get([v(sensor_memory)]/name%0)=NO MATCH,{@pe %#=Sorry, the name '%0' does not seem to exist in the sensory logs.},{[ifelse(stringeq(get(s([v(sensor_memory)]/name%1)),NO MATCH),ifelse(gt(wcount(v(1)),1),{@pe %#=Illegal name '%1'. It can only be one word in length.},name2(v(0),v(1),v(#),get(s([v(sensor_memory)]/name%0)))),{@pe %#=Sorry, the name '%1' already exists in the sensor history log.})]}
recall_list_cmd:	$++history list:@swi wcount(get(me/history))=0,{@npemit %#=Empty History List},{@foreach get(me/history)={@swi v(0)=#*,{@npemit %#='%%%%%%%[ljust(histname(v(!),v(0)),20)]' %%%%%%%[ifelse(scomp(read_memory(v(0),sensor),NO MEMORY),join(join(Mass:,word(read_memory(v(0),sensor),12)),join(Radius:,word(read_memory(v(0),sensor),13))),No Memory Entry)]}}}
relsense:	$relsense * from *:/[v(sci_man)]/@swi [histnum(v(!),v(0))]|[histnum(v(!),v(1))]|[if(wmatch(inrange(v(us)),histnum(v(!),v(0))),y)]|[if(wmatch(inrange(v(us)),histnum(v(!),v(1))),y)]=#*|#*%|y|y,{@tr me/specificsense=[histnum(v(!),v(0))],[histname(v(!),histnum(v(!),v(0)))],%#,[histnum(v(!),v(1))]},|*,{@pemit %#={'%0' does not exist as a sensor contact.}},*||*|*,{@pemit %#={'%1' does not exist as a sensor contact.}},*|*||*,{@pemit %#={'%0' is currently out of sensor range.}},*|*|*|,{@pem
approach():	[relphi(fsub(get(s(%0/linposx)),get(s(%1/linposx))),fsub(get(s(%0/linposy)),get(s(%1/linposy))),fsub(get(s(%0/linposz)),get(s(%1/linposz))),fsub(get(s(%0/linvelx)),get(s(%1/linvelx))),fsub(get(s(%0/linvely)),get(s(%1/linvely))),fsub(get(s(%0/linvelz)),get(s(%1/linvelz))))]
get_word():	NO MATCH
generalsense():	@pemit %2=basic_readout(get(me/us),%0,%1)
extrasense:	@pemit %2=Mass: [simp(fadd(0,get(s(%0/mass))))]kg Radius: [simp(fadd(0,get(s(%0/radius))))]km Attraction: [simp(pow(fdiv(grav(v(0)),pow(3d(get(me/us),v(0)),2)),.5))]km/update/update
alphabet:	Alfa Bravo Charlie Delta Echo Foxtrot Gulf Hotel India Joilet Kilo Lima Mike November Oscar Papa Quebec Romeo Sierra Tango Uniform Victor Whiskey Xray Yankee Zulu
sp:	
G:	6.67e-20
X():	[get(s(%0/linposx))]
Y():	[get(s(%0/linposy))]
Z():	[get(s(%0/linposz))]
newname:	[newname2(v(0),v(1),v(2),s([extract(get(me/alphabet),add(1,rand(26)),1)]-[rand(10)][rand(10)]))]
sense_orbit1():	Energy Apogee Perigee Eccen. Period
sense_orbit2():	Orbital Parameters: [orbit(get(s(%1/mass)),3d(v(0),v(1)),velmag(dvx(v(0),v(1)),dvy(v(0),v(1)),dvz(v(0),v(1))),approach(v(0),v(1)))]
specificsense:	@pemit %2=basic_readout(v(3),v(0),v(1));@pemit %2;@pemit %2=sense_header();@pemit %2=sense_line1(v(3),v(0),v(1));@pemit %2=sense_line2(v(3),v(0),v(1));@pemit %2=sense_line3(v(3),v(0),v(1));@pemit %2=sense_line4(v(3),v(0),v(1));@pemit %2=sense_line5(v(3),v(0),v(1));@pemit %2=sense_orbit1(v(3),v(0),v(1));@pemit %2=sense_orbit2(v(3),v(0),v(1));@pemit %2=extra_sense_info(v(3),v(0),v(1));@tr me/write_memory=%0,[sensor_record(v(3),v(0))],%2,sensor
specificview:	@pemit %2=> [histname(v(!),v(0))];@pemit %2=> [get(s(%0/Visual))]
sensor_record():	[xtime()] [simp(3d(v(0),v(1)))] [simp(dx(v(0),v(1)))] [simp(dy(v(0),v(1)))] [simp(dz(v(0),v(1)))] [simp(dvx(v(0),v(1)))] [simp(dvy(v(0),v(1)))] [simp(dvz(v(0),v(1)))] [simp(approach(v(0),v(1)))] [velhdg(dx(v(1),v(0)),dy(v(1),v(0)),dz(v(1),v(0)))] [get(s(%1/mass))] [simp(get(s(%1/radius)))] [line(histname(v(!),v(1)))]
sense_header():	Relative % % % % Position km | % % Velocity kpu |
sense_line2():	Upsilon % [rjust(simp(dy(v(0),v(1))),14)] | [rjust(simp(dvy(v(0),v(1))),14)] |
sense_line3():	Zeta % [rjust(simp(dz(v(0),v(1))),14)] | [rjust(simp(dvz(v(0),v(1))),14)] |
sense_line4():	Xi % [rjust(simp(3d(v(0),v(1))),14)] | [rjust(simp(velmag(dvx(v(0),v(1)),dvy(v(0),v(1)),dvz(v(0),v(1)))),14)] | Closing Velocity:[ifelse(add(fsgn(cos(dg2rd(approach(v(0),v(1))))),1),+,-)][velmag(fmul(cos(dg2rd(approach(v(0),v(1)))),velmag(dvx(v(0),v(1)),dvy(v(0),v(1)),dvz(v(0),v(1)))),0,0)]kpu
sense_line1():	Chi % [rjust(simp(dx(v(0),v(1))),14)] | [rjust(simp(dvx(v(0),v(1))),14)] | Approach Bearing: [relphi(dx(v(0),v(1)),dy(v(0),v(1)),dz(v(0),v(1)),dvx(v(0),v(1)),dvy(v(0),v(1)),dvz(v(0),v(1)))]
basic_readout():	Contact: [ljust(v(2),15)] Distance:[rjust(simp(3d(v(0),v(1))),12)]km Abs. Bearing:[velhdg(dx(v(1),v(0)),dy(v(1),v(0)),dz(v(1),v(0)))]
sense:	$sense *:/[get(me,sci_man)]/[switch(comp(2,get(me,pwrsense)),1,s({@pemit %#=There is not enough power available to sensors.}),s(@pwrsense me=add(get(me,pwrsense),-2);[switch(s({[histnum(v(!),v(0))]|[if(wmatch(inrange(v(us)),histnum(v(!),v(0))),y)]}),{#*|y},s({@tr me/specificsense=[histnum(v(!),v(0))],[histname(v(!),histnum(v(!),v(0)))],%#,[v(us)]}),{#*|},s({@pemit %#={'%0' is currently out of sensor range.}}),s({@pemit %#={'%0' does not exist as a sensor contact.})]
```

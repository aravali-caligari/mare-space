# TAC

## Name

TAC - Tactical Operations

## Purpose

This is the TAC legacy console object, used in older versions of the game to provide tactical combat capabilities for spacecraft. It allows players to manage weapons systems, target enemies, and handle damage control during space battles.

## Meta data

## Object Definition

## Attribute definitions

```mush
tac_weaponlist6: inherit program
shield_cmd2: inherit program
shield_cmd: inherit program
take_damage: inherit program
destroyed: inherit program
weapon_dies: inherit program
aimfor2(): inherit function
aimfor: inherit program
istarget(): inherit function
tac_weaponlist5: inherit program
tac_offload: inherit program
fire4(): inherit function
_attrdef12(): inherit function
fire3(): inherit function
fire2(): inherit function
chg(): inherit function
aim2(): inherit function
tac_weaponlist4: inherit program
weaponlist_line(): inherit function
tac_weaponlist3: inherit program
tac_weaponlist2: inherit program
tac_weaponlist1: inherit program
listweapon: inherit program
fire: inherit program
aim: inherit program
```

### Attribute list

```mush
weapon_dies:	[if(1,!)]visevent Weapondie [v(!)]=v(sex),v(linposx),v(linposy),v(linposz);!explode me;@tel num(me);@destroy me
take_damage:	@fore zwho(get(v(us),zone))={@npe %%0=[switch(v(0),{SHit},{The lights dim as the shields take a hit.},{LHit},{The ship shudders with an impact.},{HHit},{The ship rocks wildly! She's been hit hard!})]}
destroyed:	@fore zwho(get(v(us),zone))={@npe %%0=The ship has sustained non-recoverable injuries! She's goin' down...! ****BOOOOOOOOOM**** (you're dead);@tel %%0=#50707}
aim:	$aim *=* *:/[v(tac_man)]/@swi lor(lor(gt(v(1),360),lt(v(1),0)),lor(gt(v(2),90),lt(v(2),-90)))=1,{@pe %#=You must aim with the X value between 0 and 360, and the Y value between -90 and 90.},{[aim2(match(foreach(v(tac_weaponlist1),[line(name(v(0)))]),strcat(*,strcat(line(v(0)),*))),simp(fadd(v(1),0)),simp(fadd(v(2),0)),{at})]}
aimfor:	$aim * for *:/[v(tac_man)]/@swi istarget(histnum(v(!),v(1)))=0,{[ifelse(histnum(v(!),v(1)),{@npe %#='%1' is currently out of targetable range.},{@npe %#='%1' does not exist as a sensor contact.})]},{[aimfor2(match(foreach(v(tac_weaponlist1),[line(name(v(0)))]),strcat(*,strcat(line(v(0)),*))),histnum(v(!),v(1)))]}
istarget():	[wmatch(s({[indist(v(us),v(maxrange))] [inrange(v(us))] [insight(v(us),v(mag))]}),v(0))]
tac_offload:	@fo me=s({[tac_pos+vel()];[get(v(1),firing)]});@fo %0=s({[get(v(1),firee)]})
Lock:	draco(#43428P)|Ptah(#5745P)
chg():	[ifelse(match(v(1),1),strcat(v(2),strcat(spc(1),remove(v(0),1,1))),ifelse(lor(lt(v(1),1),gt(v(1),wcount(v(0)))),v(0),insert(remove(v(0),v(1),1),sub(v(1),1),v(2))))]
fire2():	[match(foreach(v(tac_weaponlist1),[line(name(v(0)))]),strcat(*,strcat(line(v(0)),*)))]
fire:	$fire *:/[v(tac_man)]/@swi {%0}={*=*},{[fire3(fire2(mid(v(0),0,sub(pos({=},v(0)),1))),delete(v(0),0,pos({=},v(0))))]},{[fire3(fire2(v(0)))]}
_attrdef12():	@linposx %%0=fadd(get(v(us),linposx),fmul(fadd(fadd(get(v(us),radius),get(%%0,radius)),1),fmul(cos(%[dg2rd(v(3))]),cos(%[dg2rd(v(4))]))));@linposy %%0=fadd(get(v(us),linposy),fmul(fadd(fadd(get(v(us),radius),get(%%0,radius)),1),fmul(sin(%[dg2rd(v(3))]),cos(%[dg2rd(v(4))]))));@linposz %%0=fadd(get(v(us),linposz),fmul(fadd(fadd(get(v(us),radius),get(%%0,radius)),1),sin(%[dg2rd(v(4))])));@linvelx %%0=fadd(get(v(us),linvelx),fmul(%%5,fmul(cos(%[dg2rd(v(3))]),cos(%[dg2rd(v(4))]))));@linvely %%0=fadd(get(v(us),linvely),fmul(%%5,fmul(sin(%[dg2rd(v(3))]),cos(%[dg2rd(v(4))]))));@linvelz %%0=fadd(get(v(us),linvelz),fmul(%%5,sin(%[dg2rd(v(4))])))
fire3():	[ifelse(v(0),ifelse(extract(v(tac_weaponlist2),v(0),1),ifelse(lt(xtime(),add(extract(v(tac_weaponlist5),v(0),1),get(extract(v(tac_weaponlist1),v(0),1),reload_time))),s({@pe %#=You must wait [sub(add(extract(v(tac_weaponlist5),v(0),1),get(extract(v(tac_weaponlist1),v(0),1),reload_time)),xtime())] more seconds to fire that weapon again.}),s({@tac_weaponlist2 me=chg(v(tac_weaponlist2),%0,sub(extract(v(tac_weaponlist2),%0,1),1));@tac_weaponlist5 me=chg(v(tac_weaponlist5),%0,xtime());[fire4(extract(v(tac_weaponlist1),v(0),1),v(1),v(0))]})),{@pe %#=That weapon has run out.}),{@pe %#=Invalid weapon.})]
shield_cmd:	$shield:@npe %#=Shield Readout for [name(v(us))]:;@pe %#=engscan3(v(us),v(us));@pe %#=engscan4(v(us),v(us))
listweapon:	$list weapons:/[v(tac_man)]/@pe %#=.[string(-,22)].[string(-,10)].[string(-,6)].[string(-,17)].[string(-,17)].;@npe %#=|[cjust(Weapon Name,22)]| Last Use | Ammo |[cjust(Heading,17)]|[cjust(Target,17)]|;@pe %#=+[string(-,22)]+[string(-,10)]+[string(-,6)]+[string(-,17)]+[string(-,17)]+;@foreach lnum(wcount(v(tac_weaponlist1)))=@pe %#=weaponlist_line(add(v(0),1));@fo me=@pe %#=`[string(-,22)]^[string(-,10)]^[string(-,6)]^[string(-,17)]^[string(-,17)]'
weaponlist_line():	| [ljust(name(extract(v(tac_weaponlist1),v(0),1)),20)] | [rjust(tms(sub(xtime(),extract(v(tac_weaponlist5),v(0),1))),4)] ago | [rjust(extract(v(tac_weaponlist2),v(0),1),4)] | [rjust(extract(v(tac_weaponlist3),v(0),1),7)] [rjust(extract(v(tac_weaponlist4),v(0),1),7)] | [ljust(histname(me,extract(v(tac_weaponlist6),v(0),1)),15)] |
aimfor2():	[ifelse(v(0),aim2(v(0),first(velhdg(dx(v(1),v(us)),dy(v(1),v(us)),dz(v(1),v(us)))),rest(velhdg(dx(v(1),v(us)),dy(v(1),v(us)),dz(v(1),v(us)))),s({for '[histname(v(!),v(1))]' at}),v(1)),{@pe %#=That is not a valid weapon.})]
aim2():	[ifelse(v(0),s({@tac_weaponlist3 me=chg(v(tac_weaponlist3),[v(0)],[v(1)]);@tac_weaponlist4 me=chg(v(tac_weaponlist4),[v(0)],[v(2)]);@tac_weaponlist6 me=chg(v(tac_weaponlist6),[v(0)],[v(4)]);@npe %#=[name(extract(v(tac_weaponlist1),v(0),1))] aimed [v(3)] heading: [v(1)] [v(2)].}),{@pe %#=That is not a valid weapon.})]
fire4():	@create get(%0,weapon_name);@startup con(me)=_me/weapon_dies;@sex con(me)=get(%0,notice_range);@add con(me)=#44444;@aship con(me)={@swi v(0)=crash,{@tr me/startup}};@type con(me)=SS;@pwrgen con(me)=get(%0,pwrgen);@radius con(me)=get(%0,radius);@mass con(me)=get(%0,mass);@tr me/tac_offload=con(me),%0,%1,{[extract(v(tac_weaponlist3),v(2),1)]},{[extract(v(tac_weaponlist4),v(2),1)]},{[get(v(0),speed)]},{[extract(v(tac_weaponlist6),v(2),1)]};@tel con(me)=loc(v(us))
shield_cmd2:	$shield *=*:@swi wmatch(lnum(10),v(0))=0,{@pe %#=Invalid shield.},{[ifelse(gt(v(1),sub(v(maxshld),1)),{@pe %#=That is beyond the shield's capacity.},ifelse(gt(v(1),get(s({[v(us)]/S%0}))),ifelse(gt(sub(v(1),get(s({[v(us)]/S%0}))),v(pwrshld)),{@pe %#=There is not enough energy allocated to charge the shield to that capacity.},{@pe %#=Raising shield %0 to %1.;@pwrshld me=sub(v(pwrshld),sub(v(1),get(s({[v(us)]/S%0}))));@s%0 v(us)=%1;!shield v(us)}),ifelse(lt(v(1),0),{@pe %#=Shields can only be charged positively.},{@pe %#=Lowering shield %0 to %1.;@s%0 v(us)=%1;!shield v(us)})))]}
```

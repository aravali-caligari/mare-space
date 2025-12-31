# Station Transmat Parent

## Name

Station Transmat Parent - Space Station Transporter Console

## Purpose

This is the Station Transmat Parent console object, used in older versions of the game to provide personnel transportation capabilities for space stations. It allows players to transport themselves and others to various locations within range using the Transporter system.

## Meta data

```mud
Station Transmat Parent(#49880)
Type:	Thing
Owner:	Ptah
Bytes:	4168
Parents:	PA's temp dash(#1022V)
Children:	19
Location:	Transmat Equipment Room(#53399R)
Home:	Transmat Equipment Room(#53399R)
```

## Object Definition

### Attribute definitions

```mud
coordcheck: inherit program
old_setcoord: program
range: inherit program
ifdeath(): inherit function
setcoordfail: inherit program
setcoordsucc: inherit program
distyes(): inherit function
Us: program
info: inherit program
transto(): inherit function
cantransto(): inherit function
transmit: inherit program
coords: inherit program
coordnum: program
setcoord: inherit program
Attribute list:
```

### Attribute list

```mud
transmit:	@set %0=slavr;@set %0=mortal;@wait 1={@pemit %0=Your entire body tingles as you dematerialize.;@oemit %0=[name(v(0))] dematerializes in a sparkle of energy.};@wait 2={@tel %0=#18879};@wait 30={@swi truth(cantransto(%1))=0,{@remit loc(me)=A figure materializes in a flash of energy.;@tel %0=loc(me);@pemit %0=Your body tingles as it regains form.;@emit Transmat -- Unable to lock onto coordinates.;@set %0=!slave;@set %0=!mortal},{@swi ifdeath(%0)=1,{@remit loc(transto(%1))=A figure begins to materializes but it cannot complete forming.;@tel %0=loc(transto(%1));@pemit %0=Your entire body reels in pain as your body materalizes in an uncompleted form.;@fo %0=:shreiks in agony!;@fo #5745=@limbo %0=num(me)},{@remit loc(transto(%1))=A figure materializes in a flash of energy.;@tel %0=loc(transto(%1));@pemit %0=Your body tingles as it regains form.;@set %0=!slave;@set %0=!mortal}}}
range:	80000
coords:	$coords:@pemit %#=Transmat Coordinates:;@foreach [indist(get(me/us),v(range))] #=@swi v(0)=#,{@fo me=@fo me=@fo me={@pemit %#=End of Coordinates list.}},{@swi truth(get(s(%%%%0/ptransmat)))=0,{},{@pemit %#=%%%%%%%[name(v(0))]}}
OnPay:	@swi name(*%n)=%n,{@pemit %#=Transmitting...;@tr me/transmit=%#,[get(me/coordnum)]},{@pemit owner(%n)=Invalid user.}
Cost:	50
transto():	[get(s(%0/Ptransmat))]
cantransto():	[ifelse(land(truth(transto(v(0))),truth(sub(get(s(%0/S0)),1))),1,0)]
info:	$info:@pemit %#=Public Personnel Transmat Info:;@pemit %#=To get a list of possible destinations type: Coords;@pemit %#=To select a destination type: Destination <coord>;@pemit %#=Once you have selected a destination you may transmit by paying 50C;@pemit %#=The command to activate transmitting is: give transmat=50;@pemit %#
Desc:	This is a Transport-Material device used mainly for personnel transportation. It is a fairly safe way to travel as deaths due tho this machiine are fairly rare. They are also quite easy to operate 'info' will display the instuctions for use.
Fail:	Too heavy.
Lock:	Ptah(#5745P)
ifdeath():	[ifelse(land(lt(rand(100),4),truth(wmatch(parents(v(0)),#44931))),1,0)]
old_setcoord:	$destination *:@coordnum me;@coordnum me=extract(indist(v(us),v(range)),wmatch(foreach(indist(v(us),v(range)),{%[dash(name(v(0)))]}),dash(v(0))),1);@swi wcount(v(coordnum))=1,{@tr me/setcoordsucc=%#},{@tr me/setcoordfail=%#}
setcoord:	$DESTINATION *:@pemit [v(#)]=Setting...;@coordnum me;@foreach [indist(v(us),v(range))]=@swi [dash(v(0))]=%[dash(name(v(0)))],{@coordnum me=%[v(0)];@tr me/setcoordsucc=[v(#)]},{};@wait 2=@tr me/coordcheck=[v(#)]
setcoordfail:	@pemit %0=TRANSMAT ERROR: Destination Unknown/Unclear.
coordcheck:	@swi [wcount(v(coordnum))]=1,{},{@tr me/setcoordfail=[v(0)]}
setcoordsucc:	@pemit [v(0)]=Destination set.;@oemit [v(0)]=[name(v(0))] sets a destination on the transmat.
```

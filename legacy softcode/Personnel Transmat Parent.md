# Legacy Console: OMS

## Name

Personnel Transmat Parent - Personnel Transporter Console

## Purpose

This is the Personnel Transmat Parent console object, used in older versions of the game to provide personnel transportation capabilities for spacecraft. It allows players to transport themselves and others to various locations within range using the Transporter system.

## Meta data

```mud
Personnel Transmat Parent(#19926h)
Type:	Thing
Owner:	Ptah
Flags:	Halted[0]
Bytes:	7016
Parents:	Internal Space Functions(#52323)
Children:	15
Modified:	Sat Mar 2 11:53:14 1996
Location:	Transmat Equipment Room(#53399R)
Home:	Transmat Equipment Room(#53399R)
```

## Object Definition

### Attribute definitions

```mud
transok: inherit program
validtrans2(): inherit function
transmiteveryone: inherit program
range: inherit program
ifdeath(): inherit function
receiveall: inherit program
cantransfrom(): inherit function
receivename: inherit program
validtrans(): inherit function
transmitall: inherit program
cantransto(): inherit function
transto(): inherit function
transmit: inherit program
distyes(): inherit function
decpwr: inherit program
transmitme: inherit program
pwryes(): inherit function
info: inherit program
toggle: inherit program
onoff: program
status: program
Helm: program
Us: program
Coords: inherit program
```

### Attribute list

```mud
transmit:	@set %0=slave;@set %0=mortal;@wait 1={@pemit %0=Your entire body tingles as you dematerialize.;@oemit %0=[name(v(0))] dematerializes in a sparkle of energy.};@wait 2={@tel %0=#18879};@wait 30={@swi truth(cantransto(%1))=0,{@remit loc(me)=A figure materializes in a flash of energy.;@tel %0=loc(me);@pemit %0=Your body tingles as it regains form.;@emit Transmat -- Unable to lock onto coordinates.;@set %0=!slave;@set %0=!mortal},{@swi ifdeath(%0)=1,{@remit loc(transto(%1))=A figure begins to materializes but it cannot complete forming.;@tel %0=loc(transto(%1));@tr %[transto(%1)]/transok=%0;@pemit %0=Your entire body reels in pain as your body materalizes in an uncompleted form.;@fo %0=:shreiks in agony!;@fo #5745=@limbo %0=num(me)},{@remit loc(transto(%1))=A figure materializes in a flash of energy.;@tel %0=loc(transto(%1));@tr %[transto(%1)]/transok=%0;@pemit %0=Your body tingles as it regains form.;@set %0=!slave;@set %0=!mortal}}}
info:	$info:@pemit %#=Transmat Commands:;@pemit %#=Transmat On/Off: Turn the transmat on or off.;@pemit %#=Coords: Get a list of possible coordinates.;@pemit %#=Transmit me to <coord>: Transmit yourself to <coord>.;@pemit %#=Transmit all to <coord>: Transmit all but yourself to <coord>.;@pemit %#=Transmit everyone to <coord>: Transmits all including yourself to <coord>.;@pemit %#=Receive <name> from <coord>: Transmits <name> from <coord> to your location.;@pemit %#=Receive all coord <coord>: Transmits everyone from <coord> to your location.
validtrans2():	[ifelse(hasflag(v(0),P),1,0)]
transmiteveryone:	$transmit everyone to *:@swi name(*%n)=%n,{@swi [truth(get(me/onoff))]=1,{@swi [pwryes()]=1,{@swi [distyes(s(%0))]=1,{@remit here=Transmitting...;@tr me/decpwr;@foreach objlist(con(here))={@swi validtrans2(v(0))=1,{@tr me/transmit=v(0),%%%%%%%%%%%%%%%[histnum(v(helm),v(0))]},{}}},{@pemit %#=Unknown coordinate.}},{@pemit %#=Power not available.}},{@pemit %#=The transmat is currently off.}},{@pemit owner(%n)=Invalid user.}
ifdeath():	[ifelse(land(lt(rand(100),4),truth(wmatch(parents(v(0)),#44931))),1,0)]
receiveall:	$receive all coord *:@swi name(*%n)=%n,{@swi [truth(get(me/onoff))]=1,{@swi [pwryes()]=1,{@swi [distyes(s(%0))]=1,{@pemit %#=Transmitting...;@tr me/decpwr;@foreach objlist(con(loc(transto(histnum(v(helm),v(0))))))={@swi validtrans(v(0),%#)=1,{@tr me/transmit=v(0),v(us)},{}}},{@pemit %#=Unknown coordinate.}},{@pemit %#=Power not available.}},{@pemit %#=The transmat is currently off.}},{@pemit owner(%n)=Invalid user.}
validtrans():	[ifelse(land(hasflag(v(0),P),lnot(wmatch(v(0),v(1)))),1,0)]
transmitall:	$transmit all to *:@swi name(*%n)=%n,{@swi [truth(get(me/onoff))]=1,{@swi [pwryes()]=1,{@swi [distyes(s(%0))]=1,{@remit here=Transmitting...;@tr me/decpwr;@foreach objlist(con(here))={@swi validtrans(v(0),%#)=1,{@tr me/transmit=v(0),%%%%%%%%%%%%%%%[histnum(v(helm),v(0))]},{}}},{@pemit %#=Unknown coordinate.}},{@pemit %#=Power not available.}},{@pemit %#=The transmat is currently off.}},{@pemit owner(%n)=Invalid user.}
cantransfrom():	[ifelse(land(hasflag(v(0),P),nearby(v(0),transto(v(1)))),1,0)]
receivename:	$receive * from *:@swi name(*%n)=%n,{@swi truth(get(me/onoff))=1,{@swi [pwryes()]=1,{@swi [distyes(s(%1))]=1,{@swi [cantransfrom(num(s(*%0)),histnum(v(helm),v(1)))]=1,{@pemit %#=Transmitting...;@tr me/decpwr;@tr me/transmit=[num(s(*%0))],[get(me/us)]},{@pemit %#=Cannot lock onto %0.}},{@pemit %#=Unknown coordinate.}},{@pemit %#=Power not available.}},{@pemit %#=The transmat is currently off.}},{@pemit owner(%n)=Invalid user.}
transmitme:	$transmit me to *:@swi name(*%n)=%n,{@swi [truth(get(me/onoff))]=1,{@swi [pwryes()]=1,{@swi [distyes(s(%0))]=1,{@pemit %#=Transmitting...;@tr me/decpwr;@tr me/transmit=%#,[histnum(v(helm),v(0))]},{@pemit %#=Unknown coordinate.}},{@pemit %#=Power not available.}},{@pemit %#=The transmat is currently off.}},{@pemit owner(%n)=Invalid user.}
cantransto():	[ifelse(land(truth(transto(v(0))),truth(sub(get(s(%0/S0)),1))),1,0)]
toggle:	$transmat *:@swi v(0)=On,{@ptransmat %/Us/=num(me);@pemit %#=Transmat switched on.;@onoff me=xxx},Off,{@ptransmat %/Us/;@pemit %#=Transmat switched off.;@onoff me},{@pemit %#=Use 'On' or 'Off'.}
Desc:	This is a Transport-Material device used mainly for personnel transportation. It is a fairly safe way to transport as deaths due to this machine are rare. They are also quite easy to operate 'info' will display the commands.
Fail:	Too heavy.
OLook:	looks at the transmat.
pwryes():	[ifelse(gt(get(s(%/Helm//pwraux)),99),1,0)]
decpwr:	@pwraux %/Helm/=sub(get(s(%/Helm//PwrAux)),100)
transto():	[get(s(%0/Ptransmat))]
range:	40000
Coords:	$coords:@pemit %#=Transmat Coordinates:;@foreach [indist(get(me/us),v(range))] #=@swi v(0)=#,{@fo me=@fo me=@fo me={@pemit %#=End of Coordinates list.}},{@swi histname(v(helm),v(0))=NO MATCH,{},{@swi truth(get(s(%%%%0/ptransmat)))=0,{},{@pemit %#=%%%%%%%[histname(v(helm),v(0))]}}}
distyes():	[ifelse(wmatch(indist(v(us),v(range)),histnum(v(helm),v(0))),1,0)]
```
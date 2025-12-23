# Legacy Console: View Screen

## Name

View Screen - 3D Viewscreen Console

## Purpose

This is the View Screen legacy console object, used in older versions of the game to provide a 3D viewscreen for spacecraft. It allows players to visualize their surroundings in space, including other ships and celestial objects, with adjustable magnification and aspect ratios.

## Object Definition

### Meta data

### Attribute definitions

```mud
tYlin(): inherit function
plotnum(): inherit function
plotcoords(): inherit function
append(): inherit function
Xlin(): inherit function
Ypos(): inherit function
plotfac: inherit program
Xpos(): inherit function
Ylin(): inherit function
plotpos(): inherit function
fac: inherit program
td0: program
td16: program
td15: program
td14: program
td13: program
td12: program
td11: program
td10: program
td9: program
td8: program
td7: program
td6: program
td5: program
td4: program
td3: program
td2: program
td1: program
d16: inherit program
d15: inherit program
d14: inherit program
d13: inherit program
d12: inherit program
d11: inherit program
d10: inherit program
d9: inherit program
d8: inherit program
d7: inherit program
d6: inherit program
d5: inherit program
d4: inherit program
d3: inherit program
d2: inherit program
d1: inherit program
d0: inherit program
plot2: inherit program
plot1: inherit program
mag: program
spacedesc: inherit program
formatname(): inherit function
hsdesc: inherit program
HS(): inherit function
magnification_change: inherit program
magnification: inherit program
aspect_change: inherit program
aspect: inherit program
viewcheck(): inherit function
viewobj: inherit program
view: inherit program
```

### Attribute list

```mud
tYlin():	[strcat(td,add(Ypos(v(0)),8))]
plotfac:	$plot *:@pemit %#=Scale factor for plot set to [v(0)]Mm.;@fac me=[v(0)]
d0:	Scale Factor: [v(fac)]Mm
Xpos():	[div(dx(v(0),v(us)),mul(v(fac),1000))]
Ylin():	[strcat(d,add(Ypos(v(0)),8))]
plot2:	@td1 me=v(d1); @td2 me=v(d2); @td3 me=v(d3); @td4 me=v(d4); @td5 me=v(d5); @td6 me=v(d6); @td7 me=v(d7); @td8 me=v(d8); @td9 me=v(d9); @td10 me=v(d10); @td11 me=v(d11); @td12 me=v(d12); @td13 me=v(d13); @td14 me=v(d14); @td15 me=v(d15); @td16 me=v(d16)
viewcheck():	[ifelse(insight(v(0),v(1)),1,ifelse(hasflag(loc(v(0)),Z),0,-1))]
formatname():	[strcat(strcat(histname(v(!),v(0)),string(% %,sub(36,strlen(histname(v(!),v(0)))))),|)]
hsdesc:	> The only thing visible in front of the ship as it hurtles through hyperspace > is lots and lots of blue light. Near to the sides, the blue light fades %% %% %% %% %% > quickly through the spectrum, reaching a thin line of red, then behind the %% %% %% > ship is total blackness.
HS():	[ifelse(wmatch(get(s(%/us//linvelx)),?),1,0)]
magnification:	0
aspect:	N
viewobj:	$view *:@swi %0=Space,{@pe %#=> [get(s([space_room()]/desc))]},Unidentified Object,{@pe %#=It is too difficult to make it out...perhaps you should use scanners first.},{[ifelse(lnot(stringeq(histnum(v(!),v(0)),NO MATCH)),ifelse(wmatch(insight(v(us),v(mag)),histnum(v(!),v(0))),s({@tr me/specificview=[histnum(v(!),v(0))],%0,%#}),s({@pe %#=You can't see that from here.})),s({@pe %#=You don't see that out there.}))]}
view:	$view:@pe %#=Viewscreen 3-d.vII - Aspect: [v(aspect)] Mag: [v(magnification)];@pe %#=.[string(-,37)].;@swi hs()=1,{@pemit %#=[v(hsdesc)]},{[switch(viewcheck(v(us),v(mag)),0,s({@npe %#=| Space%[spc(31)]|}),-1,s({@pe %#=name(loc(v(us)));@pe %#=ifelse(hasflag(loc(v(us)),R),get(loc(v(us)),desc),get(loc(v(us)),idesc))}),1,s({@npe %#=| Space%[spc(31)]|;@foreach [insight(v(us),v(mag))]=@pe %#=ifelse(histname(v(!),v(0)),s({| %%%[formatname(v(0))]}),{| Unidentified Object})}))]};@fo me=@pe %#=`[string(-,37)]'
d2:	6 . . . . . . . . . . . . . . .
d3:	5 . . . . . . . . . . . . . . .
d4:	4 . . . . . . . . . . . . . . .
d5:	3 . . . . . . . . . . . . . . .
d6:	2 . . . . . . . . . . . . . . .
d7:	1 . . . . . . . . . . . . . . .
d9:	1 . . . . . . . . . . . . . . .
d10:	2 . . . . . . . . . . . . . . .
d11:	3 . . . . . . . . . . . . . . .
d12:	4 . . . . . . . . . . . . . . .
d13:	5 . . . . . . . . . . . . . . .
d14:	6 . . . . . . . . . . . . . . .
d16:	7 6 5 4 3 2 1 0 1 2 3 4 5 6 7
fac:	40
Ypos():	[div(dy(v(0),v(us)),mul(v(fac),1000))]
Xlin():	[add(mul(add(Xpos(v(0)),7),3),4)]
append():	[get(s(me/[v(0)]))] [v(1)]
plotnum():	[extract(insight(v(us),1),v(0),1)]
plotcoords():	[spc(1)]%([Xpos(v(0))],[Ypos(v(0))]%)[spc(1)]
plot1:	$plot:@pemit %#=Generating plot at scale factor = [v(fac)]Mm;@foreach [insight(v(us),1)]=@nset me=%[strcat(t,Ylin(v(0)))]:%[plotpos(v(0),wmatch(insight(v(us),1),v(0)))];@foreach 1 2 3 4 5 6 7 8 9 10 11 12 13 14 15 16=@npemit [v(#)]=%[append(strcat(td,v(0)),if(lteq(v(0),wcount(insight(v(us),1))),strcat(strcat(v(0),plotcoords(plotnum(v(0)))),histname(v(!),plotnum(v(0))))))];@wait 1=@tr me/plot2
d8:	0 -X . . . . . . o . . . . . . +X
d15:	7 . . . . . . . +Y . . . . . . .
d1:	7 . . . . . . . -Y . . . . . . .
plotpos():	[change(v(tYlin(v(0))),v(1),Xlin(v(0)))]
```


# Telescope Parent

## Name

Telescope Parent - Telescope Console

## Purpose

This is the Telescope legacy console object, used in older versions of the game to provide telescope capabilities for spacecraft. It allows players to peer through a high-powered telescope to observe distant objects in space.

## Meta data

```mud
Telescope Parent(#12126)
Type:	Thing
Owner:	Ptah
Bytes:	3784
Parents:	Internal Space Functions(#52323)
Children:	27
Location:	Misc Room(#10558R)
Home:	Bridge ... ISA Softwind(#43152R)
```

## Object Definition

### Attribute definitions

```mud
hs(): inherit function
approach(): inherit function
telescope_display(): inherit function
basic_readout(): inherit function
coordnum: program
peer_display: inherit program
viewcheck(): inherit function
mag: inherit program
us: program
peer_at: inherit program
peer: inherit program
helm: program
intelescope(): inherit function
getnum(): inherit function
getname(): inherit function

### Attribute list

```mud
hs():	[ifelse(wmatch(get(s(%/us//linvelx)),?),1,0)]
peer:	$peer telescope:@pemit %#=You peer through the telescope and see visible...;@swi viewcheck(v(us),v(mag))=0,{@pemit %#=> %[ifelse(hs(),Hyper Space,Space)]},-1,{@pemit %#=name(loc(v(us)));@pemit %#=get([loc(v(us))]/desc)},1,{@pemit %#=> %[ifelse(hs(),Hyper Space,Space)];@foreach insight(v(us),v(mag))=@pemit %#=ifelse(getname(v(0)),{> %%%[getname(v(0))]},{> Unidentified Object})}
getnum():	[ifelse(v(helm),if(wmatch(insight(v(us),v(mag)),histnum(v(helm),v(0))),histnum(v(helm),v(0))),global)]
coordnum:	#36855
telescope_display():	% % % % % % % % % % % % % % Closing Velocity: [ifelse(add(fsgn(cos(dg2rd(approach(v(0),v(1))))),1),+,-)][velmag(fmul(cos(dg2rd(approach(v(0),v(1)))),velmag(dvx(v(0),v(1)),dvy(v(0),v(1)),dvz(v(0),v(1)))),0,0)] kpu Radius:[rjust(simp(fadd(0,get(s(%1/radius)))),10)] km
helm:	#52742
approach():	[relphi(fsub(get(s(%0/linposx)),get(s(%1/linposx))),fsub(get(s(%0/linposy)),get(s(%1/linposy))),fsub(get(s(%0/linposz)),get(s(%1/linposz))),fsub(get(s(%0/linvelx)),get(s(%1/linvelx))),fsub(get(s(%0/linvely)),get(s(%1/linvely))),fsub(get(s(%0/linvelz)),get(s(%1/linvelz))))]
Desc:	This is a high-powered telescope used to look at far distant objects in the space. Use 'peer telescope' to see what is visible, and 'peer telescope at <name>' to look at a particular object.
peer_at:	$peer telescope at *:@coordnum me;@swi getnum(v(0))=global,{@foreach insight(v(us),v(mag))={@swi name(v(0))={%0},{@coordnum me=v(0);@tr me/peer_display=%#}};@fo me=@fo me=@swi v(coordnum)=,{@pe %#=That object isn't in view.}},,{@pe %#=That object isn't in view.},#*,{@coordnum me=getnum(v(0));@tr me/peer_display=%#}
peer_display:	@pemit %0=basic_readout(v(us),v(coordnum),getname(v(coordnum)));@pemit %0=telescope_display(v(us),v(coordnum),getname(v(coordnum)));@pemit %0=get([v(coordnum)]/visual)
intelescope():	[if(lor(wmatch(insight(v(us),v(mag)),v(0)),match(get(s(%0/sector)),name(v(0)))),v(0))]
us:	#44700
viewcheck():	[ifelse(insight(v(0),v(1)),1,ifelse(hasflag(loc(v(0)),Z),0,-1))]
getname():	[ifelse(v(helm),histname(v(helm),v(0)),name(v(0)))]
mag:	200
Lock:	Carrie_Gram(#42921P)&!Carrie_Gram(#42921P)
basic_readout():	Contact: [ljust(v(2),15)] Distance:[rjust(simp(3d(v(0),v(1))),12)] km Abs. Bearing: [velhdg(dx(v(1),v(0)),dy(v(1),v(0)),dz(v(1),v(0)))]
Fail:	It is mounted here.
```

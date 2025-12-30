# Internal Space Functions

## Name

Internal Space Functions - Functions for internal spacecraft operations

## Purpose

This file contains a collection of internal functions used for spacecraft operations within the MARE-Space simulation. These functions handle various tasks such as energy management, gravitational calculations, distance measurements, and data manipulation.

## Meta data

```mud
Internal Space Functions(#52323)
Type:	Thing
Owner:	Ptah
Bytes:	2400
Children:	10
Location:	Helm Equipment Room(#11848R)
Home:	Old Space Stuff box(#3210)
```

## Object Definition

### Attribute definitions

```mud
takeenergy: inherit program
_attrdef9(): inherit function  ## SUPPOSED TO BE 3D() BUT NAME CONFLICTS WITH GLOBAL SPACE FUNCTIONS and is INVALID
set_word(): inherit function
join(): inherit function
grav(): inherit function
dvx(): inherit function
dvy(): inherit function
dvz(): inherit function
dist(): inherit function
hasenergy?(): inherit function
dy(): inherit function
dx(): inherit function
dz(): inherit function
word(): inherit function
histnum(): inherit function
histname(): inherit function
```

### Attribute list

```mud
histname():	[extract(get(s([get(v(0),sensor_memory)]/memory%1)),14,1)]
set_word():	[strcat(if(sub(v(2),1),strcat(extract(v(0),1,sub(v(2),1)),spc(1))),strcat(v(1),if(sub(v(2),wcount(v(0))),strcat(spc(1),extract(v(0),add(v(2),1),sub(wcount(v(0)),v(2)))))))]
join():	[ifelse(strlen(v(1)),strcat(strcat(v(0),spc(1)),v(1)),v(0))]
_attrdef9():	[first(dist3d(get(s(%0/linposx)),get(s(%0/linposy)),get(s(%0/linposz)),get(s(%1/linposx)),get(s(%1/linposy)),get(s(%1/linposz))))]
grav():	[fmul(get(s(%0/mass)),6.67e-18)]
dx():	[fsub(get(s(%0/linposx)),get(s(%1/linposx)))]
dy():	[fsub(get(s(%0/linposy)),get(s(%1/linposy)))]
dz():	[fsub(get(s(%0/linposz)),get(s(%1/linposz)))]
dvz():	[fsub(get(s(%0/linvelz)),get(s(%1/linvelz)))]
dvy():	[fsub(get(s(%0/linvely)),get(s(%1/linvely)))]
dvx():	[fsub(get(s(%0/linvelx)),get(s(%1/linvelx)))]
word():	[extract(v(0),v(1),1)]
histnum():	[extract(get(s([get(v(0),sensor_memory)]/name%1)),1,1)]
hasenergy?():	[truth(add(1,comp(get(s(%0/%1)),v(2))))]
takeenergy:	@%1 %0=sub(get(%0/%1),v(2))
```

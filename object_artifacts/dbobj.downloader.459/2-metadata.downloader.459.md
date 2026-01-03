# Downloader

## Name

Downloader - Sensor download utility

## Purpose

This object provides a `download` command that outputs a compact “sensor record” line for every object in range of the current ship (`v(us)`). Each record includes a display name, scaled relative position components, and coarse type/color/size classifications derived from the target’s mass. It also attempts to avoid re-sending data already present in a sensor-memory table.

## Metadata

```mud
Downloader(#459)
Owner: Ptah
Type: Thing
Bytes: 1554
Plane: 0
Created: Mon Dec  5 03:57:57 1994
Modified: Mon Dec  5 19:38:23 1994
Location: Ptah(#5745PDo)
Home: Ptah's Chambers(#10586R)
```

## Object Definition

### Attribute definitions

```mud
divby: inherit
see_if(): inherit function
get_obj_size(): inherit function
get_obj_type(): inherit function
flte(): inherit function
get_obj_color(): inherit function
spit_data(): inherit function
DownLoad: inherit
```

### Attribute list

```mud
flte(): [lnot(match(fcomp(v(1),v(0)),-1))]
get_obj_color(): [ifelse(flte(v(0),3E28),ifelse(flte(v(0),8E24),ifelse(flte(v(0),2E23),ifelse(flte(v(0),5E16),ifelse(flte(v(0),1E8),8,7),9),2),4),14)]
get_obj_type(): [ifelse(flte(v(0),3E28),ifelse(flte(v(0),8E24),ifelse(flte(v(0),2E23),ifelse(flte(v(0),5E16),ifelse(flte(v(0),1E8),Ship,Station),Moon),Terran),Jovian),Star)]
get_obj_size(): [ifelse(flte(v(0),3E28),ifelse(flte(v(0),8E24),ifelse(flte(v(0),2E23),ifelse(flte(v(0),5E16),ifelse(flte(v(0),1E8),1,2),4),8),16),32)]
see_if(): @swi [scomp(get(v(sensor_memory),strcat(memory,v(0))),NO MATCH)]=1,{},{@pem [v(2)]=[spit_data(v(0),v(1))]}
spit_data(): [histname(v(!),v(0))]|[fdiv(dx(v(us),v(0)),v(divby))]|[fdiv(dy(v(us),v(0)),v(divby))]|[fdiv(dz(v(us),v(0)),v(divby))]|[get_obj_type(get(v(0),mass))]|[get_obj_color(get(v(0),mass))]|[get_obj_size(get(v(0),mass))]|
divby: 1000000
DownLoad: $download:@foreach [inrange(v(us))] #=@swi v(0)=#,{@pem %#=[name(v(us))]|0.00|0.00|0.00|Ship|8|1},{@tr me/see_if=v(0),v(1),v(#)}
```

# Downloader

## Name

Downloader - Data Downloader Console

## Purpose

This is the Downloader legacy console object, used in older versions of the game to provide data downloading capabilities for spacecraft. It allows players to download sensor data about nearby objects and celestial bodies.

## Meta data

## Object Definition

### Attribute Definitions

```mush
divby: inherit program
see_if(): inherit function
get_obj_size(): inherit function
get_obj_type(): inherit function
flte(): inherit function
get_obj_color(): inherit function
spit_data(): inherit function
DownLoad: inherit program
```

### Attribute list

```mush
flte():	[lnot(match(fcomp(v(1),v(0)),-1))]
get_obj_color():	[ifelse(flte(v(0),3E28),ifelse(flte(v(0),8E24),ifelse(flte(v(0),2E23),ifelse(flte(v(0),5E16),ifelse(flte(v(0),1E8),8,7),9),2),4),14)]
get_obj_type():	[ifelse(flte(v(0),3E28),ifelse(flte(v(0),8E24),ifelse(flte(v(0),2E23),ifelse(flte(v(0),5E16),ifelse(flte(v(0),1E8),Ship,Station),Moon),Terran),Jovian),Star)]
get_obj_size():	[ifelse(flte(v(0),3E28),ifelse(flte(v(0),8E24),ifelse(flte(v(0),2E23),ifelse(flte(v(0),5E16),ifelse(flte(v(0),1E8),1,2),4),8),16),32)]
see_if():	@swi [scomp(get(v(sensor_memory),strcat(memory,v(0))),NO MATCH)]=1,{},{@pem [v(2)]=[spit_data(v(0),v(1))]}
spit_data():	[histname(v(!),v(0))]|[fdiv(dx(v(us),v(0)),v(divby))]|[fdiv(dy(v(us),v(0)),v(divby))]|[fdiv(dz(v(us),v(0)),v(divby))]|[get_obj_type(get(v(0),mass))]|[get_obj_color(get(v(0),mass))]|[get_obj_size(get(v(0),mass))]|
divby:	1000000
DownLoad:	$download:@foreach [inrange(v(us))] #=@swi v(0)=#,{@pem %#=[name(v(us))]|0.00|0.00|0.00|Ship|8|1},{@tr me/see_if=v(0),v(1),v(#)}
```

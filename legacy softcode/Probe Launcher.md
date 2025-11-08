# Probe Launcher

## Name

Probe Launcher - Softcode for launching probes

## Purpose

This file contains the softcode for launching probes at targets detected in sensor logs.

## Meta data

## Object Definition

### Attribute Definitions

```mush
launchprobe: inherit program
addprobe: inherit program
```

### Attribute list

```mush
addprobe:	@create ProbeHelm;@add con(me)=#26878;@fo owner(me)=@set [con(me)]=inherit;@set con(me)=!v;@helm v(0)=con(me);@set con(me)=us:%0;@tel con(me)=v(0);@aship v(0)=
launchprobe:	$launch probe at *:@swi histnum(v(!),v(0))=,{@pemit %#=That name does not exist in the sensor logs.},{@swi 3d(v(us),histnum(v(!),v(0)))=<200000,{@swi get([histnum(v(!),v(0))]/type)=SB,{@emit Probe Launched! Impact on [histname(v(!),histnum(v(!),v(0)))] in 2 minutes.;@wait 120={@tr me/addprobe={[histnum(v(!),v(0))]};@emit Probe Impacted!}},{@pemit %#=That is not a planet.}},{@pemit %#=You need to be within 200000km's of the target to launch a probe.}}}
```

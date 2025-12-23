# Memory System

## Name

Memory System - Spacecraft Memory Management Console

## Purpose

This is the Memory System legacy console object, used in older versions of the game to provide memory management capabilities for spacecraft. It includes various functions such as reading from and writing to memory cubes, erasing memory, and detecting the presence of memory cubes.

## Meta data

## Object Definition

### Attribute definitions

```mud
cube_attrnum(): inherit function
cube_num(): inherit function
detect_cube(): inherit function
erase_memory: inherit program
new_memory: inherit program
write_memory: inherit program
read_memory(): inherit function
```

### Attribute list

```mud
write_memory:	@swi detect_cube(v(3))=0,{@pemit %2=Memory Error: Memory Cube not present for recording data.},{@def [con(cube_num(v(3)))]/[if(lnot(scomp(get(s([cube_num(v(3))]/memory%0)),NO MATCH)),s(memory%0))];@memory%0 cube_num(v(3))=v(1);@swi wcount(lattrdef(con(cube_num(v(3)))))=>70,{@tr me/new_memory=%3}}
cube_attrnum():	[first(foreach(parents(cube_num(v(0))),{[if(scomp(get(s(%0/%1)),NO MATCH),v(0))]}))]
erase_memory:	@swi cube_num(v(2))=,{@pe %1=memory_error()},{@undefattr [cube_attrnum(v(2),v(0))]/%0}
cube_num():	[get(s(me/%0_memory))]
detect_cube():	[wcount(get(s(me/%0_memory)))]
new_memory:	@fo cube_num(v(0))={@create Memory Parent;@add me=con(me)}
read_memory():	[ifelse(cube_num(v(1)),get(s([cube_num(v(1))]/memory%0)),NO MEMORY)]
```

# `Frontier Storm Door Master`

## Attribute list (MARE2 conversion)

```mud
@@ -----------------------------
@@ OBJECT: Frontier Storm Door Master(#27234)
@@ LOCATION: Captain's Safe(#43072)
@@ -----------------------------

---cut---
@@ Teleport to object location as a convenience
@teleport me=#43072
---cut---

@@ ATTRIBUTE: Frontier Storm Door Master/AutoClose
@@ -------------------------------------------

---cut---
@defattr #27234/AutoClose=inherit program
---cut---
&AutoClose #27234=@@ Converted by AI
  sleep 15
  if wmatch(get(me,flags),OPEN)
    call me/Closedoor
    call get(me,Otherside)/Closedoor
  endif
---cut---

@@ ATTRIBUTE: Frontier Storm Door Master/AutoOpen
@@ -------------------------------------------

---cut---
@defattr #27234/AutoOpen=inherit program
---cut---
&AutoOpen #27234=@@ Converted by AI
  @@ Ensure both sides are OPEN
  @flags me=ifelse(wmatch(v(flags),OPEN),v(flags),strcat(strcat(OPEN,spc(1)),v(flags)))
  @flags v(otherside)=ifelse(wmatch(get(v(otherside),flags),OPEN),get(v(otherside),flags),strcat(strcat(OPEN,spc(1)),get(v(otherside),flags)))

  @@ Queue the actor in the semaphore list
  @semaphore me=strcat(strcat(v(0),spc(1)),v(semaphore))

  @@ Legacy used @swi; model it as a structured switch on the last queued entry
  switch extract(v(semaphore),wcount(v(semaphore)),1)
    case %0
      call me/Godoor=%0
      break
    default
      call me/Passthrough=%0
      break
  endswitch

  @@ Legacy semaphore-advancement delay
  sleep 3
  @force me=@force me=@semaphore me
---cut---

@@ ATTRIBUTE: Frontier Storm Door Master/Godoor
@@ -----------------------------------------

---cut---
@defattr #27234/Godoor=inherit program
---cut---
&Godoor #27234=@@ Converted by AI
  @pemit %0=s(v(doorsucc))
  @oemit %0=s(v(doorosucc))
  @force v(otherside)=@emit {[s(v(doorodrop))]}
  @force me=@tel %0=link(me)

  @@ Optional auto-close
  if wmatch(v(flags),AUTOCLOSE)
    call me/AutoClose
  endif

  @@ XOR locking of related doors
  for 8=v(XORList)
    for 9=children(parents(me))
      if match(get(s(v(9)),ID),[v(8)]*)
        call v(9)/lockup
      endif
    done
  done
---cut---

@@ ATTRIBUTE: Frontier Storm Door Master/Opendoor
@@ -------------------------------------------

---cut---
@defattr #27234/Opendoor=inherit program
---cut---
&Opendoor #27234=@@ Converted by AI
  @flags me=ifelse(wmatch(get(me,flags),OPEN),get(me,flags),strcat(strcat(OPEN,get(me,sp)),get(me,flags)))
  @emit The door %[get(me,leading)%] slides open.

  @@ XOR locking of related doors
  for 8=get(me,XORList)
    for 9=children(parents(me))
      if match(get(s(v(9)),ID),[v(8)]*)
        call v(9)/lockup
      endif
    done
  done
---cut---

@@ ATTRIBUTE: Frontier Storm Door Master/Passthrough
@@ ----------------------------------------------

---cut---
@defattr #27234/Passthrough=inherit program
---cut---
&Passthrough #27234=@@ Converted by AI
  sleep 1
  @pemit %0=v(succ)
  @oemit %0=You see [name(v(0))] go through the open door %%%[v(leading)].
  @force v(otherside)=@emit You see [name(v(0))] come in through the open door [get(s(v(otherside)),leading)].
  @force me=@tel %0=link(me)
---cut---

@@ ATTRIBUTE: Frontier Storm Door Master/Closedoor
@@ ---------------------------------------------

---cut---
@defattr #27234/Closedoor=inherit program
---cut---
&Closedoor #27234=@@ Converted by AI
  @flags me=ifelse(wmatch(get(me,flags),OPEN),remove(get(me,flags),wmatch(get(me,flags),OPEN),1),get(me,flags))
  @emit The door %[get(me,leading)%] slides shut.

  @@ XOR unlocking of related doors
  for 8=get(me,XORList)
    for 9=children(parents(me))
      if match(get(s(v(9)),ID),[v(8)]*)
        call v(9)/unlock
      endif
    done
  done
---cut---

@@ ATTRIBUTE: Frontier Storm Door Master/Override
@@ --------------------------------------------

---cut---
@defattr #27234/Override=inherit program
---cut---
@@ No value to convert, skip this attribute
---cut---

@@ ATTRIBUTE: Frontier Storm Door Master/Otherside
@@ ---------------------------------------------

---cut---
@defattr #27234/Otherside=program
---cut---
@@ No value to convert, skip this attribute
---cut---

@@ ATTRIBUTE: Frontier Storm Door Master/XORList
@@ -------------------------------------------

---cut---
@defattr #27234/XORList=program
---cut---
@@ No value to convert, skip this attribute
---cut---

@@ ATTRIBUTE: Frontier Storm Door Master/doorsucc
@@ --------------------------------------------

---cut---
@defattr #27234/doorsucc=inherit
---cut---
&doorsucc #27234=The door [get(me,leading)] slides open and you go through.
---cut---

@@ ATTRIBUTE: Frontier Storm Door Master/doorosucc
@@ ---------------------------------------------

---cut---
@defattr #27234/doorosucc=inherit
---cut---
&doorosucc #27234=The door [get(me,leading)] slides open and [name(v(0))] goes through.
---cut---

@@ ATTRIBUTE: Frontier Storm Door Master/doorodrop
@@ ---------------------------------------------

---cut---
@defattr #27234/doorodrop=inherit
---cut---
&doorodrop #27234=The door [get(s(get(me,Otherside)),leading)] slides open and [name(v(0))] comes in.
---cut---

@@ ATTRIBUTE: Frontier Storm Door Master/Locked
@@ ------------------------------------------

---cut---
@defattr #27234/Locked=inherit program
---cut---
&Locked #27234=@@ Converted by AI
  @pemit %0=The door refuses to open and you notice that the door panel has a red light on instead of a green light.
  @oemit %0=The door refuses to open and [name(v(0))] notices that there is a red light on the door panel instead of a green light.
---cut---

@@ ATTRIBUTE: Frontier Storm Door Master/Nonactive
@@ ---------------------------------------------

---cut---
@defattr #27234/Nonactive=inherit program
---cut---
&Nonactive #27234=@@ Converted by AI
  @pemit %0=The door doesn't open and you notice that the lights on the door panel are turned off.
  @oemit %0=The door doesn't open and [name(v(0))] notices that the lights on the door panel are turned off.
---cut---

@@ ATTRIBUTE: Frontier Storm Door Master/flags
@@ -----------------------------------------

---cut---
@defattr #27234/flags=program
---cut---
@@ No value to convert, skip this attribute
---cut---

@@ ATTRIBUTE: Frontier Storm Door Master/semaphore
@@ ---------------------------------------------

---cut---
@defattr #27234/semaphore=program
---cut---
@@ No value to convert, skip this attribute
---cut---

@@ ATTRIBUTE: Frontier Storm Door Master/sp
@@ --------------------------------------

---cut---
@defattr #27234/sp=inherit program
---cut---
@@ No value to convert, skip this attribute
---cut---

@@ ATTRIBUTE: Frontier Storm Door Master/ID
@@ --------------------------------------

---cut---
@defattr #27234/ID=program
---cut---
@@ No value to convert, skip this attribute
---cut---

@@ ATTRIBUTE: Frontier Storm Door Master/leading
@@ -------------------------------------------

---cut---
@defattr #27234/leading=program
---cut---
@@ No value to convert, skip this attribute
---cut---

@@ ATTRIBUTE: Frontier Storm Door Master/lookthrough
@@ ------------------------------------------------

---cut---
@defattr #27234/lookthrough=inherit program
---cut---
&lookthrough #27234=@@ Converted by AI
  @pemit %0=name(link(me))
  @pemit %0=get(s(link(me)),desc)

  if wcount(get(s(link(me)),succ))
    @pemit %0=get(s(link(me)),succ)
  endif

  if con(link(me))
    @pemit %0=Contents:
    for 8=objlist(con(link(me)))
      if flags(v(8))=*D*
        continue
      endif
      @pemit %0=name(v(8))
    done
  endif
---cut---

@@ ATTRIBUTE: Frontier Storm Door Master/lockup
@@ ------------------------------------------

---cut---
@defattr #27234/lockup=inherit program
---cut---
&lockup #27234=@@ Converted by AI
  if v(flags)=*LOCKED*
    @@ Already locked
  else
    @emit The door %[get(me,leading)%] goes *click* and the green circle on the door panel changes to a red triangle.
  endif
  @flags me=ifelse(wmatch(v(flags),LOCKED),v(flags),strcat(strcat(LOCKED,spc(1)),v(flags)))
---cut---

@@ ATTRIBUTE: Frontier Storm Door Master/unlock
@@ ------------------------------------------

---cut---
@defattr #27234/unlock=inherit program
---cut---
&unlock #27234=@@ Converted by AI
  if v(flags)=*LOCKED*
    @emit The door %[get(me,leading)%] goes *click* and the red triangle on the door panel changes to a green circle.
  endif
  @flags me=ifelse(wmatch(v(flags),LOCKED),remove(v(flags),wmatch(v(flags),LOCKED),1),v(flags))
---cut---

@@ ATTRIBUTE: Frontier Storm Door Master/level
@@ -----------------------------------------

---cut---
@defattr #27234/level=program
---cut---
@@ No value to convert, skip this attribute
---cut---

@@ ATTRIBUTE: Frontier Storm Door Master/noentry
@@ --------------------------------------------

---cut---
@defattr #27234/noentry=inherit program
---cut---
&noentry #27234=@@ Converted by AI
  @pemit %0=The door refuses to open and just buzzes at you.
  @oemit %0=The door refuses to open for [name(v(0))] and just buzzes at %1.
---cut---

@@ ATTRIBUTE: Frontier Storm Door Master/OnFail
@@ ------------------------------------------

---cut---
@@ Built-in attribute, no need to @defattr
---cut---
&OnFail #27234=@@ Converted by AI
  if wmatch(v(flags),OPEN)=0
    @oemit %#=You see %n press the open button on the door %[v(leading)].
    call me/[ifelse(wmatch(v(flags),ACTIVE),ifelse(wmatch(v(flags),LOCKED),locked,ifelse(scomp(sgn(add(v(level),extract(v(roster),add(wmatch(v(roster),owner(v(#))),1),1))),-1),autoopen,noentry)),nonactive)]=%#,%o
  else
    call me/Passthrough=%#,%o
  endif
---cut---

@@ ATTRIBUTE: Frontier Storm Door Master/OnLook
@@ ------------------------------------------

---cut---
@@ Built-in attribute, no need to @defattr
---cut---
&OnLook #27234=@@ Converted by AI
  print [ifelse(wmatch(get(me,flags),ACTIVE),ifelse(wmatch(get(me,flags),LOCKED),On the door panel you see a red triangle lit.,On the door panel you see a green circle lit.),The lights on the door panel seem to be turned off.)] The door panel has the ID #[get(me,ID)]. [ifelse(wmatch(get(me,flags),OPEN),The door is currently open and you can see into the next room.,ifelse(wmatch(get(me,flags),WINDOW),The door is closed but there is a window on the door that allows you to see into the next room.,The door is closed tight and has no window on it.))]

  if lor(wmatch(get(me,flags),OPEN),wmatch(get(me,flags),WINDOW))
    call me/lookthrough=%#
  endif
---cut---

@@ ATTRIBUTE: Frontier Storm Door Master/Desc
@@ ----------------------------------------

---cut---
@@ Built-in attribute, no need to @defattr
---cut---
&Desc #27234=You see a large metal sliding door in the shape of an elongated octagon.
---cut---

@@ ATTRIBUTE: Frontier Storm Door Master/doorsucc (built-in Succ)
@@ -----------------------------------------------------------

---cut---
@@ Built-in attribute, no need to @defattr
---cut---
&Succ #27234=You go through the open door.
---cut---

@@ ATTRIBUTE: Frontier Storm Door Master/Fail
@@ ----------------------------------------

---cut---
@@ Built-in attribute, no need to @defattr
---cut---
&Fail #27234=You walk up to the door.
---cut---

@@ ATTRIBUTE: Frontier Storm Door Master/OnSucc
@@ ------------------------------------------

---cut---
@@ Built-in attribute, no need to @defattr
---cut---
&OnSucc #27234=@@ Converted by AI
  @force get(me,Otherside)=@oemit %#=You see %n come in through the open door [get(s(get(me,Otherside)),leading)].
  @emit You see %n go through the open door [get(me,leading)].
---cut---
```

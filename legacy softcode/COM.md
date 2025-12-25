# COM - Communications Console

## Name

COM - Communications Console

## Purpose

This is the COM legacy console object, used in older versions of the game to provide communication capabilities for spacecraft. It includes various communication functions such as sending and receiving messages, initiating voice communications, and managing communication channels.

## Meta data

```mud
Name: COM
Type: Thing
```

## Object Definition

### Attribute definitions

```mud
channum(): inherit function
invalidradio: inherit program
compoweroff: inherit program
compowerlow: inherit program
com_power(): inherit function
informmessage(): inherit function
handlesentmsg: inherit program
com_alarm_check: inherit program
com_alarm: program
com_indicator: inherit program
msg_slots: inherit program
com_log_cmd: inherit program
com_msg10: inherit program
com_msg9: inherit program
com_msg8: inherit program
com_msg7: inherit program
com_msg6: inherit program
com_msg5: inherit program
com_msg4: inherit program
com_msg3: inherit program
com_msg2: inherit program
com_msg1: inherit program
com_info3: inherit program
com_info2: inherit program
com_transmit_cmd: inherit program
com_channel_cmd: inherit program
com_video_cmd: inherit program
com_wordoff_cmd: inherit program
com_word_cmd: inherit program
com_range_cmd: inherit program
com_id_cmd: inherit program
com_carrier_cmd: inherit program
com_power_cmd: inherit program
_attrdef33(): inherit function
com_status_cmd: inherit program
com_word(): inherit function
_attrdef36(): inherit function
yesno(): inherit function
com_status(): inherit function
com_flag10: inherit program
com_flag9: inherit program
com_flag8: inherit program
com_flag7: inherit program
com_flag6: inherit program
com_flag5: inherit program
com_flag4: inherit program
showmessage: inherit program
com_header(): inherit function
displaymessage(): inherit function
_attrdef49(): inherit function
com_flag3: inherit program
com_flag2: inherit program
com_flag1: inherit program
com_video: program
channels(): inherit function
```

### Attribute list

```mud
&com_channel_cmd com=$com channel *=*:/[get(me/com_man)]/@swi land(range?(v(1),1,999),range?(v(0),1,wcount(channels(v(us)))))=0,{@pemit %#=v(invalidradio)},{@pemit %#=Channel set.;@channel v(us)=set_word(channels(v(us)),v(1),v(0));@swi land(match(channum(v(us),v(0)),strcat(v(0),v(1))),land(com_word(v(0),1),com_word(v(0),3)))=0,,{@tr me/com_carrier_change=[channum(v(us),v(0))],0;@tr me/com_carrier_change=%0%1,1}}

&showmessage com=@pemit get(me/com_man)={%[displaymessage(v(0),v(5),v(1),v(2),v(3),v(4))]};@com_msg[first(get(me/msg_slots))] me=join(time(),displaymessage(v(0),v(5),v(1),v(2),v(3),v(4)));@msg_slots me=join(rest(get(me/msg_slots)),first(get(me/msg_slots)));@swi get(me/com_man)=,{@emit v(com_indicator)}

&com_log_cmd com=$com log:@foreach get(me/msg_slots)=@pemit %#={%%%[get(me/com_msg%%0)]}

&channels() com=[get(s(%0/channel))]

channum() com=[extract(channels(v(0)),v(1),1)]

&handlesentmsg com=@pwrcomm me=sub(get(me/pwrcomm),com_power(v(0)));@com_msg[first(get(me/msg_slots))] me=join(time(),informmessage(v(0),v(1),com_power(v(0))));@msg_slots me=join(rest(get(me/msg_slots)),first(get(me/msg_slots)))

&informmessage() com=[s(Outgoing Signal Power Used: %2 Channel %0/[channum(v(us),v(0))]: [v(1)])]

&com_header() com=[s(Incoming Signal: [fdiv(pow(v(4),2),pow(3d(v(5),v(us)),2))] Bearing:[velhdg(dx(v(5),v(us)),dy(v(5),v(us)),dz(v(5),v(us)))] Channel %0/[channum(v(us),v(0))])]

&com_status() com=[ljust(s(%0/[channum(v(us),v(0))]),7)] | [rjust(yesno(com_word(v(0),1)),4)] % | [rjust(yesno(com_word(v(0),2)),3)] | [rjust(ifelse(comp(get(me/com_video),v(0)),OFF,ON),4)] % | [rjust(yesno(com_word(v(0),3)),5)] % % | [rjust(com_word(v(0),4),15)] | [ifelse(scomp(com_word(v(0),5),*),mid(com_word(v(0),5),1,strlen(com_word(v(0),5))),<None>)]

&com_status_cmd com=$com status:/[get(me/com_man)]/@pemit %#=Channel | Power | ID? | Video | Carrier | Broadcast Range | Encryption Word;@pemit %#=--------+-------+-----+-------+---------+-----------------+----------------;@foreach rest(lnum(add(1,wcount(channels(v(us))))))=@pemit %#=com_status(v(0))

&com_video_cmd com=$com video *:/[get(me/com_man)]/@pemit %#=Video mode is currently unavailable.

&com_wordoff_cmd com=$com noencrypt *:/[get(me/com_man)]/@swi range?(v(0),1,wcount(channels(v(us))))=0,{@pemit %#=v(invalidradio)},{@com_flag%0 me=set_word(get(me/com_flag%0),*,5);@pemit %#=Radio %0 is now using no encryption.}

&com_word_cmd com=$com encrypt *=*:/[get(me/com_man)]/@swi range?(v(0),1,wcount(channels(v(us))))=0,{@pemit %#=v(invalidradio)},{@swi wcount(v(1))=1,{@com_flag%0 me=set_word(get(me/com_flag%0),strcat(*,v(1)),5);@pemit %#=Traffic on Radio %0 is now encrypted with keyword '%1'},{@pemit %#=Illegal Keyword. You need to use a one-word encryption keyword.}}
&com_range_cmd com=$com range *=*:/[get(me/com_man)]/@swi range?(v(0),1,wcount(channels(v(us))))=0,{@pemit %#=v(invalidradio)},{@com_flag%0 me=set_word(get(me/com_flag%0),simp(fadd(0,v(1))),4);@pemit %#=Broadcast Range on Radio %0 is now set to %%%[simp(fadd(0,v(1)))]km's}
&com_carrier_cmd com=$com carrier *=*:/[get(me/com_man)]/@swi range?(v(0),1,wcount(channels(v(us))))=0,{@pemit %#=v(invalidradio)},{@com_flag%0 me=set_word(get(me/com_flag%0),yesno?(v(1)),3);@pemit %#=Carrier Signal on Radio %0 is now turned %%%[yesno(yesno?(v(1)))];@swi [com_word(v(0),3)]=[yesno?(v(1))],,{@tr me/com_carrier_change=[channum(v(us),v(0))],[yesno?(v(1))]}
&com_id_cmd com=$com id *=*:/[get(me/com_man)]/@swi range?(v(0),1,wcount(channels(v(us))))=0,{@pemit %#=v(invalidradio)},{@com_flag%0 me=set_word(get(me/com_flag%0),yesno?(v(1)),2);@pemit %#=ID Signal on Radio %0 is now turned %%%[yesno(yesno?(v(1)))]}
&com_power_cmd com=$com power *=*:/[get(me/com_man)]/@swi range?(v(0),1,wcount(channels(v(us))))=0,{@pemit %#=v(invalidradio)},{@com_flag%0 me=set_word(get(me/com_flag%0),yesno?(v(1)),1);@pemit %#=Power on Radio %0 is now turned %%%[yesno(yesno?(v(1)))];@swi land(com_word(v(0),3),lxor([yesno?(v(1))],[com_word(v(0),1)]))=0,,{@tr me/com_carrier_change=[channum(v(us),v(0))],[yesno?(v(1))]}}}
&_attrdef33() com=[ifelse(lor(match(v(0),y*),match(v(0),on)),1,0)]
&com_word() com=[extract(get(s(me/com_flag%0)),v(1),1)]
&yesno():	[ifelse(v(0),ON,OFF)]
&_attrdef36() com=[land(lt(v(0),add(1,v(2))),gt(v(0),sub(1,v(1))))]
com_flag1:	0 0 0 100000 *
com_flag2:	0 0 0 100000 *
com_flag3:	0 0 0 100000 *
com_flag4:	0 0 0 100000 *
com_flag5:	0 0 0 100000 *
com_flag6:	0 0 0 100000 *
com_flag7:	0 0 0 100000 *
com_flag8:	0 0 0 100000 *
com_flag9:	0 0 0 100000 *
com_flag10:	0 0 0 100000 *
&com_info2 com=@pemit %0=com id <Radio#>=<on/off> : Turn identification signal on/off for radio;@pemit %0=com carrier <Radio#>=<on/off> : Turn carrier signal on/off for radio;@pemit %0=com encrypt <Radio#>=<codeword> : Set radio to encrypt/decrypt using the word;@pemit %0=com noencrypt <Radio#> : Turn off encryption of that radio;@pemit %0=com video <Radio#> : Set radio for video mode(viewscreen);@pemit %0=transmit <Radio#>=<Msg> : Transmit a message over the radio;@tr me/com_info3=%0
msg_slots:	1 2 3 4 5 6 7 8 9 10
com_msg1:	Empty Msg1
com_msg2:	Empty Msg2
com_msg3:	Empty Msg3
com_msg4:	Empty Msg4
com_msg5:	Empty Msg5
com_msg6:	Empty Msg6
com_msg7:	Empty Msg7
com_msg8:	Empty Msg8
com_msg9:	Empty Msg9
com_msg10: Empty Msg10
&com_indicator com=*BEEP* A red message indicator light blinks on the Communications Station, indicating a received message.
&com_info3 com=@pemit %0=com log : Display a log of the last 10 received messages;@pemit %0=Current Radio Standards: Channel 911 is used for ships needing emergency assistance. Channel 555 is being considered the universal ship to ship chatter channel for normal use. Channel 200 will be used for communicating with automated landing, launching, and docking facilities.
&_attrdef49() com=[if(add(0,com_flag(v(0),1)),ifelse(scomp(get(me/com_video),v(0)),1,2))]
displaymessage():	[ifelse(scomp(com_word(v(0),5),v(2)),join(com_header(v(0),v(1),v(2),v(3),v(4),v(5)),<Static>......<hiss>....),strcat(join(com_header(v(0),v(1),v(2),v(3),v(4),v(5)),if(v(3),strcat(name(v(5)),if(get(s(%5/shipname)),s({([get(s(%5/shipname))])}))))),join(:,v(1))))]
&compoweroff com=Power on Radio %0 is currently turned OFF. No message sent.
&invalidradio com=You must use a valid radio number. Valid #'s are from '1' to '[wcount(channels(v(us)))]'.
&compowerlow com=Not enough power allocated to communications to transmit.
&com_power() com=[add(0,fdiv(com_word(v(0),4),100000000))]
&com_transmit_cmd com=$transmit *=*:/[get(me/com_man)]/@swi ifelse(range?(v(0),1,wcount(channels(v(us)))),ifelse(com_word(v(0),1),ifelse(hasenergy?(v(!),pwrcomm,com_power(v(0))),1,0),-1),-2)=-2,{@pemit %#=v(invalidradio)},-1,{@pemit %#=v(compoweroff)},0,{@pemit %#=v(compowerlow)},1,{@pemit %#=Message Transmitted: %[com_power(v(0))] power used.;[ifelse(inspace(v(us)),s({!comevent v(us)=[com_word(v(0),4)],[channum(v(us),v(0))],[com_word(v(0),5)],[com_word(v(0),2)],v(1)}),s({@tr [loc(v(us))]/Comm_Signal=Comm,[channum(v(us),v(0))],[com_word(v(0),4)],*,1,[v(us)],v(1)}))];@tr me/handlesentmsg=v(0),v(1)}
````

## English Logic Descriptions (Legacy Attribute List)

### `com_channel_cmd` — English description

```text
Attribute: com_channel_cmd

Player command (legacy pattern):
- com channel <radio#>=<channel#>
- Access lock: /[get(me/com_man)]/ (must be manning the COM console)

Logic:
1) Validate inputs:
   - Channel number v(1) must be in 1..999
   - Radio number v(0) must be in 1..wcount(channels(v(us)))
   - If invalid: print v(invalidradio) and stop.
2) If valid:
   - Tell player: "Channel set."
   - Update the ship’s channel list: set the radio slot (v(0)) to the channel value (v(1)).
3) If the effective tuned channel identity changed OR the radio’s power/carrier flags imply a broadcast state change:
   - Trigger me/com_carrier_change with the new channel info and a mode flag (0/1) to update carrier/broadcast state externally.
Notes:
- Uses helper functions: channels(v(us)), channum(v(us),radio), com_word(radio,<field>).
```

### `showmessage` — English description

```text
Attribute: showmessage

Invocation context:
- Not a direct player $command; called when an incoming message should be displayed/logged.

Logic:
1) pemit to the current console operator (get(me/com_man)) a formatted message:
   - displaymessage(...) renders header + optional ship ID + message body, with encryption/static handling.
2) Store the formatted message into the next rotating message slot:
   - Writes into com_msg<N> where N=first(msg_slots)
   - Prefixes with time()
   - Rotates msg_slots so the next incoming message uses the next slot.
3) If nobody is manning the console (get(me/com_man)= empty):
   - emit the com_indicator text to the room to indicate a pending message.
```

### `com_log_cmd` — English description

```text
Attribute: com_log_cmd

Player command (legacy pattern):
- com log
- Access lock: /[get(me/com_man)]/

Logic:
1) Iterate over msg_slots (list of slot numbers 1..10).
2) For each slot number N:
   - pemit to the player the stored log line from attribute com_msgN.
Result:
- Displays the last ~10 received (or stored) messages in rotation order.
```

### `channels()` / `channum()` — English description

```text
Attribute: channels()

Logic:
- Returns the channel list from the target object’s /channel attribute:
  channels(obj) == get(s(obj/channel))

Attribute: channum()

Logic:
- Given a ship (v(0)) and a radio index (v(1)):
  returns the channel number at that index from channels(ship).
```

### `handlesentmsg` — English description

```text
Attribute: handlesentmsg

Invocation context:
- Triggered after a successful transmit to account/log usage.

Logic:
1) Subtract the computed transmission power cost from this console's pwrcomm:
   - @pwrcomm me=sub(get(me/pwrcomm),com_power(radio))
2) Log an outgoing info line into the next rotating com_msg slot:
   - informmessage(radio,msg,cost) produces "Outgoing Signal Power Used: ..."
   - Rotate msg_slots similarly to showmessage.
```

### `informmessage()` — English description

```text
Attribute: informmessage()

Logic:
- Formats an outgoing transmit log line including:
  - power used
  - radio number and derived channel display (radio/channum)
  - the message text
```

### `com_header()` — English description

```text
Attribute: com_header()

Logic:
- Builds the "Incoming Signal" header line, including:
  - a derived signal strength term based on power and distance (3d(...))
  - bearing computed from relative vector (dx/dy/dz + velhdg)
  - radio number and derived channel label (radio/channum)
```

### `displaymessage()` — English description

```text
Attribute: displaymessage()

Inputs (by position usage):
- radio index, message text, encryption word, ID flag, power, sender object (v(5))

Logic:
1) If the radio's configured encryption keyword (com_word(radio,5)) does NOT match the message’s encryption word:
   - Return header + "<Static>......<hiss>...." (scrambled).
2) Else:
   - Return header + optional sender identification:
     - If ID flag is on, include sender name and optionally sender shipname
   - Append ":" + message text.
```

### `com_status()` / `com_status_cmd` — English description

```text
Attribute: com_status()

Logic:
- Produces a formatted per-radio status line showing fields for a given radio:
  - channel label
  - power on/off
  - ID on/off
  - video on/off (based on com_video match)
  - carrier on/off
  - broadcast range
  - encryption keyword (or <None>)

Attribute: com_status_cmd

Player command (legacy pattern):
- com status
- Access lock: /[get(me/com_man)]/

Logic:
1) Print a header row and separator row.
2) For each radio index from 1..wcount(channels(v(us))):
   - Print com_status(radio).
```

### `com_video_cmd` — English description

```text
Attribute: com_video_cmd

Player command (legacy pattern):
- com video <radio#>
- Access lock: /[get(me/com_man)]/

Logic:
- Always informs the player that video mode is currently unavailable.
```

### `com_wordoff_cmd` / `com_word_cmd` — English description

```text
Attribute: com_wordoff_cmd

Player command (legacy pattern):
- com noencrypt <radio#>
- Access lock: /[get(me/com_man)]/

Logic:
1) Validate radio index is in range; else print v(invalidradio).
2) Set encryption word field (word 5) on com_flag<radio#> to '*' (no encryption).
3) Tell player: "Radio <n> is now using no encryption."

Attribute: com_word_cmd

Player command (legacy pattern):
- com encrypt <radio#>=<keyword>
- Access lock: /[get(me/com_man)]/

Logic:
1) Validate radio index; else print v(invalidradio).
2) Validate keyword is a single word (wcount(v(1))=1); else print an error.
3) Store encryption keyword into com_flag<radio#> field 5, formatted as "*<keyword>".
4) Tell player which keyword is now in use.
```

### `com_range_cmd` — English description

```text
Attribute: com_range_cmd

Player command (legacy pattern):
- com range <radio#>=<range_km>
- Access lock: /[get(me/com_man)]/

Logic:
1) Validate radio index; else print v(invalidradio).
2) Store broadcast range (field 4) on com_flag<radio#> as a sanitized numeric (simp(fadd(0,v(1)))).
3) Tell player the new broadcast range in km.
```

### `com_carrier_cmd` / `com_id_cmd` / `com_power_cmd` — English description

```text
Attribute: com_carrier_cmd

Player command (legacy pattern):
- com carrier <radio#>=<on/off>
- Access lock: /[get(me/com_man)]/

Logic:
1) Validate radio index; else print v(invalidradio).
2) Store carrier enable flag (field 3) on com_flag<radio#>.
3) Tell player carrier is now ON/OFF.
4) If carrier state changed compared to previous com_word(radio,3):
   - Trigger me/com_carrier_change with channel identity and new carrier state.

Attribute: com_id_cmd

Player command (legacy pattern):
- com id <radio#>=<on/off>
- Access lock: /[get(me/com_man)]/

Logic:
1) Validate radio index; else print v(invalidradio).
2) Store ID enable flag (field 2) on com_flag<radio#>.
3) Tell player ID is now ON/OFF.

Attribute: com_power_cmd

Player command (legacy pattern):
- com power <radio#>=<on/off>
- Access lock: /[get(me/com_man)]/

Logic:
1) Validate radio index; else print v(invalidradio).
2) Store power enable flag (field 1) on com_flag<radio#>.
3) Tell player power is now ON/OFF.
4) If the power toggle implies the carrier/broadcast state must be updated:
   - Trigger me/com_carrier_change with channel identity and new state.
```

### `invalidradio` / `compoweroff` / `compowerlow` / `com_power()` — English description

```text
Attribute: invalidradio
- Error string telling user valid radio numbers are 1..wcount(channels(v(us))).

Attribute: compoweroff
- Error string: radio power is OFF, so no message is sent.

Attribute: compowerlow
- Error string: not enough allocated comm power to transmit.

Attribute: com_power()
Logic:
- Converts the configured numeric range/power field (com_word(radio,4)) into a power cost scalar:
  com_power(radio) == fdiv(com_word(radio,4),100000000) (then add(0,...) to coerce numeric).
```

### `com_transmit_cmd` — English description

```text
Attribute: com_transmit_cmd

Player command (legacy pattern):
- transmit <radio#>=<message>
- Access lock: /[get(me/com_man)]/

Logic:
1) Validate radio index is in range; if not: print v(invalidradio).
2) Validate the radio power flag com_word(radio,1) is ON; if not: print v(compoweroff).
3) Validate the ship has enough comm energy to pay com_power(radio):
   - hasenergy?(v(!),pwrcomm,com_power(radio))
   - if not enough: print v(compowerlow).
4) On success:
   - Tell player "Message Transmitted: <cost> power used."
   - If ship is in space:
       invoke a space-sim event to propagate the comm signal (!comevent) with:
       configured range/power, derived channel number, encryption word, ID flag, and message text.
     Else (not in space):
       trigger a room/area Comm_Signal handler on the ship's location with similar parameters.
   - Trigger me/handlesentmsg=radio,message to subtract power and log the outgoing message locally.
````

## MARE 2.0 Converted Softcode (from Legacy Attribute List)

```mud
@@ --------------------
@@ Commands (player-invoked)
@@ --------------------

@@ legacy: $com channel *=*:/[get(me/com_man)]/...
&com_channel_cmd com=:/[get(me,com_man)]/2$com channel:
switch land(range?(v(1),1,999),range?(v(0),1,wcount(channels(v(us)))))=0
    print v(invalidradio)
else
    print Channel set.
    @@ Preserve legacy argument ordering to avoid behavior changes
    @channel v(us)=set_word(channels(v(us)),v(1),v(0))

    @@ legacy: @swi land(...)=0,,{...triggers...}
    switch land(match(channum(v(us),v(0)),strcat(v(0),v(1))),land(com_word(v(0),1),com_word(v(0),3)))=0
        @@ no-op
    else
        call me/com_carrier_change=[channum(v(us),v(0))],0
        @@ legacy used %0%1 concatenation; keep as-is
        call me/com_carrier_change=%0%1,1
    endswitch
endswitch

@@ legacy: $com log:/[get(me/com_man)]/@foreach ...
&com_log_cmd com=:/[get(me,com_man)]/0$com log:
foreach get(me,msg_slots)
    @@ NOTE: keep legacy dynamic get() form for com_msg%N
    @pemit %#={%%%[get(me/com_msg%%0)]}
endfor

@@ legacy: $com status:/[get(me/com_man)]/...
&com_status_cmd com=:/[get(me,com_man)]/0$com status:
print Channel | Power | ID? | Video | Carrier | Broadcast Range | Encryption Word
print --------+-------+-----+-------+---------+-----------------+----------------
foreach rest(lnum(add(1,wcount(channels(v(us))))))
    print com_status(v(0))
endfor

@@ legacy: $com video *:/[get(me/com_man)]/...
&com_video_cmd com=:/[get(me,com_man)]/1$com video:
print Video mode is currently unavailable.

@@ legacy: $com noencrypt *:/[get(me/com_man)]/...
&com_wordoff_cmd com=:/[get(me,com_man)]/1$com noencrypt:
switch range?(v(0),1,wcount(channels(v(us))))=0
    print v(invalidradio)
else
    @com_flag%0 me=set_word(get(me,com_flag%0),*,5)
    print Radio %0 is now using no encryption.
endswitch

@@ legacy: $com encrypt *=*:/[get(me/com_man)]/...
&com_word_cmd com=:/[get(me,com_man)]/2$com encrypt:
switch range?(v(0),1,wcount(channels(v(us))))=0
    print v(invalidradio)
else
    switch wcount(v(1))=1
        @com_flag%0 me=set_word(get(me,com_flag%0),strcat(*,v(1)),5)
        print Traffic on Radio %0 is now encrypted with keyword '%1'
    else
        print Illegal Keyword. You need to use a one-word encryption keyword.
    endswitch
endswitch

@@ legacy: $com range *=*:/[get(me/com_man)]/...
&com_range_cmd com=:/[get(me,com_man)]/2$com range:
switch range?(v(0),1,wcount(channels(v(us))))=0
    print v(invalidradio)
else
    @com_flag%0 me=set_word(get(me,com_flag%0),simp(fadd(0,v(1))),4)
    print Broadcast Range on Radio %0 is now set to %[simp(fadd(0,v(1)))]km's
endswitch

@@ legacy: $com carrier *=*:/[get(me/com_man)]/...
&com_carrier_cmd com=:/[get(me,com_man)]/2$com carrier:
switch range?(v(0),1,wcount(channels(v(us))))=0
    print v(invalidradio)
else
    @com_flag%0 me=set_word(get(me,com_flag%0),yesno?(v(1)),3)
    print Carrier Signal on Radio %0 is now turned %[yesno(yesno?(v(1)))]

    @@ legacy: @swi [com_word()]=[yesno?()],,{@tr ...}
    switch com_word(v(0),3)=[yesno?(v(1))]
        @@ no-op
    else
        call me/com_carrier_change=[channum(v(us),v(0))],[yesno?(v(1))]
    endswitch
endswitch

@@ legacy: $com id *=*:/[get(me/com_man)]/...
&com_id_cmd com=:/[get(me,com_man)]/2$com id:
switch range?(v(0),1,wcount(channels(v(us))))=0
    print v(invalidradio)
else
    @com_flag%0 me=set_word(get(me,com_flag%0),yesno?(v(1)),2)
    print ID Signal on Radio %0 is now turned %[yesno(yesno?(v(1)))]
endswitch

@@ legacy: $com power *=*:/[get(me/com_man)]/...
&com_power_cmd com=:/[get(me,com_man)]/2$com power:
switch range?(v(0),1,wcount(channels(v(us))))=0
    print v(invalidradio)
else
    @com_flag%0 me=set_word(get(me,com_flag%0),yesno?(v(1)),1)
    print Power on Radio %0 is now turned %[yesno(yesno?(v(1)))]

    @@ legacy: @swi land(com_word(...),lxor(...))=0,,{@tr ...}
    switch land(com_word(v(0),3),lxor([yesno?(v(1))],[com_word(v(0),1)]))=0
        @@ no-op
    else
        call me/com_carrier_change=[channum(v(us),v(0))],[yesno?(v(1))]
    endswitch
endswitch

@@ legacy: $transmit *=*:/[get(me/com_man)]/@swi ifelse(...)=-2,{...},-1,{...},0,{...},1,{...}
&com_transmit_cmd com=:/[get(me,com_man)]/2$transmit:
switch range?(v(0),1,wcount(channels(v(us))))=0
    print v(invalidradio)
else
    switch com_word(v(0),1)=0
        print v(compoweroff)
    else
        switch hasenergy?(v(!),pwrcomm,com_power(v(0)))=0
            print v(compowerlow)
        else
            print Message Transmitted: [com_power(v(0))] power used.

            if inspace(v(us))
                !comevent v(us)=[com_word(v(0),4)],[channum(v(us),v(0))],[com_word(v(0),5)],[com_word(v(0),2)],v(1)
            else
                call [loc(v(us))]/Comm_Signal=Comm,[channum(v(us),v(0))],[com_word(v(0),4)],*,1,[v(us)],v(1)
            endif

            call me/handlesentmsg=v(0),v(1)
        endswitch
    endswitch
endswitch


@@ --------------------
@@ Message receive/log helpers (programs)
@@ --------------------

&showmessage com=
@pemit get(me,com_man)={%[displaymessage(v(0),v(5),v(1),v(2),v(3),v(4))]}
@@ NOTE: keep legacy dynamic attribute write shape (com_msg%N)
@com_msg[first(get(me/msg_slots))] me=join(time(),displaymessage(v(0),v(5),v(1),v(2),v(3),v(4)))
@msg_slots me=join(rest(get(me/msg_slots)),first(get(me/msg_slots)))
switch get(me,com_man)=
    @emit v(com_indicator)
else
    @@ no-op
endswitch

&handlesentmsg com=
@pwrcomm me=sub(get(me,pwrcomm),com_power(v(0)))
@com_msg[first(get(me/msg_slots))] me=join(time(),informmessage(v(0),v(1),com_power(v(0))))
@msg_slots me=join(rest(get(me/msg_slots)),first(get(me/msg_slots)))


@@ --------------------
@@ Functions / formatting helpers
@@ --------------------

&channels() com=[get(s(%0),channel)]
channum() com=[extract(channels(v(0)),v(1),1)]

&informmessage() com=[s(Outgoing Signal Power Used: %2 Channel %0/[channum(v(us),v(0))]: [v(1)])]
&com_header() com=[s(Incoming Signal: [fdiv(pow(v(4),2),pow(3d(v(5),v(us)),2))] Bearing:[velhdg(dx(v(5),v(us)),dy(v(5),v(us)),dz(v(5),v(us)))] Channel %0/[channum(v(us),v(0))])]

&com_status() com=[ljust(s(%0/[channum(v(us),v(0))]),7)] | [rjust(yesno(com_word(v(0),1)),4)] % | [rjust(yesno(com_word(v(0),2)),3)] | [rjust(ifelse(comp(get(me,com_video),v(0)),OFF,ON),4)] % | [rjust(yesno(com_word(v(0),3)),5)] % % | [rjust(com_word(v(0),4),15)] | [ifelse(scomp(com_word(v(0),5),*),mid(com_word(v(0),5),1,strlen(com_word(v(0),5))),<None>)]

&_attrdef33() com=[ifelse(lor(match(v(0),y*),match(v(0),on)),1,0)]
&com_word() com=[extract(get(s(me),com_flag%0),v(1),1)]
&yesno() com=[ifelse(v(0),ON,OFF)]
&_attrdef36() com=[land(lt(v(0),add(1,v(2))),gt(v(0),sub(1,v(1))))]
&_attrdef49() com=[if(add(0,com_flag(v(0),1)),ifelse(scomp(get(me,com_video),v(0)),1,2))]

displaymessage() com=[ifelse(scomp(com_word(v(0),5),v(2)),join(com_header(v(0),v(1),v(2),v(3),v(4),v(5)),<Static>......<hiss>....),strcat(join(com_header(v(0),v(1),v(2),v(3),v(4),v(5)),if(v(3),strcat(name(v(5)),if(get(s(%5),shipname),s({([get(s(%5),shipname)])}))))),join(:,v(1))))]

&com_power() com=[add(0,fdiv(com_word(v(0),4),100000000))]
```


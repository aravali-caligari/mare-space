# COM - Communications Console

## Name

COM - Communications Console

## Purpose

This is the COM legacy console object, used in older versions of the game to provide communication capabilities for spacecraft. It includes various communication functions such as sending and receiving messages, initiating voice communications, and managing communication channels.

## Meta data

```mud
COM(#2409h)
Type:	Thing
Owner:	Ptah
Flags:	Halted[0]
Bytes:	10860
Children:	1
Modified:	Sun Dec 28 01:15:36 2025
Location:	Helm Equipment Room(#11848R)
Home:	Helm Equipment Room(#11848R)
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
yesno?(): inherit function
com_status_cmd: inherit program
com_word(): inherit function
range?(): inherit function
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
receivemessage?(): inherit function
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
&yesno?() com=[ifelse(lor(match(v(0),y*),match(v(0),on)),1,0)]
&com_word() com=[extract(get(s(me/com_flag%0)),v(1),1)]
&yesno():	[ifelse(v(0),ON,OFF)]
&range?() com=[land(lt(v(0),add(1,v(2))),gt(v(0),sub(1,v(1))))]
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
&receivemessage?() com=[if(add(0,com_flag(v(0),1)),ifelse(scomp(get(me/com_video),v(0)),1,2))]
displaymessage():	[ifelse(scomp(com_word(v(0),5),v(2)),join(com_header(v(0),v(1),v(2),v(3),v(4),v(5)),<Static>......<hiss>....),strcat(join(com_header(v(0),v(1),v(2),v(3),v(4),v(5)),if(v(3),strcat(name(v(5)),if(get(s(%5/shipname)),s({([get(s(%5/shipname))])}))))),join(:,v(1))))]
&compoweroff com=Power on Radio %0 is currently turned OFF. No message sent.
&invalidradio com=You must use a valid radio number. Valid #'s are from '1' to '[wcount(channels(v(us)))]'.
&compowerlow com=Not enough power allocated to communications to transmit.
&com_power() com=[add(0,fdiv(com_word(v(0),4),100000000))]
&com_transmit_cmd com=$transmit *=*:/[get(me/com_man)]/@swi ifelse(range?(v(0),1,wcount(channels(v(us)))),ifelse(com_word(v(0),1),ifelse(hasenergy?(v(!),pwrcomm,com_power(v(0))),1,0),-1),-2)=-2,{@pemit %#=v(invalidradio)},-1,{@pemit %#=v(compoweroff)},0,{@pemit %#=v(compowerlow)},1,{@pemit %#=Message Transmitted: %[com_power(v(0))] power used.;[ifelse(inspace(v(us)),s({!comevent v(us)=[com_word(v(0),4)],[channum(v(us),v(0))],[com_word(v(0),5)],[com_word(v(0),2)],v(1)}),s({@tr [loc(v(us))]/Comm_Signal=Comm,[channum(v(us),v(0))],[com_word(v(0),4)],*,1,[v(us)],v(1)}))];@tr me/handlesentmsg=v(0),v(1)}
```

## Attribute list (English description)

```markdown
### &com_channel_cmd
- Command: `com channel <radio#>=<channel#>` (locked to whoever is in `me/com_man`).
- Validates both:
  - `<channel#>` is 1..999
  - `<radio#>` is within 1..number of available channels on the ship (`wcount(channels(v(us)))`)
- On invalid input: prints `invalidradio`.
- On success:
  - Prints “Channel set.”
  - Updates the ship’s channel list (`@channel v(us)=set_word(...)`) so the selected radio index maps to the new channel number.
  - If the new channel implies carrier behavior changes (based on `channum(...)` and `com_word(...,1)` / `com_word(...,3)`), triggers `me/com_carrier_change` with different parameters to inform the rest of the system.

### &showmessage
- Delivers an incoming message to the current comms operator (`get(me/com_man)`):
  - Emits the rendered message text produced by `displaymessage(...)`.
- Logs the message into a rotating “last 10 messages” ring buffer:
  - Stores `time()` + the rendered display text into `com_msg<N>` where `<N>` is the first slot in `msg_slots`.
  - Rotates `msg_slots` by moving the used slot id to the end.
- If the console is currently unmanned (`me/com_man` is empty), it emits the `com_indicator` attention message (beep/light) instead.

### &com_log_cmd
- Command: `com log` (locked to `me/com_man`).
- Iterates over `msg_slots` and prints each stored `com_msg<N>` entry to the caller, showing the last 10 received messages.

### &channels()
- Function: given an object `%0` (typically a ship), returns the contents of that object’s `channel` attribute (`get(s(%0/channel))`), which is treated as a “list of channel numbers by radio index”.

### channum()
- Function: given a ship (v(0)) and a radio index (v(1)), extracts the channel number from the ship’s channel list (`extract(channels(v(0)),v(1),1)`).

### &handlesentmsg
- Post-transmit bookkeeping after a successful send:
  - Deducts comms power from this console (`@pwrcomm me=sub(get(me/pwrcomm),com_power(v(0)))`), where `v(0)` is the radio index used.
  - Logs an outgoing message record into the rotating `com_msg<N>` ring buffer (same slot rotation approach as inbound logging), using `informmessage(...)` to format the log entry.

### &informmessage()
- Function: formats an outgoing log line including:
  - Power used (`%2`)
  - Radio index and actual channel number (`%0/[channum(...)]`)
  - Message body (`%1`)

### &com_header()
- Function: formats an incoming message header including:
  - Computed “signal strength” term (uses transmitted power squared divided by distance squared: `pow(v(4),2) / pow(3d(...),2)`)
  - Bearing from ship to sender (via `velhdg(dx,dy,dz)`)
  - Radio index and channel number

### &com_status()
- Function: returns a single formatted status line for one radio index (`v(0)`), including:
  - `radio#/channel#`
  - Power state (ON/OFF) from `com_word(v(0),1)`
  - ID signal enabled from `com_word(v(0),2)`
  - Video mode ON/OFF if `me/com_video` matches this radio index
  - Carrier enabled from `com_word(v(0),3)`
  - Broadcast range from `com_word(v(0),4)`
  - Encryption keyword display from `com_word(v(0),5)` (shows `<None>` if `*`)

### &com_status_cmd
- Command: `com status` (locked to `me/com_man`).
- Prints a table header, then loops over all radios and prints `com_status(radioIndex)` for each.

### &com_video_cmd
- Command: `com video <radio#>` (locked to `me/com_man`).
- Currently does not implement video; always prints “Video mode is currently unavailable.”

### &com_wordoff_cmd
- Command: `com noencrypt <radio#>` (locked to `me/com_man`).
- Validates radio index.
- Sets word #5 (encryption keyword) in `com_flag<radio#>` to `*` (meaning “no encryption”).
- Prints confirmation.

### &com_word_cmd
- Command: `com encrypt <radio#>=<keyword>` (locked to `me/com_man`).
- Validates radio index.
- Enforces keyword must be exactly one word (`wcount(v(1))=1`).
- On success: sets word #5 in `com_flag<radio#>` to `*<keyword>` and prints confirmation.
- On failure: prints “Illegal Keyword...” message.

### &com_range_cmd
- Command: `com range <radio#>=<rangeKm>` (locked to `me/com_man`).
- Validates radio index.
- Sets word #4 in `com_flag<radio#>` to the numeric range value (normalized via `simp(fadd(0,v(1)))`).
- Prints confirmation showing the new range in km.

### &com_carrier_cmd
- Command: `com carrier <radio#>=<on/off>` (locked to `me/com_man`).
- Validates radio index.
- Sets word #3 in `com_flag<radio#>` to boolean on/off (`yesno?(v(1))`).
- Prints confirmation.
- If the carrier state actually changes compared to current, triggers `me/com_carrier_change` for the underlying channel.

### &com_id_cmd
- Command: `com id <radio#>=<on/off>` (locked to `me/com_man`).
- Validates radio index.
- Sets word #2 in `com_flag<radio#>` (ID signal on/off).
- Prints confirmation.

### &com_power_cmd
- Command: `com power <radio#>=<on/off>` (locked to `me/com_man`).
- Validates radio index.
- Sets word #1 in `com_flag<radio#>` (radio power on/off).
- Prints confirmation.
- If carrier behavior should be updated due to power toggling (in combination with carrier flag), triggers `me/com_carrier_change` for the channel.

### &yesno?()
- Helper function: converts textual on/off-ish inputs into boolean:
  - Returns 1 if input matches `y*` or `on`, else 0.

### &com_word()
- Function: for a radio index `%0`, returns the Nth word (`v(1)`) from that radio’s `com_flag%0` string.

### &yesno()
- Function: maps boolean to `ON`/`OFF`.

### &range?()
- Helper function: range check used elsewhere:
  - True if `v(0)` is strictly within `v(1)`..`v(2)` bounds (implemented via `lt`/`gt` around `add(1,...)` / `sub(1,...)`).

### com_flag1 .. com_flag10
- Default per-radio configuration records, each encoded as 5 words:
  1) power flag (0/1)
  2) ID flag (0/1)
  3) carrier flag (0/1)
  4) broadcast range (default `100000`)
  5) encryption keyword (default `*` meaning none)

### &com_info2
- Help text emitter (prints to `%0`), describing available COM commands, then triggers `me/com_info3` to print additional info.

### msg_slots
- Ring buffer slot order for message log storage (defaults `1 2 3 4 5 6 7 8 9 10`).

### com_msg1 .. com_msg10
- Stored message log entries for the last 10 received/sent messages (defaults “Empty MsgN”).

### &com_indicator
- Notification text emitted when a message arrives and the station is unmanned.

### &com_info3
- Additional help text: `com log` and current “radio standards” channel guidance.

### &receivemessage?()
- Appears to compute a mode/flag value based on:
  - Whether the radio is powered (`com_flag(v(0),1)`), and
  - Whether video mode is set for that radio (`scomp(get(me/com_video),v(0))`)
- Returns 1 or 2 depending on video match when powered; returns nothing/falsey when not powered (used as a derived indicator elsewhere).

### displaymessage()
- Function: renders the final display line for an incoming transmission.
- If the incoming message’s encryption key (`v(2)`) does not match the radio’s configured key (`com_word(v(0),5)`), it outputs header + “<Static>......<hiss>....”.
- If it matches:
  - Outputs header + (optional sender name / shipname details if broadcast flags allow) + `: <message text>`.

### &compoweroff
- Static message: radio is OFF, so no message sent.

### &invalidradio
- Static message: radio number invalid; prints valid range based on channel count.

### &compowerlow
- Static message: insufficient allocated comms power to transmit.

### &com_power()
- Function: computes comms power cost for a radio based on its configured range value:
  - `com_word(v(0),4) / 100000000` (numeric).

### &com_transmit_cmd
- Command: `transmit <radio#>=<msg>` (locked to `me/com_man`).
- Validates:
  - radio index in range
  - radio power is ON (`com_word(...,1)`)
  - ship has enough comms energy for the calculated cost (`hasenergy?(...,pwrcomm,com_power(...))`)
- Failure cases:
  - invalid radio -> prints `invalidradio`
  - powered off -> prints `compoweroff`
  - not enough power -> prints `compowerlow`
- Success path:
  - Prints “Message Transmitted” including power used.
  - If ship is in space: emits a space-sim `!comevent` with range, channel, encryption key, ID flag, and message.
  - If not in space: triggers a local `Comm_Signal` handler on the ship’s location with similar parameters.
  - Triggers `me/handlesentmsg` to deduct power and log the outgoing message.
```

## Attribute list (MARE2 conversion)

```mud
@@ Converted from legacy Attribute list to MARE2 style.
@@ Notes:
@@ - 'com <subcommand>' is routed through a single-word 'com' command.
@@ - Legacy '@pemit %#=' is now 'print'.
@@ - Legacy '@tr' is now 'call'.

&com_cmd COM=:/[get(v(me),com_man)]/3$com:
@@ Route COM subcommands (channel,log,status,video,noencrypt,encrypt,range,carrier,id,power)
switch first(v(0))
  case channel
    set 0=[rest(v(0))]
    call me/com_channel_cmd=v(0),v(1)
    break
  case log
    call me/com_log_cmd
    break
  case status
    call me/com_status_cmd
    break
  case video
    set 0=[rest(v(0))]
    call me/com_video_cmd=v(0)
    break
  case noencrypt
    set 0=[rest(v(0))]
    call me/com_wordoff_cmd=v(0)
    break
  case encrypt
    set 0=[rest(v(0))]
    call me/com_word_cmd=v(0),v(1)
    break
  case range
    set 0=[rest(v(0))]
    call me/com_range_cmd=v(0),v(1)
    break
  case carrier
    set 0=[rest(v(0))]
    call me/com_carrier_cmd=v(0),v(1)
    break
  case id
    set 0=[rest(v(0))]
    call me/com_id_cmd=v(0),v(1)
    break
  case power
    set 0=[rest(v(0))]
    call me/com_power_cmd=v(0),v(1)
    break
  default
    print Invalid COM command. Try: com status,com log,com channel <radio>=<chan>,com power <radio>=<on/off>
endswitch


&com_channel_cmd COM=
@@ v(0)=radio#,v(1)=channel#
if land(range?(v(1),1,999),range?(v(0),1,wcount(channels(v(us)))))=0
  print [v(invalidradio)]
  exit
endif

print Channel set.
@channel v(us)=set_word(channels(v(us)),v(1),v(0))

@@ Preserve legacy carrier-change side effects
if land(match(channum(v(us),v(0)),strcat(v(0),v(1))),land(com_word(v(0),1),com_word(v(0),3)))!=0
  call me/com_carrier_change=[channum(v(us),v(0))],0
  call me/com_carrier_change=%0%1,1
endif


&showmessage COM=
@@ v(0)=radio#,v(1)=msg,v(2)=encKey,v(3)=broadcastFlag?,v(4)=txPower,v(5)=senderObj
@pemit get(v(me),com_man)={%[displaymessage(v(0),v(5),v(1),v(2),v(3),v(4))]}
@com_msg[first(get(v(me),msg_slots))] me=join(time(),displaymessage(v(0),v(5),v(1),v(2),v(3),v(4)))
@msg_slots me=join(rest(get(v(me),msg_slots)),first(get(v(me),msg_slots)))

if get(v(me),com_man)=
  @emit v(com_indicator)
endif


&com_log_cmd COM=
for word__=get(v(me),msg_slots)
  set 0=[v(word__)]
  print {%%%[get(v(me),com_msg%0)]}
done


&channels() COM=[get(v(0),channel)]

&channum() COM=[extract(channels(v(0)),v(1),1)]


&handlesentmsg COM=
@@ v(0)=radio#,v(1)=msg
@pwrcomm me=sub(get(v(me),pwrcomm),com_power(v(0)))
@com_msg[first(get(v(me),msg_slots))] me=join(time(),informmessage(v(0),v(1),com_power(v(0))))
@msg_slots me=join(rest(get(v(me),msg_slots)),first(get(v(me),msg_slots)))


&informmessage() COM=[s(Outgoing Signal Power Used: %2 Channel %0/[channum(v(us),v(0))]: [v(1)])]

&com_header() COM=[s(Incoming Signal: [fdiv(pow(v(4),2),pow(3d(v(5),v(us)),2))] Bearing:[velhdg(dx(v(5),v(us)),dy(v(5),v(us)),dz(v(5),v(us)))] Channel %0/[channum(v(us),v(0))])]

&com_status() COM=[ljust(s(%0/[channum(v(us),v(0))]),7)] | [rjust(yesno(com_word(v(0),1)),4)] % | [rjust(yesno(com_word(v(0),2)),3)] | [rjust(ifelse(comp(get(v(me),com_video),v(0)),OFF,ON),4)] % | [rjust(yesno(com_word(v(0),3)),5)] % % | [rjust(com_word(v(0),4),15)] | [ifelse(scomp(com_word(v(0),5),*),mid(com_word(v(0),5),1,strlen(com_word(v(0),5))),<None>)]

&com_status_cmd COM=
print Channel | Power | ID? | Video | Carrier | Broadcast Range | Encryption Word
print --------+-------+-----+-------+---------+-----------------+----------------
for word__=rest(lnum(add(1,wcount(channels(v(us))))))
  set 0=[v(word__)]
  print [com_status(v(0))]
done


&com_video_cmd COM=
print Video mode is currently unavailable.


&com_wordoff_cmd COM=
@@ v(0)=radio#
if range?(v(0),1,wcount(channels(v(us))))=0
  print [v(invalidradio)]
  exit
endif

@com_flag%0 me=set_word(get(v(me),com_flag%0),*,5)
print Radio %0 is now using no encryption.


&com_word_cmd COM=
@@ v(0)=radio#,v(1)=keyword
if range?(v(0),1,wcount(channels(v(us))))=0
  print [v(invalidradio)]
  exit
endif

if wcount(v(1))=1
  @com_flag%0 me=set_word(get(v(me),com_flag%0),strcat(*,v(1)),5)
  print Traffic on Radio %0 is now encrypted with keyword '%1'
else
  print Illegal Keyword. You need to use a one-word encryption keyword.
endif


&com_range_cmd COM=
@@ v(0)=radio#,v(1)=rangeKm
if range?(v(0),1,wcount(channels(v(us))))=0
  print [v(invalidradio)]
  exit
endif

@com_flag%0 me=set_word(get(v(me),com_flag%0),simp(fadd(0,v(1))),4)
print Broadcast Range on Radio %0 is now set to %%%[simp(fadd(0,v(1)))]km's


&com_carrier_cmd COM=
@@ v(0)=radio#,v(1)=on/off
if range?(v(0),1,wcount(channels(v(us))))=0
  print [v(invalidradio)]
  exit
endif

@@ Capture prior state so the "changed?" test is meaningful
set 9=[com_word(v(0),3)]

@com_flag%0 me=set_word(get(v(me),com_flag%0),yesno?(v(1)),3)
print Carrier Signal on Radio %0 is now turned %%%[yesno(yesno?(v(1)))]

if v(9)!=yesno?(v(1))
  call me/com_carrier_change=[channum(v(us),v(0))],[yesno?(v(1))]
endif


&com_id_cmd COM=
@@ v(0)=radio#,v(1)=on/off
if range?(v(0),1,wcount(channels(v(us))))=0
  print [v(invalidradio)]
  exit
endif

@com_flag%0 me=set_word(get(v(me),com_flag%0),yesno?(v(1)),2)
print ID Signal on Radio %0 is now turned %%%[yesno(yesno?(v(1)))]


&com_power_cmd COM=
@@ v(0)=radio#,v(1)=on/off
if range?(v(0),1,wcount(channels(v(us))))=0
  print [v(invalidradio)]
  exit
endif

@@ Capture prior power state for carrier-change detection
set 9=[com_word(v(0),1)]

@com_flag%0 me=set_word(get(v(me),com_flag%0),yesno?(v(1)),1)
print Power on Radio %0 is now turned %%%[yesno(yesno?(v(1)))]

@@ If carrier is enabled and power toggled, notify channel carrier state
if land(com_word(v(0),3),lxor(yesno?(v(1)),v(9)))!=0
  call me/com_carrier_change=[channum(v(us),v(0))],[yesno?(v(1))]
endif


&yesno?() COM=[ifelse(lor(match(v(0),y*),match(v(0),on)),1,0)]

&com_word() COM=[extract(get(v(me),com_flag%0),v(1),1)]

&yesno() COM=[ifelse(v(0),ON,OFF)]

&range?() COM=[land(lt(v(0),add(1,v(2))),gt(v(0),sub(1,v(1))))]


&com_flag1 COM=0 0 0 100000 *
&com_flag2 COM=0 0 0 100000 *
&com_flag3 COM=0 0 0 100000 *
&com_flag4 COM=0 0 0 100000 *
&com_flag5 COM=0 0 0 100000 *
&com_flag6 COM=0 0 0 100000 *
&com_flag7 COM=0 0 0 100000 *
&com_flag8 COM=0 0 0 100000 *
&com_flag9 COM=0 0 0 100000 *
&com_flag10 COM=0 0 0 100000 *


&com_info2 COM=
@pemit %0=com id <Radio#>=<on/off> : Turn identification signal on/off for radio
@pemit %0=com carrier <Radio#>=<on/off> : Turn carrier signal on/off for radio
@pemit %0=com encrypt <Radio#>=<codeword> : Set radio to encrypt/decrypt using the word
@pemit %0=com noencrypt <Radio#> : Turn off encryption of that radio
@pemit %0=com video <Radio#> : Set radio for video mode(viewscreen)
@pemit %0=transmit <Radio#>=<Msg> : Transmit a message over the radio
call me/com_info3=%0


&msg_slots COM=1 2 3 4 5 6 7 8 9 10

&com_msg1 COM=Empty Msg1
&com_msg2 COM=Empty Msg2
&com_msg3 COM=Empty Msg3
&com_msg4 COM=Empty Msg4
&com_msg5 COM=Empty Msg5
&com_msg6 COM=Empty Msg6
&com_msg7 COM=Empty Msg7
&com_msg8 COM=Empty Msg8
&com_msg9 COM=Empty Msg9
&com_msg10 COM=Empty Msg10


&com_indicator COM=*BEEP* A red message indicator light blinks on the Communications Station, indicating a received message.

&com_info3 COM=
@pemit %0=com log : Display a log of the last 10 received messages
@pemit %0=Current Radio Standards: Channel 911 is used for ships needing emergency assistance. Channel 555 is being considered the universal ship to ship chatter channel for normal use. Channel 200 will be used for communicating with automated landing, launching, and docking facilities.


&receivemessage?() COM=[if(add(0,com_flag(v(0),1)),ifelse(scomp(get(v(me),com_video),v(0)),1,2))]

&displaymessage() COM=[ifelse(scomp(com_word(v(0),5),v(2)),join(com_header(v(0),v(1),v(2),v(3),v(4),v(5)),<Static>......<hiss>....),strcat(join(com_header(v(0),v(1),v(2),v(3),v(4),v(5)),if(v(3),strcat(name(v(5)),if(get(v(5),shipname),s({([get(v(5),shipname)])}))))),join(:,v(1))))]


&compoweroff COM=Power on Radio %0 is currently turned OFF. No message sent.
&invalidradio COM=You must use a valid radio number. Valid #'s are from '1' to '[wcount(channels(v(us)))]'.
&compowerlow COM=Not enough power allocated to communications to transmit.

&com_power() COM=[add(0,fdiv(com_word(v(0),4),100000000))]


&com_transmit_cmd COM=:/[get(v(me),com_man)]/2$transmit:
@@ v(0)=radio#,v(1)=msg
if range?(v(0),1,wcount(channels(v(us))))=0
  print [v(invalidradio)]
  exit
endif

if com_word(v(0),1)=0
  print [v(compoweroff)]
  exit
endif

if hasenergy?(v(!),pwrcomm,com_power(v(0)))=0
  print [v(compowerlow)]
  exit
endif

print Message Transmitted: %[com_power(v(0))] power used.

if inspace(v(us))
  !comevent v(us)=[com_word(v(0),4)],[channum(v(us),v(0))],[com_word(v(0),5)],[com_word(v(0),2)],v(1)
else
  call [loc(v(us))]/Comm_Signal=Comm,[channum(v(us),v(0))],[com_word(v(0),4)],*,1,[v(us)],v(1)
endif

call me/handlesentmsg=v(0),v(1)
```


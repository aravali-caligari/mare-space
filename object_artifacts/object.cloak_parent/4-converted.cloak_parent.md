# `Cloak Parent`

## Attribute list (MARE2 conversion)

```mud

@@ -----------------------------
@@ OBJECT: Cloak Parent(#54808h)
@@ LOCATION: PCS Equipment Room(#50723R)
@@ -----------------------------

---cut---
@@ Move to location so next commands are targeted on the right object.
@teleport me=#50723
---cut---

@@ ATTRIBUTE: Cloak Parent/passkey
@@ -----------------------------

---cut---
@defattr #54808h/passkey
---cut---
@@ No value to convert, skip this attribute
---cut---

@@ ATTRIBUTE: Cloak Parent/cloak_cmd
@@ -----------------------------

---cut---
@defattr #54808h/cloak_cmd=inherit program
---cut---
&cloak_cmd #54808h=:/[v(eng_man)]/3$cloak:
@@ Dispatch legacy 'cloak ...' subcommands.
@@ Expected patterns include:
@@ - cloak on passkey=<passkey>
@@ - cloak off
@@ - cloak passkey <old>=<new>

switch first(v(0))
  case on
    if rest(v(0))=passkey
      call me/cloak_on=v(1)
    else
      print Invalid cloak command.
    endif
    break
  case off
    call me/cloak_off
    break
  case passkey
    set 0=[rest(v(0))]
    call me/set_passkey1=v(0),v(1)
    break
  default
    print Invalid cloak command.
endswitch
---cut---

@@ ATTRIBUTE: Cloak Parent/initial_cmd
@@ -----------------------------

---cut---
@defattr #54808h/initial_cmd=inherit program
---cut---
&initial_cmd #54808h=:/[v(eng_man)]/3$initial:
@@ Legacy: initial passkey=<passkey>
if v(0)=passkey
  call me/set_passkey2=v(1)
else
  print Invalid initial command.
endif
---cut---

@@ ATTRIBUTE: Cloak Parent/cloak_on
@@ -----------------------------

---cut---
@defattr #54808h/cloak_on=inherit program
---cut---
&cloak_on #54808h=
if get(v(us),vismult)=-1
  print Cloaking device already on.
  exit
endif

if v(passkey)=00[v(0)]
  @vismult v(us)=-1
  @emit Cloaking device engaged.
else
  print Invalid cloak passkey.
endif
---cut---

@@ ATTRIBUTE: Cloak Parent/set_passkey1
@@ -----------------------------

---cut---
@defattr #54808h/set_passkey1=inherit program
---cut---
&set_passkey1 #54808h=
if v(passkey)=00[v(0)]
  @passkey me=00[v(1)]
  print Cloaking device passkey - Set.
else
  print Cloaking device passkey - Invalid.
endif
---cut---

@@ ATTRIBUTE: Cloak Parent/set_passkey2
@@ -----------------------------

---cut---
@defattr #54808h/set_passkey2=inherit program
---cut---
&set_passkey2 #54808h=
if v(passkey)=
  @passkey me=00[v(0)]
  print Cloaking device passkey - Set.
else
  print Cloaking device passkey - Invalid.
endif
---cut---

@@ ATTRIBUTE: Cloak Parent/cloak_off
@@ -----------------------------

---cut---
@defattr #54808h/cloak_off=inherit program
---cut---
&cloak_off #54808h=
if get(v(us),vismult)=1
  print Cloaking device already off.
  exit
endif

@vismult v(us)=1
@emit Cloaking device disengaged.
---cut---

@@ ATTRIBUTE: Cloak Parent/cloakhelp
@@ -----------------------------

---cut---
@defattr #54808h/cloakhelp=inherit program
---cut---
&cloakhelp #54808h=:/[v(eng_man)]/1$cloakhelp:
print CLOAK ON PASSKEY=<passkey> : Activates the cloaking device.
print INITIAL PASSKEY=<passkey> : Set the initial cloaking device passkey.
print CLOAK PASSKEY <old passkey>=<new passkey> : Changes the passkey.
print CLOAK OFF : Turns the cloaking device off.
print WARNING: The cloaking device will consume power faster than the ship can produce it. If allowed to remain on it will drain the Life Support of its power and kill everyone on board.
---cut---

```
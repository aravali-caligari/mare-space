# `Cloak Parent`

## Attribute list (MARE2 conversion)

```mud
@@ -----------------------------
@@ OBJECT: Cloak Parent(#54808)
@@ LOCATION: PCS Equipment Room(#50723)
@@ -----------------------------

---cut---
@@ Teleport to object location as a convenience
@teleport me=#50723
---cut---

@@ ATTRIBUTE: Cloak Parent/passkey
@@ ------------------------------

---cut---
@defattr #54808/passkey
---cut---
@@ No value to convert, skip this attribute
---cut---

@@ ATTRIBUTE: Cloak Parent/cloak_cmd
@@ --------------------------------

---cut---
@defattr #54808/cloak_cmd=inherit program
---cut---
&cloak_cmd #54808=:/[v(eng_man)]/3$cloak:
  @@ v(0) = subcommand words before '='
  @@ v(1) = first value after '=' (if any)
  switch v(0)
    case on passkey
      call me/cloak_on=v(1)
      break
    case off
      call me/cloak_off
      break
    default
      @@ Legacy: $cloak passkey *=*  (old=new)
      if first(v(0))=passkey
        @@ v(0) is "passkey <old>"; v(1) is "<new>"
        call me/set_passkey1=rest(v(0)),v(1)
      else
        print Invalid cloak subcommand: [v(0)]
      endif
      break
  endswitch
---cut---

@@ ATTRIBUTE: Cloak Parent/initial_cmd
@@ ----------------------------------

---cut---
@defattr #54808/initial_cmd=inherit program
---cut---
&initial_cmd #54808=:/[v(eng_man)]/3$initial:
  switch v(0)
    case passkey
      call me/set_passkey2=v(1)
      break
    default
      print Invalid initial subcommand: [v(0)]
      break
  endswitch
---cut---

@@ ATTRIBUTE: Cloak Parent/cloakhelp_cmd
@@ ------------------------------------

---cut---
@defattr #54808/cloakhelp_cmd=inherit program
---cut---
&cloakhelp_cmd #54808=:/[v(eng_man)]/1$cloakhelp:
  print CLOAK ON PASSKEY=<passkey> : Activates the cloaking device.
  print INITIAL PASSKEY=<passkey> : Set the initial cloaking device passkey.
  print CLOAK PASSKEY <old passkey>=<new passkey> : Changes the passkey.
  print CLOAK OFF : Turns the cloaking device off.
  print WARNING: The cloaking device will consume power faster than the ship can produce it. If allowed to remain on it will drain the Life Support of its power and kill everyone on board.
---cut---

@@ ATTRIBUTE: Cloak Parent/cloak_on
@@ -------------------------------

---cut---
@defattr #54808/cloak_on=inherit program
---cut---
&cloak_on #54808=
  if get(s(v(us)/vismult))=-1
    print Cloaking device already on.
  else
    if v(passkey)=00[v(0)]
      @vismult [v(us)]=-1
      @emit Cloaking device engaged.
    else
      print Invalid cloak passkey.
    endif
  endif
---cut---

@@ ATTRIBUTE: Cloak Parent/cloak_off
@@ --------------------------------

---cut---
@defattr #54808/cloak_off=inherit program
---cut---
&cloak_off #54808=
  if get(s(v(us)/vismult))=1
    print Cloaking device already off.
  else
    @vismult [v(us)]=1
    @emit Cloaking device disengaged.
  endif
---cut---

@@ ATTRIBUTE: Cloak Parent/set_passkey1
@@ -----------------------------------

---cut---
@defattr #54808/set_passkey1=inherit program
---cut---
&set_passkey1 #54808=
  if v(passkey)=00[v(0)]
    @passkey me=00[v(1)]
    print Cloaking device passkey - Set.
  else
    print Cloaking device passkey - Invalid.
  endif
---cut---

@@ ATTRIBUTE: Cloak Parent/set_passkey2
@@ -----------------------------------

---cut---
@defattr #54808/set_passkey2=inherit program
---cut---
&set_passkey2 #54808=
  if v(passkey)=
    @passkey me=00[v(0)]
    print Cloaking device passkey - Set.
  else
    print Cloaking device passkey - Invalid.
  endif
---cut---
```

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

@@ ATTRIBUTE: Cloak Parent/cloak_on
@@ -------------------------------

---cut---
@defattr #54808/cloak_on=inherit program
---cut---
&cloak_on #54808=$cloak on passkey=*:/[v(eng_man)]/
if [get(s([v(us)]/vismult))]=-1
  print Cloaking device already on.
else
  switch [v(passkey)]
    case 00%0
      @vismult [v(us)]=-1
      @emit Cloaking device engaged.
      break
    default
      print Invalid cloak passkey.
      break
  endswitch
endif
---cut---

@@ ATTRIBUTE: Cloak Parent/set_passkey1
@@ -----------------------------------

---cut---
@defattr #54808/set_passkey1=inherit program
---cut---
&set_passkey1 #54808=$cloak passkey *=*:/[v(eng_man)]/
switch [v(passkey)]
  case 00%0
    @passkey me=00%1
    print Cloaking device passkey - Set.
    break
  default
    print Cloaking device passkey - Invalid.
    break
endswitch
---cut---

@@ ATTRIBUTE: Cloak Parent/set_passkey2
@@ -----------------------------------

---cut---
@defattr #54808/set_passkey2=inherit program
---cut---
&set_passkey2 #54808=$initial passkey=*:/[v(eng_man)]/
if [strlen(v(passkey))]
  print Cloaking device passkey - Invalid.
else
  @passkey me=00%0
  print Cloaking device passkey - Set.
endif
---cut---

@@ ATTRIBUTE: Cloak Parent/cloak_off
@@ --------------------------------

---cut---
@defattr #54808/cloak_off=inherit program
---cut---
&cloak_off #54808=$cloak off:/[v(eng_man)]/
if [get(s([v(us)]/vismult))]=1
  print Cloaking device already off.
else
  @vismult [v(us)]=1
  @emit Cloaking device disengaged.
endif
---cut---

@@ ATTRIBUTE: Cloak Parent/cloakhelp
@@ --------------------------------

---cut---
@defattr #54808/cloakhelp=inherit program
---cut---
&cloakhelp #54808=$cloakhelp:/[v(eng_man)]/
print CLOAK ON PASSKEY=<passkey> : Activates the cloaking device.
print INITIAL PASSKEY=<passkey> : Set the initial cloaking device passkey.
print CLOAK PASSKEY <old passkey>=<new passkey> : Changes the passkey.
print CLOAK OFF : Turns the cloaking device off.
print WARNING: The cloaking device will consume power faster than the ship can produce it. If allowed to remain on it will drain the Life Support of its power and kill everyone on board.
---cut---

@@ ATTRIBUTE: Cloak Parent/passkey
@@ ------------------------------

---cut---
@defattr #54808/passkey
---cut---
@@ No value to convert, skip this attribute
---cut---
```

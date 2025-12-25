# Cloak Parent

## Name

Cloak Parent - Cloaking Device Console

## Purpose

This is the Cloaking Device console object, used in the game to provide players with the ability to cloak their spacecraft. It allows players to activate and deactivate the cloaking device, as well as manage passkeys for security.

## Meta data

## Object Definition

### Attribute definitions

```mud
cloakhelp: inherit program
passkey: program
set_passkey1: inherit program
set_passkey2: inherit program
cloak_on: inherit program
cloak_off: inherit program
```

### Attribute list

```mud
&cloak_on cloak parent=$cloak_on passkey=*:/[v(eng_man)]/@swi [get(s([v(us)]/vismult))]=-1,{@pemit %#=Cloaking device already on.},{@swi [v(passkey)]=00[v(0)],{@vismult [v(us)]=-1;@emit Cloaking device engaged.},{@pemit %#=Invalid cloak passkey.}}
&set_passkey1 cloak parent=$cloak_change passkey=*:/[v(eng_man)]/@swi [v(passkey)]=00[v(0)],{@passkey me=00[v(1)];@pemit %#=Cloaking device passkey - Set.},{@pemit %#=Cloaking device passkey - Invalid.}
&set_passkey2 cloak parent=$cloak_set passkey=*:/[v(eng_man)]/@swi [v(passkey)]=,{@passkey me=00[v(0)];@pemit %#=Cloaking device passkey - Set.},{@pemit %#=Cloaking device passkey - Invalid.}
&cloak_off cloak parent=$cloak_off:/[v(eng_man)]/@swi [get(s([v(us)]/vismult))]=1,{@pemit %#=Cloaking device already off.},{@vismult [v(us)]=1;@emit Cloaking device disengaged.}
&cloakhelp cloak parent=$cloak_help:/[v(eng_man)]/@pemit %#=CLOAK_ON PASSKEY=<passkey> : Activates the cloaking device.;@pemit %#=CLOAK_SET PASSKEY=<passkey> : Set the initial cloaking device passkey.;@pemit %#=CLOAK_CHANGE PASSKEY=<old passkey>,<new passkey> : Changes the passkey.;@pemit %#=CLOAK_OFF : Turns the cloaking device off.;@pemit %#=WARNING: The cloaking device will consume power faster than the ship can produce it. If allowed to remain on it will drain the Life Support of its power and kill everyone on board.
```

## English Logic Descriptions (Legacy) + Passkey Parameter Validation

### `cloak_on` — English description

```text
Attribute: cloak_on

Player command (legacy pattern):
- cloak_on passkey=<passkey>
- Access is lock-checked by :/[v(eng_man)]/ (must be the engineering console operator).

Validation to add (MARE2-style; verifies the token before '=' is literally 'passkey'):
- If v(0)=!passkey,: print an invalid syntax message and return early.
(Example snippet)
    if v(0)=!passkey,
        print Invalid syntax. Use: cloak_help
        return
    endif

Logic:
1) Read the ship cloak visibility multiplier (ship is v(us); attribute is vismult).
2) If ship vismult=-1:
   - print Cloaking device already on.
   - stop.
3) Otherwise validate the supplied passkey:
   - Compare this console’s stored passkey (v(passkey)) against 00<supplied_passkey>.
4) If it matches:
   - Set ship vismult=-1 (cloak engaged).
   - @emit Cloaking device engaged.
5) Else:
   - print Invalid cloak passkey.
```

### `set_passkey1` — English description

```text
Attribute: set_passkey1

Player command (per help intent):
- cloak_change passkey=<oldpass>=<newpass>
- Access is lock-checked by :/[v(eng_man)]/.

Validation to add (MARE2-style; verifies the token before the first '=' is literally 'passkey'):
    if v(0)=!passkey,
        print Invalid syntax. Use: cloak_help
        return
    endif

Logic:
1) Treat the first provided passkey value as the “old passkey”, and the next as the “new passkey”.
2) If current stored passkey (v(passkey)) equals 00<oldpass>:
   - Set this console’s passkey attribute to 00<newpass>.
   - print Cloaking device passkey - Set.
3) Else:
   - print Cloaking device passkey - Invalid.
```

### `set_passkey2` — English description

```text
Attribute: set_passkey2

Player command (legacy pattern):
- cloak_set passkey=<passkey>
- Access is lock-checked by :/[v(eng_man)]/.

Validation to add (MARE2-style; verifies the token before '=' is literally 'passkey'):
    if v(0)=!passkey,
        print Invalid syntax. Use: cloak_help
        return
    endif

Logic:
1) This is an “initial set” path: it only succeeds if no passkey is currently set.
2) If the stored passkey value is empty/unset:
   - Set this console’s passkey attribute to 00<supplied_passkey>.
   - print Cloaking device passkey - Set.
3) Else:
   - print Cloaking device passkey - Invalid.
```

### `cloak_off` — English description

```text
Attribute: cloak_off

Player command (legacy pattern):
- cloak_off
- Access is lock-checked by :/[v(eng_man)]/.

Logic:
1) Read ship vismult via v(us).
2) If ship vismult=1:
   - print Cloaking device already off.
   - stop.
3) Else:
   - Set ship vismult=1 (cloak disengaged).
   - @emit Cloaking device disengaged.
```

### `cloakhelp` — English description

```text
Attribute: cloakhelp

Player command (legacy pattern):
- cloak_help
- Access is lock-checked by :/[v(eng_man)]/.

Logic:
1) print a series of usage/help lines to the invoking player describing:
   - how to enable cloak with passkey
   - how to set the initial passkey
   - how to change the passkey
   - how to disable cloak
2) print a warning that leaving cloak on consumes power rapidly and can drain life support power.
```

## MARE 2.0 Converted Softcode (from Legacy Attribute list)

```mud
@@ cloak_on: cloak_on passkey=<passkey>
&cloak_on cloak parent=:/[v(eng_man)]/2$cloak_on:
@@ Validate the first parameter to be 'passkey'
if v(0)=!passkey,
    print Invalid syntax. Use: cloak_help
    exit
endif
@@ Check if cloaking device is already on
if get(v(us),vismult)=-1
    print Cloaking device already on.
    exit
endif
@@ Validate provided passkey and engage cloak
if v(passkey)=00[v(1)]
    @vismult v(us)=-1
    @emit Cloaking device engaged.
else
    print Invalid cloak passkey.
endif

@@ set_passkey1: cloak_change passkey=<oldpass>,<newpass>
&set_passkey1 cloak parent=:/[v(eng_man)]/3$cloak_change:
@@ Validate the first parameter to be 'passkey'
if v(0)=!passkey,
    print Invalid syntax. Use: cloak_help
    exit
endif
@@ v(1)=old passkey, v(2)=new passkey
if v(passkey)=00[v(1)]
    @passkey me=00[v(2)]
    print Cloaking device passkey - Set.
else
    print Cloaking device passkey - Invalid.
endif

@@ set_passkey2: cloak_set passkey=<passkey> (only if currently unset)
&set_passkey2 cloak parent=:/[v(eng_man)]/2$cloak_set:
@@ Validate the first parameter to be 'passkey'
if v(0)=!passkey,
    print Invalid syntax. Use: cloak_help
    exit
endif
if v(passkey)=
    @passkey me=00[v(1)]
    print Cloaking device passkey - Set.
else
    print Cloaking device passkey - Invalid.
endif

@@ cloak_off: cloak_off
&cloak_off cloak parent=:/[v(eng_man)]/0$cloak_off:
if get(v(us),vismult)=1
    print Cloaking device already off.
    exit
endif
@vismult v(us)=1
@emit Cloaking device disengaged.

@@ cloakhelp: cloak_help
&cloakhelp cloak parent=:/[v(eng_man)]/0$cloak_help:
print CLOAK_ON PASSKEY=<passkey> : Activates the cloaking device.
print CLOAK_SET PASSKEY=<passkey> : Set the initial cloaking device passkey.
print CLOAK_CHANGE PASSKEY=<old passkey>,<new passkey> : Changes the passkey.
print CLOAK_OFF : Turns the cloaking device off.
print WARNING: The cloaking device will consume power faster than the ship can produce it. If allowed to remain on it will drain the Life Support of its power and kill everyone on board.
```


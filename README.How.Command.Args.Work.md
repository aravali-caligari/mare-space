# How TinyMARE II `$commands` supports command arg patterns (`1$`, `2$`, `3$`), locks, player locks, and ignore unhandled signals

## Overview of command argument patterns

In TinyMARE II, when defining a `$command` attribute, you can specify how the command's arguments are parsed using special suffixes: blank, `1$`, `2$`, and `3$`. These suffixes indicate the expected shape of the arguments provided by the user when they invoke the command.

### Suffix meanings:

- (blank) — zero or more arguments (everything after the command is treated as a single string)
- `1$` — zero or one argument (space-separated, rest-of-line)
- `2$` — exactly two arguments in `arg1=arg2` form
- `3$` — three-or-more arguments in `arg1=arg2,arg3,...` form (also used for multi-word/static subcommand dispatch)

This matters because TinyMARE II command definitions only support **one static command word** (the `$command` itself), followed optionally by arguments. If you need extra static words (subcommands), you typically implement a `3$` dispatcher.

### (Blank) — No suffix: free-form single string argument

This is the default behavior when no suffix is provided. This is equivilant to `1$` behavior. The entire argument string after the command is treated as a single string. However, when converting legacy code, it's often better to use `1$` for clarity.

### Example: no suffix (free-form single string)

```mud
&do_echo me=$echo:
print You said: [v(0)]
```

---

## `1$` — No args, or one “rest-of-line” arg

### Typical user input patterns
- `command`
- `command <anything...>` (everything after the first space and before an  optional '=' sign is treated as one argument)

### Softcode binding
- `v(0)` = the optional argument string (may be empty)

### Example
```mud
&do_scan me=:1$scan:
if v(0)
  print Scanning: [v(0)]
else
  print Scanning current target.
endif
```

Use `1$` for commands that either take no arguments or take a single free-form argument (including text with spaces) before an optional `=` sign.

---

## `2$` — Two args in `*=*` form

### Typical user input pattern
- `command <left>=<right>`

### Softcode binding
- `v(0)` = left side (before `=`)
- `v(1)` = right side (after `=`)

### Example
```mud
&do_setfreq me=:2$setfreq:
print Setting frequency [v(0)] to [v(1)].
```

Use `2$` when the natural syntax is “key=value” and you only need one `=` split.

---

## `3$` — `*=*,*,...` form (and the “dispatcher” workhorse)

### Typical user input patterns

- `command <one word>=<value>`
- `command <arg1>=<arg2>,<arg3>,<arg4>...`
- `command <subcommand(s)> <arg1>=<arg2>,<arg3>,<arg4>...`
- Also commonly used when you need to parse/dispatch **extra static words** after the command (subcommands), even if you don’t actually have 3+ arguments.

### Softcode binding (common convention)
- `v(0)` = left side (also often used as a subcommand selector or “target”)
- `v(1)` = first value after `=` (if any)
- `v(2)` = second value after `,` (if any)
- etc.

### Example: real 3+ args
```mud
&do_route me=:3$route:
@@ user input: "route mars=fast,stealth"
print Dest=[v(0)] mode1=[v(1)] mode2=[v(2)]
```

---

## When to use `3$` even if you “don’t have 3 args”: subcommand dispatch

Because TinyMARE II only supports **one static command word**, a legacy pattern like:

- `$airlock open <target>=<code>`
- `$airlock close <target>=<code>`
- `$airlock off`

cannot be represented as two or more separate `$airlock ...` commands directly. Instead, create **one** `3$airlock` attribute that dispatches on the extra static words.

### Example dispatcher shape
```mud
&airlock_control me=:3$airlock:
@@ user patterns include:
@@ - "airlock open <target>=<code>"
@@ - "airlock close <target>=<code>"
@@ - "airlock set passkey=<newpasskey>"
@@ - "airlock off"
@@ - "airlock reset passkey=<oldpasskey>,<newpasskey>"
switch v(0)
  case open
    call me/airlock_open=v(1)
    break
  case close
    call me/airlock_close=v(1)
    break
  call set passkey
    call me/airlock_set_passkey=v(1)
    break
  case reset passkey
    call me/airlock_reset_passkey=v(1),v(2)
    break
  case off
    call me/airlock_off
    break
  default
    print Invalid subcommand: [v(0)]
endswitch
```

. The key rule is: **use one or more `$command` word(s) before the optional equal sign**, then dispatch in softcode.

The called attributes remove their original $command / :locks: and just implement the core logic.

The dispatcher pattern is very common in legacy softcode conversion, since many commands had multiple subcommands or modes.

---

## Quick selection guide

- Use `1$` if: `command` or `command <free text without '='>`
- Use `2$` if: `command <a>=<b>`
- Use `3$` if: `command <a>=<b>,<c>...` **or** you need `command <subcommand> ...` style dispatching

---

## Optional locking syntax

In the legacy code, many commands used optional locking syntax with the colon and slash (`:/`) characters to indicate that the command should only run if the caller had permission to do so, as evaluated by the target object using the expression after the slash and before the 2nd slash.

### Example legacy code with locking syntax

```mud
oldcommand me=:/[get(link(me),security)]/$oldcommand:<old logic>
```
This means: only run `oldcommand` if the caller (`me`) has permission as determined by evaluating `[get(link(me),security)]` as a boolean expression.

In the converted MARE2 code, you can retain this locking syntax in the converted `:/[lock expression]/#$command:<new logic>` style-attribute, as shown in the previous examples.

### Example converted code with locking syntax

```mud
&cloak_cmd me=:/[v(eng_man)]/3$cloak:print Cloak command received.
```

---

## Optional 'player locks' and 'ignore unhandled signals' syntax

In MARE2, you can also use 'player locks' and the 'ignore unhandled signals' as part of the $command attribute definition. This is only available in MARE2 and not in legacy code. Therefore, converted code will never include these features unless manually added later.

'Player locks' allow you to specify an additional lock that only allows the $command to be executed by players (not NPCs or scripts). 

'Ignore unhandled signals' allow the command to be executed and finish normally even if an unhandled code signal occurs during its execution.

### Examples with 'player locks', 'ignore unhandled signals', or both

```mud
&example_cmd me=:P/[v(eng_man)]/1$example:print Example command with player lock.
&another_cmd me=:~2$another:print Another command that ignores unhandled signals and does not use a lock.
&combined_cmd me=:~P/[v(eng_man)]/1$combined:print Combined command with both player lock and ignoring unhandled signals indicated.
```

---

## Summary

This guide explains how to use TinyMARE II's `$command` argument patterns (`1$`, `2$`, `3$`) effectively for different command structures, including subcommand dispatching, optional locking syntax, player locks, and ignoring unhandled signals. Use the appropriate pattern based on the expected user input and command structure to ensure clear and maintainable softcode.

# End of README.How.Command.Args.Work.md

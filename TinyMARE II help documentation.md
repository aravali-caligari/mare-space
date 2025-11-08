<!-- Converted from windsonline.programs.convertsource.html -->

# TinyMARE II Helptext - Programming

Programming
-----------

TinyMARE features its own built-in programming language that lets objects run commands in response to events in the virtual environment.

*List of Program Commands:*

| Command | — | Description |
|---|---:|---|
| [print](#print) `<message>` | – | Print a message. |
| [set](#set) `<var>=<value>` | – | Set a variable to a value. |
| [unset](#unset) `<var>` | – | Clear a variable. |
| [if](#if) `<expr>[=<match>,…]` | – | Run commands if the expression is true. |
| [switch](#switch) `<expr>` | – | Run different commands based on `<expr>`. |
| [while](#while) `<expr>[=<match>,…]` | – | Run commands in a loop as long as the expression is true. |
| [until](#until) `<expr>[=<match>,…]` | – | Run commands in a loop as long as the expression is false. |
| [for](#for) `<var>=<word list>` | – | Run a block of commands for each word in `<word list>`. |
| [continue](#continue) | – | Jump back to the beginning of a **while**/**until**/**for** loop. |
| [break](#break) | – | Break out of a **switch** block or **while**/**until**/**for** loop. |
| [return](#return) | – | Return from a function call. |
| [exit](#exit) | – | Exit the program. |
| [sleep](#sleep) `<secs>` | – | Pause program for a number of seconds. |
| [alarm](#alarm) `<secs>` | – | Set a timer for a number of seconds. |
| [wait](#wait) `<expr>[=<match>,…]` | – | Pause program until the expression is true. |
| [yield](#yield) `[<#cmds>]` | – | Pause program until the next timeslice. |
| [call](#call) `[<obj/attr>:][<func>][=<arg>,…]` | – | Call a function or another attribute. |
| [label](#label) `<name>` | – | Declare a label called `<name>`. |
| [goto](#goto) `<name>` | – | Jump to label `<name>`. |
| [function](#function) `<name>` | – | Declare a function block called `<name>`. |
| [signal](#signal) `<name>` | – | Declare a signal handler block called `<name>`. |
| [input](#input) `<var>[:<type>]` | – | Wait for input from the player. |
| [system](#system) `<call>[=<value>]` | – | Execute a system call. |
| [@@](#at-at) `<comment>` | – | Specify a comment. |

---

Program Example
---------------

A TinyMARE program is a series of commands—each placed on its own line or separated by semicolons—that run one by one until finished. Extra spaces around commands are ignored, but spacing can be used to indent some lines to reflect that they are part of a loop or function block.

Here is an example program that calculates the first 8 numbers of the Fibonacci sequence:

> ```
> print Calculating the Fibonacci sequence:
> set a=0;
>   print Number 1: [v(a)]
> set b=1;
>   print Number 2: [v(b)]
> set count=2
>
> @@ Loop until the counter reaches 8
> until [v(count)]=8
>   set count=[inc(v(count))]
>   set c=[add(v(a),v(b))]
>   print Number [v(count)]: [v(a)] + [v(b)] = [v(c)]
>   set a=[v(b)]
>   set b=[v(c)]
> done
> print Done!
> ```

When triggered, it produces the following output in the game window:

```
Calculating the Fibonacci sequence:
Number 1: 0
Number 2: 1
Number 3: 0 + 1 = 1
Number 4: 1 + 1 = 2
Number 5: 1 + 2 = 3
Number 6: 2 + 3 = 5
Number 7: 3 + 5 = 8
Number 8: 5 + 8 = 13
Done!
```

To run this program yourself, create a user-defined program attribute on an object (room, thing, exit, or your player). Example commands:

```
@defattr me/fib=program
/vedit me/fib
```

Paste the program into the editor, Save, then trigger:

```
@trig me/fib
```

---

Event Attributes
----------------

Normally, programs are executed in response to game events. Every game object has a list of predefined event attributes that can store a program. Events pass the cause in the `%#` or `[v(#)]` variables.

Examples:

```
@OnLook <object>=fight %#
@OnEnterRoom <object>=run
```

See the "Event Attributes" section below for the full list.

---

Program Execution
-----------------

- When a program starts, a copy of the program attribute text is stored in memory; edits during runtime affect future runs only.
- Commands execute left-to-right, line-by-line; lines split at semicolons unless semicolons are inside `{ }`.
- Variable and function substitution runs before executing the resulting command.
- Functions that insert special characters ({ } = ,) may change syntax — avoid unless controlled.

Common mistakes:
- `call subroutine=[get(v(#),desc)]` — commas in the returned string can change arguments. Use `call subroutine=get(v(#),desc)` or `call subroutine={[get(v(#),desc)]}`.
- `say [italic(I have a meeting; it starts at noon)]` — semicolon inside function causes command split. Use `say [italic({I have a meeting; it starts at noon})]`.

The Stack
---------

- Each running program has a stack for calls, loops, and `switch`. Allows `return`, `break`, `continue`, `done`.
- Stack depth: 20 entries + 1 for signal handler. Exceeding it terminates the program.

Program Variables
-----------------

Three sets of variables:

1. Local Variables
   - Named vars created with `set`. Names must start with a letter; can contain letters, digits, `_`, and special characters.
   - Reserved: `L`, `N`, `U`.
   - Local vars have program scope (single value across stack frames).
   - Access with `[v(<name>)]`.
   - `set` always creates local vars (even empty string). Use `unset` to delete.

   Example:

   ```
   set color=green
   print The selected color is [v(color)].
   ```

2. Environment Variables
   - `%0`–`%9` (or `[v(0)]`–`[v(9)]`), set from trigger arguments or `call` arguments.
   - Saved/restored across function calls.

3. Accumulator
   - `$` (or `%$` / `[v($)]`) contains return value of last game command.

Attribute Locks
---------------

- Any program attribute can have an Attribute Lock—boolean expression evaluated against the cause (see "Locks").
- A function returning blank, `0`, or starting with `#-1` is false.
- Visual editor: check "Attribute lock" and specify expression.
- "Player-only trigger" checkbox further restricts triggering to players.

Example lock (restrict OnEnterRoom to same-owner cause):

```
[match(type(v(#)),thing)] & [match(owner(v(#)),owner(me))]
```

User-defined Commands
---------------------

- Set in visual editor: check "User-defined command" and specify command & args.
- Command arg forms:
  - `command <arg0>`
  - `command <arg0>=<arg1>`
  - `command <arg0>=<arg1>,<arg2>,…`
- Arguments map to `%0`–`%9`.
- Cannot use built-in commands or common exit aliases: `n e s w ne se sw nw u d in out home`.
- If command name equals room exit, command wins; use `go <exit>` to use exit.
- Lookup order for user commands: universal zones → zone hierarchy → room → player contents → player → player's location → location contents → location exits.

Timeslices
----------

- Server ticks at 10 ticks/sec. Each program gets a timeslice each tick.
- Default commands-per-timeslice: 25 (normal) / 250 (admin).
- Program commands that do not jump do not count toward the 25/250 limit.

Diagnosing Running Programs
---------------------------

- Use `@ps` to list active programs with PID, object dbref, attribute, cause, and Next (line/command).
- Terminate with `@halt <PID>` or `@halt` to stop all programs.
- Verbose flag (`@set <object>=verbose`) shows executed commands with substitutions.

Program Energy
--------------

- Each command costs energy supplied by player owner. When depleted, programs terminate.
- Infinite loops exhaust energy; `@halt` may be needed if problematic.

Signal Handlers
---------------

- Programs terminate when their cause abandons the action (leave room, disconnect, die, etc.).
- Signals let you handle interruptions. Declare a `signal` block (top-level, not inside function).
- Example using `Alarm`:

```
@@ Set the alarm timer to fire off in 0.5 seconds
alarm 0.5

@@ Start an infinite loop
while 1
  set count=[inc(v(count))]
  print Count [v(count)]
  sleep 0.1
done

signal alarm
  print Alarm signal received!
  exit
endsig
```

- Visual editor: "Ignore unhandled signals" allows program to continue on unhandled signals.
- Program will not re-enter a signal handler while executing one; signals queue up.

Subroutine Libraries
--------------------

- `call` can load another object's attribute text as a subroutine library: `call <object>/<attribute>:<function>=...`.
- Called attribute text becomes the active program scope for function lookups; signal lookup defaults to original scope unless `system +sig` is used.
- Security: original object executes commands; calling admin-owned object without Modify permission violates security.

Destroyed Objects
-----------------

- Destroyed object: programs on that object terminate immediately.
- If destroyed object is cause of another program, it may persist (unlinked) until last dependent program ends.
- Destroyed objects can be examined/modified by dbref but cannot execute commands.

---

Event Attributes (list)
-----------------------

The following event attributes are available for storing programs (links point to attribute sections):

`@OnBlock`, `@OnClone`, `@OnConnect`, `@OnDay`, `@OnDisconnect`, `@OnDrop`, `@OnDropFail`, `@OnDropIn`, `@OnEnter`, `@OnEnterFail`, `@OnEnterRoom`, `@OnFail`, `@OnFightFail`, `@OnGive`, `@OnGiveAway`, `@OnGiveAwayFail`, `@OnGiveFail`, `@OnGrab`, `@OnGrabFail`, `@OnGrabUp`, `@OnGrabUpFail`, `@OnHour`, `@OnKill`, `@OnLeave`, `@OnLeaveFail`, `@OnLeaveRoom`, `@OnLogin`, `@OnLook`, `@OnMinute`, `@OnOpen`, `@OnPay`, `@OnPayFail`, `@OnSearch`, `@OnSearchFail`, `@OnSucc`, `@OnSunrise`, `@OnSunset`, `@OnTalk`, `@OnTalkFail`, `@OnTimeslice`, `@OnUnidle`, `@OnUse`, `@OnUseFail`.

---

## print `<message>` {#print}

Send `<message>` to the cause (`%#`) of the program. Message succeeds even if the cause moves out of normal `@pemit` range.

Note: unlike `say` or `@emit`, `print`'s `<message>` is not parsed separately; functions and `%`-variables do not need escaping.

**Example**

```
print The %U slides away to reveal a secret passage.
```

If object is named Bookshelf, displays:

```
The Bookshelf slides away to reveal a secret passage.
```

See also: Programming, `@pemit`

---

## set `<variable>=<value>` {#set}

Set a program variable to `<value>`. `<variable>` may be a Local Variable, Environment Variable (0–9), or the Accumulator `$`. Local Variables override attribute retrieval for `[v()]`.

`set` always creates/sets a Local Variable; use `unset` to delete.

**Example 1**

```
set color=green
print The selected color is [v(color)].
```

Outputs: `The selected color is green.`

**Example 2**

```
set 0=10; set 1=20
print Line 1: Environment 0="%0", 1="%1"
call subroutine=30
print Line 2: Environment 0="%0", 1="%1"

function subroutine
  print Line 3: Environment 0="%0", 1="%1"
endfunc
```

Outputs show environment variables are local to calls.

See also: Programming, `unset`, `v()`

---

## unset `<variable>` {#unset}

Clear `<variable>` to a blank string. If a Local Variable, it is deleted.

See also: Programming, `set`

---

## if / elseif / else / endif {#if}

Format:

```
if <expression>
  <commands>
endif

if <expression>=<match>,…
  <commands>
elseif <expression>=<match>,…
  <commands>
else
  <commands>
endif
```

- `if` runs commands if `<expression>` is true; otherwise jumps to next `elseif`/`else`/`endif`.
- `expression` alone is boolean using `! ( ) | &`.
- Expression with `=` compares left expression to one or more comma-separated `<match>` strings. If any match, true.
- Max 100 arguments to right of `=`.

**Example 1**

```
if [strlen(v(0))]
  print Argument %0 is specified.
  set start=%0
else
  set start=10
endif
```

**Example 2**

```
if [int(v(input))]=0
  print Exiting the program.
  exit
elseif [int(v(input))]=<1,>10
  print Invalid choice!
  exit
endif
```

See also: Programming, `switch`, `until`, `wait`, `while`

---

## switch / case / default / endswitch {#switch}

Format:

```
switch <expression>
  case <match>
    <commands>
  case <match>
    <commands>
  default
    <commands>
endswitch
```

- `switch` evaluates `<expression>` and executes the first matching `case`.
- Execution continues across subsequent `case/default` unless `break` used.
- `default` matches any expression and should be last.
- `case` matches use wildcard rules (see Wildcard Matching).
- Nested up to 20 deep.

**Example**

```
switch %0
  case *e*
    print Reached section A.
    break
  case >paper
    print Reached section B.
  case >14
    print Reached section C.
    break
  default
    print Reached section D.
endswitch
```

See also: Programming, `break`, `if`

---

## while / done {#while}

Format:

```
while <expression>
  <commands>
done

while <expression>=<match>,…
  <commands>
done
```

- Loops while `<expression>` true.
- `continue` jumps to top; `break` exits loop.
- Nested up to 20 deep.
- Max 100 arguments to the right of `=`.

See also: Programming, `break`, `continue`, `for`, `if`, `until`, `wait`

---

## until / done {#until}

Format:

```
until <expression>
  <commands>
done

until <expression>=<match>,…
  <commands>
done
```

- Loops while `<expression>` is false (i.e., until true).
- `continue` and `break` apply as with `while`.
- Nested up to 20 deep.
- Max 100 args.

See also: Programming, `break`, `continue`, `for`, `if`, `wait`, `while`

---

## for / done {#for}

Format:

```
for <variable>=<word list>
  <commands>
done
```

- Iterates over words in `<word list>`, setting `<variable>` each iteration.
- `<variable>` can be Local, Env (0–9), or Accumulator ($).
- `continue` gets next word; `break` exits loop.
- Nested up to 20 deep.

**Example 1**

```
for animal=ant bear cat dog elephant fox
  if [v(animal)]=c*
    continue
  endif
  print [v(animal)] begins with [ucstr(mid(v(animal),0,1))].
  if [strlen(v(animal))]=>4
    break
  endif
done
```

Displays: ant, bear, dog, elephant (based on logic)…

**Example 2 (nested)**

```
for x=2 7
  for y=3 5 10
    print X=[v(x)], Y=[v(y)], Sum=[add(v(x),v(y))], Product=[mul(v(x),v(y))]
  done
done
```

See also: Programming, `break`, `continue`, `set`, `until`, `while`

---

## continue {#continue}

Used only inside `while`/`until`/`for`. Jumps back to top of loop and re-evaluates or fetches next word.

See also: Programming, `break`, `for`, `until`, `while`

---

## break {#break}

Used inside `switch` or loops. Jumps to `endswitch` or `done` respectively.

See also: Programming, `continue`, `for`, `switch`, `until`, `while`

---

## return `<value>` {#return}

- Use inside `function` or `signal` blocks.
- Leaves the called function/signal and returns to line after `call`.
- Sets Accumulator `$` to `<value>` upon return (even blank).
- In signal handlers, `<value>` does nothing; accumulator restored after handler returns.

See also: Programming, `call`, `exit`, `function`, `signal`

---

## exit `<value>` {#exit}

- Immediately terminates running program, except whole-attribute `call` (in which case sets `$` and returns).
- End-of-program auto-terminates; whole-attribute call clears `$`.

See also: Programming, `call`, `return`

---

## sleep `<seconds>` {#sleep}

- Pause for `<seconds>`; multiples of 0.1 sec only (server tick = 1/10 sec).
- Sleeping programs listed separately in `@ps`.
- Use `@halt` to stop by PID.

See also: Programming, `wait`, `yield`

---

## alarm `<seconds>` {#alarm}

- Sets or resets an alarm timer to send `Alarm` signal after `<seconds>` (multiples of 0.1).
- `alarm 0` disables.
- Requires a `signal alarm` handler or program will terminate (unless signals ignored).

See also: Programming, `signal`

---

## wait `<expression>` {#wait}

Format:

```
wait <expression>
wait <expression>=<match>,…
```

- Pauses until `<expression>` true. Evaluated once per tick (1/10s). Programs consume no energy while waiting.
- Expression forms as in `if`/`while`.
- Max 100 args.
- Example:

```
wait [v(health)] = <100
use medical herb
```

See also: Programming, `if`, `sleep`, `until`, `while`

---

## yield `[<#commands>]` {#yield}

- Pause until next timeslice. If `<#commands>` specified, only pauses if that many commands cannot fit in remaining timeslice.
- Helps ensure atomic execution of small command groups.
- Cannot exceed timeslice limits (25 / 250 default).

Example:

```
yield 3
@create Macguffin
@addparent %$=Macguffin Parent
@teleport %$=here
```

See also: Programming, `sleep`

---

## call (functions / attributes) {#call}

Forms:

```
call <function>
call <function>=<argument>,…
call <object>/<attribute>=<argument>,…
call <object>/<attribute>:<function>=<argument>,…
```

- Calls function in current scope or another object's attribute.
- Up to 10 arguments `%0`–`%9`.
- Called attribute text is loaded into memory and becomes active scope for function lookups; signals default to original scope unless `system +sig` used.
- Uses program stack (max 20 entries).

See also: Programming, `function`, `return`

---

## label `<name>` {#label}

Declare a label to jump to with `goto`.

See also: Programming, `goto`

---

## goto `<name>` {#goto}

- Jump to first line where `label <name>` is declared in current program/function scope.
- `goto` cannot jump into `switch` or loops; does not use stack.

Examples show using `goto` to break out of nested loops, or to retry.

See also: Programming, `label`

---

## function / endfunc {#function}

```
function <name>
  ...
endfunc
```

- Declares a top-level function block callable with `call`.
- `endfunc` required.

See also: Programming, `call`, `signal`

---

## signal / endsig {#signal}

```
signal <name>
  <commands>
endsig
```

- Declares a signal handler named `<name>`. `%0` gets set to the signal received.
- Can list multiple signals comma-separated or use `*` for all.
- Must be top-level; `endsig` required.

Example catching `leave, disconnect, death`.

See also: Programming, `function`

---

## input `<variable>[:<type>]` {#input}

- Pauses program until player inputs a response to the active program via PID (intended for HTML modules / JS client).
- Client sends `!<PID>!<input string>` which becomes the variable value.
- Only the program's cause may send input.
- `<type>` controls sanitization (default Safe):

| Type | — | Description |
|---|---:|---|
| Any | – | Stored as-is. |
| Float | – | Converted to float. |
| Integer | – | Converted to integer. |
| Line | – | Newlines replaced with spaces. |
| Safe | – | `{ } = ,` and newlines replaced with spaces (safe for `[v()]`). |

See also: Programming, `set`

---

## system `<call>[=<value>]` {#system}

System calls modify program parameters or session behavior. Most require Security power.

Common calls:

- `+sig` — When `call` loads another attribute, switch signal lookups to current program scope.
- `-sig` — Revert signal handler lookup to original scope.
- `-output` — (Security) Freeze normal game output on cause; output queued up to 1MB. `print` sends to console output instead.
- `+output` — (Security) Release frozen output; queued output is sent.
- `target` — Change cause (`%#`) of current program to `<value>` (requires Modify). With Security power, `<value>` can be `FD:ConcID` to target sessions not logged in.
- `connect` — (WIP/hidden) Connect a session to a player char (security).

See also: Programming

---

## @@ `<comment>` {#at-at}

- Comment line in program. Does nothing.
- Comments cannot contain `;` because that denotes next command.

See also: Programming

---

Wildcard Matching
-----------------

Each `<match>` is case-insensitive. Forms:

- `value` — exact match (case-insensitive). `*` wildcard matches zero or more chars, `?` matches exactly one char.
- `<value` — if `value` numeric, expression < value. Otherwise alphabetical comparison (expression comes before).
- `>value` — numeric or alphabetical greater-than.
- `!value` — negation; prefix before `<` or `>` if used.

---

<!-- End of converted document -->
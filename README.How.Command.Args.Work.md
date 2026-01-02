# TinyMARE II `$command` argument parsing (short guide)

This is a conversion-focused cheat sheet for how TinyMARE II parses `$command` attributes and how to preserve legacy behavior when porting multi-word commands.

## Core rule (why `3$` exists)

TinyMARE II user-defined commands have **one static command word** (the `$command`). Any additional static words ("subcommands") must be handled by a **single dispatcher** attribute, usually using `3$`.

## Suffixes: what they mean

When defining a `$command` attribute, the suffix determines how input is split into `v()` arguments:

- (blank) — free-form; the entire post-command text becomes one string (effectively the same as `1$`).
- `1$` — 0 or 1 argument; rest-of-line string (may include spaces) up to an optional `=`.
- `2$` — exactly two args in `left=right` form.
- `3$` — `left=right1,right2,...` form **and** the standard choice for multi-word/subcommand dispatch.

## Bindings (what ends up in `v(0)`, `v(1)`, ...)

- `1$`
  - `v(0)` = optional argument string (may be empty)
- `2$`
  - `v(0)` = left of `=`
  - `v(1)` = right of `=`
- `3$` (common convention)
  - `v(0)` = left of `=` (often used as a selector like `open`, `set passkey`, `on passkey`, etc)
  - `v(1)` = first value after `=` (if any)
  - `v(2)` = second value after `,` (if any)
  - etc.

## Dispatching multi-word legacy commands (use `3$` even without 3 args)

Legacy softcode often used multiple `$command ...` attributes like:

- `$airlock open passkey=*`
- `$airlock passkey *=*,etc...`
- `$airlock initial=*`
- `$airlock off`

In TinyMARE II, these become **one** `3$airlock` command that switches on the extra static words (contained in `v(0)`)

Minimal dispatcher shape:

```mud
&airlock_cmd me=:3$airlock:
switch v(0)
  case open passkey
    call me/airlock_open=v(1)
    break
  case passkey *
    call me/airlock_passkey=rest(v(0)),v(1)
    break
  case initial
    call me/airlock_initial=v(1)
    break
  case off
    call me/airlock_off
    break
  default
    print Invalid subcommand: [v(0)]
endswitch
```

Conversion nuance:

- The dispatcher is the **only** `$airlock` command definition.
- The called attributes (`airlock_open`, `airlock_close`, etc) should contain only the core logic (remove their legacy `$command` wrappers and locks).
- The key rule is: parse **static words before the optional `=`**, then dispatch.
- The dispatcher always uses `switch`/`case` for clarity.

## Quick selection

- Use `1$` for: `command` or `command <free text>` (no structured `=` parsing needed).
- Use `2$` for: `command <a>=<b>`.
- Use `3$` for: `command <a>=<b>,<c>...` **or** any subcommand-style pattern: `command <subcommand> ...`.

## Optional lock syntax (legacy and conversion)

Legacy code often used `:/.../` to guard a command (only run if the lock expression passes). Preserve it in converted `$command` attributes.

```mud
&cloak_cmd me=:/[v(eng_man)]/3$cloak:print Cloak command received.
```

## Optional MARE2-only flags (usually not added during conversion)

These exist in TinyMARE II but not legacy dumps; avoid adding them unless you are intentionally extending behavior:

- `P` (player-only lock): only players can run the command.
- `~` (ignore unhandled signals): command continues normally if an unhandled signal occurs.

Examples:

```mud
&example_cmd me=:P/[v(eng_man)]/1$example:print Example with player lock.
&another_cmd me=:~2$another:print Example that ignores unhandled signals.
&combined_cmd me=:~P/[v(eng_man)]/1$combined:print Both flags.
```

<!-- End of README.How.Command.Args.Work.md -->

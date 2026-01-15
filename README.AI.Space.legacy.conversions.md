# SpaceMUSE → MARE:Space2 conversion cheat sheet (AI-short)

MARE:Space (aka MARE:Space2 softcode) was rebuilt vs the SpaceMUSE 1.0 used in MicroMUSE. Legacy space softcode will often **not** work unchanged.

This doc is the short list of what usually needs to change.
For authoritative MARE:Space commands/functions/datatypes, see `README.Space.softcode.manual.md`.

## Quick mindset

- Expect both **syntax changes** (MUSE → TinyMARE II/MARE2 softcode) and **space-model changes** (SpaceMUSE → MARE:Space).
- Prefer migrating to **vector/euler attributes** and MARE:Space’s **new `@` commands** rather than preserving per-axis legacy patterns.

## Terminology mapping

- Linear Position → `Pos`
- Linear Velocity → `Vel`
- Linear Accel → `Acc`
- Heading → Attitude Position (Euler) (`Att_Pos`) (not “altitude”)
- Angular Vel → Attitude Velocity (`Att_Vel`)
- Angular Accel → Attitude Accel (`Att_Acc`)
- X/Y/Z triplets → “Vector”
- Angle triplets X/Y/Z → Yaw/Pitch/Roll (“Euler”)
- Fleet → Universe
- Ship → Space Obj (a ship is a Space Obj with type `Spacecraft`)
- Dock/Land → Station Inside / Land
- Sector → Region (MARE2 uses “sectors” for other purposes)

See `README.Space.terminology.md` for the extended glossary.

## Datatypes (high impact)

- Most space-state attributes are now **single attributes** containing **3 space-delimited values**:
  - Example vector: `1.5 2.37 0.8`
  - Example euler: `yaw pitch roll` (in **degrees**)
- Math functions generally operate on vectors/eulers as a unit (e.g., `vadd()`).
- Angles are presented as degrees; radians can still be used by prefixing values with `rad` (followed by a space).
- Some functions return **key/value** strings like `key=value:key2=value2:...`.

## Attribute renames (SpaceMUSE → MARE:Space)

Most of these collapse X/Y/Z into a single vector/euler attribute.

| SpaceMUSE | MARE:Space |
| --- | --- |
| `LinposX/Y/Z` | `Pos` |
| `LinvelX/Y/Z` | `Vel` |
| `LinAccX/Y/Z` | `Acc` |
| `AngposX/Y/Z` | `Att_Pos` |
| `AngvelX/Y/Z` | `Att_Vel` |
| `AngaccX/Y/Z` | `Att_Acc` |
| `Thrust` | `Main_Burn` (vector X,Y,Z) |
| `Acceleration` | `Acc_Forward` (vector X,Y,Z) |
| `Sector` | `Region` |

Tip: When converting softcode that does per-axis reads/writes, replace it with the vector/euler form and adjust calculations accordingly.

## Function conversions (common)

- `dg2rd` → `deg2rad`
- `rd2deg` → `rad2deg`
- `km2ps` → `km2pc`
- `ps2km` → `pc2km`
- `ks2ls` → `kms2ls`
- `ls2ks` → `ls2kms`
- `dist3d` → `vdist` (or parse `relstate()` field `distance`)
- `head3d` → `vlookat` (or parse `relstate()` field `bearing`)
- `relhead` → parse `relstate()` field `orient`
- `velhdg` → `v2e`
- `velmag` → `vmag`
- `relphi` → parse `relstate()` field `ApprAngle`
- `orbit` → parse `orbitstate()`
- `updates` → `spupdates`
- `inrange` / `insight` → `sensorlist`

Unchanged (per legacy doc): `km2au`, `au2km`, `km2ly`, `ly2km`, `inspace`, `indist`.

TBD / not available / N/A (as of this doc): `face`, `acctime`, `relacc`, `swait`, `sync`, `zone2obj`.

## Attributes that are unchanged

- `Mass`
- `Radius`
- `Type`

## No equivalent yet (don’t assume they exist)

- `Rating`, `Efficiency`, `Fuel`, `VisMult`
- `Recover` (obsolete)
- `Hull`, `SprStr`
- `Pwrgen`, `Pwrfuel`, `Energy`
- `S0` through `S9`
- `AShip`

## Other notable behavioral differences

- SpaceMUSE `ROOM_ZEROG` flag is not present in MARE:Space.
- Docking/Landing:
  - Uses Station Inside/Land concepts.
  - Typically requires a lock attribute and a Station attribute indicating destination.
- Spacecraft do not “leave the universe”; they typically go to a NullSpace region and return to a StarSystem region.
- Sensors are primarily hardcode-driven now (Visual/IR/LIDAR/Gravity Waves) and return multiple values.
- Space Objs:
  - Are object type flag `S` with a separate `Space_obj_Type`.
  - Usually have no location (they are “inside themselves” conceptually) and are not meant to be regular player-owned objects.
  - Spacecraft often reference a normal Mare object via `@body`/`Body` for descriptions/standard attributes.

## New MARE:Space attributes (high-level)

These are the kinds of attributes you’ll see/need to integrate with when converting.

- Identity/state:
  - `Space_ID`
  - `Space_obj_Type`
  - `Body`
- Physics:
  - `Grav`
  - `Acc_SC`
  - `Linear_Burn`
  - `Acc_Forward`
  - `Main_Burn` (and timer-related targets)
- Attitude control goals:
  - `Att_Acc_Goal`, `Att_Vel_Goal`, `Att_Pos_Goal`
  - `Att_Control`
- Timer helpers:
  - `burn_timer`, `main_burn_target`, `linear_burn_target`
  - `att_burn_timer`, `att_burn_target`
- Relative state slots:
  - `Rs1Tgt`, `Rs2`–`Rs5` and `relstate(#source,#target)`
- Orbit state slots:
  - `os1`–`os5`, `os*orbited`, and `orbitstate()`

## Practical conversion checklist

- Convert any `Lin*X/Y/Z` and `Ang*X/Y/Z` logic to vector/euler equivalents.
- Replace legacy thrust/accel control with MARE:Space’s burn/control commands from `README.Space.softcode.manual.md`.
- Replace legacy “distance/heading/orbit” helpers with `vdist`, `vlookat`, `relstate()`, and `orbitstate()` patterns.
- If a legacy attribute/function has no MARE:Space equivalent, treat it as a redesign point (don’t fake it).

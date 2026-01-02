# SpaceMARE2 softcode manual (AI-short)

This is the **short, conversion-focused** version of `README.Space.softcode.manual.md`.
Use it as the “what do I call / what do I rename / what shape is the data” guide when porting SpaceMUSE softcode to SpaceMARE2.

For full details and long reference tables, see `README.Space.softcode.manual.md`.

## Core datatypes you’ll see everywhere

- `n` / number: decimal number or boolean (`0`/`1`).
- `s` / string.
- `d` / dbref: object id like `#1234` (often a Space Obj dbref).
- `v` / vector: `x y z` (3 space-delimited numbers). Units depend on context (km, km/s, km/s^2, newtons).
- `e` / euler: `yaw pitch roll` (3 space-delimited angles, **degrees**).
  - Some functions accept optional `deg` or `rad` prefix (followed by a space); output is usually degrees.
- Key/value strings: `key=value:key2=value2:...`.

Practical rule: if legacy SpaceMUSE code manipulates `linposx/linposy/linposz`, convert it to **one** vector attribute/argument.

## The high-value `@` commands (what you’ll use in conversions)

Most of these show usage if run with no parameters.

### Region + object basics

- `@defspregion`, `@redefspregion`, `@undefspregion`: create/edit/delete regions.
- `@spregion`: move/update a spacecraft’s region.
- `@spcreate`: create a basic space object.
- `@spimport`: import ephemeris objects (pos/vel/mass/etc) from CSV.

### Position + velocity + attitude

- `@pos`, `@vel`, `@posvel`: set/reset position/velocity.
- `@attpos`, `@attvel`, `@attacc`: set attitude position/velocity/accel.
- `@att`: set angles + rotation velocity + accel in one command.
- `@sv`: set the whole state snapshot (pos/vel/acc + rotations).

### Thrust / navigation control

- `@mainburn`: main engines (forward direction only).
- `@linburn`: small thrusters (vector burn for fine maneuvering; X is “forward”).
- `@burntimer`: timed burn that ramps down to 0 at timer end.
- Targets for timers:
  - `@mainburntarget`, `@linburntarget`.
- Attitude goal control:
  - `@attposgoal`, `@attvelgoal`, `@attaccgoal`.
- `@spupdate`: force exactly one space update tick (useful when stepping).

### Docking / landing

- `@sppark`: park (dock/land/stationkeep).
- `@spunpark`: leave dock/land.

### Time

- `@sptime`: show simulation time (not server time).

### Tracking targets for derived data

- `@orbittarget`: track an object for orbit calculations each update.
- `@reltarget`: track an object for relative-state calculations each update.

## “Powers” required

- Power `Space`: required to run space `@` commands and privileged functions.

## Key config knobs (often relevant when debugging)

- `SPACE_LORD`, `SPACE_DEBUG`, `SPACE_RUNNING`.
- Bulk fast-forward: `SPACE_BULK_REMAINING`, `SPACE_BULK_MAX`.
- Ephemeris tracking: `EPHEMERIS_LOADED_JD`, `EPHEMERIS_LOADED_UPDATE`.
- Sensors retention: `SENSOR_RECENT_THRESHOLD`, `SENSOR_LOST_RETENTION`.

## Key `@list` inventories (for names/enums)

- Space: `SpObjects`, `SpObjectTypes`, `SpRegions`, `SpRegionTypes`.
- Sensors: `SensorFlags`, `VisualContactTypes` (as applicable).
- Navigation: `OrbitStateTypes`, `AttControlTypes`.
- Docking: `StationTypes`, `ParkTypes`, `StationResults`.

## Softcode functions: what matters in conversions

You’ll usually consume these via key/value parsing or vector/euler math.

- Vector math: `vadd()`, `vsub()`, `vdist()`, `vmag()`.
- Euler helpers: `eshortest()` and other euler math utilities.
- Relative/orbit state:
  - `relstate(d,d)` returns a key/value string with relative position/velocity/angles.
  - `orbitstate(d,d)` returns a key/value string with orbital elements/state.
- Sensors:
  - Prefer sensor APIs; `indist()` exists but is often less useful than sensor functions.

## High-signal Space Obj attributes (read/write targets)

These are the attributes most conversions touch directly.

### General

- `@spaceid`, `@spregion`, `@spregionprev`, `@spbody`.
- `@mass` (kg), `@radius` (km), `@albedo`.
- State vectors:
  - `@pos` (km), `@vel` (km/s), `@acc` (km/s^2), `@grav` (km/s^2).
- Attitude:
  - `@attpos` (euler), `@attvel` (euler), `@attacc` (euler).

### Spacecraft-only

- Main/linear burn inputs + derived accel:
  - `@mainburn`, `@mainburnacc`, `@linburn`, `@linburnacc`.
  - Timers/targets: `@burntimer`, `@mainburntgt`, `@linburntgt`, `@attburntimer`, `@attburntgt`.
- Attitude goals/control:
  - `@attvelgoal`, `@attposgoal`, `@attcontrol`.
- `@accforward`, `@accsc`.

## Key/value parsing (very common)

Many “big” functions return `name=value` fields separated by `:`.
Expect to parse fields like these (examples):

- `relstate()` commonly includes: `Pos`, `Vel`, `Acc`, `Distance`, `Altitude`, `Bearing`, `Approach`, `Orient`, `ApprAngle`, `NullPoint`.
- `orbitstate()` commonly includes: `Type`, `Pos`, `Vel`, `Distance`, `Altitude`, `Periapsis`, `Apoapsis`, `Eccentricity`, `Inclination`, `PeriodSecs`.

## Dock/land practical notes

- Stationing depends on distance/velocity thresholds and station size/type.
- Station must have the `Station` flag enabled.
- Station types include `DockPort`, `Hangar`, `Land`.

For locks/hooks, see the full manual’s station attributes section (e.g., `@ParkLock`, `@OnAdmit`, `@OnPark`, `@OnParkFail`, `@OnRelease`, `@OnDepart`).

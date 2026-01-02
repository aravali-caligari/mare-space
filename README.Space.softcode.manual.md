# Softcode Manual

Short version for conversions: `README.AI.Space.softcode.manual.md`.

This has a summary of @commands and functions and general notes to help MARE softcoders to use the SpaceMARE features. Most of these commands display usage info if they are run without parameters

## Datatypes

number, n = Decimal number or boolean (0=false, 1=true)
string/text/s = String
vector, v = Vector (3 space-delimited X,Y,Z numbers, usually km but can be km/s or km/s^2)
euler, e = Euler angles (3 space-delimited numbers, degrees in Yaw Pitch Roll order)
angle, a = Angle (degrees)
Key-Value pairs = Colon-delimited, keyname + "=" + value
dbref, d = DB Ref # (usually referring to a Space Obj DBREF)

## @command's

### Space region commands

- @defspregion = Create a new space region (i.e. star system)
- @redefspregion = Change name and other info for a space region
- @undefspregion = Delete a space region
- @spregion = Update a spacecraft to switch regions

### Space obj commands

- @spcreate = Create a basic space object
- @spimport = Load space objects with ephemeris (pos/vel/mass/etc) from a CSV file

### Positional and attitude (heading)

- @pos = Reset spacecraft position to values
- @posvel = Reset spacecraft velocity to values
- @vel = Reset a spacecraft's velocity
- @att = Set angles of the spacecraft (direction in space) plus rotation velocity and accel in one command
- @attpos = Set angular position (i.e. direction)
- @attacc = Set angular accelerion
- @attvel = Set angular velocity
- @attposgoal = Set a goal euler to turn to
- @attvelgoal = Set a goal velocity euler to speed up to
- @attaccgoal = Set a goal accel euler to burn with
- @sv = Set every position/vel/accel/rotations for a spacecraft

### Navigational control

- @linburn = Set thrusters for small movements in any direction (like to prepare to dock with small stuff). The X-direction means 'forward' towards attitude
- @linburntarget = Target Linear Burn when using @burntimer
- @mainburn = Set main thrusters to start burning, only to 'forward'
- @mainburntarget = Target main burn for when using @burntimer
- @burntimer = # of seconds for a timed burn that starts as the target values and then stops at 0 seconds.
- @attaccgoal = Set a goal for spacecraft to speed up to a specific rotational accel
- @attvelgoal = Set a goal for spacecraft to speed up a specific rotational vel
- @attposgoal = Set goal for spacecraft to point to a specific angle
- @spupdate = force a space update, once. Useful if space is 'frozen', to step it once at a time

### Docking/Landing/etc

- @sppark = Park the spacecraft at a station (land/dock)
- @spunpark = Leaving the dock/land/free space

### Space Time

This is showing Space Sim 'time' which is the date of the object positions, not the server time.

- @sptime = Display space sim time info

### Targeting objects for constant updates

- @orbittarget = Set a target object as being tracked for orbital value calculations each update
- @reltarget = Set a target object as being tracked for relative value calculations each update

## Powers

"Space" - Able to run all the space @Command's and privileged space functions

## @config values

SPACE_LORD = Name of player that owns all Space Objects
SPACE_DEBUG = Enable/disable output of Space debugging info into LOG_SPACE
SPACE_RUNNING = enable/disable automatic space updates each second
SPACE_BULK_REMAINING = Set number of space updates to fast-forward to (it takes some time because updates are done in batches and not a large jump)
SPACE_BULK_MAX = Number of bulk space updates to do per second when a bulk operation was asked for
EPHEMERIS_LOADED_JD = Julian Date of last loaded ephemeris data
EPHEMERIS_LOADED_UPDATE = Space update # when ephemeris was loaded
SENSOR_RECENT_THRESHOLD = How long are new or missing sensor contacts considered 'Recent'
SENSOR_LOST_RETENTION = How long to keep sensor data for lost contacts

## @List's available

- CoordSymbols - Used for formatting degree to coordinates conversions
- SpCensus - Counts of everything in space
- SpObjects - Space Objects list
- SpObjectTypes - Space Obj types
- SpRegions - listing of all current regions
- SpRegionTypes - Space Region Types
- OrbitStateTypes - Types of Orbits
- SensorFlags - Flags describing a sensor reading
- StationTypes - Types of stations (hangar, dockport, land)
- ParkTypes - Types of parking (dock, land, stationkeep)
- StationResults - Reasons a dock or landing did or didn't work
- AttControlTypes - Attitude Control types

## '@list counters'

SpaceUpdates (how many updates/secs has the space code been updating positions/vels/etc)
SpaceId (next id # to use)

## Type lists in detail

### Space Obj Types

"Star"
"Planet"
"Moon"
"Smallbody" = Asteroid or comet
"Spacecraft" = Anything human-made like satellites, crewed vessels
"Debris" = Former spacecraft blown up
"Ordnance" = Missiles usually
"Marker" = Navigational marker

### Space Region Types

"Starsystem"
"Interstellar" (the vast space and place between Starsystem Regions)
"FTL" (e.g. warpspace, hyperspace, etc, as opposed to FTL drives that stay in regular space)
"Null Space" (no gravity and a blind region to prepare spacecraft or park them temporarily)

### Orbit State Types

"Elliptic" Normal orbit with a max and min distance to the gravity source
"Circular" rare moment of a perfectly circular orbit (almost impossible to get)
"Parabolic" Orbit that will be on the edge of escaping the source's gravity (almost impossible to get)
"Hyperbolic" Orbit that will escape a gravity source
"Retrograde" Moves clockwise around a gravity sources as seen from 'above'. Normal orbits are counter-clockwise

### Visual Contact Types

Invalid
Light Source (e.g. Star)
Seen
Eclipsed
Occultation (hidden by another)
Hidden
Too Dim
Too Small
Cloaked

### Station Types

'None' = No dock or landing
'Hangar' = An inside hangar to safely hold spacecraft
'DockPort' = An outside docking port to connect two spacecraft
'Land' = spaceport on land

### Parking Types

'None'
'Dock' = Connect to a dockport or hangar
'Land' = Landing on a spaceport
'StationKeep' = Do station keeping without a connection

### Coord Symbol Types

"HMS" = Hours, Mins, Secs = example 17h 56m 23s
"HMSNoSymbols" = example 23 34 10
"DegMinSecs" = Degrees, Mins Secs = example 23&deg; 23m 15s
"DegTicks" = example 23&deg; 23' 56"
"DegOMinSecs" = example 23o 23m 56s
"DegOTicks" = example 12o 23' 56"
"DegNoSymbols" = example: 23 15 56

Using the 'decimal position' parameter that some functions have, you can shorten the output and use decimals, e.g. 23o 23.27m

## Flags

### Space object flags

"Immaterial"   can pass through objects, no collisons possible
"Undetectable" hidden from everything
"Station"      Things can dock/attach/land to this object
"FixedPos"     Does not move for any updates (gravity + vel doesn't affect)
"Charted"      Well-known object that everybody knows where it is
"Sensor"       Has Space sensors to detect other objects

### Space Region Flags (used for each type of Region)

"Frozen" No updates happen here
"Gravity" Region has normal gravity effects
"Blind" Objects are unable to detect anything else
"Vast" Positions/vel/acc are measured in lightyears
"Collision" Objects are able to collide
"FTL" Objects are able to go past lightspeed

## softcode functions()

Definition of Parameter and output types.
Each one is expressed as a single argument and sometimes space-delimited

- n = regular number
- b = boolean (0 or 1)
- s = string
- d = DB ref # (usually a space obj)
- r = region id #
- a = radian or degree angle
- v = vector or position is 3 space-delimited numbers (x y z)
- e = euler set of angles is 3 space-delimited numbers (yaw pitch roll) with an optional prefix of 'deg ' or 'rad ' to pick degrees or radians

### Conversion functions

  | function name     | Purpose                                    |
  | ----------------- | ------------------------------------------ |
  | n = deg2rad(n)    | Convert degrees to radians for 1 angle     |
  | n = rad2deg(n)    | Convert radians to degrees for 1 angle     |
  | n = kms2ls(n)     | Convert kilometers per sec to light speed  |
  | n = ls2kms(n)     | Convert light speed to kilometers per sec  |
  | n = au2km(n)      | Convert AUs to kilometers                  |
  | n = km2au(n)      | Convert kilometers to AUs                  |
  | n = km2ly(n)      | Convert kilometers to light-years          |
  | n = km2pc(n)      | Convert kilometers to parsecs              |
  | n = pc2km(n)      | Convert parsecs to kilometers              |
  | n = pc2ly(n)      | Convert parsecs to light-years             |
  | n = ly2km(n)      | Convert light-years to kilometers          |
  | n = ly2pc(n)      | Convert light-years to parsecs             |
  | s = secs2elapsed  | convert secs to a nicer display of elapsed |

### Vector math

  | function name           | Purpose                                                |
  | ----------------------- | ------------------------------------------------------ |
  | e = v2e(v)              | Convert vector to a euler                              |
  | v = v2q(v)              | Convert vector to a quaternion                         |
  | v = vadd(v,v,..)        | Add vectors together                                   |
  | v = vaddhalf(v,v)       | Add a vector to half of another vector                 |
  | n = vapprangle(v,v)     | determine approach angle between 2 vectors (pos+vel)   |
  | n = vapprvel            | Closing or seperating velocity between pos+vel         |
  | v = varc(v,v)           | get arcseconds between 2 vectors                       |
  | v = vavg(v,v)           | get average between 2 vectors                          |
  | n = vclosest(v,v,v,v)   | Closest distance between two line segments             |
  | v = vconj(v)            | get conjugate (flip) of a vector                       |
  | v = vcross(v,v)         | Cross product of 2 vectors                             |
  | n = vdist(v,v,..)       | distance between 2 or more vectors in a series         |
  | n = vdet(v,v,v)         | Determinant of a matrix formed by 3 vectors            |
  | v = vdiv(v,n)           | divide a vector by a number                            |
  | n = vdotproduct(v,v)    | get dot product of 2 vectors                           |
  | v = vhalf(v)            | get half of a vector                                   |
  | n = vlinept(v,v)        | Closest distance from a line to a point                |
  | e = vlookat(v,v)        | get a euler degree to look from 1 vector to another    |
  | n = vmag(v,v,..)        | magnitude - same as vdist()                            |
  | v = vmul(v,n)           | multiply a vector by a number                          |
  | v = vnorm(v)            | Normalize the vector to a unit vector                  |
  | v = vopposite(v)        | opposite vector                                        |
  | v = vrel(v,v)           | get relative vector between 2 vectors                  |
  | v = vrotate(v,e)        | rotate a vector by a euler                             |
  | v = vscale(v,n)         | multiply a vector along its direction by a scalar      |
  | v = vset(n,n,n)         | Set a vector based on 3 args                           |
  | e = vshortturn(v,v)     | get the shortest rotation between 2 vectors as a euler |
  | v = vsub(v,v,..)        | subtract a series of 2 or more vectors                 |

### Euler math

  | function name        | Purpose                                                 |
  | -------------------- | --------------------------------------------------------|
  | v = e2v(e)           | Convert a euler to a vector                             |
  | e = ebetween(e,e)    | Find the angle between two eulers                       |
  | e = econj(e)         | Find the euler conjugate (to reverse the rotation)      |
  | e = edeg2rad(e)      | Convert a euler set from degree to radians              |
  | e = edotproduct(e,e) | Get the dot product of two eulers                       |
  | e = ehalf(e)         | Get half the euler                                      |
  | e = einterp(e,e,n)   | Interpolate from 1 euler to another on a scale          |
  | e = eopposite(e)     | Find the opposite euler set of angles                   |
  | e = erad2deg(e)      | Convert a euler set from radians to degrees             |
  | e = erotate(e,e)     | Rotate a euler set with another to a new set            |
  | e = escale(e,n)      | Scale-down or up a euler set                            |
  | e = eset(n,n,n)      | Set a euler up by using 3 args                          |
  | e = eshortest(e,e)   | Get the shortest angle between two eulers               |

### Region functions

  | function name        | Purpose                                                                |
  | -------------------- | ---------------------------------------------------------------------- |
  | s = regionlist()     | List of Space region ID's (1-10+) space-delimited                      |
  | s = starregions()    | List of Star system region ID's (space-delimited)                      |
  | s = starlist()       | List of all Stars in star systems                                      |
  | s = regionname(r)    | name of a space region                                                 |
  | s = regiontype(r)    | type of a space region                                                 |
  |                      | (Nullspace, StarSystem, Interstellar, FTL)                             |
  | s = regionobjs(r,s)  | Space obj's in a region with an optional obj type filter               |
  | n = getregion(d)     | Region # a space obj is located in                                     |
  | b = inspace(d)       | Space Obj In regular space? (non-NullSpace) (0 or 1)                   |
  | b = inftl(d)         | Space Obj in FTL space? (0 or 1)                                       |
  | v = regionpos(r)     | position vector in lightyears of region                                |
  | b = inregion(d,s)    | Is a Space Obj in this region (by Name) (0=false, 1=true)?             |
  | b = instation(s)     | Is this space obj stationed? (i.e. parked) (0 or 1)                    |

### Relative/Orbit State functions

  | function name        | Purpose                                                                             |
  | -------------------- | ----------------------------------------------------------------------------------- |
  | s = relstate(d,d)    | Returns a long key-value pair of Relate State info for 2 space obj's. Details below |
  | s = orbitstate(d,d)  | Returns a long key-value pair of Orbit State info for 2 space obj's. Details below  |

### Sensor functions

  | function name        | Purpose                                                                  |
  | -------------------- | ------------------------------------------------------------------------ |
  | s = sensorlist(d)    | List of DB obj #'s a space object detects                                |
  | s = sensorinfo(d,d)  | Key-value pair list of sensor info for an object (see below for details) |
  | s = issensed(d,d)    | return 1 or 0 if an obj is detected by another                           |

### In-distance function

- Use sensor functions instead of this for most purposes

  | function name        | Purpose                                                 |
  | -------------------- | ------------------------------------------------------- |
  | s = indist(d, n)     | List of Space Obj's within a certain distance           |

### Charted functions

  | function name        | Purpose                                                                   |
  | -------------------- | ------------------------------------------------------------------------- |
  | s = chartedlist(d)   | List of DB obj #'s a space object knows about                             |
  | s = chartedinfo(d,d) | Key-value pair list of charted info for an object (see below for details) |

### Navigational functions

  | function name             | Purpose                                                     |
  | ------------------------- | ----------------------------------------------------------- |
  | n = acc2dist(n,n,n,n)     | Get least accel to slow from 1 vel to another in a distance |
  | n = acc2maxvel(n,n,n)     | Get new acc allowed to fit a max vel                        |
  | n = acc2stop(n,n,n,n)     | Get accel to stop at a distance with a new timeframe        |
  | n = distmin(n,n,n,n)      | Get Distance to arrive at a mid-point                       |
  | n = dist2stop(n,n,n,n)    | Get distance to arrive at a stop at the target              |
  | n = distatstop(n,n,n,n,n) | Arrival distance to a target                                |
  | n = time2mid(n,n,n)       | Time to arrive at the mid-point                             |
  | n = time2stop(n,n,n)      | Time to arrive at the stop point                            |

### Coordinate functions

For converting celestial (Right-Ascension, Declination) or land coordinates (Longitude, Latitude)

  | function name           | Purpose                                                                          |
  | ----------------------- | -------------------------------------------------------------------------------- |
  | n = coord2deg(s)        | Convert a text coordinate to degrees                                             |
  | s = coords2deg(s,s)     | Convert a pair of coordinates to a pair of degrees                               |
  | s = deg2coord(n,n,n)    | Convert degrees to a coordinate with symbolset and an optional decimal position  |
  | s = deg2latlong(n,n,n)  | Convert 2 degrees to Lat/Long with optional symbol set                           |
  | s = deg2radec(n,n,n,n)  | Convert 2 degrees to RA/DEC with optional symbol sets                            |

See @list CoordSymbols for a list of symbol set names that can be used for the 'deg2*' functions.

Meaning of'Decimal position' used by some coordinate functions

1. Stop at the first position and turn it into a decimal
2. Stop at the 2nd position (minutes) and make that a decimal
3. Include all 3 positions and make seconds a decimal (default)
4. Make all positions into integers (no decimal)

### Time functions

  | function name         | Purpose                                                     |
  | --------------------- | ----------------------------------------------------------- |
  | n = spupdates()       | Get # of space updates (secs) since beginning of time       |
  | n = spephemupdates()  | # of updates since last load of ephemeris (space-data)      |
  | n = spephemjulian()   | julian date of last ephemeris load (space-data)             |
  | s = spephemdate()     | date/time in TDB of last ephemeris load                     |
  | s = sptime()          | date/time of now in Space sim time                          |
  | n = spjulian          | julian date of now                                          |

## Attributes (Space Obj - General)

Anything listed as 'x 3' is a triple set of numbers (like a position x y z) in space-separated format.
'Euler' is an angle in degrees. Euler x 3 is Yaw, Pitch, Roll.
'Station' is any place that can be docked, landed or drifted near by in free space.

### Station / Dock / Park attributes

- @ParkLock = Check if a spacecraft is allowed to station there
- @OnAdmit = Code that runs on the object when a spacecraft has stationed with it
- @OnPark = Code running on a space obj when it succeeds on stationing
- @OnParkFail = Code on a space obj that fails on an attempt with a station
- @OnRelease = Code run on the station when a space obj departs
- @OnDepart = Code run on the space obj when it leaves a station

### Other Space obj attributes

@spaceid = Unique identifier for Natural space objects and spacecraft
@spregion = Region the obj is in
@spregionprev = Previous region it was in
@spbody = DB Ref of the 'body' (decorative 'thing' object associated to this space obj)
@mass = Mass in kg
@radius = Radius in km
@albedo = How reflective (visible) the object is (0 to 1.0)
@pos = Position (km x 3)
@vel = Velocity (km/s x 3)
@acc = Acceleration Total (km/s^2 x 3) from Gravity + Spacecraft
@grav = Current gravity acceleration (km/s^2 x 3)
@attpos = Attitude position (direction, Euler x 3)
@attvel = Attitude velocity (spin, Euler x 3)
@attacc = Attitude accel (thrusters, Euler x 3)

## Attributes (Space Obj - Star only)

@luminosity = How bright the star is (1.0 = Brightness of our Sun)

## Attributes (Space Obj - Spacecraft only)

@aperture = Diameter of the spacecraft's telescopes (mm). 500mm is a good telescope.
@maglimit = What is the highest magnitude the spacecraft can see? +20.0 is good.
@accforward = Accel along 'forward' of the spacecraft hull when thrusting with main engines + OMS thrusters (km/s^2 x 3)
@mainburn = Main engine burn (Newtons) along 'forward'
@mainburnacc = Main burn (km/s^2) along 'forward'
@linburn = OMS thrusters burn (newtons x 3) along 'forward'
@linburnacc = linearburn as km/s^2
@burntimer = # of seconds to burn before a automatic cut-off
@mainburntgt = Main burn (N) to use during a timer event
@mainburntgtacc = Same but as km/s^2 during timer
@linburntgt = Linear Burn (N) to use during a timer event
@linburntgtacc = Linear burn target as km/s^2
@attburntimer = # of seconds to burn attitude accel
@attburntgt = Attitude Accel to use during a timer event
@attvelgoal = Attitude (direction) Vel Goal for rotations (Euler x 3)
@attposgoal = Attitude (direction) Pos Goal for rotations (Euler x 3)
@attcontrol = Preferred method to control automatic attitude (0 = none, 1 = pos, 2 = vel, 3 = acc)
@accsc = Accel due to Spacecraft thrusting (km/s^2 x 3) after taking into account its direction

## Key Value Pairs

Some functions need to return a lot of data and do that by returning a long string called a key/value pair. Colon-delimited, with: name + '=' + value
Example: abc=123:def=xyz:ghi=56.234

### Key Value Pairs of relstate()

Origin = DB# of Origin obj
OriginName = Name of Origin
OrigRadius = Radius of Origin
Target = DB# of target space obj
TargetName = Name of target
TargetRadius = Target radius (km)
Pos = Relative Positiion (km x 3)
Vel = Relative Vel (km/s x 3)
Acc = Relative Acc (km/s^2 x 3)
Distance = Distance (km)
Altitude = Distance 'above' the radius of the target
Bearing = Angle to face target (Euler x 3)
Approach = Approach (Euler x 3)
Orient = Orientation to the target (relative) (Euler x 3)
ApprAngle = Approach Angle (0-180)
NullPoint = Angle to go towards stationary velocity (Euler x 3)

Example Output:

Origin=13215:OriginName=ISA Frontier Storm:OriginRadius=0.08:Target=12988:TargetName=Earth:TargetRadius=6371.01:Pos=-443.33745724 6762.44683966 0.007615859:Vel=-7.652826295 -0.500457488 0.000028457:Acc=0.000562861 -0.008660684 -0.00000001:Distance=6776.963579678:Altitude=405.953579678:Approach=-89.990665554 -0.000281334 -0.006573268:Bearing=20 0 0:Orient=93.750871262 0.000064388 0.000068748:ApprAngle=90.009334446:NullPoint=-176.258463184 0.000212597 -0.006508869:

### Key Value Pairs of orbitstate()

Orbiter = DB# of Orbiting obj
OrbiterlName = Name of the orbiter
OrbiterMass = Mass of the orbiting obj (kg)
Orbiteradius = Orbiting obj radius (km)
Central = DB# of the orbited
CentralName = Name of the orbited
CentralMass = Mass of the orbited obj (kg)
CentralRadius = Radius of the orbited obj (km)
Type = Type of Orbit (String)
Pos = Relative pos (km x 3)
Vel = Rel. vel (km/s x 3)
Distance = Distance (km)
Altitude = Distance 'above' a radius (km)
Periapsis = Periapsis (closest dist during the orbit)
PeriapsisAlt = Altitude of periapsis above the radius
Apoapsis = Apoapsis (fartest dist during the orbit)
ApoapsisAlt = Altitude of apoapsis above the radius
Eccentricity = Eccentricity (0.0 to i.0 to >1.0)
Inclination = Inclination (deg)
TrueAnomaly = True Anomaly (deg)
LAN = Longitude Ascending Node (deg)
AzimuthAngle = Azimuth Angle (deg)
ArgumentPeri = Argument of Periapsis (deg)
PeriodSecs = Orbit period (sec)
PeriodText = Descriptive text of the orbit (string)
Time2PeriSecs = Time to Periapsis (sec)
Time2PeriText = Text of Time to Periapsis (string)
Time2SincePeriSecs = Time after Periapsis (sec)
Time2SincePeriText = Text of Time after Periapsis (string)
Time2ApoSecs = Time to Apoapsis (sec)
Time2ApoText = Text of Time to Apoapsis (string)
Result = Result description (string)

Example output:
Orbiter=13215:OrbiterName=ISA Frontier Storm:OrbiterMass=128100:OrbiterRadius=0.08:Central=12988:CentralName=Earth:CentralMass=5972168398723500348538880:CentralRadius=6371.01:Type=Elliptic:Pos=-5372.746765018 4131.789236411 0.0239522:Vel=-4.675244979 -6.078190202 0.000012398:Distance=6777.764387739:Altitude=406.754387739:Periapsis=6775.76676624:PeriapsisAlt=404.75676624:Apoapsis=6777.986320823:ApoapsisAlt=406.976320823:Eccentricity=0.000163759:Inclination=0.000222658:TrueAnomaly=143.13765663:LAN=77.019082858:AzimuthAngle=0.009167656:ArgumentPeri=77.718008668:PeriodSecs=5553:PeriodText=1h 32m 32s:Time2PeriSecs=3345:Time2PeriText=55m 44s:TimeSincePeriSecs=2208:TimeSincePeriText=36m 47s:Time2ApoSecs=569:Time2ApoText=9m 28s:Result=Determined

### Key Value Pairs of sensorinfo()

Colon-delimited, name + '=' + value

id = Target DB#
name = Target name
type = Type of target obj
flags = Contact sensor hit flags
dist = distance
radius = radius of target
diameter = diameter of target
arcsecs = Arc-Seconds of apparent size of target (3600th of a degree)
arcdegs = degrees wide of apparent size
firstdetected = time since first detected (secs)
lastdetected = last detected (secs)
pos = position (km x 3)
vel = velocity (km x 3)
acc = acceleration (km x 3)
velmag = magnitude of velocity (km)
accmag = magnitude of accel (km)
appmag = apparent magnitude (mag #)
absmag = absolute magnitude (magnitude #)
albedo = albedo of the target (0 - 1.0)
phase = phase angle (0-180 deg)
apprangle = approach angle (0-180 deg)
apprvel = Approach vel (km/s)
linept = shortest Distance to line between objects
lookat = Direction to object
shortestangle = Direction to object (shortest rotation)

Example:

id=12988:name=Earth:type=Planet:flags=Detected,Known,SeenVisual:dist=6776.578644888:radius=6371.01:diameter=12742.02:arcsecs=504554.400704404:arcdegs=140.154000196:firstdetected=606795:lastdetected=0:pos=1753.210442886 -6545.859093592 -0.012351614:vel=7.408171478 1.985418732 -0.00002644:acc=0.002240894 -0.008385684 -0.000000016:velmag=7.669608347:accmag=0.008679937:appmag=-20.8538:absmag=-3.8002:albedo=0.367:phase=133.462721811:apprangle=89.990973923:apprvel=-0.00120823:linept=6776.578644888:lookat=-75.070948692 -0.000104209 0.000080065:shortestangle=-90.009026077 -0.000049772 0.00004978:

## Dock/Land/takeoff/undock

For 'stationing/parking' (dock/land/station keeping), a spacecraft has to be within a certain distance and velocity parameters of another space obj (planet/moon/craft/etc). The rules are based on the sizes of the involved space obj's, and type of docking.
Short Terminology:

- Station is the thing being docked or landed on. It could be a planet/moon/spacecraft/etc.
- Space Obj's must have a 'Station' flag turned on to be docked/landed with.
- Station Types are: DockPort, Hangar, Land
- Park/Parking is the action of docking/landing/station keeping with another obj, and also the name of the command @SpPark
- Unpark is the act of leaving (taking off or undocking).
- Park Types are: DockedToPort, DockedInHangar, Landed, StationKeeping
- 'DockPort' is the thing a station can have that is just a way to attach using a docking collar to another craft, on the outside. Like a semi-truck attaching to a warehouse door. All craft start with this but may have a hangar instead.
- 'Hangar' is a thing to allow a docking craft to go 'inside' the station. Like going in a parking garage. This means the docking ship has stopped and can no longer pilot or use sensors until it leaves. It is also undetectable to outside spacecraft.
- 'StationKeeping' means a craft is 'outside' the station and not attached and instead is floating close by and manuevering to keep itself at that spot. Like parking in an outside parking spot.
- 'Land' is for planets/moons/asteroids. A spacecraft that has landed is still considered outside and detectable and able to use sensors as normal.

Eligibility Rules to dock/land:

- A 'station/receiving obj' must have the 'Station' flag turned on. And must be detectable.
- For docking (dockport or Hangar)
  - Attitude and regular thrusters must not be firing. Spacecraft has to stay still for attempting a dock.
  - Relative velocity must be 50 meters/sec (0.050km/s) difference or less
  - Distance between craft (with accounting for the sizes of them) must be less than 1km from hull to hull.
  - A receiving station will get @parklock used to verify it's allowing the incoming craft to dock. This could verify 'friendly' craft or indicate it's full or something else.
- For station-keeping
  - Attiude and regular thrusters must not be firing.
  - Relative velocity \<= 0.05km/sec
  - Distance from hull to hull \< 2km
  - Craft will maintain their relative position and velocity with the target automatically.
  - Station-Keeping can be broken if relative velocity goes too high or thrusters are used.
- For landing
  - Are they within 1.5% of distance from hull to the land and 0.03% of radius for vel?
  - example for earth: 1.5% of 6378 km = \<95.67 km, 0.03% of 6378 km = \<1.91 km/sec. This is distance 'above' (i.e. altitude) the planet. By comparision, asteroids of 100km radius would allow only for landing at \<= 1.5km and \< 0.03km/sec velocity.

Eligibility for leaving:

- A craft is always allowed to leave, even if its in a hangar.

Breaking the dock/landing:

- Hangar docks will always remain docked until the craft leaves
- Docking ports and station keeping can be 'broken' if relative velocity exceeds 0.025km/s (25meters/s) or thrusters are used
- Landing can be broken if relative vel > 0.04% of radius or altitude > 2% or thrusters are used

Leaving:

- Craft that are docked will point to 'away' from the station and given a small 3 m/s velocity to kick away
- Craft that were landed are placed into a 1.5% altitude circular orbit above the landing spot

Soft code attributes / commands involved:

- @SpPark - Used to do the parking (docking/landing/stationkeeping). One of the parameters says what type of parking. Env 0 gets the result code.
- @SpUnPark - To leave
- @ParkLock - Verifies if an obj is allowed to dock/land.
- @OnPark - Triggered if the obj succeeds at docking/landing.
- @OnParkFail - Gets triggered if an obj fails to dock/land
- @OnAdmit - Gets triggered on the station obj if a spacecraft lands/docks on it
- @OnDepart - Triggered on the spacecraft when it leaves the station
- @OnRelease - Triggered on a station when a craft has left

## Common how-to's

### Create a space obj

1. @spcreate SomeShipName=spacecraft,Solar System
2. Take a note of the obj id or consult with '@list spobjects'. This object won't be in the room so you can't refer to names directly
3. @body #123=#456   This associates a space obj to a decorative Thing object to represent the space object. Locks and Triggers, events, exist on the body, not the spobj.
4. @mass #123=121000     In kg's
5. @radius #123=0.25     In km's
6. @albedo #123=0.75     0.0 (complete black) through 1.0 (shiny)
7. @aperture #123=500    mm's wide of telescopes
8. @maglimit #123=20     upper magnitude it can see (high numbers = fainter)
9. @attpos #123=45 23 57   Set attitude (direction) to Yaw 45deg's, Pitch 23deg's, Roll 57deg's
10. Up to this point, the space obj is in the region but has no position or velocity (nan)
11. @posvel #123=5.6 567 234, 99.76 1.23 567    This set a beginning position/velocity
12. This fully places the object and gets it moving

### Create a space obj that undocks from a station

1. Follow the steps as above for creating a space obj except the @posvel step
2. @spregion #123=NullSpace    NullSpace is used when inside a hangar. Otherwise it stays in the regular region
3. @stationtype #999=hangar    This is the type of station of #999
4. @parktype #123=DockedInHangar    This is the type of dock/landing of #123
5. @stationedto #123=#999   This places the spacecraft at the station #999
6. @spunpark #123           "Un-park" (leave)

### Thrusts and attitude controls for spacecraft

- @mainburn #123 = 128100       128,100 newtons accel 'forward'
- @mainburnacc #123 = 1         1 km/s^2 accel 'forward'
- @linearburnacc #123 = 0.02, 0.03, 0     20m/s^2 'forward', 30m/s^2 'left'
- @mainburntarget #123 = 1281000     Target values used for timed burns
- @linearburntargetacc #123 = 0.02, 0.03, 0       Target values used for timed burns
- @burntimer #123 = 30     Burn using the target values for 30 seconds
- @attposgoal #123 = 23 45 0     Set attitude position goal to yaw 23 deg's, pitch 45 deg's, roll 0 deg's
- @attcontrol #123 = 1      Lock attitude position to whatever @attposgoal says
- @attburntarget #123 = 1 0 0    Attitude accel to use during a timed event
- @attburntimer #123 = 10        Burn attitude thrusters for 10 seconds

### Docking

- @SpPark #123 = #456,DockedToPort

### Undocking

- @SpUnPark #123

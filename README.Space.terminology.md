# Glossary / Terminology

## Universe

* A Listing of Space Objects in the Universe organized by Space Regions

## Space Region (SPACE_REGION and space_regions[])

* Individual areas of space separated by either vast distances (i.e. star systems) or by technology (i.e. Hyperspace)
* Every star system counts as a region, which may have one or more stars (i.e. binary star systems)
* The interstellar space between stars is a single region that extends forever
* Star system regions are located within the Instellar region
* Objects in one region cannot effect or see objects in another region except Stars
* Each starsystem region has a Position in Lightyears inside the Interstellar region
* A spacecraft could leave a star system region and enter the Interstellar region if it travelled far enough and even enter another star system region if it travelled even more, but this would imply FTL-drive technology that keeps it in normal space.
* Each Region has its own listing of Space Objects that belong to it

## Space Region types (SPACE_REGION_TYPE)

* Nullspace (basically a parking lot where space objects don't move and don't see)
* Interstellar (the space between star systems) - Only 1 Interstellar region can exist at a time
* Starsystem (one or multiple stars together, e.g. The Solar System, or Proxima Centauri)
* FTL region (a dimension or special place where faster-than-light travel can occur)

## Space Object (SPACE_OBJ)

* A single object that represents a star/planet/moon/spacecraft/etc
* Has identifiers like name, dbref, Space ID's
  * Space ID closely follows the standards of NASA JPL NAIF ID's, DSN, NORAD
* Physical properties like mass/radius/albedo/luminosity
* Has a State vector for pos/vel/accel's and rotation heading/vel/accel
* Various spacecraft-specific properties like shields, thrust, fuel, etc
* Visibility performance like mag limit, aperture size

## Space Object types (SPACE_OBJ_TYPE)

* Null
* Star
* Planet
* Moon
* Smallbody (i.e. asteroids or comets)
* Spacecraft
* Debris
* Ordnance (i.e. missiles, projectiles)
* Marker (navigational spot)

## Space Object flags (flags[])

* These flags would typically be used by markers for the center of the starsystem and other spots of interest,
Planets, moons, well-known space stations, etc.
  * Cloaked - Unseen by visual or sensor readings
  * Immaterial - Cannot collide or interact with matter
  * Dock - Can be docked with
  * Land - Can be landed on
  * FixedPos - Fixed in space, no gravity, no updates
  * Charted - Charted on space maps
  * Sensor - Has ability to see and detect other space objects

## Position (POSITION datatype structure)

* Positions have an X, Y, Z that is tied to a region and uses 0,0,0 as the center of the region (i.e. approx. Sun)
* Right-hand cartesian coordinates
* Heliocentric Eliptic rectangular, NOT airplane-based (which would be Z+ down)
* Coordinates are defined by a system named ICRS (International Celestial Reference System), see below for details
* Positions in starsystem regions are expressed in kilometers
* Interstellar and FTL regions have position expressed as Lightyears
* Positions and velocities update every second unless SPACE_DT is changed to something different
* There is a variable named SPACE_RUNNING that also controls if space is updating per second in Mare

### X,Y,Z - ICRS (International Celestial Reference System)

* ICRS is a standard coordinate system for Space object positions as defined by the International Astronomical Union.
* The center of ICRS is centered on the Sun's barycenter
  * A barycenter is the 'true' center of the star system
  * Our Sun is offset from the barycenter due to influences by the Gas giants and other planets pulling slightly on it
  * The sun circles the true 'barycenter'
  * The distance of the sun to the barycenter changes and may be 500,000 to 800,000 km's depending on if the gas giants are lined up or equidistant. The sun itself is a radius of ~690,000km's so sometimes the barycenter position is 'inside' the sun
* Directions of X, Y, Z axises
  * Positive X Axis points to where Vernal Equinox was on J2000.0, which is Jan 1, 2000 12:00 TT (Noon terestial time)
  * Positive Y axis points to 'right' (or 'east') of Positive X by 90 degrees and lives on the eliptic plane, as seen from 'above'
  * Positive Z points to 'up' (North celestial pole). Z=0 is at the eliptic plane
* ICRF (international Celestial Reference Frame) is a realiziation of ICRS that takes into account about what reference points are used to define ICRS
* For ICRF, The IAU has most recently defined what the reference points are in 2019, and called it the ICRF3 standard. This has reference points made up of 303 'definining' sources that don't appear to move as they are extragalatic sources, mainly quasars that are very distant so that it doesn't appear to move.

## Quaternion (QUAT datatype structure)

* Invented by William Hamilton
* A 4-dimensional math construct that records a rotation (r, i, j, k)
* Very useful in calculating the results of rotations. Used internally for all rotations.
* The quat.c has lot more commented details on how it works and is used and references
* Right-hand intrinsic active rotations
* Using Hamilton Rotation conventions (not JPL)

## Euler (EULER datatype structure)

* Euler angles were invented by Leonhard Euler, pronounced "oiler" in 1751, a Swiss mathematician
* Standard Yaw, Pitch, Roll angles are in radians/degrees
* Only used for human-readable output and input.
* Converted to/from Quaternions before rotation work is done
* Right-hand instrinsic active Rotation in the ZYX order

## Rotations and Angles

* Angle directions
  * Yaw (left/right)
  * Pitch (up/down)
  * Roll
* Represented as "Tait-Bryan Euler" Angles
  * Invented by Peter Tait in mid to late 19th century
  * Further worked on by George Bryan in early 20th century
  * A type of Euler angles that are intrinsic versions of Euler angles
* Right-hand intrinsic active rotations
* Commonly used in Aerospace for spacecraft
* Rotation is applied in the ZYX (321) order
* Represented in code as Euler Angles with radians, or Quaternions
* Qauternions follows the Hamilton Rotation conventions (not JPL)
* When viewing the rotations by looking toward the spacecraft from the outside, it is always counter-clockwise
* Conversion/display/input functions for degrees understands and displays these formats
  * Lattitude, Longitude (various formats)
  * Right-ascention, Declination (various formats)
  * Can use the degree symbol

### What does each rotation point do?

| Rotate | Dir   |
| :----- | ----- |
| +Yaw   | Right |
| +Pitch | Up    |
| +Roll  | Right |
|        |       |
| -Yaw   | Left  |
| -Pitch | down  |
| -Roll  | Left  |

### Definitions of the Rotation Axes

| Axis   | Axis dir             | Spinning around it measures |
| ------ | -------------------- | --------------------------- |
| Z-axis | straight up/down     | Yaw                         |
| Y-axis | left wing to right   | Pitch                       |
| X-axis | forward/backward     | Roll                        |

## Vector (VECTOR datatype structure)

* Uses X, Y, Z as a delta / offset from a position or to do math with velocities / accelerations
* Commonly used as kilometers in the code but vectors could mean anything like light-years

## State Vector (STATE_VECTOR datatype structure)

* A combination of properties that define position, velocity and accelerations
* Every space object has its own state vector
* Linear position, velocity
* Accelerations by nature gravity, artificial gravity, and spacecraft thrust
* Rotation heading, velocity, acceleration
* Many properties are temporary in nature and only used for gravity calculations and not meant to be saved to the DB

## Gravity / Acceleration Calculations

* Acceleration comes from three sources
  * Natural gravity
  * Artificial gravity (i.e. tractor beams or certain FTL-drives)
  * Spacecraft-based thrust
* Velocities and Positions are updated based on acceleration
* Calculations are per second unless SPACE_DT is changed
* Accelerations and the resulting updates are calculated using the integration math known as 'Velocity Verlet', which is a 'Symplectic' integrator.
* 'Velocity Verlet' is highly accurate. As an example for a simulation of the Earth around the sun which is 149 million km distant, after 31 million seconds (i.e. a year), the position of Earth was only 'off' by 20km from its position that NASA JPL says it is
* Calculations are done in 'long double' variables and then lower precision values are copied that would be saved by the db

## Orbit (ORBIT_STATE datatype structure)

* Used to describe the various classical elements and extra elements of a space object
* Usually only for display of orbit elements that occur due to positions and velocities
* Most orbits turn counter-clockwise when viewed just above the planet/star
* A Space object can reference up to 3 (MAX_ORBIT_STATE) Orbit State targets. Example: A Spacecraft gets Orbital parameters with the Sun and a nearby Planet.
* Each update (sec), the Orbit states that are targeted get recalculated.

## Relative State (RELATIVE_STATE datatype structure)

* Used to calculate positions, velocities, attitude angles between two space objects
* e.g. The relative state between a spacecraft and Earth
* Space Objects are allowed up to 3 (MAX_RELATIVE_STATE) target space objects to compare against. Example: A Spacecraft relative to the Sun, a nearby Planet, and the close-by Spacestation
* Every update, the relative states are re-calculated.

## Space Sensors

* Anything that detects other objects is named Sensors.
* Types of things detected by sensors are: Visible light, Infrared, LIDAR, Radar, Gravity Waves.
* LIDAR and Radar are considered Active sensors while the others are passive detection.
* Another thing detected by sensors are spacecraft Transponders.
* Things behind a planet/moon or other object completely are in 'Occultation'.
* Things that pass into the shadow of another object like when the earth casting a shadow on the moon, are called "eclipses". Example: Lunar eclipse
* Solar "eclipses" are actually occultation despite the name because the moon is blocking the sun.
* Most sensors cannot detect things behind another thing except Gravity Waves or Transponders
* Sensors generically measure these things:
  * Arcseconds (how wide an object appears to the observer, in 3600th of a degree. e.g. Moon from Earth is ~1,800 arcseconds or 0.5 degs)
  * Distance / Velocity / Accel
  * How long ago was it last seen
    * Contacts remain on the list for sometime after it disappears
    * Position and Vel are estimated based on last numbers
  * How recently was it detected
* Visual sensors measure these additional things
  * Phase Angle % (how much of the object is lit up by the nearby Star, i.e. moon phases)
  * Absolute Magnitude (how bright in magnitude would the object appear at 1AU or 1 Parsec)
  * Magnitude ("Apparent Mag") is a measure of how bright it is, in a negative logarithmic scale. Smaller values are brighter. Sample values:
    * -26.80 = direct sun at a distance of 1AU
    * -12.60 = full moon, seen from Earth
    * -04.14 = Venus (from Earth)
    * -02.94 = Jupiter (from Earth)
    * +06.50 = magnitude of the dimmest star visible to the naked eye on Earth
    * +07.78 = Neptune (from Earth)
    * +11.05 = Proxima Centauri (closest star)
    * +31.50 = magnitude that Hubble can detect

## Docking / Landing / Station Keeping

* A 'Station' is a space obj that can be docked or landed or with station keeping
* Station Types
  * DockPort - An attachment point on the outside of a craft for joining two craft together with an airlock
  * Hangar - An Inside 'garage', typically in a large spacecraft
  * Land - Found potentially on planets/moons/asteroids
* 'Parking/Park' is the act of docking / landing / station-keeping with a station
* Park Types
  * DockedToPort - Docked outside like a semi-truck parked against a warehouse door
  * DockedInHangar - Docked like an inside garage spot
  * Landed
  * StationKeeping - Floating nearby but keep in synch with pos/vel like an outside parking spot
* 'UnPark' is leaving

## Julian Date / Gregorian Calendar

* Gregorian Calendar
  * This is what people are used to for Dates and Times
* Julian Date (JD)
  * It is a whole + fractional number that is days since an epoch (Nov 24 -4713 BC at Noon). The fraction part refers to the time of day since Noon.
  * A typical value that is recent is 2460354.5 (Feb 14 2024 12:00AM)
  * The fraction refers to a 86,400th of a day plus noon. 0.0 = Noon, 0.25 = 6pm, 0.5 = 12midnight. One second = ~0.0000115741 (1 / 86400).
  * A C Library from the IAU (International Astronomical Union) named SOFA (Standards of Fundamental Astronomy) handles conversions between systems.

## Terminology of Stars/Systems

* Star is the generic term for any massive illuminating body made of gas.
* 'Sun' is a specific name for our star. No other star is named Sun.
* 'Sol' or 'Solis' are latin words for the Sun that has been re-used by SciFi books and popular culture but has no official meaning.
* Star system refers to a grouping of stars sharing gravitational attraction.
  * Binary stars fit this category.
  * Officially, single stars do not count as a Star System.
  * But for this Simulation we count single stars as a Star System.
* Planetary systems refer to any star or star system with orbiting natural bodies like planets.
* For purposes of this code, every planetary system is named a 'Star system'. Because its shorter and sounds cooler.
* 'Solar system' is technically a unique name for our Planetary system and no others. There is a lot of debate on this distinction. And popular culture often says every star planetary system is a Solar System.
* This simulation treats 'Solar System' as the name of our planetary system with the star named 'Sun'.
* No other star is 'Sun', and no other planentary or star system is named 'Solar System'.

## FTL Faster-than-light travel

* Some FTL drives make use of an FTL-type space region that the spacecraft goes "through"
  * e.g. Subspace (for warp drives), Hyperspace, Jump Space, etc.
  * Those count as a special type of Space region and may behave differently than regular space regions
  * Spacecraft enter the FTL region, spend some time there, and then re-appear into a Star system or Interstellar region.
* Some spacecraft may have FTL drives that jump instantly or travel large distances instead of going into a special space
  * e.g. Wormhole Drives, Star Gates, Stutterwarp, Blink drive, Fold Space Drives, Bergenholm Drive
  * Those move the spacecraft to another star system region or the interstellar region

## Identification numbers - NAIF ID's / DSN GSCID's / NORAD ID's / COSPAR ID's

* There four well-known spacecraft and space object (natural bodies) identification schemes.
  * NAIF, DSN, NORAD, COSPAR

### NAIF (Navigation and Ancillary Information Facility) ID's

* This is an ID system that is assigned by NASA JPL to catalog Solar System objects and spacecraft
* These types of objects get NAIF ID's
  * Sun, planets, moons, comets, asteriods
  * Spacecraft, Satellites, deep-space spacecraft
  * Special locations in space, such as Barycenters
    * Example: NAIF ID 10 = Sun, 0 = Sun's Solar-system Barycenter
  * Ground stations on Earth
  * Even identifying scientific instruments and equipment on a spacecraft
  * .. etc ...
* Slides [https://naif.jpl.nasa.gov/pub/naif/toolkit_docs/Tutorials/pdf/individual_docs/06_naif_ids.pdf]
* Detailed doc [https://naif.jpl.nasa.gov/pub/naif/toolkit_docs/C/req/naif_ids.html]

### DSN (Deep Space Network) ID's

* DSN (Deep Space Network) ID's named GSCID (Global Spacecraft Identifier) are assigned to long-range spacecraft that leave Earth orbit
* DSN is part of NASA JPL
* NAIF includes DSN GSCID's into their numbering scheme as negative ID's
* Listing of assigned spacecraft ID's [https://public.ccsds.org/SpacecraftID.aspx]

### NORAD ID's

* NORAD's abbreviation standards for North American Aerospace Defense Command
* NORAD has tracked space objects for decades
* US Space Command took over space monitoring duties from NORAD ~2000
* NORAD ID's are assigned to Earth-orbit spacecraft, satellites, and space debris
* [https://en.wikipedia.org/wiki/Satellite_Catalog_Number]
* NAIF encodes NORAD ID's into their ID system as negative numbers

### COSPAR ID's

* COSPAR (Committee on Space Research)
* An International body that assign's IDs to spacecraft
* COSPAR ID list [https://ilrs.gsfc.nasa.gov/missions/satellite_missions/past_missions/index.html]
* United Nations Office for Outer Space Affairs [https://www.unoosa.org/oosa/osoindex/search-ng.jspx]

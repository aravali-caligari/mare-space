# Legacy Space to new Space conversions

MARE:Space was re-created from the ground up as compared to the SpaceMuse 1.0 used in MicroMUSE in the 90s.
There was a large body of MUSE 'softcode' written to work with Space 1.0 that did things like display read-outs, work controls, and perform space actions and certain calculations.

For a shorter version of this guide, see `README.AI.Space.legacy.conversions.md`.

Given that MARE:Space was re-created, many things that the MicroMUSE space-related softcode relied on do not work and requires changes. This doc gives a guide on how to modify MUSE softcode to work with the new MARE:Space code. Some of the conversions are not only because Space was completely changed but because the new Space is going into a MARE software instead of MUSE. There are similiarities between those two but not completely.

## Terminology changes from SpaceMUSE to MARE:Space

* Linear Position -> Pos
* Linear Velocity -> Vel
* Linear Accel -> Acc
* Heading -> Attitude Pos (this is not 'altitude')
* Angular Vel -> Attitude Vel
* Angular Accel -> Attitude Acc
* Anything X, Y, Z are collectively known as a Vector or Position
* Any angles listed as X, Y, Z -> Yaw, Pitch, Roll (as known as Euler's)
* Fleet -> Universe
* Ship -> Space Obj (A real ship is known as a space obj with type Spacecraft)
* Dock/Land -> Station Inside/Land
* Sector -> Space Region (due to Mare 2.0 using Sectors for something else)
See README named 'README.terminology.md' for more info.

## Data Types

* Most attributes are now 3-part space-delimited attributes with X/Y/Z/Yaw/Pitch/Roll as 3 values (example: 1.5 2.37 0.8) instead of 3 attributes
  * All the math functions work on the 3 values together (example: vadd())
* Yaw/Roll/Pitch together are called a Euler datatype
* Angles are shown as degrees instead of radians, conversions happen internally
* Internally, anything yaw/pitch/roll are handled as Quaternions but the attributes are always converted at the last second to Yaw/Pitch/Roll for ease of use
* Radians can still be used by prefixing the values with 'rad '
* Some attributes and return values are listed as key/value pairs with this format: "keyname1=value:keyname2=value2:keyname3=..."
  * A softcode function helps parse this. Soon to be a hardcode one.
* Space Objects have space obj types (Star, Planet, Moon, Smallbody, Spacecraft, ordnance, debris, marker)

## Soft-code Attribute renaming from SpaceMUSE to MARE:Space

* Most of these were slimmed down from 3 separate attributes to 1 attribute with 3 space-delimited values (example: "@pos #365=1.5 2.0 0.37")
* LinposX/Y/Z -> Pos
* LinvelX/Y/Z -> Vel
* LinAccX/Y/Z -> Acc
* AngposX/Y/Z -> Att_Pos
* AngvelX/Y/Z -> Att_Vel
* AngaccX/Y/Z -> Att_Acc
* Thrust -> Main_Burn (N)
* Acceleration -> Acc_Forward (X,Y,Z)
* Sector -> Region
See 'README.softcode.manual.md' for more info.

## Function name conversions

* dg2rd = deg2rad
* rd2deg = rad2deg
* km2au = same
* au2km = same
* km2ps = km2pc
* ps2km = pc2km
* km2ly = same
* ly2km = same
* ks2ls = kms2ls
* ls2ks = ls2kms
* dist3d = vdist or store and parse relstate() for value 'distance'
* head3d = vlookat or store/parse relstation() fro value 'bearing'
* relhead = Store and parse relstate() for value 'orient'
* velhdg = v2e
* velmag = vmag
* relphi = Store and parse relstate() for value 'ApprAngle'
* orbit = Store and parse orbitstate()
* swait = N/A
* sync = N/A
* updates = spupdates
* inrange = sensorlist
* insight = sensorlist
* inspace = inspace
* indist = indist
* face = TBD
* acctime = TBD
* relacc = TBD
* zone2obj = N/A

## Soft-code unchanged attribute names

* Mass
* Radius
* Type

## No Equivilant attributes yet for these

* Rating
* Efficiency
* Fuel
* VisMult
* Recover (obsolete, will never be used)
* Hull
* SprStr
* Pwrgen
* Pwrfuel
* Energy
* S0 through S9
* AShip

## Other notable thing not handled yet

* The ROOM_ZEROG flag from SpaceMUSE is not in MARE:Space
  * There is however the Mare 2.0 idea of Sectors that list Space as a choice.
  * Perhaps a suitable replacement

## Other differences

* Docking -> Station Inside
* Docking / Landing have to pass a lock attribute to do that and have a Station attribute to point to where it went
* Spacecraft never really 'leave the universe' but go to a NullSpace region instead and come back to a StarSystem region when its 'back'
* New 'Mated Station' (attach two spacecraft airlock to airlock)
* Sensors are now handled in the hardcode, with Visual, IR, LIDAR, Gravity Waves. Multiple values are returned when detected
* Space Objs are an object type flag ("S") and have a separate Space Obj type attribute
* Space Objs have no location (inside themselves) and not meant to be owned by regular players and not used as spacecraft rooms / items.
* spacecraft have a '@body' attribute to point to its equivilant Mare object that has a real description and regular attributes / softcode (Type: Thing or Room)

## New softcode attributes in MARE:Space

* Space_ID (closely mirrors NASA JPL NAIF ID's. Every object gets a unique ID)
* Grav (acceleration due to gravity)
* Acc_SC (acceleration in X,Y,Z due to the spacecraft)
* Space_obj_Type (type of space object)
* Space_obj_Type (type of space object)
* Body (points to the thing that people see in docks and other places)
* Linear_Burn (low-powered thrust as newtons along the direction of the spacecraft, linear burn)
* Acc_Forward (total accel km/s^2 along the direction of the spacecraft due to thrust. Main + Burn)
* Att_Acc_Goal (Attitude acceleration goal for spacecraft to get to)
* Att_Vel_Goal (Attitude Velocity goal for spacecraft to get to)
* Att_Pos_Goal (Attitude position goal for spacecraft to get to)
* Att_Control (Is Spacecraft trying to go the pos, vel, or acc goal, or no goal?)
* burn_timer = # of seconds to burn before a automatic cut-off
* main_burn_target = Main burn to use during a timer event
* linear_burn_target = Linear Burn to use during a timer event
* att_burn_timer = # of seconds to burn attitude accel
* att_burn_target = Attitude Accel to use during a timer event

* Relative State variables
  * Rs1Tgt (Target Space object this relate state set is comparing to)
  * Rs2 - 5 (other target slots)
  * relstate(#source,#target) will return a lot of data

* Orbit State variables (os1, os2, os3, os4, os5)
  * os*orbited (Target space object for tracking orbit around)
  * orbitstate() to get data

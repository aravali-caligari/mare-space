# Features List

In summary of the below current features and planned features:

* A very large amount of time was spent ensuring the accuracy of movements, gravity, and rotations, and initial positions of Space objects like Planets and moons
* New data structures and a large list of math functions were made to help give the code a good base to stand on
* Updates were sped up from 10-second updates to 1
* HTML is now a display format
* The ability was made to test functions outside of Mare help verify things quickly without loading up Mare everytime a test is done
* The new Mare code is falling quickly into place since the new code has a good base to start from
* The 'commands' in Mare are going to be very different but there will be attempts to make the Mare functions as compatible as possible. Expect some level of softcode breakage
* This new code is a re-imagining of the original code and does not re-use it

## Features completed

* Suite of math unit functions to perform:
  * Vector / Positional math (24 functions)
  * Rotation math with Quaternions and Euler angles (15 functions)
  * Unit and type conversions (17 functions)
  * Orbital parameter calculations
  * Relative position calculations
* Navigational
  * 1 sec space updates
  * State vector updates (basic navigation)
  * Gravity updates
  * Velocity Verlet gravity integration
  * Attitude control and Thrust
  * Timed thrusts with thrust targets
  * Docking / Landing
  * Attachments between objects or station-keeping (e.g. spacecraft to a spacestation)
  * Launching into space
  * Obey's lightspeed and introducing relativistic effects (i.e. slower accel as velocity goes up)
* Extreme accuracy of
  * Orbital parameters
  * Gravity and Velocity Verlet integration
  * Rotations and Angles using Quaternions instead of Euler angles
  * Starting positions and velocities imported from NASA JPL Ephemeris data
  * Accuracy of the Earth position being within 20km's of NASA's predicted position after 1 year of 31 million second/updates
  * 250+ Space Objects (Planet/Moons/Asteroids) being tracked. Could be tracking hundreds more.
* Data readouts (html and ascii)
  * Orbital parameters
  * Relative space objects
  * Regular space vector, spacecraft
  * Object list by a range of distance and sorted by distance
* Coordinate conversions
  * Degrees to Latitude/Longitude or Right-Ascention and Declination and the reverse
  * Many display formats available and input formats accepted
* Data management structures
  * Quaternions - Internal Rotation data handling (more accurate than regular Euler Angles)
  * Euler - Angles used for displaying to users and/or softcode. Not used for internal calculations
  * Positions - Different than vectors
  * Vectors - Commonly used for velocities and accelerations and other relative numbers
  * State Vector - Used to track Space obj pos/vel/acc/rotations
  * Space Obj - Contains all data about a planet/moon/asteroid/spacecraft/more
  * Relative state - (compares one Space Obj to another to give relative pos/rotations/velocities/etc)
  * Orbit State - Tracks Orbital element data of a Space Obj orbiting another Space Obj
  * Distant Obj - Tracks Space Objs within a distance from another, in distance order
  * Space Region - Most of the time a region = star system but other types exist like Interstellar and FTL spaces
* MARE Softcode functions
  * Conversions of distances
  * Conversions of Coordinates (HMS or Deg Min Sec) to/from Angles
  * Vector math
  * Rotational math
  * attitude
  * sensor lists and detailed info
  * navigational math
* Testing
  * Off-line command line test suit to test all the internal functions without Mare running
* Sensory
  * Detect which space obj's can be seen visually
    * telescope sizes and magnitude limits
    * detailed visual info
    * Handle large objects hiding smaller objects behind them or partial eclipses
    * handling of how 'full' a space obj looks based on angles of the observer, target, and Sun (i.e. full moon, new moon, partial moon)
  * Sensor info
  * Transponders
* HTML display of
  * Space objects
  * State vectors
  * Orbital parameters
  * Relative state
  * Dynamic display of changing values for a period of time
  * Sensor info
* Automatically updating relative states and orbit states for a spaceobj based on a maintained target list (up to 3 targets)
* Detailed display of space obj attributes in 'examine' command
* Individual space attributes for spaceobj, statevector, relative states, orbit states

## Planned features for future

* Sensory
  * Infrared
  * radar
  * Stealth effects
  * Brighter objects based on thrust
  * Sensory softcode events (like we just detected something)
* Navigational
  * Tracking of fuel and engine efficency
  * Solar panels
  * Collision checks
  * Determining what side of a planet/moon/asteriod a spacecraft is 'over'
  * FTL travel
  * Transition between Interstellar and star systems
  * Orbit-related math functions (e.g. escape velocity, circular orbit vel, etc)
  * auto-pilot of spacecraft orientation changes (i.e. swing to this direction)
  * advanced navigational math (e.g. intercepts)
* Communications
  * Sending and receiving of messages
* Combat
  * Concept of 'Hull' strength and shields
  * Missile space obj's
  * Lasers
  * Slugs
  * Damaging of spacecraft
  * Exploding

/*  Mark William Wilkinson <mark@towerravens.com>
	 MUSE-Space, Copyright (C) 1992, 1993, All rights reserved.
    See space.h for additional copyright information.
	 Version 1.1, 26 November 1994.
 */

/* Standard '/usr/include' header files. */
#include <stdlib.h>
#include <stdio.h>
#include <fcntl.h>
#include <time.h>
#include <math.h>
#include <ctype.h> /* for isdigit() */

/* Muse 'src/hdrs' header files. */
#include "externs.h"
#include "config.h"
#include "space.h"
#include "db.h"

/*  Shortened names for constants defined in space.h.  */
#define UPDATE SPACE_INTERVAL  /*  Frequency of position updates.  */
#define SHIPS (MAX_SHIPS + 1)  /*  Max number of objects permitted in space. */
#define BEACON MAX_DIST  /*  Max dist in km before a ship is lost.  */

/* The mass below _was_ 1.592E29 but it turns out Wolf-359's
	mass is 3.96E28, so I changed it to work. -Majere */
#define STARMASS 3.00E28   /* Mass of the smallest star in struct. */

/*  Universal Constants.  */
#define PI 3.141592654     /*  Units in radians.  */
#define GRAV 6.67E-20      /*  Units in (km^3)/(s^2)*(kg).  */
#define C 2.999977454E5    /*  Speed of light in km/ps. */
#define LY (C * 3.1536E7)  /*  Light Year in kms. */
#define AU 1.50E8          /*  Astronomical Unit in kms.  */
#define PS 206264.8062     /*  Parsec in AUs.  */

/*  Structure for any object in space including starships,
	 moons, planets, stars, etc.  */
struct ship
{
	dbref obj;                /*  Database object number.  */
	struct ref sect;          /*  Name of sector (closest star).  */
	double mass;              /*  Units in kilograms.  */
	double radius;            /*  Units in kilometers (not for ships).  */
	double thrust;            /*  Units in newtons.  */
	double rating;            /*  Engine rating in newtons.  */
	double effcny;            /*  Engine efficiency.  Percentage.  */
	double fuel;              /*  Units not yet determined (Kmols?).  */
	double accel;             /*  Units in kilometers per update update.  */
	struct coords location;   /*  Units in kilometers.  */
	struct coords oldloc;     /*  Units in kilometers.  */
	struct coords linvel;     /*  Units in kilometers per update.  */
	struct coords linaccl;    /*  Units in kilometers per update update.  */
	struct coords heading;    /*  Units in radians.  */
	struct coords angvel;     /*  Units in radians per update */
	struct coords angaccl;    /*  Units in radians per update update.  */
	int superst;              /*  Superstructure; indeterminate units.  */
	int hull;                 /*  Hull strength for penetration.  */
	int s_nav;                /*  Shielding: Navigational.  */
	int s_bsd;                /*  Shielding: Bow-Starboard-Deck.  */
	int s_bsk;                /*  Shielding: Bow-Starboard-Keel.  */
	int s_bpd;                /*  Shielding: Bow-Port-Deck.  */
	int s_bpk;                /*  Shielding: Bow-Port-Keel.  */
	int s_asd;                /*  Shielding: Aft-Starboard-Deck.  */
	int s_ask;                /*  Shielding: Aft-Starboard-Keel.  */
	int s_apd;                /*  Shielding: Aft-Port-Deck.  */
	int s_apk;                /*  Shielding: Aft-Port-Keel.  */
	int o_att;                /*  Object attachment.  */
	int checked;              /*  To avoid double crashing. */
	int exploding;            /*  To avoid recursive explosions */
	int vismult;              /*  Multiplier for visibility.  */
	long pwrgen;              /*  Power currently in generator.  */
	long pwrfuel;             /*  Ammount of fuel feed to generator.  */
	long energy;              /*  Total detectable energy output.  */
	int tractor;              /*  Object that has ship in tractor. */
	double artf_g;             /*  Artificial Gravity on ship. */
	char dark[320];           /*  Dark attribute for recovery info.  */
};

/*  Declaration of ship array.  */
struct ship fleet[SHIPS];

/*  Structure for output file.  */
struct log space_log = { NULL, -1, "logs/space", "*log_space"};

/*  >> Internal Prototypes. <<  */

/*  Functions for management of ship array.  */
void clear_fleet P((void));
int check_fleet P((void));
int count_fleet P((void));
void list_fleet P((char *));
int init_ship P((dbref));
void del_ship P((dbref));
int read_ship P((dbref, int));
void read_manvr P((int));
void write_ship P((int));
void dump_space P((void));
int init_space P((void));
void update_space P((void));
int find_ship P((dbref));
int find_sect P((int));
/*  Utilities for data management.  */
char *ftoa P((double, int));
double deg2rad P((double));
double rad2deg P((double));
double km2au P((double));
double au2km P((double));
double km2psec P((double));
double psec2km P((double));
double km2ly P((double));
double ly2km P((double));
double ks2ls P((double));
double ls2ks P((double));
double distance2 P((struct coords, struct coords));
double distance3 P((struct coords, struct coords));
struct coords vect_diff P((struct coords, struct coords));
double vect_mag P((struct coords));
struct coords vect_cross P((struct coords, struct coords));
double linept_dist P((struct coords, struct coords, struct coords));
struct coords abs_heading P((struct coords, struct coords));
struct coords rel_heading P((struct ship *, struct coords));
/*  Functions for combat simulation.  */
void damage_ship P((int, int, int, int));
int shield_hit P((int, struct coords, int));
int face_d6 P((int, struct coords));
int face_d8 P((int, struct coords));
void planet_error P((int, int));
void explode P((int));
void gen_power P((struct ship *));
/*  Functions for user interface.  */
void sense_sweep P((dbref, char *));
void vis_range P((dbref, char *, double));
void line_of_sight P((int, int *, int));
void dist_check P((dbref, double, char *));
/*  Functions for Astrodynamics.  */
void grav_attr P((struct ship *, struct ship *, double));
void maneuver P((int));
void check_collision P((int, int));
void hyperspace P((dbref));
int checkdock P((int, int, int));
int isfloat P((char *));
/*  Carrie Gram's functions.  */
double relvelangle P((struct coords, struct coords));
void orbit P((char *, double, double, double, double));

/*  Clears the db object reference number, which is used to determine if a
	 ship is active, of all ship structures from the fleet array.  */
void clear_fleet (void)
{
	int count;
	for (count = 0; count < SHIPS; ++count)
		fleet[count].obj = NOTHING;
}

/*  Check to see if adding the ship structure to the fleet array will
	 exceed the maximum number of ships allowed.  Will return a positive
	 integer for an array element which is open.   */
int check_fleet (void)
{
	int count;
	/*  Find an empty location by checking all elements, low to high.  */
	for (count = 0; count < SHIPS; ++count)
		if (fleet[count].obj == NOTHING)
			break;
	return (count == SHIPS) ? -1 : count;
}

/*  Count the number of objects in the ship structure.  */
int count_fleet (void)
{
	int count;
	int total;
	total = 0;
	for (count = 0; count < SHIPS; ++count)
		if (fleet[count].obj != NOTHING)
			++total;
	return (total);
}

/*  Fills a string with the db reference number of all the objects
	 currently in the ship array.  */
void list_fleet (ship_str)
	char *ship_str;
{
	int count;
	*ship_str = '\0';
	for (count=0; count < SHIPS; ++count)
		if (fleet[count].obj != NOTHING) {
			sprintf(ship_str,"%s(#%d) ",db[fleet[count].obj].name,fleet[count].obj);
			ship_str += strlen(ship_str);
		}
}
/*  Initialize a new ship.  Gets an array position from check_fleet() and
	 inserts the new ship into that position by calling read_ship().  */
int init_ship (obj)
	dbref obj;
{
	int ship_num;
	ship_num = check_fleet();
	if (ship_num >= 0)
		return read_ship(obj, ship_num);
	else
		return 0;
}

/*  Deletes a ship from the fleet array by specifying the db reference
	 number.  The ship is removed simply by searching for that number and
	 replacing it with NOTHING.  */
void del_ship (obj)
	dbref obj;
{
	int count;
	for (count = 0; count < SHIPS; ++count)
		if (fleet[count].obj == obj)
			fleet[count].obj = NOTHING;
}

/*  Read a new ship into the array.  It is requsite to have the ships db
	 reference number and an integer specifying the array location to use.  */
int read_ship (obj, ship_num)
	dbref obj;
	int ship_num;
{
	char *tmpstr;
	int goodship = 1;
	struct ship *new;
	new = &fleet[ship_num];
	new->obj = obj;
	new->exploding = 0;
	strncpy(new->sect.name, atr_get(obj, A_SECTOR),11);
	strncpy(new->dark, atr_get(obj, A_RECOVER),300);

	/* In this bit of code we extract the values from the muse database for
   the ship object in question. If the string returned will not make a happy
	float value then we set goodship to 0 and return that. However, in the
	case of the linpos and linvel values we set goodship to -1 because we
	want init_space to still load the values (because lin data is overwritten
	from the 'recover' attribute). -PA */

	new->mass = (isfloat((tmpstr = atr_get(obj, A_MASS))) ? atof(tmpstr) : (goodship = 0));
	new->radius = (isfloat((tmpstr = atr_get(obj, A_RADIUS))) ? atof(tmpstr) : (goodship = 0));
	new->thrust = (isfloat((tmpstr = atr_get(obj, A_THRUST))) ? atof(tmpstr) : (goodship = 0));
	new->rating = (isfloat((tmpstr = atr_get(obj, A_RATING))) ? atof(tmpstr) : (goodship = 0));
	new->effcny = (isfloat((tmpstr = atr_get(obj, A_EFFICIENCY))) ? atof(tmpstr) : (goodship = 0));
	new->fuel = (isfloat((tmpstr = atr_get(obj, A_FUEL))) ? atof(tmpstr) : (goodship = 0));
	new->accel = (isfloat((tmpstr = atr_get(obj, A_ACCELERATION))) ? atof(tmpstr) : (goodship = 0));
	new->location.x = (isfloat((tmpstr = atr_get(obj, A_LINPOSX))) ? atof(tmpstr) : (goodship = -1));
	new->location.y = (isfloat((tmpstr = atr_get(obj, A_LINPOSY))) ? atof(tmpstr) : (goodship = -1));
	new->location.z = (isfloat((tmpstr = atr_get(obj, A_LINPOSZ))) ? atof(tmpstr) : (goodship = -1));
	new->linvel.x = (isfloat((tmpstr = atr_get(obj, A_LINVELX))) ? atof(tmpstr) : (goodship = -1));
	new->linvel.y = (isfloat((tmpstr = atr_get(obj, A_LINVELY))) ? atof(tmpstr) : (goodship = -1));
	new->linvel.z = (isfloat((tmpstr = atr_get(obj, A_LINVELZ))) ? atof(tmpstr) : (goodship = -1));
	new->linaccl.x = (isfloat((tmpstr = atr_get(obj, A_LINACCX))) ? atof(tmpstr) : (goodship = 0));
	new->linaccl.y = (isfloat((tmpstr = atr_get(obj, A_LINACCY))) ? atof(tmpstr) : (goodship = 0));
	new->linaccl.z = (isfloat((tmpstr = atr_get(obj, A_LINACCZ))) ? atof(tmpstr) : (goodship = 0));
	new->heading.x = (isfloat((tmpstr = atr_get(obj, A_ANGPOSX))) ? deg2rad(atof(tmpstr)) : (goodship = 0));
	new->heading.y = (isfloat((tmpstr = atr_get(obj, A_ANGPOSY))) ? deg2rad(atof(tmpstr)) : (goodship = 0));
	new->heading.z = (isfloat((tmpstr = atr_get(obj, A_ANGPOSZ))) ? deg2rad(atof(tmpstr)) : (goodship = 0));
	new->angaccl.x = (isfloat((tmpstr = atr_get(obj, A_ANGACCX))) ? deg2rad(atof(tmpstr)) : (goodship = 0));
	new->angaccl.y = (isfloat((tmpstr = atr_get(obj, A_ANGACCY))) ? deg2rad(atof(tmpstr)) : (goodship = 0));
	new->angaccl.z = (isfloat((tmpstr = atr_get(obj, A_ANGACCZ))) ? deg2rad(atof(tmpstr)) : (goodship = 0));
	new->superst = (isfloat((tmpstr = atr_get(obj, A_SPRSTR))) ? atof(tmpstr) : (goodship = 0));
	new->hull = (isfloat((tmpstr = atr_get(obj, A_HULL))) ? atof(tmpstr) : (goodship = 0));
	new->s_nav = (isfloat((tmpstr = atr_get(obj, A_S0))) ? atof(tmpstr) : (goodship = 0));
	new->s_bsd = (isfloat((tmpstr = atr_get(obj, A_S1))) ? atof(tmpstr) : (goodship = 0));
	new->s_bsk = (isfloat((tmpstr = atr_get(obj, A_S2))) ? atof(tmpstr) : (goodship = 0));
	new->s_bpd = (isfloat((tmpstr = atr_get(obj, A_S3))) ? atof(tmpstr) : (goodship = 0));
	new->s_bpk = (isfloat((tmpstr = atr_get(obj, A_S4))) ? atof(tmpstr) : (goodship = 0));
	new->s_asd = (isfloat((tmpstr = atr_get(obj, A_S5))) ? atof(tmpstr) : (goodship = 0));
	new->s_ask = (isfloat((tmpstr = atr_get(obj, A_S6))) ? atof(tmpstr) : (goodship = 0));
	new->s_apd = (isfloat((tmpstr = atr_get(obj, A_S7))) ? atof(tmpstr) : (goodship = 0));
	new->s_apk = (isfloat((tmpstr = atr_get(obj, A_S8))) ? atof(tmpstr) : (goodship = 0));
	new->o_att = (isfloat((tmpstr = atr_get(obj, A_S9))) ? atof(tmpstr) : (goodship = 0));
	new->pwrgen = (isfloat((tmpstr = atr_get(obj, A_PWRGEN))) ? atof(tmpstr) : (goodship = 0));
	new->pwrfuel = (isfloat((tmpstr = atr_get(obj, A_PWRFUEL))) ? atof(tmpstr) : (goodship = 0));
	new->vismult = (isfloat((tmpstr = atr_get(obj, A_VISMULT))) ? atof(tmpstr) : (goodship = 0));
	new->checked = NULL;
	new->sect.nebu = NULL;
	new->tractor = NULL;
	/*  strip = (char)atr_get(obj, A_S9);
		 new->o_att = strtol(*strip[1], NULL, 10); */
	/*  sscanf(atr_get(obj, A_S9), "%#c%d", &new->o_att); */

	return goodship;
}

/*  Read a ship's maneuver into the array.  The only required input is the
	 array number for the ship.  */
void read_manvr (ship_num)
	int ship_num;
{
	dbref obj;
	char *tmpstr;
	struct ship *new;
	new = &fleet[ship_num];
	obj = new->obj;
	strncpy(new->sect.name, atr_get(obj, A_SECTOR),11);

	/* Check to make sure the attributes contain a valid number before adding
	the value to the fleet struct. If not, keep the value the same. */
	new->thrust = (isfloat((tmpstr = atr_get(obj, A_THRUST))) ? atof(tmpstr) : new->thrust);
	new->rating = (isfloat((tmpstr = atr_get(obj, A_RATING))) ? atof(tmpstr) : new->rating);
	new->effcny = (isfloat((tmpstr = atr_get(obj, A_EFFICIENCY))) ? atof(tmpstr) : new->effcny);
	new->fuel = (isfloat((tmpstr = atr_get(obj, A_FUEL))) ? atof(tmpstr) : new->fuel);
	new->linaccl.x = (isfloat((tmpstr = atr_get(obj, A_LINACCX))) ? atof(tmpstr) : new->linaccl.x);
	new->linaccl.y = (isfloat((tmpstr = atr_get(obj, A_LINACCY))) ? atof(tmpstr) : new->linaccl.y);
	new->linaccl.z = (isfloat((tmpstr = atr_get(obj, A_LINACCZ))) ? atof(tmpstr) : new->linaccl.z);
	new->angaccl.x = (isfloat((tmpstr = atr_get(obj, A_ANGACCX))) ? deg2rad(atof(tmpstr)) : new->angaccl.x);
	new->angaccl.y = (isfloat((tmpstr = atr_get(obj, A_ANGACCY))) ? deg2rad(atof(tmpstr)) : new->angaccl.y);
	new->angaccl.z = (isfloat((tmpstr = atr_get(obj, A_ANGACCZ))) ? deg2rad(atof(tmpstr)) : new->angaccl.z);
	new->pwrgen = (isfloat((tmpstr = atr_get(obj, A_PWRGEN))) ? atof(tmpstr) : new->pwrgen);
	new->pwrfuel = (isfloat((tmpstr = atr_get(obj, A_PWRFUEL))) ? atof(tmpstr) : new->pwrfuel);
	new->vismult = (isfloat((tmpstr = atr_get(obj, A_VISMULT))) ? atof(tmpstr) : new->vismult);
}

/*  Write data to the data base.  The only required input is the array
	 number of the ship.  */
void write_ship (ship_num)
	int ship_num;
{
	dbref obj;
	struct ship *out;
	struct coords centre;
	float becrand;      /*  Random number for becon effective distance.  */
	out = &fleet[ship_num];
	obj = out->obj;
	centre.x = 0.0; centre.y = 0.0; centre.z = 0.0;
	atr_add(obj, A_SECTOR, out->sect.name);
	atr_add(obj, A_FUEL, ftoa(out->fuel, 1));
	atr_add(obj, A_ACCELERATION, ftoa(out->accel, 3));
	becrand = (float)rand()/32767.0;
	
	/* Getting rid of the beacon for now. Stars that are too far out
	are 'lost', and ships in those systems also have no way of knowing
	what their positions are. -MM (11/04/04)
	if (!In_Hspace(ship_num) && (distance3(centre, out->location) <
				(becrand*BEACON*0.05) + BEACON)) */
	if (!In_Hspace(ship_num))
	{
		atr_add(obj, A_LINPOSX, ftoa(out->location.x, 1));
		atr_add(obj, A_LINPOSY, ftoa(out->location.y, 1));
		atr_add(obj, A_LINPOSZ, ftoa(out->location.z, 1));
		atr_add(obj, A_LINVELX, ftoa(out->linvel.x, 3));
		atr_add(obj, A_LINVELY, ftoa(out->linvel.y, 3));
		atr_add(obj, A_LINVELZ, ftoa(out->linvel.z, 3));
	}
	else
	{
		atr_add(obj, A_LINPOSX, "                ?");
		atr_add(obj, A_LINPOSY, "                ?");
		atr_add(obj, A_LINPOSZ, "                ?");
		atr_add(obj, A_LINVELX, "            ?");
		atr_add(obj, A_LINVELY, "            ?");
		atr_add(obj, A_LINVELZ, "            ?");
	}
	atr_add(obj, A_LINACCX, ftoa(out->linaccl.x, 5));
	atr_add(obj, A_LINACCY, ftoa(out->linaccl.y, 5));
	atr_add(obj, A_LINACCZ, ftoa(out->linaccl.z, 5));
	atr_add(obj, A_ANGPOSX, ftoa(out->heading.x, 2));
	atr_add(obj, A_ANGPOSY, ftoa(out->heading.y, 2));
	atr_add(obj, A_ANGPOSZ, ftoa(out->heading.z, 2));
	atr_add(obj, A_ANGVELX, ftoa(out->angvel.x, 2));
	atr_add(obj, A_ANGVELY, ftoa(out->angvel.y, 2));
	atr_add(obj, A_ANGVELZ, ftoa(out->angvel.z, 2));
	atr_add(obj, A_ANGACCX, ftoa(out->angaccl.x, 2));
	atr_add(obj, A_ANGACCY, ftoa(out->angaccl.y, 2));
	atr_add(obj, A_ANGACCZ, ftoa(out->angaccl.z, 2));
	atr_add(obj, A_PWRGEN, ftoa(out->pwrgen, 3));
	atr_add(obj, A_ENERGY, ftoa(out->energy, 3));
}

/*  Fills all ships with data pertenent to their recovery after a
	 shutdown.  This funciton is externally called.  This data is
	 preserved to its last significant digit.  */
void dump_space ()
{
	int count;
	dbref obj;
	if (update_count)
		atr_add(SPACE_LORD, A_RECOVER, int_to_str(update_count));
	for (count=0; count < SHIPS; ++count)
		if (fleet[count].obj != NOTHING)
		{
			obj = fleet[count].obj;
			fleet[count].dark[0] = '\0';
			sprintf(fleet[count].dark, "%f %f %f %f %f %f",
					fleet[count].location.x, fleet[count].location.y,
					fleet[count].location.z, fleet[count].linvel.x,
					fleet[count].linvel.y, fleet[count].linvel.z);
			atr_add(obj, A_RECOVER, fleet[count].dark);
		}
}

/*  Function initializes space objects by clearing the array and loading
	 it with the objects found in space.  */
int init_space (void)
{
	dbref space_room, current;
	int count;

	clear_fleet();
	space_count = 1;

	update_count=atol(atr_get(SPACE_LORD, A_RECOVER));

	for (space_room = 0; space_room < db_top; space_room++)
	{
		if IS(space_room,TYPE_ROOM,ROOM_ZEROG)
			for(current = db[space_room].contents; current != NOTHING;
					current = db[current].next)
				if Ship(current)
				{
					/* Fail out if we hit a ship with bad attribute data */
					if (init_ship(current) == 0)
					{
						log_space(tprintf("Bad attribute data in ship #%d, space not started.", current));
						halt_space = 0;
						clear_fleet();
						return 0;
					}

					/*  Read in dark attributes to overwrite null position.  */
					for (count = 0; count < SHIPS; ++count)
						if (fleet[count].obj == current)
						{
							char temp[300];
							strcpy(temp, atr_get(current, A_RECOVER));

							/* Fail out if we hit a ship with bad recover data */
							if (!isfloat(temp))
							{
								log_space(tprintf("Bad recover data in ship #%d, space not started.", current));
								halt_space = 0;
								clear_fleet();
								return 0;
							}

							sscanf(temp, "%lf %lf %lf %lf %lf %lf",
									&fleet[count].location.x, &fleet[count].location.y,
									&fleet[count].location.z, &fleet[count].linvel.x,
									&fleet[count].linvel.y,   &fleet[count].linvel.z);
						}
				}
	}
	/* Fill in the sector number for each ship/planet. */
	for (count = 0; count < SHIPS; ++count)
		fleet[count].sect.numb = find_sect(count);

return 1;
}

/*  Function updates the position of all space objects.  */
void update_space(void)
{
	int count,count2;
	update_count++;
	/*  Read in all ship maneuvers.  */
	for (count = 0; count < SHIPS; ++count)
		if ((fleet[count].obj != NOTHING) && (fleet[count].mass < 1E8))
			read_manvr(count);
	/*  Maneuver each ship.  */
	for (count = 0; count < SHIPS; ++count)
		if (fleet[count].obj != NOTHING)
			maneuver(count);
	/*  Check for Collisions */
	for (count = 0; count < SHIPS; ++count)
		if (fleet[count].obj != NOTHING)
			for (count2 = count+1;count2 < SHIPS; ++count2)
				if (fleet[count2].obj != NOTHING) {
					if (fleet[count].checked == count2)
						fleet[count].checked = NULL;
					else
						check_collision(count,count2);
				}
	/*  Write all ships to db.  */
	for (count = 0; count < SHIPS; ++count)
		if (fleet[count].obj != NOTHING) {
			fleet[count].checked = NULL;
			write_ship(count);
		}
}

/* Function takes ship dbref # and finds the ship struct #. */
/* NOTE - Usage syntax: if (ship = find_ship(obj)) */
int find_ship (ship)
	dbref ship;
{
	int count;
	for (count = 0; count < SHIPS; ++count)
		if (ship == fleet[count].obj)
			return (count);
	return -1;
}

/*  Function finds the sector fleet number for all ships. */
int find_sect(ship)
	int ship;
{
	int count;
	if(fleet[ship].obj == NOTHING)
		return(NULL);

	if(!strcmp(fleet[ship].sect.name,"IS") ||
			!strcmp(fleet[ship].sect.name,"HS"))
		return(NULL);
	for (count = 0; count < SHIPS; ++count) {
		/* lines added 5/26/99 dba (also added {} around enclosing 'for') */
		if (fleet[count].obj == NOTHING)
			return(count);
		/* end lines added 5/26/99 dba */
		if(!strcmp(fleet[ship].sect.name,
					db[fleet[count].obj].name))
			return(count);
	}

	return(NULL);
}

/*  Utility for converting doubles to strings.  The second parameter
	 determines what format the float takes (No Format 0; Linear Varialbes
	 1,3,4; Angular Variables 2, Type int Variables 6).  */
char *ftoa (double flt, int formt)
{
	static char buf[30];
	switch(formt) {
		case 1:
			sprintf(buf, "%17.0f", flt);
			break;
		case 2:
			sprintf(buf, "%6.3f", rad2deg(flt));
			break;
		case 3:
			sprintf(buf, "%13.2f", flt);
			break;
		case 4:
			sprintf(buf, "%6.0f", flt);
			break;
		case 5:
			sprintf(buf, "%6.3f", flt);
			break;
		case 6:
			sprintf(buf, "%d", (int) flt);
			break;
		default:
			sprintf(buf, "%f", flt);
	}
	return buf;
}

/*  Converts degrees to radians.  */
double deg2rad (degrees)
	double degrees;
{
	double temp;
	temp = degrees * PI / 180.0;
	return (temp);
}
/*  Converts radians to degrees.  */
double rad2deg (radians)
	double radians;
{
	double temp;
	temp = radians * 180.0 / PI;
	return (temp);
}

/*  Converts kilometers to astronomical units.  */
double km2au (kmeter)
	double kmeter;
{
	double temp;
	temp = kmeter / AU;
	return (temp);
}
/*  Converts astronomical units to kilometers.  */
double au2km (aunits)
	double aunits;
{
	double temp;
	temp = aunits * AU;
	return (temp);
}

/*  Converts kilometers to parsecs.  */
double km2psec (kmeter)
	double kmeter;
{
	double temp;
	temp = km2au(kmeter) / PS;
	return (temp);
}

/*  Converts parsecs to kilometers.  */
double psec2km (parsec)
	double parsec;
{
	double temp;
	temp = au2km(parsec * PS);
	return (temp);
}

/*  Converts kilometers to light-years.  */
double km2ly (kmeter)
	double kmeter;
{
	double temp;
	temp = kmeter / LY;
	return (temp);
}

/*  Coverts light-years to kilometers.  */
double ly2km (lyear)
	double lyear;
{
	double temp;
	temp = lyear * LY;
	return (temp);
}

/*  Coverts kilometers per second to light speed.  */
double ks2ls (kps)
	double kps;
{
	double temp;
	temp = kps / (C * UPDATE);
	return (temp);
}

/*  Coverts light speed to kilometers per second.  */
double ls2ks (lspeed)
	double lspeed;
{
	double temp;
	temp = lspeed * (C * UPDATE);
	return (temp);
}

/*  Calculates the 2D distance between two 3D points in the
	 XY plane.  */
double distance2 (pt1, pt2)
	struct coords pt1;
	struct coords pt2;
{
	double temp;
	temp = sqrt((pt1.x-pt2.x)*(pt1.x-pt2.x)+(pt1.y-pt2.y)*(pt1.y-pt2.y));
	return (temp);
}

/*  Calculates the 3D distance between two 3D points in
	 XYZ space.  */
double distance3 (pt1, pt2)
	struct coords pt1;
	struct coords pt2;
{
	double temp;
	temp = sqrt((pt1.x-pt2.x)*(pt1.x-pt2.x)+(pt1.y-pt2.y)*(pt1.y-pt2.y)+
			(pt1.z-pt2.z)*(pt1.z-pt2.z));
	return (temp);
}

/*  Calculates the difference of two vectors.  */
struct coords vect_diff (vect1, vect2)
	struct coords vect1;
	struct coords vect2;
{
	struct coords temp;
	temp.x = vect1.x - vect2.x;
	temp.y = vect1.y - vect2.y;
	temp.z = vect1.z - vect2.z;
	return (temp);
}

/*  Calculates the magnitude of a vector.  */
double vect_mag (vect)
	struct coords vect;
{
	double temp;
	temp = sqrt((vect.x * vect.x) + (vect.y * vect.y) + (vect.z * vect.z));
	return (temp);
}

/*  Calculate the cross product of two vectors.  */
struct coords vect_cross (vect1,vect2)
	struct coords vect1;
	struct coords vect2;
{
	struct coords temp;
	temp.x = (vect1.y * vect2.z) - (vect1.z * vect2.y);
	temp.y = (vect1.z * vect2.x) - (vect1.x * vect2.z);
	temp.z = (vect1.x * vect2.y) - (vect1.y * vect2.x);
	return (temp);
}

/*  Calculates the distance between a line and a point.
	 The variables are:  pt1, beginning point of line; pt2,
	 end point of line; pt3, point in space to which distance
	 is desired.  */
double linept_dist (pt1, pt2, pt3)
	struct coords pt1;  /*  Line endpoint.  */
	struct coords pt2;  /*  Line endpoint.  */
	struct coords pt3;  /*  Point to determine distance.  */
{
	struct coords sip2pp;
	/*  Ship initial position to planet position vector.  */
	struct coords sip2sfp;
	/*  Ship initial position to ship final position vector.  */
	struct coords xprod;
	/*  Vector cross product (sip2pp x sip2sfp).  */
	double dist;  /*  Distance between line and point.  */
	sip2pp = vect_diff(pt3,pt1);
	sip2sfp = vect_diff(pt2,pt1);
	if (vect_mag(sip2sfp) != 0)
	{
		xprod = vect_cross(sip2pp,sip2sfp);
		dist = (vect_mag(xprod)/vect_mag(sip2sfp));
	}
	else
		dist = distance3(pt1,pt3);
	return (dist);
}

/*  Determines the instantaneous constant yaw and pitch needed to move
	 toward another position.  Instantaneous means that velocitiy and
	 acceleration of the two objects is assumed to be zero.  */
struct coords abs_heading (pt1, pt2)
	struct coords pt1;
	struct coords pt2;
{
	struct coords diff;   /*  Difference in linear location.  */
	struct coords head;   /*  Storage location for heading.  */
	double dist2;  /*  Distance in XY plane between points.  */
	double ratio;
	/*  Determine yaw to destination.  */
	diff.x = pt2.x - pt1.x;
	diff.y = pt2.y - pt1.y;
	diff.z = pt2.z - pt1.z;
	dist2 = distance2(pt1, pt2);
	if (dist2 != 0.0)
	{
		ratio = diff.x/dist2;
		if (ratio > 1.0)
			ratio = 1.0;
		else if (ratio < -1.0)
			ratio = -1.0;
		head.x = acos(ratio);
	}
	else
		head.x = 0.0;
	if (diff.y < 0)
		head.x = 2*PI - head.x;
	/*  Determine pitch to destination.  */
	if (dist2 != 0.0)
		head.y = atan(diff.z/dist2);
	else
	{
		if (diff.z > 0.0)
			head.y = PI/2;
		else if (diff.z < 0.0)
			head.y = -1.0*PI/2;
		else
			head.y = 0.0;
	}
	/*  Roll to destination is not applicable.  */
	head.z = 0.0;
	return (head);
}

/*  Determines the relative heading from a ship to a destination.
	 The function calcualtes the absolute heading and adjusts this
	 information based on the ship's attitude.  */
struct coords rel_heading (ref, pt)
	struct ship *ref;  /*  Ship from which heading is referenced.  */
	struct coords pt;  /*  Destination of heading.  */
{
	struct coords head;    /*  Return value for relative heading.  */
	struct coords abshdg;  /*  Absolute heading to destination.  */
	struct coords centre;  /*  Center point 0,0,0.  */
	double tmpang = 0.0;   /*  View angle assuming ship at 0 roll.  */
	double tmpmag;         /*  View magnitude assuming ship 0 roll and
										distance between view center and target.  */
	double ratio;
	centre.x = 0.0; centre.y = 0.0; centre.z = 0.0;
	abshdg = abs_heading(ref->location, pt);
	head.y = ref->heading.y - abshdg.y;
	while (head.y < 0)
		head.y += 2*PI;
	while (head.y >=2*PI)
		head.y -= 2*PI;
	head.x = ref->heading.x - abshdg.x;
	if (head.y > PI)
	{
		head.y -= PI;
		head.x += PI;
	}
	while (head.x >= 2*PI)
		head.x -= 2*PI;
	while (head.x < 0)
		head.x += 2*PI;
	head.z = 0.0;
	/*  Recalculate yaw and pitch considering roll.  */
	tmpmag = distance2(centre, head);
	if (tmpmag != 0.0)
	{
		ratio = head.x/tmpmag;
		if (ratio > 1.0)
			ratio = 1.0;
		else if (ratio < -1.0)
			ratio = -1.0;
		tmpang = acos(ratio);
	}
	tmpang += ref->heading.z;
	head.x = tmpmag * cos(tmpang);
	head.y = tmpmag * sin(tmpang);
	head.z = 0;
	return(head);
}

/*  Damages a ship.  Must be passed the fleet number, active
	 shields, amount of damage, and ship of the source of damage.
	 Sufficient damage will remove the ship from  space.  */
void damage_ship (shipnum, shields, damage, source)
	int shipnum;
	int shields;
	int damage;
	int source;
{
	struct ship *vict;
	struct coords rel,abs;
	double tot,amt;
	char t[10];
	int sstatus;
	vict = &fleet[shipnum];
	if(vict->obj==NOTHING)
		return;
	vict->checked = source;
	for (;;) {
		sstatus=0;
		if (vict->s_nav) {
			if (damage >= vict->s_nav) {
				damage -= vict->s_nav;
				vict->s_nav = 0;
				sstatus++;
			} else {
				vict->s_nav -= damage;
				break;
			}
		}
		if ((shields & 1) && (vict->s_bsd)) {
			if (damage >= vict->s_bsd) {
				damage -= vict->s_bsd;
				vict->s_bsd = 0;
				sstatus++;
			} else {
				vict->s_bsd -= damage;
				damage = 0;
				break;
			}
		}
		if ((shields & 2) && (vict->s_bsk)) {
			if (damage >= vict->s_bsk) {
				damage -= vict->s_bsk;
				vict->s_bsk = 0;
				sstatus++;
			} else {
				vict->s_bsk -= damage;
				damage = 0;
				break;
			}
		}
		if ((shields & 4) && (vict->s_bpd)) {
			if (damage >= vict->s_bpd) {
				damage -= vict->s_bpd;
				vict->s_bpd = 0;
				sstatus++;
			} else {
				vict->s_bpd -= damage;
				damage = 0;
				break;
			}
		}
		if ((shields & 8) && (vict->s_bpk)) {
			if (damage >= vict->s_bpk) {
				damage -= vict->s_bpk;
				vict->s_bpk = 0;
				sstatus++;
			} else {
				vict->s_bpk -= damage;
				damage = 0;
				break;
			}
		}
		if ((shields & 16) && (vict->s_asd)) {
			if (damage >= vict->s_asd) {
				damage -= vict->s_asd;
				vict->s_asd = 0;
				sstatus++;
			} else {
				vict->s_asd -= damage;
				damage = 0;
				break;
			}
		}
		if ((shields & 32) && (vict->s_ask)) {
			if (damage >= vict->s_ask) {
				damage -= vict->s_ask;
				vict->s_ask = 0;
				sstatus++;
			} else {
				vict->s_ask -= damage;
				damage = 0;
				break;
			}
		}
		if ((shields & 64) && (vict->s_apd)) {
			if (damage >= vict->s_apd) {
				damage -= vict->s_apd;
				vict->s_apd = 0;
				sstatus++;
			} else {
				vict->s_apd -= damage;
				damage = 0;
				break;
			}
		}
		if ((shields & 128) && (vict->s_apk)) {
			if (damage >= vict->s_apk) {
				damage -= vict->s_apk;
				vict->s_apk = 0;
				sstatus++;
			} else {
				vict->s_apk -= damage;
				damage = 0;
				break;
			}
		}
		if (!sstatus)
			break;
	}
	/* Write shields to DB. */
	atr_add(vict->obj, A_S0, ftoa(vict->s_nav,6));
	atr_add(vict->obj, A_S1, ftoa(vict->s_bsd,6));
	atr_add(vict->obj, A_S2, ftoa(vict->s_bsk,6));
	atr_add(vict->obj, A_S3, ftoa(vict->s_bpd,6));
	atr_add(vict->obj, A_S4, ftoa(vict->s_bpk,6));
	atr_add(vict->obj, A_S5, ftoa(vict->s_asd,6));
	atr_add(vict->obj, A_S6, ftoa(vict->s_ask,6));
	atr_add(vict->obj, A_S7, ftoa(vict->s_apd,6));
	atr_add(vict->obj, A_S8, ftoa(vict->s_apk,6));

	sprintf(t, "#%d", fleet[source].obj==NOTHING ? fleet[source].exploding
			: fleet[source].obj);

	/* Exit if hit did not get past shields. */
	if (damage <= 0) {
		wptr[0] = "SHit"; /* No, it is short for 'Shield Hit'. :) */
		wptr[1] = t;
		did_it(SPACE_LORD, vict->obj, NULL, 0, NULL, 0, A_ASHIP);
		return;
	}

	/* Give the ship a lurch if damage is spread out and sufficent. */
	if (shields != 255) {
		if (shields & 15 || shields & 51 || shields & 107 || shields & 170 ||
				shields & 204 || shields & 240) {
			rel = vect_diff(vict->location,fleet[source].location);
			tot = fabs(rel.x) + fabs(rel.y) + fabs(rel.z);
			vict->linvel.x -= (damage * (rel.x / tot));
			vict->linvel.y -= (damage * (rel.y / tot));
			vict->linvel.z -= (damage * (rel.z / tot));
		} else {
			/* Just give the ship a good spin if not */
			amt = damage / 100;
			if (amt > (4 * PI)) amt = ((4 * PI) - 0.11);
			amt /= 2;
			abs = abs_heading(vict->heading, fleet[source].heading);
			if (abs.x >= 0 && abs.x < (PI / 2)) {
				vict->angvel.x -= amt;
				if (abs.y >= 0)
					vict->angvel.y -= amt;
				if (abs.y < 0)
					vict->angvel.y += amt;
			}
			if (abs.x >= (PI + (PI / 2))) {
				vict->angvel.x += amt;
				if (abs.y >= 0)
					vict->angvel.y -= amt;
				if (abs.y < 0)
					vict->angvel.y += amt;
			}
			if (abs.x >= (PI / 2) && abs.x < PI) {
				vict->angvel.x += amt;
				if (abs.y >= 0)
					vict->angvel.y += amt;
				if (abs.y < 0)
					vict->angvel.y -= amt;
			}
			if (abs.x >= PI && abs.x < (PI + (PI / 2))) {
				vict->angvel.x -= amt;
				if (abs.y >= 0)
					vict->angvel.y += amt;
				if (abs.y < 0)
					vict->angvel.y -= amt;
			}
		}
	}
	/* Notify the ship of the type of hit. */
	wptr[0] = (damage > (vict->superst / 4)) ? "HHit" : "LHit";
	wptr[1] = t;
	did_it(SPACE_LORD, vict->obj, NULL, 0, NULL, 0, A_ASHIP);

	/* Subtract armour value from damage taken. */
	damage -= vict->hull;
	if (damage < 0) damage = 0;

	/* Okay, the rest of the damage goes to the superstructure. */
	if (damage >= vict->superst) {
#ifdef LOG_COMMANDS
		log_space(tprintf("Destroyed ship #%d.",vict->obj));
#endif
		wptr[0] = "Destroy";
		did_it(SPACE_LORD, vict->obj, NULL, 0, NULL, 0, A_ASHIP);
		atr_add(vict->obj, A_SPRSTR, "0");
		explode(shipnum);
	} else {
		vict->superst -= damage;
		atr_add(vict->obj, A_SPRSTR, ftoa(vict->superst,6));
	}
	return;
}

int shield_hit (target, source, type)
	int target;
	struct coords source;
	int type;
{
	int shields = 0;
	int face;
	if (type == 2)
		/* Total shield hit */
	{
		shields = 255;
		return (shields);
	}
	if (type == 1)
		/* Multiple shield hit */
	{
		face = face_d6(target, source);
		if (face == 1) shields = 15;  /* Shields: 1, 2, 3, 4. */
		if (face == 2) shields = 51;  /* Shields: 1, 2, 5, 6. */
		if (face == 3) shields = 240; /* Shields: 5, 6, 7, 8. */
		if (face == 4) shields = 204; /* Shields: 3, 4, 7, 8. */
		if (face == 5) shields = 75;  /* Shields: 1, 2, 4, 7. */
		if (face == 6) shields = 170; /* Shields: 2, 4, 6, 8. */
		return (shields);
	}
	if (type != 1 && type != 2)
		/* Singular shield hit */
	{
		face = face_d8(target, source);
		if (face == 1) shields = 1;
		if (face == 2) shields = 2;
		if (face == 3) shields = 4;
		if (face == 4) shields = 8;
		if (face == 5) shields = 16;
		if (face == 6) shields = 32;
		if (face == 7) shields = 64;
		if (face == 8) shields = 128;
		return (shields);
	}
	return (shields);
}

/* Function for returning a facing on a 6 sided object.
	1=Forward, 2=Starboard, 3=Port, 4=Aft, 5=Deck, 6=Keel. */
int face_d6(target, source)
	int target;
	struct coords source;
{
	int facing = 0;
	struct coords heading;
	heading = rel_heading(&fleet[target], source);
	if (((heading.x >= ((PI * 2) - (PI / 4))) ||
				(heading.x < (PI / 4))) &&
			((heading.y < (PI / 4)) &&
			 (heading.y > -(PI / 4))))
		facing = 1;
	if (((heading.x >= (PI / 4)) &&
				(heading.x < (PI - (PI / 4)))) &&
			((heading.y < (PI / 4)) &&
			 (heading.y > -(PI / 4))))
		facing = 2;
	if (((heading.x >= (PI - (PI / 4))) &&
				(heading.x < (PI + (PI / 4)))) &&
			((heading.y < (PI / 4)) &&
			 (heading.y > -(PI / 4))))
		facing = 3;
	if (((heading.x >= (PI + (PI / 4))) &&
				(heading.x < ((PI * 2) - (PI / 4)))) &&
			((heading.y < (PI / 4)) &&
			 (heading.y > -(PI / 4))))
		facing = 4;
	if (heading.y >= (PI / 4))
		facing = 5;
	if (heading.y <= -(PI / 4))
		facing = 6;
	return (facing);
}

/* Function for returning a facing on an 8 sided object. */
int face_d8 (target, source)
	int target;
	struct coords source;
{
	int facing = 0;
	struct coords heading;
	heading = rel_heading(&fleet[target], source);

	if (heading.x >= 0 && heading.x < (PI / 2)) {
		if (heading.y >= 0)
			facing = 1;
		if (heading.y < 0)
			facing = 2;
	}
	if (heading.x >= (PI + (PI / 2))) {
		if (heading.y >= 0)
			facing = 3;
		if (heading.y < 0)
			facing = 4;
	}
	if (heading.x >= (PI / 2) && heading.x < PI) {
		if (heading.y >= 0)
			facing = 5;
		if (heading.y < 0)
			facing = 6;
	}
	if (heading.x >= PI && heading.x < (PI + (PI / 2))) {
		if (heading.y >= 0)
			facing = 7;
		if (heading.y < 0)
			facing = 8;
	}
	return (facing);
}

/* Function is called if two stellar bodies collide. */
/* Change this to take only the smaller of the two objects out. */
void planet_error (obj1, obj2)
	int obj1, obj2;
{
	char player[80],message[1024];
	sprintf(player, "%s", db[SPACE_LORD].name);
	sprintf(message,
			"Error - Stellar Body %s(#%d) was hit by Stellar Body %s(#%d).",
			db[fleet[obj1].obj].name,fleet[obj1].obj,db[fleet[obj2].obj].name,
			fleet[obj2].obj);
	do_mail(GOD, player, message);
#ifdef LOG_COMMANDS
	log_space(tprintf("ERROR: Stellar Body %s(#%d) hit Stellar Body %s(#%d).",
				db[fleet[obj1].obj].name,fleet[obj1].obj,db[fleet[obj2].obj].name,
				fleet[obj2].obj));
#endif
	if (fleet[obj1].mass < 1E30)
		del_ship(fleet[obj1].obj);
	if (fleet[obj2].mass < 1E30)
		del_ship(fleet[obj2].obj);
	if ((fleet[obj1].mass >= 1E30) && (fleet[obj2].mass >= 1E30)){
		del_ship(fleet[obj1].obj);
		del_ship(fleet[obj2].obj);
	}
	return;
}

/* Explodes an object in the space struct (instantaneous). */
void explode (shipnum)
	int shipnum;
{
	struct ship *vict;
	double dist;
	int force;
	int count;
	int shield;
	int dmg;
	vict = &fleet[shipnum];
	vict->exploding=vict->obj;
	if (vict->mass)
		force = fabs((vict->pwrgen + (vict->fuel / 100000.0)));
	else {
		force = 0;
		del_ship(vict->obj);
		return;
	}
	for (count = 0; count < SHIPS; ++count) {
		if (fleet[count].obj != NOTHING &&
				(!In_Hspace(count)) && (!fleet[count].exploding) &&
				(fleet[count].mass < 1E8))
			if((dist=distance3(vict->location,fleet[count].location))<=force) {
				dmg = ((force - dist) / 10);
				if (dmg < 1) dmg = 1;
				shield = shield_hit(count,vict->location,1);
				damage_ship(count, shield, dmg, shipnum);
			}
	}
	del_ship(vict->obj);
	return;
}

/*  Generate power from fuel supply.  */
void gen_power(mod)
	struct ship *mod;
{
	long solar;
	if (mod->mass == 0.0) return;
	/* Make sure fuel is not more than maximum for ship's mass */
	if (mod->fuel > (mod->mass * 5000.00)) {
		mod->fuel = (mod->mass * 5000.00);
	}
	mod->fuel -= mod->pwrfuel;
	mod->pwrgen += (mod->pwrfuel / 5.0);
	if (mod->fuel < 0.0) {
		mod->pwrgen += (mod->fuel / 5.0);
		mod->fuel = 0.0;
	}
	if (mod->pwrgen > 5001.00) {
		mod->pwrgen = 5001.00;
		mod->fuel += mod->pwrfuel;
	}
	/* Allow for solar power to add to generator. */
	if (((solar=((fleet[mod->sect.numb].energy) / (distance3(mod->location,
								fleet[mod->sect.numb].location)))) > 0.0) && (mod->mass <= 1E8)) {
		if (solar > 0.0) {
			/* Washout */
			if (solar > 5.0) solar = 5.0;
			if ((solar + mod->pwrgen) > 5001.00) mod->pwrgen = 5001.00;
			else mod->pwrgen += solar;
		}
	}
	/* Decrement power for Life Support.  */
	if (mod->mass <= 1E8) {
		mod->pwrgen -= 1;
		/* Decrement for Cloak. */
		if (mod->vismult < 0) {
			mod->pwrgen -= 100;
		}
		if (mod->pwrgen <= 0.0) {
			mod->pwrgen = 0.0;
			/* Trigger LSFail only once, softcode the rest. */
#ifdef LOG_COMMANDS
			log_space(tprintf("Life support failure for #%d.",mod->obj));
#endif
			wptr[0] = "LSFail";
			did_it(SPACE_LORD, mod->obj, NULL, 0, NULL, 0, A_ASHIP);
		}
	}
}

/*  Calculates the detectability of objects based on the gravitational
	 attraction and energy output of that object.  Returns a string of
	 the dbref items which can be detected at the ships position.  */
void sense_sweep (obj, ship_str)
	dbref obj;
	char *ship_str;
{
	int ship;
	int count;
	*ship_str = '\0';
	for (ship = 0; ship < SHIPS; ++ship)
		if (obj == fleet[ship].obj) {
			if (!In_Hspace(ship))
			{
				for (count = 0; count < SHIPS; ++count)
					/*  Improper indenting this function here down.  */
					if (fleet[count].obj != NOTHING)
						if (fleet[count].vismult >= 0)
							if (!In_Hspace(count) &&
									(fleet[count].obj != fleet[ship].obj))
								/*  ((Mass plus energy)/(distance^2)) >= (sensitivity).  */
								if (((GRAV * fleet[count].mass * 1E-3) +
											(fleet[count].energy * 1E-5))/
										(distance3(fleet[ship].location,fleet[count].location) *
										 distance3(fleet[ship].location,fleet[count].location)) >=
										(GRAV * STARMASS/(MAX_SENSE * MAX_SENSE)))
								{
									sprintf(ship_str, "#%d ", fleet[count].obj);
									ship_str += strlen(ship_str);
								}
			}
			break;
		}
}

/*  Calculates the visibility of objects based on the radius of that object
	 Returns a string of the dbref items which can be seen from the ship.  */
void vis_range (obj, ship_str,mag)
	dbref obj;
	char *ship_str;
	double mag;
{
	int ship;
	int count;
	int visible[SHIPS];
	int viscount=0;
	*ship_str = '\0';
	for (ship = 0; ship < SHIPS; ++ship)
		if (obj == fleet[ship].obj) {
			if (!In_Hspace(ship))
			{
				for (count = 0; count < SHIPS; ++count)
					if (fleet[count].obj != NOTHING)
						if (fleet[count].vismult >  0)
							if ((((fleet[count].radius * fleet[count].vismult) /
											((distance3(fleet[ship].location,
															fleet[count].location)/mag)*(distance3(fleet[ship].location,
																fleet[count].location)/mag))) >= 2.934E-11) &&
									(!In_Hspace(count)) &&
									(fleet[count].obj != fleet[ship].obj))
							{
								visible[viscount++]=count;
							}
			}
			line_of_sight(ship,visible,viscount);
			break;
		}
	for(count=0;count < viscount;count++)
		if(visible[count]!=NOTHING) {
			sprintf(ship_str, "#%d ", fleet[visible[count]].obj);
			ship_str += strlen(ship_str);
		}
}


void line_of_sight(source,visible,vis_count)
	int source;		/* ship # doing the line of sight */
	int *visible;		/* array of ships that can be seen so far */
	int vis_count;		/* count of the visible array length */
{
	int count,count2,countx,county;
	struct ship *i;
	struct ship *j;
	/* char tmp[200]; -unused */
	struct ship *k;
	struct coords empty;
	struct coords shadow;
	struct coords target;
	struct coords result1;
	struct coords result2;
	empty.x=empty.y=empty.z=0;

	k=&fleet[source];
	for(count=0;count < (vis_count-1);count++)
		for(count2=count+1;count2 < vis_count && visible[count]!=NOTHING;count2++) {
			if(visible[count2]==NOTHING) continue;
			countx=count;
			county=count2;
			i=&fleet[visible[countx]];
			j=&fleet[visible[county]];
			/* check who's in 'front' of the other.. Put them first in check */
			if(distance3(i->location,k->location) - i->radius >=
					distance3(j->location,k->location) - j->radius) {
				countx=count2;
				county=count;
				i=&fleet[visible[countx]];
				j=&fleet[visible[county]];
			}
			target.z=shadow.z=0;
			target.y=i->radius;
			shadow.y=j->radius;
			target.x=distance3(i->location,k->location);
			shadow.x=distance3(j->location,k->location);
			result1=abs_heading(empty,shadow);
			result2=abs_heading(empty,target);
			if(relvelangle(vect_diff(i->location,k->location),
						vect_diff(k->location,j->location)) +
					rad2deg(result1.x) <= rad2deg(result2.x)) {
				visible[county] = NOTHING;
			}
			if(visible[count] == NOTHING) break;
		}
}

void dist_check (obj, dist, ship_str)
	dbref obj;
	double dist;
	char *ship_str;
{
	int ship;
	int count;
	*ship_str = '\0';
	for (ship = 0; ship < SHIPS; ++ship)
		if (obj == fleet[ship].obj)
			if (!In_Hspace(ship))
			{
				for (count = 0; count < SHIPS; ++count)
					if (fleet[count].obj != NOTHING)
						if ((distance3(fleet[ship].location,fleet[count].location)
									<= dist) && (fleet[ship].obj != fleet[count].obj))
						{
							sprintf(ship_str, "#%d ", fleet[count].obj);
							ship_str += strlen(ship_str);
						}
				break;
			}
}

/*  Computes the gravitational attraction upon satellite from
	 parent.  Satellite velocity modified to reflect attraction,
	 but no modification is made to position.  No changes are made
	 to parent object.  This function is intended to be called
	 from function maneuver.  */
void grav_attr (satellite, parent, artf_g)
	struct ship *satellite;
	struct ship *parent;
	double artf_g; /* Artificial gravity, if applied. */
{
	struct coords forceh;  /*  Force heading in radians.  */
	struct coords tmpaccl; /*  Intermediate acceleration.  */
	struct coords tmploc;  /*  Intermediate location.  */
	double forced;         /*  Force distance in km.  */
	double forcem;         /*  Force magnitude, an accel, in km/s^2.  */
	forceh = abs_heading (satellite->location, parent->location);
	forced = distance3 (satellite->location, parent->location);
	if (forced <= 10.0)
		return;
	forcem = (-1.0)*((GRAV)*(UPDATE*UPDATE)*(parent->mass)/(forced*forced));
	if (artf_g) forcem = (-1.0 * artf_g / 2);
	tmpaccl.x = (forcem * cos(forceh.x) * cos(forceh.y));
	tmpaccl.y = (forcem * sin(forceh.x) * cos(forceh.y));
	tmpaccl.z = (forcem                 * sin(forceh.y));
	tmploc.x = satellite->location.x + satellite->linvel.x +
		(0.5 * satellite->linaccl.x);
	tmploc.y = satellite->location.y + satellite->linvel.y +
		(0.5 * satellite->linaccl.y);
	tmploc.z = satellite->location.z + satellite->linvel.z +
		(0.5 * satellite->linaccl.z);
	forceh = abs_heading (tmploc, parent->location);
	forced = distance3 (tmploc, parent->location);
	forcem = (-1.0)*((GRAV)*(UPDATE*UPDATE)*(parent->mass)/(forced*forced));
	if (artf_g) forcem = (-1.0 * artf_g / 2);
	satellite->linaccl.x -=
		(tmpaccl.x + (forcem * cos(forceh.x) * cos(forceh.y))) / 2.0;
	satellite->linaccl.y -=
		(tmpaccl.y + (forcem * sin(forceh.x) * cos(forceh.y))) / 2.0;
	satellite->linaccl.z -=
		(tmpaccl.z + (forcem                 * sin(forceh.y))) / 2.0;
}


/*  Calculates a ship's new location based on its current attributes
	 as listed in its structure and based on a maneuver consisting
	 of its angular accleleration and its linear acceleration (thrust).
	 The final position is recorded in the ship's structure.  */
void maneuver (ship_num)
	int ship_num;
{
	dbref obj;
	int count;
	struct ship *mod;    /*  Ship to be modified.  */
	struct coords ihdg;  /*  Temporary location for initial heading.  */
	struct coords iloc;  /*  Temporary location for initial location.  */
	mod = &fleet[ship_num];
	obj = mod->obj;
	ihdg.x = mod->heading.x;
	ihdg.y = mod->heading.y;
	ihdg.z = mod->heading.z;
	iloc.x = mod->location.x;
	iloc.y = mod->location.y;
	iloc.z = mod->location.z;
	mod->oldloc.x = mod->location.x;
	mod->oldloc.y = mod->location.y;
	mod->oldloc.z = mod->location.z;
	if (mod->mass < 5E16) gen_power(mod);

	/*  Decrement fuel for maintaining hyperspace.  */
	if (In_Hspace(ship_num))
	{
		mod->fuel -= 100;
		if (mod->fuel < 0)
		{
			mod->fuel = 0;
			hyperspace(mod->obj);
		}
	}
	/*  OMS (linear) and RCS (rotation) fuel decrimation.  */
	if (((fabs(mod->linaccl.x) + fabs(mod->linaccl.y) + fabs(mod->linaccl.z)) *
				mod->mass) > mod->fuel)
	{
		mod->linaccl.x = 0.0;
		mod->linaccl.y = 0.0;
		mod->linaccl.z = 0.0;
	}
	else
		mod->fuel -= (fabs(mod->linaccl.x) + fabs(mod->linaccl.y) +
				fabs(mod->linaccl.z)) * mod->mass;
	if (((fabs(mod->angaccl.x) + fabs(mod->angaccl.y) + fabs(mod->angaccl.z)) *
				mod->mass) > mod->fuel)
	{
		mod->angaccl.x = 0.0;
		mod->angaccl.y = 0.0;
		mod->angaccl.z = 0.0;
	}
	else
		mod->fuel -= (fabs(mod->angaccl.x) + fabs(mod->angaccl.y) +
				fabs(mod->angaccl.z)) * mod->mass;
	/*  Calculates acceleration based on user input thrust level
		 and ship mass.  Decrements fuel based on thrust ammount
		 and engine efficiency.  Decrements thrust if fuel is expended.  */
	if ((mod->effcny != 0.0) && (mod->rating != 0.0))
	{
		mod->fuel -= (fabs(mod->thrust) / (mod->effcny * mod->rating));
		if (mod->fuel < 0.0)
		{
			mod->thrust += (mod->fuel * mod->effcny * mod->rating);
			mod->fuel = 0.0;
			wptr[0] = "OOG";
			did_it(SPACE_LORD, mod->obj, NULL, 0, NULL, 0, A_ASHIP);
		}
	}
	else
		mod->thrust = 0.0;
	if (mod->mass != 0.0)
	{
		/*  Calculates the acceleration (both from thrust and OMS) based on
			 thrust, mass, and relativity.  */
		mod->accel = (mod->thrust / mod->mass) *
			(1.0-(vect_mag(mod->linvel)*vect_mag(mod->linvel)/
					(C*C*UPDATE*UPDATE)));
		mod->linaccl.x = mod->linaccl.x *
			(1.0-(vect_mag(mod->linvel)*vect_mag(mod->linvel)/
					(C*C*UPDATE*UPDATE)));
		mod->linaccl.y = mod->linaccl.y *
			(1.0-(vect_mag(mod->linvel)*vect_mag(mod->linvel)/
					(C*C*UPDATE*UPDATE)));
		mod->linaccl.z = mod->linaccl.z *
			(1.0-(vect_mag(mod->linvel)*vect_mag(mod->linvel)/
					(C*C*UPDATE*UPDATE)));
	}
	else
		mod->accel = 0.0;
	/*  Calculates the energy (detectibility) based on power output.  */
	mod->energy = fabs(mod->thrust) + mod->s_bsd + mod->s_bsk + mod->s_bpd +
		mod->s_bpk + mod->s_asd + mod->s_ask + mod->s_apd + mod->s_apk +
		mod->s_nav + mod->pwrgen;
	/*  Calculates new angular velocity (current angular velocity
		 plus angular acceleration).  */
	mod->angvel.x += mod->angaccl.x;
	mod->angvel.y += mod->angaccl.y;
	mod->angvel.z += mod->angaccl.z;
	/*  Calculates new heading (current heading plus current angular
		 velocity plus half of the angular acceleration).  */
	mod->heading.x += mod->angvel.x - (0.5 * mod->angaccl.x);
	mod->heading.y += mod->angvel.y - (0.5 * mod->angaccl.y);
	mod->heading.z += mod->angvel.z - (0.5 * mod->angaccl.z);
	/*  Adjusts heading to accomodate convention.  Convention is Yaw and
		 Roll between 0 and 2PI, Pitch between 0 and PI.  */
	while (mod->heading.y < (-0.5 * PI))
		mod->heading.y += (TWO_PI);
	while (mod->heading.y >= ( 1.5 * PI))
		mod->heading.y -= (TWO_PI);
	if (mod->heading.y > (0.5* PI))
	{
		mod->heading.y = PI - mod->heading.y;
		mod->heading.z += PI;
		mod->heading.x += PI;
		mod->angvel.y = -1.0 * mod->angvel.y;
	}
	while (mod->heading.x < 0)
		mod->heading.x += (TWO_PI);
	while (mod->heading.x >= (TWO_PI))
		mod->heading.x -= (TWO_PI);
	while (mod->heading.z < 0)
		mod->heading.z += (TWO_PI);
	while (mod->heading.z >= (TWO_PI))
		mod->heading.z -= (TWO_PI);
	/*  Calculates new linear velocity (an approximation).  Two-
		 thirds of the thrust resolved to heading applies to the
		 current heading and one-third to the new heading.  This
		 approximation does not consider angular acceleration, only
		 angular velocity.  A differential equation is necessary to
		 consider angular acceleration and will be written in the
		 future.  */
	mod->linaccl.x +=
		(mod->accel * 0.667 * cos(ihdg.x)         * cos(ihdg.y) ) +
		(mod->accel * 0.333 * cos(mod->heading.x) * cos(mod->heading.y) );
	mod->linaccl.y +=
		(mod->accel * 0.667 * sin(ihdg.x)         * cos(ihdg.y) ) +
		(mod->accel * 0.333 * sin(mod->heading.x) * cos(mod->heading.y) );
	mod->linaccl.z +=
		(mod->accel * 0.667 * 1.0                 * sin(ihdg.y) ) +
		(mod->accel * 0.333 * 1.0                 * sin(mod->heading.y) );
	/*  Scan for all items in fleet array for items of similar sector.
		 Objects with mass > 100000000 kg act upon the mod ship.
		 Function grav_attr finds the acceleration due to the gravity of
		 significant mass in the area.  Gravitational attraction is
		 assumed to be instantaneous from the midpoint of the path.  It is
		 not integrated over the path of the starship.  */
	for (count = 0; count < SHIPS; ++count)
		if (!strcmp(fleet[count].sect.name, mod->sect.name) &&
				(mod != &fleet[count]))
			if ((fleet[count].mass) > 1E8 && fleet[count].obj != NOTHING)
				grav_attr(mod, &fleet[count], 0.0);
	/*  Effect ship by any tractor beam in place. */
	if (mod->tractor == count)
		grav_attr(mod, &fleet[count], mod->artf_g);
	/*  Calculates new location, aka linear position (current location
		 plus the initial velocity plus one-half of the acceleration
		 resolved in Cartesian directions).  */
	mod->location.x += mod->linvel.x + (0.5 * mod->linaccl.x);
	mod->location.y += mod->linvel.y + (0.5 * mod->linaccl.y);
	mod->location.z += mod->linvel.z + (0.5 * mod->linaccl.z);
	/*  Updates the velocity.  The new velocity (resolved in Cartesian
		 directions) equals the acceleration plus the initial velocity.  */
	mod->linvel.x += mod->linaccl.x;
	mod->linvel.y += mod->linaccl.y;
	mod->linvel.z += mod->linaccl.z;
	/*  Set OMS and RCS accelerations to zero to simulate bursts.  */
	mod->linaccl.x = 0;
	mod->linaccl.y = 0;
	mod->linaccl.z = 0;
	mod->angaccl.x = 0;
	mod->angaccl.y = 0;
	mod->angaccl.z = 0;

	/*  Check hyperspace for interstellar entry.  */
	if (In_Hspace(ship_num))
	{
		if (vect_mag(mod->linvel) < (C * UPDATE))
			strcpy(mod->sect.name, "IS");
	}
	/*  Check interstellar space sector for system entry.  */
	if (!strcmp(mod->sect.name,"IS"))
	{
		for (count=0; count < SHIPS; ++count)
			/* The mass below _was_ 1.592E29, but it turns out Wolf-359's
				mass is 3.96E28, so I fixed it to work. -Majere */
			if (fleet[count].mass >= STARMASS && fleet[count].obj != NOTHING)
				if (distance3(mod->location,fleet[count].location) < 3E11) {
					strcpy(mod->sect.name, fleet[count].sect.name);
					mod->sect.numb = count;
				}
	}
	/*  Check system sectors for interstellar space entry.  */
	if (!In_Hspace(ship_num) && strcmp(mod->sect.name,"IS"))
	{
		for (count=0; count < SHIPS; ++count)
			if (fleet[count].mass >= STARMASS && fleet[count].obj != NOTHING)
				if (!strcmp(fleet[count].sect.name, mod->sect.name))
					if (distance3(mod->location,fleet[count].location) > 3E11) {
						strcpy(mod->sect.name, "IS");
						mod->sect.numb = NULL;
					}
	}
}

void check_collision(count, count2)
	int count, count2;
{
	struct ship *i;
	struct ship *j;
	struct coords relvel;
	int mpact;
	/*  int i_shield, j_shield;
		 int i_dmg, j_dmg; Why are these here? */
	char t1[10], t2[10];
	if(fleet[count].obj == NOTHING || fleet[count2].obj == NOTHING
			|| fleet[count].obj == fleet[count2].obj)
		return;

	i = &fleet[count];
	j = &fleet[count2];

	sprintf(t1, "#%d", i->obj);
	sprintf(t2, "#%d", j->obj);

	/* Check to see if they are attached (docked) first. */
	if (i->o_att == j->obj) {
		/* Undock them if they have moved out of position */
		if ((i->angvel.x != 0.0) || (i->angvel.y != 0.0) ||
				(j->angvel.x != 0.0) || (j->angvel.y != 0.0) ||
				(((i->angvel.z) - (j->angvel.z)) != 0.0) ||
				(i->accel > 0) || (j->accel > 0) ||
				((distance3(i->location,j->location)-(i->radius+j->radius))>1.0))
		{
#ifdef LOG_COMMANDS
			log_space(tprintf("Undocking #%d and #%d.",i->obj,j->obj));
#endif
			sprintf(t1, "#%d", i->obj);
			sprintf(t2, "#%d", j->obj);
			wptr[0] = "Undocked";
			wptr[1] = t2;
			did_it(SPACE_LORD, i->obj, NULL, 0, NULL, 0, A_ASHIP);
			wptr[0] = "Undocked";
			wptr[1] = t1;
			did_it(SPACE_LORD, j->obj, NULL, 0, NULL, 0, A_ASHIP);
			i->o_att = 0;
			j->o_att = 0;
			atr_add(i->obj, A_S9, "\0");
			atr_add(j->obj, A_S9, "\0");
			return;
		} else
			return;
	}

	/* Check to see if they are anywhere near each other */
	/*  Need to know maximum velocity from either the begining or end
		 of the current update. Consider accel in eqation. */
	/*  if(fabs(distance3(i->location,j->location) - (i->radius + j->radius)) >
		 fabs(distance3(i->linvel,j->linvel))) {
		 i->sect.nebu = NULL;
		 j->sect.nebu = NULL;
		 return;
		 } */
	mpact=0;
	/*  Check if endpoints of maneuver are contained in
		 the radius of another object.   */

	if (distance3(i->location, j->location) <=
			(i->radius+j->radius))
	{
		if ((i->mass == 0.0 && i->pwrgen == 0.0) ||
				(j->mass == 0.0 && j->pwrgen == 0.0))
		{
			if (distance3(i->oldloc, j->oldloc) >
					(i->radius+j->radius)) {
				if (i->radius > j->radius) j->sect.nebu = count;
				if (j->radius > i->radius) i->sect.nebu = count2;
				wptr[0]="Entry";
				wptr[1]=t1;
				did_it(SPACE_LORD, j->obj, NULL, 0, NULL, 0, A_ASHIP);
				wptr[0]="Entry";
				wptr[1]=t2;
				did_it(SPACE_LORD, i->obj, NULL, 0, NULL, 0, A_ASHIP);
				return;
			} else return;
		}
		mpact = 1;
	}
	relvel = vect_diff(vect_diff(i->oldloc,i->location),
			vect_diff(j->oldloc,j->location));
	/*  Check if course is in line with a body in space.  */
	if (mpact != 1 && linept_dist(vect_diff(i->location,i->location),
				relvel, vect_diff(i->oldloc,j->oldloc)) <= (j->radius+i->radius))
	{
		/*  Check if the radius of object count contains the
			 segment between the two endpoints.  */
		if ((vect_mag(relvel) >= distance3(i->oldloc,j->oldloc)) &&
				(vect_mag(relvel) >= distance3(i->location,j->location)))
		{
			if ((i->mass == 0.0 && i->pwrgen == 0.0) ||
					(j->mass == 0.0 && j->pwrgen == 0.0)) {
				wptr[0]="Entry";
				wptr[1]=t1;
				did_it(SPACE_LORD, j->obj, NULL, 0, NULL, 0, A_ASHIP);
				wptr[0]="Entry";
				wptr[1]=t2;
				did_it(SPACE_LORD, i->obj, NULL, 0, NULL, 0, A_ASHIP);
				return;
			} else mpact = 1;
		}
	}
	if (mpact == 1)
	{
		/* In case a planet hits a planet */
		if ((i->mass > 1E8) && (j->mass > 1E8))
		{
			planet_error(count,count2);
		}
		else
		{
			int i_shield, j_shield;
			int i_dmg, j_dmg;
#ifdef LOG_COMMANDS
			log_space(tprintf("Impact #%d with #%d.",fleet[count].obj,
						fleet[count2].obj));
#endif

			/* Determine type of shield hit
				0 - One shield hit.
				1 - Multiple (4) shields hit.
				2 - All shields hit (8). */
			if (i->radius >= (j->radius * 8)) {
				i_shield = shield_hit(count,j->oldloc,0);
				if (i->radius >= (j->radius * 80))
					j_shield = shield_hit(count2,i->oldloc,2);
				else
					j_shield = shield_hit(count2,i->oldloc,1);
			} else if (j->radius >= (i->radius * 8)) {
				j_shield = shield_hit(count2,i->oldloc,0);
				if (j->radius >= (i->radius * 80))
					i_shield = shield_hit(count,j->oldloc,2);
				else
					i_shield = shield_hit(count,j->oldloc,1);
			} else {
				i_shield = shield_hit(count,j->oldloc,1);
				j_shield = shield_hit(count2,i->oldloc,1);
			}
			/* Determine damage from collision */
			/* No mass means the energy caused the damage */
			if (!i->mass)
				j_dmg = i->pwrgen;
			else
				/* Damage is mass * velocity / 1000 */
				j_dmg = ((fabs(i->mass) * fabs(distance3(i->linvel,j->linvel)))
						/ 1000);
			/* It takes at least one point of damage from any hit */
			if (j_dmg < 1) j_dmg = 1;
			/* Planets don't take damage */
			if (j->mass > 5E16) j_dmg = 0;
			/* Now for the other ship */
			if (!j->mass)
				i_dmg = j->pwrgen;
			else
				i_dmg = ((fabs(j->mass) * fabs(distance3(j->linvel,i->linvel)))
						/ 1000);
			if (i_dmg < 1) i_dmg = 1;
			if  (i->mass > 5E16) i_dmg = 0;
			/* Anti-matter does ten times the damage to both */
			if ((i->mass < 0) || (j->mass < 0)) {
				i_dmg *= 10;
				j_dmg *= 10;
			}
			/* Execute damage to ships */
#ifdef LOG_COMMANDS
			log_space(tprintf("Hit Shields %d, %d. Damage: %d, %d",
						i_shield,j_shield,i_dmg,j_dmg));
#endif
			damage_ship(count,i_shield,i_dmg,count2);
			damage_ship(count2,j_shield,j_dmg,count);
		}
	}
}

void hyperspace (obj)
	dbref obj;
{
	int search;
	int count = -1;
	for (search = 0; search < SHIPS; ++search)
		if (fleet[search].obj == obj)
			count = search;
	if (count == -1)
		return;
	if (fleet[count].fuel < 1000) {

		fleet[count].fuel = 0;
		wptr[0] = "Hyperfail";
		did_it(SPACE_LORD, obj, NULL, 0, NULL, 0, A_ASHIP);
		return;
	}
	if (!In_Hspace(count)) {
		if (fleet[count].fuel < 1000) {
			fleet[count].fuel = 0;
			wptr[0] = "Hyperfail";
			did_it(SPACE_LORD, obj, NULL, 0, NULL, 0, A_ASHIP);
			return;
		} else {
			fleet[count].fuel -= 1000;
			fleet[count].linvel.x = fleet[count].linvel.x * 365.0;
			fleet[count].linvel.y = fleet[count].linvel.y * 365.0;
			fleet[count].linvel.z = fleet[count].linvel.z * 365.0;
			strcpy(fleet[count].sect.name, "HS");
			fleet[count].sect.numb = NULL;
			write_ship(count);
			wptr[0] = "Hyperenter";
			did_it(SPACE_LORD, obj, NULL, 0, NULL, 0, A_ASHIP);
			return;
		}
	} else {
		fleet[count].linvel.x = fleet[count].linvel.x / 365.0;
		fleet[count].linvel.y = fleet[count].linvel.y / 365.0;
		fleet[count].linvel.z = fleet[count].linvel.z / 365.0;
		strcpy(fleet[count].sect.name, "IS");
		write_ship(count);
		wptr[0] = "Hyperexit";
		did_it(SPACE_LORD, obj, NULL, 0, NULL, 0, A_ASHIP);
		return;
	}
}

/*  Function determines if two ships meet the criteria for docking.  */
int checkdock (dock, statn, land)
	int dock;   /*  The ship that is docking.       */
	int statn;  /*  The ship that is being docked.  */
	int land;   /*  0 for nose to nose, 1 for nose to aft.  */
{
	struct coords hdline;  /*  Heading line of statn.  */
	int dock_ok = 0;
	hdline.x = (fleet[statn].location.x +
			(10.0 * cos(fleet[statn].heading.x) * cos(fleet[statn].heading.y)));
	hdline.y = (fleet[statn].location.y +
			(10.0 * sin(fleet[statn].heading.x) * cos(fleet[statn].heading.y)));
	hdline.z = (fleet[statn].location.z +
			(10.0                               * sin(fleet[statn].heading.y)));
	/*  Indention convention disregarded.  */
	if ((fleet[statn].mass) < (5E16))
		if ((fleet[dock].mass) < (1E8))
			if (distance3(fleet[dock].location, fleet[statn].location) <=
					(fleet[dock].radius + fleet[statn].radius + 2.0))
				if (linept_dist(fleet[statn].location,hdline,fleet[dock].location) <=
						(1.0))
					if (distance3(fleet[dock].location,hdline) < (50.0))
						/*  if (fabs(fleet[statn].linvel.x - fleet[dock].linvel.x) <= (1.0))
							 if (fabs(fleet[statn].linvel.y - fleet[dock].linvel.y) <= (1.0))
							 if (fabs(fleet[statn].linvel.z - fleet[dock].linvel.z) <= (1.0))  */
						if (((!land)&&(distance3(fleet[statn].linvel,fleet[dock].linvel)<=1.0))
								||((land)&&(distance3(fleet[statn].linvel,fleet[dock].linvel)<=10.0)))
							/*  Not sure if this line works with every case.  */
							if (land) goto landpart;
	if (rad2deg(PI - fabs(fleet[statn].heading.x - fleet[dock].heading.x))
			<= (5.0))
		if (rad2deg(fabs(fleet[statn].heading.y + fleet[dock].heading.y))
				<= (5.0))
			if (rad2deg(fabs(2*PI - fleet[statn].heading.z - fleet[dock].heading.z))
					<= (5.0))
				goto lastpart;
landpart:
	if (rad2deg(fabs(fleet[statn].heading.x - fleet[dock].heading.x))
			<= (5.0))
		if (rad2deg(fabs(fleet[statn].heading.y - fleet[dock].heading.y))
				<= (5.0))

			if (rad2deg(fabs(fleet[statn].heading.y - fleet[dock].heading.y))
					<= (5.0))
				lastpart:
					if (rad2deg(fabs(fleet[statn].angvel.x)) <= (1.0))
						if (rad2deg(fabs(fleet[statn].angvel.y)) <= (1.0))
							if (rad2deg(fabs(fleet[dock].angvel.x)) <= (1.0))
								if (rad2deg(fabs(fleet[dock].angvel.y)) <= (1.0))
									if (rad2deg(fabs(fleet[statn].angvel.z + fleet[dock].angvel.z)) <= (1.0))
										dock_ok = 1;
	if (dock_ok == 1)
		return(1);
	else
		return(0);
}

/* The following two functions were written by Carrie_Gram and are not subject
	to copyright restrictions. */

/* The posx, posy, velx, vely, etc...Are all relative position and velocity
	between two space objects. It will return the largest angle between
	the relative position vector and relative velocity vector in degrees.  */
double relvelangle(pos,vel)
	struct coords pos, vel;
{
	double ratio;
	double phi;
	ratio = (((pos.x * -vel.x) + (pos.y * -vel.y) + (pos.z * -vel.z)) /
			(sqrt(fabs((pos.x * pos.x) + (pos.y * pos.y) + (pos.z * pos.z)))*
			 sqrt(fabs((vel.x * vel.x) + (vel.y * vel.y) + (vel.z * vel.z)))));
	if (ratio > 1.0)
		ratio = 1.0;
	else if (ratio < -1.0)
		ratio = -1.0;
	phi = (acos(ratio) * 180 / PI);
	return (phi);
}

/*  Utility function to get orbital data.  */
void orbit (string, mass, distance, velocity, angle)
	char *string;     /* String to be filled */
	double mass;      /* The mass of the object orbited */
	double distance;  /* The distance of orbit */
	double velocity;  /* ? */
	double angle;     /* ? */
{
	double attr;    /* Generic gravitational attraction */
	double energy;  /* Combined kinetic and potential energy of orbit */
	double value;   /* Constant value of orbit */
	double eccen;   /* Eccentricity of orbit */
	double axis;    /* The semi-major axis of the orbit */
	double apogee;  /* The apogee of the current orbit */
	double perigee; /* The perigee of the current orbit */
	double period;  /* The period of the current orbit */
	*string = '\0';
	angle = angle + 90;
	attr = (GRAV * (UPDATE * UPDATE) * mass);
	if (distance == 0)
		energy = 0;
	else
		energy = ((velocity * velocity) / 2.0) - (attr / distance);
	value = (distance * velocity * cos(angle * PI / 180));
	if (attr == 0)
		eccen = 0;
	else
		eccen = sqrt(fabs(1 + ((2.0 * energy * value*value)/(attr*attr))));
	if (energy == 0)
		axis = 0;
	else
		axis = (-attr / (2.0 * energy));
	apogee = (axis * (1.0 + eccen));
	perigee = (axis * (1.0 - eccen));
	if (attr == 0)
		period = 0;
	else
		period = (2.0 * PI * sqrt(fabs((axis * axis * axis) / attr)));
	sprintf(string,"%15.6f %10.2f %10.2f %10.6f %8.1f",
			energy, apogee, perigee, eccen, period);
	return;
}


/*  >> Externally Called functions. <<  */

/*  The next 'do_' functions are called from process_command in game.c,
	 they have been installed into space.c to more localize the code.  */

/*  Loads all valid objects in ROOM_ZEROG into the space struct.  */
void do_spaceboot (player)
	dbref player;
{
	if (power(player, POW_SPACE))
	{
		if (halt_space == 1) {
			notify(player, "Space is currently running.");
			return;
		}
#ifdef LOG_COMMANDS
		log_space(tprintf("BOOT by %s(#%d).", db[player].name, player));
#endif
		halt_space = 1;

		if (init_space())
			notify(player, "Space booted!");
		else
			notify(player, "Space error, see log.");
	}
	else
		notify(player, "Not in this lifetime!");
}

/*  Shows the contents of the space struct by dbref number.  */
void do_spacecont (player)
	dbref player;
{
	char ship_str[SHPSTR];
	char ship_cat[SHPSTR+18];
	char total_str[80];
	int total_ships;
	if (power(player, POW_SPACE))
	{
		list_fleet(ship_str);
		total_ships = count_fleet();
		*ship_cat = '\0';
		sprintf(total_str, "Total number of objects in space: %d  Maximum: %d",
				total_ships,MAX_SHIPS);
		strcat(ship_cat, "Objects in space: ");
		strcat(ship_cat, ship_str);
		if (halt_space == 1) {
			notify(player, "Space Status: Running");
		} else {
			notify(player, "Space Status: Halted");
		}
		notify(player, total_str);
		notify(player, ship_cat);
	}
	else
		notify(player, "You have to use sensors.");
}
/*  Show the variables of the space struct for a single object.  */
void do_spacedata (player, name)
	dbref player;
	char *name;
{
	dbref obj;
	if ((obj = match_thing(player, name)) == NOTHING) return;
	if (!power(player, POW_SPACE))
		notify(player, "NOT!");
	else
	{
		int count;
		char data[80], numb[80], save[300];
		char nav0[80],nav1[80],nav2[80],nav3[80],nav4[80],nav5[80],nav6[80];
		char sci1[80], sci2[80], sci3[80], sci4[80], sci5[80];
		char tac1[80], tac2[80], tac3[80], tac4[80];
		for(count = 0; count < SHIPS; ++count)
			if (count == SHIPS)
				notify(player, "That object is not in the space struct.");
			else if (fleet[count].obj == obj)
			{
				/*  Assign variables.  */
				sprintf(data, "DATA READOUT FOR:  %s", db[obj].name);
				sprintf(numb, "Struct number: %d  Dbref number: #%d  Type: %s",
						count,obj,atr_get(obj, A_TYPE));
				sprintf(nav0, "Sector: %s  Acceleration: %f",
						fleet[count].sect.name, fleet[count].accel);
				sprintf(nav1, "Linpos: %f %f %f", fleet[count].location.x,
						fleet[count].location.y, fleet[count].location.z);
				sprintf(nav2, "Linvel: %f %f %f", fleet[count].linvel.x,
						fleet[count].linvel.y, fleet[count].linvel.z);
				sprintf(nav3, "Linacc: %f %f %f", fleet[count].linaccl.x,
						fleet[count].linaccl.y, fleet[count].linaccl.z);
				sprintf(nav4, "Angpos: %f %f %f", fleet[count].heading.x,
						fleet[count].heading.y, fleet[count].heading.z);
				sprintf(nav5, "Angvel: %f %f %f", fleet[count].angvel.x,
						fleet[count].angvel.y, fleet[count].angvel.z);
				sprintf(nav6, "Angacc: %f %f %f", fleet[count].angaccl.x,
						fleet[count].angaccl.y, fleet[count].angaccl.z);
				sprintf(sci1, "Mass: %f  Energy: %ld",
						fleet[count].mass, fleet[count].energy);
				sprintf(sci2, "Radius: %f  Vismult: %d",
						fleet[count].radius, fleet[count].vismult);
				sprintf(sci3, "Thrust: %f  Fuel: %f",
						fleet[count].thrust, fleet[count].fuel);
				sprintf(sci4, "Rating: %f  Efficiency: %f",
						fleet[count].rating, fleet[count].effcny);
				sprintf(sci5, "Power Generator: %ld  Power Fuel: %ld",
						fleet[count].pwrgen, fleet[count].pwrfuel);
				sprintf(tac1, "BSM: %d  BSK: %d  BPM: %d  BPK: %d",
						fleet[count].s_bsd, fleet[count].s_bsk,
						fleet[count].s_bpd, fleet[count].s_bpk);
				sprintf(tac2, "ASM: %d  ASK: %d  APM: %d  APK: %d",
						fleet[count].s_asd, fleet[count].s_ask,
						fleet[count].s_apd, fleet[count].s_apk);
				sprintf(tac3, "Nav: %d  Hull: %d  Super-Structure: %d",
						fleet[count].s_nav, fleet[count].hull, fleet[count].superst);
				sprintf(tac4, "Tractor: %d  Force: %f",
						fleet[count].tractor, fleet[count].artf_g);
				strcpy(save, fleet[count].dark);
				/*  Output variables to user.  */
				notify(player, " ");
				notify(player, data);
				notify(player, numb);
				notify(player, " ");
				notify(player, "NAVIGATIONAL DATA");
				notify(player, nav0);
				notify(player, nav1);
				notify(player, nav2);
				notify(player, nav3);
				notify(player, nav4);
				notify(player, nav5);
				notify(player, nav6);
				notify(player, " ");
				notify(player, "SCIENTIFIC DATA");
				notify(player, sci1);
				notify(player, sci2);
				notify(player, sci3);
				notify(player, sci4);
				notify(player, sci5);
				notify(player, " ");
				notify(player, "TACTICAL DATA");
				notify(player, tac1);
				notify(player, tac2);
				notify(player, tac3);
				notify(player, tac4);
				notify(player, " ");
				notify(player, "RECOVER DATA");
				notify(player, save);
				notify(player, " ");
				notify(player, "END");
				break;
			}
	}
}

void do_spacedock(player, ship1, ship2)
	dbref player;
	char *ship1;
	char *ship2;
{
	dbref docker;
	dbref dockie;
	char t1[10], t2[10];
	int i,j,count;
	if ((docker = match_thing(player, ship1)) == NOTHING) return;
	if ((dockie = match_thing(player, ship2)) == NOTHING) return;
	if (!power(player, POW_SPACE))
	{
		notify(player,
				"Okay, @destroying everything you own...please wait.");
		return;
	}
	else
	{
		notify(player, "Power recognized.");
		i = -1; j= -1;
		for(count=0;count < SHIPS; count++)
		{
			if(fleet[count].obj == docker)
				i = count;
			if(fleet[count].obj == dockie)
				j = count;
		}
		if (i == -1)
		{
			notify(player, "First ship is not in the struct.");
			return;
		}
		if (j == -1)
		{
			notify(player,"Second ship is not in the struct.");
			return;
		}
		if (checkdock(i,j,0))
		{
			sprintf(t1, "#%d", dockie);
			sprintf(t2, "#%d", docker);
			fleet[i].o_att = dockie;
			fleet[j].o_att = docker;
			fleet[i].location.x = fleet[j].location.x;
			fleet[i].location.y = fleet[j].location.y;
			fleet[i].location.z = fleet[j].location.z;
			fleet[i].linvel.x = fleet[j].linvel.x;
			fleet[i].linvel.y = fleet[j].linvel.y;
			fleet[i].linvel.z = fleet[j].linvel.z;
			fleet[i].angvel.z = fleet[j].angvel.z;
			fleet[i].angvel.y = 0.0;
			fleet[j].angvel.y = 0.0;
			fleet[i].angvel.x = 0.0;
			fleet[j].angvel.x = 0.0;
			fleet[i].heading.x = (fleet[j].heading.x + PI);
			fleet[i].heading.y = (2*PI - fleet[j].heading.z);
			fleet[i].heading.z = (2*PI - fleet[j].heading.z);
			atr_add(docker, A_S9, t1);
			atr_add(dockie, A_S9, t2);
			wptr[0]="Successfull Docker";
			wptr[1]=t1;
			did_it(SPACE_LORD, docker, NULL, 0, NULL, 0, A_ASHIP);
			wptr[0]="Successfull Dockie";
			wptr[1]=t2;
			did_it(SPACE_LORD, dockie, NULL, 0, NULL, 0, A_ASHIP);
			notify(player, "Ships docked.");
		}
		else
		{
			wptr[0]="Failed Docker";
			did_it(SPACE_LORD, docker, NULL, 0, NULL, 0, A_ASHIP);
			wptr[0]="Failed Dockie";
			did_it(SPACE_LORD, dockie, NULL, 0, NULL, 0, A_ASHIP);
			notify(player, "Docking failed.");
		}
	}
}

/*  Loads a single valid ship into the space struct.  */
void do_spaceenter (player, name)
	dbref player;
	char *name;
{
	dbref obj;
	if ((obj = match_thing(player, name)) == NOTHING)
		return;
	if (power(player, POW_SPACE))
	{
		if (halt_space != 1) {
			notify(player, "Space is not running.");
			return;
		}
		if (find_ship(obj) != -1) {
			notify(player, "That ship is already in space.");
			return;
		}
		if Ship(obj) {
			if (init_ship(obj) == 1)
			{
				notify(player, "Ship added.");
#ifdef LOG_COMMANDS
				log_space(tprintf("Ship #%d added by %s(#%d).",obj,
						db[player].name, player));
#endif
			} else {
				del_ship(obj);
				notify(player, "Ship contains bad attribute data, not added.");
			}
		} else {
			notify(player, "That is not a valid ship.");
		}
	}
	else
		notify(player, "Nice try buddy.");
}

/*  Removes a single ship from the space struct.  */
void do_spaceexit (player, name)
	dbref player;
	char *name;
{
	dbref obj;
	if ((obj = match_thing(player, name)) == NOTHING)
		return;
	if (power(player, POW_SPACE))
	{
		if (!strcmp(atr_get(obj, A_TYPE),"SB"))
			notify(player, "Protected stellar body.");
		else
		{
			notify(player, "Ship removed.");
			del_ship(obj);
#ifdef LOG_COMMANDS
			log_space(tprintf("Ship #%d removed by %s(#%d).",obj,
						db[player].name, player));
#endif
		}
	}
	else
		notify(player, "Try crashing yourself instead.");
}
/* Function allows manual control over explode(). */
void do_spaceexplode(player, arg1)
	dbref player;
	char *arg1;
{
	dbref obj;
	int shipnum;
	if(!power(player, POW_SPACE)) {
		notify(player, "Only in your wildest of dreams.");
		return;
	}
	if ((obj = match_thing(player,arg1)) == NOTHING)
		return;
	if ((shipnum = find_ship(obj))==-1) {
		notify(player, "Not in space.");
		return;
	}
	wptr[0] = "Destroy";
	did_it(SPACE_LORD, obj, NULL, 0, NULL, 0, A_ASHIP);
	atr_add(obj, A_SPRSTR, "0");
	explode(shipnum);
	notify(player, "Ship has been exploded.");
	return;
}

/* Function to allow manual control over gravity. */
void do_spacegrav (player, ship1, shipv)
	dbref player;
	char *ship1;
	char *shipv[10];
{
	dbref obj1, obj2;
	int shipnum1, shipnum2;
	double grav;
	if(!power(player, POW_SPACE)) {
		notify(player, "Should have eaten your wheaties...");
		return;
	}
	if ((obj1 = match_thing(player,ship1)) == NOTHING)
		return;
	if ((obj2 = match_thing(player,shipv[1])) == NOTHING)
		return;
	if ((shipnum1 = find_ship(obj1))==-1) {
		notify(player, "Ship 1 is not in space.");
		return;
	}
	if ((shipnum2 = find_ship(obj2))==-1) {
		notify(player, "Ship 2 is not in space.");
		return;
	}
	grav = atof(shipv[2]);
	fleet[shipnum2].tractor = shipnum1;
	fleet[shipnum2].artf_g = grav;
	notify(player, "Gravity executed.");
	return;
}
/*  Stops the space() loop, saves space, and clears the ship struct.  */
void do_spacehalt (player)
	dbref player;
{
	if (power(player, POW_SPACE))
	{
#ifdef LOG_COMMANDS
		log_space(tprintf("HALT by %s(#%d).", db[player].name, player));
#endif
		notify(player, "Space halted.");
		halt_space = 0;
		dump_space();
		clear_fleet();
	}
	else
		notify(player, "You may not halt space.");
}

/*  Gives a list of vaild space commands.  */
void do_spacehelp (player)
	dbref player;
{
	if (power(player, POW_SPACE))
	{
		notify(player, "Space commands are as follows:");
		notify(player, "!boot - Fills the ship struct and starts space()");
		notify(player, "!halt - Clears the ship struct and stops space()");
		notify(player, "!cont - List dbrefs of ships in the ship struct");
		notify(player, "!enter <#> - Puts # into the ship struct");
		notify(player, "!exit <#> - Clears # from the ship struct");
		notify(player, "!data <#> - Lists ship struct for #");
		notify(player, "!hyper <#> - Puts # into hyperspace");
		notify(player, "!worm <#>=<x>,<y>,<z> - Jumps # to xyz");
		notify(player, "!dock <#1>=<#2> - Attempts a dock between 1 and 2");
		notify(player, "!land <#1>=<#2> - 1 attempts to land in 2");
		notify(player, "!visevent <event>=<dist>,<X>,<Y>,<Z> - Visual event");
		notify(player, "!senevent <event>=<dist>,<X>,<Y>,<Z> - Sensor event");
		notify(player, "!comevent <#>=<dist>,<ch#>,<encrypt>,<id>,<msg>");
		notify(player, "!shield <#> - Reads shields into struct");
		notify(player, "!explode <#> - Violently removes # from ship struct");
		notify(player, "!track <#1>=<#2> - 1 automatically tracks 2");
		notify(player, "!grav <#1>=<#2>,<MAG> - Gravitational attraction");
	}
	else
		notify(player, "Find help somewhere else...");
}

/*  Puts a valid ship into hyperspace.  */
void do_spacehyper (player, name)
	dbref player;
	char *name;
{
	dbref obj;
	int count;
	if ((obj = match_thing(player, name)) == NOTHING)
		return;
	if (power(player, POW_SPACE))
	{
		for(count=0;count < SHIPS; ++count)
			if (count == SHIPS)
				notify(player, "That object is not in space.");
			else if (fleet[count].obj == obj)
			{
				hyperspace(obj);
				notify (player, "Hyperspace function executed.");
				break;
			}
	}
	else
		notify(player, "You have to use a hyperdrive.");
}

/*  Called from game.c.  */
void do_spaceland(player, ship1, ship2)
	dbref player;
	char *ship1;
	char *ship2;
{
	dbref lander;
	dbref landie;
	char t1[10], t2[10];
	int i,j;
	if ((lander = match_thing(player, ship1)) == NOTHING) return;

	if ((landie = match_thing(player, ship2)) == NOTHING) return;
	if (!power(player, POW_SPACE)) {
		notify(player, "You have been given the power of 'space'.");
		return;
	} else {
		if ((i = find_ship(lander))==-1) return;
		if ((j = find_ship(landie))==-1) return;
		if (checkdock(i,j,1)) {
			notify(player, "The Eagle has landed!!");
			del_ship(lander);
			sprintf(t1, "#%d", lander);
			sprintf(t2, "#%d", landie);
			wptr[0]="Successfull Lander";
			wptr[1]=t2;
			did_it(SPACE_LORD, lander, NULL, 0, NULL, 0, A_ASHIP);
			wptr[0]="Successfull Landie";
			wptr[1]=t1;
			did_it(SPACE_LORD, landie, NULL, 0, NULL, 0, A_ASHIP);
			return;
		} else {
			notify(player, "Landing has failed.");
			wptr[0]="Failed Lander";
			did_it(SPACE_LORD, lander, NULL, 0, NULL, 0, A_ASHIP);
			wptr[0]="Failed Landie";
			did_it(SPACE_LORD, landie, NULL, 0, NULL, 0, A_ASHIP);
			return;
		}
	}
}

/* Function to read in a ships shields from the DB. */
void do_spaceshield (player, arg1)
	dbref player;
	char *arg1;
{
	dbref obj;
	int shipnum;
	struct ship *subj;
	if(!power(player, POW_SPACE)) {
		notify(player, "Permission denied.");
		return;
	}
	if ((obj = match_thing(player, arg1)) == NOTHING)
		return;
	if((shipnum = find_ship(obj))==-1) {
		notify(player, "Not in space.");
		return;
	}
	subj = &fleet[shipnum];
	subj->s_nav = atof(atr_get(obj, A_S0));
	subj->s_bsd = atof(atr_get(obj, A_S1));
	subj->s_bsk = atof(atr_get(obj, A_S2));
	subj->s_bpd = atof(atr_get(obj, A_S3));
	subj->s_bpk = atof(atr_get(obj, A_S4));
	subj->s_asd = atof(atr_get(obj, A_S5));
	subj->s_ask = atof(atr_get(obj, A_S6));
	subj->s_apd = atof(atr_get(obj, A_S7));
	subj->s_apk = atof(atr_get(obj, A_S8));
	notify(player, "Shields read.");
	return;
}

/* Function for tracking destinations automatically */
void do_spacetrack(player, ship1, ship2)
	dbref player;
	char *ship1;
	char *ship2;
{
	dbref obj1, obj2;
	int shipnum1, shipnum2;
	if(!power(player, POW_SPACE)) {
		notify(player, "What?! You serious?");
		return;
	}
	if ((obj1 = match_thing(player,ship1)) == NOTHING)
		return;
	if ((obj2 = match_thing(player,ship2)) == NOTHING)
		return;
	if ((shipnum1 = find_ship(obj1))==-1) {
		notify(player, "Ship 1 is not in space.");
		return;
	}
	if ((shipnum2 = find_ship(obj2))==-1) {
		notify(player, "Ship 2 is not in space.");
		return;
	}
	fleet[shipnum1].heading = abs_heading(fleet[shipnum1].location,
			fleet[shipnum2].location);
	notify(player, "Ship tracked.");
	return;
}

/*  Relocates a ship in space.  Used mostly for wormholes.  */
void do_spaceworm (player, name, argv)
	dbref player;
	char *name;
	char *argv[];
{
	dbref obj;
	int count;
	if ((obj = match_thing(player, name)) == NOTHING)
		return;
	if (!power(player, POW_SPACE))
		notify(player, "You have to use a wormdrive.");
	else
	{
		for(count=0; count < SHIPS; ++count)
			if (count == SHIPS)
				notify(player, "That object is not in space.");
			else if (fleet[count].obj == obj)
			{
				notify(player, "Ship jumped!");
				fleet[count].location.x = atof(argv[1]);
				fleet[count].location.y = atof(argv[2]);
				fleet[count].location.z = atof(argv[3]);
				write_ship(count);
				break;
			}
	}
}

/*  Sensor event.  */
void do_senevent(player, arg1, argv)
	char *arg1;
	char *argv[10];
	dbref player;
{
	struct coords loc;
	double dist;
	int count;
	if (!power(player, POW_SPACE))
		notify(player, "Permission Denied.");
	else
	{
		wptr[0]="Sensor";
		dist = atof(argv[1]);
		loc.x = atof(argv[2]);
		loc.y = atof(argv[3]);
		loc.z = atof(argv[4]);
		wptr[1] = arg1;
		for (count = 0; count < SHIPS; ++count)
			if ((fleet[count].obj != NOTHING) &&
					(!In_Hspace(count)))
			{
				if ((!fleet[count].sect.nebu) ||
						(!fleet[fleet[count].sect.nebu].s_bsd))
					if (distance3(loc, fleet[count].location) <= dist)
						did_it(SPACE_LORD, fleet[count].obj,
								NULL, 0, NULL, 0, A_ASHIP);
			}
		notify(player, "Sensor Event Done.");
		return;
	}
}

/*  Next functions determines which ships view an event which
	 occurs.  */
void do_visevent (player, arg1, argv)
	char *arg1;
	char *argv[10];
	dbref player;
{
	struct coords loc;
	double dist;
	int count;
	if (!power(player, POW_SPACE))
		notify(player, "Permission Denied.");
	else
	{
		wptr[0]="Visual";
		dist = atof(argv[1]);
		loc.x = atof(argv[2]);
		loc.y = atof(argv[3]);
		loc.z = atof(argv[4]);
		wptr[1] = arg1;
		for (count = 0; count < SHIPS; ++count)
			if ((fleet[count].obj != NOTHING) &&
					(!In_Hspace(count)))
			{
				if ((!fleet[count].sect.nebu) ||
						(!fleet[fleet[count].sect.nebu].s_bsk))
					if (distance3(loc, fleet[count].location) <= dist)
						did_it(SPACE_LORD, fleet[count].obj,
								NULL, 0, NULL, 0, A_ASHIP);
			}
		notify(player, "Visual Event Done.");
		return;
	}
}
/*   Com Event  */
/* !comevent <ship>=<dist>,<ch#>,<encrypt>,<id>,<msg> */
void do_comevent(player, arg1, argv)
	dbref player;
	char *arg1;
	char *argv[10];
{
	struct coords loc;
	double dist;
	int count, radio, shipflg = 0;
	dbref shipdb;
	char *tkn, *tkn2;
	char chan[1024];
	char return1[10],return2[10];

	if (!power(player, POW_SPACE)) {
		notify(player, "Permission Denied.");
		return;
	}
	shipdb = match_thing(player,arg1);
	if (shipdb == NOTHING || shipdb == AMBIGUOUS)
		return;
	shipflg=-1;
	for (count=0; count < SHIPS; ++count)
		if (fleet[count].obj == shipdb)
			shipflg=count;
	if (shipflg == -1) {
		notify(player, "That ship is not in space.");
		return;
	}
	if (In_Hspace(shipflg)) {
		notify(player, "Unable to transmit while in hyperspace.");
		return;
	}
	if ((fleet[shipflg].sect.nebu) &&
			(fleet[fleet[shipflg].sect.nebu].s_bpd)) {
		notify(player, "Transmission blocked.");
		return;
	}
	if (!strcmp(argv[2],"")) {
		notify(player, "You need to specify a channel.");
		return;
	}
	wptr[0]="Comm";
	dist = atof(argv[1]);
	if (dist < 0) {
		notify(player, "You must specify a positive distance.");
		return;
	}
	loc=fleet[shipflg].location;
	wptr[2]=argv[1];
	wptr[3]=argv[3];
	wptr[4]=argv[4];
	sprintf(return1,"#%d",shipdb);
	wptr[5]=return1;
	wptr[6]=argv[5];

	for (count=0;count < SHIPS; ++count)
		if ((fleet[count].obj != NOTHING) &&
				(fleet[count].obj != shipdb) &&
				(!In_Hspace(count)))
			if (distance3(loc, fleet[count].location) <= dist) {
				/* Guts */
				strcpy(chan,atr_get(fleet[count].obj,A_CHANNEL));
				if (strcmp(chan,"")) { /* Makes sure A_CHANNEL is not NULL */
					tkn = strstr(chan,argv[2]);
					while (tkn) {
						*tkn = '\0';
						radio = 0;
						tkn2 = strchr(chan,' ');
						while (tkn2) {
							radio++;
							tkn2 = strchr(tkn2+1,' ');
						}
						sprintf(return2,"%d",radio+1); /* This is the radio number */
						wptr[1]=return2;
						did_it(SPACE_LORD, fleet[count].obj, NULL, 0, NULL, 0, A_ASHIP);
						*tkn = '!';
						tkn = strstr(tkn,argv[2]);
					}
				}
			}
	notify(player, "Com Event Done.");
	return;
}

/*  The next 'fun_' functions are called by do_fun in eval.c,
	 they have been installed into space.c to localize code.  */

/*  Returns the value of the speed of light used with space().  */
void fun_c (buff, args)
	char *buff;
	char *args[10];
{
	sprintf(buff, "%f", (C * UPDATE));
	return;
}

/*  Function for converting degrees to radians.  */
void fun_dg2rd (buff,args)
	char *buff;
	char *args[10];
{
	sprintf(buff, "%8.6f", deg2rad(atof(args[0])));
	return;
}

/*  Function for converting radians to degrees.  */
void fun_rd2dg (buff,args)
	char *buff;
	char *args[10];
{
	sprintf(buff, "%6.2f", rad2deg(atof(args[0])));
	return;
}

/*  Function for converting kilometers to astronomical units.  */
void fun_km2au (buff,args)
	char *buff;
	char *args[10];
{
	sprintf(buff, "%10.2f", km2au(atof(args[0])));
	return;
}

/*  Function for converting astronomical units to kilometers.  */
void fun_au2km (buff,args)
	char *buff;
	char *args[10];
{
	sprintf(buff, "%17.0f", au2km(atof(args[0])));
	return;
}

/*  Function for converting kilometers to parsecs.  */
void fun_km2ps (buff,args)
	char *buff;
	char *args[10];
{
	sprintf(buff, "%6.2f", km2psec(atof(args[0])));
	return;
}

/*  Function for converting parsecs to kilometers. */
void fun_ps2km (buff,args)
	char *buff;
	char *args[10];
{
	sprintf(buff, "%17.0f", psec2km(atof(args[0])));
	return;
}

/*  Function for coverting kilometers to light-years.  */
void fun_km2ly(buff,args)
	char *buff;
	char *args[10];
{
	sprintf(buff, "%10.2f", km2ly(atof(args[0])));
	return;
}

/*  Function for coverting light-years to kilometers. */
void fun_ly2km (buff,args)
	char *buff;
	char *args[10];
{
	sprintf(buff, "%17.0f", ly2km(atof(args[0])));
	return;
}

/*  Function call for ks2ls.  */
void fun_ks2ls (buff, args)
	char *buff;
	char *args[10];
{
	sprintf(buff, "%7.4f", ks2ls(atof(args[0])));
	return;
}

/*  Function call for ls2ks.  */
void fun_ls2ks (buff, args)
	char *buff;
	char *args[10];
{
	sprintf(buff, "%13.2f", ls2ks(atof(args[0])));
	return;
}

/*  Function for determining distance from x1 y1 z1 to x2 y2 z2.  */
void fun_dist3d (buff,args)
	char *buff;
	char *args[10];
{
	struct coords pt1,pt2;
	pt1.x = atof(args[0]);pt1.y = atof(args[1]);pt1.z = atof(args[2]);
	pt2.x = atof(args[3]);pt2.y = atof(args[4]);pt2.z = atof(args[5]);
	sprintf(buff, "%17.0f", distance3(pt1,pt2));
	return;
}

/*  Function for determining absolute heading from x1 y1 z1
	 to x2 y2 z2.  */
void fun_head3d (buff,args)
	char *buff;
	char *args[10];
{
	struct coords pt1,pt2,pt3;
	pt1.x = atof(args[0]);pt1.y = atof(args[1]);pt1.z = atof(args[2]);
	pt2.x = atof(args[3]);pt2.y = atof(args[4]);pt2.z = atof(args[5]);
	pt3 = abs_heading(pt1,pt2);
	sprintf(buff, "%6.2f %6.2f %6.2f", rad2deg(pt3.x),
			rad2deg(pt3.y),rad2deg(pt3.z));
	return;
}

void fun_relhead (buff,args,player)
	char *buff;
	char *args[10];
	dbref player;
{
	struct coords pt1, pt2;
	dbref obj;
	int ship;
	if ((obj = match_thing(player, args[0])) == NOTHING)
	{
		strcpy(buff, "#-1");
		return;
	}
	if (power(player, POW_SPACE))
	{
		for (ship = 0; ship < SHIPS; ++ship)
			if (obj == fleet[ship].obj)
			{
				pt1.x = atof(args[1]);pt1.y = atof(args[2]);pt1.z = atof(args[3]);
				pt2 = rel_heading(&fleet[ship], pt1);
				sprintf(buff, "%6.2f %6.2f %6.2f", rad2deg(pt2.x),
						rad2deg(pt2.y),rad2deg(pt2.z));
				return;
			}
	}
	else
	{
		strcpy(buff, "Permission denied.");
		return;
	}
}

/*  Function for determining inertial heading.  */
void fun_velhdg (buff,args)
	char *buff;
	char *args[10];
{
	struct coords pt1,pt2,pt3;
	pt1.x = 0.0; pt1.y = 0.0; pt1.z = 0.0;
	pt2.x = atof(args[0]);pt2.y = atof(args[1]);pt2.z = atof(args[2]);
	pt3 = abs_heading(pt1,pt2);
	sprintf(buff, "%6.3f %6.3f", rad2deg(pt3.x),rad2deg(pt3.y));
	return;
}

/*  Function for determining absolute velocity.  */
void fun_velmag (buff,args)
	char *buff;
	char *args[10];
{
	struct coords pt1;
	pt1.x = atof(args[0]);pt1.y = atof(args[1]);pt1.z = atof(args[2]);
	sprintf(buff, "%13.2f", vect_mag(pt1));
	return;
}

/*  Function for determining relative Phi to object.  */
void fun_relphi (buff,args)
	char *buff;
	char *args[10];
{
	double fin;
	struct coords pos,vel;
	pos.x = atof(args[0]);pos.y = atof(args[1]);pos.z = atof(args[2]);
	vel.x = atof(args[3]);vel.y = atof(args[4]);vel.z = atof(args[5]);
	fin = relvelangle(pos,vel);
	sprintf(buff, "%10.6f", fin);
	return;
}

/*  Function to obtain orbital information.  */
void fun_orbit (buff,args)
	char *buff;
	char *args[10];
{
	char string[80];
	double mass,dist,vel,ang;
	mass = atof(args[0]);dist = atof(args[1]);
	vel  = atof(args[2]);ang  = atof(args[3]);
	orbit(string,mass,dist,vel,ang);
	strcpy(buff, string);
	return;
}

/*  Function to sync 'ticks' in the queue to the space clock.  */
void fun_sync(buff,args)
	char *buff;
	char *args[10];
{
	int wait;
	if (halt_space == 0) {
		sprintf(buff, "#-1");
		return;
	}
	wait = atoi(args[0]);
	wait=((wait * SPACE_INTERVAL) + (SPACE_INTERVAL - space_count));
	sprintf(buff, "%d", wait);
	return;
}

/* Function to return the facing of a planet closest to a ship. */
void fun_face (buff, args, player)
	char *buff;
	char *args[10];
	dbref player;
{
	int face, count, planet;
	dbref obj1, obj2;
	struct coords ship_loc;
	/*  if (strcmp(args[0],"6") && strcmp(args[0],"8")) {
		 strcpy(buff, "#-1");
		 return;
		 } */
	if (((obj1 = match_thing(player, args[1])) == NOTHING) ||
			((obj2 = match_thing(player, args[2])) == NOTHING)) {
		strcpy(buff, "#-1");
		return;
	}
	if (power(player, POW_SPACE))
	{
		for (count = 0; count <= SHIPS; ++count)
			if (obj1 == fleet[count].obj) {
				planet = count;
				count = 0;
				break;
			}
		if (count >= SHIPS) {
			strcpy(buff, "#-1");
			return;
		}
		for (count = 0; count <= SHIPS; ++count)
			if (obj2 == fleet[count].obj) {
				ship_loc = fleet[count].location;
				count = 0;
				break;
			}
		if (count >= SHIPS) {
			strcpy(buff, "#-1");
			return;
		}
		if (!strcmp(args[0], "6"))
			face = face_d6(planet, ship_loc);
		else
			face = face_d8(planet, ship_loc);
		sprintf(buff, "%d", face);
		return;
	} else {
		strcpy(buff, "Permission denied.");
		return;
	}
}

/*  Function to output the number of updates that have passed. */
void fun_updates(buff,args)
	char *buff;
	char *args[10];
{
	if (halt_space == 0) {
		sprintf(buff, "#-1");
		return;
	}
	sprintf(buff, "%ld", update_count);
	return;
}

/*  Function for determining what is in sensor range from current
	 position.  */
void fun_inrange (buff,args,player)
	char *buff;
	char *args[10];
	dbref player;
{
	char ship_str[SHPSTR];
	dbref obj;
	if ((obj = match_thing(player, args[0])) == NOTHING)
	{
		strcpy(buff, "#-1");
		return;
	}
	if (power(player, POW_SPACE))
	{
		sense_sweep(obj, ship_str);
		strcpy(buff, ship_str);
		return;
	}
	else
	{
		strcpy(buff, "Permission denied.");
		return;
	}
}

/*  Function for determining what is in sight of another ship.  */
void fun_insight (buff,args,player)
	char *buff;
	char *args[10];
	dbref player;
{
	char ship_str[SHPSTR];
	double mag;
	dbref obj;
	if ((obj = match_thing(player, args[0])) == NOTHING)
	{
		strcpy(buff, "#-1");
		return;
	}
	mag=atof(args[1]);
	if(mag<=0) mag=1;
	if (power(player, POW_SPACE))
	{
		vis_range(obj, ship_str,mag);
		strcpy(buff, ship_str);
		return;
	}
	else
	{
		strcpy(buff, "Permission denied.");
		return;
	}
}

/*  Function to tell if an object *is* in space. (boolean)  */
void fun_inspace (buff,args,player)
	char *buff;
	char *args[10];
	dbref player;
{
	dbref obj;
	int ship;
	if ((obj = match_thing(player, args[0])) == NOTHING)
	{
		strcpy(buff, "#-1");
		return;
	}
	if (power(player, POW_SPACE))
	{
		for (ship = 0; ship < SHIPS; ++ship)
			if (obj == fleet[ship].obj)
			{
				strcpy(buff, "1");
				return;
			}
		strcpy(buff, "0");
		return;
	}
	else
	{
		strcpy(buff, "Permission denied.");
		return;
	}
}

/*  Function to give a list of ships within a certain distance from a obj.  */
void fun_indist (buff,args,player)
	char *buff;
	char *args[10];
	dbref player;
{
	char ship_str[SHPSTR];
	dbref obj;
	double dist;
	dist = atof(args[1]);
	if ((obj = match_thing(player, args[0])) == NOTHING)
	{
		strcpy(buff, "#-1");
		return;
	}
	if (power(player, POW_SPACE))
	{
		dist_check(obj, dist, ship_str);
		strcpy(buff, ship_str);
		return;
	}
	else
	{
		strcpy(buff, "Permission denied.");
		return;
	}
}

/* internal function to determine if a string will make a valid float value */
int isfloat (tstr)
	char *tstr;
{
	int i = 0;

	for (; i < strlen(tstr); i++)
	{
		if (!isdigit(tstr[i]) && tstr[i] != ' ' && tstr[i] != '-' && tstr[i] != '.' && tstr[i] != 'e' && tstr[i] != 'E')
		{
			return 0;
		}
	}

	return 1;
}

/* The following two functions were written by Kevin Kane (aka Frnkzk)
	and are not subject to copyright restrictions. */

/* acctime(thrust, mass, starting velocity, ending velocity)
	spacey function.. calculates how long it will take to get from one
	speed to another -Frnkzk */
void fun_acctime(buff, args, privs)
	char *buff;
	char *args[10];
	dbref privs;
{
	int updates = 0; /* how long it will take */
	double thrust, mass, startvel, endvel; /* inputted */
	double accel = 0;

	thrust = atof(args[0]);
	mass = atof(args[1]);
	startvel = atof(args[2]);
	endvel = atof(args[3]);

	if (startvel > endvel) {
		double temp;
		temp = startvel;
		startvel = endvel;
		endvel = temp; /* startvel must be < or = endvel */
	}

	/* checks to make sure we don't go into an infinite loop */
	/* unlike relacc, thrust MUST be positive. the above check deals
		with slowing down instead of speeding up */
	if (thrust <= 0 || mass <= 0) {
		sprintf(buff, "#-1");
		return;
	}

	/* We will never reach C - Fix by MM 3/30/96 */
	/* Modified so that velocity is C*UPDATE, not C, since we measure in kpu
	 * Fix by KK 7/29/97 */
	if (endvel >= C*UPDATE) {
		sprintf(buff, "Inf");
		return;
	}

	while (startvel < endvel) { /* don't execute if they're = or s > e */
		accel = ((thrust / mass) *
				(1.0 - (startvel*startvel / (C*C*SPACE_INTERVAL*SPACE_INTERVAL))));
		startvel += accel;
		updates++;
	}

	sprintf(buff, "%d", updates);
}

/* relacc(thrust, mass, starting velocity, updates) */
/* spacey function.. like acc, except it accounts for relativity -Frnkzk */
/* if thrust is with vel, thrust is positive. if thrust is against vel,
	thrust is negative. */
void fun_relacc(buff, args, privs)
	char *buff;
	char *args[10];
	dbref privs;
{
	double distance = 0, accel = 0; /* internal vars */
	double thrust, mass, velocity; /* inputted stuff */
	int updates, counter; /* inputted updates, update counter */

	thrust = atof(args[0]);
	mass = atof(args[1]);
	velocity = atof(args[2]);
	updates = atoi(args[3]);

	for (counter = 0; counter < updates; counter++) {
		accel = ((thrust / mass) *
				(1.0 - (velocity*velocity / (C*C*SPACE_INTERVAL*SPACE_INTERVAL))));
		velocity += accel;
		distance += velocity;
	}

	sprintf(buff, "%.0f", distance);
}

/* There's no slick way for when one has a zone object number one can easily
 * get the number of the space object.  This is the ugly way. -Frnkzk */
void fun_zone2obj(buff, args, privs)
	char *buff;
	char *args[10];
	dbref privs;
{
	dbref thing; int i;

	if (!power(privs, POW_SPACE)) {
		notify(privs, "Permission denied.");
		sprintf(buff, "#-1");
		return;
	}

	thing = match_thing(privs, args[0]);

	if (thing == NOTHING) {
		sprintf(buff, "#-1");
		return;
	}

	/* space objs with no surface use the Space Zone. */
	if (thing == (dbref)6117) {
		sprintf(buff, "#-1");
		return;
	}

	/* This assumes that all spaceships are direct children of the ship parent.
	 * If they are not (i.e., they are children of a child of the ship parent),
	 * this won't find them.  As far as I know all spaceships have to have the
	 * parent directly on them.
	 */
	for (i = 0; db[SHIP_PARENT].children[i] != NOTHING; i++) {
		dbref thing2;
		/* dbref bullshit; */
		ATTR *zone;

		/*    if (!parse_attrib(SPACE_LORD, tprintf("#%d/#%d.Zone",
				db[SHIP_PARENT].children[i],
				SHIP_PARENT),
				&bullshit, &zone, 0))*/
		if ((zone = atr_str(SPACE_LORD, db[SHIP_PARENT].children[i],
						tprintf("#%d.Zone", SHIP_PARENT))) == NULL) {
			log_space(tprintf("Unable to find a Zone attribute for #%d",
						db[SHIP_PARENT].children[i]));
			continue;
		}

		/*    thing2 = match_thing(SPACE_LORD, atr_get(db[SHIP_PARENT].children[i],
				zone));*/
		thing2 = atoi(atr_get(db[SHIP_PARENT].children[i], zone) + 1);

		if (thing2 == thing) {
			sprintf(buff, "#%d", db[SHIP_PARENT].children[i]);
			return;
		}
	}

	sprintf(buff, "#-1"); /* this should happen only if it isn't a zone */
	return;
}

#if 0
/* The functions below have not yet been integrated and/or debuged. -PA */

void collision_bounce(count,count2)
	int count,count2;
{
	struct ship *i;
	struct ship *j;
	struct coords relvel;
	struct coords impact_point;
	double closest_dist; /* closest distance between the two objects */
	double closest_lead; /* distance along movement path to closest point */
	double impact_dist; /* distance at exact point of impact */
	double impact_lead; /* distance along movement path to impact point */
	double dist; /* distance between two objects at start */

	dist = distance3(i->oldloc,j->oldloc);

	relvel = vect_diff(vect_diff(i->oldloc,i->location),
			vect_diff(j->oldloc,j->location));
	/*  Check if course is in line with a body in space.  */
	closest_dist = linept_dist(vect_diff(i->location,i->location),
			relvel, vect_diff(i->oldloc,j->oldloc));
	/*  Check if the radius of object count contains the
		 segment between the two endpoints.
		 if ((vect_mag(relvel) >= distance3(i->oldloc,j->oldloc)) &&
		 (vect_mag(relvel) >= distance3(i->location,j->location)))
	 */
	impact_dist = i->radius + j->radius;
	impact_lead = fsqrt(impact_dist*impact_dist - closest_dist*closest_dist);
	closest_lead = fsqrt(dist*dist - closest_dist*closest_dist);
	impact_point.x = (relvel.x/vect_mag(relvel)) * (vect_mag(relvel) -
			(closest_lead - impact_lead)) + i->oldloc.x;
	impact_point.y = (relvel.y/vect_mag(relvel)) * (vect_mag(relvel) -
			(closest_lead - impact_lead)) + i->oldloc.y;
	impact_point.z = (relvel.z/vect_mag(relvel)) * (vect_mag(relvel) -
			(closest_lead - impact_lead)) + i->oldloc.z;
	i->linvel.x += (



			void line_of_sight()
			int source;		/* ship # doing the line of sight */
			int *visible;		/* array of ships that can be seen so far */
			int vis_count;		/* count of the visible array length */
			{
			int count,count2,countx,county;
			struct ship *i;
			struct ship *j;
			struct ship *k;
			k=&fleet[source];
			for(count=0;count < (vis_count-1) && visible[count]!=NOTHING;count++)
			for(count2=count+1;count2 < vis_count && visible[count2]!=NOTHING;count2++) {
			countx=count;
			county=count2;
			i=&fleet[visible[countx]];
			j=&fleet[visible[county]];
			/* check who's in 'front' of the other.. Put them first in check */
			if(distance3(i->location,k->location) - i->radius >=
				distance3(j->location,k->location) - j->radius) {
				countx=count2;
				county=count;
				i=&fleet[visible[countx]];
				j=&fleet[visible[county]];
			}

			/* check angles to see if 'j' is hidden by 'i' */
			if(relphi(vect_diff(i->location,k->location),
						vect_diff(j->location,k->location)) +
					absolute_heading(0,0,0,j->radius,0,0) <=
					absolute_heading(0,0,0,i->radius,0,0)) {
				visible[county] = NOTHING;
			}
			if(visible[count] == NOTHING) break;
			}
			}
}
*/
#endif
/*  END of space.c code.  */

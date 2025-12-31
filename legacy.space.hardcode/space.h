/*  space.h: Header file for space.c  */

/*-------------------------------------------------------------------------*/
/*  MUSE-Space(c) was taken from a personal project concieved, written     */
/*  and copyrighted (1992-93) by Mark Wilkinson <mark@towerravens.com>,    */
/*  aka Yarus on MicroMUSE.                                                */
/*                                                                         */
/*  It was co-written and adapted for TinyMUSE under permission of the     */
/*  afore mentioned by Michael Majere <mike@towerravens.com>, aka          */
/*  Priam_Agrivar on MicroMUSE.                                            */
/*                                                                         */
/*  Additional Coders: Eric Wallace, aka Erk; Carrie Gram, aka S'lar, and  */
/*  Kevin Kane, aka Frnkzk (of MicroMUSE).                                 */
/*                                                                         */
/*  Permission is given by the author to use and/or modify this code for   */
/*  non-profit purposes only. The author requests that any bug fixes or    */
/*  improvement to the code be shared with all.                            */
/*-------------------------------------------------------------------------*/

#ifndef __SPACE_H
#define __SPACE_H

/*  Version of space.c being used.  */
#define SPACE_VERSION "MUSE-Space(c) v1.1"

/*  These are the variables for use with space.c, you should know what
    you are doing BEFORE you change any of these.  */

/*  Seconds (ticks) between updates.  */
#define SPACE_INTERVAL 10

/*  Maximum number of objects allowed in space.  */
#define MAX_SHIPS 200

/*  Maximum distance to outer marker (5 light years). 1.42E14 - 5% */
#define MAX_DIST 1.349E14

/*  Maximum distance for sensor sweep.  */
#define MAX_SENSE 4.73E13

/*  Top size of ship array.  */
#define SHPSTR (MAX_SHIPS*30)

/*  Declarations for output.  */
extern char *strstr(const char *, const char *);
extern struct log space_log;
#define log_space(str) muse_log(&space_log, (str))

/*  Macros.  */
#define Ship(x) ((Typeof(x) == TYPE_THING) && (db[x].owner == SPACE_LORD) \
                && (!(db[x].flags & HAVEN)||!(strcmp(atr_get(x,A_TYPE),"SB")))\
                && is_a(x, SHIP_PARENT))

#define In_Hspace(x) (!strcmp(fleet[x].sect.name, "HS"))

/*  Global variables.  */
int halt_space;
int space_count;
long update_count;

/*  Global structures.  */
struct coords
  /* Currently the program is set up to run at 64 bit precision
  by running the coords as a 'double', providing a range of
  1.7E-308 to 1.7E+308.  If the program needs more precision it
  may be set to 80 bit by making this a 'long double' providing
  a range of 3.4E-4932 to 1.1E+4932. */
  {
    double x,y,z;
  };
struct ref
  {
    char name[12];
    int numb;
    int nebu;
  };

/*  >> External Prototypes <<  */

extern void dump_space P((void));
extern void update_space P((void));
extern void do_spaceboot P((dbref));
extern void do_spacecont P((dbref));
extern void do_spacedata P((dbref, char *));
extern void do_spacedock P((dbref, char *, char *));
extern void do_spaceenter P((dbref, char *));
extern void do_spaceexit P((dbref, char *));
extern void do_spaceexplode P((dbref, char *));
extern void do_spacegrav P((dbref, char *, char **));
extern void do_spacehalt P((dbref));
extern void do_spacehelp P((dbref));
extern void do_spacehyper P((dbref, char *));
extern void do_spaceland P((dbref, char *, char *));
extern void do_spaceshield P((dbref, char *));
extern void do_spacetrack P((dbref, char *, char *));
extern void do_spaceworm P((dbref, char *, char **));
extern void do_senevent P((dbref, char *, char **));
extern void do_visevent P((dbref, char *, char **));
extern void do_comevent P((dbref, char *, char **));
extern void fun_c P((char *, char **));
extern void fun_dg2rd P((char *, char **));
extern void fun_rd2dg P((char *, char **));
extern void fun_km2au P((char *, char **));
extern void fun_au2km P((char *, char **));
extern void fun_km2ps P((char *, char **));
extern void fun_ps2km P((char *, char **));
extern void fun_km2ly P((char *, char **));
extern void fun_ly2km P((char *, char **));
extern void fun_ks2ls P((char *, char **));
extern void fun_ls2ks P((char *, char **));
extern void fun_dist3d P((char *, char **));
extern void fun_head3d P((char *, char **));
extern void fun_relhead P((char *, char **, dbref));
extern void fun_velhdg P((char *, char **));
extern void fun_velmag P((char *, char **));
extern void fun_relphi P((char *, char **));
extern void fun_orbit P((char *, char **));
extern void fun_sync P((char *, char **));
extern void fun_face P((char *, char **, dbref));
extern void fun_updates P((char *, char **));
extern void fun_inrange P((char *, char **, dbref));
extern void fun_insight P((char *, char **, dbref));
extern void fun_inspace P((char *, char **, dbref));
extern void fun_indist P((char *, char **, dbref));
extern void fun_acctime P((char *, char **, dbref));
extern void fun_relacc P((char *, char **, dbref));
extern void fun_zone2obj P((char *, char **, dbref));
extern void log_space P((char *));

#endif /* __SPACE_H */

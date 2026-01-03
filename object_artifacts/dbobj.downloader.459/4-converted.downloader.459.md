# `Downloader`

## Attribute list (MARE2 conversion)

```mud
@@ -----------------------------
@@ OBJECT: Downloader(#459)
@@ LOCATION: Ptah(#5745)
@@ -----------------------------

---cut---
@@ Teleport to object location as a convenience
@teleport me=#5745
---cut---

@@ ATTRIBUTE: Downloader/divby
@@ --------------------------

---cut---
@defattr #459/divby=inherit
---cut---
&divby #459=1000000
---cut---

@@ ATTRIBUTE: Downloader/flte()
@@ ---------------------------

---cut---
@defattr #459/flte()=inherit function
---cut---
&flte() #459=[lnot(match(fcomp(v(1),v(0)),-1))]
---cut---

@@ ATTRIBUTE: Downloader/get_obj_color()
@@ ------------------------------------

---cut---
@defattr #459/get_obj_color()=inherit function
---cut---
&get_obj_color() #459=[ifelse(flte(v(0),3E28),ifelse(flte(v(0),8E24),ifelse(flte(v(0),2E23),ifelse(flte(v(0),5E16),ifelse(flte(v(0),1E8),8,7),9),2),4),14)]
---cut---

@@ ATTRIBUTE: Downloader/get_obj_type()
@@ -----------------------------------

---cut---
@defattr #459/get_obj_type()=inherit function
---cut---
&get_obj_type() #459=[ifelse(flte(v(0),3E28),ifelse(flte(v(0),8E24),ifelse(flte(v(0),2E23),ifelse(flte(v(0),5E16),ifelse(flte(v(0),1E8),Ship,Station),Moon),Terran),Jovian),Star)]
---cut---

@@ ATTRIBUTE: Downloader/get_obj_size()
@@ -----------------------------------

---cut---
@defattr #459/get_obj_size()=inherit function
---cut---
&get_obj_size() #459=[ifelse(flte(v(0),3E28),ifelse(flte(v(0),8E24),ifelse(flte(v(0),2E23),ifelse(flte(v(0),5E16),ifelse(flte(v(0),1E8),1,2),4),8),16),32)]
---cut---

@@ ATTRIBUTE: Downloader/spit_data()
@@ --------------------------------

---cut---
@defattr #459/spit_data()=inherit function
---cut---
&spit_data() #459=[histname(v(!),v(0))]|[fdiv(dx(v(us),v(0)),v(divby))]|[fdiv(dy(v(us),v(0)),v(divby))]|[fdiv(dz(v(us),v(0)),v(divby))]|[get_obj_type(get(v(0),mass))]|[get_obj_color(get(v(0),mass))]|[get_obj_size(get(v(0),mass))]|
---cut---

@@ ATTRIBUTE: Downloader/see_if()
@@ -----------------------------

---cut---
@defattr #459/see_if()=inherit function
---cut---
&see_if() #459=
  if scomp(get(v(sensor_memory),strcat(memory,v(0))),NO MATCH)=1
    @@ already present, do nothing
  else
    @pemit [v(2)]=[spit_data(v(0),v(1))]
  endif
---cut---

@@ ATTRIBUTE: Downloader/DownLoad
@@ -----------------------------

---cut---
@defattr #459/DownLoad=inherit
---cut---
&DownLoad #459=:1$download:
  @@ Legacy loop semantics: iterates inrange(v(us)) plus a literal '#'
  for i__=[inrange(v(us))] #
    set 0=v(i__)
    switch v(0)
      case #
        print [name(v(us))]|0.00|0.00|0.00|Ship|8|1
        break
      default
        call me/see_if=v(0),v(1),%#
        break
    endswitch
  done
---cut---
```

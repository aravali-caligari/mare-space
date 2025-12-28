# 

## Name

## Purpose

## Meta data

```mud
PA's temp dash(#1022V)
Owner: Ptah
Type: Thing  Flags: Visible
Bytes: 954
Plane: 0
Location: Transmat Equipment Room(#53399R)
Home: Director of Space Administration(#23415RJ)
```

## Object Definition

### Attribute definitions

```mud
dash(): inherit function
4wordash(): inherit function
3wordash(): inherit function
1wordash(): inherit function
2wordash(): inherit function
```

### Attribute list

```mud
dash():[ifelse(truth(gt(wcount(v(0)),4)),#-1,ifelse(truth(gt(wcount(v(0)),3)),4
wordash(v(0)),ifelse(truth(gt(wcount(v(0)),2)),3wordash(v(0)),ifelse(truth(gt(w
count(v(0)),1)),2wordash(v(0)),v(0)))))]
4wordash():[edit(v(0),v(0),strcat(strcat(strcat(strcat(strcat(strcat(first(v(0)
),_),extract(v(0),2,1)),_),extract(v(0),3,1)),_),extract(v(0),4,1)))]
3wordash():[edit(v(0),v(0),strcat(strcat(strcat(strcat(first(v(0)),_),extract(v
(0),2,1)),_),extract(v(0),3,1)))]
1wordash():[v(0)]
2wordash():[edit(v(0),v(0),strcat(strcat(first(v(0)),_),rest(v(0))))]
```


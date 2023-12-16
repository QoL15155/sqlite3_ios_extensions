# iOS extensions for SQLite

Useful extensions for analyzing iOS databases (core data). These can be use with **DB Browser for SQLite**.

Supported for both linux and windows.

# How to use

## DB Browser

Loading Extension
+ One-time 
    + Tools -> "Load Extension"
+ Permanent:
    + Edit -> Preferences -> Extensions -> 

Edit column to add extension or -

Execute SQL
``` sql
select storaged(ZCOLUMN) from ZTABLE;
```


## SQLite3 shell:
``` shell
sqlite3 database.db
# From inside the shell
.load ./ios
```

# Features

+ `storaged(col_name)` : Read Core-Data format for external stored (backed up) binaries.

# Compilation

Directories
+ `include/` : Contains sqlite3 mandatory include files. Do NOT touch this folder!
+ `out/` : Compilation output

## Linux

``` shell
gcc -g -fPIC -shared ios.c  -o ios.so
```
# iOS extensions for SQLite

Useful extensions for analyzing iOS databases (core data). These can be use with **DB Browser for SQLite**.

Supported for both linux and windows.

# How to use

## DB Browser

Loading the extension
+ One-time 
    + Tools -> "Load Extension"
+ Permanent:
    + Edit -> Preferences -> Extensions -> 

*Browse Data*: Edit the column's display format:
![DB Browser diff](https://github.com/QoL15155/sqlite3_ios_extensions/assets/13380824/6b1323af-fff7-442e-858b-96cf3a2cdb9e)

*Execute SQL*: run a query
``` sql
select storaged(ZCOLUMN) from ZTABLE;
```


## SQLite3 shell:
``` sh
sqlite3 database.db
# From inside the shell
.load ./ios
```

# Features

+ `storaged(col_name)` : Read Core-Data format for external stored (backed up) binaries.

# Compilation

Instructions are in [BUILDING](BUILDING.md)

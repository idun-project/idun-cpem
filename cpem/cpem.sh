#!/bin/bash
export CPMFS=$HOME/CPM
setfacl -d -m u:cpm:rwx,g:idun:rwx,o::rx $CPMFS
cd $CPMFS
exec ./cpem.bin

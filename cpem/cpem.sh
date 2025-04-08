#!/bin/bash
export CPMFS=/home/idun/idun-base/cpm
source /etc/profile.d/z88dk.sh
setfacl -d -m u:cpm:rwx,g:idun:rwx,o::rx $CPMFS
cd $CPMFS
exec ./cpem

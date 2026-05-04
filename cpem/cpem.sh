#!/bin/bash
export CPMFS=/home/idun/CPM
cd $CPMFS
umask 0002
exec cpem.bin

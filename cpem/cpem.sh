#!/bin/bash
export CPMFS=$HOME/CPM
cd $CPMFS
umask 0002
exec cpem.bin

\#!/bin/bash
export LD_LIBRARY_PATH=.
#gdb -d ~/Projects/games/github/capengine -s libcapengine.so spacecombat
gdb -ex "dir ~/Projects/games/github/capengine" spacecombat




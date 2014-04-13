#!/bin/bash
export LD_LIBRARY_PATH=.
valgrind --tool=callgrind ./spacecombat

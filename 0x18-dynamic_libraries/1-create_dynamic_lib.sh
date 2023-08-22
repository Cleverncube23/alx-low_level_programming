#!/bin/bash

gcc -fPIC -shared $(ls *.c) -o liball.so

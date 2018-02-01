#!/bin/sh
rm -f gerbers.zip
zip -r gerbers.zip *.g{t,b}{l,s,o} *.{gm1,drl}

#!/bin/bash

for run in {1..100}; do
  ./Debug/3/occ-c90 3/main-c90.c > occ-c90.txt
done
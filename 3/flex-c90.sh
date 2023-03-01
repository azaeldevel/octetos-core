#!/bin/bash

for run in {1..100}; do
  ./Debug/3/develop-lexer-flex-c90 < 3/main-c90.c > flex-c90.txt
done
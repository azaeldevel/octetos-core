#!/bin/bash

echo "OCC Lexer"
time 3/occ-c90.sh

echo ""
echo "Flex lexer"
time 3/flex-c90.sh
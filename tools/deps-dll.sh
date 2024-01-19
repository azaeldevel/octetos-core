#!/bin/sh

list=`ntldd $1`
readarray -t lines <<<"$list"
#echo ${lines[0]}
for line in "${lines[@]}"
do
  #echo "Dep : $line"
  dll=`sed 's/[^"]*\(C:[^"]*.dll\) ([^"]*)/\1/' <<< "$line"`
  mkdir -p $2
  cp $dll $2
done
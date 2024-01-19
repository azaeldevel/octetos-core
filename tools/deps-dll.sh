#!/bin/sh

if [ -z "$1" ]
then
	echo "deps-dll 'dll' 'dir to copy'"
	exit
fi
if [ -z "$2" ]
then
	echo "deps-dll 'dll' 'dir to copy'"
	exit
fi

list=`ntldd $1`
readarray -t lines <<<"$list"
#echo ${lines[0]}
for line in "${lines[@]}"
do
  #echo "Dep : $line"
  dll=`sed 's/[^"]*\(C:[^"]*.dll\) ([^"]*)/\1/' <<< "$line"`
  mkdir $2
  cp $dll $2
done
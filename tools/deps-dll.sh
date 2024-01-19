#!/bin/sh

if [ -z "$1" ]
then
	echo "Usage:\tdeps-dll [library] [directory]"
	exit
fi
if [ -z "$2" ]
then
	echo "Usage:\tdeps-dll [library] [directory]"
	exit
fi

list=`ntldd $1`
readarray -t lines <<<"$list"
#echo ${lines[0]}
mkdir $2
for line in "${lines[@]}"
do
	dll=`sed 's/[^"]*\(C:[^"]*.dll\) ([^"]*)/\1/' <<< "$line"`
	WINDIR="$(dirname "${dll}")"
	#echo "dir:$WINDIR"
	if [ "$WINDIR" = "C:\Windows\SYSTEM32" ]; then
		continue
	fi
	echo "copiying $dll"
	cp $dll $2
done
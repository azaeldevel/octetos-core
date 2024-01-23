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
mkdir -p $2
for line in "${lines[@]}"
do
	dll=`sed 's/[^"]*\(C:[^"]*.dll\) ([^"]*)/\1/' <<< "$line"`
	WINDIR="$(dirname "${dll}")"
	WINFILE="$(basename "${dll}")"
	if [ -f "$2/$WINFILE" ] ; then
		echo "Skiping $dll.."
		continue
	fi
	#echo "dir:$WINDIR"
	if [ "$WINDIR" = "C:\Windows\SYSTEM32" ]; then
		continue
	fi
	if ! [ -f "$dll" ] ; then
		echo "$dll"
		continue
	fi
	echo "Procesando $dll.."
	cp -v $dll $2
	$0 $dll $2
done
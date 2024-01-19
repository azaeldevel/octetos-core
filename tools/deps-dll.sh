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
	case $dll in
		"C:\Windows\SYSTEM32\ADVAPI32.dll")
			continue
		;;
		"C:\Windows\SYSTEM32\KERNEL32.dll")
			continue
		;;
	esac
	echo $dll
	cp $dll $2
done
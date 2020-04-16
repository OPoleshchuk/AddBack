#!/bin/bash

#Author: Oleksii Poleshchuk
#
#KU Leuven 2016-2020
#
# This script is used for automatic add-back for the all files
# generated with SpecMATscint by replacing the file name "fileN = " value
# in the AddBack.h file.
#
# \file AddBackLoop.sh
#

iterator=10
while [ $iterator -le 14000 ]
do

if [ $iterator -lt 1000 ]
then
	ba="CeBr3_48mmx48mmx48mm_15x1x3crystals_R131.25mm_gamma0"
elif [ $iterator -ge 1000 ]
then
	ba="CeBr3_48mmx48mmx48mm_15x1x3crystals_R131.25mm_gamma"
fi

if [ $iterator -lt 100 ]
then
	caflt=$( bc <<< "scale=2; (($iterator)/(1000))")
elif [ $iterator -eq 100 ]
then
	caflt=$( bc <<< "scale=1; (($iterator)/(1000))")
elif [ $iterator -gt 100 ] && [ $iterator -lt 200 ]
then
	caflt=$( bc <<< "scale=2; (($iterator)/(1000))")
elif [ $iterator -eq 200 ]
then
	caflt=$( bc <<< "scale=1; (($iterator)/(1000))")
elif [ $iterator -gt 200 ] && [ $iterator -lt 300 ]
then
	caflt=$( bc <<< "scale=2; (($iterator)/(1000))")
elif [ $iterator -ge 300 ] && [ $iterator -lt 1000 ]
then
	caflt=$( bc <<< "scale=1; (($iterator)/(1000))")
elif [ $iterator -eq 1000 ]
then
	caflt=$( bc <<< "scale=0; (($iterator)/(1000))")
elif [ $iterator -gt 1000 ] && [ $iterator -lt 2000 ]
then
	caflt=$( bc <<< "scale=1; (($iterator)/(1000))")
elif [ $iterator -ge 2000 ]
then
	caflt=$( bc <<< "scale=0; (($iterator)/(1000))")
fi

ca=$caflt

ea=$ba$ca

if [ $iterator -lt 300 ]
then
	((iterator=iterator+10))
elif [ $iterator -ge 300 ] && [ $iterator -lt 2000 ]
then
	((iterator=iterator+100))
elif [ $iterator -ge 2000 ]
then
	((iterator=iterator+1000))
fi

if [ $iterator -lt 1000 ]
then
	ba="CeBr3_48mmx48mmx48mm_15x1x3crystals_R131.25mm_gamma0"
elif [ $iterator -ge 1000 ]
then
	ba="CeBr3_48mmx48mmx48mm_15x1x3crystals_R131.25mm_gamma"
fi

if [ $iterator -lt 100 ]
then
	cbflt=$( bc <<< "scale=2; (($iterator)/(1000))")
elif [ $iterator -eq 100 ]
then
	cbflt=$( bc <<< "scale=1; (($iterator)/(1000))")
elif [ $iterator -gt 100 ] && [ $iterator -lt 200 ]
then
	cbflt=$( bc <<< "scale=2; (($iterator)/(1000))")
elif [ $iterator -eq 200 ]
then
	cbflt=$( bc <<< "scale=1; (($iterator)/(1000))")
elif [ $iterator -gt 200 ] && [ $iterator -lt 300 ]
then
	cbflt=$( bc <<< "scale=2; (($iterator)/(1000))")
elif [ $iterator -ge 300 ] && [ $iterator -lt 1000 ]
then
	cbflt=$( bc <<< "scale=1; (($iterator)/(1000))")
elif [ $iterator -eq 1000 ]
then
	cbflt=$( bc <<< "scale=0; (($iterator)/(1000))")
elif [ $iterator -gt 1000 ] && [ $iterator -lt 2000 ]
then
	cbflt=$( bc <<< "scale=1; (($iterator)/(1000))")
elif [ $iterator -ge 2000 ]
then
	cbflt=$( bc <<< "scale=0; (($iterator)/(1000))")
fi
cb=$cbflt

eb=$ba$cb

ga="s/$ea/$eb/g"
echo -e "s/$ea/$eb/g"
sed -i "s/$ea/$eb/g" ./AddBack.h
#echo -e "s/$ea/$eb/g"

root -l <<-EOF
.L AddBack.c
 AddBack y
y.Loop()
.q
EOF

done

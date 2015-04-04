#!/bin/bash

# Word find executable
EXE=./self-organizing-list/wf

RESULT=myresult.out
DIFFRESULT=myresult.diff

# Clear out any results form last run
cat /dev/null > $RESULT

case $# in
0) echo "Usage: wftest.sh {std|self} <textfile>"; exit 1;;
1) echo "Usage: wftest.sh {std|self} <textfile>"; exit 1;;
esac

textfile=`basename $2`
inputdir=sample-input
outputdir=sample-output
expected=$outputdir/$textfile.out


if test "$1" = "std"
then
	# run std list test and compare output
	time ./self-organizing-list/wf --std-list $inputdir/$textfile | sort -r -k2 -k1 >> $RESULT
else
	# run self-organizing list test and compare output
	time ./self-organizing-list/wf --self-organized-list $inputdir/$textfile | sort -k2r -k1r >> $RESULT
fi

diff -v $expected $RESULT > $DIFFRESULT
if [ $? -ne 0 ]
then
	echo "Processing complete. Sorting output..."
	echo "Sorting complete. Comparing output..."
	echo "Test failed. Check $DIFFRESULT for differences."
	echo
else
	echo "Processing complete. Sorting output.."
	echo "Sorting complete. Comparing output..."
	echo "All tests passed!"
	echo
	rm $DIFFRESULT
fi

#!/bin/bash

for x in $(find *)
do
	echo  $(basename $x)
done
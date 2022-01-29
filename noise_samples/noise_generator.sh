#!/bin/bash

if [ $# -eq 0 ]
  then
    echo "usage: ./noise_generator.sh volume"
    exit 1
fi

vol="$1" # 0.1standard value

FILES="../music_samples/*"
for f in $FILES
do
# FAILSAFE #
# Check if "$f" FILE exists and is a regular file and then only copy it #
  if [ -f "$f" ] && [[ $f == *.wav ]]
  then
    output=`echo $f | rev | cut -d'/' -f 1 | rev`
    sox $f noise.wav synth whitenoise vol $vol && sox -m $f noise.wav $output
  else
    echo "Ignoring \"$f\""
  fi
done

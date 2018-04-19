#! /bin/sh

race()
{
  while true
  do
    ./race_condition < attack_input
    done
}
race
RACE_PID=$!
kill $RACE_PID

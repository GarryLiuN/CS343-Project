#!/bin/bash

EXEC=./soda
SEED=10013
TEST_DIR=tests/*
COUNT=0

echo "Start Testing for SODA"

for test in $TEST_DIR
do
    echo -e "\nTEST $COUNT"
    echo "================================================"
    cat $test
    echo -e "\n$EXEC $test $SEED "
    $EXEC $test $SEED > temp
    (head; echo -e "\n................\n omitted\n................\n" ;tail)< temp
    COUNT=$((COUNT+1))
done
rm temp

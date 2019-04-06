#!/bin/bash

EXEC=./soda
SEED=10013
TEST_DIR=tests/*
COUNT=0

echo -e "* Building Soda\n"

touch main.cc
make &> /dev/null

if [ $? -ne 0 ]; then
    echo "Build Failed!!!"
    exit $?
fi

echo -e "\n* Build Completed"

echo -e "\n* Start Testing for Soda"

for test in $TEST_DIR
do
    echo
    echo "================================================================================================"
    echo -e "TEST $COUNT"
    echo "================================================================================================"
    cat $test
    echo -e "\n\$> $EXEC $test $SEED "
    $EXEC $test $SEED > temp
    (head; echo -e "\n................\n omitted\n................\n" ;tail)< temp
    COUNT=$((COUNT+1))
done
rm temp

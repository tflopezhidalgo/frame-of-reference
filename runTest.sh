#!/bin/bash

SUCESS=true

for i in {1..50}; do
    ./tp 4 1 1 test-files/alot out 
    diff out test-files/alot4.out

    if [ $? -gt 0 ]; then
        SUCESS=false
    fi

    ./tp 4 1 1 test-files/oneblk out
    diff out test-files/oneblk4.out

    if [ $? -gt 0 ]; then
        SUCESS=false
    fi

    ./tp 4 1 1 test-files/largenum out
    diff out test-files/largenum4.out

    if [ $? -gt 0 ]; then
        SUCESS=false
    fi

    ./tp 3 1 1 test-files/zeroblk out
    diff out test-files/zeroblk3.out

    if [ $? -gt 0 ]; then
        SUCESS=false
    fi
done

if [ "$SUCESS" = true ]; then
    echo "OK"
else
    echo "FAILED"
fi

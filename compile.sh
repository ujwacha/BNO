#!/bin/bash

set +e

if [[ "$1" == "clean" ]]; then
    rm -rf build
fi

if [ ! -d "build" ]; then
    mkdir build
fi

bear -- make -j

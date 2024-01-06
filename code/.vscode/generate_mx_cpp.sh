#!/bin/bash
echo "Script executed from: ${PWD}"

BASEDIR=$(dirname $0)
echo "Script location: ${BASEDIR}"

if test -f "${PWD}/Src/main.cpp"; then
    mv ${PWD}/Src/main.cpp ${PWD}/Src/main.c
fi

stm32pio generate

mv ${PWD}/Src/main.c ${PWD}/Src/main.cpp
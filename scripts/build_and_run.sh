#! /bin/bash

SCRIPT_PATH="${BASH_SOURCE:-$0}"
SCRIPT_DIRECTORY="$(dirname "${SCRIPT_PATH}")"

cd ${SCRIPT_DIRECTORY}/..

cmake -DCMAKE_EXPORT_COMPILE_COMMANDS=1 -B build .
cmake --build build


build/N_Body

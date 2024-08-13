#!/bin/bash

SCRIPT_PATH="${BASH_SOURCE:-$0}"
SCRIPT_DIRECTORY="$(dirname "${SCRIPT_PATH}")"

cd ${SCRIPT_DIRECTORY}/..

PREFIX_PATH="/home/dmitro/Documents/Projects/C/NBodyProject/Nbody/vendor/OpenCL-Headers/install;/home/dmitro/Documents/Projects/C/NBodyProject/Nbody/vendor/OpenCL-ICD-Loader/install;/home/dmitro/Documents/Projects/C/NBodyProject/Nbody/vendor/OpenCL-CLHPP/install"

cmake -D CMAKE_PREFIX_PATH="${PREFIX_PATH}" -DCMAKE_EXPORT_COMPILE_COMMANDS=1 -B build .
cmake --build build

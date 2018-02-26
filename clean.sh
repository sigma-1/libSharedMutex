#!/usr/bin/env bash

make clean
./setup.py --clean
./setup.py --clearCache
rm -rf bin
rm -rf build
rm -rf external
rm -rf lib
rm -rf SharedMutex
rm compfile.mk
rm makefile-common.mk

#!/usr/bin/env bash

./configure.py -CC clang -CXX clang++
./setup.py --compfile compfile.mk --outMakefile makefile-common.mk
make && make install

if [[ $(uname) == "Darwin" ]];then
	rm -rf SharedMutex/lib/libSharedMutex.so
fi

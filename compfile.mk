CC = clang
CXX = clang++
CXXOUTNAME = sharedMutex
CXXFLAGS = -std=c++14
CXXFLAGS += -Wall -ftemplate-depth=1024
CXXOPT += -O2 -funroll-loops -DNDEBUG  
ifneq ($(shell uname -s),Darwin)
	CXXOPT += -march=native -mtune=native
endif

#debug
CXXDEBUG = -g -gstabs+ 
INSTALL_DIR=./sharedMutex
EXT_PATH=$(realpath /Users/nick/hathaway/external/)

USE_CPPITERTOOLS = 0
USE_CPPPROGUTILS = 0
USE_ZI_LIB = 0
USE_BOOST = 0
USE_R = 0
USE_BAMTOOLS = 0
USE_CPPCMS = 0
USE_MATHGL = 0
USE_ARMADILLO = 0
USE_MLPACK = 0
USE_LIBLINEAR = 0
USE_PEAR = 0
USE_CURL = 0
USE_GTKMM = 0
USE_BIBSEQ = 0
USE_BIBCPP = 0
USE_SEEKDEEP = 0
USE_BIBSEQDEV = 0
USE_SEEKDEEPDEV = 0
USE_CATCH = 0
USE_JSONCPP = 0
USE_TWOBIT = 0
USE_SEQSERVER = 0
USE_NJHRINSIDE = 0
USE_PSTREAMS = 0
USE_MONGOC = 0
USE_MONGOCXX = 0

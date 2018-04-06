# this makefile relies on implicit suffix rules.


CPPUTEST_HOME = /home/jarmo/Projects/proximity/cpputest

CPPFLAGS += -I$(CPPUTEST_HOME)/include
# Add the memory leak macros to your Makefile (needed for additional debug info!). Something like:
CXXFLAGS += -include $(CPPUTEST_HOME)/include/CppUTest/MemoryLeakDetectorNewMacros.h
CFLAGS += -include $(CPPUTEST_HOME)/include/CppUTest/MemoryLeakDetectorMallocMacros.h
# Add the library linking to your Makefile. Something like:
LDLIBS = -L$(CPPUTEST_HOME)/lib -lCppUTest -lCppUTestExt




CPPUTEST_HOME = /home/jarmo/Projects/proximity/cpputest

test:
	g++ tests/test.cpp \
		-g \
		-I$(CPPUTEST_HOME)/include \
		-Ibuild/ \
		-include $(CPPUTEST_HOME)/include/CppUTest/MemoryLeakDetectorNewMacros.h \
		-include $(CPPUTEST_HOME)/include/CppUTest/MemoryLeakDetectorMallocMacros.h \
		-L$(CPPUTEST_HOME)/lib -lCppUTest -lCppUTestExt \
		-o build/test \

runtest: test
	./build/test

codestyle:
	astyle src/*

clean:
	rm -rf /build/*

exenamed = CholeskyDecompD.exe	
exenamer = CholeskyDecompR.exe	

sources =	\
Exception.cpp	\
Cholesky.cpp	\
Cholesky_driver.cpp

objects = $(patsubst %.cpp,%.o,$(sources))	

CXX = g++	
CXXFLAGS = -Wall -fPIC -std=c++11	

ifeq "$(findstring release, $(MAKECMDGOALS))" ""	
    CXXFLAGS += -DDEBUG -g	
else	
    CXXFLAGS += -O3	
endif	

INCLUDEDIRS = -I.	
CPPFLAGS = $(INCLUDEDIRS)	

debug:	$(objects)	
	$(CXX) $(objects) $(CXXFLAGS) $(CPPFLAGS) -o  $(exenamed)  

release:  $(objects)	
	$(CXX)  $(objects) $(CXXFLAGS) $(CPPFLAGS) -o  $(exenamer)

clean:	
	rm -f *.o	
	rm -f *.exe

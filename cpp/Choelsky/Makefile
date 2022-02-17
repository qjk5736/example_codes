exenamed = ChoelskyDecompD.exe	
exenamer = ChoelskyDecompR.exe	

sources =	\
Exception.cpp	\
Choelsky.cpp	\
Choelsky_driver.cpp

objects = $(patsubst %.cpp,%.o,$(sources))	

CXX = /usr/bin/g++	
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

PLATFORM=UNIX
CAPENGINEPATH=../../github/capengine
LOGLEVEL=Logger::CDEBUG
CC=g++
CPP=g++
INCLUDE=./src
INCLUDEDIRS=-I$(CAPENGINEPATH)
CFLAGS= -g -Wall -D$(PLATFORM) -DDEBUG -DLOGLEVEL=$(LOGLEVEL) -std=c++0x $(INCLUDEDIRS) `sdl-config --cflags` `xml2-config --cflags`
LIBS=`sdl-config --cflags --libs` `xml2-config --libs` -lSDL_image -lboost_system -lboost_filesystem
#CFLAGS= -O3 -D$(PLATFORM) -DDEBUG

objects = spacecombat.o ship.o map1.o gameobject.o locator.o ship_input_component.o ship_physics_component.o ship_graphics_component.o ship_custom_component.o world.o basicgun.o \
	bullet_physics_component.o bullet_graphics_component.o

#Application
spacecombat: $(objects)
	$(CPP) $(CFLAGS) -o spacecombat $(objects) libcapengine.so $(LIBS)

all: $(objects)

$(objects): %.o: %.cpp
	$(CC) -c $(CFLAGS) $< -o $@


.PHONEY: clean tests tags extract

clean:
	-rm -f *.o
	-rm -f *.so
	-rm spacecombat
	-rm test/*.o
	-rm test/test

extract:
	cp $(CAPENGINEPATH)/libcapengine.so ./

tests:
	cd test && $(MAKE)

tags:
	ctags -e -R . && ctags -e -R -a /usr/include/SDL && ctags -e -R -a $(CAPENGINEPATH)
#	ctags -e -R .

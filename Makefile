CSRCS=  entity.cpp ship.cpp shipcontroller.cpp world.cpp main.cpp
COBJS=$(patsubst %.cpp,%.o,$(CSRCS))

CFLAGS = -g -c -O2 -DLINUX

INCLUDE = -I. -I/usr/include/ -I/usr/include/X11/
INCOSG = -I/usr/include/osg

# LDLIBS = -lm -ldl -lGL -lGLU -lpthread -lXext -lX11
LDFLAGS =  -L. -L/usr/lib -L/usr/X11R6/lib -L/usr/local/lib
LDOSG = -L/usr/lib64 -losg -losgGA -losgViewer -losgSim
LDLUA = -L/usr/lib64 -llua

CC = g++

EXE=bship

all: $(EXE)


$(EXE): $(COBJS)
	$(CC) -o$(EXE) $(COBJS) $(LDFLAGS) $(LDLIBS) $(LDOSG) $(LDLUA)


$(COBJS): %.o : %.cpp
	$(CC) $(INCLUDE) $(INCOSG) $(CFLAGS) -o $@ $< 

clean:
	rm -f *.o $(EXE)

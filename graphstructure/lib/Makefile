#// =============================================================== 
#// Makefile for MESH (OpenGL)
#// =============================================================== 
#ar rvf libmesh.a edge.o face.o loop.o edgelist.o facelist.o vertex.o vertexlist.o halfedge.o solid.o
#// ===============================
#// A few generic defines


#// ===============================
#// Compiler to use : if you want to use the DEC native "cc"
#// compiler, some of the flags below may not work

CC        = CC
AR        = ar
RAN       = ranlib

#// ===============================
#// Compile flags flags : 
#//	-g = include debug info
#//	-pg = include profile info
#//	-Wall = enable all warnings
#//	-O6 = highest optimization

#// ===============================
#// Paths :

LIB       = -lglut -lGLU -lGL -lX11 -lXmu -lm 

CFLAGS     = -g $(INCPATH)	 
#CFLAGS     = -O6 -Wall 
#CFLAGS     = -O6
LFLAGS      = rvf 

#// ===============================
#// Linking flags :

#OFLAGS    = -pg
OFLAGS    = 


#// ===============================
#// Files :

INCLUDES = mesh.h\
  	   funcs.h\
	
SOURCES  = edge.c\
	heapsort.c\
	face.c\
	loop.c\
	edgelist.c\
	facelist.c\
	vertex.c\
	vertexlist.c\
	halfedge.c\
	solid.c\
	list.c\


OBJECTS  = edge.o\
	heapsort.o\
	face.o\
	loop.o\
	edgelist.o\
	facelist.o\
	vertex.o\
	vertexlist.o\
	halfedge.o\
	solid.o\
	list.o\

TARGET   = libmesh.a

# Target --------------------------

$(TARGET):	$(OBJECTS)
	$(AR) $(LFLAGS) $(TARGET)  $(OBJECTS)
	$(RAN) $(TARGET)
	chmod a+rx $(TARGET) *.o

# Utilities ------------------------

# Print up the entire source tree
#
print:
	enscript -2rG -pprint.ps $(SOURCES) $(INCLUDES) Makefile

# Create code dependencies 
#
depend: $(SOURCES) $(INCLUDES)
	$(CC) $(CPPFLAGS) -M $(SOURCES) > makedep
	echo '/^# DO NOT DELETE THIS LINE/+2,$$d' >eddep
	echo '$$r makedep' >>eddep
	echo 'w' >>eddep
	ed - Makefile < eddep
	rm eddep makedep
	echo '# DEPENDENCIES MUST END AT END OF FILE' >> Makefile
	echo '# IF YOU PUT STUFF HERE IT WILL GO AWAY' >> Makefile
	echo '# see make depend above' >> Makefile

# Cleanup
#
clean:
	rm -rf core *~ *.o $(TARGET)

# Code checkin
#
ci:
	ci -l $(SOURCES) $(INCLUDES) Makefile

#-----------------------------------------------------------------
# DO NOT DELETE THIS LINE -- make depend uses it
# DEPENDENCIES MUST END AT END OF FILE









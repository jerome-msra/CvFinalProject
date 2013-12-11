##########################################################
#	DIRECTORY NAMES
#

#MATLAB = /usr/local/matlab65
#MATLAB = /usr/local/matlab72

SRCROOT = ../../code
OBJDIR =../../o32/exttype
BINDIR = ../../lib
##########################################################
#	ADDITIONAL C PREPROCESSOR AND COMPILER OPTIONS
#
#CC = g++
CC = g++-3.3.6
CFLAGS = -O3 -w -fpermissive #-pedantic
#CFLAGS += -fPIC -fno-omit-frame-pointer -ansi -D_GNU_SOURCE -pthread -fexceptions
CFLAGS += -I$(SRCROOT) -I$(INCDIR)
CFLAGS += -I$(MATLAB)/extern/include
#CFLAGS += -I$(INCDIR) -DV5_COMPAT
############################################################
#	SRC
#

PRG = exttype

HDRS = 

SRCS = block_allocator.cpp\
	dataset.cpp\
	xfs.cpp\
	logs.cpp\
	pvect.cpp\
	xstringstream.cpp\
	math.cpp\
	vectn.cpp

############################################################
#	LIB
#
#LDLIBS = libstdc++.a $(LIB)/qt-3/lib/qt-mt.lib
#LD0 = -O -pthread -shared -Wl,--version-script,$(MATLAB)/extern/lib/glnx86/mexFunction.map
#LDLIBS = -L$(MATLAB)/bin/glnx86 -lmx -lmex -lmat -lm mexversion.o
#LDLIBS += -Wl,--rpath-link,$(MATLAB)/lib/glnx86,--rpath-link,$(MATLAB)/bin/glnx86 -L$(MATLAB)/bin/glnx86

#############################################################
#	PATH

RPATH = exttype\
	data\
	debug\
	streams\
	files\
	dynamic\
	geom\
 	.
	
VPATH = $(RPATH:%=$(SRCROOT)/%)

#
#############################################################
#	MAKROS
#
HEADERS=${HDRS:%=${HDRDIR}/%}
SOURCES=${SRCS:%=${SRCDIR}/%}
SOURCESM=${SRCMS:%=${SRCDIR}/%}

OBJECTS = $(SRCS:%.cpp=$(OBJDIR)/%.o)
OBJECTSM = $(SRCMS:%.cpp=$(OBJDIR)/%.o)

EXTDIROBJECTS = $(EXTOBJECTS:%.o=$(OBJDIR)/%.o)
ALLOBJECTS = $(OBJECTS) $(EXTDIROBJECTS)
PROGRAM = $(BINDIR)/$(PRG).a

#############################################################
all: $(BINDIR)/lib$(PRG).a

$(BINDIR)/lib$(PRG).a: ${OBJECTS}
	@echo linking...
	@ar rc $(BINDIR)/lib$(PRG).a ${ALLOBJECTS}
#	${CC} -shared -o $(BINDIR)/lib$(PRG).so ${ALLOBJECTS}
	ar rc $(BINDIR)/lib$(PRG).a ${ALLOBJECTS}
#	@echo $(LDFLAGS)
#	${CC} -o $(PRG)-g.exe ${ALLOBJECTS} -g
	@echo done.

${OBJDIR}/%.o : %.cpp ${HEADERS}
	@echo $<
	@${CC} ${CFLAGS} ${CPPFLAGS} -c -o $@ -g $<

#############################################################

clean:
	rm -f $(OBJDIR)/*.o *~ 
	rm -f $(PROGRAM).*

lib:

#	@ar rc lib$(PRG).a ${ALLOBJECTS}
#	${CC} -shared -o lib$(PRG).so ${ALLOBJECTS}
#	ar rc lib$(PRG).a ${ALLOBJECTS}

fmex: ${OBJECTS} ${OBJECTSM}
	${CC} --version
	@$(MATLAB)/bin/mex -v -g -V5 -f mexopts1.sh -I$(SRCROOT) dummy.cpp ${ALLOBJECTS} ${OBJECTSM} -outdir $(BINDIR) -output $(PRG) >1

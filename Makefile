# Default rule: $(CXX) $(CXXFLAGS) $(CPPFLAGS) $(TARGET_ARCH)

CC = /opt/gcc412/bin/gcc412
CXX = /opt/gcc412/bin/g++412
LD = /opt/gcc412/bin/g++412
RM = rm -f

INCLUDES = -I./ -I/usr/X11R6/include -I/usr/autodesk/maya2015-x64/include
LDFLAGS = -L/usr/autodesk/maya2015-x64/lib -lOpenMaya -lsndfile -lfftw3f -Wl,-Bsymbolic -shared

# Preprocessor Flags

CPPFLAGS:=$(CPPFLAGS) -DBits64
CPPFLAGS:=$(CPPFLAGS) -D_BOOL
CPPFLAGS:=$(CPPFLAGS) -DUNIX
CPPFLAGS:=$(CPPFLAGS) -DLINUX
CPPFLAGS:=$(CPPFLAGS) -DLINUX_64
CPPFLAGS:=$(CPPFLAGS) -DFUNCPROTO
CPPFLAGS:=$(CPPFLAGS) -D_GNU_SOURCE
CPPFLAGS:=$(CPPFLAGS) -DREQUIRE_IOSTREAM

# C++ Compilation Flags

CXXFLAGS:=$(CXXFLAGS) -m64
CXXFLAGS:=$(CXXFLAGS) -fPIC
CXXFLAGS:=$(CXXFLAGS) -fno-strict-aliasing
CXXFLAGS:=$(CXXFLAGS) -O3
CXXFLAGS:=$(CXXFLAGS) -Wall
CXXFLAGS:=$(CXXFLAGS) -Wno-multichar
CXXFLAGS:=$(CXXFLAGS) -Wno-comment
CXXFLAGS:=$(CXXFLAGS) -Wno-sign-compare
CXXFLAGS:=$(CXXFLAGS) -funsigned-char
CXXFLAGS:=$(CXXFLAGS) -pthread
CXXFLAGS:=$(CXXFLAGS) -L/usr/autodesk/maya2015-x64/lib
CXXFLAGS:=$(CXXFLAGS) $(INCLUDES)
CXXFLAGS:=$(CXXFLAGS) -Wno-deprecated
CXXFLAGS:=$(CXXFLAGS) -Wno-reorder
CXXFLAGS:=$(CXXFLAGS) -ftemplate-depth-25
CXXFLAGS:=$(CXXFLAGS) -fno-gnu-keywords

all: audioAnalyzer.so

clean:
	$(RM) *.o *.so

audioAnalyzer.so : audioAnalyzerNode.o MayaException.o plugin.o DFFT.o
	$(LD) -o $@ $(LDFLAGS) $^


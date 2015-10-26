CC = /opt/gcc412/bin/gcc412
C++ = /opt/gcc412/bin/g++412

CFLAGS = -DBits64_ -m64 -DUNIX -D_BOOL -DLINUX -DFUNCPROTO -D_GNU_SOURCE \
         -DLINUX_64 -fPIC \
         -fno-strict-aliasing -DREQUIRE_IOSTREAM -O3 -Wall \
         -Wno-multichar -Wno-comment -Wno-sign-compare -funsigned-char \
         -pthread -I/usr/autodesk/maya2015-x64/include

C++FLAGS = $(CFLAGS) $(WARNFLAGS) -Wno-deprecated -Wno-reorder \
		-ftemplate-depth-25 -fno-gnu-keywords -I/usr/autodesk/maya2015-x64/include

INCLUDES	= -I$(SRCDIR) -I$(DEVKIT_INCLUDE) -I/usr/X11R6/include -I/usr/autodesk/maya2015-x64/include

%.o : %.cpp
	$(C++) -c $(C++FLAGS) $(INCLUDES) $< -o $@

all : plugin

plugin : audioAnalyzer.mll

audioAnalyzer.mll : audioAnalyzerNode.o MayaException.o plugin.o


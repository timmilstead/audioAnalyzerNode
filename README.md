This plugin was developed for Maya 2015, but will probably recompile on other versions.

On Linux you must compile using GCC 4.1.2:

http://help.autodesk.com/view/MAYAUL/2015/ENU/?guid=__files_Setting_up_your_build_environment_Linux_compiler_requirement_htm

You can't use C++ 11 or 0x because GCC 4.1.2 doesn't support it (even though the Visual Studio 2012 used by the Windows version of Maya does).

The linux version was actually developed on Ubuntu 14.04 LTS to match the setup of a receiving third party.
It has not been tested on any of Autodesk's supported platforms, e.g. Centos 6.2 although I expect it will work just fine.
N.B. Installing Maya, not to mention GCC 4.1.2, on Ubuntu 14.04 is hard work - use the recommended platforms unless you have good reason not to.

The Windows version was developed on Windows 7 Pro 64bit with Visual Studio 2012 pro.

Dependencies:

libfftw
libsndfile
boost (unit tests)

Maya plug-ins can only persist using their nodes and attributes so the fftw plan can not be cached between computations.
Creating a plan is computationally very expensive unless one uses the FFTW_ESTIMATE flag. Even then it could be that changing this code to use a different DFFT library (e.g. KISS FFT) will speed things up.

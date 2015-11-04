This is a more advanced, open source replacement for the audio wave plug-in provided by the Maya Bonus Tools.
In addition to providing the existing input (time) and output (audio level) attributes it adds low, middle and high frequency output attributes.
These are calculated using a fast fourier transform (power spectrum).
The source code includes an example audio file and MEL script that creates a simple demo animation.
The MEL script needs editing before use - to match the absolute path of the audio file (referenced in two separate lines).

This plugin was developed for Maya 2015, but will probably recompile on other versions.

On Linux you must compile using GCC 4.1.2 and the Makefile:

http://help.autodesk.com/view/MAYAUL/2015/ENU/?guid=__files_Setting_up_your_build_environment_Linux_compiler_requirement_htm

On Windows use Visual Studio 2012 and the solution (.sln) file.

The code does not use C++ 11 or 0x because GCC 4.1.2 doesn't support it (even though Visual Studio 2012 does).

The Linux version is best complied on RHEL 6.2 WS, Centos 6.2 (tested) or Fedora 14 - Autodesk's recommended platforms.

Dependencies:

libfftw
libsndfile
boost (unit tests)
libaudiofile (linux)

Install the development versions when installing on Linux, e.g.

	sudo yum install fftw-devel libsndfile-devel audiofile-devel

On Windows you will have to generate the fftw lib files to compile - see the FFTW documentation.

See:

	http://www.milstead.me.uk/maya_audio_analyzer_plug-in/ 

for a description of the node attributes.



Copyright, License and Non Warranty:

(c) Tim Milstead 2015
Do whatever you like with the source code and binaries.
This software comes with no warranty.

Music by Gorowski: Attribution-NonCommercial-ShareAlike 3.0 International License. See http://freemusicarchive.org/music/Gorowski/The_Gorowski_Archives_Previously_Unreleased_Tuneage_from_the_Archives_2005-2015/


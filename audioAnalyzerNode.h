//(c) Tim Milstead 2015

#ifndef AUDIO_ANALYZER_NODE_H
#define AUDIO_ANALYZER_NODE_H

#include <string.h>
#include <maya/MIOStream.h>
#include <math.h>
#include <ctime>

#include <maya/MPxNode.h> 
#include <maya/MFnNumericAttribute.h>
#include <maya/MFnTypedAttribute.h>
#include <maya/MString.h> 
#include <maya/MTypeId.h> 
#include <maya/MPlug.h>
#include <maya/MVector.h>
#include <maya/MDataBlock.h>
#include <maya/MDataHandle.h>
#include <maya/MFloatArray.h>
#include <maya/MArrayDataBuilder.h>
#include <maya/MGlobal.h>
#include <maya/MFnFloatArrayData.h>
#include <maya/MFnUnitAttribute.h>
#include <maya/MTime.h>

#include <sndfile.h>
#include <fftw3.h>

#include "Util.h"
#include "MayaException.h"

// -------- Class Declaration --------

/** A replacement for the audio wave node provided by Autodesk's Bonus Tools pack.
* Adds output of low, middle and high power spectrum values.
* Uses a discrete fast fourier transform to calculate the power spectrum over 1 second centered on the current time. */
class audioAnalyzer : public MPxNode
{
public:
						audioAnalyzer();
	virtual				~audioAnalyzer(); 

	virtual MStatus compute(const MPlug& plug, MDataBlock& data );
private:
	void computeData(const MPlug& plug, MDataBlock& dataBlock);
	void computeOutput(const MPlug& plug, MDataBlock& dataBlock);
	void computePowerSpectrum(const MPlug& plug, MDataBlock& dataBlock);
	static void createAttributes();
	
	static void createInputAttributes();
	static void createIntermediateAttributes();
	static void createOutputAttributes();
public:
	static void* creator();
	
	static MStatus initialize();


	static void addAttributes();
	static void affectAttributes();

public:

	static MTypeId id;

	// -------- Attributes --------

	/** The full path and file name of the audio file. */
	static MObject audioAttr;
	
	/** The cached raw audio data. */
	static MObject dataAttr;

	/** The time to calculate the outputs at. */
	static MObject inputAttr;

	/** The audio value (average volumne of all channels) at the current input time. Output attribute. */
	static MObject outputAttr;

	/** Scale the output by the specified amount - same as the audio wave plugin. */
	static MObject scaleAttr;

	/** The amount of low frequencies (up to 250Hz) covering one second about the current input time. Output attribute. */
	static MObject lowAttr;

	/** Scale the low value by the specified amount - like scale from the audio wave plugin. */
	static MObject lowScaleAttr;

	/** The amount of middle frequencies (250Hz - 4kHz) covering one second about the current input time. Output attribute. */
	static MObject midAttr;

	/** Scale the mid value by the specified amount - like scale from the audio wave plugin. */
	static MObject midScaleAttr;

	/** The amount of high frequencies (above 4kHz) covering one second about the current input time. Output attribute. */
	static MObject highAttr;

	/** Scale the high value by the specified amount - like scale from the audio wave plugin. */
	static MObject highScaleAttr;

	/** The size of the audio. */
	static MObject sizeAttr;

	/** The sample rate of the audio. */
	static MObject sampleRateAttr;

	/** The number of samples used to calculate the output attribute value.
	* This matches the attribute in the audioWave plugin. */
	static MObject sampleSizeAttr;
};

#endif
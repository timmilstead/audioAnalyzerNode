//(c) Tim Milstead 2015

#include "audioAnalyzerNode.h"

// -------- Static Fields --------

MTypeId audioAnalyzer::id( 0x80012 );

// Attributes

MObject audioAnalyzer::audioAttr;        
MObject audioAnalyzer::dataAttr;
MObject audioAnalyzer::outputAttr;
MObject audioAnalyzer::scaleAttr;
MObject audioAnalyzer::inputAttr;
MObject audioAnalyzer::lowAttr;
MObject audioAnalyzer::lowScaleAttr;
MObject audioAnalyzer::midAttr;
MObject audioAnalyzer::midScaleAttr;
MObject audioAnalyzer::highAttr;
MObject audioAnalyzer::highScaleAttr;
MObject audioAnalyzer::sizeAttr;
MObject audioAnalyzer::sampleRateAttr;
MObject audioAnalyzer::sampleSizeAttr;
MObject audioAnalyzer::bpmAttr;

// -------- Functions --------

/** Default constructor. */
audioAnalyzer::audioAnalyzer()
{
	TRACE_OUTPUT("audioAnalyzer()")
}

/** Called when createNode audioNode is called. */
void* audioAnalyzer::creator()
{
	TRACE_OUTPUT("creator()")
	return new audioAnalyzer();
}

MStatus audioAnalyzer::initialize()
{
	TRACE_OUTPUT("initialize()");
	try
	{
		createAttributes();
		addAttributes();
		affectAttributes();
	}
	catch (const MayaException& mayaException)
	{
		cerr << mayaException.what() << endl;
		return mayaException.status;
	}
	return MS::kSuccess;
}

void audioAnalyzer::createAttributes()
{
	TRACE_OUTPUT("createAttributes()");

	createInputAttributes();
	createIntermediateAttributes();
	createOutputAttributes();
}

void audioAnalyzer::createInputAttributes()
{
	TRACE_OUTPUT("createInputAttributes()");

	MStatus status;
	MFnTypedAttribute typedAttrFn;
	MFnNumericAttribute numAttrFn;
	MFnUnitAttribute unitAttrFn;

	ASSERT_PASSED_MSTATUS(audioAttr = typedAttrFn.create("audio","a",MFnData::kString,&status));
	ASSERT_PASSED_MSTATUS(sampleSizeAttr = numAttrFn.create("sampleSize","sz",MFnNumericData::kInt, 20, &status));
	
	ASSERT_PASSED_MSTATUS(scaleAttr =     numAttrFn.create("scale","s",MFnNumericData::kFloat, 1.0, &status));
	ASSERT_RETURN_MSTATUS(numAttrFn.setStorable(true));
	ASSERT_RETURN_MSTATUS(numAttrFn.setWritable(true));

	ASSERT_PASSED_MSTATUS(lowScaleAttr =  numAttrFn.create("lowScale","ls",MFnNumericData::kFloat, 1.0, &status));
	ASSERT_RETURN_MSTATUS(numAttrFn.setStorable(true));
	ASSERT_RETURN_MSTATUS(numAttrFn.setWritable(true));
	
	ASSERT_PASSED_MSTATUS(midScaleAttr =  numAttrFn.create("middleScale","ms",MFnNumericData::kFloat, 1.0, &status));
	ASSERT_RETURN_MSTATUS(numAttrFn.setStorable(true));
	ASSERT_RETURN_MSTATUS(numAttrFn.setWritable(true));
	
	ASSERT_PASSED_MSTATUS(highScaleAttr = numAttrFn.create("highScale","hs",MFnNumericData::kFloat, 1.0, &status));
	ASSERT_RETURN_MSTATUS(numAttrFn.setStorable(true));
	ASSERT_RETURN_MSTATUS(numAttrFn.setWritable(true));

	MTime defaultTime(0.0);
	ASSERT_PASSED_MSTATUS(inputAttr = unitAttrFn.create("input","i",defaultTime,&status));

	ASSERT_PASSED_MSTATUS(bpmAttr = numAttrFn.create("bpm","bpm",MFnNumericData::kInt, 0, &status));


}

/** Create intermediate attributes that are affected by the input attributes and affect the output attributes. */
void audioAnalyzer::createIntermediateAttributes()
{
	TRACE_OUTPUT("createIntermediateAttributes()");

	MStatus status;
	MFnNumericAttribute numAttrFn;
	MFnTypedAttribute typedAttrFn;

	ASSERT_PASSED_MSTATUS(sizeAttr = numAttrFn.create("size","size",MFnNumericData::kLong, 0.0, &status));
	ASSERT_RETURN_MSTATUS(numAttrFn.setWritable(false));
	ASSERT_RETURN_MSTATUS(numAttrFn.setKeyable(false));

	ASSERT_PASSED_MSTATUS(sampleRateAttr = numAttrFn.create("sampleRate","sr",MFnNumericData::kInt, 0, &status));
	ASSERT_RETURN_MSTATUS(numAttrFn.setWritable(false));
	ASSERT_RETURN_MSTATUS(numAttrFn.setKeyable(false));

	MObject defaultData;
	MFnFloatArrayData floatArrayDataFn;
	MFloatArray floatArray(10,0.0f);
	ASSERT_PASSED_MSTATUS(defaultData = floatArrayDataFn.create(floatArray,&status));
	ASSERT_PASSED_MSTATUS(dataAttr = typedAttrFn.create("data","d",MFnData::kFloatArray, defaultData ,&status));
}

void audioAnalyzer::createOutputAttributes()
{
	TRACE_OUTPUT("createOutputAttributes()");

	MStatus status;
	MFnNumericAttribute numAttrFn;

	ASSERT_PASSED_MSTATUS(outputAttr = numAttrFn.create("output","o",MFnNumericData::kFloat, 0.0, &status));
	ASSERT_RETURN_MSTATUS(numAttrFn.setWritable(false));
	ASSERT_RETURN_MSTATUS(numAttrFn.setKeyable(false));

	ASSERT_PASSED_MSTATUS(lowAttr = numAttrFn.create("low","l",MFnNumericData::kFloat, 0.0, &status));
	ASSERT_RETURN_MSTATUS(numAttrFn.setWritable(false));
	ASSERT_RETURN_MSTATUS(numAttrFn.setKeyable(false));

	ASSERT_PASSED_MSTATUS(midAttr = numAttrFn.create("middle","m",MFnNumericData::kFloat, 0.0, &status));
	ASSERT_RETURN_MSTATUS(numAttrFn.setWritable(false));
	ASSERT_RETURN_MSTATUS(numAttrFn.setKeyable(false));

	ASSERT_PASSED_MSTATUS(highAttr = numAttrFn.create("high","h",MFnNumericData::kFloat, 0.0, &status));
	ASSERT_RETURN_MSTATUS(numAttrFn.setWritable(false));
	ASSERT_RETURN_MSTATUS(numAttrFn.setKeyable(false));
}

void audioAnalyzer::addAttributes()
{
	TRACE_OUTPUT("addAttributes()");

	ASSERT_RETURN_MSTATUS(addAttribute(audioAttr ));
	ASSERT_RETURN_MSTATUS(addAttribute(inputAttr ));
	ASSERT_RETURN_MSTATUS(addAttribute(dataAttr ));
	ASSERT_RETURN_MSTATUS(addAttribute(outputAttr ));
	ASSERT_RETURN_MSTATUS(addAttribute(scaleAttr ));
	ASSERT_RETURN_MSTATUS(addAttribute(lowAttr ));
	ASSERT_RETURN_MSTATUS(addAttribute(lowScaleAttr ));
	ASSERT_RETURN_MSTATUS(addAttribute(midAttr ));
	ASSERT_RETURN_MSTATUS(addAttribute(midScaleAttr ));
	ASSERT_RETURN_MSTATUS(addAttribute(highAttr ));
	ASSERT_RETURN_MSTATUS(addAttribute(highScaleAttr ));
	ASSERT_RETURN_MSTATUS(addAttribute(sizeAttr ));
	ASSERT_RETURN_MSTATUS(addAttribute(sampleRateAttr ));
	ASSERT_RETURN_MSTATUS(addAttribute(sampleSizeAttr ));
	ASSERT_RETURN_MSTATUS(addAttribute(bpmAttr ));
}

void audioAnalyzer::affectAttributes()
{
	TRACE_OUTPUT("affectAttributes()");

	ASSERT_RETURN_MSTATUS(attributeAffects(audioAttr, dataAttr ));
	ASSERT_RETURN_MSTATUS(attributeAffects(audioAttr, sizeAttr ));
	ASSERT_RETURN_MSTATUS(attributeAffects(audioAttr, sampleRateAttr ));
	ASSERT_RETURN_MSTATUS(attributeAffects(audioAttr, sampleSizeAttr ));

	ASSERT_RETURN_MSTATUS(attributeAffects(dataAttr, outputAttr ));
	ASSERT_RETURN_MSTATUS(attributeAffects(dataAttr, lowAttr ));
	ASSERT_RETURN_MSTATUS(attributeAffects(dataAttr, midAttr ));
	ASSERT_RETURN_MSTATUS(attributeAffects(dataAttr, highAttr ));

	ASSERT_RETURN_MSTATUS(attributeAffects(sampleRateAttr, outputAttr ));
	ASSERT_RETURN_MSTATUS(attributeAffects(sampleRateAttr, lowAttr ));
	ASSERT_RETURN_MSTATUS(attributeAffects(sampleRateAttr, midAttr ));
	ASSERT_RETURN_MSTATUS(attributeAffects(sampleRateAttr, highAttr ));

	ASSERT_RETURN_MSTATUS(attributeAffects(sampleSizeAttr, outputAttr ));

	ASSERT_RETURN_MSTATUS(attributeAffects(inputAttr, outputAttr ));
	ASSERT_RETURN_MSTATUS(attributeAffects(inputAttr, lowAttr ));
	ASSERT_RETURN_MSTATUS(attributeAffects(inputAttr, midAttr ));
	ASSERT_RETURN_MSTATUS(attributeAffects(inputAttr, highAttr ));

	ASSERT_RETURN_MSTATUS(attributeAffects(bpmAttr, outputAttr ));
	ASSERT_RETURN_MSTATUS(attributeAffects(bpmAttr, lowAttr ));
	ASSERT_RETURN_MSTATUS(attributeAffects(bpmAttr, midAttr ));
	ASSERT_RETURN_MSTATUS(attributeAffects(bpmAttr, highAttr ));

	ASSERT_RETURN_MSTATUS(attributeAffects(scaleAttr, outputAttr ));
	ASSERT_RETURN_MSTATUS(attributeAffects(lowScaleAttr, lowAttr ));
	ASSERT_RETURN_MSTATUS(attributeAffects(midScaleAttr, midAttr ));
	ASSERT_RETURN_MSTATUS(attributeAffects(highScaleAttr, highAttr ));
}

/** Calculate output attribute values for a change in the input attribute (audio file name) value. */ 
MStatus audioAnalyzer::compute(const MPlug& plug, MDataBlock& dataBlock)
{
	TRACE_OUTPUT("compute(...)")
	try
	{

		MStatus status;
 
		if (plug == dataAttr || plug == sizeAttr || plug == sampleRateAttr || plug == sampleSizeAttr) // audio (file name) has changed - update the data cache with the audio data
		{
			computeData(plug, dataBlock);
		}
		else if (plug == outputAttr) // input (time) or (cached) data has changed
		{
			computeOutput(plug, dataBlock);
		}
		else if (plug == lowAttr || plug == midAttr || plug == highAttr) // input (time) or (cached) data has changed
		{
			computePowerSpectrum(plug, dataBlock);
		}
	}
	catch (const MayaException& mayaException)
	{
		cerr << mayaException.what() << endl;
		return mayaException.status;
	}
	return MS::kSuccess;
}

void audioAnalyzer::computeData(const MPlug&, MDataBlock& dataBlock)
{
	TRACE_OUTPUT("computeData(...)")

	MStatus status;

	ASSERT_PASSED_MSTATUS(MDataHandle audioDataHandle = dataBlock.inputValue(audioAttr, &status));
	MString fileName = audioDataHandle.asString();

	// Read in the raw data using libsndfile

	SF_INFO sfInfo;
	float* buffer = NULL;

	if (fileName.length() > 0)
	{
		SNDFILE* sndfile = sf_open(fileName.asChar(), SFM_READ, &sfInfo); 
		
		if (sndfile != NULL)
		{
			buffer = new float[sfInfo.frames * sfInfo.channels];
			sf_readf_float(sndfile, buffer, sfInfo.frames);
			sf_close(sndfile);
		}
		else
		{
			MGlobal::displayWarning("Could not load audio from: "+fileName);
			sfInfo.frames = 0;
			sfInfo.channels = 0;
			sfInfo.samplerate = 0;
		}
	}
	else
	{
		MGlobal::displayInfo("No audio file name set");
		sfInfo.frames = 0;
		sfInfo.channels = 0;
		sfInfo.samplerate = 0;
	}

	// Set a float array with the result

	MFloatArray mFloatArray(static_cast<unsigned int>(sfInfo.frames),0.0);
	for (long frameNo = 0; frameNo < sfInfo.frames; ++frameNo)
	{
		float average = 0.0;
		for (int channelNo = 0; channelNo < sfInfo.channels; ++channelNo)
		{
			int bufferIndex = frameNo * sfInfo.channels + channelNo;
			average += buffer[bufferIndex];
		}
		average /= sfInfo.channels;
		mFloatArray.set(average,frameNo);
	}

	// Set the attributes

	ASSERT_PASSED_MSTATUS(MDataHandle dataHandle = dataBlock.outputValue(dataAttr, &status));
	MFnFloatArrayData floatArrayDataFn;
	ASSERT_PASSED_MSTATUS(MObject arrayObject = floatArrayDataFn.create(mFloatArray,&status));
	ASSERT_RETURN_MSTATUS(dataHandle.set(arrayObject));

	ASSERT_PASSED_MSTATUS(dataHandle = dataBlock.outputValue(sizeAttr, &status));
	dataHandle.set(static_cast<int>(sfInfo.frames));

	ASSERT_PASSED_MSTATUS(dataHandle = dataBlock.outputValue(sampleRateAttr, &status));
	dataHandle.set(sfInfo.samplerate);

	// Clean up

	if (sfInfo.frames > 0 && sfInfo.channels > 0 && buffer != NULL)
	{
		delete[] buffer;
	}

	ASSERT_RETURN_MSTATUS(dataBlock.setClean(dataAttr));
	ASSERT_RETURN_MSTATUS(dataBlock.setClean(sizeAttr));
	ASSERT_RETURN_MSTATUS(dataBlock.setClean(sampleRateAttr));
}

void audioAnalyzer::computeOutput(const MPlug& plug, MDataBlock& dataBlock)
{
	TRACE_OUTPUT("computeOutput(...)")
	MStatus status;
	float output = 0.0;

	ASSERT_PASSED_MSTATUS(MDataHandle dataHandle = dataBlock.inputValue(sizeAttr,&status));
	long size = dataHandle.asLong();

	if (size > 0)
	{
		ASSERT_PASSED_MSTATUS( dataHandle = dataBlock.inputValue(inputAttr,&status));
		MTime time = dataHandle.asTime();

		ASSERT_PASSED_MSTATUS(dataHandle = dataBlock.inputValue(sampleRateAttr,&status));
		int sampleRate = dataHandle.asInt();

		ASSERT_PASSED_MSTATUS(dataHandle = dataBlock.inputValue(sampleSizeAttr,&status));
		int sampleSize = dataHandle.asInt();

		long middleIndexNo = static_cast<long>(time.as(MTime::kSeconds) * static_cast<double>(sampleRate));
		long startIndexNo = middleIndexNo - (sampleSize / 2);
		long finishIndexNo = startIndexNo + sampleSize;
		if (finishIndexNo > size) finishIndexNo = size;

		ASSERT_PASSED_MSTATUS(dataHandle = dataBlock.inputValue(dataAttr,&status));
		MObject arrayObject = dataHandle.data();
		ASSERT_PASSED_MSTATUS(MFnFloatArrayData floatArrayData(arrayObject, &status));
		MFloatArray floatArray = floatArrayData.array();

		float average = 0;
		for (long indexNo = startIndexNo ; indexNo < finishIndexNo; ++indexNo)
		{
			if (indexNo >= 0 && indexNo < size)
			{
				average += floatArray[indexNo];
			}
			else
			{
				average += 0.0f;
			}
		}
		average /= size;

		ASSERT_PASSED_MSTATUS(dataHandle = dataBlock.inputValue(scaleAttr,&status));
		float scale = dataHandle.asFloat();

		output = scale * average;
	}

	ASSERT_PASSED_MSTATUS(dataHandle = dataBlock.outputValue(outputAttr, &status));
	dataHandle.setFloat(output);

	ASSERT_RETURN_MSTATUS(dataBlock.setClean(outputAttr));
}

void audioAnalyzer::computePowerSpectrum(const MPlug& plug, MDataBlock& dataBlock)
{
	TRACE_OUTPUT("computePowerSpectrum(...)")

	MStatus status;
	float low = 0.0f;
	float mid = 0.0f;
	float high = 0.0f;
	
	ASSERT_PASSED_MSTATUS(MDataHandle dataHandle = dataBlock.inputValue(sizeAttr,&status));
	long size = dataHandle.asLong();

	if (size > 0)
	{

		ASSERT_PASSED_MSTATUS( dataHandle = dataBlock.inputValue(inputAttr,&status));
		MTime mTime = dataHandle.asTime();
		float time = mTime.as(MTime::kSeconds);

		ASSERT_PASSED_MSTATUS( dataHandle = dataBlock.inputValue(bpmAttr,&status));
		int bpm = dataHandle.asInt();

		if (bpm != 0)
		{
			float resolution = 60.0 / static_cast<float>(bpm);
			float temp = int(time / resolution);
			time = temp * resolution;
		}

		ASSERT_PASSED_MSTATUS(dataHandle = dataBlock.inputValue(sampleRateAttr,&status));
		int sampleRate = dataHandle.asInt();

		long fftSampleSize = 1024;
		float spectralLineFrequencyResolution = static_cast<float>(sampleRate) / static_cast<float>(fftSampleSize);


		long middleIndexNo = static_cast<long>(time * static_cast<double>(sampleRate));
		long startIndexNo = middleIndexNo - static_cast<long>(fftSampleSize / 2.0);
		long finishIndexNo = startIndexNo + fftSampleSize;

		ASSERT_PASSED_MSTATUS(dataHandle = dataBlock.inputValue(dataAttr,&status));
		MObject arrayObject = dataHandle.data();
		ASSERT_PASSED_MSTATUS(MFnFloatArrayData floatArrayData(arrayObject, &status));
		MFloatArray floatArray = floatArrayData.array();

		std::vector<float> values(fftSampleSize);
		for (long indexNo = startIndexNo ; indexNo < finishIndexNo; ++indexNo)
		{
			if (indexNo >= 0 && indexNo < size)
			{
				values[indexNo - startIndexNo] = floatArray[indexNo];
			}
			else
			{
				values[indexNo - startIndexNo] = 0.0f;
			}
		}

		std::vector<float> out(fftSampleSize / 2 + 1);
		DFFT::powerSpectrum(values,out);
		
		// Up to 250Hz
		int lowCount = 0;

		// 250Hz - 4kHz
		int midCount = 0;

		// 4kHz +
		int highCount = 0;

		for (long indexNo = 0; indexNo < (fftSampleSize / 2 +1); ++indexNo)
		{
			float frequency = indexNo * spectralLineFrequencyResolution;
			if (indexNo != 0 && frequency < 250)
			{
				low += out[indexNo];
				lowCount++;
			}
			else if (frequency >= 250 && frequency < 4000)
			{
				mid += out[indexNo];
				midCount++;
			}
			else
			{
				high += out[indexNo];
				highCount++;
			}			
		}

		low /= lowCount;
		ASSERT_PASSED_MSTATUS(dataHandle = dataBlock.inputValue(lowScaleAttr,&status));
		float scale = dataHandle.asFloat();
		low *= scale;

		mid /= midCount;
		ASSERT_PASSED_MSTATUS(dataHandle = dataBlock.inputValue(midScaleAttr,&status));
		scale = dataHandle.asFloat();
		mid *= scale;

		high /= highCount;
		ASSERT_PASSED_MSTATUS(dataHandle = dataBlock.inputValue(highScaleAttr,&status));
		scale = dataHandle.asFloat();
		high *= scale;

	}
	// Set low, mid, high

	ASSERT_PASSED_MSTATUS(dataHandle = dataBlock.outputValue(lowAttr, &status));
	dataHandle.setFloat((float)low);
	ASSERT_PASSED_MSTATUS(dataHandle = dataBlock.outputValue(midAttr, &status));
	dataHandle.setFloat((float)mid);
	ASSERT_PASSED_MSTATUS(dataHandle = dataBlock.outputValue(highAttr, &status));
	dataHandle.setFloat((float)high);

	ASSERT_RETURN_MSTATUS(dataBlock.setClean(lowAttr));
	ASSERT_RETURN_MSTATUS(dataBlock.setClean(midAttr));
	ASSERT_RETURN_MSTATUS(dataBlock.setClean(highAttr));
}

/** (Virtual) destructor.
* Called when a node is deleted. */
audioAnalyzer::~audioAnalyzer()
{
	TRACE_OUTPUT("~audioAnalyzer(...)")
}

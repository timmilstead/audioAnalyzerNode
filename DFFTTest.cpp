#define _USE_MATH_DEFINES // for C++

#include <vector>
#include <iostream>
#include <cmath>
#include <fstream>

#include "DFFT.h"

#define BOOST_TEST_MODULE test_module_name
#include <boost/test/unit_test.hpp>

/** Returns (a copy of) a generated signal.
* @param smapleRate Samples per second, e.g. 44100.
* @param length Length of output in seconds.
* @param freqency Frequency of the signal to produce in Hz.
* @return A copy (we can't use c++ 11 on GCC 4.2.1 so can't use r values and I don't want to pass in a vector) of the generated signal. */
void addSignal(std::vector<float>& carrier, int sampleRate, float outputFrequency)
{
	for (size_t index = 0; index < carrier.size(); ++index)
	{
		float time = (float)index / (float)sampleRate;
		float value = sin(2.0f * static_cast<float>(M_PI) * outputFrequency * time);
		carrier[index] += value;
	}
}

/** Use to output data, e.g. for plotting with gnuplot, e.g.:
* plot(<FILENAME>) with lines. */
void write(const std::vector<float>& data, const std::string fileName)
{
	std::ofstream outputFileStream;
	outputFileStream.open(fileName);
	for (size_t index = 0; index < data.size(); ++index)
	{
		outputFileStream << data[index] << std::endl;
	}
	outputFileStream.close();
}

BOOST_AUTO_TEST_CASE(test_no_1)
{
	std::vector<float> input(22050);
	
	int sampleRate = 44100;

	addSignal(input,sampleRate,500);
	addSignal(input,sampleRate,1000);
	addSignal(input,sampleRate,10000);
	addSignal(input,sampleRate,15000);
	addSignal(input,sampleRate,20000);
	addSignal(input,sampleRate,1);

	write(input,"input.txt"); // gnuplot> plot("input.txt") with lines 

	std::vector<float> output(input.size() / 2 + 1);
	DFFT::powerSpectrum(input,output);

	float spectralLineFrequencyResolution = static_cast<float>(sampleRate) / static_cast<float>(input.size());

	float percentageTolerance = 0.001f;

	BOOST_REQUIRE_CLOSE(1.0,output[static_cast<size_t>(500 / spectralLineFrequencyResolution)],percentageTolerance);
	BOOST_REQUIRE_CLOSE(1.0,output[static_cast<size_t>(1000 / spectralLineFrequencyResolution)],percentageTolerance);
	BOOST_REQUIRE_CLOSE(1.0,output[static_cast<size_t>(10000 / spectralLineFrequencyResolution)],percentageTolerance);
	BOOST_REQUIRE_CLOSE(1.0,output[static_cast<size_t>(15000 / spectralLineFrequencyResolution)],percentageTolerance);
	BOOST_REQUIRE_CLOSE(1.0,output[static_cast<size_t>(20000 / spectralLineFrequencyResolution)],percentageTolerance);


	write(output,"output.txt"); // gnuplot> plot("output.txt") with lines 

}
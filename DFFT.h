#ifndef DFFT_H
#define DFFT_H

#include <vector>
#include <math.h>
#include <fftw3.h>

namespace DFFT
{
	void powerSpectrum(std::vector<float>& input,std::vector<float>& output);
}

#endif
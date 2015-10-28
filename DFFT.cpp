#include "DFFT.h"

namespace DFFT
{

	void powerSpectrum(std::vector<float>& input, std::vector<float>& output)
	{
		fftwf_complex* transform = new fftwf_complex[input.size() / 2 + 1];
		
		fftwf_plan plan = fftwf_plan_dft_r2c_1d(static_cast<int>(input.size()), &input[0], transform, FFTW_ESTIMATE); // Computationally expensive if not FFTW_ESTIMATE
		fftwf_execute(plan);
		fftwf_destroy_plan(plan);

		output.resize(input.size() / 2 + 1);

		for(int index = 0; index < input.size() / 2 + 1; ++index) // pre increment to avoid copy
		{
			output[index] = sqrt(transform[index][0] * transform[index][0] + transform[index][1] * transform[index][1]) / (input.size() / 2.0f);
		}

		delete[] transform;

	}

}

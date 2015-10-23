//(c) Tim Milstead 2015

#include "MayaException.h"

MayaException::MayaException(const MStatus& status, const char* file, int line):
	std::runtime_error(std::string(status.errorString().asChar())+std::string(". ")+file+std::string(", line ")+std::to_string(line)), status(status)
{}

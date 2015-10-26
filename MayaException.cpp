//(c) Tim Milstead 2015

#include "MayaException.h"
#include <boost/lexical_cast.hpp>

MayaException::MayaException(const MStatus& status, const char* file, int line):
	std::runtime_error(std::string(status.errorString().asChar())+std::string(". ")+file+std::string(", line ")+boost::lexical_cast<std::string>(line), status(status)
{}

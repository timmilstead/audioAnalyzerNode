//(c) Tim Milstead 2015

#ifndef MAYA_EXCEPTION_H
#define MAYA_EXCEPTION_H

// -------- Language Headers --------

#include <stdexcept>
#include <string>
#include <sstream>

// -------- Maya Headers --------

#include <maya/MStatus.h>
#include <maya/MString.h>

// -------- Macros --------

// Requires declared MStatus status
#define ASSERT_PASSED_MSTATUS(CODE) CODE; if (status != MStatus::kSuccess) {throw MayaException(status, __FILE__, __LINE__);}

// Self contained MStatus
// Warning: Internal declarations will be scoped to this block (unlikely to be an issue)
#define ASSERT_RETURN_MSTATUS(CODE) { MStatus assertReturnMStatus = CODE; if (assertReturnMStatus != MStatus::kSuccess) {throw MayaException(assertReturnMStatus, __FILE__, __LINE__);} }

// -------- Class --------

class MayaException : public std::runtime_error
{
public:
	MStatus status;

	MayaException(const MStatus& status, const char* file, int line);
};

#endif

//(c) Tim Milstead 2015

#include "plugin.h"

MStatus initializePlugin( MObject obj )
{
	TRACE_OUTPUT("initializePlugin(...)")

	MStatus   status;
	MFnPlugin plugin( obj, "Tim Milstead", "1.0", "Any");

	status = plugin.registerNode( "audioAnalyzer", audioAnalyzer::id, audioAnalyzer::creator,  audioAnalyzer::initialize );
	if (!status)
	{
		status.perror("Error registering audioData node");
		return status;
	}

	return status;
}

MStatus uninitializePlugin( MObject obj)
{
	TRACE_OUTPUT("uninitializePlugin(...)")

	MStatus   status;
	MFnPlugin plugin( obj );

	status = plugin.deregisterNode( audioAnalyzer::id );
	if (!status) {
		status.perror("deregisterNode");
		return status;
	}

	return status;
}


#ifndef MAIN_H
#define MAIN_H

//(c) Tim Milstead 2015

#include <string.h>
#include <maya/MIOStream.h>
#include <math.h>

#include <maya/MPxNode.h> 
#include <maya/MFnNumericAttribute.h>
#include <maya/MFnTypedAttribute.h>
#include <maya/MFnPlugin.h>
#include <maya/MString.h> 
#include <maya/MTypeId.h> 
#include <maya/MPlug.h>
#include <maya/MVector.h>
#include <maya/MDataBlock.h>
#include <maya/MDataHandle.h>
#include <maya/MFloatArray.h>
#include <maya/MArrayDataBuilder.h>
#include <maya/MGlobal.h>

#include "Util.h"
#include "audioAnalyzerNode.h"

MStatus initializePlugin( MObject obj );
MStatus uninitializePlugin( MObject obj);

#endif
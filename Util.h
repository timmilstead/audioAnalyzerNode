//(c) Tim Milstead 2015

#ifndef UTIL_H
#define UTIL_H

// -------- Macros --------

// Provide switchable tracing (debug) output without the overhead of an if statement

// Uncomment/comment as to enable/disable trace output
#define TRACE

#ifndef TRACE_OUTPUT
#ifdef TRACE
// Use cerr because Windows output doesn't work with cout
#define TRACE_OUTPUT(message) cerr << message << endl;
#endif
#ifndef TRACE
#define TRACE_OUTPUT(message) //cerr << message << endl;
#endif
#endif

#endif

#pragma once

class Source
{
	//
	// Construction and destruction.
	//
public:
	//! Constructor.
	Source() = default;
	//! Destructor.
	~Source() = default;

	//
	// Public interface.
	//
public:
	//! Fires event.
	void FireEvent(int n);

	//
	// Public data members.
	//
public:
	// Event.
	Poco::BasicEvent<int> theEvent_;
};
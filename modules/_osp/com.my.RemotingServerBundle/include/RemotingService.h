#pragma once

namespace com
{
namespace my
{

//@ remote
class RemotingService
{
public:
	RemotingService() = default;
	virtual	~RemotingService() = default;

	//
	// Public interface.
	//
public:
	//! Does remoting.
	void DoRemoting();
};

} // namespace my
} // namespace com
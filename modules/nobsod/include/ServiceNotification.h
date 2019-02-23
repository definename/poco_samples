#pragma once

namespace nobsod
{

class ServiceNotification : public Poco::Notification
{
public:
	//! Pointer type.
	using Ptr = Poco::AutoPtr<ServiceNotification>;
	//! Action type.
	enum class Type : int
	{
		StopService = 0
	};

public:
	//! Constructor.
	ServiceNotification(Type action)
		: action_(action)
	{

	}
	//! Destructor.
	~ServiceNotification() = default;

public:
	Type GetType() const {
		return action_;
	}

private:
	//! Action.
	Type action_;
};

} // namespace nobsod

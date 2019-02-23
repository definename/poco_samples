#pragma once

namespace nobsod
{

class Service : public Poco::Runnable, public Poco::RefCountedObject
{
public:
	//! Service pointer type.
	using Ptr = Poco::AutoPtr<Service>;

public:
	//! Constructor.
	Service(Poco::Logger& logger, const std::string& name);
	//! Destructor.
	~Service();

public:
	//! Start service.
	virtual void Start();
	//! Stops service.
	virtual void Stop();
	//! Returns service name
	std::string Name() const;

protected:
	//! Logger reference.
	Poco::Logger& logger_;
	//! Notification queue.
	Poco::NotificationQueue queue_;
	//! Working thread.
	Poco::Thread thread_;
	//! Service name.
	std::string name_;
};

} // namespace nobsod

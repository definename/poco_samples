#pragma once


namespace Services
{

// Forward declaration.
class TimeService;

class WakeUpTask : public Poco::Util::TimerTask
{
	//
	// Construction and destruction.
	//
public:
	//! Constructor.
	WakeUpTask(TimeService& owner, const std::string& message);
	//! Destructor.
	~WakeUpTask() = default;

	//
	// Public interface.
	//
public:
	//! Do whatever the thread needs to do.
	void run() override;

	//
	// Private data members.
	//
private:
	//! Task owner reference.
	TimeService &owner_;
	//! Message.
	std::string message_;
};

} // namespace Services
#ifndef _RCO_H_
#define _RCO_H_

class RCO : public Poco::RefCountedObject
{
public:
	RCO(Poco::Logger& logger)
		: logger_(logger)
	{

	}

protected:
	~RCO() {
		logger_.information("Destroyed!!");
	}
public:
	void Boom() {
		logger_.information("Boom...");
	}

private:
	Poco::Logger& logger_;
};

#endif _RCO_H_
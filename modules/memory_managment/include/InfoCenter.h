#ifndef _INFOCENTER_H_
#define _INFOCENTER_H_

class A
{
public:
	virtual ~A() = default;
	std::string nameA_;
};

class B : public A
{
public:
	std::string nameB_;
};

class InfoCenter
{
public:
	static InfoCenter& GetInstance()
	{
		static InfoCenter infoCenter;
		return infoCenter;
	}

protected:
	InfoCenter() = default;
	~InfoCenter() = default;

	InfoCenter(const InfoCenter&);
	void operator=(const InfoCenter&);

public:
	Poco::SharedPtr<A> aPtr_;
};

#endif _INFOCENTER_H_
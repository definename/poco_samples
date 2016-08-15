#include "pch.h"
#include "TimeServiceClientHelper.h"

class ClientApp : public Poco::Util::ServerApplication
{
	//
	// Construction and destruction.
	//
public:
	//! Construction.
	ClientApp()
		: tcpService_(nullptr)
		, tcpListener_(nullptr)
	{
	}

	//
	// Protected interface.
	//
protected:
	int main(const ArgVec& args)
	{
		int code = ServerApplication::EXIT_OK;
		try
		{
			// StartSoapTransport();
			StartTcpTransport();

			waitForTerminationRequest();

			tcpService_->wakeUp_ -= Poco::delegate(this, &ClientApp::OnWakeUp);
			tcpService_->remoting__enableEvents(tcpListener_, false);
		}
		catch (const Poco::Exception& e)
		{
			logger().error("Poco error occurred: %s", e.displayText());
			code = ServerApplication::EXIT_SOFTWARE;
		}
		return code;
	}
	//! Starts Remoting TCP transport.
	void StartTcpTransport()
	{
		Poco::RemotingNG::TCP::TransportFactory::registerFactory();

		std::string tcpUri("remoting.tcp://localhost:9090/tcp/Services.TimeService/TheClock");
		tcpService_ = Services::TimeServiceClientHelper::find(tcpUri);

		tcpListener_ = new Poco::RemotingNG::TCP::Listener();
		tcpService_->remoting__enableEvents(tcpListener_);
		tcpService_->wakeUp_ += Poco::delegate(this, &ClientApp::OnWakeUp);

		Poco::DateTime wakeUpTime;
		wakeUpTime += Poco::Timespan(2000000); // 2 sec
		tcpService_->WakeUp(wakeUpTime, "Good morning!!!");

		Services::TEvent timeEvent;
		timeEvent.timeEvent_ = "TCP TIME EVENT";
		timeEvent.timeStatus_ = Services::BETTER;
		tcpService_->TimeEvent(timeEvent);
	}
	//! Starts Remoting SOAP transport.
	void StartSoapTransport()
	{
		Poco::RemotingNG::SOAP::TransportFactory::registerFactory();

		const std::string soapUri("http://127.0.0.1:8080/soap/Services.TimeService/TheClock");
		Services::ITimeService::Ptr soapService = Services::TimeServiceClientHelper::find(soapUri);

		Poco::DateTime dt = soapService->currentTime();
		std::cout << Poco::DateTimeFormatter::format(dt, Poco::DateTimeFormat::SORTABLE_FORMAT) << std::endl;

		auto loc = soapService->GetLocation();
		std::cout << "Accuracy: " << loc.accuracy_ << std::endl;
		std::cout << "Speed: " << loc.speed_ << std::endl;
		std::cout << "Velocity: " << loc.velocity_ << std::endl;
		std::cout << "String data: " << loc.data_ << std::endl;

		for (const auto& val : loc.buf_) {
			std::cout << val << " ";
		}
		std::cout << std::endl;

		Services::Internal internal = loc.internal_;
		std::cout << "Internal: " << internal.core_ << std::endl;


		Services::TEvent timeEvent;
		timeEvent.timeEvent_ = ">SOAP< service time event";
		timeEvent.timeStatus_ = Services::GOOD;

		soapService->TimeEvent(timeEvent);
	}

	//
	// Private interface.
	//
private:
	//! On wake up handler.
	void OnWakeUp(const std::string& msg)
	{
		logger().information("Remote message: %s", msg);

		Poco::DateTime wakeUpTime;
		wakeUpTime += Poco::Timespan(2000000); // 2 sec
		tcpService_->WakeUp(wakeUpTime, "Good morning!!!");
	}

	//
	// Private data member.
	//
private:
	//! Tcp service pointer.
	Services::ITimeService::Ptr tcpService_;
	//! Tcp listener pointer.
	Poco::RemotingNG::TCP::Listener::Ptr tcpListener_;
};

POCO_SERVER_MAIN(ClientApp);
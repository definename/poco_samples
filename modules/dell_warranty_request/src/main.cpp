#include "pch.h"

void parseJSON(const std::string& str)
{
	try
	{
		Poco::JSON::Object::Ptr js;
		Poco::Dynamic::Var var = Poco::JSON::Parser().parse(str);

		std::string resultStr = var.convert<std::string>();
		std::cout << resultStr << std::endl;

		js = var.extract<Poco::JSON::Object::Ptr>();
		var = js->get("GetAssetWarrantyResponse");
		js = var.extract<Poco::JSON::Object::Ptr>();
		var = js->get("GetAssetWarrantyResult");
		js = var.extract<Poco::JSON::Object::Ptr>();

		if (!js->isNull("Faults"))
		{
			var = js->get("Faults");
			js = var.extract<Poco::JSON::Object::Ptr>();
			var = js->get("FaultException");
			js = var.extract<Poco::JSON::Object::Ptr>();

			BOOST_THROW_EXCEPTION(
				std::runtime_error(
				boost::str(boost::format("%d %s")
				% js->get("Code").extract<int>() % js->get("Message").extract<std::string>())));
		}

		var = js->get("Response");
		js = var.extract<Poco::JSON::Object::Ptr>();
		var = js->get("DellAsset");
		js = var.extract<Poco::JSON::Object::Ptr>();

		std::cout << "ServiceTag: " <<  js->get("ServiceTag").extract<std::string>() << std::endl;
		std::cout << "ShipDate: " << js->get("ShipDate").extract<std::string>() << std::endl;
		std::cout << std::endl;

		var = js->get("Warranties");
		js = var.extract<Poco::JSON::Object::Ptr>();

		Poco::JSON::Array::Ptr arr(new Poco::JSON::Array);
		arr = js->getArray("Warranty");

		for (int i = 0; i != arr->size(); i++)
		{
			Poco::JSON::Object::Ptr innerObj = arr->get(i).extract<Poco::JSON::Object::Ptr>();
			std::cout << "StartDate: " << innerObj->get("StartDate").extract<std::string>() << std::endl;
			std::cout << "EndDate: " << innerObj->get("EndDate").extract<std::string>() << std::endl;
			std::cout << "EntitlementType: " << innerObj->get("EntitlementType").extract<std::string>() << std::endl;
			std::cout << std::endl;
		}
	}
	catch (const std::exception& e)
	{
		BOOST_THROW_EXCEPTION(std::runtime_error(e.what()));
	}
}

int main(int argc, char** argv)
{
	try
	{
	/*
		//! Without https request
		std::string json("{\"GetAssetWarrantyResponse\":{\"@xmlns\":\"http:123\",\"GetAssetWarrantyResult\":{\"@a\":\"http:321\",\"@i\":\"http:456\",\"Faults\":null,\"Response\":{\"DellAsset\":{\"AssetParts\":{\"@nil\":\"true\"},\"CountryLookupCode\":707,\"CustomerNumber\":5406032,\"IsDuplicate\":\"false\",\"ItemClassCode\":\"A2006\",\"LocalChannel\":\"DP\",\"MachineDescription\":\"Optiplex 380, MCSF, Azteca Y\",\"OrderNumber\":366232023,\"ParentServiceTag\":{\"@nil\":\"true\"},\"ServiceTag\":\"2H3QGQ1\",\"ShipDate\":\"2011-05-18T00:00:00\",\"Warranties\":{\"Warranty\":[{\"EndDate\":\"2014-05-18T23:59:59\",\"EntitlementType\":\"EXTENDED\",\"ItemNumber\":\"907-2052\",\"ServiceLevelCode\":\"ND\",\"ServiceLevelDescription\":\"Next Business Day Support\",\"ServiceLevelGroup\":5,\"ServiceProvider\":\"UNY\",\"StartDate\":\"2012-05-19T00:00:00\"},{\"EndDate\":\"2012-05-18T23:59:59\",\"EntitlementType\":\"INITIAL\",\"ItemNumber\":\"908-2750\",\"ServiceLevelCode\":\"ND\",\"ServiceLevelDescription\":\"Next Business Day Support\",\"ServiceLevelGroup\":5,\"ServiceProvider\":\"UNY\",\"StartDate\":\"2011-05-18T00:00:00\"}]}}}}}}");
		parseJSON(json);
		*/

		//! With https request
		std::string tag("2H3QGQ1");
		std::string apiKey("1adecee8a60444738f280aad1cd87d0e");
		std::string url("https://api.dell.com/support/v2/assetinfo/warranty/tags.json?svctags=");
		url.append(tag);
		url.append("&apikey=");
		url.append(apiKey);

		//! Do request
		URI uri(url);
		std::string path(uri.getPathAndQuery());

		const Poco::Net::Context::Ptr context = new Poco::Net::Context(
			Poco::Net::Context::CLIENT_USE, "", "", "", Poco::Net::Context::VERIFY_NONE);

		HTTPSClientSession session(uri.getHost(), uri.getPort(), context);
		HTTPRequest request(HTTPRequest::HTTP_GET, path, HTTPMessage::HTTP_1_1);
		HTTPResponse response;

		session.sendRequest(request);
		std::istream& rs = session.receiveResponse(response);
		std::cout << response.getStatus() << " " << response.getReason() << std::endl;

		if (response.getStatus() == Poco::Net::HTTPResponse::HTTP_BAD_REQUEST) //! Error code 400
			BOOST_THROW_EXCEPTION(std::runtime_error("Missing API Key"));
		else if (response.getStatus() == Poco::Net::HTTPResponse::HTTP_UNAUTHORIZED) //! Error code 401
			BOOST_THROW_EXCEPTION(std::runtime_error("Invalid API Key / API Key not found"));
		else if (response.getStatus() == Poco::Net::HTTPResponse::HTTP_FORBIDDEN)
			BOOST_THROW_EXCEPTION(std::runtime_error("Access Denied / Rate Limit Exceeded")); //! Error code 403

		std::string result;
		StreamCopier::copyToString(rs, result);

		//! Parse json
		Poco::JSON::Object::Ptr js;
		Poco::Dynamic::Var var = Poco::JSON::Parser().parse(result);

		std::string resultStr = var.convert<std::string>();
		//std::cout << resultStr << std::endl;

		js = var.extract<Poco::JSON::Object::Ptr>();
		var = js->get("GetAssetWarrantyResponse");
		js = var.extract<Poco::JSON::Object::Ptr>();
		var = js->get("GetAssetWarrantyResult");
		js = var.extract<Poco::JSON::Object::Ptr>();

		if (!js->isNull("Faults"))
		{
			var = js->get("Faults");
			js = var.extract<Poco::JSON::Object::Ptr>();
			var = js->get("FaultException");
			js = var.extract<Poco::JSON::Object::Ptr>();

			BOOST_THROW_EXCEPTION(
				std::runtime_error(
				boost::str(boost::format("%d %s")
				% js->get("Code").extract<int>() % js->get("Message").extract<std::string>())));
		}

		var = js->get("Response");
		js = var.extract<Poco::JSON::Object::Ptr>();
		var = js->get("DellAsset");
		js = var.extract<Poco::JSON::Object::Ptr>();

		std::cout << "ServiceTag: " <<  js->get("ServiceTag").extract<std::string>() << std::endl;

		std::string shipStr(js->get("ShipDate").extract<std::string>());
		std::cout << "ShipDate: " << shipStr << std::endl;
		std::cout << std::endl;

		//! Parse date time
		boost::posix_time::ptime ship(boost::date_time::parse_delimited_time<boost::posix_time::ptime>(shipStr, 'T'));
		std::cout << "Date: " << ship.date() << std::endl;
		std::cout << "Time: " << ship.time_of_day() << std::endl;

		var = js->get("Warranties");
		js = var.extract<Poco::JSON::Object::Ptr>();

		Poco::JSON::Array::Ptr arr(new Poco::JSON::Array);
		arr = js->getArray("Warranty");

		for (int i = 0; i != arr->size(); i++)
		{
			Poco::JSON::Object::Ptr innerObj = arr->get(i).extract<Poco::JSON::Object::Ptr>();
			std::cout << "StartDate: " << innerObj->get("StartDate").extract<std::string>() << std::endl;
			std::cout << "EndDate: " << innerObj->get("EndDate").extract<std::string>() << std::endl;
			std::cout << "EntitlementType: " << innerObj->get("EntitlementType").extract<std::string>() << std::endl;
			std::cout << std::endl;
		}
	}
	catch (const std::exception& e)
	{
		std::cerr << "Warranty request error: " << e.what() << std::endl;
		return 1;
	}

	std::cin.get();
	return 0;
}

#pragma warning(disable : 4996) //Disables error code for deprecation for std::asctime
#include "libraries.h"
#include <string>
#include <chrono>
#include <ctime>
#include <iostream>



size_t writeCallback(void* content, size_t size, size_t nmemb, std::string* output)
{
	output->append(static_cast<char*> (content), size * nmemb);

	return size * nmemb;
}

std::string APIHandler::fetchPrice(const std::string& ticker)
{
	CURL* curl = curl_easy_init();
	std::string response;

	if (curl)
	{
		//TODO: REDO API CALL TO FINNHUB'S TO ACCESS MORE IMPORTANT INFORMATION LIKE TICKER PRICE
		//WEBSITE: https://finnhub.io/docs/api/open-data
		std::string token = "d2nq9lpr01qsrqkpl7mgd2nq9lpr01qsrqkpl7n0"; //Nothing to see here
		std::string url = "https://finnhub.io/api/v1/quote?symbol=" + ticker + "&token=" + token;
		curl_easy_setopt(curl, CURLOPT_URL, url.c_str());
		curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, writeCallback);
		curl_easy_setopt(curl, CURLOPT_WRITEDATA, &response);
		curl_easy_setopt(curl, CURLOPT_SSL_VERIFYPEER, 0L);
		curl_easy_setopt(curl, CURLOPT_SSL_VERIFYHOST, 0L);


		CURLcode res = curl_easy_perform(curl);
		curl_easy_cleanup(curl);

		if (res != CURLE_OK)
		{
			std::cout << "cURL request failed: " << curl_easy_strerror(res) << std::endl;
			return "";
		}
	}//Set up API access. 
	else
	{
		std::cerr << "Failed to initialie cURL" << std::endl;
		return "";
	}

	if (response.empty())
	{
		std::cerr << "Empty response from cURL request. " << std::endl;
		return "";
	}

	rapidjson::Document document;
	//Use RapidJSON to parse the response recieved from cURL
	document.Parse(response.c_str());

	if (document.HasParseError())
	{
		std::cerr << "Error occured parsing the URL response.\n";
		return ""; //Error, return an empty string
	}

	if (document.Empty())
	{
		std::cout << "Ticker is not available! \n";
	}
	if (document.HasMember("c") && document["c"].IsDouble())
	{
		auto now = std::chrono::system_clock::now();
		std::time_t end = std::chrono::system_clock::to_time_t(now);
		//Use chrono to determine the current time and date
		double priceRes = document["c"].GetDouble();
		std::cout << "Current Price: $" << priceRes << std::endl;
		return std::to_string(priceRes);//Returns the result as a string in order to be called
	}
	if (document.HasMember("d") && document["d"].IsNumber())
	{
		double ChangeRes = document["d"].GetDouble();//Get and store the current price of the stock
		std::cout << "Price change: $" << ChangeRes << std::endl;
	}
	if (document.HasMember("dp") && document["dp"].IsNumber())
	{
		double percentRes = document["dp"].GetDouble();//Get and store the current price of the stock
		std::cout << "Percent Change: " << percentRes << "%" << std::endl;
	}
	if (document.HasMember("l") && document["l"].IsNumber())
	{
		double lowRes = document["l"].GetDouble();//Get and store the current price of the stock
		std::cout << "Low Price: $" << lowRes << std::endl;
	}
	if (document.HasMember("h") && document["h"].IsNumber())
	{
		double highRes = document["h"].GetDouble();//Get and store the current price of the stock
		std::cout << "High price: $" << highRes << "%" << std::endl;
	}
	std::cout << "\n";
	
	return "";//Return empty string. Never hurts to return the cURL response though! Its a lot of jibberish until its parsed.
}

std::string APIHandler::fetchProfile(const std::string& ticker)
{
	CURL* curl = curl_easy_init();
	std::string response;

	if (curl)
	{
		//TODO: REDO API CALL TO FINNHUB'S TO ACCESS MORE IMPORTANT INFORMATION LIKE TICKER PRICE
		
		//WEBSITE: https://finnhub.io/docs/api/open-data
		std::string token = "blah blah"; //First time seriously using GitHub for a project, forgor to change this
		std::string url = "https://finnhub.io/api/v1/search?q=" + ticker + "&exchange=US&token=" + token;
		curl_easy_setopt(curl, CURLOPT_URL, url.c_str());
		curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, writeCallback);
		curl_easy_setopt(curl, CURLOPT_WRITEDATA, &response);

		CURLcode res = curl_easy_perform(curl);
		curl_easy_cleanup(curl);
		if (res != CURLE_OK)
		{
			std::cout << "cURL request failed: " << curl_easy_strerror(res) << std::endl;
			return "";
		}
	}//Set up API access. 
	else
	{
		std::cerr << "Failed to initialie cURL" << std::endl;
		return "";
	}

	if (response.empty())
	{
		std::cerr << "Empty response from cURL request. " << std::endl;
		return "";
	}

	rapidjson::Document document;
	//Use RapidJSON to parse the response recieved from cURL
	document.Parse(response.c_str());

	if (document.HasParseError())
	{
		std::cerr << "Error parsing URL response.\n";
		return "";
	}
	if (document.HasMember("result") && document["result"].IsArray())
	{ 
		rapidjson::Value& result = document["result"];
		if (result.Empty())
		{
			std::cout << "Ticker does not exist! \n";
		}
		if (result.Size() > 0 && result[0].IsObject())
		{
			const rapidjson::Value& firstRes = result[0];
			if (firstRes.HasMember("displaySymbol") && firstRes["displaySymbol"].IsString())
			{
				std::string displayRes = firstRes["displaySymbol"].GetString();
				std::cout << "Stock symbol: " << displayRes << std::endl;
			}
			if (firstRes.HasMember("description") && firstRes["description"].IsString())
			{
				std::string descRes = firstRes["description"].GetString();
				std::cout << "Description: " << descRes << std::endl;
			}
			if (firstRes.HasMember("type") && firstRes["type"].IsString())
			{
				std::string typeRes = firstRes["type"].GetString();
				std::cout << "Stock type: " << typeRes << std::endl;
			}
		}
		std::cout << "\n";
	}
	return "";//SIGHHHHHH RETURN AN EMPTY STRING AT LEAST SO THIS THING STOPS CRASHING
}



#include "osrb_pch.h"
#include "OSRPediaApi.h"
#include <winhttp.h>

#define OSR_PEDIA_DOMAIN std::string("oldschoolrivals.com")
#define OSR_PEDIA_URL_ITEMS_GET std::string("/action/pedia/search")
#define OSR_PEDIA_URL_ITEM_DETAIL_GET std::string("/action/pedia/item")

OSRPediaApi::OSRPediaApi()
{
	m_pedia_client = std::make_unique<httplib::SSLClient>(OSR_PEDIA_DOMAIN);
}

bool OSRPediaApi::ItemSearchRequest(std::string searchtext, nlohmann::json& result) const
{
	std::string url = OSR_PEDIA_URL_ITEMS_GET + "/" + searchtext;
	auto request_result = m_pedia_client->Get(url.c_str());

	if (request_result->status == HTTP_STATUS_OK)
	{
		result.clear();
		try
		{
		   	result = nlohmann::json::parse(request_result->body);
			return true;
		}
		catch(exception)
		{
			return false;
		}				 		
	}

	return false;
}

bool OSRPediaApi::ItemDetailRequest(INT itemnumber, nlohmann::json& result)	const
{
	std::string url = OSR_PEDIA_URL_ITEM_DETAIL_GET + "/" + std::to_string(itemnumber);
	auto request_result = m_pedia_client->Get(url.c_str());

	if (request_result->status == HTTP_STATUS_OK)
	{
		result.clear();
		try
		{
			result = nlohmann::json::parse(request_result->body);
			return true;
		}
		catch (exception)
		{
			return false;
		}
	}

	return false;
}

bool OSRPediaApi::ItemDetailRequest(std::string searchtext, std::vector<nlohmann::json>& results) const
{
	nlohmann::json searchresult;
	if (!ItemSearchRequest(searchtext, searchresult))
	{
		return false;
	}

	if (searchresult.find("pedia") == searchresult.end() ||
		searchresult["pedia"].find("search") == searchresult["pedia"].end() ||
		searchresult["pedia"]["search"].find("items") == searchresult["pedia"]["search"].end())
	{
		return false;
	}

	for (auto& item : searchresult["pedia"]["search"]["items"])
	{ 		
		if (item.find("Num") == item.end())
		{
			continue;
		}

		nlohmann::json detailResult;
		if(!ItemDetailRequest(TO_INT(item["Num"]), detailResult))
		{
			continue;
		}
		results.push_back(detailResult);
	}
	return true;
}

void OSRPediaApi::ItemSearchRequest(std::string searchtext, std::function<void(bool, nlohmann::json& result)> callback) const
{
	nlohmann::json result_json;
	bool res =ItemSearchRequest(searchtext, result_json);
	callback(res, result_json);
}

void OSRPediaApi::ItemDetailRequest(INT itemnumber, std::function<void(bool, nlohmann::json& result)> callback) const
{
	nlohmann::json result_json;
	bool res = ItemDetailRequest(itemnumber, result_json);
	callback(res, result_json);
}

void OSRPediaApi::ItemDetailRequest(std::string searchtext, std::function<void(bool, std::vector<nlohmann::json>& results)> callback) const
{
	std::vector<nlohmann::json> results;
	bool res = ItemDetailRequest(searchtext, results);
	callback(res, results);
}

void OSRPediaApi::ItemSearchRequestAsync(std::string searchtext, std::function<void(bool, nlohmann::json& result)> callback) const
{
	using functype = void(OSRPediaApi::*)(std::string, std::function<void(bool, nlohmann::json& result)>) const;
	functype func = &OSRPediaApi::ItemSearchRequest;
	std::thread worker(func, this, searchtext, callback); // I dont care for spawning threads lol, there is no anticheat
	worker.detach();
}

void OSRPediaApi::ItemDetailRequestAsync(INT itemnumber, std::function<void(bool, nlohmann::json& result)> callback) const
{
	using functype = void(OSRPediaApi::*)(INT, std::function<void(bool, nlohmann::json& result)>) const;
	functype func = &OSRPediaApi::ItemDetailRequest;
	std::thread worker(func, this, itemnumber, callback); // I dont care for spawning threads lol, there is no anticheat
	worker.detach();
}

void OSRPediaApi::ItemDetailRequestAsync(std::string searchtext, std::function<void(bool, std::vector<nlohmann::json>& results)> callback) const
{
	using functype = void(OSRPediaApi::*)(std::string, std::function<void(bool, std::vector<nlohmann::json>& result)>) const;
	functype func = &OSRPediaApi::ItemDetailRequest;
	std::thread worker(func, this, searchtext, callback); // I dont care for spawning threads lol, there is no anticheat
	worker.detach();
}

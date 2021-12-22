#pragma once
#include "nlohmann/json.hpp"
#include <memory>
#include <functional>

#define CPPHTTPLIB_OPENSSL_SUPPORT
#include "Httplib/Httplib.h"
#pragma comment(lib, "ws2_32.lib")

class OSRPediaApi
{
	friend class OSRBuddyMain;
public:
	OSRPediaApi();
	//OSRPediaApi(const OSRPediaApi& other) = delete;
	//OSRPediaApi& operator=(const OSRPediaApi& other) = delete;


	bool ItemSearchRequest(std::string searchtext, nlohmann::json& result) const;
	bool ItemDetailRequest(INT itemnumber, nlohmann::json& result) const;
	// will execute ItemSearch and then ItemDetail for each result 
	bool ItemDetailRequest(std::string searchtext, std::vector<nlohmann::json>& results) const; 

	void ItemSearchRequest(std::string searchtext, std::function<void(bool, nlohmann::json& result)> callback) const;
	void ItemDetailRequest(INT itemnumber, std::function<void(bool, nlohmann::json& result)> callback) const;
	// will execute ItemSearch and then ItemDetail for each result 
	void ItemDetailRequest(std::string searchtext, std::function<void(bool, std::vector<nlohmann::json>& result)> callback) const;

	void ItemSearchRequestAsync(std::string searchtext, std::function<void(bool, nlohmann::json& result)> callback) const;
	void ItemDetailRequestAsync(INT itemnumber, std::function<void(bool, nlohmann::json& result)> callback) const;
	// will execute ItemSearch and then ItemDetail for each result async
	void ItemDetailRequestAsync(std::string searchtext, std::function<void(bool, std::vector<nlohmann::json>& results)> callback) const;	 

private:
	std::unique_ptr<httplib::SSLClient> m_pedia_client;
};
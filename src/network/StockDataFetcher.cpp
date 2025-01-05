#include "StockDataFetcher.h"
#include <iostream>

StockDataFetcher::StockDataFetcher() {
    curl_global_init(CURL_GLOBAL_DEFAULT);
    curl = curl_easy_init();
}

StockDataFetcher::~StockDataFetcher() {
    if (curl) {
        curl_easy_cleanup(curl);
    }
    curl_global_cleanup();
}

size_t StockDataFetcher::WriteCallback(void* contents, size_t size, size_t nmemb, void* userp) {
    ((std::string*)userp)->append((char*)contents, size * nmemb);
    return size * nmemb;
}

nlohmann::json StockDataFetcher::fetchStockData(const std::string& ticker) {
    if (!curl) {
        throw std::runtime_error("Curl initialization failed.");
    }

    // Define the URL (this example uses Alpha Vantage; modify for Google or others)
    std::string url = "https://www.alphavantage.co/query?function=TIME_SERIES_INTRADAY&symbol=" + ticker + "&interval=5min&apikey=YOUR_API_KEY";
    // check out https://site.financialmodelingprep.com/developer/docs/realtime-stock-quote-api

    std::string response_string;
    curl_easy_setopt(curl, CURLOPT_URL, url.c_str());
    curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, WriteCallback);
    curl_easy_setopt(curl, CURLOPT_WRITEDATA, &response_string);

    CURLcode res = curl_easy_perform(curl);
    if (res != CURLE_OK) {
        throw std::runtime_error("CURL request failed: " + std::string(curl_easy_strerror(res)));
    }

    try {
        return nlohmann::json::parse(response_string);
    }
    catch (const std::exception& e) {
        throw std::runtime_error("JSON parsing failed: " + std::string(e.what()));
    }
}

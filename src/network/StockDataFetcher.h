#ifndef STOCKDATAFETCHER_H
#define STOCKDATAFETCHER_H

#include <string>
#include <curl/curl.h>
#include <third_party/json/json.hpp>

class StockDataFetcher {
public:
    StockDataFetcher(const char*);
    ~StockDataFetcher();

    // Fetch stock data for a given ticker symbol
    nlohmann::json fetchStockData(const std::string& ticker);

private:
    // Helper function to handle the response
    static size_t WriteCallback(void* contents, size_t size, size_t nmemb, void* userp);

    const char* apiKey;

    CURL* curl;
};

#endif // STOCKDATAFETCHER_H

#include <iostream>
#include "core/Portfolio.h"
#include "network/StockDataFetcher.h"
#include "utils/envparser.h"

double fetchStockPrice(const std::string& ticker, StockDataFetcher& fetcher) {
    try {
        nlohmann::json stockData = fetcher.fetchStockData(ticker);

        // Extract the price from the JSON response
        if (stockData.contains("Global Quote")) {
            const auto& globalQuote = stockData["Global Quote"];
            if (globalQuote.contains("05. price")) {
                return std::stod(globalQuote["05. price"].get<std::string>());
            }
            else {
                throw std::runtime_error("'05. price' field not found in 'Global Quote'.");
            }
        }
        else {
            throw std::runtime_error("'Global Quote' field not found in stock data.");
        }
    }
    catch (const std::exception& e) {
        std::cerr << "Error fetching stock price: " << e.what() << std::endl;
        throw;
    }
}

void performTrading(const std::string& ticker, StockDataFetcher& fetcher, Portfolio& portfolio) {
    // Fetch and print the stock price before buying
    double buyPrice = fetchStockPrice(ticker, fetcher);
    std::cout << "Current stock price before buying: " << buyPrice << "\n";

    // Buy 10 shares
    portfolio.buyStock(ticker, 10, buyPrice);
    portfolio.printPortfolioSummary();

    // Fetch and print the stock price before selling
    double sellPrice = fetchStockPrice(ticker, fetcher);
    std::cout << "Current stock price before selling: " << sellPrice << "\n";

    // Sell 5 shares
    portfolio.sellStock(ticker, 5, sellPrice);
    portfolio.printPortfolioSummary();
}


int main() {
    try {
        // Load API key from .env file
        loadEnvFile(".env");
        const char* apiKey = std::getenv("ALPHA_VANTAGE_API_KEY");
        if (!apiKey || std::string(apiKey).empty()) {
            throw std::runtime_error("API key not found in environment variables.");
        }
        std::cout << "API key loaded successfully.\n";

        // Initialize objects
        StockDataFetcher fetcher(apiKey);
        Portfolio portfolio(10000.0);

        // Perform trading
        performTrading("AAPL", fetcher, portfolio);
    }
    catch (const std::exception& e) {
        std::cerr << "Error: " << e.what() << std::endl;
        return 1;
    }

    return 0;
}


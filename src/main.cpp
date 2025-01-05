#include <iostream>
#include "core/Portfolio.h"
#include "network/StockDataFetcher.h"

int main() {
    try {
        StockDataFetcher fetcher;
        std::string ticker = "AAPL";  // Example: Apple stock
        nlohmann::json stockData = fetcher.fetchStockData(ticker);

        std::cout << "Stock data for " << ticker << ":\n";
        std::cout << stockData.dump(4) << std::endl;  // Pretty print JSON

    }
    catch (const std::exception& e) {
        std::cerr << "Error: " << e.what() << std::endl;
        return 1;
    }
 
    Portfolio portfolio(10000.0); // Start with $10,000 cash

    // Print portfolio summary
    portfolio.printPortfolioSummary();

    try {
        std::string ticker = "AAPL"; // Example stock
        //nlohmann::json stockData = fetcher.fetchStockData(ticker);

        // Example: Fetch stock price (hardcoded for now; parse JSON later)
        double price = 150.0; // TODO: Use parsed data from `stockData` here

        // Example: Buy 10 shares
        portfolio.buyStock(ticker, 10, price);

        // Print portfolio summary
        portfolio.printPortfolioSummary();

        // Example: Sell 5 shares
        portfolio.sellStock(ticker, 5, price + 5);

        // Print portfolio summary
        portfolio.printPortfolioSummary();

    }
    catch (const std::exception& e) {
        std::cerr << "Error: " << e.what() << std::endl;
    }

    return 0;
}

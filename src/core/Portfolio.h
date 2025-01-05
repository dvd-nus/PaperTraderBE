#ifndef PORTFOLIO_H
#define PORTFOLIO_H

#include <string>
#include <unordered_map>
#include <vector>
#include "Stock.h"

class Portfolio {
public:
    Portfolio(double initialCash);

    // Buy or sell stocks
    bool buyStock(const std::string& ticker, int quantity, double price);
    bool sellStock(const std::string& ticker, int quantity, double price);

    // Get portfolio details
    double getCashBalance() const;
    double getPortfolioValue() const;
    void printPortfolioSummary() const;

private:
    double cashBalance;
    std::unordered_map<std::string, Stock> stocksOwned;
    std::vector<std::string> tradeHistory;

    void addTradeToHistory(const std::string& trade);
};

#endif // PORTFOLIO_H

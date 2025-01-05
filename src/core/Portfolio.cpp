#include "Portfolio.h"
#include <iostream>
#include <iomanip>

Portfolio::Portfolio(double initialCash) : cashBalance(initialCash) {}

bool Portfolio::buyStock(const std::string& ticker, int quantity, double price) {
    double cost = quantity * price;
    if (cost > cashBalance) {
        std::cerr << "Insufficient cash to buy " << quantity << " shares of " << ticker << ".\n";
        return false;
    }

    // Deduct cash and add stock
    cashBalance -= cost;
    stocksOwned[ticker].addShares(quantity, price);

    // Add trade to history
    addTradeToHistory("Bought " + std::to_string(quantity) + " of " + ticker + " at $" + std::to_string(price));
    return true;
}

bool Portfolio::sellStock(const std::string& ticker, int quantity, double price) {
    if (stocksOwned.find(ticker) == stocksOwned.end() || stocksOwned[ticker].getQuantity() < quantity) {
        std::cerr << "Not enough shares of " << ticker << " to sell.\n";
        return false;
    }

    // Add cash and remove stock
    double earnings = quantity * price;
    cashBalance += earnings;
    stocksOwned[ticker].removeShares(quantity);

    // Add trade to history
    addTradeToHistory("Sold " + std::to_string(quantity) + " of " + ticker + " at $" + std::to_string(price));
    return true;
}

double Portfolio::getCashBalance() const {
    return cashBalance;
}

double Portfolio::getPortfolioValue() const {
    double totalValue = cashBalance;
    for (const auto& [ticker, stock] : stocksOwned) {
        totalValue += stock.getQuantity() * stock.getAveragePrice();
    }
    return totalValue;
}

void Portfolio::printPortfolioSummary() const {
    std::cout << "Cash Balance: $" << std::fixed << std::setprecision(2) << cashBalance << "\n";
    std::cout << "Stocks Owned:\n";
    for (const auto& [ticker, stock] : stocksOwned) {
        std::cout << " - " << ticker << ": " << stock.getQuantity() << " shares @ $" << stock.getAveragePrice() << "\n";
    }
}

void Portfolio::addTradeToHistory(const std::string& trade) {
    tradeHistory.push_back(trade);
}

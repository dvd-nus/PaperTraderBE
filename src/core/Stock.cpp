#include "Stock.h"
#include <stdexcept>

Stock::Stock() : quantity(0), totalCost(0.0) {}

void Stock::addShares(int quantity, double price) {
    this->quantity += quantity;
    this->totalCost += quantity * price;
}

void Stock::removeShares(int quantity) {
    if (quantity > this->quantity) {
        throw std::runtime_error("Attempted to remove more shares than owned.");
    }
    // Adjust total cost proportionally
    totalCost -= (totalCost / this->quantity) * quantity;

    this->quantity -= quantity;
}

int Stock::getQuantity() const {
    return quantity;
}

double Stock::getAveragePrice() const {
    return quantity > 0 ? totalCost / quantity : 0.0;
}

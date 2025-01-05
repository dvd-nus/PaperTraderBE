#ifndef STOCK_H
#define STOCK_H

#include <string>

class Stock {
public:
    Stock();

    void addShares(int quantity, double price);
    void removeShares(int quantity);
    int getQuantity() const;
    double getAveragePrice() const;

private:
    int quantity;
    double totalCost; // Used to calculate average price
};

#endif // STOCK_H

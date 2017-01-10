#ifndef _STOCKITEM_H_
#define _STOCKITEM_H_

#define DESC_MAX_LENGTH 30

#include <string>

using namespace std;

class StockItem
{
  private:
    int sku;   
    string description; 
    double price;       
    int stock; 

  public:
    StockItem();
    StockItem(int skuid, string desc, double p);

    int GetSKU() const;
    string GetDescription() const;
    double GetPrice() const;
    int GetStock() const;

    bool SetDescription(string newdesc);
    bool SetPrice(double newprice);
    bool SetStock(int amount);

    bool operator==(const StockItem& item) const;
    bool operator!=(const StockItem& item) const;
    bool operator>(const StockItem& item) const;
    bool operator<(const StockItem& item) const;
    bool operator>=(const StockItem& item) const;
    bool operator<=(const StockItem& item) const;

    StockItem& operator=(const StockItem& item);
};

#endif
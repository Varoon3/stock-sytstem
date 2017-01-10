
#pragma once

#include <math.h>
#include <sstream>

#include "stockitem.h"
#include "rbtree.h"

class StockSystem
{
  private:
    RBTree<StockItem> records;
    double balance; 

  public:
    StockSystem();
    // returns the balance member
    double GetBalance();
    // Add a new SKU to the system. Do not allow insertion of duplicate sku
    bool StockNewItem(StockItem item);
    // Locate the item with key itemsku and update its description field.
    bool EditStockItemDescription(int itemsku, string desc);
    // Locate the item with key itemsku and update its description field.
    bool EditStockItemPrice(int itemsku, double retailprice);
    // Purchase quantity of item at unitprice each, to reach a maximum (post-purchase) on-hand stock quantity of 1000.
    bool Restock(int itemsku, int quantity, double unitprice);
    // Sell an item to a customer, if quantity of stock is available and SKU exists.
    bool Sell(int itemsku, int quantity);

    // Return a formatted string containing complete stock catalogue information in the following format:
    string GetCatalogue()
    {
      ostringstream strcatalogue;
      int desclengthdiff;
      int cataloguesize = 0; 
      StockItem* catalogue = records.DumpInOrder(cataloguesize);
      strcatalogue << "SKU\tDESCRIPTION\t\t\tQTY\tPRICE\n";
      for (int i = 0; i < cataloguesize; i++)
      {
        strcatalogue << catalogue[i].GetSKU() << "\t" << catalogue[i].GetDescription();
        desclengthdiff = 32 - catalogue[i].GetDescription().length();
        for (int j = 0; j < ceil((double) desclengthdiff / 8); j++)
          strcatalogue << "\t";
        strcatalogue << catalogue[i].GetStock() << "\t$" << catalogue[i].GetPrice() << "\n";
      }
      return strcatalogue.str();
    }

    // Provides access to internal RedBlackTree.
    RBTree<StockItem>& GetRecords()
    {
      return records;
    }
};
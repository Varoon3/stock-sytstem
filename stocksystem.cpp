// File:        stocksystem.cpp
// Author:      Varoon Mathur
// Date:        2016-06-13
// Description: Full Implementation of StockSystem Class for Assignment #3 CPSC 221

#include "stocksystem.h"
#include "stockitem.h"
#include "rbtree.h"

using namespace std;


StockSystem::StockSystem(){
	RBTree<StockItem> *records = new RBTree<StockItem>;
	balance = 100000.00;
}
	
double StockSystem::GetBalance(){
	return this->balance;
}

bool StockSystem::StockNewItem(StockItem item){
	if (records.Contains(item) == true){
		return false;
	}

	if (item.GetSKU() < 10000 || item.GetSKU() > 99999){
		return false;
	}

	records.Insert(item);

	return true;
}

bool StockSystem::EditStockItemDescription(int itemsku, string desc){
	if (desc == "")
		return false;
	
	int size = records.Size();
	StockItem* arr = records.DumpInOrder(size);

	for (int i = 0; i < size; i++){
		if (arr[i].GetSKU() == itemsku){
			StockItem *item = records.Retrieve(arr[i]);
			item->SetDescription(desc);
			delete[] arr;
			return true;
		}
	}

	delete[] arr;
	return false;
}

bool StockSystem::EditStockItemPrice(int itemsku, double retailprice){
	if (retailprice < 0) {return false;}

	int size = records.Size();
	StockItem* arr = records.DumpInOrder(size);

	for (int i = 0; i < size; i++) {
		if (arr[i].GetSKU() == itemsku) {
			StockItem *item = records.Retrieve(arr[i]);
			item->SetPrice(retailprice);
			delete[] arr;
			return true;
		}
	}

	delete[] arr;
	return false;
}

bool StockSystem::Restock(int itemsku, int quantity, double unitprice){
	int size = records.Size();
	StockItem* arr = records.DumpInOrder(size);

	if (quantity < 0 || unitprice < 0) 
		return false;

	if (quantity >= 1000)
		quantity = 1000;

	if ((quantity*unitprice) > balance) 
		return false;

	for (int i = 0; i < size; i++) {
		if (arr[i].GetSKU() == itemsku) {
			StockItem *item = records.Retrieve(arr[i]);
			if(item->GetStock() >= 1000){return false;}

			int number = item->GetStock() + quantity;
			if(number >= 1000){quantity = 1000 - item->GetStock(); number = 1000;}

			item->SetStock(number);
			this->balance = balance - (quantity*unitprice);
			delete[] arr;
			return true;
		}
	}

	delete[] arr;
	return false;
}

bool StockSystem::Sell(int itemsku, int quantity){
	int size = records.Size();
	StockItem* arr = records.DumpInOrder(size);

	if (quantity < 0) 
		return false; 

	for (int i = 0; i < size; i++) {
		if (arr[i].GetSKU() == itemsku){
			StockItem *item = records.Retrieve(arr[i]);

			int number = item->GetStock() - quantity;
			if (number <= 0)  
				number = 0; 
			if (item->GetStock() <= 0) 
				return false; 

			if (number == 0){
				this->balance = balance + ( item->GetStock()*item->GetPrice());
			} else {
				this->balance = balance + (quantity*item->GetPrice());
			}

			delete[] arr;
			item->SetStock(number);
			return true;
		}
	}

	delete[] arr;
	return false;
}





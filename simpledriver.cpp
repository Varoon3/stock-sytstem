#include <iostream>
#include <cstdlib>
#include <string>
#include "rbtree.h"
#include "stocksystem.h"
using namespace std;

void PrintMenu();
void RBTreeTest();

int main()
{
  RBTreeTest();

  int choice = 0;
  string inputchoice;
  int asku;
  string inputasku;
  string adesc;
  double aprice;
  string inputaprice;
  int amount;
  string inputamt;
  string ctlg = "";

  StockSystem mystore;

  while (choice != 8)
  {
    PrintMenu();
    // get the menu choice from standard input
    getline(cin, inputchoice);
    choice = atoi(inputchoice.c_str());

    switch (choice)
    {
      case 1: // Print balance
        cout << "Funds: $" << mystore.GetBalance() << endl << endl;
        break;
      case 2: // Print catalogue
        ctlg = mystore.GetCatalogue();
        cout << ctlg << endl;
        break;
      case 3: // Add SKU
        cout << "Enter a numeric SKU (will be converted to 5 digits): ";
        getline(cin, inputasku);
        asku = atoi(inputasku.c_str());
        cout << "Enter item description: ";
        getline(cin, adesc);
        cout << "Enter a retail price: $";
        getline(cin, inputaprice);
        aprice = atof(inputaprice.c_str());
        if (mystore.StockNewItem(StockItem(asku, adesc, aprice)))
          cout << "Successfully added item to catalogue." << endl;
        else
          cout << "Item not added to catalogue." << endl;
        break;
      case 4: // Edit item description
        cout << "Enter a numeric SKU to edit: ";
        getline(cin, inputasku);
        asku = atoi(inputasku.c_str());
        cout << "Enter item description: ";
        getline(cin, adesc);
        if (mystore.EditStockItemDescription(asku, adesc))
          cout << "Item successfully updated." << endl;
        else
          cout << "Item not updated." << endl;
        break;
      case 5: // Edit item price
        cout << "Enter a numeric SKU to edit: ";
        getline(cin, inputasku);
        asku = atoi(inputasku.c_str());
        cout << "Enter a retail price: $";
        getline(cin, inputaprice);
        aprice = atof(inputaprice.c_str());
        if (mystore.EditStockItemPrice(asku, aprice))
          cout << "Item successfully updated." << endl;
        else
          cout << "Item not updated." << endl;
        break;
      case 6: // Restock an item
        cout << "Enter a numeric SKU to purchase: ";
        getline(cin, inputasku);
        asku = atoi(inputasku.c_str());
        cout << "Enter a quantity to purchase: ";
        getline(cin, inputamt);
        amount = atoi(inputamt.c_str());
        cout << "Enter the per-unit purchase price: $";
        getline(cin, inputaprice);
        aprice = atof(inputaprice.c_str());
        if (mystore.Restock(asku, amount, aprice))
          cout << "Item successfully restocked." << endl;
        else
          cout << "Item not restocked." << endl;
        break;
      case 7: // Sell an item
        cout << "Enter the SKU of item to sell: ";
        getline(cin, inputasku);
        asku = atoi(inputasku.c_str());
        cout << "Enter a quantity to sell: ";
        getline(cin, inputamt);
        amount = atoi(inputamt.c_str());
        if (mystore.Sell(asku, amount))
          cout << "Transaction complete. Have a nice day." << endl;
        else
          cout << "Item is out of stock. Sorry!" << endl;
        break;
      case 8: // Quit
        // no need to do anything, will cause while loop to break
        break;
      default:
        cout << "Invalid choice." << endl;
        break;
    }
  }

  return 0;
}

void PrintMenu()
{
  cout << "****************************************************\n"
       << "* Please select an option:                         *\n"
       << "* 1. Print balance             6. Restock an item  *\n"
       << "* 2. Print catalogue           7. Sell an item     *\n"
       << "* 3. Add a new SKU                                 *\n"
       << "* 4. Edit item description                         *\n"
       << "* 5. Edit item price           8. Quit             *\n"
       << "****************************************************\n" << endl;
  cout << "Enter your choice: ";
}

void RBTreeTest()
{
  RBTree<int> tree1;

  tree1.Insert(1);
  tree1.Insert(3);
  tree1.Insert(2); // should cause 2 rotations to occur
  tree1.Insert(4);
  tree1.Remove(4);


   //tree1.Insert(1);   // first case to induce rotation
   //tree1.Insert(3);
   //tree1.Insert(2);
   //tree1.Insert(4);
   //tree1.Remove(4);
   //tree1.Insert(100);
   //tree1.Insert(5);
   //tree1.Insert(6);
   //tree1.Insert(7);
   //tree1.Remove(2);
  
   //tree1.Insert(5);    // second case to induce rotation
   //tree1.Insert(3);
   //tree1.Insert(1);
   //tree1.Insert(54);
   //tree1.Insert(13);
   //tree1.Insert(100);
   //tree1.Insert(132);
   //tree1.Insert(14);
   //tree1.Insert(122);
   //tree1.Insert(11);
   //tree1.Insert(121);
   //tree1.Insert(15);
   //tree1.Insert(144);
  
   //tree1.Remove(121);

   //tree1.Insert(13);  // third case to induce rotation where XisNOTLeft and multiple removals
   //tree1.Insert(123);
   //tree1.Insert(234);
   //tree1.Insert(53);
   //tree1.Insert(54);
   //tree1.Insert(4);
   //tree1.Insert(57);
   //tree1.Insert(76);
   //tree1.Insert(8);
   //tree1.Insert(74);
   //tree1.Insert(34);
   //tree1.Insert(3);
   //tree1.Insert(87);
   //tree1.Insert(432);
   //tree1.Insert(23);
   //tree1.Insert(2);

   //tree1.Remove(57);
   //tree1.Remove(54);
   //tree1.Remove(53);
   //tree1.Remove(34);
   //tree1.Remove(23);
   //tree1.Remove(13);  
   //tree1.Remove(8);
   //tree1.Remove(4);
  


   //tree1.Insert(4);  // fourth case to induce rotation
   //tree1.Insert(3);
   //tree1.Insert(21);
   //tree1.Insert(423);
   //tree1.Insert(5);
   //tree1.Insert(7);
   //tree1.Insert(23);
   //tree1.Insert(747);
   //tree1.Insert(13);
   //tree1.Insert(234);
   //tree1.Insert(49);
   //tree1.Insert(456);
   //tree1.Insert(76);
   //tree1.Insert(9);

   //tree1.Remove(4);

   //tree1.Insert(32);   // tried every unique case of rotation inducing removals here
   //tree1.Insert(3);
   //tree1.Insert(132);
   //tree1.Insert(7);
   //tree1.Insert(12);
   //tree1.Insert(76);
   //tree1.Insert(43);
   //tree1.Insert(89);
   //tree1.Insert(1);
   //tree1.Insert(765);
   //tree1.Insert(13);
   //tree1.Insert(879);
   //tree1.Insert(153);
   //tree1.Insert(23);
   //tree1.Insert(143);
   //tree1.Insert(166);
   //tree1.Insert(222);
   //tree1.Insert(777);
   //tree1.Insert(111);
  
   //tree1.Remove(89);

   //tree1.Insert(3);     //Final test
   //tree1.Insert(432); 
   //tree1.Insert(12); 
   //tree1.Insert(767); 
   //tree1.Insert(2); 
   //tree1.Insert(64); 
   //tree1.Insert(78); 
   //tree1.Insert(323); 
   //tree1.Insert(98); 
   //tree1.Insert(36); 
   //tree1.Insert(533); 
   //tree1.Insert(337); 

   //tree1.Remove(767);

  cout << "Tree contains " << tree1.Size() << " entries." << endl;
  cout << "Tree height: " << tree1.Height() << endl;

  int arr_size = tree1.Size();
  int* arr = tree1.DumpPreOrder(arr_size);

  for (int i = 0; i < tree1.Size(); i++) {
	cout << arr[i] << endl;
  }

 
  RBTree<int> tree2(tree1);

  tree1.RemoveAll();


  RBTree<int> tree3;
  tree3.Insert(5);
  tree3 = tree2;
}
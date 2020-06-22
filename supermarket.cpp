#include <iostream>
using namespace std;
const int HASHTABLE_SIZE =13;							//Size of Hash Table Array

struct Item {									//Structure for Product
    long long int ITEM_ID;
    string NAME;
    float RATE;
    int QUANTITY;
    Item* next;
    item(long long ITEM_ID, string NAME, float RATE, int QUANTITY)    
    {
        this->ITEM_ID = ITEM_ID;
        this->NAME = NAME;
        this->RATE = RATE;
        this->QUANTITY = QUANTITY;
    }
};

class Inventory{
 private:
  Item **inventoryHashTable;
  int getHash(long long ITEM_ID) 						//This returns hash value of the product ID
  {
   return (ITEM_ID % (long long)(HASHTABLE_SIZE));
  }

  void Add_item(long long ITEM_ID, string NAME, float RATE, int QUANTITY) 	// Function to add item to inventory databse
  {
  	int hash = getHash(ITEM_ID);
        item *temp = NULL;
        item *current = inventoryHashTable[hash];
        while(current!=NULL)
        {
         temp = current;
         current = current->next;
        }

        if(current==NULL)
        {
         current = new item(ITEM_ID, NAME, RATE, QUANTITY);
         if(temp==NULL)
           inventoryHashTable[hash] = current;
         else
           temp->next = current;
        }

        else
        {
          current->NAME = NAME;
          current->RATE = RATE;
          current->QUANTITY = QUANTITY;
        }
  }

  void Delete_item(long long ITEM_ID)						//Function to delete item from inventory
  {
    int hash = getHash(ITEM_ID);
    Item *current = inventoryHashTable[hash];
    Item *previous = NULL;
    bool flag = false;
    while(current != NULL)
    {
      if(current->ITEM_ID == ITEM_ID)
      {
        previous->next = current->next;
        flag = true;
        delete current;
        break;
      }
      else
      {
        previous = current;
        current = current->next;
      }
    } 
            
    if(flag==false)
      cout<<"No item with item ID "<<ITEM_ID<<" found"<<endl;
    else
      cout<<"The item is deleted";
  }

  void Update_item(long long ITEM_ID, float RATE, int QUANTITY)			//Function to update rate and quantity of an item of inventory
  {
    int hash = getHash(ITEM_ID);
    Item* current = inventoryHashTable[hash];
    bool flag = false;
    while(current!=NULL)
    {
      if(current->ITEM_ID==ITEM_ID)
      {
        current->RATE = RATE;
        current->QUANTITY = QUANTITY;
        flag = true;
        break;
      }
      else
        current = current->next;
    }

    if(flag==true)
      cout<<"The item is updated"<<endl;
    else
      cout<<"The item is not updated"<<endl;
  }
  
 public:
  friend class Manager;
  Inventory();

  void Update_stock(long long ITEM_ID, int QUANTITY)				//Function to update quantity of any item in inventory
  {
    int hash = getHash(ITEM_ID);
    Item* temp = inventoryHashTable[hash];
    while(temp!=NULL)
    {
      if(temp->ITEM_ID == ITEM_ID)
      {
        temp->QUANTITY -= QUANTITY;
        cout<<"Stock of product ID "<<ITEM_ID<<" is updated"<<endl;
        return;
      }
      temp = temp->next;
    }
    cout<<"Stock of "<<ITEM_ID<<" not updated"<<endl;
  }

  void get_product_info(long long ITEM_ID)					//Function to get information of any item in the inventory
  {
    int hash = getHash(ITEM_ID);
    Item* temp = inventoryHashTable[hash];
    while(temp!=NULL)
    {
      if(temp->ITEM_ID==ITEM_ID)
      {
        cout<<"Item ID: "<<temp->ITEM_ID<<endl;
        cout<<"Name: "<<temp->NAME<<endl;
        cout<<"Rate: "<<temp->RATE<<endl;
        cout<<"Quantity: "<<temp->QUANTITY<<endl;
        cout<<"\n\n";
        return;
      }
      temp = temp->next;
    }
    cout<<"Item ID invalid"<<endl;
  }

  Item* search_product(long long ITEM_ID)//this function returns item* pointer for a given product ID.
            {
                int hash = getHash(productID);
                item* current = inventoryHashTable[hash];
                while(current!=NULL)
                {
                    if(current->productID == productID)    
                        return current;
                    else
                        current = current->next;
                }
                return NULL;
            }
};

Inventory::Inventory() 
{
    inventoryHashTable = new Item*[HASHTABLE_SIZE];
    for(int i = 0; i < HASHTABLE_SIZE; i++)
      inventoryHashTable[i] = NULL;
}

void Inventory::Insert(long int id, string name, float rate, int quantity) {
    Item* it = new Item;
    it->ITEM_ID = id;
    it->NAME = name;
    it->RATE = rate;
    it->QUANTITY = quantity;
    it->next = nullptr;

    int index = hash(it->ITEM_ID);
    SortedInsert(it, index);
}




struct Customer {
    long long int CUSTOMER_ID;
    string NAME_CUSTOMER;
    float POINTS;
    Customer* next;
    Customer(long long CUSTOMER_ID, string NAME_CUSTOMER)
    {
        this->CUSTOMER_ID = CUSTOMER_ID;
        this->NAME_CUSTOMER = NAME_CUSTOMER;
        this->POINTS = 0;
        this->next = NULL;
    }
};

class Customers{
 private:
  Customer* HT2[10];
  void SortedInsert(Customer*, int);
  int hash(int key) { return key % 10; };
  long int CUSTOMER_ID;
  string NAME_CUSTOMER;
  float POINTS;
 public:
  Customers();
  void Insert(long int, string, float);
  void Add_customer();
  void Update_points();
  Customer* Find(int);
};

void Customers::SortedInsert(Customer* cust, int index) {
    Customer* head = HT2[index];
    if (!head)
        HT2[index] = cust;
    else {
        Customer* p = head, * q = nullptr;
        while (p && p->CUSTOMER_ID < cust->CUSTOMER_ID) {
            q = p;
            p = p->next;
        }
        if (q) {
            q->next = cust;
            cust->next = p;
        }
        else {
            cust->next = head;
            HT2[index] = cust;
        }
    }

}

Customers::Customers() {
    for (int i = 0; i < 100; i++)
        HT2[i] = nullptr;
}

void Customers::Insert(long int id, string name, float points) {
    Customer* cust = new Customer;
    cust->CUSTOMER_ID = id;
    cust->NAME_CUSTOMER = name;
    cust->POINTS = points;
    cust->next = nullptr;

    int index = hash(cust->CUSTOMER_ID);
    SortedInsert(cust, index);
}

Customer * Customers::Find(int key) {
    int index = hash(key);
    Customer* p = HT2[index];

    while (p && p->CUSTOMER_ID != key) {
        p = p->next;
    }

    return p;

}


class Manager{
 private:
  long int MANAGER_ID;
  string NAME_MANAGER;
 public:
  
};


class Billing: public Inventory, public Customers{

};


int main(){
 Inventory Item_list;
 
 long INVENTORY_DATASET[100][4] = {
  {111100000001,1,100,20},{111100000002,2,110,20},{111100000003,3,120,20},{111100000004,4,130,20},{111100000005,5,140,20},{111100000006,6,150,20},{111100000007,7,160,20},{111100000008,8,170,20},{111100000009,9,180,20},{111100000010,10,190,20},
  {111100000011,11,200,20},{111100000012,12,210,20},{111100000013,13,220,20},{111100000014,14,230,20},{111100000015,15,240,20},{111100000016,16,250,20},{111100000017,17,260,20},{111100000018,18,270,20},{111100000019,19,280,20},{111100000020,20,290,20},
  {111100000021,21,300,20},{111100000022,22,310,20},{111100000023,23,320,20},{111100000024,24,330,20},{111100000025,25,340,20},{111100000026,26,350,20},{111100000027,27,360,20},{111100000028,28,370,20},{111100000029,29,380,20},{111100000030,30,390,20},
  {111100000031,31,400,20},{111100000032,32,410,20},{111100000033,33,420,20},{111100000034,34,430,20},{111100000035,35,440,20},{111100000036,36,450,20},{111100000037,37,460,20},{111100000038,38,470,20},{111100000039,39,480,20},{111100000040,40,490,20},
  {111100000041,41,500,20},{111100000042,42,510,20},{111100000043,43,520,20},{111100000044,44,530,20},{111100000045,45,540,20},{111100000046,46,550,20},{111100000047,47,560,20},{111100000048,48,570,20},{111100000049,49,580,20},{222200001111,50,590,20},
  {222200001114,51,600,20},{222200001117,52,610,20},{222200001120,53,620,20},{222200001123,54,630,20},{222200001126,55,640,20},{222200001129,56,650,20},{222200001132,57,660,20},{222200001135,58,670,20},{222200001138,59,680,20},{222200001141,60,690,20},
  {222200001144,61,700,20},{222200001147,62,710,20},{222200001150,63,720,20},{222200001153,64,730,20},{222200001156,65,740,20},{222200001159,66,750,20},{222200001162,67,760,20},{222200001165,68,770,20},{222200001168,69,780,20},{222200001171,70,790,20},
  {222200001174,71,800,20},{222200001177,72,810,20},{222200001180,73,820,20},{222200001183,74,830,20},{222200001186,75,840,20},{222200001189,76,850,20},{222200001192,77,860,20},{222200001195,78,870,20},{222200001198,79,880,20},{222200001201,80,890,20},
  {222200001204,81,900,20},{222200001207,82,910,20},{222200001210,83,920,20},{222200001213,84,930,20},{222200001216,85,940,20},{222200001219,86,950,20},{222200001222,87,960,20},{222200001225,88,970,20},{222200001228,89,980,20},{222200001231,90,990,20},
  {222200001234,91,1000,20},{222200001237,92,1010,20},{222200001240,93,1020,20},{222200001243,94,1030,20},{222200001246,95,1040,20},{222200001249,96,1050,20},{222200001252,97,1060,20},{222200001255,98,1070,20},{222200001258,99,1080,20},{222200001261,100,1090,20},
 };

 for (int i = 0; i < 100; i++) {
  long int ITEM_ID = INVENTORY_DATASET[i][0];
  string NAME = to_string(INVENTORY_DATASET[i][1]);
  float RATE =  INVENTORY_DATASET[i][2];
  int QUANTITY =  INVENTORY_DATASET[i][2];
  Item_list.Insert(ITEM_ID, NAME, RATE, QUANTITY);
 }


 Customers Customer_List;

 long CUSTOMER_DATASET[100][3] = {
  {9400000001,1,0},{9400000002,2,0},{9400000003,3,0},{9400000004,4,0},{9400000005,5,0},{9400000006,6,0},{9400000007,7,0},{9400000008,8,0},{9400000009,9,0},{9400000010,10,0},
  {9400000011,11,0},{9400000012,12,0},{9400000013,13,0},{9400000014,14,0},{9400000015,15,0},{9400000016,16,0},{9400000017,17,0},{9400000018,18,0},{9400000019,19,0},{9400000020,20,0},
  {9400000021,21,0},{9400000022,22,0},{9400000023,23,0},{9400000024,24,0},{9400000025,25,0},{9400000026,26,0},{9400000027,27,0},{9400000028,28,0},{9400000029,29,0},{9400000030,30,0},
  {9400000031,31,0},{9400000032,32,0},{9400000033,33,0},{9400000034,34,0},{9400000035,35,0},{9400000036,36,0},{9400000037,37,0},{9400000038,38,0},{9400000039,39,0},{9400000040,40,0},
  {9400000041,41,0},{9400000042,42,0},{9400000043,43,0},{9400000044,44,0},{9400000045,45,0},{9400000046,46,0},{9400000047,47,0},{9400000048,48,0},{9400000049,49,0},{9400000050,50,0},
  {9400000051,51,0},{9400000052,52,0},{9400000053,53,0},{9400000054,54,0},{9400000055,55,0},{9400000056,56,0},{9400000057,57,0},{9400000058,58,0},{9400000059,59,0},{9400000060,60,0},
  {9400000061,61,0},{9400000062,62,0},{9400000063,63,0},{9400000064,64,0},{9400000065,65,0},{9400000066,66,0},{9400000067,67,0},{9400000068,68,0},{9400000069,69,0},{9400000070,70,0},
  {9400000071,71,0},{9400000072,72,0},{9400000073,73,0},{9400000074,74,0},{9400000075,75,0},{9400000076,76,0},{9400000077,77,0},{9400000078,78,0},{9400000079,79,0},{9400000080,80,0},
  {9400000081,81,0},{9400000082,82,0},{9400000083,83,0},{9400000084,84,0},{9400000085,85,0},{9400000086,86,0},{9400000087,87,0},{9400000088,88,0},{9400000089,89,0},{9400000090,90,0},
  {9400000091,91,0},{9400000092,92,0},{9400000093,93,0},{9400000094,94,0},{9400000095,95,0},{9400000096,96,0},{9400000097,97,0},{9400000098,98,0},{9400000099,99,0},{9400000100,100,0},
 };
 
 for (int i = 0; i < 100; i++) {
  long int CUSTOMER_ID = CUSTOMER_DATASET[i][0];
  string NAME_CUSTOMER = to_string(CUSTOMER_DATASET[i][1]);
  float POINTS =  CUSTOMER_DATASET[i][2];
  Customer_List.Insert(CUSTOMER_ID, NAME_CUSTOMER, POINTS);
 }

 long int count, customerId;
 cin>>customerId;
 cin>>count;
 long int itemId[count];
 int quantity[count];
 for(int i = 0; i < count; i++)
 {
  cin>>itemId[i];
  cin>>quantity[i];
 }

 Inventory *s1, *s2, *s3;

 s1 = Item_list.Find(111100000021);
 s2 = Item_list.Find(111100000057);
 s3 = Item_list.Find(111100000084);

    cout << s1->NAME  << endl << s2->NAME << endl << s3->NAME << endl;
 
 return 0;
}

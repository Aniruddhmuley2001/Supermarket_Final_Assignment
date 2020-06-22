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

  Item* search_product(long long ITEM_ID)					//This function returns Item* pointer for a given item ID.
  {
    int hash = getHash(ITEM_ID);
    Item* current = inventoryHashTable[hash];
    while(current != NULL)
    {
      if(current->ITEM_ID == ITEM_ID)    
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
      long long ID;
      string name;
    public:
      Manager(long long ID, string name)								//constructor to assign ID and name to Manager
      {
        this->ID = ID;
        this->name = name;
      }
      long long getID()
        return ID;
        
      string getName()
        return name;
        
      void addItem(Inventory* i1, long long ITEM_ID, string NAME, float RATE, int QUANTITY)		//This function accesses private member add_item() of Inventory
        i1->add_item(ITEM_ID, NAME, RATE, QUANTITY);
        
      void deleteItem(Inventory* i1, long long ITEM_ID)							//This function accesses private member delete_item() of Inventory
        i1->delete_item(ITEM_ID);
        
      void updateItem(Inventory* i1, long long ITEM_ID, float RATE, int QUANTITY)			//This function accesses private member update_item() of Inventory
        i1->update_item(ITEM_ID, RATE, QUANTITY);
};


struct Item1												// This structure is for items in the shopping list
{
	long long productID;
	string name;
	float rate;
	int quantity;
	float amount;
	item1 *next;
	item1(long long productID, string name, float rate, int quantity)
	{
		this->productID = productID;
		this->name = name;
		this->rate = rate;
		this->quantity = quantity;
		this->amount = quantity*rate;
		this->next = NULL;
	}
};

class Billing{
    private:
      Item1 *head = NULL;
      float total_amount = 0;
    public:
      int getHash(long long productID)									//returns hash for given product ID
      {
      	return productID%(HASHTABLE_SIZE);
      }
      void buy_item(long long productID, int productQuantity, Inventory* I1)				//Adds an item to the shopping list
      {
      	item* temp = I1->search_product(productID);
       	if(temp)
       	{
      	  if(head==NULL)
          {
            item1* newNode = new item1(productID, temp->name, temp->rate, productQuantity);
            head = newNode;
	  }
	  else
	  {
	    item1* tempNode = head;
	    while(tempNode->next!=NULL)
		tempNode = tempNode->next;

	    item1* newNode = new item1(productID, temp->name, temp->rate, productQuantity);
	    tempNode->next = newNode;
	  }
	}
	else
	  cout<<"Product ID not found"<<endl;  	
      }
        
      void cancel_item(long long productID)								// function to remove an item from the shopping list
      {
       	item1* p = NULL;
        item1 *q = head;
        bool flag = false;
        while(q!=NULL)
        {
          if(q==head)
          {
            if(q->productID==productID)
            {
        	flag = true;
        	head = q->next;
        	delete q;
        	cout<<"Item cancelled"<<endl;
        	break;
	    }
	   else
	   {
		p = q;
		q = q->next;
	   }
	 }
	 else if(q->productID== productID)
	 {
	   p->next = q->next;
	   flag = true;
	   cout<<"Item cancelled"<<endl;
	   delete q;
	   break;
	 }
	 else
	 {
	   p = q;
	   q = q->next;
	 }
       }
       if(!flag)
	 cout<<"Enter valid product ID"<<endl;
     }

     void make_payment()										// function to make final payment for all the items and print the invoice.
     {
       item1 *temp = head;
       while(temp!=NULL)
       {
       	 cout<<"Product ID: "<<temp->productID<<endl;
         cout<<"Name: "<<temp->name<<endl;
         cout<<"Quantity: "<<temp->quantity<<endl;
         cout<<"Rate: "<<temp->rate<<endl;
         cout<<"Amount: "<<temp->amount<<endl;
         cout<<"\n\n";
         total_amount += temp->amount;
         temp = temp->next;
       }
       cout<<"Total amount to be paid: "<<total_amount<<"\n\n";
     }

     void assign_customer_id(long long customerID, CustomerDatabase* C1)				//function to print the customer ID on top of the bill
     {
       customer* temp = C1->search_customer(customerID);
       cout<<"Customer ID: "<<temp->customerID<<endl;
     }

     void update_stock(Inventory* I1)									// function to update stock in inventory after billing process is done.
     {
	item1 *temp = head;
	while(temp!=NULL)
	{
	  I1->update_stock(temp->productID,temp->quantity);
	  temp = temp->next;
	}
     }

    item1* getHead()											// function which returns head which points to the first item in the shopping list
      	return head;

    float getTotalAmount()										//function to get total amount to be paid after billing.
	return total_amount;
};


int main(){ 
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
 
 Manager m1(1,"ABC");
 Inventory i1;
 Customers c1;
 Billing b1;
 int choice;
 bool flag = true;
 string transaction_id = "ABCDEFGH";//tranasction ID for a particular customer.

 for(int i = 0 ;i< 100; i++)
   m1.addItem(&i1,INVENTORY_DATASET[i][0],to_string(INVENTORY_DATASET[i][1]),INVENTORY_DATASET[i][2],INVENTORY_DATASET[i][3]);//adds item to inventory database.
 for(int i = 0 ; i<100; i++)
   c1.add_customer(CUSTOMER_DATASET[i][0],to_string(CUSTOMER_DATASET[i][1]));// adds item to customer database.
    
 do
 {
   cout<<"Enter your choice"<<endl;
   cout<<"1. To buy an item"<<endl;
   cout<<"2. To make payment"<<endl;
   cout<<"3. To cancel an item"<<endl;
   cout<<"4. To exit"<<endl;
   cin>>choice;

   switch(choice)								// switch-case for a menu driven program.
   {
     case 1: {
               long long productID;
               int quantity;
               cout<<"Enter product ID for the item and quantity of the item"<<endl;
               cin>>productID>>quantity;
               b1.buy_item(productID,quantity,&i1);
               break;
             }

     case 2: {
               long long customerID;
               string name;
               cout<<"Enter your mobile number"<<endl;
               cin>>customerID;

               if(c1.search_customer(customerID)==NULL)
               {
                 cin>>name;
                 c1.add_customer(customerID, name);
	       }
	       cout<<endl;
	       cout<<"Transaction ID: "<<transaction_id<<endl;
	       b1.assign_customer_id(customerID, &c1);
               b1.make_payment();
               b1.update_stock(&i1);
               cout<<endl;
               c1.update_points(customerID,b1.getTotalAmount());
               cout<<endl;
               flag = false;
               break;
             }

     case 3: {
               cout<<"Enter product ID to cancel"<<endl;
               long long productID_cancel;
               cin>>productID_cancel;
               b1.cancel_item(productID_cancel);
               break;
	     }

     case 4:{
               flag = false;
	       break;
	    }
			
     default: cout<<"Enter valid number"<<endl;    
   }
        
 }while(flag);
 cout<<"Below is the updated Inventory:"<<endl;
 Item1* temp = b1.getHead();
 if(temp)
 {
   while(temp!=NULL)//prints updated inventory after whole billing process.
   {
     i1.get_product_info(temp->productID);
     temp = temp->next;
   }
 }
 else
   cout<<"No items found"<<endl;
 
 return 0;
}

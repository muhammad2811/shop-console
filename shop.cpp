// Mahmoud Sayed Ashour
// 20200498
// Muhammad Mostafa Kamil
// 20200478

// This system adds information about the seller such as the name and email.
// It also adds items in the seller's store and information for each item such as the name, id, price and quantity.
// It also allows the possibility of selling.
// When a certain number of an item is requested to be sold, it decreases the available quantity.

#include <iostream>
#include <string>

using namespace std;
class Item {
    //private member
    int ID, quant;
    string name;
    float price;
    static int objID;
    friend class Seller;
public:
    //Default Constructor 
    Item()
    {
        name = "";
        quant = 0;
        price = 0;
        ID = objID;
    }

    //parameterized Constructor 
    Item(string n, int q, float p)
    {
        name = n;
        quant = q;
        price = p;
        ID = objID;
        objID++;
        if (price == 0 && quant == 0) { ID = 0; objID--; }//we use it if user ordered to print item does not exist
    }

    //copy Constructors 
    Item(const Item& o)
    {
        ID = o.ID;
        name = o.name;
        price = o.price;
        quant = o.quant;
    }

    //Setters
    void setName(string n)
    {
        name = n;
    }
    void setQ(int q)
    {
        quant = q;
    }
    void setprice(float p)
    {
        price = p;
    }

    //Getters
    string getName()
    {
        return name;
    }
    int getQ()
    {
        return quant;
    }
    int getid()
    {
        return ID;
    }
    float getprice()
    {
        return price;
    }

    //Operator overloading for the ==, +=,-=
    bool operator==(const Item& o)
    {
        if (name == o.name)
            return true;
        return false;
    }
    void operator+=(const int i)
    {
        quant += i;
    }
    void operator-=(const int i)
    {
        quant -= i;
    }

    //cout the information of items
    friend ostream& operator<<(ostream& out, const Item& o)
    {
        out << "ID: " << o.ID << "\tName: " << o.name
            << "\tPrice: " << o.price << "\tQuantity: " << o.quant;
        return out;
    }
};

class Seller {
    //private member
    string name, email;
    int maxI;
    Item* itemsArray;
public:
    //Default Constructor 
    Seller()
    {
        name = "";
        email = "em";
        maxI = 0;
    }

    //parameterized Constructor 
    Seller(string n, string em, int mxI, Item arr[])
    {
        name = n;
        email = em;
        maxI = mxI;
        itemsArray = new Item[maxI];
        for (size_t i = 0; i < maxI; i++)//to copy the element of array
        {
            itemsArray[i] = arr[i];
        }
    }

    //Getters
    string getName()
    {
        return name;
    }
    int getMaxI()
    {
        return maxI;
    }

    //Function to print items
    void printItems()
    {
        for (size_t i = 0; i < maxI; i++)//to loop the elment of array
        {
            if (itemsArray[i].getName() == "" && itemsArray[i].getprice() == 0);//Do not print anything if the item does not exist
            else//Print the information of the items inside the array
            {
                cout << itemsArray[i] << endl;
            }
        }
    }

    //A function that finds an item from the array by ID
    Item find(int ID)
    {
        for (size_t i = 0; i < maxI; i++)//for loop to find the item specific ID and return the item
        {
            if (itemsArray[i].getid() == ID) { return itemsArray[i]; }//return the item with ID be wanted
        }
        cout << "not found\n";
        return (Item("", 0, 0));//if it didn't find the item return no information 
    }

    //function is to sell an item if it is found and reduce its quantity
    bool sells(string item, int n)
    {
        int x = -1;
        for (size_t i = 0; i < maxI; i++)// to find the item with name
            if (itemsArray[i].getName() == item) { x = i; break; }

        if (x == -1)return false;// that mean .. there is no item with this name

        if (n <= itemsArray[x].getQ()) {// quantity is avilable
            itemsArray[x] -= n;
        }
        else {// quantity isn't avilable
            cout << "There is only " << itemsArray[x].getQ() << " of this Item\n";
        }
        return true; //that mean .. there is item with this name
    }

    //A function that adds new items in array if possible
    bool addItem(Item& o)
    {
        int x = -1, y = -1;
        for (size_t i = 0; i < maxI; i++)//for loop to add the item if it found
        {
            if (itemsArray[i].getName() == o.getName())//A condition that if the element does not exist before, the quantity will be increased
            {
                itemsArray[i] += o.getQ();
                x = 1;
                Item::objID--;
                break;
            }
            if (itemsArray[i].getprice() == 0)//A condition if there is no data in the index of array ,break from loop
            {
                y = i;
                break;
            }
        }
        if (x == -1 && y != -1)//A condition that if the element does not exist and there is a place within the array, it will be added
        {
            itemsArray[y] = o;
            return 1;
        }
        else if (x == -1 && y == -1)//A condition if the element does not exist and there is no place within the array,print there is no space 
        {
            cout << "didn't added , there is no place";
            return 0;
        }
    }

    //cout information seller
    friend ostream& operator<<(ostream& out, const Seller& o)
    {
        out << "Seller: " << o.name << "\nE-mail: " << o.email;
        return out;
    }

    //Destructor
    ~Seller()
    {
        delete[] itemsArray;
    }
};
int Item::objID = 1;

int main()
{
    cout << "please enter your name : ";
    string name;
    cin >> name;
    cout << "pleas enter your email : ";
    string email;
    cin >> email;
    cout << "please enter your store capacity : ";
    int n;
    cin >> n;
    //the menu
    cout << endl << "1. Print My Info.";
    cout << endl << "2. Add An Item.";
    cout << endl << "3. Sell An Item.";
    cout << endl << "4. Print Items.";
    cout << endl << "5. Find an Item by ID.";
    cout << endl << "6. Exi.";
    cout << endl << endl << "enter your choose from menu : ";
    int m;

    Item* i = new Item[n];
    Seller s(name, email, n, i);

    //while loop to enter any order from users 
    while (cin >> m)
    {
        if (m == 1)
        {
            cout << s;
        }
        else if (m == 2)
        {
            cout << "enter the Item name ";
            string na;
            cin >> na;
            cout << "enter the quant ";
            int qu;
            cin >> qu;
            cout << "enter the price ";
            float pr;
            cin >> pr;
            Item opj(na, qu, pr);
            s.addItem(opj);
        }
        else if (m == 3)
        {
            cout << "enter the Item name ";
            string na;
            cin >> na;
            cout << "enter the quant ";
            int qu;
            cin >> qu;
            s.sells(na, qu);
        }
        else if (m == 4)
        {
            s.printItems();
        }
        else if (m == 5)
        {
            int id;
            cout << "enter ID's item ";
            cin >> id;
            cout << s.find(id);
        }
        else if (m == 6)
        {
            break;
        }
        cout << endl << endl << "enter your choose from menu : ";
    }
}

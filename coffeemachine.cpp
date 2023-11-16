#include<iostream>
#include<iomanip>
#include<map>
#include<vector>
#include<algorithm>
#include<string>

using namespace std;

class Menu
{
    public:
    map<string,int>menu{
        {"latte",25},
        {"espresso",30},
        {"capuccino",35}
    };

    //to display the contents of the menu
    void display_menu() {
    cout << "Menu:" << endl;
    cout << left << setw(15) << "Item" << "Price" << endl;
    cout << "-----------------------" << endl;
    
    for (const auto &item : menu) {
        cout << left << setw(15) << item.first << "Rs." << item.second << endl;
    }
}

    //to check if the entered drink is in the menu
    bool find_drink(string drink)
    {
        for(auto i:menu){
            if(i.first==drink){
            return true;
            }
        }

        cout<<"Your drink"<<drink<<" is not available.Sorry!"<<endl;
        return false;
    }

};    
class ingredients{
    protected:
    int milk=200;
    int water=300;
    int coffee=100;
    public:

    //displays the quantity of ingredients
     void report()
    {
        cout<<"Available Ingredients"<<endl;
        cout<<left<<setw(15)<<"Milk"<<milk<<"ml"<<endl;
        cout<<left<<setw(15)<<"Water"<<water<<"ml"<<endl;
        cout<<left<<setw(15)<<"Coffee Powder"<<coffee<<"g"<<endl;
    }
    //to calculate the quantity of ingredients consumed
    bool consume_ingredients(int milk_needed,int water_needed,int coffee_needed){
        if(milk_needed<milk && water_needed<water && coffee_needed<coffee){
            milk-=milk_needed;
            water-=water_needed;
            coffee-=coffee_needed;
            return true;
        }
        else{
            cout<<"Sorry!Shoratge of ingredients"<<endl;
            return false;
        }
    }
};

//this class is derived from class ingredients
class coffee_maker:public ingredients
{
    ingredients &ingdts;
public:
    coffee_maker(ingredients &ingredientsInstance):ingdts(ingredientsInstance){}
    void get(string order) {
        if (order == "latte") {
                ingdts.consume_ingredients(15, 20, 10);
                cout << "Enjoy your latte!!" << endl;
            }
    
        else if(order=="espresso"){
             ingdts.consume_ingredients(25,30,15);
             cout<<"Enjoy your espresso!!"<<endl;
        }
        else if(order=="capuccino"){
            ingdts.consume_ingredients(30,25,22);
            cout<<"Enjoy your capuccino!!"<<endl;
        }
    }
};

class payment:public Menu
{
    int amt,money=0;

    public:
    //to accept the payments from the user
    bool make_payment(string order){
        for (auto i:menu){
            if(order==i.first){
                cout<<"Please make the payment!"<<endl;
                cin>>amt;
                if(amt>=i.second){
                    if(amt>i.second){
                        cout<<"please collect your change : Rs."<<amt-i.second<<endl;
                    }
                    money+=i.second;
                    return true;
                }
                else{
                    cout<<"Sorry!Insufficient amount"<<endl;
                    return false;
                }
            }
        }
    }
    //displays the amount in the machine
   void display_money()
   {
    cout<<"TOTAL AMOUNT:"<<money<<endl;
   }
};

int main()
{
    Menu menu;
    bool is_on=true;
    string choice,order,user,password;
    bool drink=false;
    ingredients ingredients;
    coffee_maker coffee(ingredients);
    payment pay;


    while(is_on)
    {
        cout<<"User or Owner?"<<endl;
        cin>>user;
        transform(user.begin(), user.end(), user.begin(),::tolower);//transforms user entered input to lowercase
        if(user=="owner")
        {
            cout<<"Enter Password"<<endl;
            cin>>password;
            if(password=="AMJG"){
            ingredients.report();
            pay.display_money();
            cout<<endl;
            
            cout<<"Should the machine be on?(Enter off to close)"<<endl;
            cin>>choice;
            if(choice=="off")
            is_on=false;
            }

        }

        else if(user=="user"){
        cout<<endl;
        menu.display_menu();
        cout<<endl;
            cout<<"Enter your drink((Enter 'np' for no orders)"<<endl;//takes innput from user
            cin>>order;
            transform(order.begin(), order.end(), order.begin(),::tolower);
            if(order=="np"){
                cout<<"have a nice day!"<<endl;
            }
            else{
                if(menu.find_drink(order)){
                    if(pay.make_payment(order)){
                     coffee.get(order);   
                    }      
            }
        }
    
    }
    }

    return 0;
}
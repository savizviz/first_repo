#include <iostream>
#include <vector>
#include <string>
#include <set>
#include <map>

#define pending "Pending"
#define failed "Failed"
#define completed "Completed"
#define addProduct "add_product"
#define increaseQuantity "increase_quantity"
#define addOrder "add_order"
#define processOrders "process_orders"
#define reportPending "report_pending"
#define soldQuantity "sold_quantity"
#define showStock "show_stock"
#define ok "OK"

using namespace std;

struct orderInfo {
    string customerName;
    string productName;
    int quantity;
    string status;
};

struct productInfo {
    string productName;
    int productQuantity;

    bool operator<(const productInfo& other) const {
        return productName < other.productName;  
    }
};


void add_product(const string& product_name, int quantity, map<string,int>& products) {
    products[product_name] = quantity;
}

void increase_quantity(const string& product_name, int count, map<string,int>& products) {
    products[product_name] += count;
}

vector<orderInfo> add_order(string& customer_name,const string& product_name,int& quantityOfOrder) {
    vector<orderInfo> newOrder;
    newOrder. push_back({customer_name, product_name, quantityOfOrder,pending});
    return newOrder;
}

void process_orders(vector<orderInfo>& orders, map<string,int>& products) {
    
    for(int i = 0; i < orders.size(); i++) {
        for(auto& pair : products) {
            if (orders[i]. status == pending && pair. first == orders[i]. productName && pair. second >= orders[i]. quantity) {
                pair. second = pair. second - orders[i]. quantity;
                orders[i]. status = completed;
            }
            else if (orders[i]. status == pending && pair. first == orders[i]. productName && pair. second < orders[i]. quantity) {
                orders[i]. status = failed;
            }
        }
    }
}

void report_pending(const vector<orderInfo>& orders) {
    int has_pending = 0;
    for(int i = 0; i < orders.size(); i++) {
        if(orders[i]. status == pending) {
            ++has_pending;
            cout << (i+1) << '.' << ' ' << orders[i]. customerName << ": " << orders[i]. productName << ' ' << orders[i]. quantity << endl;
        }
    }
    if (!has_pending) {
        cout << "No pending orders" << endl;
    }
}

int sold_quantity(const vector<orderInfo>& orders,const string& product_name) {
    int total_sold_quantity = 0;
    for(int i = 0; i < orders.size(); i++) {
        if (orders[i]. status == completed && orders[i]. productName == product_name) {
            total_sold_quantity += orders[i]. quantity;
        }
    }
    return total_sold_quantity;
}

void show_stock(const map<string,int>& products) {
    int stock = 0;
    
    set<productInfo> products_info; //we do this, because we need stocks list in alphabetic order
    
    for(auto & pair : products) {
        products_info.insert({pair. first,pair.second});
    }
    int i = 0;
    for(const auto& it : products_info) {
        ++stock;
        cout << (i+1) << '.' << ' ' << it.productName << ": " << it. productQuantity << endl;
        i++;
    }
    if(!stock) {
        cout << "No products found"<<endl;
    }
}

void get_commands() {

    string command;
    string product_name;
    string customer_name;
    int quantity = 0;
    int quantityOfOrder = 0;
    int count = 0;
    int total_sold = 0;
    map<string,int> products;
    vector<orderInfo> orders;

    while (cin >> command) {
        if (command == addProduct){
            cin >> product_name >> quantity;
            add_product(product_name,quantity,products);
            cout << ok << endl;
        }
        else if (command == increaseQuantity) {
            cin >> product_name >> count;
            increase_quantity(product_name,count,products);
            cout << ok << endl;
        }

        else if (command == addOrder) {
            cin >> customer_name >> product_name >> quantityOfOrder;
            auto newOrder = add_order(customer_name,product_name,quantityOfOrder);
            orders.insert(orders.end(), newOrder.begin(), newOrder.end()); 
            cout << ok << endl;
        }

        else if (command == processOrders) {
            process_orders(orders,products);
        }
        else if (command == reportPending) {
            report_pending(orders);
        }
        else if (command == soldQuantity) {
            total_sold = sold_quantity(orders,product_name);
            cout << total_sold << endl;
        }
        else if(command == showStock) {
            show_stock(products);
        }
    }
}

int main() {
    get_commands();
    return 0;
}
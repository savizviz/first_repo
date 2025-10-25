#include <iostream>
#include <string>
using namespace std;

void say_hello() {
    cout << "Hello";
}

int main() {
    string name;
    cin >> name;
    cout << "hi" << name << endl;
    say_hello();
    cout << "hi";
    return 0;
}
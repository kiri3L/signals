#include <iostream>

using namespace std;

class A {
public:
    int foo(string & s){
        cout << s;
        return 0;
    }
};


#define SIGNAL_D(signal_f) ((void(*)(string &))((&signal_f)))
#define HANDLER_D(handler_f) ((void(*)(cl_base*,string & ))(&(handler_f)))

int foo(string & s){
    cout << s;
    return 0;
}

int main() {
    void(*f)(string &) = SIGNAL_D(foo);
    string s = "Hello, World\n";
    f(s);
    return 0;
}

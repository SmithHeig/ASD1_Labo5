//HIDE
// Codecheck 1 teste l’insertion, l’accès et la suppression
//  d’éléments en queue ou en position quelconque, ainsi que
//  le constructeur et destructeur simple et les exceptions
//  levées par votre code.

#include <iostream>
using namespace std;

#include "ResizableArray.cpp"

int main() {
    
    {
        cout << "Constructeur par défaut";
        ResizableArray<int> v;
        cout << "\n" << v;
        /*cout << "\nreserve(5)";
        v.reserve(5);
        cout << "\n" << v;
        cout << "\n7 fois push_back(rand() % 10)";
        for(size_t i = 0;i < 7; ++i) {
            v.push_back(rand() % 10);
            cout << "\n" << v;
        }
        cout << "\nresize(12)";
        v.resize(12);
        cout << "\n" << v;
        cout << "\n6 fois pop_back()";
        for(size_t i = 0;i < 6; ++i) {
            v.pop_back();
            cout << "\n" << v;
        }
        cout << "\nback() = 42";
        v.back() = 42;
        cout << "\n" << v;
        cout << "\nresize(2)";
        v.resize(2);
        cout << "\n" << v;
    }
    
    {
        cout << "\nConstructeur de 7 éléments";
        ResizableArray<short> v(7);
        cout << "\n" << v;
        cout << "\n7 fois insert(2*i,rand() % 10)";
        for(size_t i = 0;i < 7; ++i) {
            v.insert(2*i,rand() % 10);
            cout << "\n" << v;
        }
        cout << "\n10 fois erase(size()/2)";
        for(size_t i = 0;i < 10; ++i) {
            v.erase(v.size()/2);
            cout << "\n" << v;
        }
        cout << "\nshrinkToFit";
        v.shrinkToFit();
        cout << "\n" << v;
        cout << "\nat(1) = 42";
        v.at(1) = 42;
        cout << "\n" << v;
        cout << "\nreserve(13)";
        v.reserve(13);
        cout << "\n" << v;
        
        try {
            v.at(4) = 42;
            cout << "\nPas d'exception";
            cout << "\n" << v;
        } catch( out_of_range& e ) {
            cout << "\nout_of_range ";
        } catch(...) {
            cout << "\nAutre exception ";
        }
        
        try {
            v.insert(4,42);
            cout << "\nPas d'exception";
            cout << "\n" << v;
        } catch( out_of_range& e ) {
            cout << "\nout_of_range ";
        } catch(...) {
            cout << "\nAutre exception ";
        }
        
        try {
            v.insert(6,42);
            cout << "\nPas d'exception";
            cout << "\n" << v;
        } catch( out_of_range& e ) {
            cout << "\nout_of_range ";
        } catch(...) {
            cout << "\nAutre exception ";
        }
        
        try {
            v.erase(5);
            cout << "\nPas d'exception";
            cout << "\n" << v;
        } catch( out_of_range& e ) {
            cout << "\nout_of_range ";
        } catch(...) {
            cout << "\nAutre exception ";
        }
        
        try {
            v.resize(0);
            v.back() = 42;
            cout << "\nPas d'exception";
        } catch( runtime_error& e ) {
            cout << "\nruntime_error ";
        } catch(...) {
            cout << "\nAutre exception ";
        }
        
        try {
            v.pop_back();
            cout << "\nPas d'exception";
        } catch( runtime_error& e ) {
            cout << "\nruntime_error ";
        } catch(...) {
            cout << "\nAutre exception ";
        }
        
        cout << "\n";*/
    }

}

//HIDE
/* 	Codecheck 1 teste l’insertion, l’accès et la suppression d’éléments en queue ou en position quelconque, ainsi que le constructeurs et destructeur simple et les exceptions levées par votre code.
	
 Codecheck 2 teste les mêmes éléments que le 1, mais aussi les constructeur de copie, opérateur d’affectation, constructeur et opérateur de déplacement et les garanties offertes par votre code en cas d’exceptions.
 */


#include <iostream>
#include <vector>
using namespace std;

#include "ResizableArray.cpp"

class Int {
    int val;
public:
    
    static int dc;
    static int ic;
    static int cc;
    static int d;
    static int egal;
    
    static void ResetCounts() {
        dc = ic = cc = d = egal = 0;
    }
    
    static int copyConstructBombValue;
    static int copyAssignBombValue;
    
    Int() : val(0) {
        cout << "(CD) ";
        dc++;
    }
    Int(int i) : val(i) {
        cout << "(C" << i << ") " << flush;
        ic++;
    }
    Int(const Int& i) : val(i.val) {
        if (i.val == copyConstructBombValue) throw std::logic_error("Int::CopyConstructor");
        cout << "(CC" << val << ") ";
        cc++;
    }
    Int& operator=(const Int& i) {
        if (i.val == copyAssignBombValue) throw std::logic_error("Int::Copy=");
        val = i.val;
        cout << "(=" << val << ") " << flush;
        egal++;
        return *this;
    }
    ~Int() {
        cout << "(D" << val << ") " << flush;
        d++;
    }
    bool operator< ( const Int& i ) const noexcept {
        return val < i.val;
        }
        friend ostream& operator<< ( ostream& os, const Int& i );
        };
        
        int Int::copyAssignBombValue = -1;
        int Int::copyConstructBombValue = -3;
        
        int Int::cc = 0;
        int Int::dc = 0;
        int Int::ic = 0;
        int Int::egal = 0;
        int Int::d = 0;
        
        ostream& operator<< ( ostream& os, const Int& i ) {
            os << i.val;
            return os;
        }
        
        
        template <typename T>
        void tester ( const int N = 5, const int M = 7 ) {
            
            {
                cout << "Constructeur par défaut ";
                ResizableArray<T> v;
                cout << "\n" << v;
                cout << "\nreserve(" << N << ") ";
                v.reserve(N);
                cout << "\n" << v;
                for(size_t i = 0;i < M; ++i) {
                    int val = rand() % 10;
                    cout << "\npush_back(" << val << ") ";
                    v.push_back(val);
                    cout << "\n" << v;
                }
                cout << "\nresize(" << (v.capacity() + 2) << ") ";
                v.resize(v.capacity() + 2);
                cout << "\n" << v;
                for(size_t i = 0;i <= M; ++i) {
                    cout << "\npop_back() ";
                    v.pop_back();
                    cout << "\n" << v;
                }
                cout << "\nback() = 42 ";
                v.back() = 42;
                cout << "\n" << v;
                cout << "\nresize(1) ";
                v.resize(1);
                cout << "\n" << v;
                cout << "\nDestructeur ";
            }
            
            {
                cout << "\n\nConstructeur de " << M << " éléments ";
                ResizableArray<T> v(M);
                cout << "\n" << v;
                for(size_t i = 0;i < M; ++i) {
                    int val = 1 + rand() % 9;
                    cout << "\ninsert(" << 2*i << "," << val << ") ";
                    v.insert(2*i,val);
                    cout << "\n" << v;
                }
                cout << "\n" << ((3*M)/2) << " fois erase(size()/2)";
                for(size_t i = 0;i < ((3*M)/2); ++i) {
                    cout << "\nerase(" << v.size()/2 << ") ";
                    v.erase(v.size()/2);
                    cout << "\n" << v;
                }
                cout << "\nshrinkToFit";
                v.shrinkToFit();
                cout << "\n" << v;
                cout << "\nat(1) = 42";
                v.at(1) = 42;
                cout << "\n" << v;
                cout << "\nreserve(" << 2*M << ")";
                v.reserve(2*M);
                cout << "\n" << v;
                
                try {
                    cout << "\nat(" << v.size() << ") = 42 ";
                    v.at(v.size()) = 42;
                    cout << "\nPas d'exception";
                    cout << "\n" << v;
                } catch( out_of_range& e ) {
                    cout << "\nout_of_range ";
                } catch(...) {
                    cout << "\nAutre exception ";
                }
                
                try {
                    cout << "\ninsert(" << v.size() << ",42) ";
                    v.insert(v.size(),42);
                    cout << "\nPas d'exception";
                    cout << "\n" << v;
                } catch( out_of_range& e ) {
                    cout << "\nout_of_range ";
                } catch(...) {
                    cout << "\nAutre exception ";
                }
                
                try {
                    cout << "\ninsert(" << v.size()+1 << ",42); ";
                    v.insert(v.size()+1,42);
                    cout << "\nPas d'exception";
                    cout << "\n" << v;
                } catch( out_of_range& e ) {
                    cout << "\nout_of_range ";
                } catch(...) {
                    cout << "\nAutre exception ";
                }
                
                try {
                    cout << "\nerase(" << v.size() << "); ";
                    v.erase(v.size());
                    cout << "\nPas d'exception";
                    cout << "\n" << v;
                } catch( out_of_range& e ) {
                    cout << "\nout_of_range ";
                } catch(...) {
                    cout << "\nAutre exception ";
                }
                
                try {
                    cout << "\nresize(0)";
                    v.resize(0);
                    cout << "\nback() = 42";
                    v.back() = 42;
                    cout << "\nPas d'exception";
                } catch( runtime_error& e ) {
                    cout << "\nruntime_error ";
                } catch(...) {
                    cout << "\nAutre exception ";
                }
                
                try {
                    cout << "\npop_back()";
                    v.pop_back();
                    cout << "\nPas d'exception";
                } catch( runtime_error& e ) {
                    cout << "\nruntime_error ";
                } catch(...) {
                    cout << "\nAutre exception ";
                }
                
                cout << "\nDestructeur ";
            }
            
            cout << "\n\nConstructeur de 3 éléments ";
            ResizableArray<T> v(3);
            cout << "\n" << v;
            cout << "\nreserve(6) ";
            v.reserve(6);
            cout << "\n" << v;
            for(size_t i = 0; i < v.size(); ++i) {
                int val = rand()%9+1;
                cout << "\nat(" << i << ") = " << val << " ";
                v.at(i) = val;
            }
            cout << "\n" << v;
            
            {
                cout << "\n\nConstructeur de copie w(v)";
                ResizableArray<T> w(v);
                cout << "\nv: " << v;
                cout << "\nw: " << w;
                for(size_t i = 0; i < w.size(); ++i) {
                    int val = rand()%9+1;
                    cout << "\nw.at(" << i << ") = " << val << " ";
                    w.at(i) = val;
                }
                cout << "\nw.reserve(4) ";
                w.reserve(4);
                cout << "\nw.push_back(42) ";
                w.push_back(42);
                cout << "\nv: " << v;
                cout << "\nw: " << w;
                cout << "\nOpérateur d'affectation par copie v=w ";
                v = w;
                cout << "\nv: " << v;
                cout << "\nw: " << w;
                for(size_t i = w.size(); i <= v.capacity(); ++i) {
                    int val = rand()%9+1;
                    cout << "\nw.push_back(" << val << ") ";
                    w.push_back(val);
                }
                cout << "\nv: " << v;
                cout << "\nw: " << w;
                cout << "\nOpérateur d'affectation par copie v=w ";
                v = w;
                cout << "\nv: " << v;
                cout << "\nw: " << w;
                cout << "\nDestructeur(w) ";
            }
            
            {
                cout << "\n\nConstructeur de copie w(move(v)) ";
                ResizableArray<T> w(move(v));
                cout << "\nv: " << v;
                cout << "\nw: " << w;
                for(size_t i = 0; i <= 2; ++i) {
                    int val = rand()%9+1;
                    cout << "\nw.push_back(" << val << ") ";
                    w.push_back(val);
                }
                cout << "\nw: " << w;
                cout << "\nOpérateur d'affectation par déplacement v=move(w) ";
                v = move(w);
                cout << "\nv: " << v;
                cout << "\nw: " << w;
                cout << "\nDestructeur(w) ";
            }
            
            cout << "\n\nshrinkToFit";
            v.shrinkToFit();
            cout << "\n" << v;
            
            
            try {
                cout << "\nbad_alloc au resize ";
                v.resize(-1);
                cout << "\nException non levée ";
            } catch ( bad_alloc& e ) {
                cout << "\nbad_alloc capturée ";
                cout << "\n" << v;
            } catch (...) {
                cout << "\nPas la bonne exception ";
            }
            
            try {
                cout << "\nbad_alloc au reserve ";
                v.reserve(-1);
                cout << "\nException non levée ";
            } catch ( bad_alloc& e ) {
                cout << "\nbad_alloc capturée ";
                cout << "\n" << v;
            } catch (...) {
                cout << "\nPas la bonne exception ";
            }
            
            cout << "\n\nConstructeur de 3 éléments ";
            ResizableArray<T> w(3);
            cout << "\nw: " << w;
            
            Int::copyConstructBombValue = 42;
            
            try {
                cout << "\nlogic_error a la copie par constructeur de l'élément 42";
                cout << "\nreserve(15)";
                v.reserve(15);
                cout << "\nException non levée ";
            } catch ( logic_error& e ) {
                cout << "\nlogic_error capturée ";
                cout << "\n" << v;
            } catch (...) {
                cout << "\nPas la bonne exception ";
            }
            
            try {
                cout << "\nresize(15)";
                v.resize(15);
                cout << "\nException non levée ";
            } catch ( logic_error& e ) {
                cout << "\nlogic_error capturée ";
                cout << "\n" << v;
            } catch (...) {
                cout << "\nPas la bonne exception ";
            }
            
            
            cout << "\nDestructeur(v) ";
            
        }
        
        int main() {
            
            tester<Int>(3,5);
            
            cout << "\n\n";
            cout << "Constructeur par défaut         : " << Int::dc << "\n";
            cout << "Constructeur par initialisation : " << Int::ic << "\n";
            cout << "Constructeur de copie           : " << Int::cc << "\n";
            cout << "Opérateur d'affectation         : " << Int::egal << "\n";
            cout << "Destructeur                     : " << Int::d << "\n";
            cout << Int::dc << " + " << Int::ic << " + " << Int::cc << " = "
            << Int::d << " ? " << ( Int::dc + Int::ic + Int::cc - Int::d ? "KO":"OK") << "\n";
            
        }

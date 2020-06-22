//Хренов Геннадий М8О-207Б

//реализовать класс Bitstring с прегрузкой операторов

#include<iostream>
#include<string.h>
using namespace std;
 
class Bitstring{
    private:
        unsigned long long x;
        unsigned int  y;

    public: 
        Bitstring(unsigned long long part64, unsigned int part32): x(part64), y(part32)
        {}

        friend const Bitstring operator&(const Bitstring& w, const Bitstring& q); 
        friend const Bitstring operator|(const Bitstring& w, const Bitstring& q); 
        friend const Bitstring operator^(const Bitstring& w, const Bitstring& q);
        friend const Bitstring operator~(const Bitstring& w);
        friend  Bitstring operator ""_BS(const char* i);
        friend bool operator==(const Bitstring& w,const Bitstring& q);
        friend bool operator>(const Bitstring& w,const Bitstring& q);
        friend bool operator<(const Bitstring& w,const Bitstring& q);
        friend int Count_1 (unsigned long long x, unsigned int y);
    void print(const Bitstring q) {
            for(int i = 63; i >= 0; --i){
                printf("%llu", (q.x >> i)&1);
            }
            cout << " ";
            for(int i = 31; i >= 0; --i){
                printf("%u", (q.y >> i)&1);
            }
            cout << '\n';
        
    }
};

 int Count_1 (unsigned long long x, unsigned int y){
        int res = 0;
        while (x) {
            res++;
            x &= x-1;  // Забираем младшую единичку.
        }
  
         while (y) {
            res++;
            y &= y-1;  // Забираем младшую единичку.
        }
        return res;
    }

const Bitstring operator&(const Bitstring& w, const Bitstring& q){
    return Bitstring(w.x & q.x, w.y & q.y);     
} 

const Bitstring operator|(const Bitstring& w, const Bitstring& q){
    return Bitstring(w.x | q.x, w.y | q.y);
} 

const Bitstring operator^(const Bitstring& w, const Bitstring& q){
    return Bitstring(w.x ^ q.x, w.y ^ q.y);
} 

const Bitstring operator~(const Bitstring& w){
    return Bitstring(~w.x, ~w.y);
} 

bool operator==(const Bitstring& w,const Bitstring& q){
    return (Count_1(w.x, w.y) == Count_1(q.x, q.y));
}

bool operator>(const Bitstring& w,const Bitstring& q){
    return (Count_1(w.x, w.y) > Count_1(q.x, q.y));
}

bool operator<(const Bitstring& w,const Bitstring& q){
    return (Count_1(w.x, w.y) < Count_1(q.x, q.y));
}

Bitstring operator ""_BS(const char* i){
    int n = 0;
    char integ[32];
    while (i[n] != '.'){
        ++n;
    }

   for (int j = n + 1; j < strlen(i); j++){
        integ[j - (n + 1)] = i[j];
    }
    return Bitstring(atoll(i),atoi(integ));

    
}
void Shiftleft(unsigned long long x, unsigned int y,int n){
        x << n;
        y << n;    
    }
    void Shiftright(unsigned long long x, unsigned int y,int n){
        x >> n;
        y >> n;
    }

    void compare_1(unsigned long long a, unsigned int b,unsigned long long x, unsigned int y){
        if (Count_1(a, b) == Count_1(x, y)){
            printf("equal_1\n");
        } else printf("not_equal_1\n");             
    }

    void inclusion_check(unsigned long long a, unsigned int b,unsigned long long x, unsigned int y){
        if ((a | x) == a && (b | y) == b){
            printf("it`s inclusion\n");
        } else printf("it`s not inclusion\n");
    }

int main() {
    
    unsigned long long p1,p3;
    unsigned int p2,p4;
    cout << "operation on bitstrings\n";
    cout << "enter 2 Bitstring(ull, ui, ull, ui)\n";
    cin >> p1 >> p2 >> p3 >> p4;
    Bitstring d1(p1,p2);
    Bitstring d2(p3,p4);
    Bitstring answ(0,0);
    
    cout << "A:" << endl;
    answ.print(d1);
    cout << "B:" << endl;
    answ.print(d2);
    cout << "A & B:" << endl;
    answ.print(d1 & d2);
    cout << "A | B:" << endl;
    answ.print(d1 | d2);
    cout << "A ^ B" << endl;
    answ.print(d1 ^ d2);
    cout << "~A:" << endl;
    answ.print(~d1);


    if (d1 == d2){
        cout << "A equal B (by number of units)\n";
    }
    if (d1 > d2){
        cout << "A is bigger than B (by number of units)\n";
    }
    if (d1 < d2){

      cout << "A is smaller B (by number of units)\n";
    }

    cout << " <12.128> with literal <_BS> turn into class Bitstring:\n";
    answ.print(12.128_BS);
    return 0;
}
//Хренов Геннадий М8О-207Б

#include<iostream> 
using namespace std;
 
class Bitstring{
    
    public: unsigned long long a, resa;
    unsigned int b, resb;
    void AND(unsigned long long x, unsigned int y){
        resa = a & x;
        resb = b & y;
    }
    void OR(unsigned long long x, unsigned int y){
        resa = a | x;
        resb = b | y;
    }
    void XOR(unsigned long long x, unsigned int y){
        resa = a ^ x;
        resb = b ^ y;       
    }
    void NOT(unsigned long long x, unsigned int y){
        resa = ~x;
        resb = ~y;        
    }

    void Shiftleft(int n){
        resa = a << n;
        resb = b << n;    
    }
    void Shiftright(int n){
        resa = a >> n;
        resb = b >> n;
    }
    unsigned long long getResa(){
        return resa;
    }
    unsigned int getResb(){
        return resb;
    }
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

    void compare_1(unsigned long long x, unsigned int y){
        if (Count_1(a, b) == Count_1(x, y)){
            printf("equal_1\n");
        } else printf("not_equal_1\n");             
    }

    void inclusion_check(unsigned long long x, unsigned int y){
        OR(x,y);
        if (getResa() == a && getResb() == b){
            printf("it`s inclusion\n");
        } else printf("it`s not inclusion\n");
    }

    void print(const string type) {
        if(type == "bin") {
            for(int i = 63; i >= 0; --i){
                printf("%llu", (resa >> i)&1);
            }
            cout << " ";
            for(int i = 31; i >= 0; --i){
                printf("%u", (resb >> i)&1);
            }
            cout << '\n';
        }
    }
};

int main() {
    Bitstring m;
    unsigned long long x;
    unsigned int y;

    cout << "operation on bitstrings\n";
    cout << "enter 2 string(ull, ui, ull, ui)\n";
    cin >> m.a >> m.b >> x >> y;
    m.resa = m.a;
    m.resb = m.b;

    cout << "A:\n";
    m.print("bin");

    m.resa = x;
    m.resb = y;
    cout << "B:\n";
    m.print("bin");

    m.AND(x, y);
    cout << "and:\n";
    m.print("bin");
    cout << "произведена логическая операция И\n";
   
    m.OR(x,y);
    cout << "or:\n";
    m.print("bin");
    cout << "произведена логическая операция ИЛИ\n";

    m.XOR(x,y);
    cout << "xor:\n";
    m.print("bin");
    cout << "произведена логическая операция исключающее ИЛИ\n";

    m.NOT(x,y);
    cout << "not for B:\n";
    m.print("bin");
    cout << "произведена логическая операция НЕ для числа B\n";

    m.Shiftleft(3);
    cout << "left A on 3:\n";
    m.print("bin");
    cout << "произведен сдвиг влево на 3 бита числа А\n";

    m.Shiftright(2);
    cout << "right A on 2:\n";
    m.print("bin");
    cout << "произведен сдвиг вправо на 2 бита числа А\n";   

    cout << "подсчёт единиц в числе B\n";
    printf("count B: %d\n", m.Count_1(x,y));

    cout << "cравнение количества единиц в А и В\n";
    m.compare_1(x,y);
 
    cout << "проверка включения В в А\n";
    m.inclusion_check(x,y);

    return 0;

}
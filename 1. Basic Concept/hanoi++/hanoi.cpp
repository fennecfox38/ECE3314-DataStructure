#include <iostream>
#include <vector>
#include <string>
#include <sstream>
using namespace std;

vector<int> A, B, C;
int cnt=0;
int siz=0;

void printStack(vector<int> &v);
void hanoi(int n, vector<int> &src, vector<int> &dst, vector<int> &tmp);

int main(void){
    cout << "Input : ";

    string buffer,str;
    getline(cin,buffer);
    stringstream input(buffer);

    while(input>>str)
        C.push_back(stoi(str));
    siz = C.size();
    A.reserve(siz);
    for(vector<int>::reverse_iterator it=C.rbegin();it!=C.rend();++it)
        A.push_back(*it);
    C.clear();
    
    cout<<"          start : ";
    printStack(A);
    cout<<endl;

    hanoi(siz,A,C,B);
    return 0;
}

void hanoi(int n, vector<int> &src, vector<int> &dst, vector<int> &tmp){
    if(!n) return;

    hanoi(n-1,src,tmp,dst);

    dst.push_back(src.back());
    src.pop_back();
    cout<<++cnt<<" : Move disk "<<n<<" : ";
    printStack(A);
    printStack(B);
    printStack(C);
    cout<<endl;

    hanoi(n-1,tmp,dst,src);
}

void printStack(vector<int> &v){
    for(int i=siz-v.size();i>0;--i)
        cout<<"  ";
    for(vector<int>::reverse_iterator it=v.rbegin();it!=v.rend();++it){
        cout<<' '<<*it;
    }
}
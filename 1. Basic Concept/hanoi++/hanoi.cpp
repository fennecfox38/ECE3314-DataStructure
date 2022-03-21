/************************************************************************************************************************
 * File Name            : hanoi.c
 * Author               : Kang, Jun Gu
 * Student ID           : 1218XXXX
 * Date                 : 2022.03.21
 * Operating System     : Ubuntu 20.04.4 LTS
 * Compiler             : gcc 9.4.0
 * Build/Host/Target    : x86_64-linux-gnu
 ************************************************************************************************************************
 * version      : 1.0.0
 * description  : Calculate and Print the procedure to move all of the disks in proper ways
 *                (following the rule of 'Towers of Hanoi')
 * functions    : int main(void);
 *                void init(string buffer);
 *                void printStack(vector<int> &v);
 *                void hanoi(int n, vector<int> &src, vector<int> &dst, vector<int> &tmp);
 ************************************************************************************************************************/

#include <iostream>
#include <algorithm>
#include <vector>
#include <string>
#include <sstream>
using namespace std;

vector<int> A, B, C;                        // each stack bar of disk.
int cnt=0;                                  // count for the number of movement.
int siz=0;                                  // the number of disks.

void init(string buffer);
void printStack(vector<int> &v);
void hanoi(int n, vector<int> &src, vector<int> &dst, vector<int> &tmp);

/************************************************************************************************************************
 * function     : int main(void);
 * description  : The main function. Get input and process it, and call function 'hanoi'.
 ************************************************************************************************************************
 * Input        : void
 * Output       : int
 ************************************************************************************************************************/
int main(void){
    cout << "Input : ";

    string input;
    getline(cin,input);                     // get the one line from inputstream.

    init(input);                            // process the input string and store disks properly.
    
    cout<<"         start  : ";
    printStack(A);                          // print the initial condition.
    cout<<endl;

    hanoi(siz,A,C,B);                       // Move 'siz' th disk from A to C (using B as temporary space)
    return 0;
}

/************************************************************************************************************************
 * function     : void hanoi(int n, vector<int> &src, vector<int> &dst, vector<int> &tmp);
 * description  : Calculate and print a message that tells which disk should be moved from where to where in what order.
 *                It moves upper (n-1) disks to temporary space first, (by recursive call)
 *                then move 'n'th disk to destination,
 *                and move (n-1) disks to destination again. (by recursive call)
 *                n<0 is not allowed therefore return (terminate recursion) 
 ************************************************************************************************************************
 * Input        : int n (The size of the stack of sorted disks)
 *                vector<int> src (The container where the disk stack to move is)
 *                vector<int> dst (The container that the disk stack should be moved to)
 *                vector<int> tmp (The container that can be used as a temporary space in the moving process)
 * Output       : void
 ************************************************************************************************************************/
void hanoi(int n, vector<int> &src, vector<int> &dst, vector<int> &tmp){
    if(n<=0) return;                        // Do not execute if n<0.

    hanoi(n-1,src,tmp,dst);                 // Move stack of (n-1) disks to tmp (temporarily)

    dst.push_back(src.back());              // Move 'n'th disk from src to disk
    src.pop_back();                         //

    cout<<++cnt<<" : Move disk "<<n<<" : "; // Print moving information
    printStack(A);                          //
    printStack(B);                          //
    printStack(C);                          //
    cout<<endl;                             //

    hanoi(n-1,tmp,dst,src);                 // Move stack of (n-1) disk from tmp to dst.
}

/************************************************************************************************************************
 * function     : void printStack(vector<int> &v);
 * description  : Print the values of all elements of the given vector v in the format requested.
 *                It prints from top to bottom  (access element in reverse order)
 *                It prints blank for empty space (for alignment)
 ************************************************************************************************************************
 * Input        : vector<int> &v (The vector container that should be printed)
 * Output       : void
 ************************************************************************************************************************/
void printStack(vector<int> &v){
    for(int i=siz-v.size();i>0;--i)         // print blank for empty space (alignment)
        cout<<"  ";
    for(vector<int>::reverse_iterator it=v.rbegin();it!=v.rend();++it){ //access element in reverse order
        cout<<' '<<*it;                     // print the value of disk
    }
}

/************************************************************************************************************************
 * function     : void init(string buffer);
 * description  : Interpret the input (split by blank, convert to integer)
 *                and sort in legal order and save into container.
 ************************************************************************************************************************
 * Input        : string buffer (The string of a whole line from inputstream.)
 * Output       : void
 ************************************************************************************************************************/
void init(string buffer){
    stringstream input(buffer);             // convert to stringstream.
    string str;

    while(input>>str)                       // get element one by one iteratively.
        A.push_back(stoi(str));             // convert to integer and push it to stack A.
    siz = A.size();                         // store the total number of disks.
    C.reserve(siz);

    sort(A.begin(),A.end(),greater<int>()); // Sort disk in descending. (legal order)
}
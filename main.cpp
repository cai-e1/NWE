//====================================================
//main.cpp 
//
//demonstrates the accuracy of usecase.cpp using
//user input from the terminal.
//====================================================

#include <iostream>
using namespace std;
#include "bst.cpp"
#include "usecase.cpp"

//====================================================
//main()
//pre:none
//post: stirng of hexs values based on binary input from
//terminal
//====================================================
int main(){
    cout<< "Enter a binary combination (of 0's and 1's): "<<endl;
    string binarystring;
    cin>>binarystring;
    //uses usecase functions to convert values
    BST<string, string> *bst1 = create_bst<string, string>("binhex.txt");
    cout<< convert<string,string>(bst1, binarystring)<<endl;
}
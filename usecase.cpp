
//====================================================
//usecase.cpp
//
//creates a binary search tree of values from a given csv
//and creates a string of returned hex values through a 
//binary input using get() function
//====================================================

#include "iostream"
#include <sstream>
#include <string>
#include "fstream"
#include "bst.h"

using namespace std;

//====================================================
//create_bst(const string& csvfile)

//pre:none
//post:creates a binary search tree inputing values from 
//a csv file that takes in the first value as hex data 
//and the second value as binary data, separated by the ","
//====================================================
#include <string>
template <typename D, typename K>
BST<D,K>* create_bst(const string& csvfile)
{   //checks whether the csv file is able to open
    ifstream fin(csvfile);
    if (!fin.is_open()) {
        cerr << "Error: could not open file " << csvfile << endl;
        return nullptr;
    }
    //instantiate a new hashtable with size m
    BST<D,K>* bst = new BST<D,K>();
    string line;

    // Read each line from the CSV
    while (getline(fin, line)) {
        stringstream ss(line);
        string hex, binary;

        // Split by comma
        if (getline(ss, hex, ',') && getline(ss, binary)) {
            try {
                std::string hex_string = hex;
                std::string bin_string = binary;
                //create an element with this pair
                bst->insert(hex_string, bin_string);
            } catch (invalid_argument&) {
                cerr << "Invalid"<< endl;
            }
        }
    }

    fin.close();
    
    return bst;

}

//====================================================
//convert(BST<D,K>*bst, string bin)
//pre: binary search tree bst instantiated and bin is 
//a none empty value
//post: returns the string of hex values given a string
//of bianry values. 
//if binary value is not a multiple of four, the last 
//converted bianry value will be front padded with 0's 
//====================================================
template <typename D, typename K>
string convert(BST<D,K>*bst, string bin){
    //check if the tree is filled 
    if (bst == nullptr){
        cout<< "Tree is empty"<<endl;
        return "error";
    }
    //checks that the input is not also empty
    if (bin.empty()) {
    cerr << "Error: empty binary string" << endl;
    return "error";
}

    //find the hex in the hastable through get function
    try{
        string converting;
        string converted;
        //all values that don't need to be padded get converted
        while (bin.length()>=4){
            converting = bin.substr(bin.length() - 4, 4);
            bin.erase(bin.length() - 4, 4);
            converted = bst->get(converting) + converted;
        }
        //if last binary value has len<4, pad the front and convert
        if (bin.length()>0){
            while (bin.length()<4){
                bin = "0" + bin;
            }
            converted = bst->get(bin) + converted;
        }
        //return the full string of converted values
        return (converted);
    }

    catch (const std::exception& e) {
        cerr << "Error: could not find key " << bin << ": " << e.what() << endl;
        return "unfound";
    }

}
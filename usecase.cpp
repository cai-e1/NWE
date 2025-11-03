

#include "iostream"
#include <sstream>
#include <string>
#include "fstream"
#include "bst.h"

using namespace std;


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
                // cout<< bin_string <<" "<<hex_string<<endl;
                // cout << "Read line: [" << binary << "] -> [" << hex << "]" << endl;
                bst->insert(hex_string, bin_string);
            } catch (invalid_argument&) {
                cerr << "Invalid"<< endl;
            }
        }
    }

    fin.close();
    
    return bst;

}


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

    //if it is, find the hex in the hastable through get function
    try{
        string converting;
        string converted;
        while (bin.length()>=4){
            converting = bin.substr(bin.length() - 4, 4);
            bin.erase(bin.length() - 4, 4);
            converted = bst->get(converting) + converted;
        }
        if (bin.length()>0){
            while (bin.length()<4){
                bin = "0" + bin;
            }
            converted = bst->get(bin) + converted;
        }
        return (converted);
    }

    catch (const std::exception& e) {
        cerr << "Error: could not find key " << bin << ": " << e.what() << endl;
        return "unfound";
    }

}
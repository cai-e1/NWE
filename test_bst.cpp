//
//  test_bst.cpp
//  CS 271 BST Project: Test File
//
//  Expanded Test File
//

#include <stdlib.h>
#include <iostream>
#include <math.h>
#include "bst.cpp"
#include "usecase.cpp"

using namespace std;

void test_empty()
{
    try
    {
        BST<string, int> bst;
        if (!bst.empty())
        {
            cout << "Incorrect empty result." << endl;
        }

        // edge: remove on empty should be a no-op (and not throw)
        bst.remove(12345);
        if (!bst.empty())
        {
            cout << "Empty edge: remove on empty altered tree." << endl;
        }

        // edge: becomes non-empty after insert
        bst.insert("one", 1);
        if (bst.empty())
        {
            cout << "Incorrect empty result." << endl;
        }

        // edge: becomes empty again after removing the only node
        bst.remove(1);
        if (!bst.empty())
        {
            cout << "Empty edge: tree should be empty after removing sole node." << endl;
        }
    }
    catch (exception &e)
    {
        cerr << "Error in determining if BST is empty : " << e.what() << endl;
    }
}

void test_insert()
{
    try
    {
        BST<string, int> bst;
        bst.insert("one", 1);
        string bst_str = bst.to_string();
        if (bst_str != "1")
        {
            cout << "Incorrect result of inserting (\"one\", 1). Expected 1 but got : " << bst_str << endl;
        }

        // edge: negative and zero keys
        BST<string, int> signs;
        signs.insert("zero", 0);
        signs.insert("neg", -2);
        signs.insert("pos", 2);
        string signs_in = signs.in_order();
        if (signs_in != "-2 0 2")
        {
            cout << "Insert edge (neg/zero): expected -2 0 2 but got : " << signs_in << endl;
        }

        // Insert increasing 1..10
        for (int i = 2; i <= 10; i++)
        {
            bst.insert("some data", i);
        }
        bst_str = bst.to_string();
        if (bst_str != "1 2 3 4 5 6 7 8 9 10")
        {
            cout << "Incorrect result of inserting keys 1-10 in order. Expected 1 2 3 4 5 6 7 8 9 10 but got : " << bst_str << endl;
        }

        // Balanced-ish shape
        int vals[10] = {5, 2, 7, 1, 3, 4, 6, 9, 8, 10};
        BST<string, int> balanced_bst;
        for (int i = 0; i < 10; i++)
        {
            balanced_bst.insert("some data", vals[i]);
        }
        bst_str = balanced_bst.to_string();
        if (bst_str != "5 2 7 1 3 6 9 4 8 10")
        {
            cout << "Incorrect result of inserting keys {5, 2, 7, 1, 3, 4, 6, 9, 8, 10}. Expected 5 2 7 1 3 6 9 4 8 10 but got : " << bst_str << endl;
        }

        // edge: duplicates (policy: equals go right in this implementation)
        BST<string, int> dups;
        dups.insert("a", 5);
        dups.insert("b", 5);
        dups.insert("c", 5);
        string dups_bfs = dups.to_string();
        if (dups_bfs != "5 5 5")
        {
            cout << "Insert edge (duplicates): expected 5 5 5 but got : " << dups_bfs << endl;
        }
        string dups_in = dups.in_order();
        if (dups_in != "5 5 5")
        {
            cout << "Insert edge (duplicates inorder): expected 5 5 5 but got : " << dups_in << endl;
        }

        //trying different combinations of datatypes to insert
        BST<int, int> int_type;
        int_type.insert(6, 5);
        int_type.insert(7, 15);
        int_type.insert(98, 52);
        string int_type_ts = int_type.to_string();
        if (int_type_ts != "5 15 52")
        {
            cout << "Insert edge: expected 5 15 2 but got : " << int_type_ts << endl;
        }
        int max_int_data = int_type.max_data();
        if (max_int_data != 98){
            cout << "Max data edge: expected 52 but got : " << max_int_data << endl;
        }

        BST<float, float> float_type;
        float_type.insert(6.5, 5.895);
        float_type.insert(139.329, 5.35);
        float_type.insert(9.8, 5.362);
        string float_type_ts = float_type.to_string();
        if (float_type_ts != "5.895 5.35 5.362")
        {
            cout << "Insert edge: expected 5.895 5.35 5.362 but got : " << int_type_ts << endl;
        }
        float max_float_data = float_type.max_data();
        if (max_float_data != 6.5){
            cout << "Max data edge: expected 52 but got : " << max_float_data << endl;
        }

        BST<char, char> char_type;
        char_type.insert('a', 'a');
        char_type.insert('b', 'c');
        char_type.insert('d', 'a');
        string char_type_ts = char_type.to_string();
        if (char_type_ts != "a c a")
        {
            cout << "Insert edge: expected a c a : " << char_type_ts << endl;
        }
        char min_char_data = char_type.min_data();
        if (min_char_data != 'a'){
            cout << "Min data edge: expected a but got : " << min_char_data << endl;
        }

        BST<string, string> string_type;
        string_type.insert("all", "ball");
        string_type.insert("back", "call");
        string_type.insert("hi", "hello");
        string string_type_ts = string_type.to_string();
        if (string_type_ts != "ball call hello")
        {
            cout << "Insert edge: expected ball call hello : " << string_type_ts << endl;
        }
        string min_string_data = string_type.min_data();
        if (min_string_data != "all"){
            cout << "Min data edge: expected \"all\" but got : " << min_string_data << endl;
        }

    }
    catch (exception &e)
    {
        cerr << "Error inserting into bst : " << e.what() << endl;
    }
}

void test_get()
{
    try
    {
        BST<string, int> bst;

        // edge: get from empty -> default D()
        string val = bst.get(0);
        if (val != "")
        {
            cout << "Incorrect get result from empty bst. Expected 0 but got " << val << endl;
        }

        // edge: missing key in non-empty -> default D()
        int ks[] = {4, 2, 6, 1, 3, 5, 7};
        for (int k : ks) bst.insert("v" + to_string(k), k);

        if (bst.get(100) != "")
        {
            cout << "Get edge: expected default for missing key 100." << endl;
        }

        // normal case
        val = bst.get(1);
        if (val != "v1")
        {
            cout << "Incorrect get result. Expected \"v1\" but got : " << val << endl;
        }

        BST<string, string> bst1;
        string val1 = bst1.get(" ");
        if(val1!="") {
            cout << "Incorrect get result from empty string bst. Expected 0 but got " << val1 << endl;
        }
        string ks1[10] = {"a", "b", "c", "d", "e", "f", "g", "h", "i", "j"};
        for(int i = 0; i < 10; i++) {
            bst1.insert("hi", ks1[i]);
        }
        val1 = bst1.get("f");
        if(val1!="hi") {
            cout << "Incorrect get result from string bst. Expected 'hi' but got " << val1 << endl;
        }

        BST<float, float> bst2;
        float val2 = bst2.get((float)0.0);
        if (val2 != (float)0.0) {
            cout << "Incorrect get result from empty float bst. Expected 0.0 but got " << val2 << endl;
        }
        float ks2[6] = {(float)1.11, (float)2.22, (float)3.33, (float)4.44, (float)5.55, (float)6.66};
        float num = (float)3.00;
        for (int i = 0; i < 6; i++) {
            bst2.insert(num, ks2[i]);
            num += 1.0;
        }

        val2 = bst2.get((float)4.44);
        if (val2 != (float)6.00) {
            cout << "Incorrect get result from float bst. Expected '6.14' but got " << val2 << endl;
        }

        BST<int, int> bst3;
        int val3 = bst3.get(0);
        if (val3 != 0) {
            cout << "Incorrect get result from empty int bdt. Expected 0 but got " << val3 << endl;
        }
        int ks3[9] = {1, 2, 3, 4, 5, 6, 7, 8, 9};
        for (int i = 0; i < 9; i++) {
            bst3.insert(i, ks3[i]);
        }

        val3 = bst3.get(8);
        if (val3 != 7) {
            cout << "Incorrect get result from int bst. Expected 7 but got " << val3 << endl;
        }

    }
    catch (exception &e)
    {
        cerr << "Error in getting data from bst : " << e.what() << endl;
    }
}

void test_remove()
{
    try
    {
        // Base tree
        int vals[10] = {5, 2, 7, 1, 3, 4, 6, 9, 8, 10};
        BST<string, int> bst;
        for (int i = 0; i < 10; i++) bst.insert("x", vals[i]);

        // edge: removing non-existent key should not change structure
        string before = bst.to_string();
        bst.remove(1000);
        string after = bst.to_string();
        if (before != after)
        {
            cout << "Remove edge: removing missing key changed tree." << endl;
        }

        // leaf removal
        bst.remove(4); // 4 is a leaf in this shape
        string s = bst.to_string();
        if (s != "5 2 7 1 3 6 9 8 10")
        {
            cout << "Remove edge (leaf 4): expected 5 2 7 1 3 6 9 8 10 but got : " << s << endl;
        }

        // one-child (right) removal: make small tree 1->2
        BST<string, int> oneRight;
        oneRight.insert("a", 1);
        oneRight.insert("b", 2);
        oneRight.remove(1);
        if (oneRight.to_string() != "2")
        {
            cout << "Remove edge (root with one right child): expected 2 but got : " << oneRight.to_string() << endl;
        }

        // one-child (left) removal: 2<-1
        BST<string, int> oneLeft;
        oneLeft.insert("a", 2);
        oneLeft.insert("b", 1);
        oneLeft.remove(2);
        if (oneLeft.to_string() != "1")
        {
            cout << "Remove edge (root with one left child): expected 1 but got : " << oneLeft.to_string() << endl;
        }

        // two-children removal where successor is direct right child (6’s successor is 7 initially)
        BST<string, int> twoChildren1;
        for (int i = 0; i < 10; i++) twoChildren1.insert("x", vals[i]);
        twoChildren1.remove(7);
        if (twoChildren1.to_string() != "5 2 8 1 3 6 9 4 10")
        {
            cout << "Remove (two children, succ direct): expected 5 2 8 1 3 6 9 4 10 but got : " << twoChildren1.to_string() << endl;
        }

        // two-children removal where successor is deeper (successor has a right child)
        // Remove 5: successor is 6 (which has no left, but may have right in other shapes).
        BST<string, int> twoChildren2;
        for (int i = 0; i < 10; i++) twoChildren2.insert("x", vals[i]);
        twoChildren2.remove(5);
        string expected = "6 2 7 1 3 9 4 8 10"; // BFS after replacing 5 with 6
        if (twoChildren2.to_string() != expected)
        {
            cout << "Remove (two children, root): expected " << expected << " but got : " << twoChildren2.to_string() << endl;
        }
    }
    catch (exception &e)
    {
        cerr << "Error in removing node from bst : " << e.what() << endl;
    }
}

void test_max_data()
{
    try
    {
        // edge: single node
        BST<string, int> one;
        one.insert("only", 42);
        string md = one.max_data();
        if (md != "only")
        {
            cout << "max_data edge (single): expected \"only\" but got : " << md << endl;
        }

        int vals[10] = {5, 2, 7, 1, 3, 4, 6, 9, 8, 10};
        BST<string, int> balanced_bst;
        for (int i = 0; i < 10; i++)
        {
            balanced_bst.insert(to_string(vals[i]) + " data", vals[i]);
        }
        string max_str = balanced_bst.max_data();
        if (max_str != "10 data")
        {
            cout << "Incorrect result of max_data. Expected \"10 data\" but got : " << max_str << endl;
        }
    }
    catch (exception &e)
    {
        cerr << "Error in determining data of max node in bst : " << e.what() << endl;
    }
}

void test_max_key()
{
    try
    {
        // edge: chain increasing
        BST<string, int> chain;
        for (int i = 1; i <= 5; ++i) chain.insert("d", i);
        if (chain.max_key() != 5)
        {
            cout << "max_key edge (chain): expected 5 but got : " << chain.max_key() << endl;
        }

        int vals[10] = {5, 2, 7, 1, 3, 4, 6, 9, 8, 10};
        BST<string, int> balanced_bst;
        for (int i = 0; i < 10; i++)
        {
            balanced_bst.insert(to_string(vals[i]) + " data", vals[i]);
        }
        int max_k = balanced_bst.max_key();
        if (max_k != 10)
        {
            cout << "Incorrect result of max_key. Expected 10 but got : " << max_k << endl;
        }
    }
    catch (exception &e)
    {
        cerr << "Error in determining key of max node in bst : " << e.what() << endl;
    }
}

void test_min_data()
{
    try
    {
        // edge: single node
        BST<string, int> one;
        one.insert("only", 42);
        string md = one.min_data();
        if (md != "only")
        {
            cout << "min_data edge (single): expected \"only\" but got : " << md << endl;
        }

        int vals[10] = {5, 2, 7, 1, 3, 4, 6, 9, 8, 10};
        BST<string, int> balanced_bst;
        for (int i = 0; i < 10; i++)
        {
            balanced_bst.insert(to_string(vals[i]) + " data", vals[i]);
        }
        string min_str = balanced_bst.min_data();
        if (min_str != "1 data")
        {
            cout << "Incorrect result of min_data. Expected \"1 data\" but got : " << min_str << endl;
        }
    }
    catch (exception &e)
    {
        cerr << "Error in determining data of min node in bst : " << e.what() << endl;
    }
}

void test_min_key()
{
    try
    {
        // edge: chain decreasing
        BST<string, int> chain;
        int v[] = {5,4,3,2,1};
        for (int k : v) chain.insert("d", k);
        if (chain.min_key() != 1)
        {
            cout << "min_key edge (chain): expected 1 but got : " << chain.min_key() << endl;
        }

        int vals[10] = {5, 2, 7, 1, 3, 4, 6, 9, 8, 10};
        BST<string, int> balanced_bst;
        for (int i = 0; i < 10; i++)
        {
            balanced_bst.insert(to_string(vals[i]) + " data", vals[i]);
        }
        int min_k = balanced_bst.min_key();
        if (min_k != 1)
        {
            cout << "Incorrect result of min_key. Expected 1 but got : " << min_k << endl;
        }
    }
    catch (exception &e)
    {
        cerr << "Error in determining key of min node in bst : " << e.what() << endl;
    }
}

void test_successor()
{
    try
    {
        int vals[10] = {5, 2, 7, 1, 3, 4, 6, 9, 8, 10};
        BST<string, int> balanced_bst;
        for (int i = 0; i < 10; i++)
        {
            balanced_bst.insert(to_string(vals[i]) + " data", vals[i]);
        }

        int succ = balanced_bst.successor(4);
        if (succ != 5)
        {
            cout << "Incorrect result of successor of 4. Expected 5 but got : " << succ << endl;
        }
        succ = balanced_bst.successor(7);
        if (succ != 8)
        {
            cout << "Incorrect result of successor of 7. Expected 8 but got : " << succ << endl;
        }
        succ = balanced_bst.successor(10);
        if (succ != 0)
        {
            cout << "Incorrect result of successor of 10. Expected 0 but got : " << succ << endl;
        }

        // edge: successor of minimum
        if (balanced_bst.successor(1) != 2)
        {
            cout << "Successor edge (min): expected 2 but got : " << balanced_bst.successor(1) << endl;
        }

        // edge: successor of missing key -> default K()
        if (balanced_bst.successor(11) != 0)
        {
            cout << "Successor edge (missing key): expected 0 but got : " << balanced_bst.successor(11) << endl;
        }
    }
    catch (exception &e)
    {
        cerr << "Error in determining successor in bst : " << e.what() << endl;
    }
}

void test_in_order()
{
    try
    {
        BST<string, int> bst;
        for (int i = 1; i <= 10; i++)
        {
            bst.insert("some data", i);
        }
        string bst_str = bst.in_order();
        if (bst_str != "1 2 3 4 5 6 7 8 9 10")
        {
            cout << "Incorrect in_order result after inserting keys 1-10 in order. Expected 1 2 3 4 5 6 7 8 9 10 but got : " << bst_str << endl;
        }

        int vals[10] = {5, 2, 7, 1, 3, 4, 6, 9, 8, 10};
        BST<string, int> balanced_bst;
        for (int i = 0; i < 10; i++)
        {
            balanced_bst.insert("some data", vals[i]);
        }
        bst_str = balanced_bst.in_order();
        if (bst_str != "1 2 3 4 5 6 7 8 9 10")
        {
            cout << "Incorrect in_order result after inserting keys {5, 2, 7, 1, 3, 4, 6, 9, 8, 10}. Expected 1 2 3 4 5 6 7 8 9 10 but got : " << bst_str << endl;
        }

        // edge: duplicates appear contiguously in-order
        BST<string,int> dups;
        dups.insert("a", 5); dups.insert("b", 5); dups.insert("c", 5);
        string in = dups.in_order();
        if (in != "5 5 5")
        {
            cout << "in_order edge (duplicates): expected 5 5 5 but got : " << in << endl;
        }
    }
    catch (exception &e)
    {
        cerr << "Error getting keys in_order from bst : " << e.what() << endl;
    }
}

void test_trim()
{
    try
    {
        BST<string, int> bst;
        int vals[3] = {1, 0, 2};
        for (int i = 0; i < 3; i++)
        {
            bst.insert(to_string(vals[i]) + " data", vals[i]);
        }
        bst.trim(1, 2);
        string bst_str = bst.to_string();
        if (bst_str != "1 2")
        {
            cout << "Incorrect tree after trimming 1 0 2 with low=1, high=2. Expected 1 2 but got : " << bst_str << endl;
        }

        BST<string, int> bst2;
        int vals2[5] = {3, 0, 4, 2, 1};
        for (int i = 0; i < 5; i++)
        {
            bst2.insert(to_string(vals2[i]) + " data", vals2[i]);
        }
        bst2.trim(1, 3);
        bst_str = bst2.to_string();
        if (bst_str != "3 2 1")
        {
            cout << "Incorrect tree after trimming 3 0 4 2 1 with low=1, high=3. Expected 3 2 1 but got : " << bst_str << endl;
        }

        // edge: no-op when everything is inside range
        BST<string,int> all_in;
        int vals3[5] = {2,1,3,2,3};
        for (int i=0;i<5;i++) all_in.insert("d", vals3[i]);
        string before = all_in.to_string();
        all_in.trim(1,3);
        string after = all_in.to_string();
        if (before != after)
        {
            cout << "Trim edge (no-op) changed tree unexpectedly." << endl;
        }

        // edge: range that removes everything
        BST<string,int> all_out;
        all_out.insert("a", 1);
        all_out.insert("b", 2);
        all_out.trim(3, 4);
        if (!all_out.empty())
        {
            cout << "Trim edge (all removed): expected empty tree." << endl;
        }
    }
    catch (exception &e)
    {
        cerr << "Error in trimming the bst : " << e.what() << endl;
    }
}

void test_binhex()
{
    try
    {
        BST<string, string> *bst1 = create_bst<string, string>("binhex.txt");
        string bin1 = "111010100101";
        string expected_hex1 = "EA5";

        string hex1 = convert<string, string>(bst1, bin1);
        delete bst1;

        if (hex1 != expected_hex1)
        {
            cout << "Incorrect result converting " << bin1 << " to hex. Expected : " << expected_hex1 << ", but got : " << hex1 << endl;
        }
    }
    catch (exception &e)
    {
        cerr << "Error converting binary to hex : " << e.what() << endl;
    }

    try
    {
        BST<string, string> *bst2 = create_bst<string, string>("binhex.txt");
        string bin2 = "110101";
        string expected_hex2 = "35";

        string hex2 = convert<string, string>(bst2, bin2);
        delete bst2;

        if (hex2 != expected_hex2)
        {
            cout << "Incorrect result converting " << bin2 << " to hex. Expected : " << expected_hex2 << ", but got : " << hex2 << endl;
        }
    }
    catch (exception &e)
    {
        cerr << "Error converting binary to hex : " << e.what() << endl;
    }

    // edge: leading zeros should be handled (e.g., 0010 -> 2)
    try
    {
        BST<string, string> *bst3 = create_bst<string, string>("binhex.txt");
        string bin3 = "0010";
        string expected_hex3 = "2";
        string hex3 = convert<string, string>(bst3, bin3);
        delete bst3;
        if (hex3 != expected_hex3)
        {
            cout << "Incorrect result converting " << bin3 << " to hex. Expected : " << expected_hex3 << ", but got : " << hex3 << endl;
        }
    }
    catch (exception &e)
    {
        cerr << "Error converting binary with leading zeros : " << e.what() << endl;
    }
}

void test_to_string()
{
    try
    {
        // Single node -> exactly "1"
        BST<string, int> one;
        one.insert("one", 1);
        string s = one.to_string();
        if (s != "1")
        {
            cout << "Incorrect to_string for single node. Expected \"1\" but got : " << s << endl;
        }

        // Ascending inserts -> degenerate tree; BFS still yields 1..10
        BST<string, int> chain;
        for (int i = 1; i <= 10; ++i) chain.insert("x", i);
        s = chain.to_string();
        if (s != "1 2 3 4 5 6 7 8 9 10")
        {
            cout << "Incorrect to_string for ascending inserts. Expected 1 2 3 4 5 6 7 8 9 10 but got : " << s << endl;
        }

        // Mixed inserts building a more balanced shape -> exact BFS order
        int vals[10] = {5, 2, 7, 1, 3, 6, 9, 4, 8, 10};
        BST<string, int> shaped;
        for (int i = 0; i < 10; ++i) shaped.insert("d", vals[i]);
        s = shaped.to_string();
        if (s != "5 2 7 1 3 6 9 4 8 10")
        {
            cout << "Incorrect to_string for shaped tree. Expected 5 2 7 1 3 6 9 4 8 10 but got : " << s << endl;
        }

        // edge: duplicates still appear (level-order with equals on right)
        BST<string,int> dups;
        dups.insert("a", 5); dups.insert("b", 5); dups.insert("c", 5);
        s = dups.to_string();
        if (s != "5 5 5")
        {
            cout << "to_string edge (duplicates): expected 5 5 5 but got : " << s << endl;
        }
    }
    catch (exception &e)
    {
        cerr << "Error in to_string() tests : " << e.what() << endl;
    }
}

int main()
{

    string file_name = "usecase.cpp";
    cout << endl
         << "Running tests for " << file_name << endl
         << endl;

    test_empty();
    test_insert();
    test_get();
    test_remove();
    test_max_data();
    test_max_key();
    test_min_data();
    test_min_key();
    test_successor();
    test_in_order();
    test_trim();
    test_binhex();
    test_to_string();   

    cout << "Testing completed" << endl;

    return 0;
}

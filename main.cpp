#include <string>
#include <iostream>
#include <fstream>

using namespace std;

void swapByteOrder(unsigned short & us)
{
    us = (us >> 8) |
         (us << 8);
}


int main (void)
{
    string path1, path2, yes_or_not;
    cout << "Path of the first binary file: ";
    cin >> path1;
    cout << path1 << endl;
    cout << "Path of the second binary file: ";
    cin >> path2;
    cout << "Do you want it going through all the file ? (no exit when it finds a differance)";
    cin >> yes_or_not;
    while (yes_or_not != "Yes" && yes_or_not != "yes" && yes_or_not != "y" && yes_or_not != "No" && yes_or_not != "no" && yes_or_not != "n")
    {
        cout << "Wrong input, Do you want it going through all the file ?";
        cin >> yes_or_not;
    }
    
    ifstream first_file, second_file;
    first_file.open(path1, ios::in | ios::binary);
    if (! first_file.is_open()){
        cerr << "Error: file 1 won't open" << endl;
        exit(1);
    }

    second_file.open(path2, ios::in);
    if (! second_file.is_open()){
        cerr << "Error: file 2 won't open" << endl;
        exit(2);
    }

    // Save in this file the bytes that are diffrents.
    ofstream save_diffrences;
    save_diffrences.open("./saves/test.txt", ios::out);
    if (! save_diffrences.is_open()){
        string continu;
        cerr << "couldn't open the file that save the wrong bytes, do you still want to continue ?" << endl;
        cin >> continu;
        if (continu != "No" || continu != "no" || continu != "n"){
            exit(3);
        }
    }

    while(! first_file.eof() && ! second_file.eof())
    {
        unsigned short first_bin, second_bin;
        cout << "bip bip je passe" << endl;
        first_file.read((char *)&first_bin, sizeof(unsigned short));
        swapByteOrder(first_bin);
        second_file.read((char *)&second_bin, sizeof(unsigned short));
        if (first_bin != second_bin){
            cout << "At offset " << hex << (first_file.tellg() - 2) << " ( " << hex << (second_file.tellg() - 2)
            << " ) the byte is " << hex << first_bin << "in the first file, and " << hex << second_bin << " in the second one" << endl;
            if (save_diffrences.is_open()){
                string to_write = to_string(first_file.tellg() - 2) + " " + to_string(first_bin) + " " + to_string(second_bin) + "\n";
                const char* to_write_char = to_write.c_str();
                save_diffrences.write(to_write_char,to_write.size());
            }
            if (yes_or_not != "No" || yes_or_not != "no" || yes_or_not != "n")
            {
                exit(0);
            }
        }
    }
    if (! first_file.eof() || ! second_file.eof()){
        cerr << "WARNING : One of the file is bigger than the other" << endl;
    }

    return 0;
}
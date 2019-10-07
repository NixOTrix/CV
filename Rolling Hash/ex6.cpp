/*
Exercise 6 – Karp‐Rabin String Search  
Nikola Mahmutagic nm319 6082671
Wed 18:30 - 20:30
*/

#include <iostream>
#include <fstream>
#include <string>
using namespace std;


void rabinKarp(string str, string pat) {
    int n = str.length();
    int m = pat.length();
    int i, j;                      
    int s = 0, p = 0;                     
    const int pm = 256;                   
    const int q = 101;                   
    int h = 1;                               

    for (i = 0; i < m-1; i++)
        h = (h * pm) % q;

    for (i = 0; i < m; i++) {
        s = (pm * s + str[i]) % q;
        p = (pm * p + pat[i]) % q;
    }

    for (i = 0; i <= n-m; i++) {
        if (s == p) {                     
            for (j = 0; j < m; j++)
                if (str[i+j] != pat[j])
                    break;
            if (j == m) {
                cout<<"Pattern found at pos: "<<i+1<<endl;
            }
        }
        s = (pm * (s - h * str[i]) + str[i+m]) % q;
        if (s < 0)                       
            s = s + q;
    }
}

int main(){
    //making i/o
    ifstream inFile;
    //opening file
    cout << "Enter file name: " << endl;
    string in;
    cin >> in;
    inFile.open(in.c_str());
    //making sure file opened
    cout<<"Loading file:"<< endl;
    if (inFile.fail()){
        cout<< "In file failed to load" << endl;
        exit(8);
    }   
    //file reading
    cout<<"Reading in the file:"<< endl;
    
    string fileLine, sequence;
    getline(inFile, fileLine);
    getline(inFile, sequence);
    
    //just making sure :)
    // cout << sequence << endl;
    // cout<< fileLine << endl;
    
    inFile.close();

    rabinKarp(fileLine, sequence);
    
    return 0;
}

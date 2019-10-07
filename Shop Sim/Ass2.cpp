/*
Assignment 2 – Simul Que 
Nikola Mahmutagic nm319 6082671
Wed 18:30 - 20:30
*/

#include <time.h>
#include <cstdlib>
#include <iostream>
#include <fstream>
#include <string>
#include <cstring>
#include <iomanip>
using namespace std;

struct customer{
    double arrival;
    double tally;
    bool card;
};

struct event{
    int type;
    double etime;
    double ttime;
    bool card;
};

class queue{    

    int n, front, back, size;
    customer array[500];

   void enque(customer c){
       if(back == n - 1){
            cout << "Overflow" << endl;
            return ;
        } else {
            if (front == -1){
                front = 0;
            }
            back++;
            size ++;
            array[back] = c;
        }
   }
   
   customer deque(){
       if ( front == -1 || front > back){
            cout << "Underflow" << endl;
            exit(1);
        } else {
            //cout << array[front]<< endl;
            int f = front;
            front ++;
            size --;
            return array[f];
        }
   }
   bool empty(){
       return (size == 0);
   }

public:
//constructor
    queue(){
        n = 500;
        front = -1;
        back = -1;
        size = 0;
    }
    ~queue(){
        //add code

    }
    void add(customer c){
        enque(c);
    }
    customer deadd(){
        return deque();
    }
    bool isEmpty(){
        //fix add +1 to back to test this todo
        return empty();
    }
};

class eventqueue{
    int en, efront, eback, esize;
    event earray[100];

    void enque(event e){
       if(eback == en - 1){
            cout << "Overflow" << endl;
            return ;
        } else {
            if (efront == -1){
                efront = 0;
            }
            eback++;
            esize ++;
            earray[eback] = e;
        }
   }

    event deque(){
       if ( efront == -1 || efront > eback){
            cout << "Underflow" << endl;
            exit(1);
        } else {
            //cout << array[front]<< endl;
            int f = efront;
            efront ++;
            esize --;
            return earray[f];
        }
   }
   bool empty(){
       return (esize == 0);
   }

public:
    eventqueue(){
        en = 500;
        efront = -1;
        eback = -1;
        esize = 0;
    }
    ~eventqueue(){
        //add code

    }
    void add(event c){
        enque(c);
    }
    event deadd(){
        return deque();
    }
    bool isEmpty(){
        return empty();
    }
};

int main(){
    //making i/o
    ifstream inFile;
    //opening file
    cout<< "opening file: ass2.txt" << endl;
    string fileName = "ass2.txt";
    inFile.open(fileName.c_str());
    //making sure file opened
    cout<<"Loading file:"<< endl;
    if (inFile.fail()){
        cout<< "In file failed to load" << endl;
        exit(8);
    }
    //file reading
    cout<<"Reading in the file:"<< endl;
    string fileLine;
    while (getline(inFile, fileLine)){

    
    
    
    }      
    inFile.close();

    return 0;  
}


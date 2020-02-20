





#include <time.h>
#include <iostream>
#include <fstream>
#include <string>
#include <cstring>
using namespace std;

//todo
clock_t tStart = clock();

//prototyping
void palindrome();
string backwards(string);
void binarypalidrome();
string processing(string);
bool lastStep3(string);
string sortingStrings(string);
void quickSortUniqueWords(int, int);
void quickSortUniqueWordsArr2(int, int);
void quickSortUniqueWordsAlpha(int, int);
void anagramSorter(int, int);

//making a counter and array and other globals
int offset = -1;
int offset2 = -1;
int offset3 = -1;
int UniqueF = -1;
string array[400000];
string array2[400000];
string alphaarray[400000];
string step3Unique[400000];
string UniqueFound[400000];
string longest = "";
string anagramToSort[40];
int anagramToSortInt;

int main(){
    //making i/o
    ifstream inFile;
    //opening file
    string fileName;
    
    //todo rename into just dictionary
    fileName = "dictionary.txt";
    inFile.open(fileName.c_str());
    
    //making sure file opened
    cout<<"Loading file: "<< fileName << endl;
    if (inFile.fail()){
        cout<< "In file failed to load" << endl;
        exit(8);
    }

    //file reading
    cout<<"Loaded. Reading:"<< endl;
    string fileLine;
    while (getline(inFile, fileLine)){
        offset++;
        array[offset] = fileLine;
    }
    inFile.close();
    
    //part 2
    cout << "Number of words = " << offset + 1 << endl;
    cout<< "first 5 emordnilap words: " << endl;
    cout<< "original : backward" << endl;
    binarypalidrome();
    cout << "The longest: " << longest << endl;


    //part 3
    cout << "loading sample.txt" << endl;
    fileName = "sample.txt";
    inFile.open(fileName.c_str());
    if (inFile.fail()){
        cout<< "In file failed to load" << endl;
        exit(8);
    }
    cout<<"Loaded sample.txt; Reading:"<< endl;


    string word;
    string proword;
    int step2;
    while (getline(inFile, fileLine)){
        int step1 = 0;
        //todo add spliting the line and the length
        for (int index = 0; index <= fileLine.length(); index++){
            if(fileLine[index] == ' '){
                word ="";
                step2 = index;
                while(step1 < step2){
                    word += fileLine[step1];
                    step1++;
                }
                proword = processing(word);
                if (proword.length() != 0){
                    offset2++; 
                    array2[offset2] = proword;
                }
                step1 = step2 + 1;
            } else if(fileLine[index] == '\0'){
                word ="";
                step2 = index;
                while(step1 < step2){
                    word += fileLine[step1];
                    step1++;
                }
                proword = processing(word);
                if (proword.length() != 0){
                    offset2++; 
                    array2[offset2] = proword;
                }
            }
        }
    }
    inFile.close();
    
    cout << "number of valid words in sample.txt : " << offset2 + 1 << endl;

    // sort non unique words and linear search to insert them

   quickSortUniqueWordsArr2(0, offset2);

    for (int h = 0; h <= offset2; h++){
        while(h <= offset2  && array2[h] == array2[h+1]){
            h++;
        }
        offset3++;
        step3Unique[offset3] = array2[h];
    }
    cout << "number of unique words : " << offset3 + 1 << endl;

    for (int h = 0; h <=offset3; h++){
        if(lastStep3(step3Unique[h])){
            UniqueF++;
            UniqueFound[UniqueF] = step3Unique[h];
        }
    }

    cout << "Number of unique words found in the dictionary : " << UniqueF + 1 << endl;

    quickSortUniqueWords(0, UniqueF);


    for(int t = 0; t <= offset; t++){
        alphaarray[t] = sortingStrings(array[t]);
        //myTree.insert(array[t]);
    }

    //assuming this works
    quickSortUniqueWordsAlpha(0, offset);


    //OH BOY HERE COME THE ANAGRAMMIES
    string bigboi, string1, string2;
    string longestbigboi = " ";
    int totalwords = 0;
    int totalanagrams = 0;
    bool match;
    int counterPrinter = 0;
    int eachWord;
    int holderForWord = 0;
    int pointerForWord = 0;
    
    for (int h = 0; h <= UniqueF; h++){
        anagramToSortInt = -1;
        eachWord = 0;
        match = false;
        bigboi = UniqueFound[h];
        bigboi += " : ";
        //turn every word into a char array and sort it
        string1 = sortingStrings(UniqueFound[h]);

        int first = 0;
        int last = 0;
        int midmid = 0;
        int pos = 0;
        int middle = 0;
        int size = offset;
        
        while(pos <= size){
            middle = (pos + size)/2;
            
            if(string1 == alphaarray[middle]){
                midmid = middle;
                while(string1 == alphaarray[middle]){
                    
                    middle --;
                    if (middle == -1)
                        break;
                }
                first = middle + 1;
                while(string1 == alphaarray[midmid]){
                    midmid++;
                    if (midmid > offset)
                        break;
                }
                last = midmid -1;
                
                break;

            } 
            if(string1 > alphaarray[middle]){
                pos = middle + 1;

            } 
            if (string1 < alphaarray[middle]){
                size = middle - 1;
            }
        }

        while (first <= last){
            if (UniqueFound[h] != array[first]){
                eachWord+= 1;
                totalanagrams++;
                match = true;
                if (longestbigboi.length() < UniqueFound[h].length()){
                    longestbigboi = UniqueFound[h];
                }
                if (counterPrinter < 10){
                    anagramToSortInt++;
                    anagramToSort[anagramToSortInt] = array[first];
                }
            }
            first++;
        }
        
        if(match){
            if (counterPrinter < 10){
                anagramSorter(0, anagramToSortInt);
                cout << bigboi;
                for(int z = 0; z <= anagramToSortInt; z ++){
                    cout << " " << anagramToSort[z];
                }
                cout << endl;
                counterPrinter++;
            }
            totalwords++;
        }

        if(holderForWord < eachWord){
            holderForWord = eachWord;
            pointerForWord = h;
        }
    }
    
    //todo fix most anagrams and first 10 in order

    cout << "longest word that has an anagram : " << longestbigboi << endl;
    cout<< "word with the most anagrams : " << UniqueFound[pointerForWord] << endl;
    cout << "total words with anagrams : " << totalwords << endl;
    cout << "total amount of anagrams : " << totalanagrams << endl;



    //time elapsed measuring
    double taken = double(clock() - tStart) / CLOCKS_PER_SEC;
    cout << "time taken: " << taken << " seconds" << endl;
    return 0;
}

/*void palindrome(){
    int counter = 0;
    //todo fix the number in for loop
    for(int i = 0; i <= offset; i++){
        string backward = backwards(array[i]);
        //todo for loop to chekc all words for emorsafsdfnilap
        for(int t = 0; t <= offset; t++){
            if (array[t] == backward){
                counter ++;
                //add(array[i], backward);
                //do the thing
            }
            if (counter == 5){
                cout << "number of words covered: " << i << endl;
                break;
            }
        }
        if (counter == 5){
                break;
            }
    }
}*/

void binarypalidrome(){
    int counter = 0;
    for(int i = 0; i <= offset; i++){
        int pos = 0;
        int middle = 0;
        int size = offset - 1;
        string backward = backwards(array[i]);
        
        while(pos <= size){
            middle = (pos + size)/2;

            if(backward == array[middle]){
                counter += 1;
                if (longest.size() < backward.size()){
                    longest = backward;
                }
                if (counter <= 10){
                    cout << array[i] << " : " << backward << endl;
                }
                break;
            } 

            if(backward > array[middle]){
                pos = middle + 1;
            } 
            if (backward < array[middle]){
                size = middle - 1;
            }
        }
    }

}

bool lastStep3(string words){
    int pos = 0;
    int middle;
    int size = offset;
    
    while(pos <= size){
        middle = (pos + size)/2;

        if(words == array[middle]){
            return true;
        } 
        if(words > array[middle]){
            pos = middle + 1;
        } 
        if (words < array[middle]){
            size = middle - 1;
        }
    }
    return false;
}

string backwards(string str){
    int l, i, j = -1;
    //getting the length of a string not using strlen
    for (l = 0; str[l] != '\0'; l++){
        j++;
    }
    //reversing the string
    if(j > 0){
        char temp;
        for (i = 0; i < j; i++,j--){
            temp = str[i];
            str[i] = str[j];
            str[j] = temp;
        }
    } else 
        str = "NOTAREALWORD";
    return str;
}

string processing(string str){
    //going through each char and getting rid of it
    string process = "";
    for (int l = 0; str[l] != '\0'; l++){
        if (isalpha(str[l])){
            if(isupper(str[l])){
                process += (char) tolower(str[l]);
            } else {
                process += str[l];
            }  
        }
    }
    return process;
}

string sortingStrings(string str){

    char sent[100], temp;
    int i, j;

    for(int x =0; x <= str.length(); x++){
        sent[x] = str[x];
    }
    
    for (i = 0; i < sent[i]; i++){
        for (j = i +1; i < sent[j]; j++){
            if (sent[j] < sent[i]){
                temp = sent[j];
                sent[j] = sent[i];
                sent[i] = temp;
            }
        }
    }

    for(int x =0; x <= str.length(); x++){
        str[x] = sent[x];
    }
    return str;
}

void quickSortUniqueWords(int low, int high) {
	int i = low, j = high;
	string temp;
	string pivot = UniqueFound[(low + high)/2];

	while (i <= j) {
		while (UniqueFound[i].compare(pivot) < 0) {
			i++;
		}

		while (UniqueFound[j].compare(pivot) > 0) {
			j--;
		}

		if ( i <= j ) {
            temp = UniqueFound[i];
            UniqueFound[i] = UniqueFound[j];
            UniqueFound[j] = temp;
            i++;
            j--;
        }
	}

	if ( low < j ) {
        quickSortUniqueWords(low, j);
    }
    if ( i < high ) {
        quickSortUniqueWords(i, high);
    }
}

void quickSortUniqueWordsArr2(int low, int high) {
	int i = low, j = high;
	string temp;
	string pivot = array2[(low + high)/2];

	while (i <= j) {
		while (array2[i].compare(pivot) < 0) {
			i++;
		}

		while (array2[j].compare(pivot) > 0) {
			j--;
		}

		if ( i <= j ) {
            temp = array2[i];
            array2[i] = array2[j];
            array2[j] = temp;
            i++;
            j--;
        }
	}

	if ( low < j ) {
        quickSortUniqueWordsArr2(low, j);
    }
    if ( i < high ) {
        quickSortUniqueWordsArr2(i, high);
    }
}

void quickSortUniqueWordsAlpha(int low, int high) {
	int i = low, j = high;
	string temp;
	string pivot = alphaarray[(low + high)/2];

	while (i <= j) {
		while (alphaarray[i].compare(pivot) < 0) {
			i++;
		}

		while (alphaarray[j].compare(pivot) > 0) {
			j--;
		}

		if ( i <= j ) {
            temp = alphaarray[i];
            alphaarray[i] = alphaarray[j];
            alphaarray[j] = temp;
            temp = array[i];
            array[i] = array[j];
            array[j] = temp;
            i++;
            j--;
        }
	}

	if ( low < j ) {
        quickSortUniqueWordsAlpha(low, j);
    }
    if ( i < high ) {
        quickSortUniqueWordsAlpha(i, high);
    }
}

void anagramSorter(int low, int high){
    int i = low, j = high;
	string temp;
	string pivot = anagramToSort[(low + high)/2];
	while (i <= j) {
        //test
		while (anagramToSort[i] < pivot) {
			i++;
		}
		while (anagramToSort[j] > pivot) {
			j--;
		}
		if ( i <= j ) {
            temp = anagramToSort[i];
            anagramToSort[i] = anagramToSort[j];
            anagramToSort[j] = temp;
            i++;
            j--;
        }
	}
	if ( low < j ) {
        anagramSorter(low, j);
    }
    if ( i < high ) {
        anagramSorter(i, high);
    }
}

/*
    STEP 5:
    No explicit speed ups outside of implementing quicksort and using makeshift
    hash maps to make my program faster overall.

    Read in the Dictionary file, and assume it is sorted, then for each word
    revrse it, then using binary search find if it has an emordilap.

    Then read in the text file, split tokens based off of spaces or \0 which
    are esacape sequences at the end of strings. As I take each token, I put
    it through my pre-processing function which takes the string and goes through
    it character by character and processes it into a valid token. Then I sort the 
    array of valid words using a quicksort algorithm and use a while loop to test
    if the word next to it matches the word we are on, and strip out all the unique 
    words. Then using binary search I try to find each of the unique words in the dictionary.

    For anagrams I create a second array which holds the same word as dictionary
    at the same index, but the word had its letters arranged in alphabetic order.
    then I sort that array, but do the same movements on the original dictionary array too.
    Creating a sort of hash map. Then I take each word of my unique words that were found in the
    dictionary and binary search through the alpabetic array to find an index which matches.
    then I do 2 while loops that find the first and last occurance of the same letter order.
    And I finally take each of those indexes and find the original word in the original dictionary array.

    The final run time of the program on Banshee is fluctuating from 11 sec to 15 sec.

    The speed up process goes from 11h for linear search to 6 seconds using Binary search
    this is because Linear search is O(n^2) while the Binary search is O(n*log(n))
    making it aprox-- 62,000 times faster.
*/



#include <iostream>
#include <vector>
#include <cmath>
#include "program3.h"
using namespace std;


vector<int> hashTable; //our hashtable
int firstFunction; //an int 1-5
int secondFunction; //an int 1-5
int tableSize; //size of our hashtable
bool setSizeWasCalled; //if SetHashTableSize has been called atleast once, this will be true. if not, its false
int collisions = 0;

//HashTable Functions
int primaryHashFunction(int key);
int secondaryHashFunction(int key);
bool AddValue(int key);
int RemoveValue(int key);


// Sets the size of the hash table.  Returns if it succeeded.
bool SetHashTableSize(int n) {

    int hashTableSize = n; //setting local variable to what was passed in
    tableSize = n; //setting global variable to what was passed in
    bool hasSize; //false if table has size of 0 or less
    hashTable.clear(); //clearing hashTable
    hashTable.resize(hashTableSize); //resizing hashTable vector to size specified

    //sets hasSize to false if size is 0 or less
    if(hashTableSize <= 0)
    {
        hasSize = false;
        return hasSize;
    }
    else
    {
        hasSize = true;
        setSizeWasCalled = true; //SetHashTableSize did something so we set this global bool to true.
        return hasSize;
    }

}

// Sets the primary and secondary hash functions for hashing.  Returns if it succeeded.
bool SetHashFunctions(int f, int s) {
    if(f < 1 || f > 5) //if f or s is not between 1 and 5, return false
        return false;
    else if(s < 1 || s > 5)
        return false;
    else
    {
        firstFunction = f;
        secondFunction = s;
        return true;
    }
}

int primaryHashFunction(int key){

    switch(firstFunction) {
        case 1:
            return (int) (53 * fmod((0.2897 * key), 1));
        case 2:
            return (int) (key % tableSize);
        case 3:
            return (int) (key % 53);
        case 4:
            return (int) (key % 48);
        case 5:
            return 1;
    }
    return 0;
}

int secondaryHashFunction(int key){

    switch(secondFunction) {
        case 1:
            return (int) (52 * fmod((0.2897 * key), 1));
        case 2:
            return (int) (key % tableSize - 1);
        case 3:
            return (int) (key % 52);
        case 4:
            return (int) (key % 47);
        case 5:
            return 1;
    }
    return 0;
}

// Loads the data from the array into the hash table.  Returns the number of values added.
int LoadData(int a[ARRAY_SIZE]) {

    int numOfValues;

    for(int i = 0; i < ARRAY_SIZE; i++) {
        hashTable.push_back(a[i]);
        if(a[i] > 0)
            numOfValues++;
    }

	return numOfValues;
}

// Adds the key to the hash table.  Returns if it succeeded.
bool AddValue(int key)
{
    //if key is negative or setHashTableSize wasn't called, return false
    if(key < 0 || setSizeWasCalled == false)
        return false;
        else
        {
            collisions = 0;
            //while collisions is less than 5 total collisions and the index is occupied
            while(collisions < MAX_COLLISIONS && hashTable[(primaryHashFunction(key) + collisions * secondaryHashFunction(key)) % hashTable.size()] != 0)
            {
               // int index = (primaryHashFunction(key) + collisions * secondaryHashFunction(key)) % hashTable.size();
               // cout << "Trying to place "<< key <<" at index: " << index << endl;
                collisions++;

               //if collisions reaches MAX_Collisions, return false
                if(collisions == MAX_COLLISIONS)
                {
                   // cout << "Max collisions reached value not added " << endl;
                    return false;
                }

            }

            hashTable[(primaryHashFunction(key) + collisions * secondaryHashFunction(key)) % hashTable.size()] = key;
            return true;

    }
}

// Removes the key from the hash table.  Returns the index that the key was stored in.
int RemoveValue(int key) {
//if key is negative or setHashTableSize wasn't called, return false
    if(key < 0 || setSizeWasCalled == false)
        return INVALID_CALL;
    else
    {
        collisions = 0;
        //while collisions is less than 5 total collisions and the index is occupied
        while(collisions < MAX_COLLISIONS)
        {
            //if the key exists at the index, remove it and return index, otherwise increase collision by one and repeat until key is found
            if(hashTable[(primaryHashFunction(key) + collisions * secondaryHashFunction(key)) % hashTable.size()] == key)
            {
                int index = (primaryHashFunction(key) + collisions * secondaryHashFunction(key)) % hashTable.size();
                hashTable[(primaryHashFunction(key) + collisions * secondaryHashFunction(key)) % hashTable.size()] = 0;
                return index;
            } else
                collisions++;
        }

    }

	return INVALID_CALL;
}

// Finds the key in the hash table and returns its index.
int GetHashTableLocation(int key) {
	return INVALID_CALL;
}

// Returns the number of collisions that have occurred since the hash table was set up.
int GetNumberOfCollisions() {
	return INVALID_CALL;
}


/*
int main(int argv, char **argc)
{


    SetHashTableSize(10);
    SetHashFunctions(2,2);

    AddValue(9);
    AddValue(8);
    AddValue(7);
    AddValue(6);
    AddValue(5);
    AddValue(4);
    AddValue(3);
    AddValue(2);
    AddValue(1);
    AddValue(4);



    for(int i = 0; i < hashTable.size(); i++)
        cout << hashTable.at(i) << " ";


    return 0;
}
 */



#ifndef FlightHASHTABLE_H
#define FlightHASHTABLE_H

#include<iostream>
#include "flightticket.h"
#include "myList.h"
// include additional header files as needed


using namespace std;

class HashNode
{
	private:
		string key; // key = companyName+flightNumber 
		Flight_Ticket value;
	public:
		HashNode(string key, Flight_Ticket value) : key(key), value(value)
		{
			this->key = key;
			this->value = value;
		};
		HashNode(){}; // default constructor
		string getKey()
		{
			return key;
		};
		Flight_Ticket getValue()
		{
			return value;
		};
		friend class FlightHASHTABLE;
bool operator==(const HashNode& other) const
{
	return (key == other.key && value == other.value);
};
};

//=============================================================================
class FlightHASHTABLE
{
	private:
		MyList<HashNode> *buckets;		//List of Buckets, Please create your own List Class called MyList
		MyList<HashNode> dateBuckets; //List of Buckets for date

		int size;					    //Current Size of HashTable
		int capacity;				    // Total Capacity of HashTable
		int collisions;					// Total number of collisions

	public:
		FlightHASHTABLE();						//constructor
		FlightHASHTABLE(int capacity);			//constructor
		~FlightHASHTABLE();						//destructor
		unsigned long hashCode(string key); 				//implement and test different hash functions
		int importCSV(string path); 			//Load all the flight-tickets from the CSV file to the HashTable
		int exportCSV(string path); 			//Export all the flight-tickets from the HashTable to a CSV file in an ascending order		
		int count_collisions();					//return the number of collisions on the HashTable
		int add(Flight_Ticket* data); 			//add new flight to the HashTable
		void removeRecord (string companyName, int flightNumber);	//Delete a record with key from the hashtable
		void find(string companyName, int flightNumber);		//Find and Display records with same key entered 
		void allinday(string date);  					//Find and Display records with same day entered
		void printASC(string companyName, int flightNumber);  		//display the collisions for the entered key in an ascending order 
		// add more methods as needed	
};

#endif

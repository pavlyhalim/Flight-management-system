
#include<iostream>
#include<fstream>
#include<string>
#include<sstream>
#include<exception>
#include<string>
#include <cmath>
#include "myList.h"
#include "flightticket.h"
#include "flighthashtable.h"


#define TABLE_SIZE 125003
using namespace std;

//==============================================
// Constructor
//==============================================
FlightHASHTABLE::FlightHASHTABLE()
{
    buckets = new MyList<HashNode>[TABLE_SIZE];
    // dateBuckets= new MyList<HashNode>[TABLE_SIZE];
    size = 0;
    capacity = TABLE_SIZE;
    collisions = 0;
}

//==============================================
//constructor  with parameter
//==============================================
FlightHASHTABLE::FlightHASHTABLE(int capacity)
{
    buckets = new MyList<HashNode>[capacity];
    size = 0;
    collisions = 0;
    this->capacity = capacity;
}

//==============================================
//destructor
//==============================================
FlightHASHTABLE::~FlightHASHTABLE()
{
    delete buckets;
}
//==============================================
//6 hash functions to hash the key to an index in the table
//1. Division method
//2. Multiplication method
//3. Polynomial method
//4. summation method
//5. Mid-square method
//6. cyclic shift method
//==============================================
// 1. Division method
// unsigned long FlightHASHTABLE::hashCode(string key){
//     unsigned long hash = 0;
//     for (int i = 0; i < key.size(); i++){
//         hash = hash + (unsigned int) key[i];
//     }
//     hash = hash % TABLE_SIZE;
//     return hash;
// }


// 2. Multiplication method
// unsigned long FlightHASHTABLE::hashCode(string key){
//     long hash2 = 0;
//     for (int i = 0; i < key.length(); i++){
//         hash2 = hash2 * (int)key[i];
//     }
//     hash2 = hash2 % TABLE_SIZE;
//     return hash2;
// }
// 3. Polynomial method
// unsigned long FlightHASHTABLE::hashCode(string key){
//     const int p3 = 31;
//     long hash3 = 0;
//     for(int i = 0; i < key.length(); i++){
//         hash3 = (hash3 * p3 + key[i]) % TABLE_SIZE;
//     }
//     return hash3;
// }

// 4. summation method
// unsigned long FlightHASHTABLE::hashCode(string key){
//     long hash4 = 0;
//     for (int i = 0; i < key.length(); i++){
//         hash4 = hash4 + (int)key[i];
//     }
//     hash4 = hash4 % TABLE_SIZE;
//     return hash4;
// }

// 5. Cyclic shift method
// unsigned long FlightHASHTABLE::hashCode(string key)
// {
// 	unsigned long hash = 0;
// 	for(int i=0; i<key.length(); i++){
// 		hash = (hash<<5)|(hash>>27);
// 		hash = hash + (unsigned int)key[i];}
// 	return hash%TABLE_SIZE;
// }

// 6. Simple method using operators
// unsigned long FlightHASHTABLE::hashCode(string key){
//     unsigned long hash = 0;
//     for (int i = 0; i < key.size(); i++){
//         hash += 33 * ((unsigned int) key[i]);
//         hash -= 'a';
//     }
//     return hash;
// }


//==============================================
//default hash function (Polynomial method)
//==============================================
unsigned long FlightHASHTABLE::hashCode(string key){
    const int p3 = 31;
    long hash3 = 0;
    for(int i = 0; i < key.length(); i++){
        hash3 = (hash3 * p3 + key[i]) % TABLE_SIZE;
    }
    return hash3;
}
//==============================================
//importCSV
//==============================================
int FlightHASHTABLE::importCSV(string path)
{
    ifstream file(path);
    string line;
    string companyName;
    string flightNumber;
    string country_of_origin;
    string country_of_destination;
    string stopOver;
    string price;
    string time_of_departure;
    string time_of_arrival;
    string date;
    int count = 0;
    if (file.is_open())
    {
        (getline(file, line));
        while (getline(file, line))
        {
            stringstream ss(line);
            getline(ss, companyName, ',');
            getline(ss, flightNumber, ',');
            getline(ss, country_of_origin, ',');
            if (country_of_origin[0] == '"')
            {
                getline(ss, country_of_origin, '"');
                getline(ss, country_of_origin, ',');
            }

            getline(ss, country_of_destination, ',');
            if (country_of_destination[0] == '"')
            {
                getline(ss, country_of_destination, '"');
                getline(ss, country_of_destination, ',');
            }
            getline(ss, stopOver, ',');
            getline(ss, price, ',');
            getline(ss, time_of_departure, ',');
            getline(ss, time_of_arrival, ',');
            getline(ss, date);

            // Convert the flight number from string to int.
            int flightNumberInt = stoi(flightNumber);

            Flight_Ticket* data = new Flight_Ticket(companyName, flightNumberInt, country_of_origin, country_of_destination, stopOver, price, time_of_departure, time_of_arrival, date);
            add(data);
            count++;
        }

        file.close();

        cout << count << " records have been imported successfully." << endl;

        return count;
    }
   
     else
    {
        cout << "Unable to open file";
    }
}

//==============================================
//add a new entry to the hash table with the key and value as parameters
//==============================================
int FlightHASHTABLE::add(Flight_Ticket *data)
{
    // Concatenate the company name and flight number to form the key.
    string key = data->getCompanyName() + to_string(data->getFlightNumber());

    // Get the hash value of the key.
    int hashValue = hashCode(key);
    // Create an iterator for the list of hash nodes.
    MyList<HashNode>::iterator it = buckets[hashValue].begin();
    // Check if the key already exists in the list and the value is the same
    int keyExists =0;
    while (it != buckets[hashValue].end())
    {
        // Check if the current node's key is equal to the key of the record being added.
        if ((*it).key == key) {
            {
                keyExists++;
                // Check if the value is not the same.
                if((*it).value.getCompanyName() == data->getCompanyName() && (*it).value.getFlightNumber() == data->getFlightNumber() && (*it).value.getCountryOfOrigin() == data->getCountryOfOrigin() && (*it).value.getCountryOfDestination() == data->getCountryOfDestination() && (*it).value.getStopOver() == data->getStopOver() &&(*it).value.getPrice() == data->getPrice() && (*it).value.getTimeOfDeparture() == data->getTimeOfDeparture() && (*it).value.getTimeOfArrival() == data->getTimeOfArrival() && (*it).value.getDate() == data->getDate())
                {
                    //print the error message
                    cout << "The record already exists in the hash table" << endl;
                    return -1;
                }
            }          
        }
        // Move the iterator to the next node in the list
        it++;
    }  
        if (keyExists == 0)
        {
            if (buckets[hashValue].size > 0)
            {
                collisions++;
            }
        }
        
        // Create a new node and add it to the list.
        HashNode newNode;
        newNode.key = key;
        newNode.value = *data;
        buckets[hashValue].addBack(newNode);
        return 1;            
}

//==============================================
//find and display records with the same key (the key is companyName and flightNumber)
//==============================================
void FlightHASHTABLE::find(string companyName, int flightNumber)
{
    int recordsFound = 0;
    string key = companyName + to_string(flightNumber);
    long index = hashCode(key);
    for (MyList<HashNode>::iterator it = buckets[index].begin(); it != buckets[index].end(); ++it)
    {
        if ((*it).value.getCompanyName() == companyName && (*it).value.getFlightNumber() == flightNumber)
        {
            // Print the flight ticket in the desired format
            cout << "Company Name: " << (*it).value.getCompanyName() << endl;
            cout << "Flight Number: " << (*it).value.getFlightNumber() << endl;
            cout << "Country of Origin: " << (*it).value.getCountryOfOrigin() << endl;
            cout << "Country of Destination: " << (*it).value.getCountryOfDestination() << endl;
            cout << "Stop Over: " << (*it).value.getStopOver() << endl;
            cout << "Price: " << (*it).value.getPrice() << endl;
            cout << "Time of Departure: " << (*it).value.getTimeOfDeparture() << endl;
            cout << "Time of Arrival: " << (*it).value.getTimeOfArrival() << endl;
            cout << "Date: " << (*it).value.getDate() << endl;
            cout << endl;
            recordsFound++;
        }
    }
    if (recordsFound == 0)
    {
        cout << "Record with key " << key << " not found" << endl;
    }
    else
    {
        cout << recordsFound << " records found with key " << key << endl;
    }
}

//==============================================
// remove an entry from the hash table with the given company name and flight number
//==============================================
void FlightHASHTABLE::removeRecord(string companyName, int flightNumber) 
{
    // Generate the key for the flight ticket
    string key = companyName + to_string(flightNumber);

    // Compute the index of the bucket where the flight ticket is stored
    long index = hashCode(key);

    // Iterate over each element in the bucket and print the details of the flight tickets with the same key
    int count = 0;
    for (auto it = buckets[index].begin(); it != buckets[index].end(); ++it) {
        if ((*it).key == key) {
            count++;
            // Print the flight ticket in the desired format
            cout << count << ". " << endl;
            cout << "Company Name: " << (*it).value.getCompanyName() << endl;
            cout << "Flight Number: " << (*it).value.getFlightNumber() << endl;
            cout << "Country of Origin: " << (*it).value.getCountryOfOrigin() << endl;
            cout << "Country of Destination: " << (*it).value.getCountryOfDestination() << endl;
            cout << "Stop Over: " << (*it).value.getStopOver() << endl;
            cout << "Price: " << (*it).value.getPrice() << endl;
            cout << "Time of Departure: " << (*it).value.getTimeOfDeparture() << endl;
            cout << "Time of Arrival: " << (*it).value.getTimeOfArrival() << endl;
            cout << "Date: " << (*it).value.getDate() << endl;
            cout << endl;
        }
    }

    // Prompt the user to enter the index of the flight ticket to remove
    int index_to_remove;
    cout << "Enter the index of the record you want to remove: ";
    cin >> index_to_remove;

    // Iterate over the bucket again and remove the flight ticket with the specified index
    count = 0;
    for (auto it = buckets[index].begin(); it != buckets[index].end(); ++it) {
        if ((*it).key == key) {
            count++;
            if (count == index_to_remove) {
                // Remove the flight ticket
                buckets[index].erase(*it);
                cout << "Record removed successfully" << endl;
                return;
            }
        }
    }
    cout << "Record not found" << endl;
}

//==============================================
//print all records in the hash table in a specific date
//==============================================
void FlightHASHTABLE::allinday(string date)
{
    // Generate the key for the flight ticket
    string key = date;

    // Compute the index of the bucket where the flight ticket is stored
    long index = hashCode(key);

    // Create a local MyList object to store the flight tickets
    MyList<HashNode>* dateBuckets = new MyList<HashNode>[TABLE_SIZE];

    // Copy the flight tickets from the bucket into the list
    for (int i = 0; i < TABLE_SIZE; i++)
        {
        for (MyList<HashNode>::iterator it = buckets[i].begin(); it != buckets[i].end(); ++it)
            {
                string tem = (*it).getValue().getDate();
                tem.erase(tem.length() - 1);
                long hash = hashCode(tem);
                dateBuckets[hash].addBack(*it);
            }
        }

    // Initialize an array to store the flight tickets
    HashNode tickets[dateBuckets[index].size];

    // Copy the flight tickets from the list into the array
    int i = 0;
    for (MyList<HashNode>::iterator it = dateBuckets[index].begin(); it != dateBuckets[index].end(); ++it)
    {
        tickets[i] = *it;
        i++;
    }

    // Use the bubble sort algorithm to sort the flight tickets in ascending order by their destination country
    for (int i = 0; i < dateBuckets[index].size; i++)
    {
        for (int j = 0; j < dateBuckets[index].size; j++)
        {
            if (tickets[i].value.getTimeOfDeparture() < tickets[j].value.getTimeOfDeparture())
            {
                // Swap the two elements using a temporary variable
                HashNode temp = tickets[i];
                tickets[i] = tickets[j];
                tickets[j] = temp;
            }
        }
    }

    cout << dateBuckets->size << " records found on " << date << endl;

    // Initialize the destination country counter to 0
    int destinationCounter = 0;

    // Print the sorted flight tickets in the desired format
    for (int i = 0; i < dateBuckets[index].size; i++)
    {
        string temp = tickets[i].value.getDate();
        temp.erase(temp.length() - 1);
   
        if (temp == date)
        {
            cout << "Company Name: " << tickets[i].value.getCompanyName() << endl;
            cout << "Flight Number: " << tickets[i].value.getFlightNumber() << endl;
            cout << "Country of Origin: " << tickets[i].value.getCountryOfOrigin() << endl;
            cout << "Country of Destination: " << tickets[i].value.getCountryOfDestination() << endl;
            cout << "Stop Over: " << tickets[i].value.getStopOver() << endl;
            cout << "Price: " << tickets[i].value.getPrice() << endl;
            cout << "Time of Departure: " << tickets[i].value.getTimeOfDeparture() << endl;
            cout << "Time of Arrival: " << tickets[i].value.getTimeOfArrival() << endl;
            cout << "Date: " << tickets[i].value.getDate() << endl;
            cout << endl;
            destinationCounter++;
        }
    }

    if (destinationCounter == 0)
    {
        cout << "No flights with that key" << endl;
    }
    else if (destinationCounter == 1)
    {
        cout << "There is " << destinationCounter << " flight with that key" << endl;
    }
    else
    {
        cout << "There are " << destinationCounter << " flights with that key" << endl;
    }
}


//==============================================
//Prints in ascending order (based on the flight destination country) all flight-tickets having the same key entered by the user <companyName,flightNumber>.
//==============================================
void FlightHASHTABLE::printASC(string companyName, int flightNumber)
{
    // Generate the key for the flight ticket
    string key = companyName + to_string(flightNumber);

    // Compute the index of the bucket where the flight ticket is stored
    long index = hashCode(key);

    // Create a local MyList object to store the flight tickets
    MyList<HashNode> ticketList;

    // Copy the flight tickets from the bucket into the list
    for (MyList<HashNode>::iterator it = buckets[index].begin(); it != buckets[index].end(); ++it)
    {
        ticketList.addBack(*it);
    }

    // Initialize an array to store the flight tickets
    HashNode tickets[ticketList.size];

    // Copy the flight tickets from the list into the array
    int i = 0;
    for (MyList<HashNode>::iterator it = ticketList.begin(); it != ticketList.end(); ++it)
    {
        tickets[i] = *it;
        i++;
    }

    // Use the bubble sort algorithm to sort the flight tickets in ascending order by their destination country
    for (int i = 0; i < ticketList.size; i++)
    {
        for (int j = 0; j < ticketList.size; j++)
        {
            if (tickets[i].value.getCountryOfDestination() < tickets[j].value.getCountryOfDestination())
            {
                // Swap the two elements using a temporary variable
                HashNode temp = tickets[i];
                tickets[i] = tickets[j];
                tickets[j] = temp;
            }
        }
    }

    // Initialize the destination country counter to 0
    int destinationCounter = 0;

    // Print the sorted flight tickets in the desired format
    for (int i = 0; i < buckets[index].size; i++)
    {
        if (tickets[i].value.getCompanyName() == companyName && tickets[i].value.getFlightNumber() == flightNumber)
        {
            cout << "Company Name: " << tickets[i].value.getCompanyName() << endl;
            cout << "Flight Number: " << tickets[i].value.getFlightNumber() << endl;
            cout << "Country of Origin: " << tickets[i].value.getCountryOfOrigin() << endl;
            cout << "Country of Destination: " << tickets[i].value.getCountryOfDestination() << endl;
            cout << "Stop Over: " << tickets[i].value.getStopOver() << endl;
            cout << "Price: " << tickets[i].value.getPrice() << endl;
            cout << "Time of Departure: " << tickets[i].value.getTimeOfDeparture() << endl;
            cout << "Time of Arrival: " << tickets[i].value.getTimeOfArrival() << endl;
            cout << "Date: " << tickets[i].value.getDate() << endl;
            cout << endl;
            destinationCounter++;
        }
    }

    if (destinationCounter == 0)
    {
        cout << "No flights with that key" << endl;
    }
    else if (destinationCounter == 1)
    {
        cout << "There is " << destinationCounter << " flight with that key" << endl;
    }
    else
    {
        cout << "There are " << destinationCounter << " flights with that key" << endl;
    }
}

//==============================================
//return the number of collisions on the HashTable
//================================================
int FlightHASHTABLE::count_collisions()
{
    return collisions;
}

//==============================================
//Export all the flight-tickets from the HashTable to a CSV file in an ascending order
//==============================================
int FlightHASHTABLE::exportCSV(string path)
{
    ofstream file;
    file.open(path, ios::app);
    int numRecordsExported = 0;

    if (file.is_open())
    {
        file << "Company Name" << "," << "Flight Number" << "," << "Country of Origin" << "," << "Country of Destination" << "," << "Stop Over" << "," << "Price" << "," << "Time of Departure" << "," << "Time of Arrival" << "," << "Date" << endl;
        for (int i = 0; i < TABLE_SIZE; i++)
        {
            if (buckets[i].size != 0)
            {
                // Create an iterator for the list of hash nodes.
                MyList<HashNode>::iterator it = buckets[i].begin(); 
                // Iterate over the list of hash nodes and output each node's data to the file.
                while (it != buckets[i].end())
                {
                    file << (*it).value.getCompanyName()<< "," << (*it).value.getFlightNumber() << "," << (*it).value.getCountryOfOrigin() << "," << (*it).value.getCountryOfDestination() << "," << (*it).value.getStopOver() << "," << (*it).value.getPrice() << "," << (*it).value.getTimeOfDeparture() << "," << (*it).value.getTimeOfArrival() << "," << (*it).value.getDate() << endl;

                    // Move the iterator to the next node in the list.
                    it++;

                    // Increment the count of records exported to the file.
                    numRecordsExported++;
                }
            }
        }

        // Close the file.
        file.close();

        // Return the number of records that were exported to the file.
        return numRecordsExported;
    }
    else
    {
        cout << "File not found" << endl;
        return 0;
    }
}


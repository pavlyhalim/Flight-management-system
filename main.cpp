
//=================================================================================
// Name         : DS Assignment#4 
// Author       : 
// Version      : 1.0
// Date Created : Apr-17-2022
// Date Modified: 
// Description  : Starter Code for Flight-Ticket Management System using HASH TABLE in C++
//=================================================================================
#include<iostream>
#include<cstdlib>
#include<sstream>

#include "flightticket.h"
#include "flighthashtable.h"
#include "myList.h"

//==========================================================
void listCommands()
{
	cout<<"\n----------------------------------"<<endl;
	cout<<"import <path>      	:Import flight-tickets from a CSV file"<<endl
		<<"export <path>      	:Export flight-tickets to a CSV file"<<endl
		<<"count_collisions   	:Print number of collisions"<<endl
		<<"add                	:Add a new flight-ticket"<<endl
		<<"delete <key>       	:Delete a flight-ticket"<<endl
		<<"find <key>         	:Find a flight-ticket's details"<<endl
		<<"allinday <date>    	:Display all flight-tickets in a day"<<endl
		<<"printASC <key>     	:Print flight-tickets in ascending order"<<endl
		<<"exit               	:Exit the program"<<endl;
}
//==========================================================

// to be completed with all the necessary method definitions

//==========================================================
int main(void)
{
	FlightHASHTABLE myFlightHASHTABLE;
	string command;
	string path;
	string user_input;
	string parameter;
	string key;
	string companyName;
	int flightNumber;
	string country_of_origin;
	string country_of_destination;
	string stopOver;
	string price;
	string time_of_departure;
	string time_of_arrival;
	string date;
	string parameter2;
	int i;

	while(true)
	{
	listCommands();

	cout<<">";
	getline(cin, user_input);
	stringstream ss(user_input);
	getline(ss,command,' ');
	getline(ss,parameter);
	getline(ss,parameter2);

	if (command == "import")
	{
		myFlightHASHTABLE.importCSV(parameter);
	}
	else if (command == "export")
{
        // Use the provided parameter as the name of the exported file.
        int x = myFlightHASHTABLE.exportCSV(parameter);
        cout << x <<  " records exported successfully" << endl;
    }
	else if (command == "count_collisions")
	{
		cout << "Number of collisions: " << myFlightHASHTABLE.count_collisions() << endl;
	}
	else if (command == "add")
	{
		cout<<"Enter company name: ";
		getline(cin, companyName);
		cout<<"Enter flight number: ";
		cin >> flightNumber;
		while (cin.fail())
		{
			cin.clear();
			cin.ignore(256, '\n');
			cout << "Invalid input. Please enter a number: ";
			cin >> flightNumber;
		}
		cout<<"Enter country of origin: ";
		getline(cin, country_of_origin);
		while (country_of_origin == "")
		{
			getline(cin, country_of_origin);
		}
		cout<<"Enter country of destination: ";
		getline(cin, country_of_destination);
		while (country_of_destination == "")
		{
			getline(cin, country_of_destination);
		}
		cout<<"Enter stop over: ";
		getline(cin, stopOver);
		cout<<"Enter price: ";
		getline(cin, price);
		cout<<"Enter time of departure: ";
		getline(cin, time_of_departure);
		cout<<"Enter time of arrival: ";
		getline(cin, time_of_arrival);
		cout<<"Enter date: ";
		getline(cin, date);
		Flight_Ticket* data = new Flight_Ticket(companyName, flightNumber, country_of_origin, country_of_destination, stopOver, price, time_of_departure, time_of_arrival, date);
    	int x;
		x = myFlightHASHTABLE.add(data);
		if (x==1) cout << "The record was added successfully" << endl;


	}
	else if (command == "delete")
	{
		// Read the input from cin.
		string input;

		// Parse the input string into separate companyname and flightnumber variables by comma.
		stringstream ss(parameter);
		getline(ss, input, ',');
		getline(ss, parameter2);

		int parameter2_int = stoi(parameter2);

		myFlightHASHTABLE.removeRecord(input, parameter2_int);

	}
	else if (command == "find")
	{
		// Read the input from cin.
		string input;

		// Parse the input string into separate companyname and flightnumber variables by comma.
		stringstream ss(parameter);
		getline(ss, input, ',');
		getline(ss, parameter2);

		int parameter2_int = stoi(parameter2);

		//calculate the time taken to find the flight ticket
		auto start = chrono::high_resolution_clock::now();
		// Find the flight ticket.
		myFlightHASHTABLE.find(input, parameter2_int);
		auto end = chrono::high_resolution_clock::now();
		auto duration = chrono::duration_cast<chrono::microseconds>(end - start);
		cout << "Time taken to find the flight ticket: " << duration.count() << " microseconds" << endl;
	}

	else if (command == "allinday")
	{
		myFlightHASHTABLE.allinday(parameter);
	}
	else if (command == "printASC")
	{
		// Read the input from cin.
		string input;

		// Parse the input string into separate companyname and flightnumber variables by comma.
		stringstream ss(parameter);
		getline(ss, input, ',');
		getline(ss, parameter2);

		int parameter2_int = stoi(parameter2);

		// Print the flight tickets in ascending order.
		myFlightHASHTABLE.printASC(input, parameter2_int);
	}
	else if (command == "exit")
	{
		exit(1);
	}
	else
	{
		cout << "Invalid command. Please try again." << endl;
	}
	}
}



#ifndef FLIGHT_TICKET_H
#define FLIGHT_TICKET_H

#include<iostream>
using namespace std;

class Flight_Ticket
{
	private:
		string companyName;
		int flightNumber;
		string country_of_origin;
		string country_of_destination;
		string stopOver;
		string price;
		string time_of_departure;
		string time_of_arrival;
		string date;

	public:
		Flight_Ticket(string companyName, int flightNumber, string country_of_origin, string country_of_destination, string stopOver, string price, string time_of_departure, string time_of_arrival, string date);
		Flight_Ticket(){};
		string getCompanyName()
		{
			return companyName;
		}
		int getFlightNumber()
		{
			return flightNumber;
		}
		string getCountryOfOrigin()
		{
			return country_of_origin;
		}
		string getCountryOfDestination()
		{
			return country_of_destination;
		}
		string getStopOver()
		{
			return stopOver;
		}
		string getPrice()
		{
			return price;
		}
		string getTimeOfDeparture()
		{
			return time_of_departure;
		}
		string getTimeOfArrival()
		{
			return time_of_arrival;
		}
		string getkey()
		{
			return (companyName + to_string(flightNumber));
		}
		string getDate()
		{
			return date;
		}
		bool operator==(const Flight_Ticket& other) const
		{
			return (companyName == other.companyName && flightNumber == other.flightNumber && country_of_origin == other.country_of_origin && country_of_destination == other.country_of_destination && stopOver == other.stopOver && price == other.price && time_of_departure == other.time_of_departure && time_of_arrival == other.time_of_arrival && date == other.date);
		}

};

#endif

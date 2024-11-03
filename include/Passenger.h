// include/Passenger.h
#ifndef PASSENGER_H
#define PASSENGER_H

#include <string>

class Passenger {
public:
    int passengerID;
    std::string name;

    Passenger(int id, const std::string& passengerName);
};

#endif // PASSENGER_H


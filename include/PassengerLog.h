// include/PassengerLog.h
#ifndef PASSENGERLOG_H
#define PASSENGERLOG_H

#include <string>

struct PassengerLog {
    int logID;
    int passengerID;
    std::string timestamp;
    std::string actionType; // RideBooking/Payment/ProfileUpdate/SecurityAction
    int driverID;           // -1 if not applicable
    std::string details;
};

#endif // PASSENGERLOG_H


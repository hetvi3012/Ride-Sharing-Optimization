// include/AdminLog.h
#ifndef ADMINLOG_H
#define ADMINLOG_H

#include <string>

struct AdminLog {
    int logID;
    std::string timestamp;
    std::string category; // Driver/Passenger/System
    int driverID;         // -1 if not applicable
    std::string details;
};

#endif // ADMINLOG_H


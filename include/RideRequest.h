// include/RideRequest.h
#ifndef RIDEREQUEST_H
#define RIDEREQUEST_H

struct RideRequest {
    int requestID;
    int passengerID;
    double pickupLat, pickupLon;
    double dropoffLat, dropoffLon;
    double fare;
    bool isAccepted;
    int driverID; // -1 if not assigned
};

#endif // RIDEREQUEST_H


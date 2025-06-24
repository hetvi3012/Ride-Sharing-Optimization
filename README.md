# Ride-Sharing-Optimization

🛠️ This is a fork of the original team project. I contributed equally as a collaborator, with my commits on the main repository.


# CS201 - DSA Project  
**Project Title:** Ride-Sharing Optimization System Using R-Trees and Splay Trees  
**Instructor:** Dr. Anil Shukla  
**Mentor:** Shubham Thawait  

**Authors:**  
- Hetvi Bagdai - 2023CSB1123  
- Bhavya Rao - 2023CSB1291  
- Dheemanth Papolu - 2023MCB1230

# How to Run the Project

1. Download the files onto your device and navigate to the project directory.
2. This is a C++ program, so it can be compiled using the GCC or Clang compiler.
3. **Dependencies**: The project requires the following libraries:
   - **Boost**: Install Boost for geometry and filesystem operations.
 
   A. On Ubuntu, you can install Boost by running:
      ```bash
      sudo apt-get update
      sudo apt-get install libboost-all-dev
      ```
   B. On macOS (using Homebrew):
      ```bash
      brew install boost
## How to Run the Project

1. Clone this repository and navigate to the project directory:
   ```bash
   git clone https://github.com/your-repository/ride-sharing-system.git
   cd ride-sharing-system
2. Compile the project using the make command:
   ```bash
   make
3. Run the executable
   ```bash
   ./ride-sharing-system

## Introduction

The Ride-Sharing Optimization System is designed to improve the efficiency and accuracy of ride assignments in a ride-sharing platform. This system uses advanced data structures:
- **R-Trees**: For spatial indexing of driver locations, enabling rapid retrieval of the nearest drivers for ride requests.
- **Splay Trees**: For managing logs of passengers and administrators, optimizing retrieval times for frequently accessed logs.

This project aims to reduce passenger wait times, improve resource allocation, and ensure efficient log management, making it a scalable solution for modern urban transportation systems.

## Modules

The system comprises three main modules, each with specific functionalities:

### 1. Driver Module
The Driver Module allows drivers to interact with the system to view and accept ride requests. Key features include:
- **Pending Ride Requests**: Drivers can view a list of pending ride requests within their proximity.
- **Accept Ride Requests**: Upon accepting a request, the driver's location is updated to reflect the drop-off point of the completed ride.
- **Real-Time Location Update**: Driver locations are stored in the R-Tree, allowing the system to update and retrieve driver positions dynamically.

### 2. Passenger Module
The Passenger Module enables passengers to request rides and view their ride history. Key features include:
- **Request a Ride**: Passengers select a pickup and drop-off location. The system then calculates the top 3 nearest drivers based on location and estimates the fare.
- **Fare Estimation**: Using the Haversine formula, the system calculates the distance between pickup and drop-off locations and provides a fare estimate.
- **Log Management**: Passenger activities, such as ride history and fare information, are recorded in a Splay Tree for efficient access and retrieval.

### 3. Admin Module
The Admin Module provides administrators with tools to manage the ride-sharing system and access logs. Key features include:
- **Log Management**: Administrative logs are maintained in a Splay Tree, allowing efficient search and retrieval of frequently accessed records.
- **Driver and Passenger Monitoring**: The admin can review driver and passenger activities, ensuring quality control and auditing capabilities.
- **System Management**: Allows for adjustments in system settings, log review, and performance monitoring.


## What to Input

After running the `ride-sharing-system` executable, you will see a main menu with options. The program provides a user-friendly prompt to guide you through each option:

- **Admin Interface**: Manage logs and view system operations.
- **Passenger Interface**: Request a ride, view ride history, and check fare estimates.
- **Driver Interface**: View and accept pending ride requests.
- **Exit**: Exit the application.

You can follow the prompts in each section to provide the necessary inputs (e.g., selecting pickup and drop-off locations, accepting ride requests).

---


## What to Expect as a Result

Based on the selected operation:

- In the **Passenger Interface**, you’ll receive the top 3 nearest drivers and a fare estimate.
- In the **Driver Interface**, drivers will see pending ride requests and can choose to accept them. The driver’s location will automatically update upon ride completion.
- In the **Admin Interface**, you can view logs stored in a Splay Tree for efficient access to frequently accessed data.

The results for each operation will be displayed in the terminal, reflecting the real-time updates in the system.

## Acknowledgements

We would like to express our gratitude to our Course Instructor, **Dr. Anil Shukla**, and Mentor, **Shubham Thawait** guidance and support throughout this project. We also extend our thanks to our friends for their valuable feedback and encouragement.

## References

1. **R-Trees for Spatial Data Indexing**  
   R-Trees are used in this project for efficient spatial indexing of driver locations, enabling quick retrieval of the nearest drivers. For a detailed overview and foundational research, refer to:
   - Wikipedia: [R-Tree](https://en.wikipedia.org/wiki/R-tree)
   - GeeksforGeeks: [R-Tree - Introduction, Insertion, and Deletion](https://www.geeksforgeeks.org/r-tree-introduction-insertion-and-deletion/)
   - Original Research Paper: Guttman, A. (1984). *R-trees: A dynamic index structure for spatial searching*. ACM SIGMOD Record, 14(2), 47-57. [Link](https://doi.org/10.1145/602259.602266)

2. **Splay Trees for Efficient Log Management**  
   Splay Trees are implemented in this project to optimize log retrieval by bringing frequently accessed logs closer to the root. For more information, see:
   - Wikipedia: [Splay Tree](https://en.wikipedia.org/wiki/Splay_tree)
   - GeeksforGeeks: [Splay Tree](https://www.geeksforgeeks.org/splay-tree-set-1-insert/)
   - Original Research Paper: Sleator, D. D., & Tarjan, R. E. (1985). *Self-adjusting binary search trees*. Journal of the ACM (JACM), 32(3), 652-686. [Link](https://doi.org/10.1145/3828.3835)

3. **Haversine Formula for Distance Calculation**  
   The Haversine formula is used to calculate the great-circle distance between two points on the Earth's surface, which is essential for fare estimation in this project. For details, refer to:
   - Wikipedia: [Haversine Formula](https://en.wikipedia.org/wiki/Haversine_formula)
   - Movable Type Scripts: [Haversine Formula](https://www.movable-type.co.uk/scripts/latlong.html)

4. **Geospatial Data Structures**  
   This project is inspired by geospatial data structures commonly used for proximity searches and dynamic location indexing. Further reading:
   - CP-Algorithms: [Geospatial Data Structures](https://cp-algorithms.com/geometry/geospatial-data-structures.html)

---

These references provided foundational knowledge and guidance for implementing efficient data structures and algorithms in the Ride-Sharing Optimization System.

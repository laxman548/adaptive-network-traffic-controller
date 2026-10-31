#ifndef SERVER_H
#define SERVER_H

#include <string>
using namespace std;

struct Server {
    string serverId;
    int activerequests;
    int capacity;
    double latency;
    bool healthy;
};

// Function declarations
double calculateUtilization(int activeRequests, int capacity);

double calculateLoadScore(const Server& server);

#endif
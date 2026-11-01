
#ifndef SERVER_H
#define SERVER_H

#include <string>
using namespace std;

// Server health states
enum class HealthStatus {
    HEALTHY,
    UNHEALTHY,
    RECOVERING
};

struct Server {
    string serverId;
    int activerequests;
    int capacity;
    double latency;

    // Health monitoring
    HealthStatus healthStatus = HealthStatus::HEALTHY;

    int consecutiveFailures = 0;
    int consecutiveSuccesses = 0;
};

// Function declarations
double calculateUtilization(int activeRequests, int capacity);

double calculateLoadScore(const Server& server);

void performHealthCheck(Server& server, bool success);

#endif

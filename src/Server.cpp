#include "Server.h"

double calculateUtilization(int activeRequests, int capacity) {

    // Validate capacity
    if (capacity <= 0) {
        return -1.0;
    }

    // Validate active requests
    if (activeRequests < 0) {
        return -1.0;
    }

    // Calculate utilization percentage
    double utilization =
        (static_cast<double>(activeRequests) / capacity) * 100.0;

    return utilization;
}


double calculateLoadScore(const Server& server) {

    // Step 1: Exclude unhealthy servers
    if (!server.healthy) {
        return -1.0;
    }

    // Step 2: Calculate utilization
    double utilization = calculateUtilization(
        server.activerequests,
        server.capacity
    );

    // Step 3: Validate utilization
    if (utilization < 0) {
        return -1.0;
    }

    // Step 4: Normalize utilization
    double normalizedUtilization = utilization / 100.0;

    // Step 5: Validate latency
    if (server.latency < 0) {
        return -1.0;
    }

    // Step 6: Normalize latency
    double normalizedLatency = server.latency / 200.0;

    if (normalizedLatency > 1.0) {
        normalizedLatency = 1.0;
    }

    // Step 7: Calculate weighted load score
    double loadScore =
        (0.7 * normalizedUtilization) +
        (0.3 * normalizedLatency);

    return loadScore;
}
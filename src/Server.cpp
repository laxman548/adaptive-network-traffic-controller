
#include "Server.h"

// Day 2: Calculate server utilization
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


// Day 2: Calculate normalized server load score
double calculateLoadScore(const Server& server) {

    // Exclude servers that are not healthy
    if (server.healthStatus != HealthStatus::HEALTHY) {
        return -1.0;
    }

    // Calculate utilization
    double utilization = calculateUtilization(
        server.activerequests,
        server.capacity
    );

    // Validate utilization
    if (utilization < 0) {
        return -1.0;
    }

    // Normalize utilization
    double normalizedUtilization = utilization / 100.0;

    // Validate latency
    if (server.latency < 0) {
        return -1.0;
    }

    // Normalize latency
    double normalizedLatency = server.latency / 200.0;

    if (normalizedLatency > 1.0) {
        normalizedLatency = 1.0;
    }

    // Calculate weighted load score
    double loadScore =
        (0.7 * normalizedUtilization) +
        (0.3 * normalizedLatency);

    return loadScore;
}


// Day 4: Server health monitoring
void performHealthCheck(Server& server, bool success) {

    if (success) {

        // Health check successful
        server.consecutiveSuccesses++;

        // Reset failure counter
        server.consecutiveFailures = 0;

        // Recovering server needs 2 consecutive successes
        if (server.healthStatus == HealthStatus::UNHEALTHY) {

            server.healthStatus = HealthStatus::RECOVERING;

        }
        else if (server.healthStatus == HealthStatus::RECOVERING &&
                 server.consecutiveSuccesses >= 2) {

            server.healthStatus = HealthStatus::HEALTHY;

        }

    }
    else {

        // Health check failed
        server.consecutiveFailures++;

        // Reset success counter
        server.consecutiveSuccesses = 0;

        // Failure during recovery returns server to unhealthy
        if (server.healthStatus == HealthStatus::RECOVERING ||
            server.consecutiveFailures >= 3) {

            server.healthStatus = HealthStatus::UNHEALTHY;

        }
    }
}

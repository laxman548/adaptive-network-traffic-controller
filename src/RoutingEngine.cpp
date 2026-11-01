
#include "RoutingEngine.h"

#include <limits>

// Adaptive Routing: Find the least-loaded healthy server
int findLeastLoadedServer(const vector<Server>& servers) {

    // Step 1: Initialize minimum score to infinity
    double minScore = numeric_limits<double>::infinity();

    // Step 2: No server selected initially
    int selectedServer = -1;

    // Step 3: Iterate through all servers
    for (int i = 0; i < servers.size(); i++) {

        // Step 4: Skip unhealthy and recovering servers
        if (servers[i].healthStatus != HealthStatus::HEALTHY) {
            continue;
        }

        // Step 5: Calculate load score
        double currentScore = calculateLoadScore(servers[i]);

        // Step 6: Skip invalid scores
        if (currentScore < 0) {
            continue;
        }

        // Step 7: Find the lowest score
        if (currentScore < minScore) {

            minScore = currentScore;
            selectedServer = i;
        }
    }

    // Step 8: Return selected server index
    return selectedServer;
}


// Round Robin: Find the next healthy server
int findNextRoundRobinServer(
    const vector<Server>& servers,
    int& currentIndex
) {

    // Step 1: Check whether servers exist
    if (servers.empty()) {
        return -1;
    }

    int totalServers = servers.size();

    // Step 2: Validate current index
    if (currentIndex < 0 || currentIndex >= totalServers) {
        currentIndex = 0;
    }

    // Step 3: Check servers in circular order
    for (int i = 0; i < totalServers; i++) {

        int index = (currentIndex + i) % totalServers;

        // Step 4: Skip unhealthy and recovering servers
        if (servers[index].healthStatus != HealthStatus::HEALTHY) {
            continue;
        }

        // Step 5: Move index to the next position
        currentIndex = (index + 1) % totalServers;

        // Step 6: Return selected server
        return index;
    }

    // Step 7: No healthy server found
    return -1;
}

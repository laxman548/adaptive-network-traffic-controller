#include <bits/stdc++.h>
using namespace std;

struct Server{
    string serverId;
    int activerequests;
    int capacity;
    double latency;
    bool healthy;
};

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

int findLeastLoadedServer(const vector<Server>& servers) {

    // Step 1: Initialize minimum score to infinity
    double minScore = numeric_limits<double>::infinity();

    // Step 2: No server selected initially
    int selectedServer = -1;

    // Step 3: Iterate through all servers
    for (int i = 0; i < servers.size(); i++) {

        // Step 4: Skip unhealthy servers
        if (!servers[i].healthy) {
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

int main(){
     vector<Server> servers = {
        {"Server A", 150, 100, 40.0, true},
        {"Server B", 80, 100, 250.0, true},
        {"Server C", 20, 100, 60.0, false}
    };

   for (int i = 0; i < servers.size(); i++) {

    cout << "Server ID: " << servers[i].serverId << endl;
    cout << "Active Requests: " << servers[i].activerequests << endl;
    cout << "Capacity: " << servers[i].capacity << endl;

    // Calculate server utilization
    double utilization = calculateUtilization(
        servers[i].activerequests,
        servers[i].capacity
    );

    cout << "Utilization: " << utilization << "%" << endl;

    cout << "Latency: " << servers[i].latency << " ms" << endl;
    cout << "Health: " << boolalpha << servers[i].healthy << endl;
    double loadScore = calculateLoadScore(servers[i]);

    if (loadScore < 0) {
        cout << "Load Score: Unavailable" << endl;
    }
    else {
        cout << "Load Score: " << loadScore << endl;
    }

        cout << "------------------------" << endl;
    }

     int bestServer = findLeastLoadedServer(servers);

    if (bestServer != -1) {
        cout << "\nLeast Loaded Server: "
             << servers[bestServer].serverId << endl;
    }
    else {
        cout << "\nNo healthy servers available!" << endl;
    }


    return 0;

}

#include <iostream>
#include <vector>

#include "Server.h"
#include "RoutingEngine.h"

using namespace std;

// Display server health status
string getHealthStatus(HealthStatus status) {

    switch (status) {

        case HealthStatus::HEALTHY:
            return "HEALTHY";

        case HealthStatus::UNHEALTHY:
            return "UNHEALTHY";

        case HealthStatus::RECOVERING:
            return "RECOVERING";
    }

    return "UNKNOWN";
}

int main() {

    // Initialize backend servers
    vector<Server> servers = {
        {"Server A", 10, 100, 40.0},
        {"Server B", 80, 100, 250.0},
        {"Server C", 20, 100, 60.0}
    };

    // Display initial server information
    cout << "\n========== INITIAL SERVER STATUS ==========\n";

    for (const Server& server : servers) {

        cout << "\nServer ID: " << server.serverId << endl;
        cout << "Active Requests: " << server.activerequests << endl;
        cout << "Capacity: " << server.capacity << endl;

        double utilization = calculateUtilization(
            server.activerequests,
            server.capacity
        );

        cout << "Utilization: " << utilization << "%" << endl;
        cout << "Latency: " << server.latency << " ms" << endl;

        cout << "Health: "
             << getHealthStatus(server.healthStatus) << endl;

        double loadScore = calculateLoadScore(server);

        if (loadScore < 0) {
            cout << "Load Score: Unavailable" << endl;
        }
        else {
            cout << "Load Score: " << loadScore << endl;
        }

        cout << "------------------------" << endl;
    }

    // Test 1: Server failure detection
    cout << "\n========== SERVER FAILURE SIMULATION ==========\n";

    cout << "\nServer B health checks:\n";

    for (int i = 1; i <= 3; i++) {

        performHealthCheck(servers[1], false);

        cout << "Check " << i << ": FAILED"
             << " | Consecutive Failures: "
             << servers[1].consecutiveFailures
             << " | Status: "
             << getHealthStatus(servers[1].healthStatus)
             << endl;
    }

    // Test 2: Adaptive routing
    cout << "\n========== ADAPTIVE ROUTING ==========\n";

    int bestServer = findLeastLoadedServer(servers);

    if (bestServer != -1) {

        cout << "Least Loaded Server: "
             << servers[bestServer].serverId << endl;
    }
    else {

        cout << "No healthy servers available!" << endl;
    }

    // Test 3: Round Robin routing
    cout << "\n========== ROUND ROBIN ROUTING ==========\n";

    int currentIndex = 0;
    int totalRequests = 6;

    for (int i = 1; i <= totalRequests; i++) {

        int selectedServer = findNextRoundRobinServer(
            servers,
            currentIndex
        );

        if (selectedServer != -1) {

            cout << "Request " << i
                 << " -> "
                 << servers[selectedServer].serverId
                 << endl;
        }
        else {

            cout << "Request " << i
                 << " -> No healthy server available!"
                 << endl;
        }
    }

    // Test 4: Server recovery
    cout << "\n========== SERVER RECOVERY SIMULATION ==========\n";

    for (int i = 1; i <= 2; i++) {

        performHealthCheck(servers[1], true);

        cout << "Check " << i << ": SUCCESS"
             << " | Consecutive Successes: "
             << servers[1].consecutiveSuccesses
             << " | Status: "
             << getHealthStatus(servers[1].healthStatus)
             << endl;
    }

    // Test Case 4: Routing after server recovery

cout << "\n========== ROUTING AFTER RECOVERY TEST ==========\n";

// Create a separate copy for testing
vector<Server> recoveredServers = servers;

// Temporarily disable Server A and Server C
recoveredServers[0].healthStatus = HealthStatus::UNHEALTHY;
recoveredServers[2].healthStatus = HealthStatus::UNHEALTHY;

// Server B should be the only available server
int recoveredAdaptive = findLeastLoadedServer(recoveredServers);

int recoveredRoundRobin = findNextRoundRobinServer(
    recoveredServers,
    currentIndex
);

cout << "Adaptive Routing: ";

if (recoveredAdaptive != -1) {
    cout << recoveredServers[recoveredAdaptive].serverId << endl;
}
else {
    cout << "No healthy server available!" << endl;
}

cout << "Round Robin Routing: ";

if (recoveredRoundRobin != -1) {
    cout << recoveredServers[recoveredRoundRobin].serverId << endl;
}
else {
    cout << "No healthy server available!" << endl;
}

    // Display final server status
    cout << "\n========== FINAL SERVER STATUS ==========\n";

    for (const Server& server : servers) {

        cout << server.serverId << " -> "
             << getHealthStatus(server.healthStatus)
             << endl;
    }

    // Test 5: All servers unhealthy
    cout << "\n========== ALL SERVERS UNHEALTHY TEST ==========\n";

    vector<Server> unhealthyServers = servers;

    for (auto& server : unhealthyServers) {
        server.healthStatus = HealthStatus::UNHEALTHY;
    }

    int adaptiveResult = findLeastLoadedServer(unhealthyServers);

    int roundRobinResult = findNextRoundRobinServer(
        unhealthyServers,
        currentIndex
    );

    cout << "Adaptive Routing: " << adaptiveResult << endl;
    cout << "Round Robin: " << roundRobinResult << endl;

    // Test 6: Recovery failure
    cout << "\n========== RECOVERY FAILURE TEST ==========\n";

    Server testServer = {"Server D", 10, 100, 40.0};

    // Three consecutive failures
    performHealthCheck(testServer, false);
    performHealthCheck(testServer, false);
    performHealthCheck(testServer, false);

    cout << "After 3 failures: "
         << getHealthStatus(testServer.healthStatus) << endl;

    // One successful check
    performHealthCheck(testServer, true);

    cout << "After 1 success: "
         << getHealthStatus(testServer.healthStatus) << endl;

    // Failure during recovery
    performHealthCheck(testServer, false);

    cout << "After recovery failure: "
         << getHealthStatus(testServer.healthStatus) << endl;

    // Test 7: Consecutive failure counter reset
    cout << "\n========== CONSECUTIVE FAILURE RESET TEST ==========\n";

    Server resetTestServer = {"Server E", 10, 100, 40.0};

    bool healthChecks[] = {
        false, false, true, false, false, false
    };

    for (int i = 0; i < 6; i++) {

        performHealthCheck(resetTestServer, healthChecks[i]);

        cout << "Check " << i + 1
             << " | Result: "
             << (healthChecks[i] ? "SUCCESS" : "FAILED")
             << " | Consecutive Failures: "
             << resetTestServer.consecutiveFailures
             << " | Consecutive Successes: "
             << resetTestServer.consecutiveSuccesses
             << " | Status: "
             << getHealthStatus(resetTestServer.healthStatus)
             << endl;
    }

    return 0;
}

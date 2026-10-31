#include <iostream>
#include <vector>

#include "Server.h"
#include "RoutingEngine.h"

using namespace std;

int main() {

    // Initialize backend servers
    vector<Server> servers = {
        {"Server A", 10, 100, 40.0, false},
        {"Server B", 80, 100, 250.0, true},
        {"Server C", 20, 100, 60.0, false}
    };

    // Display server information
    for (int i = 0; i < servers.size(); i++) {

        cout << "Server ID: "
             << servers[i].serverId << endl;

        cout << "Active Requests: "
             << servers[i].activerequests << endl;

        cout << "Capacity: "
             << servers[i].capacity << endl;

        // Calculate utilization
        double utilization = calculateUtilization(
            servers[i].activerequests,
            servers[i].capacity
        );

        cout << "Utilization: "
             << utilization << "%" << endl;

        cout << "Latency: "
             << servers[i].latency << " ms" << endl;

        cout << "Health: "
             << boolalpha << servers[i].healthy << endl;

        // Calculate load score
        double loadScore = calculateLoadScore(servers[i]);

        if (loadScore < 0) {
            cout << "Load Score: Unavailable" << endl;
        }
        else {
            cout << "Load Score: " << loadScore << endl;
        }

        cout << "------------------------" << endl;
    }

    // Adaptive routing
    int bestServer = findLeastLoadedServer(servers);

    if (bestServer != -1) {

        cout << "\nLeast Loaded Server: "
             << servers[bestServer].serverId << endl;
    }
    else {

        cout << "\nNo healthy servers available!" << endl;
    }

    // Round Robin Routing
cout << "\n========== ROUND ROBIN ROUTING ==========\n";

int currentIndex = 0;

int totalRequests = 4;

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

    return 0;
}
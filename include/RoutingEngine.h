#ifndef ROUTING_ENGINE_H
#define ROUTING_ENGINE_H

#include <vector>
#include "Server.h"

using namespace std;

// Adaptive routing
int findLeastLoadedServer(const vector<Server>& servers);

// Round Robin routing
int findNextRoundRobinServer(
    const vector<Server>& servers,
    int& currentIndex
);

#endif
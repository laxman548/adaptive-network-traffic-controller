#include <bits/stdc++.h>
using namespace std;

struct Server{
    string serverId;
    int activerequests;
    double latency;
    bool healthy;
};

int main(){
     vector<Server> servers = {
        {"Server A", 10, 40.0, true},
        {"Server B", 80, 250.0, true},
        {"Server C", 20, 60.0, false}
    };

    for (int i = 0; i < servers.size(); i++) {

    cout << "Server ID: " << servers[i].serverId << endl;
    cout << "Active Requests: " << servers[i].activerequests << endl;
    cout << "Latency: " << servers[i].latency << " ms" << endl;
    cout << "Health: " << boolalpha << servers[i].healthy << endl;

    cout << "------------------------" << endl;
}

    return 0;

}
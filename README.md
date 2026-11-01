
# 🚀 Adaptive Network Traffic Controller

A C++17 project that explores intelligent load balancing across multiple backend servers using **Least-Loaded Adaptive Routing**, **Round Robin Routing**, and **Server Health Monitoring**.

This project is being developed incrementally through a 30-day roadmap, with the goal of building a real-world network traffic controller featuring HTTP request handling, Docker deployment, a graphical monitoring dashboard, and performance benchmarking.

---

## 📌 Project Overview

When an application serves many clients, incoming requests need to be distributed across multiple backend servers.

A load balancer selects an appropriate backend for each request according to a routing policy.

This project implements an Adaptive Network Traffic Controller in C++, gradually introducing server metrics, routing algorithms, health monitoring, failure detection, and recovery mechanisms.

**Current scope:** The application currently uses configured C++ Server objects and simulates server health and routing decisions. Real HTTP request forwarding and live backend monitoring are planned for upcoming phases.

## 🎯 Project Objectives

- Model multiple backend servers.
- Track active requests, capacity, latency, and health.
- Calculate server utilization and normalized load scores.
- Implement Least-Loaded Adaptive Routing.
- Implement Round Robin Routing.
- Detect unhealthy backend servers.
- Implement automatic server recovery.
- Exclude unhealthy and recovering servers from routing.
- Handle scenarios where no healthy backend is available.
- Add real HTTP request handling.
- Deploy backend services using Docker.
- Build a graphical monitoring dashboard.
- Visualize server performance using Chart.js.
- Benchmark routing strategies under different workloads.

---

## ✅ Implemented Features

### 1. Server Model

Implemented in `Server.h`.

Each server maintains:

- `serverId`
- `activerequests`
- `capacity`
- `latency`
- `healthStatus`
- `consecutiveFailures`
- `consecutiveSuccesses`

Server health states:

- `HEALTHY`
- `UNHEALTHY`
- `RECOVERING`

### 2. Server Utilization

Implemented in `Server.cpp`.

Function:

`calculateUtilization(int activeRequests, int capacity)`

Formula:

```text
Utilization (%) = (Active Requests / Capacity) × 100
```

Features:

- Validates server capacity.
- Prevents division by zero.
- Rejects negative active requests.
- Calculates utilization percentage.
- Allows utilization above 100% to identify overloaded servers.

### 3. Normalized Load Score

Implemented in `Server.cpp`.

Function:

`calculateLoadScore(const Server& server)`

Formula:

```text
U = Utilization / 100

L = min(Latency / 200, 1)

Load Score = (0.7 × U) + (0.3 × L)
```

Configuration:

- Utilization weight: 70%.
- Latency weight: 30%.
- Reference latency: 200 ms.
- Lower valid scores indicate better server performance.

Unhealthy servers and servers with invalid metrics return `-1.0`.

### 4. Adaptive Routing — Least-Loaded Server

Implemented in `RoutingEngine.cpp`.

Function:

`findLeastLoadedServer(const vector<Server>& servers)`

Features:

- Iterates through all configured servers.
- Skips unhealthy servers.
- Skips recovering servers.
- Calculates valid load scores.
- Selects the server with the lowest load score.
- Returns `-1` when no eligible server exists.

### 5. Round Robin Routing

Implemented in `RoutingEngine.cpp`.

Function:

`findNextRoundRobinServer(const vector<Server>& servers, int& currentIndex)`

Features:

- Distributes requests in circular order.
- Uses modulo (`%`) for circular indexing.
- Skips unhealthy servers.
- Skips recovering servers.
- Maintains the current routing index.
- Returns the selected server index.
- Returns `-1` when no healthy server is available.

**Important distinction:**

Round Robin selects servers using circular order, whereas Adaptive Routing selects servers based on their calculated load scores.

### 6. Server Health Monitoring and Recovery

Implemented in `Server.cpp`.

Function:

`performHealthCheck(Server& server, bool success)`

The health monitoring module maintains consecutive failure and success counters.

**Failure detection:**

- First consecutive failure: Server remains HEALTHY.
- Second consecutive failure: Server remains HEALTHY.
- Third consecutive failure: Server becomes UNHEALTHY.

**Recovery mechanism:**

- A successful health check resets the failure counter.
- An unhealthy server enters RECOVERING after its first successful check.
- Two consecutive successful checks restore the server to HEALTHY.
- A failed check during recovery returns the server to UNHEALTHY.
- A recovered server becomes eligible for routing again.

**Routing integration:**

Both Adaptive Routing and Round Robin exclude servers whose status is not HEALTHY.

---

## 🧪 Day 3 Test Results

| Test Scenario | Result |
|---|---|
| Multiple backend server initialization | Passed |
| Server utilization calculation | Passed |
| Normalized load score calculation | Passed |
| Least-loaded server selection | Passed |
| Round Robin circular indexing | Passed |
| Skip unhealthy servers | Passed |
| All servers unhealthy | Passed |
| Multiple request distribution | Passed |

---

## 🧪 Day 4 Test Results — Server Health Monitoring

Day 4 focused on implementing server health monitoring, consecutive failure detection, recovery, and integration with both routing algorithms.

| Test Scenario | Expected Behaviour | Result |
|---|---|---|
| Three consecutive failures | Server becomes UNHEALTHY | Passed |
| Adaptive routing with unhealthy server | Skip unhealthy server | Passed |
| Round Robin with unhealthy server | Skip unhealthy server | Passed |
| First successful recovery check | Server becomes RECOVERING | Passed |
| Second successful recovery check | Server becomes HEALTHY | Passed |
| All servers unhealthy | Both algorithms return -1 | Passed |
| Failure during recovery | Server returns to UNHEALTHY | Passed |
| Consecutive failure counter reset | Successful check resets failure counter | Passed |
| Routing after recovery | Recovered server becomes eligible | Passed |

### Failure Detection Example

```text
Check 1: FAILED | Consecutive Failures: 1 | Status: HEALTHY

Check 2: FAILED | Consecutive Failures: 2 | Status: HEALTHY

Check 3: FAILED | Consecutive Failures: 3 | Status: UNHEALTHY
```

### Recovery Example

```text
Check 1: SUCCESS | Consecutive Successes: 1 | Status: RECOVERING

Check 2: SUCCESS | Consecutive Successes: 2 | Status: HEALTHY
```

### Routing During Server Failure

```text
Request 1 -> Server A
Request 2 -> Server C
Request 3 -> Server A
Request 4 -> Server C
Request 5 -> Server A
Request 6 -> Server C
```

Server B is excluded while unhealthy.

### All Servers Unhealthy

```text
Adaptive Routing: -1

Round Robin: -1
```

### Failure During Recovery

```text
After 3 failures: UNHEALTHY

After 1 success: RECOVERING

After recovery failure: UNHEALTHY
```

### Consecutive Failure Counter Reset

```text
Check 1 | FAILED  | Failures: 1 | HEALTHY

Check 2 | FAILED  | Failures: 2 | HEALTHY

Check 3 | SUCCESS | Failures: 0 | HEALTHY

Check 4 | FAILED  | Failures: 1 | HEALTHY

Check 5 | FAILED  | Failures: 2 | HEALTHY

Check 6 | FAILED  | Failures: 3 | UNHEALTHY
```

### Routing After Recovery

```text
Adaptive Routing: Server B

Round Robin Routing: Server B
```

**Day 4 Result: All 8 validation scenarios passed.**

Note: These tests use simulated health-check results. Actual network health checks against running backend services will be implemented in a future phase.

---

## 🏗️ Current Project Architecture

```text
Adaptive-Network-Traffic-Controller/
│
├── include/
│   ├── Server.h
│   └── RoutingEngine.h
│
├── src/
│   ├── main.cpp
│   ├── Server.cpp
│   └── RoutingEngine.cpp
│
├── build/                  # Generated locally
├── CMakeLists.txt
├── .gitignore
└── README.md
```

| File | Responsibility |
|---|---|
| `Server.h` | Server structure, health states and function declarations |
| `Server.cpp` | Server utilization, load score and health monitoring |
| `RoutingEngine.h` | Routing function declarations |
| `RoutingEngine.cpp` | Adaptive and Round Robin algorithms |
| `main.cpp` | Server initialization, simulations and testing |
| `CMakeLists.txt` | Build configuration |

---

## ⚙️ Technology Stack

| Technology | Purpose |
|---|---|
| C++17 | Core application |
| g++ / MinGW | C++ compilation |
| CMake | Build automation |
| Git | Version control |
| GitHub | Source-code hosting |
| Docker | Planned backend deployment |
| HTML | Dashboard structure |
| CSS | Dashboard styling |
| JavaScript | Dashboard functionality |
| Chart.js | Performance visualization |

---

## 🖥️ Build and Run

### Prerequisites

- C++17-compatible compiler
- CMake
- MinGW Make
- Git

### Clone Repository

```powershell
git clone https://github.com/laxman548/adaptive-network-traffic-controller.git
```

### Navigate to Project

```powershell
cd adaptive-network-traffic-controller
```

### Configure CMake

```powershell
cmake -S . -B build -G "MinGW Makefiles"
```

### Build

```powershell
cmake --build build
```

### Run

```powershell
.\build\controller.exe
```

---

## 🗺️ 30-Day Development Roadmap

| Phase | Implementation | Status |
|---|---|---|
| Day 1 | Environment setup, Server model, CMake and GitHub | Completed |
| Day 2 | Server metrics, utilization and normalized load score | Completed |
| Day 3 | Adaptive Routing, Round Robin and edge-case testing | Completed |
| Day 4 | Server health monitoring, failure detection and recovery | Completed |
| Day 5 | Prepare the controller for real HTTP backend servers | Upcoming |
| Upcoming | HTTP request handling | Planned |
| Upcoming | Live backend health monitoring | Planned |
| Upcoming | JSON-based server configuration | Planned |
| Upcoming | Docker integration | Planned |
| Upcoming | Multiple backend containers | Planned |
| Upcoming | Graphical monitoring dashboard | Planned |
| Upcoming | Chart.js visualizations | Planned |
| Upcoming | Performance benchmarking | Planned |

---

## 📊 Expected Final Outcomes

- Distribute real HTTP requests across multiple backend servers.
- Prevent unhealthy servers from receiving traffic.
- Compare Round Robin and Adaptive Routing.
- Detect backend failures automatically.
- Restore recovered servers to the routing pool.
- Monitor server utilization and latency.
- Visualize server performance through a graphical dashboard.
- Benchmark routing efficiency under different workloads.
- Demonstrate practical C++, networking, Docker and cloud-native concepts.

---

## 👨‍💻 Developer

**Laxman K**

GitHub: [@laxman548](https://github.com/laxman548)

---

This project is a hands-on exploration of C++, computer networking, load-balancing algorithms and cloud-native infrastructure, developed incrementally as part of a 30-day project plan.

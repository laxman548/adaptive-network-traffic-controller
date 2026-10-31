# 🚀 Adaptive Network Traffic Controller

A C++17 project that explores load balancing across multiple backend servers. It currently models server metrics and implements two routing strategies: **Least-Loaded Adaptive Routing** and **Round Robin**.

The project is being developed incrementally through a 30-day roadmap. Planned phases include real HTTP request handling, backend health monitoring, Docker deployment, a browser-based dashboard, and performance benchmarking.

---

## 📌 Project Overview

When an application serves many clients, incoming requests may need to be distributed across multiple backend servers. A load balancer selects an eligible backend for each request according to a routing policy.

This project builds that functionality step by step in C++, beginning with a server model and metric calculations, then adding routing algorithms that consider server health and load.

**Current scope:** The application uses configured `Server` objects and simulates request-to-server decisions. It does not yet forward live HTTP traffic or collect real-time metrics from deployed backend processes.

## 🎯 Project Objectives

- Model multiple backend servers.
- Track active requests, capacity, latency, and health.
- Calculate server utilization and a normalized load score.
- Exclude unhealthy or invalid servers from routing.
- Select the least-loaded eligible server.
- Distribute requests using Round Robin.
- Compare routing strategies under different server conditions.
- Add real HTTP request handling and backend health monitoring.
- Deploy backend services with Docker.
- Build a graphical monitoring dashboard using HTML, CSS, JavaScript, and Chart.js.
- Benchmark routing behaviour and performance.

## ✅ Implemented Features

### 1. Server Model

Each server stores:

- `serverId`
- `activerequests`
- `capacity`
- `latency`
- `healthy`

### 2. Server Utilization

Implemented in `Server.cpp`:

`calculateUtilization(activeRequests, capacity)`

```text
Utilization (%) = (Active Requests / Capacity) × 100
```

The function validates inputs and prevents division by zero. Utilization is not capped at 100%, allowing overloaded servers to be identified.

### 3. Normalized Load Score

Implemented in `Server.cpp`:

`calculateLoadScore(const Server& server)`

```text
U = Utilization / 100
L = min(Latency / 200, 1)

Load Score = (0.7 × U) + (0.3 × L)
```

- Utilization weight: 70%.
- Latency weight: 30%.
- Reference latency: 200 ms.
- Lower valid scores indicate more desirable servers.
- Unhealthy servers and servers with invalid metrics return `-1.0`.

These weights and thresholds are initial project choices and can be tuned during benchmarking.

### 4. Adaptive Routing — Least-Loaded Server

Implemented in `RoutingEngine.cpp`:

`findLeastLoadedServer(const vector<Server>& servers)`

The function:

- Iterates through all configured servers.
- Skips unhealthy servers.
- Rejects invalid load scores.
- Compares valid server scores.
- Selects the server with the lowest score.
- Returns `-1` when no eligible server exists.

### 5. Round Robin Routing

Implemented in `RoutingEngine.cpp`:

`findNextRoundRobinServer(const vector<Server>& servers, int& currentIndex)`

The function:

- Searches servers in circular order.
- Uses the modulo (`%`) operator for circular indexing.
- Skips unhealthy servers.
- Updates the index after selecting a server.
- Returns the selected server index.
- Returns `-1` if no healthy server is available.

The caller maintains `currentIndex` between requests so that the sequence continues across calls.

**Important distinction:** Round Robin selects servers by circular order, whereas adaptive routing selects servers based on their calculated load scores.

## 🧪 Day 3 Test Results

| Test Scenario | Result |
|---|---|
| Two healthy servers and one unhealthy server | Passed |
| All servers unhealthy | Passed |
| Only one healthy server | Passed |
| Multiple incoming request simulation | Passed |
| Adaptive routing comparison | Passed |

Example Round Robin distribution:

```text
Request 1 -> Server A
Request 2 -> Server B
Request 3 -> Server A
Request 4 -> Server B
```

When no healthy server is available, the routing function returns `-1`.

HTTP 503 handling will be implemented in a future HTTP-handling phase. The current application is a console-based simulation.

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
| `Server.h` | Server structure and function declarations |
| `Server.cpp` | Utilization and load-score implementation |
| `RoutingEngine.h` | Routing function declarations |
| `RoutingEngine.cpp` | Adaptive and Round Robin algorithms |
| `main.cpp` | Server initialization, metric display and request simulation |
| `CMakeLists.txt` | Build configuration |

## ⚙️ Technology Stack

| Technology | Purpose |
|---|---|
| C++17 | Core application |
| g++ / MinGW | C++ compilation |
| CMake | Build automation |
| Git | Version control |
| GitHub | Source-code hosting |
| Docker | Planned backend deployment |
| HTML, CSS, JavaScript | Planned dashboard |
| Chart.js | Planned monitoring visualizations |

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

## 🗺️ 30-Day Development Roadmap

| Phase | Implementation | Status |
|---|---|---|
| Day 1 | Environment setup, Server model, CMake and GitHub | Completed |
| Day 2 | Server metrics, utilization and adaptive routing | Completed |
| Day 3 | Modular architecture, Round Robin and edge-case testing | Completed |
| Upcoming | Additional routing algorithms | Planned |
| Upcoming | Backend health monitoring | Planned |
| Upcoming | HTTP request handling | Planned |
| Upcoming | Docker integration | Planned |
| Upcoming | Graphical dashboard | Planned |
| Upcoming | Chart.js visualizations | Planned |
| Upcoming | Performance benchmarking | Planned |

## 📊 Expected Final Outcomes

- Distribute real HTTP requests across multiple backend servers.
- Prevent unhealthy servers from receiving traffic.
- Compare Round Robin and adaptive routing.
- Handle backend failures.
- Visualize server performance through a graphical dashboard.
- Benchmark routing efficiency under different workloads.
- Demonstrate practical C++, networking and cloud-native concepts.

## 👨‍💻 Developer

**Laxman K**

GitHub: [@laxman548](https://github.com/laxman548)

---

This project is a hands-on exploration of C++, computer networking, load-balancing algorithms and cloud-native infrastructure, developed incrementally as part of a 30-day project plan.
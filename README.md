# 🚀 Adaptive Network Traffic Controller

A C++-based adaptive load-balancing project that evaluates backend server utilization, latency, and health to select the most suitable server.

The project is being developed incrementally over 30 days, with Round Robin routing, adaptive algorithms, Docker deployment, and a graphical monitoring dashboard planned for future phases.

---

## 📌 Project Overview

Applications commonly distribute incoming requests across multiple backend servers. Poor distribution can overload some servers while others remain underutilized.

The Adaptive Network Traffic Controller aims to solve this problem by monitoring backend server metrics and intelligently selecting an eligible server.

The project focuses on C++, computer networking, load-balancing algorithms, and cloud-native technologies.

## 🎯 Project Objectives

- Monitor multiple backend servers.
- Track active requests and server capacity.
- Calculate server utilization and latency.
- Calculate normalized server load scores.
- Exclude unhealthy servers from routing.
- Select the least-loaded healthy server.
- Implement Round Robin and adaptive routing algorithms.
- Integrate backend health checks and failure handling.
- Containerize the application using Docker.
- Develop a graphical dashboard using HTML, CSS, JavaScript, and Chart.js.
- Benchmark routing performance.

## 🏗️ Current System Architecture

The current implementation follows this workflow:

```text
             BACKEND SERVERS
                     |
                     v
           +-------------------+
           | Server Monitoring |
           | Load / Latency /  |
           | Health / Capacity |
           +-------------------+
                     |
                     v
           +-------------------+
           | Utilization       |
           | Calculation       |
           +-------------------+
                     |
                     v
           +-------------------+
           | Normalized Load   |
           | Score Calculation |
           +-------------------+
                     |
                     v
           +-------------------+
           | Health Validation |
           +-------------------+
                     |
                     v
           +-------------------+
           | Least-Loaded      |
           | Server Selection |
           +-------------------+
                     |
           +---------+---------+
           |         |         |
           v         v         v
        Server A  Server B  Server C
```

The current application evaluates configured server objects. Live HTTP request forwarding and real-time server monitoring are planned for future development.

## ⚙️ Technology Stack

| Technology | Purpose |
|---|---|
| C++17 | Core application development |
| g++ / MinGW | C++ compilation |
| CMake | Build automation |
| MinGW Makefiles | Build generator |
| Git | Version control |
| GitHub | Source code management |
| Docker | Planned containerization |
| HTML, CSS, JavaScript | Planned dashboard |
| Chart.js | Planned monitoring visualizations |

## 📂 Project Structure

```text
Adaptive-Network-Traffic-Controller/
│
├── src/
│   └── main.cpp
│
├── build/              # Generated locally
├── CMakeLists.txt
├── .gitignore
└── README.md
```

## 🖥️ Development Progress

### Day 1 — Project Foundation

**Status: Completed**

- Verified g++, Docker Engine, CMake, and MinGW Make.
- Created the project directory structure.
- Defined the C++ Server structure.
- Initialized three server objects.
- Displayed server information using loops.
- Configured CMakeLists.txt.
- Successfully built and executed the application.
- Initialized Git and connected GitHub.
- Created .gitignore and README.md.

### Day 2 — Server Metrics and Load Calculation

**Status: Completed**

Implemented the first server load calculation and selection mechanism.

**1. Server Metrics**

Extended the Server structure with:

- `serverId`
- `activerequests`
- `capacity`
- `latency`
- `healthy`

**2. Server Utilization Calculation**

Implemented:

`calculateUtilization(activeRequests, capacity)`

Formula:

```text
Utilization = (Active Requests / Capacity) × 100
```

The function validates invalid inputs, prevents division by zero, and calculates utilization using floating-point arithmetic.

**3. Normalized Load Score**

Implemented:

`calculateLoadScore(const Server& server)`

Initial scoring model:

```text
U = Utilization / 100

L = min(Latency / 200, 1)

Load Score = (0.7 × U) + (0.3 × L)
```

Where:

- U represents normalized utilization.
- L represents normalized latency.
- 70% weight is assigned to utilization.
- 30% weight is assigned to latency.
- 200 ms is the initial reference latency.
- Lower valid scores indicate more desirable servers.

These weights and thresholds are initial project configuration choices and can be tuned during benchmarking.

Note: Utilization is intentionally not capped at 100%, allowing the controller to identify overloaded servers.

**4. Least-Loaded Healthy Server Selection**

Implemented:

`findLeastLoadedServer(const vector<Server>& servers)`

The function:

- Iterates through all configured servers.
- Skips unhealthy servers.
- Rejects servers with invalid metrics.
- Compares valid server load scores.
- Selects the server with the lowest score.
- Returns `-1` when no eligible server is available.

**5. Example Server Results**

| Server | Active Requests | Capacity | Latency | Health | Load Score |
|---|---:|---:|---:|---|---:|
| Server A | 10 | 100 | 40 ms | Healthy | 0.13 |
| Server B | 80 | 100 | 250 ms | Healthy | 0.86 |
| Server C | 20 | 100 | 60 ms | Unhealthy | Unavailable |

**Selected Server: Server A**

**6. Edge-Case Testing**

Successfully tested:

| Test Scenario | Expected Behavior |
|---|---|
| All servers unhealthy | No healthy server available |
| Server with zero capacity | Reject invalid server |
| Server utilization above 100% | Identify overload |
| Healthy and unhealthy servers together | Exclude unhealthy servers |

## 🔧 Build and Run

### Prerequisites

- C++17-compatible compiler
- CMake
- MinGW Make
- Git

### Clone the Repository

```powershell
git clone https://github.com/laxman548/adaptive-network-traffic-controller.git
```

### Navigate to the Project

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

### Execute

```powershell
.\build\controller.exe
```

## 🗺️ Development Roadmap

| Phase | Implementation | Status |
|---|---|---|
| Day 1 | Project foundation and server modelling | Completed |
| Day 2 | Server metrics, utilization, normalized load scoring, and healthy server selection | Completed |
| Upcoming | Round Robin load balancing | Planned |
| Upcoming | Request distribution | Planned |
| Upcoming | HTTP request handling | Planned |
| Upcoming | Backend health monitoring | Planned |
| Upcoming | Adaptive routing engine | Planned |
| Upcoming | Docker integration | Planned |
| Upcoming | HTML/CSS/JavaScript dashboard | Planned |
| Upcoming | Chart.js monitoring | Planned |
| Upcoming | Performance benchmarking | Planned |

## 📊 Expected Final Outcomes

The completed system aims to:

- Distribute incoming requests across multiple backend servers.
- Prevent unhealthy servers from receiving traffic.
- Reduce unnecessary server overload.
- Adapt routing decisions to changing server conditions.
- Compare Round Robin and adaptive load balancing.
- Monitor server performance through a graphical dashboard.
- Evaluate routing efficiency through benchmarking.

## 👨‍💻 Developer

**Laxman K**

GitHub: [@laxman548](https://github.com/laxman548)

---

This project is a hands-on exploration of C++, computer networking, load balancing, algorithms, and cloud-native infrastructure, developed incrementally as part of a 30-day project plan.
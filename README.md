# 🚀 Adaptive Network Traffic Controller

**A C++-based intelligent load balancing system that dynamically distributes incoming HTTP requests across multiple backend servers based on server load, latency, and health.**

---

## 📌 Project Overview

In distributed systems, multiple backend servers handle incoming client requests. If requests are distributed poorly, some servers become overloaded while others remain underutilized.

The **Adaptive Network Traffic Controller** aims to solve this problem by monitoring backend server conditions and intelligently selecting the most suitable server for each incoming request.

The project focuses on building an adaptive traffic management system using C++, networking concepts, algorithms, and containerization.

## 🎯 Project Objectives

- Monitor backend server health and availability.
- Track active requests and server response latency.
- Dynamically distribute incoming HTTP requests.
- Avoid overloaded and unhealthy backend servers.
- Implement and compare load balancing algorithms.
- Containerize the system using Docker.

## 🏗️ System Architecture

The planned architecture:

```text
              CLIENT REQUESTS
                     |
                     v
          +----------------------+
          |  Traffic Controller  |
          +----------------------+
                     |
                     v
          +----------------------+
          |   Server Monitoring  |
          |  Load / Latency /    |
          |       Health         |
          +----------------------+
                     |
                     v
          +----------------------+
          |   Routing Engine     |
          |  Server Selection    |
          +----------------------+
                     |
          +----------+----------+
          |          |          |
          v          v          v
      +--------+ +--------+ +--------+
      |Server A| |Server B| |Server C|
      +--------+ +--------+ +--------+
```

## ⚙️ Technology Stack

| Technology | Purpose |
|---|---|
| C++17 | Core development |
| CMake | Build automation |
| g++ | C++ compilation |
| Git | Version control |
| GitHub | Source code management |
| Docker | Containerization |

## 📂 Project Structure

```text
Adaptive-Network-Traffic-Controller/
│
├── src/
│   └── main.cpp
│
├── CMakeLists.txt
├── .gitignore
├── README.md
└── build/             (Generated locally)
```

## 🖥️ Current Implementation

### Day 1 – Project Foundation

Completed:

- Development environment setup.
- Created the `Server` structure.
- Defined server attributes:
  - `serverId`
  - `activeRequests`
  - `latency`
  - `healthy`
- Created multiple server objects using `vector`.
- Implemented server information display using loops.
- Configured CMake build system.
- Successfully compiled and executed the application.
- Initialized GitHub repository.

## 🔧 Build and Run

### Prerequisites

- C++17 compatible compiler
- CMake
- Git

### Build Instructions

Clone the repository:

```bash
git clone https://github.com/laxman548/adaptive-network-traffic-controller.git
```

Navigate into the project:

```bash
cd adaptive-network-traffic-controller
```

Configure the project:

```bash
cmake -S . -B build -G "MinGW Makefiles"
```

Compile:

```bash
cmake --build build
```

Run:

```powershell
.\build\controller.exe
```

## 🗺️ Development Roadmap

| Phase | Implementation | Status |
|---|---|---|
| 1 | Project setup and server modelling | Completed |
| 2 | Server selection algorithm | Planned |
| 3 | Load balancing algorithms | Planned |
| 4 | HTTP request handling | Planned |
| 5 | Backend health monitoring | Planned |
| 6 | Adaptive routing engine | Planned |
| 7 | Docker integration | Planned |
| 8 | Performance evaluation | Planned |

## 📊 Expected Results

The final system aims to:

- Improve request distribution across backend servers.
- Reduce unnecessary server overload.
- Avoid routing requests to unhealthy servers.
- Adapt routing decisions to changing server conditions.
- Demonstrate the performance differences between adaptive routing and traditional load balancing.

---

## 👨‍💻 Developer

**Laxman K**

GitHub: [@laxman548](https://github.com/laxman548)

---

*This project is being developed incrementally as a hands-on exploration of C++, computer networking, load balancing, and cloud-native infrastructure.*
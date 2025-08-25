# ⚡ Parallel Task Manager (C++ with Pthreads & OpenMP)

This project is a **C++ console application** that demonstrates **parallel programming concepts** using both **POSIX Threads (pthreads)** and **OpenMP**.  
It simulates a simple **Task Manager**, where multiple tasks run in parallel, log their execution, and report results.

---

## 📖 Overview

The program creates **six different tasks**, executes them concurrently using **pthreads** with mutex-based synchronization,  
and then re-implements the same tasks using **OpenMP** with critical regions.

This project showcases:

- Multi-threading with **pthreads**
- Synchronization with **mutex locks**
- Parallel sections with **OpenMP**
- Performance comparison between pthreads and OpenMP

---

## 🎮 Implemented Tasks

Each thread simulates a different system-like task:

1. **Factorial Calculation**
   - Computes factorial of a number.
2. **Fibonacci Sequence**
   - Computes the nth Fibonacci number.
3. **Prime Number Counter**
   - Counts all prime numbers up to 100,000.
4. **File Download Simulation**
   - Simulates downloading a file with percentage updates.
5. **Directory Scan Simulation**
   - Simulates scanning a folder and listing files.
6. **Random Number Generator**
   - Generates and prints random numbers.

Each task reports:

- Start & finish messages
- Execution result (e.g., factorial result, Fibonacci number, prime count, etc.)
- Execution time

---

## 🧵 Threading & Synchronization

### 🔹 Pthreads Implementation

- Uses **`pthread_create`** to launch threads.
- Each thread logs its execution details in a shared vector `taskLogs`.
- A **mutex lock** (`pthread_mutex_t`) ensures that logs are written safely without race conditions.
- Main thread waits for completion using **`pthread_join`**.

### 🔹 OpenMP Implementation

- Uses **`#pragma omp parallel sections`** to run tasks in parallel.
- Shared log storage (`taskLogsOmp`) is protected by **`#pragma omp critical`** sections.
- No manual thread creation/joining needed.

---

## 📂 Project Structure

```
parallel-task-manager-cpp/
│
├── src/
│   └── parallel_task_manager.cpp   # Main C++ source code
│
├── README.md              # Project documentation
└── LICENSE                # MIT License
```

---

## ▶️ How to Run

### 🔧 Compile with Pthreads

```bash
g++ src/task_manager.cpp -o task_manager -lpthread
./parallel_task_manager
```

### 🔧 Compile with OpenMP

```bash
g++ src/task_manager.cpp -o task_manager -fopenmp
./parallel_task_manager
```

---

## 📸 Sample Output

```
[Thread 1] Starting Factorial Task...
[Thread 2] Starting Fibonacci Task...
[Thread 3] Starting Prime Number Task...
[Thread 4] Starting Download File Task...
[Thread 5] Starting Directory Scan Task...
[Thread 6] Starting Random Number Task...
...
[Thread 1] Done!!! Result = 40320
[Thread 2] Done!!! Fibonacci(18) = 2584
[Thread 3] Done!!! Primes Found Between (2-100000). Count = 9592
[Thread 4] File Download Completed :)
[Thread 5] Directory Scan Completed :)
[Thread 6] Random Numbers = 72 15 93 40 61

<<<<<<<< [Pthreads + Mutex] Execution Time: 12.452891 seconds. >>>>>>>>
!! PASSING TO THE OpenMP !!

<<<<<<<< [OpenMP] Execution Time: 15.823712 seconds. >>>>>>>>
```

---

## 🚀 Future Improvements

- Add more task types (e.g., sorting, matrix multiplication).
- Store logs in external files.
- Visualize thread execution timeline.
- Compare performance across different system configurations.

---

## 🛠️ Technologies

- **Language**: C++17
- **Threading APIs**: POSIX Threads (pthreads), OpenMP
- **Synchronization**: Mutex locks, critical sections
- **Libraries**: `<pthread.h>`, `<omp.h>`, `<chrono>`, `<thread>`, `<vector>`

---

## 📜 License

This project is licensed under the **MIT License**.  
See the [LICENSE](./LICENSE) file for details.

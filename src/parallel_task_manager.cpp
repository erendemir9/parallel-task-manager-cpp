#include <chrono>
#include <cstdlib>
#include <ctime>
#include <iostream>
#include <omp.h>
#include <pthread.h>
#include <stdio.h>
#include <string>
#include <thread>
#include <time.h>
#include <vector>

using namespace std;

struct TaskLog {
  int thread_id;
  string task_name;
  double duration_sec;
};

pthread_mutex_t log_mutex = PTHREAD_MUTEX_INITIALIZER;
vector<TaskLog> taskLogs;
vector<TaskLog> taskLogsOmp;

double get_time_sec() {
  struct timespec ts;
  clock_gettime(CLOCK_MONOTONIC, &ts);
  return ts.tv_sec + ts.tv_nsec / 1e9;
}

void *factorial_task(void *arg) {
  int thread_id = *(int *)arg;
  double start_time = get_time_sec();
  printf("[Thread %d] Starting Factorial Task...\n", thread_id);
  int result = 1;
  int number = 8;

  for (int i = 1; i <= number; i++) {
    result *= i;
  }

  this_thread::sleep_for(chrono::seconds(2));
  printf("[Thread %d] Done!!! Result = %d\n", thread_id, result);

  double end_time = get_time_sec();

  pthread_mutex_lock(&log_mutex);
  taskLogs.push_back({thread_id, "Factorial", end_time - start_time});
  pthread_mutex_unlock(&log_mutex);
  return NULL;
}

void *factorial_task_omp(void *arg) {
  int thread_id = *(int *)arg;
  double start_time = get_time_sec();
  printf("[Thread %d] Starting Factorial Task...\n", thread_id);
  int result = 1;
  int number = 8;

  for (int i = 1; i <= number; i++) {
    result *= i;
  }

  this_thread::sleep_for(chrono::seconds(2));
  printf("[Thread %d] Done!!! Result = %d\n", thread_id, result);

  double end_time = get_time_sec();

#pragma omp critical
  {
    taskLogsOmp.push_back({thread_id, "Factorial", end_time - start_time});
  }
  return NULL;
}

void *fibonacci_task(void *arg) {
  int thread_id = *(int *)arg;
  double start_time = get_time_sec();
  printf("[Thread %d] Starting Fibonacci Task...\n", thread_id);

  int N = 18;
  int a = 0, b = 1, c;
  if (N == 0) {
    c = 0;
  } else if (N == 1) {
    c = 1;
  } else {
    for (int i = 2; i <= N; ++i) {
      c = a + b;
      a = b;
      b = c;
    }
  }

  this_thread::sleep_for(chrono::seconds(3));
  printf("[Thread %d] Done!!! Fibonacci(%d) = %d\n", thread_id, N, c);

  double end_time = get_time_sec();

  pthread_mutex_lock(&log_mutex);
  taskLogs.push_back({thread_id, "Fibonacci", end_time - start_time});
  pthread_mutex_unlock(&log_mutex);
  return NULL;
}

void *fibonacci_task_omp(void *arg) {
  int thread_id = *(int *)arg;
  double start_time = get_time_sec();
  printf("[Thread %d] Starting Fibonacci Task...\n", thread_id);

  int N = 18;
  int a = 0, b = 1, c;
  if (N == 0) {
    c = 0;
  } else if (N == 1) {
    c = 1;
  } else {
    for (int i = 2; i <= N; ++i) {
      c = a + b;
      a = b;
      b = c;
    }
  }

  this_thread::sleep_for(chrono::seconds(3));
  printf("[Thread %d] Done!!! Fibonacci(%d) = %d\n", thread_id, N, c);

  double end_time = get_time_sec();

#pragma omp critical
  {
    taskLogsOmp.push_back({thread_id, "Fibonacci", end_time - start_time});
  }
  return NULL;
}

void *primenumber_task(void *arg) {
  int thread_id = *(int *)arg;
  double start_time = get_time_sec();
  printf("[Thread %d] Starting Prime Number Task...\n", thread_id);
  int primeCount = 0;
  int limit = 100000;
  for (int i = 2; i <= limit; i++) {
    bool isPrime = true;
    for (int j = 2; j < i; j++) {
      if (i % j == 0) {
        isPrime = false;
        break;
      }
    }
    if (isPrime) {
      ++primeCount;
    }
  }
  printf("->[Thread %d] Prime Numbers Count Calculating...\n", thread_id);
  this_thread::sleep_for(chrono::seconds(3));
  printf("[Thread %d] Done!!! Primes Found Between (2-100000). Count = %d\n",
         thread_id, primeCount);
  double end_time = get_time_sec();

  pthread_mutex_lock(&log_mutex);
  taskLogs.push_back({thread_id, "Prime Number", end_time - start_time});
  pthread_mutex_unlock(&log_mutex);

  return NULL;
}

void *primenumber_task_omp(void *arg) {
  int thread_id = *(int *)arg;
  double start_time = get_time_sec();
  printf("[Thread %d] Starting Prime Number Task...\n", thread_id);
  int primeCount = 0;
  int limit = 100000;
  for (int i = 2; i <= limit; i++) {
    bool isPrime = true;
    for (int j = 2; j < i; j++) {
      if (i % j == 0) {
        isPrime = false;
        break;
      }
    }
    if (isPrime) {
      ++primeCount;
    }
  }
  printf("->[Thread %d] Prime Numbers Count Calculating...\n", thread_id);
  this_thread::sleep_for(chrono::seconds(3));
  printf("[Thread %d] Done!!! Primes Found Between (2-100000). Count = %d\n",
         thread_id, primeCount);
  double end_time = get_time_sec();

#pragma omp critical
  {
    taskLogsOmp.push_back({thread_id, "Prime Number", end_time - start_time});
  }

  return NULL;
}

void *download_file_task(void *arg) {
  int thread_id = *(int *)arg;
  double start_time = get_time_sec();
  printf("[Thread %d] Starting Download File Task...\n", thread_id);

  int totalPercentage = 10;
  for (int i = 1; i <= totalPercentage; ++i) {
    this_thread::sleep_for(chrono::seconds(2)); //
    printf("===>>>[Thread %d] File Downloading Progress: %d%%\n", thread_id,
           i * 10);
  }

  printf("===>>>[Thread %d] File Download Completed :)\n", thread_id);
  printf("[Thread %d] Done!!! File Download Simulation.\n", thread_id);
  double end_time = get_time_sec();
  pthread_mutex_lock(&log_mutex);
  taskLogs.push_back({thread_id, "Download Simulation", end_time - start_time});
  pthread_mutex_unlock(&log_mutex);

  return NULL;
}
void *download_file_task_omp(void *arg) {
  int thread_id = *(int *)arg;
  double start_time = get_time_sec();
  printf("[Thread %d] Starting Download File Task...\n", thread_id);

  int totalPercentage = 10;
  for (int i = 1; i <= totalPercentage; ++i) {
    this_thread::sleep_for(chrono::seconds(2)); //
    printf("===>>>[Thread %d] File Downloading Progress: %d%%\n", thread_id,
           i * 10);
  }

  printf("===>>>[Thread %d] File Download Completed :)\n", thread_id);
  printf("[Thread %d] Done!!! File Download Simulation.\n", thread_id);
  double end_time = get_time_sec();
#pragma omp critical
  {
    taskLogsOmp.push_back(
        {thread_id, "Download Simulation", end_time - start_time});
  }

  return NULL;
}

void *directory_task(void *arg) {
  int thread_id = *(int *)arg;
  double start_time = get_time_sec();

  printf("[Thread %d] Starting Directory Scan Task...\n", thread_id);

  string files[] = {"photo_1.png", "cpp_threads_report.pdf", "new_lyrics.txt"};

  for (int i = 1; i <= 3; ++i) {
    this_thread::sleep_for(chrono::seconds(2));
    printf("-->>[Thread %d] Found File %s\n", thread_id, files[i - 1].c_str());
  }

  printf("-->>[Thread %d] Directory Scan Completed :)\n", thread_id);
  printf("[Thread %d] Done!!! Directory Scan Simulation.\n", thread_id);

  double end_time = get_time_sec();
  pthread_mutex_lock(&log_mutex);
  taskLogs.push_back({thread_id, "Directory Scan", end_time - start_time});
  pthread_mutex_unlock(&log_mutex);

  return NULL;
}

void *directory_task_omp(void *arg) {
  int thread_id = *(int *)arg;
  double start_time = get_time_sec();

  printf("[Thread %d] Starting Directory Scan Task...\n", thread_id);

  string files[] = {"photo_1.png", "cpp_threads_report.pdf", "new_lyrics.txt"};

  for (int i = 1; i <= 3; ++i) {
    this_thread::sleep_for(chrono::seconds(2));
    printf("-->>[Thread %d] Found File %s\n", thread_id, files[i - 1].c_str());
  }

  printf("-->>[Thread %d] Directory Scan Completed :)\n", thread_id);
  printf("[Thread %d] Done!!! Directory Scan Simulation.\n", thread_id);

  double end_time = get_time_sec();
#pragma omp critical
  {
    taskLogsOmp.push_back({thread_id, "Directory Scan", end_time - start_time});
  }

  return NULL;
}

void *random_number_task(void *arg) {
  int thread_id = *(int *)arg;

  srand(time(NULL) + thread_id);
  double start_time = get_time_sec();

  printf("[Thread %d] Starting Random Number Task...\n", thread_id);

  int nums[5];
  for (int i = 0; i < 5; ++i) {
    nums[i] = rand() % 100 + 1;
    this_thread::sleep_for(chrono::seconds(1));
  }

  printf("---->>>>[Thread %d] Random numbers = ", thread_id);
  for (int i = 0; i < 5; ++i) {
    printf(" %d", nums[i]);
  }
  printf("\n");

  printf("[Thread %d] Done!!! Random Number Simulation\n", thread_id);
  double end_time = get_time_sec();
  pthread_mutex_lock(&log_mutex);
  taskLogs.push_back({thread_id, "Random Numbers", end_time - start_time});
  pthread_mutex_unlock(&log_mutex);

  return NULL;
}

void *random_number_task_omp(void *arg) {
  int thread_id = *(int *)arg;

  srand(time(NULL) + thread_id);
  double start_time = get_time_sec();

  printf("[Thread %d] Starting Random Number Task...\n", thread_id);

  int nums[5];
  for (int i = 0; i < 5; ++i) {
    nums[i] = rand() % 100 + 1;
    this_thread::sleep_for(chrono::seconds(1));
  }

  printf("---->>>>[Thread %d] Random numbers = ", thread_id);
  for (int i = 0; i < 5; ++i) {
    printf(" %d", nums[i]);
  }
  printf("\n");

  printf("[Thread %d] Done!!! Random Number Simulation\n", thread_id);
  double end_time = get_time_sec();
#pragma omp critical
  {
    taskLogsOmp.push_back({thread_id, "Random Numbers", end_time - start_time});
  }

  return NULL;
}

void run_pthread_mutex() {
  pthread_t t1, t2, t3, t4, t5, t6;
  int id1 = 1, id2 = 2, id3 = 3, id4 = 4, id5 = 5, id6 = 6;

  double start = get_time_sec();

  pthread_create(&t1, NULL, factorial_task, &id1);
  pthread_create(&t2, NULL, fibonacci_task, &id2);
  pthread_create(&t3, NULL, primenumber_task, &id3);
  pthread_create(&t4, NULL, download_file_task, &id4);
  pthread_create(&t5, NULL, directory_task, &id5);
  pthread_create(&t6, NULL, random_number_task, &id6);

  pthread_join(t1, NULL);
  pthread_join(t2, NULL);
  pthread_join(t3, NULL);
  pthread_join(t4, NULL);
  pthread_join(t5, NULL);
  pthread_join(t6, NULL);

  double end = get_time_sec();

  printf(
      "\n <<<<<<<< [Pthreads + Mutex] Execution Time: %.6f seconds. >>>>>>>>\n",
      end - start);
}

void run_openmp_tasks() {
  int id1 = 1, id2 = 2, id3 = 3, id4 = 4, id5 = 5, id6 = 6;
  double start = get_time_sec();

#pragma omp parallel sections
  {
#pragma omp section
    factorial_task_omp(&id1);
#pragma omp section
    fibonacci_task_omp(&id2);
#pragma omp section
    primenumber_task_omp(&id3);
#pragma omp section
    download_file_task_omp(&id4);
#pragma omp section
    directory_task_omp(&id5);
#pragma omp section
    random_number_task_omp(&id6);
  }

  double end = get_time_sec();
  printf("\n <<<<<<<< [OpenMP] Execution Time: %.6f seconds. >>>>>>>>\n",
         end - start);
}

int main() {
  run_pthread_mutex();

  cout << "\n!! PASSING TO THE OpenMP !!\n" << endl;

  run_openmp_tasks();

  cout << "\n**************** Execution Summary (Pthreads): ****************\n"
       << endl;
  for (const auto &t : taskLogs) {
    cout << " - Thread " << t.thread_id << ": Task = " << t.task_name
         << " -> Time = " << t.duration_sec << " seconds.\n";
  }
  cout << "\n**************************************************************\n"
       << endl;

  cout << "\n**************** Execution Summary (OpenMP): ****************\n"
       << endl;
  for (const auto &t : taskLogsOmp) {
    cout << "Thread " << t.thread_id << ": " << t.task_name << " | "
         << t.duration_sec << " sec\n";
  }
  cout << "\n**************************************************************\n"
       << endl;

  return 0;
}

# Operating System Synchronization Examples

This repository contains implementations of classic operating system synchronization problems.

## Examples

### 1. Readers-Writers Problem
- Located in: `Example/Reader_Write.cc`
- Implementation in C++ using mutex and condition variables
- Demonstrates how multiple readers can read simultaneously while writers need exclusive access
- To compile and run:
  ```bash
  g++ -std=c++11 Example/Reader_Write.cc -o reader_writer -pthread
  ./reader_writer
  ```

### 2. Dining Philosophers Problem
- Located in: `Example/Dining_Philosopher.py`
- Implementation in Python using threading
- Shows deadlock prevention in the classic dining philosophers scenario
- To run:
  ```bash
  python3 Example/Dining_Philosopher.py
  ```

### 3. Producer-Consumer Problem
- Located in: `Example/Producer_consumer_problem.cc`
- Implementation in C++ using condition variables and mutex
- Demonstrates bounded buffer synchronization between producer and consumer
- To compile and run:
  ```bash
  g++ -std=c++11 Example/Producer_consumer_problem.cc -o producer_consumer -pthread
  ./producer_consumer
  ```

## Problem Descriptions

### Readers-Writers
- Multiple readers can read simultaneously
- Only one writer can write at a time
- While a writer is writing, no reader can read

### Dining Philosophers
- Five philosophers sitting around a table
- Need two forks to eat
- Implements resource hierarchy solution to prevent deadlock

### Producer-Consumer
- Producer adds data to a bounded buffer
- Consumer removes data from the buffer
- Synchronization ensures buffer integrity

## References
1. Readers-Writers: https://blog.jyotiprakash.org/readers-writers-problemz
2. Dining Philosophers: https://brandonkindred.medium.com/mastering-concurrency-with-the-dining-philosopher-problem-8445920f7863
3. Producer-Consumer: https://www.pradeepbangalore.in/post/producer-consumer-problem-c-solution-using-condition-variables
NPU (Neural Processing Unit) là bộ vi xử lý chuyên dụng được thiết kế để mô phỏng chức năng xử lý của não người, tối ưu hóa cho các tác vụ AI.
# Producer–Consumer Synchronization Using IPC

This project implements the classic **producer–consumer problem** in **C** using **Linux interprocess communication (IPC)** mechanisms. The goal is to safely coordinate multiple producer and consumer processes while preventing race conditions, data loss, and duplicate consumption under asynchronous execution conditions.

## ✨ Features
- Producer–consumer coordination across processes
- Custom semaphore implementation (`SSemaphore`)
- Message queues for data transfer
- Lock files for mutual exclusion
- Robust handling of concurrent access

## 🛠️ Technologies Used
- C
- Linux IPC
  - Semaphores
  - Message queues
  - Lock files
- GCC

## 📁 Project Structure
```bash
├── producer_consumer.cxx   # Main producer–consumer implementation
├── SSemaphore.h            # Semaphore interface
├── SSemaphore.cxx          # Semaphore implementation
```

## ⚙️ How It Works
- **Producers** generate data and place it into a shared message queue.
- **Consumers** retrieve and process data from the queue.
- **Semaphores** control access to shared resources and enforce ordering.
- **Lock files** ensure mutual exclusion where required.
- The design prevents:
  - Race conditions
  - Lost messages
  - Duplicate consumption

This implementation emphasizes OS-level synchronization primitives rather than thread-level abstractions.

## 🧪 Build & Run
Compile using GCC:
```bash
g++ producer_consumer.cxx SSemaphore.cxx -o producer_consumer
```

Run:
```bash
./producer_consumer
```
⚠️ This program is intended to be run on a Linux-based system with IPC support.

---

## 📜 License

This project is licensed under the MIT License. See the LICENSE file for details.

---

## 📬 Contact
For questions or feedback, please contact Hannah G. Simon at hgsimon2@gmail.com.

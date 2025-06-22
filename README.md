# # Project 2 – OpenMP Parallel Merge Sort

##  Overview

This project is a parallelized implementation of the Merge Sort algorithm using **OpenMP**. It builds on the sequential version from Project 1 by applying multithreading to speed up sorting large arrays using shared-memory parallelism.

---

## ⚙ Parallelization Approach (OpenMP)

The core recursive `mergeSort` function is parallelized using OpenMP’s `#pragma omp parallel` and `#pragma omp task` directives. The parallelization strategy includes:

- Dividing the recursive calls to `mergeSort()` into separate **OpenMP tasks**, allowing different threads to sort different subarrays in parallel.
- A **depth limit** is used to control task creation and prevent thread oversubscription.
- The `merge()` step is executed sequentially (it could be parallelized too, but doing so adds complexity and minimal gain for small merges).

---

## Compilation & Execution

### Requirements:
- Linux environment with `g++` and OpenMP support.
- You can use WSL or any Linux VM.

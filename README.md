# Metal BLAS Implementation (WIP)

This repository is a personal exploration project where I implement various Basic Linear Algebra Subprograms (BLAS) using Apple's Metal framework. It's designed as a way to understand Metal's performance and functionality in mathematical computations.

## Features

- **BLAS Level 1 Functions:** `axpy`, `copy`, `dot`(wip), `scal`, and `swap`.
- **BLAS Level 2 Functions:** `gemv`(wip) (General Matrix-Vector multiplication).
- **BLAS Level 3 Functions:** `gemm`(wip) (General Matrix-Matrix multiplication).

## TODO
- [ ] 2D supports for Tensor
- [ ] Implement `dot`
- [ ] Implement `gemv`
- [ ] Implement `gemm`

## Metal Concepts

- **Thread:** The smallest unit of execution, similar to a thread in CUDA.
- **Threadgroup:** Equivalent to a "thread block" in CUDA, a group of threads that share data and synchronize execution.
- **Implicit Grid:** Metal kernels are dispatched with a 3D grid of threadgroups, setting the framework for executing kernels across multiple threads and threadgroups.

## Memory Types

- **Registers:** Fastest, per-thread access.
- **Local Memory:** Per-thread but stored in global memory, higher latency.
- **Shared Memory:** Shared within a thread block, faster inter-thread communication.
- **Global Memory:** Available to the entire grid, highest latency.
- **Constant Memory:** Optimized for read-only access when shared across multiple threads.

This project is just for fun and learning, enhancing understanding of both BLAS and Metal's parallel computing capabilities.


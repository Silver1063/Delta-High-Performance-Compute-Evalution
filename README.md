<img width="1992" height="960" alt="image" src="https://github.com/user-attachments/assets/4758c9b4-d034-4e33-8b39-b570d4a8e9a8" />

# Acknowledgement
This research used the Delta advanced computing and data resource which is supported by the National Science Foundation (award OAC 2005572) and the State of Illinois. Delta is a joint effort of the University of Illinois Urbana-Champaign and its National Center for Supercomputing Applications.
https://delta.ncsa.illinois.edu/

<img width="490" height="209" alt="image" src="https://github.com/user-attachments/assets/eabef75f-48ba-495f-a4b9-94bdfd10e687" />

To view the results, the pdf paper is provided for ease of reading, while the machine learning models and training are under the jupyter notebook

# Project Overview
This project focuses on Predicting and Optimizing High Performance Computing (HPC) Input/Output Variability by examining how system configurations influence performance fluctuations. The goal is to develop a robust data-analytic framework that can predict throughput variability, a critical yet underexplored factor that impacts scientific reproducibility and resource efficiency.

The study utilizes a custom built benchmarking tool to collect performance data on the Delta Supercomputer. By analyzing metrics such as file size, record size, and thread counts, this project seeks to balance the trade-off between maximizing raw throughput and minimizing the unpredictable "jitter" that can lead to inefficient resource allocation and increased computational costs.

# Key Features
- Benchmarking & Data Collection
  - Custom I/O Profiling: A C based benchmarking utility (benchmark.c) designed to measure read/write throughput across various file and record sizes
  - Delta Supercomputer Integration: Performance testing specifically adjusted for the architecture of the Delta Supercomputer to ensure practical relevance.
- Surrogate Modeling & Prediction
  - Performance vs. Variability Surfaces: Developing distinct statistical models to map both raw performance (throughput) and the variability of that performance across different configurations.
  - Interpolation & Extrapolation: Using regression techniques to estimate system behavior for configurations not tested experimentally.
- Statistical Modeling & Optimization
  - Constrained Optimization: Implementing an objective function to minimize variability while maintaining a mandatory minimum performance threshold.
  - Predictive Regression: Training Linear Regression and Gamma GLM models in Python to quantify the impact of features like num_threads and memory_size on throughput.

# Results
The project identifies that system configurations specifically record size and file size directly and significantly affect I/O speed and variability. Optimization results suggests that settings such as a 1024KB file size and 512KB record size provide a "best fit" solution for the tested environment. These findings provide a systematic methodology for HPC administrators to manage variability, ultimately leading to more predictable task scheduling and reduced energy costs.

# Tools Used
- Languages: C (Benchmarking), Python (Data Modeling)
- Libraries: pandas, numpy, scikit-learn (StandardScaler, LinearRegression), scipy.optimize (Direct)
- Environment: Delta Supercomputer, Jupyter Notebook

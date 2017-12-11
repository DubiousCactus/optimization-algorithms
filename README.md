# Introduction
Implementation of different optimization / classification algorithms. This was done as a research project for the MSc. in Computer Engineering.
The different classifiers implemented are tested on two sets of data:

- [**MNIST**](http://yann.lecun.com/exdb/mnist/): A set of 70K (vectorized) 28x28 pixel images depicting hand-written images
- [**ORL**](http://www.cad.zju.edu.cn/home/dengcai/Data/FaceData.html): A set of 400 (vectorized) 40x30 facial images depicting 40 persons

# Algorithms implemented

The following classification algorithms are implemented:

- [x] Nearest class centroid
- [x] Nearest sub-class centroid
- [x] Nearest neighbour
- [ ] Perceptron trained using backpropagation
- [x] Perceptron trained using MSE

# External libraries & requirements

This project uses the following embedded libraries:

- [**Eigen**](http://eigen.tuxfamily.org/index.php?title=Main_Page): A C++ template library for linear algebra: matrices, vectors, numerical solvers, and related algorithms.
- [**mnist-parser**](https://github.com/wichtounet/mnist): A simple C++ reader for MNIST dataset

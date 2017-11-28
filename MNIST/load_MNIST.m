

function [train_images,test_images,train_labels,test_labels] = load_MNIST()

train_images = loadMNISTImages('train-images.idx3-ubyte');
test_images = loadMNISTImages('t10k-images.idx3-ubyte');
train_labels = loadMNISTLabels('train-labels.idx1-ubyte');
test_labels = loadMNISTLabels('t10k-labels.idx1-ubyte');

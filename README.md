Multi-Label Classification Benchmark
====================================

This repository constists of all the benchmarks done for multi-label
classification implemented using [Shogun Machine Learning
Toolbox](https://shogun-toolbox.org). 

Multi-Label classification is done using the Structured Output (SO) Learning
framework implemented in ```SHOGUN```. 

###Contents

* ```multilabel_structured_prediction``` : It is the first notebook to give a
  very brief understanding and background of *Multi-Label Structrured
  Prediction* along with the benchmarks done against ```scikit-learn```'s
  implemenation.

* ```benchmarks.md```: It contains brief description of the accurarcy and
  time-taken by the multi-label models implemented in shogun.

* ```benchmarks.cpp```: It is ```C++``` programming for performing benchmarks on
  various multi-label models implemented with varying number of classes,
  samples and features.

####Usage of benchmarks.cpp

```
$ make
$ ./benchmarks <model> <num_classes> <dim_features> <num_samples>
```

for example
```
$ ./benchmarks MultilabelModel 10 1000 100
```
would perform tests on ```MultilabelModel``` with 

* 10 number of classes

* 1000 dimesional features

* 100 training examples

This *doesn't* perform accuracy analysis as the data are very random. It should
be only used for performing **timing** analysis and **memory usage** analysis.

For **memory usage** profiling, you can use ```valgrind``` along with
```massiff``` like :

```
$ valgrind --tool=massif ./benchmark MultilabelModel 100 10000 1000
$ ms_print massif.*
```


Benchmarks
==========

```StochasticSOSVM``` machine is used for training all the models.

###Yeast Multi-Label Data


| Model                                           | Accuracy | Train-time |
|-------------------------------------------------|----------|------------|
|MultilabelModel *without* threshold/bias term    | 0.339940 | 1.974854   |
|MultilabelModel *with* threshold/bias term       | 0.491876 | 2.007969   |
|MultilabelCLRModel *without* threshold/bias term | 0.345868 | 2.505659   |
|MultilabelCLRModel *with* threshold/bias term    | 0.500197 | 2.655564   |

Comparing the results with ```scikit-learn``` implemenation 

* Accuracy   : 0.497962
* Train-time : 3.018060

###Scene Multi-Label Data

| Model                                           | Accuracy | Train-time |
|-------------------------------------------------|----------|------------|
|MultilabelModel *without* threshold/bias term    | 0.548774 | 1.877675   |
|MultilabelModel *with* threshold/bias term       | 0.579571 | 1.782198   |
|MultilabelCLRModel *without* threshold/bias term | 0.557414 | 2.507857   |
|MultilabelCLRModel *with* threshold/bias term    | 0.581800 | 2.474834   |

Comparing the results with ```scikit-learn``` implemenation 

* Accuracy   : 0.576226
* Train-time : 1.697819

###RCV1V2 (Regions; Full Sets)

* Number of classes: 279

* Number of samples:  
	* 23,149 (Training)   
	* 199,328 (testing)

* Number of features: 47,236

| Model                                         | Accuracy | Train-time |
|-----------------------------------------------|----------|------------|
|MultilabelModel *with* threshold/bias term     | 0.821756 | 12732.122  |
|MultilabelCLRModel *with* threshold/bias term  | 0.841264 | 27864.244  |

###RCV1V2 (Topics; Subsets)

* Number of classes: 101

* Number of samples:  
	* 3000 (Training)   
	* 3000 (testing)

* Number of features: 47,236

For this data set, the models were trained using multi-processing (on 4-cores processor) with 8 threads.

| Model                                         | Accuracy | Train-time |
|-----------------------------------------------|----------|------------|
|MultilabelModel *with* threshold/bias term     | 0.843219 | 2250.233   |
|MultilabelCLRModel *with* threshold/bias term  | 0.857997 | 5170.678   |


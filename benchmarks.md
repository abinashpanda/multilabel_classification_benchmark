Benchmarks
==========

```StochasticSOSVM``` machine is used for training all the models.

###Yeast Multi-Label Data


| Model | Accuracy | Train-time |
|---------|----------|------------|
|MultilabelModel *without* threshold/bias term    | 0.339940 | 1.974854 |
|MultilabelModel *with* threshold/bias term       | 0.491876 | 2.007969 |
|MultilabelCLRModel *without* threshold/bias term | 0.345868 | 2.505659 |
|MultilabelCLRModel *with* threshold/bias term    | 0.500197 | 2.655564 |

Comparing the results with ```scikit-learn``` implemenation 

* Accuracy   : 0.497962
* Train-time : 3.018060

###Scene Multi-Label Data

| Model | Accuracy | Train-time |
|---------|----------|------------|
|MultilabelModel *without* threshold/bias term    | 0.548774 | 1.877675 |
|MultilabelModel *with* threshold/bias term       | 0.579571 | 1.782198 |
|MultilabelCLRModel *without* threshold/bias term | 0.557414 | 2.507857 |
|MultilabelCLRModel *with* threshold/bias term    | 0.581800 | 2.474834 |

Comparing the results with ```scikit-learn``` implemenation 

* Accuracy   : 0.576226
* Train-time : 1.697819


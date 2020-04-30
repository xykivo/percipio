Introduction to Machine Learning (Google Crash course)
======================================================

Notes for Google online crash course at
https://developers.google.com/machine-learning/crash-course/ml-intro

# Framing
What is (supervised) machine learning?
ML systems produce useful predictions on never before seen data.

## Label
A label is the value predicted.

## Feature
An input variable. A machine learning model may hold more have more than 1
feature.

## Example
An instance of data.
* Labeled example: includes both the features and label values  
  {feature-0, feature-1, feature-2, label}: (f0, f1, f2, l)
* Unlabeled example: holds only feature values  
  {feature-0, feature-1, feature-2, ?}: (f0, f1, f2, ?)

Labeled examples are used to train the machine learning model.
The machine learning model is used to predict the label values of unlabeled
examples.

## Model
A model defines the relationship between features and labels.

### Training
Creating, or teaching the mode. This is usually done by "showing" the model
labeled examples from the model gradually learns the relationship between
the features and labels.

### Inference
Applying the trained to unlabeled examples. Use a trained model to get the
predicted label values from the provided feature values in the unlableled
example.

## Regression
A regression model predicts continous values.
E.g. probability a user will perform some action such as click a button

## Classification
A classification model predicts discrete values.
E.g. Is a given email spam or not spam? Is the given image the image of a dog?

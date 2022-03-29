# 
#   Copyright 2022 John I. Krassikoff
#   
#   This program is free software : you can redistribute it and /or modify
#   it under the terms of the GNU General Public License as published
#   by the Free Software Foundation, either version 3 of the License, or
#   (at your option) any later version.
#   
#   This program is distributed in the hope that it will be useful,
#   but WITHOUT ANY WARRANTY; without even the implied warranty of
#   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.See the
#   GNU General Public License for more details.
#   
#
#  A 1 dimensional CNN for processing of time-series data.
#  The fitted model is used to calculate a naive prediction
#  from sample test data. This is the core of a more stable
#  and complete construction. Uses Keras and Tensorflow.
#
from keras.models import Sequential
from keras.layers import Dense
from keras.layers import Flatten
from keras.layers.convolutional import Conv1D
from keras.layers.convolutional import MaxPooling1D
import numpy as np
import matplotlib.pyplot as plt
import os
os.environ['KERAS_BACKEND'] = 'Tensorflow'
 
def subdivide_data_array(data_array, number_of_data_points, number_of_chunks):
    x1 = list()
    x2 = list()
    end_idx_location = 0
    last_valid_location = number_of_data_points - 1
    for idx in range(number_of_data_points):
        end_idx_location = idx + number_of_chunks
        if end_idx_location > last_valid_location:
            break
        x1.append(data_array[idx:end_idx_location])
        x2.append(data_array[end_idx_location])
    return np.array(x1), np.array(x2)

def construct_model(number_of_chunks, number_of_features):
    model = Sequential()
    model.add(Conv1D(filters=128, kernel_size=3, activation='relu', input_shape=(number_of_chunks, number_of_features)))
    model.add(MaxPooling1D(pool_size=2))
    model.add(Flatten())
    model.add(Dense(64, activation='relu'))
    model.add(Dense(32, activation='relu'))
    model.add(Dense(16, activation='relu'))
    model.add(Dense(8, activation='relu'))
    model.add(Dense(2, activation='relu'))
    model.add(Dense(1))
    model.compile(optimizer='adam', loss='mse')
    return model

def fit_model(model, x1, x2, num_epochs):
    model.fit(x1, x2, epochs=num_epochs, verbose=1)
    return model
 
def naive_prediction_from_model(model, test_input, number_of_chunks, number_of_features):
    test_input = test_input.reshape((1, number_of_chunks, number_of_features))
    predicted = model.predict(test_input, verbose=0)
    return predicted

def generate_model(data_array, test_input, stride, number_of_data_points, number_of_chunks, number_of_features, num_epochs):
    predicted = 0
    x1, x2 = subdivide_data_array(data_array, number_of_data_points, number_of_chunks)
    x1 = x1.reshape((x1.shape[0], x1.shape[1], number_of_features))
    model = construct_model(number_of_chunks, number_of_features)
    model = fit_model(model, x1, x2, num_epochs)
    return model

def plot_data(data_array):
    fig, axs = plt.subplots(3, figsize=(10,5))
    fig.suptitle('Vertically stacked subplots')
    axs[0].plot(data_array[0,:], color = 'red')
    axs[1].plot(data_array[1,:], color = 'green')
    axs[2].plot(data_array[2,:], color = 'blue')
    plt.show()

def execute():
    predicted = 0
    tmp_array = np.load('test.npy')
    #plot_data(tmp_array)
    data_array = tmp_array[0,:]
    test_input = np.sort(data_array[100:1124])
    stride = 4
    num_epochs = 1000
    number_of_features = 1
    number_of_data_points = len(data_array)
    number_of_chunks = (int)(number_of_data_points/stride)
    print('number_of_chunks: ', number_of_chunks)
    model = generate_model(data_array, test_input, stride, number_of_data_points, number_of_chunks, number_of_features, num_epochs)
    prediction = naive_prediction_from_model(model, test_input, len(test_input), number_of_features)
    print(' test_input: ', test_input, flush=True)
    print(' prediction: ', prediction, flush=True)

if __name__=="__main__":
    print(' Running ',  flush=True)
    execute()
    print(' Complete ',  flush=True)
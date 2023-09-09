#
# Copyright (c) 2022 John I. Krassikoff
#
# Permission is hereby granted, free of charge, to any person obtaining a copy
# of this software and associated documentation files (the "Software"), to deal
# in the Software without restriction, including without limitation the rights
# to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
# copies of the Software, and to permit persons to whom the Software is
# furnished to do so, subject to the following conditions:
#
# The above copyright notice and this permission notice shall be included in all
# copies or substantial portions of the Software.
#
# THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
# IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
# FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
# AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
# LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
# OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
# SOFTWARE.
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
    tst = list()
    end_idx_location = 0
    last_valid_location = number_of_data_points - 1
    for idx in range(number_of_data_points):
        end_idx_location = idx + number_of_chunks
        if end_idx_location > last_valid_location:
            break
        x1.append(data_array[idx:end_idx_location])
        x2.append(data_array[end_idx_location])
    for idx in range(3072,number_of_data_points):
        tst.append(data_array[idx])
    print(' x1.len(): ', len(x1), flush=True)
    print(' x2.len(): ', len(x2), flush=True)
    return np.array(x1), np.array(x2), np.array(tst)

def construct_model(number_of_chunks, number_of_features):
    model = Sequential()
    model.add(Conv1D(filters=128, kernel_size=3, activation='relu', input_shape=(number_of_chunks, number_of_features)))
    model.add(MaxPooling1D(pool_size=2))
    model.add(Flatten())
    model.add(Dense(64, activation='relu'))
    model.add(Dense(1))
    model.compile(optimizer='Adagrad', loss='mse')
    return model

def fit_model(model, x1, x2, num_epochs):
    model.fit(x1, x2, epochs=num_epochs, verbose=1)
    return model
 
def naive_prediction_from_model(model, test_input, number_of_chunks, number_of_features):
    test_input = test_input.reshape((1, number_of_chunks, number_of_features))
    predicted = model.predict(test_input, verbose=0)
    return predicted

def generate_model(data_array, number_of_data_points, number_of_chunks, number_of_features, num_epochs):
    predicted = 0
    x1, x2, test_input = subdivide_data_array(data_array, number_of_data_points, number_of_chunks)
    print(' x1.size(): ', np.size(x1), flush=True)
    print(' x2.size(): ', np.size(x2), flush=True)
    x1 = x1.reshape((x1.shape[0], x1.shape[1], number_of_features))
    print(' x1[10].size(): ', np.size(x1[10]), flush=True)
    model = construct_model(number_of_chunks, number_of_features)
    model = fit_model(model, x1, x2, num_epochs)
    return model, test_input

def plot_data(data_array):
    fig, axs = plt.subplots(3, figsize=(10,5))
    fig.suptitle('Vertically stacked subplots')
    axs[0].plot(data_array[0,:], color = 'red')
    axs[1].plot(data_array[1,:], color = 'green')
    axs[2].plot(data_array[2,:], color = 'blue')
    plt.show()

def execute(filnam):
    predicted = 0
    tmp_array = np.load(filnam)
    data_array = tmp_array[0,:]
    stride = 4
    num_epochs = 1000
    number_of_features = 1
    number_of_data_points = len(data_array)
    number_of_chunks = (int)(number_of_data_points/stride)
    print('number_of_chunks: ', number_of_chunks)
    model, test_input = generate_model(data_array, number_of_data_points, number_of_chunks, number_of_features, num_epochs)
    prediction = naive_prediction_from_model(model, test_input, len(test_input), number_of_features)
    #plt.figure(1)
    #plt.plot(test_input)
    #plt.show()
    print(' test_input: ', test_input, flush=True)
    print(' max test_input: ', test_input.max(), flush=True)
    print(' min test_input: ', test_input.min(), flush=True)
    print(' prediction: ', prediction, flush=True)

if __name__=="__main__":
    print(' Running ',  flush=True)
    filnam = 'test.npy'
    execute(filnam)
    print(' Complete ',  flush=True)
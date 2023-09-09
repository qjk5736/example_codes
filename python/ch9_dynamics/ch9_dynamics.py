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
#  This is an implementation of the algorithm in
#  The Feynman Lectures on Physics Vol. I Ch. 9
#  Newton's Laws of Mechanics, Section 9_6.
#
def dynamics_update(x, v_t_2, a_t, t, epsilon,first):
    old_x = x
    x = old_x + epsilon*v_t_2
    a_t = -old_x
    if first == True:
        v_t_2 = v_t_2 + (epsilon/2)*a_t
    else:
        v_t_2 = v_t_2 + epsilon*a_t
    return x, v_t_2, a_t

def run_dynamics_update():
    import numpy as np
    epsilon  = 0.0100 # seconds
    max_time = 1.6 # seconds
    num_steps = int(round((max_time/epsilon)+1))
    results = np.zeros((num_steps, 5))
    t = 0.0
    v_t_2 = 0.0
    last_v_t_2 = 0.0
    a_t = 0.0
    x = 1.0
    idx = 0;
    first = True
    while t <= (max_time+epsilon):
        x, v_t_2, a_t = dynamics_update(x, v_t_2, a_t, t, epsilon,first)
        results[idx,0] = x
        results[idx,1] = v_t_2
        results[idx,2] = a_t
        results[idx,3] =  t
        results[idx,4] = epsilon
        first = False
        idx += 1
        t += epsilon
    return results

if __name__=="__main__":
    import matplotlib.pyplot as plt
    results = run_dynamics_update()
    print(results, flush=True)
    fig = plt.figure()
    plot0 = plt.plot(results[:,3], results[:,0], label="Section_9_6_dynamical_eqns")
    plt.title("Solutions of the dynamical equations.")
    plt.ylabel("x(meters)")
    plt.xlabel("time(seconds)")
    plt.grid(True)
    plt.show()

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

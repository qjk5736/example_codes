  module;
  #include <tuple>
  #include <vector>
  #include <array>

  export module newtonian_dynamics;

  export std::tuple<double, double, double> dynamics_update(double x,
    double v_t,
    double a_t,
    double t,
    double epsilon,
    bool first)
  {
    double old_x = x;
    x = old_x + epsilon * v_t;
    a_t = -old_x;
    if (first == true)
      v_t = v_t + (epsilon / 2) * a_t;
    else
      v_t = v_t + epsilon * a_t;
    return { x, v_t, a_t };
  }

  export void run_dynamics_update(std::vector < std::array<double, 5> >& results)
  {
    double epsilon = 0.0100;  // seconds
    double max_time = 1.6;    // seconds
    int num_steps = int(round((max_time / epsilon) + 1));
    results.reserve(num_steps);
    std::array<double, 5> state = { 0.0,0.0,0.0,0.0,0.0 };
    double t = 0.0;         // seconds
    double v_t = 0.0;       // m/s
    double last_v_t = 0.0;  // m/s
    double a_t = 0.0;       // m/s^2
    double x = 1.0;         // m
    size_t idx = 0;
    bool first = true;
    while (t <= (max_time + epsilon))
    {
      std::tie(x, v_t, a_t) = dynamics_update(x, v_t, a_t, t, epsilon, first);
      state[0] = x;
      state[1] = v_t;
      state[2] = a_t;
      state[3] = t;
      state[4] = epsilon;
      results.push_back(state);
      first = false;
      idx += 1;
      t += epsilon;
    }
  }

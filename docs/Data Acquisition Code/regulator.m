clc; clear all; close all;

%% Motor ID1
Hf = tf(14.96, [1, 1.141]);
Hf_discret = c2d(Hf, 0.05, 'zoh');
Hf_discret.Variable = "z^-1";

% Use pidtune to get PI controller
[c_tuned, info] = pidtune(Hf_discret, 'PI', 13.33) % 13.33 rad/s desired bandwidth

% Discretize controller
Hc_discret = minreal(tf(c_tuned));
Hc_discret.Variable = 'z^-1'

figure;
step(feedback(series(Hf_discret, Hc_discret), 1), 1);
title("Step Response for Motor ID1");

%% Motor ID2
Hf = tf(15.08, [1, 1.161]);
Hf_discret = c2d(Hf, 0.05, 'zoh');
Hf_discret.Variable = "z^-1";

% Use pidtune to get PI controller
[c_tuned, info] = pidtune(Hf_discret, 'PI', 13.33) % 13.55 rad/s desired bandwidth

% Discretize controller
Hc_discret = tf(c_tuned);
Hc_discret.Variable = 'z^-1'

figure;
step(feedback(series(Hc_discret, Hf_discret), 1));
title("Step Response for Motor ID2");

%% Motor ID3
Hf = tf(15.03, [1, 1.14])
Hf_discret = c2d(Hf, 0.05, 'zoh');
Hf_discret.Variable = "z^-1"

% Use pidtune to get PI controller
[c_tuned, info] = pidtune(Hf_discret, 'PI', 13.33) % 13.55 rad/s desired bandwidth

% Discretize controller
Hc_discret = tf(c_tuned);
Hc_discret.Variable = 'z^-1'

figure;
step(feedback(series(Hc_discret, Hf_discret), 1));
title("Step Response for Motor ID3");
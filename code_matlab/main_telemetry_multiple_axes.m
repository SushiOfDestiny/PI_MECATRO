%Duration of the experiment
Tmax = 10;

%Serial port name
port_name = "COM7";

%CONTROL_LOOP_PERIOD constant in the Arduino sketch
dt_arduino = 5e-3;

%Target folder
target_folder = './';

[log_time, data_values, line_idx] = ...
    get_data_from_robot(port_name, Tmax, target_folder);

%Display logged variable names
disp(data_values.keys)  

% Plot logged variables
% figure; 

% Create multiple Axes
nb_axes = 3;

tiledlayout(nb_axes,1);

ax1 = nexttile;
ax2 = nexttile;
ax3 = nexttile;

axes = [ax1 ax2 ax3];

hold(axes, 'on');

legend_labels = data_values.keys;

for i = 1:nb_axes
    % Plot on axe i
    d = legend_labels{i};
    v = data_values(d);
    plot(axes(i), log_time, v, 'DisplayName', d);
    legend(axes(i),d);
end

hold(axes, 'off');

grid on;

GAINS = [1.5,   % MAHONY_TAU
         8.0,   % KP
         0.05,  % KD
         0.05,  % KP_PHI
         0.015];% KD_PHI



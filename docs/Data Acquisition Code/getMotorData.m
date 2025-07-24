% COM port & duration
comPort = "COM8";
baudRate = 115200;
duration = 25; 

% Create serialport object
s = serialport(comPort, baudRate);
flush(s); % Clear old data

% Prepare for logging
input = [];
time = [];
rpm = [];
startTime = datetime('now');

disp("Logging...");

while seconds(datetime('now') - startTime) < duration
    if s.NumBytesAvailable > 0
        line = readline(s);
        data = sscanf(line, '%f,%f,%f');
        if numel(data) == 3
            input(end+1) = data(1);
            time(end+1) = data(2) / 1000; % ms to seconds
            rpm(end+1) = data(3);
        end
    end
end

% Clean up
clear s
disp("Logging complete.");

% Save to CSV
T = table(input', time', rpm', 'VariableNames', {'Input', 'Time_s', 'Speed_RPM'});
writetable(T, 'motor_data.csv');
%%
T = readtable("motor_data_ID3.csv");
% Plot
figure; 
subplot(211);
plot(T.Time_s, T.Speed_RPM); grid on; hold on;
xlabel('Time (s)');
ylabel('Speed (RPM)');
title('Step Response');

subplot(212);
plot(T.Time_s, T.Input); grid on;
xlabel('Time (s)');
ylabel('Input (PWM)');
title('Input');
sgtitle("Motor ID3");
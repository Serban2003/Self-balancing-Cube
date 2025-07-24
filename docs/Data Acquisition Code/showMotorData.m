clc; close all; clear all;

dataTable_motorID1 = readtable("motor_data_ID1.csv");
dataTable_motorID2 = readtable("motor_data_ID2.csv");
dataTable_motorID3 = readtable("motor_data_ID3.csv");

inputArray_motorID1 = dataTable_motorID1.Input(5:260);
valueArray_motorID1 = dataTable_motorID1.Speed_RPM(5:260);

inputArray_motorID2 = dataTable_motorID2.Input(27:282);
valueArray_motorID2 = dataTable_motorID2.Speed_RPM(27:282);

inputArray_motorID3 = dataTable_motorID3.Input(38:293);
valueArray_motorID3 = dataTable_motorID3.Speed_RPM(38:293);

inputArray_motorID1_id = inputArray_motorID1(145:end);
valueArray_motorID1_id = valueArray_motorID1(145:end);

inputArray_motorID2_id = inputArray_motorID2(141:end);
valueArray_motorID2_id = valueArray_motorID2(141:end);

inputArray_motorID3_id = inputArray_motorID3(141:end);
valueArray_motorID3_id = valueArray_motorID3(141:end);

iddata_motorID1_id = iddata(valueArray_motorID1_id, inputArray_motorID1_id, 0.05);
iddata_motorID2_id = iddata(valueArray_motorID2_id, inputArray_motorID2_id, 0.05);
iddata_motorID3_id = iddata(valueArray_motorID3_id, inputArray_motorID3_id, 0.05);

TF_motorID1 = calculateTF(inputArray_motorID1_id, valueArray_motorID1_id, 2100, 1);
TF_motorID2 = calculateTF(inputArray_motorID2_id, valueArray_motorID2_id, 1782, 2);
TF_motorID3 = calculateTF(inputArray_motorID3_id, valueArray_motorID3_id, 1806, 3);

function TF = calculateTF(input_data, output_data, initial_cond, motorID)
    iddata_motor = iddata(output_data, input_data, 0.05);
    arx_model = arx(iddata_motor, [1 1 1]);
    [num, den] = tfdata(arx_model, 'v');
    [A, B, C, D] = tf2ss(num, den);
    y_calc = dlsim(A', C', B', D', input_data, initial_cond);
    TF = minreal(tf(arx_model))

    figure;
    plot(1:length(y_calc), [y_calc, output_data]);
    grid on;
    legend("Y\_calc", "Y\_real");
    title("MotorID" + motorID);
    xlabel("Sample Time");
    ylabel("RPM");
    nmse = norm(output_data - y_calc) / norm(output_data - mean(output_data)) * 100
end


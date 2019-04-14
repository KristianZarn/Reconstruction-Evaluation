dataset = 'statue';
gen_filename = strcat('../dataset/', dataset, '_gen/', 'ctol_', dataset, '_gen.txt');
nbv_filename = strcat('../dataset/', dataset, '_nbv/', 'ctol_', dataset, '_nbv.txt');

% Read data
gen_data = dlmread(gen_filename);
nbv_data = dlmread(nbv_filename);

% Plot
figure(1);
hold on;
plot(gen_data(:, 1), gen_data(:, 2), 'LineWidth', 2);
plot(nbv_data(:, 1), nbv_data(:, 2), 'LineWidth', 2);
hold off;
title('Izbira mejne vrednosti');
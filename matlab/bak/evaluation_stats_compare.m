dataset = 'hydrant';
gen_filename = strcat('../dataset/', dataset, '_gen/', 'eval_', dataset, '_gen.txt');
nbv_filename = strcat('../dataset/', dataset, '_nbv/', 'eval_', dataset, '_nbv.txt');

% Read data
gen_data = dlmread(gen_filename, ',', 2, 1);
nbv_data = dlmread(nbv_filename, ',', 2, 1);

% Plot
figure(1); clf;

% rec_to_ref_mean
subplot(2, 2, 1);
hold on;
plot(gen_data(:, 2), 'LineWidth', 2);
plot(nbv_data(:, 2), 'LineWidth', 2);
hold off;
title('Rec to ref mean');

% accuracy
subplot(2, 2, 2);
hold on;
plot(gen_data(:, 3), 'LineWidth', 2);
plot(nbv_data(:, 3), 'LineWidth', 2);
hold off;
title('Natančnost');

% ref_to_rec_mean
subplot(2, 2, 3);
hold on;
plot(gen_data(:, 4), 'LineWidth', 2);
plot(nbv_data(:, 4), 'LineWidth', 2);
hold off;
title('Ref to rec mean');

% completeness
subplot(2, 2, 4);
hold on;
plot(gen_data(:, 5), 'LineWidth', 2);
plot(nbv_data(:, 5), 'LineWidth', 2);
hold off;
title('Pokritost');

% Plot
figure(2); clf;

% accuracy
subplot(1, 2, 1);
hold on;
plot(gen_data(:, 3), 'LineWidth', 2);
plot(nbv_data(:, 3), 'LineWidth', 2);
hold off;
xlabel('Število slik');
ylabel('Natančnost')

% completeness
subplot(1, 2, 2);
hold on;
plot(gen_data(:, 5), 'LineWidth', 2);
plot(nbv_data(:, 5), 'LineWidth', 2);
hold off;
xlabel('Število slik');
ylabel('Pokritost')

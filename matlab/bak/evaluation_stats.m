evaluation_filename = 'Data/eval_hydrant_nbv.txt';
data = dlmread(evaluation_filename, ',', 2, 1);

rec_to_ref_mean = data(:, 2);
accuracy = data(:, 3);

ref_to_rec_mean = data(:, 4);
completeness = data(:, 5);

% Plot
figure(1);
subplot(2, 2, 1);
plot(rec_to_ref_mean, 'LineWidth', 2);
title('Rec to ref mean');

subplot(2, 2, 2);
plot(accuracy, 'LineWidth', 2);
title('Accuracy');

subplot(2, 2, 3);
plot(ref_to_rec_mean, 'LineWidth', 2);
title('Ref to rec mean');

subplot(2, 2, 4);
plot(completeness, 'LineWidth', 2);
title('Completeness');
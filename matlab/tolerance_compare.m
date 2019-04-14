dataset_name = 'krava';
root_folder = strcat('../dataset/', dataset_name, '/');
labels = {'gen_20', 'gen_25', 'gen_30', 'nbv'};
legend_labels = {'20', '25', '30', 'NBV'};
colors = [
    0, 0, 0;
    0, 0, 1;
    0.12, 0.56, 1;
    1, 0, 0;
    ];

% Prepare plot
figure(1); clf;

for i = 1:length(labels)
    label = labels{i};
    ctol_filename = strcat(root_folder, 'ctol_', dataset_name, '_', label, '.txt');

    % Read data
    data = dlmread(ctol_filename);
    
    % Plot data
    hold on;
    plot(data(:, 1), data(:, 2), 'Color', colors(i, :), 'LineWidth', 2);
    hold off;
    title('Izbira mejne vrednosti');
end

% Add legend to plot
legend(legend_labels, 'Location','southeast');
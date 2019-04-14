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
    eval_filename = strcat(root_folder, 'eval_', dataset_name, '_', label, '.txt');
    
    % Read data
    data = dlmread(eval_filename, ',', 2, 1);
    x_axis = data(:, 1);
    
    % rec_to_ref_mean
    subplot(2, 2, 1);
    hold on;
    plot(x_axis, data(:, 3), 'Color', colors(i, :), 'LineWidth', 2);
    hold off;
    xlim([min(x_axis) max(x_axis)]);
    title('Razdalja R do G');

    % accuracy
    subplot(2, 2, 3);
    hold on;
    plot(x_axis, data(:, 4), 'Color', colors(i, :), 'LineWidth', 2);
    hold off;
    xlim([min(x_axis) max(x_axis)]);
    title('Nenatančnost');
    
    % ref_to_rec_mean
    subplot(2, 2, 2);
    hold on;
    plot(x_axis, data(:, 5), 'Color', colors(i, :), 'LineWidth', 2);
    hold off;
    xlim([min(x_axis) max(x_axis)]);
    title('Razdalja G do R');

    % completeness
    subplot(2, 2, 4);
    hold on;
    plot(x_axis, data(:, 6), 'Color', colors(i, :), 'LineWidth', 2);
    hold off;
    xlim([min(x_axis) max(x_axis)]);
    title('Pokritost');
end

% Handle missing data
for i = 1:length(labels)
    label = labels{i};
    eval_filename = strcat(root_folder, 'eval_', dataset_name, '_', label, '.txt');
    
    % Read data
    data = dlmread(eval_filename, ',', 2, 1);
    x_axis = data(:, 1);
    intervals = missing_intervals(x_axis);
    
    for j = 1:size(intervals, 1)
        interval = intervals(j, :);
        
        % rec_to_ref_mean
        subplot(2, 2, 1);
        hold on;
        plot(x_axis(interval), data(interval, 3), 'Color', 'white', 'LineWidth', 2);
        plot(x_axis(interval), data(interval, 3), ':', 'Color', colors(i, :), 'LineWidth', 1.5);
        hold off;
        
        % accuracy
        subplot(2, 2, 3);
        hold on;
        plot(x_axis(interval), data(interval, 4), 'Color', 'white', 'LineWidth', 2);
        plot(x_axis(interval), data(interval, 4), ':', 'Color', colors(i, :), 'LineWidth', 1.5);
        hold off;

        % ref_to_rec_mean
        subplot(2, 2, 2);
        hold on;
        plot(x_axis(interval), data(interval, 5), 'Color', 'white', 'LineWidth', 2);
        plot(x_axis(interval), data(interval, 5), ':', 'Color', colors(i, :), 'LineWidth', 1.5);
        hold off;

        % completeness
        subplot(2, 2, 4);
        hold on;
        plot(x_axis(interval), data(interval, 6), 'Color', 'white', 'LineWidth', 2);
        plot(x_axis(interval), data(interval, 6), ':', 'Color', colors(i, :), 'LineWidth', 1.5);
        hold off;
    end
end

% Add legend to plots
subplot(2, 2, 3);
legend(legend_labels, 'Location','northeast');

subplot(2, 2, 4);
legend(legend_labels, 'Location','southeast');


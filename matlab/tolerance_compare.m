dataset_name = 'frank';
root_folder = strcat('../dataset/', dataset_name, '/');
% labels = {'gen_20', 'gen_40', 'gen_60', 'nbv'};
% legend_labels = {'20', '40', '60', 'NBV'};
labels = {'gen_20', 'gen_40', 'gen_60'};
legend_labels = {'20', '40', '60'};
% colors = [
%     0, 0, 0;
%     0, 0, 1;
%     0.12, 0.56, 1;
%     1, 0, 0;
% ];
c1 = [0, 0, 0] / 255;
c2 = [130, 130, 130] / 255;
c3 = [180, 180, 180] / 255;
c4 = [255, 0, 0] / 255;
colors = [c1; c2; c3; c4];

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
legend(legend_labels, 'Location', 'southeast');
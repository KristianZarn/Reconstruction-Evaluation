
dataset = 'quality_statue';
data_folder = strcat('../dataset/', dataset, '/gen_20/');

pc_num = 14;

% PPA, GSD
correlation = zeros(1, 2);

figure(2); clf;
plot_titles = {'Mera PPA', 'Mera GSD'};
fprintf('\tShowing data for point cloud number: %03d\n', pc_num);

pc_filenames = {
sprintf('%s%03d_ppa.dat', data_folder, pc_num)
sprintf('%s%03d_gsd.dat', data_folder, pc_num)};

num_plots = length(pc_filenames);
for j = 1:num_plots
    pc_filename = pc_filenames{j};
    rec_dat = dlmread(pc_filename);

    % Quality per point
    quality = rec_dat(:, 4);

    % Clamp quality values (for gsd)
    if (j == 2)
        max_q = prctile(quality, 90);
        mask = (quality > max_q) | (quality == 0.0);
        quality(mask) = max_q;
    end

    % Accuracy
    rec_to_ref = rec_dat(:, 5);

    % Plot accuracy quality correlation
    subplot(num_plots, 1, j);
    hold on;
    scatter(quality, rec_to_ref, 5, 'filled', 'MarkerFaceColor', 'black');
    title(plot_titles{j}, 'FontWeight', 'Normal');
    xlabel('Ocena kvalitete');
    ylabel('Razdalja R do G');

    % Compute correlation coefficient
    tmp = corrcoef(quality, rec_to_ref);
    correlation(j) = tmp(2, 1);
    
    % Fit line through data
    c = polyfit(quality, rec_to_ref, 1);
    trend = polyval(c, quality);
    
    plot(quality, trend, 'r', 'LineWidth', 2);
    hold off;
end

disp(correlation)

dataset = 'statue_gen';
data_folder = strcat('../dataset/', dataset, '/raw_export/');
min_pc_num = 3;
max_pc_num = 71;

% PPA, GSD, MPA
correlation = zeros(length(min_pc_num:max_pc_num), 3);

figure(1); clf;
plot_titles = {'Mera PPA', 'Mera GSD', 'Mera MPA'};
for i = min_pc_num:max_pc_num
    fprintf('\tShowing data for point cloud number: %03d\n', i);
    
    pc_filenames = {
        sprintf('%s%03d_ppa.dat', data_folder, i)
        sprintf('%s%03d_gsd.dat', data_folder, i)};
%         sprintf('%s%03d_mpa.dat', data_folder, i)};
    
    num_plots = length(pc_filenames);
    for j = 1:num_plots
        pc_filename = pc_filenames{j};
        rec_dat = dlmread(pc_filename);

        % Quality per point
        quality = rec_dat(:, 4);

        % Clamp quality values (useful for gsd)
        if (j == 2)
            max_q = prctile(quality, 90);
            mask = (quality > max_q) | (quality == 0.0);
            quality(mask) = max_q;
        end

        % Accuracy
        rec_to_ref = rec_dat(:, 5);

        % Plot accuracy quality correlation
        subplot(num_plots, 1, j);
        scatter(quality, rec_to_ref, 10, 'filled');
        title(plot_titles{j});
        xlabel('Ocena kvalitete');
        ylabel('Razdalja do reference');
        
        tmp = corrcoef(quality, rec_to_ref);
        correlation(i - min_pc_num + 1, j) = tmp(2, 1);
    end
    
    pause;
end

output_filename = strcat('../dataset/', dataset, '/corr_', dataset, '.txt');
dlmwrite(output_filename, correlation, 'Delimiter', '\t')

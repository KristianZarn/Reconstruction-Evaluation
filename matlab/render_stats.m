dataset_name = 'storz';

root_folder = strcat('../dataset/', dataset_name, '/');
stats_filename = strcat(root_folder, 'render_view_picks.txt');

view_picks = dlmread(stats_filename);
view_picks = view_picks(view_picks >= 0);

mean_pick = mean(view_picks);
median_pick = median(view_picks);

disp(mean_pick);
disp(median_pick);

ref_filename = 'Data/ref_pc.dat';
ref_dat = dlmread(ref_filename);
ref_pc = pointCloud(ref_dat);

rec_filenames = {
    'Data/rec_pc_with_ppa.dat'
    'Data/rec_pc_with_gsd.dat'
    'Data/rec_pc_with_mpa.dat'};

figure(1); clf;
for i = 1:length(rec_filenames)
    rec_filename = rec_filenames{i};
    rec_dat = dlmread(rec_filename);

    % Quality per point
    quality = rec_dat(:, 4);
    
    % Clamp quality values (useful for gsd)
    if (i == 2)
        max_q = prctile(quality, 90);
        mask = (quality > max_q) | (quality == 0.0);
        quality(mask) = max_q;
    end

    % Accuracy
    rec_to_ref = rec_dat(:, 5);

    % Plot accuracy quality correlation
    subplot(3, 1, i);
    scatter(quality, rec_to_ref, 'filled');
    corrcoef(quality, rec_to_ref)
end


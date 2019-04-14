
ref_filename = 'Data/ref_pc.dat';
ref_dat = dlmread(ref_filename);
ref_pc = pointCloud(ref_dat);

rec_filename = 'Data/rec_pc.dat';
rec_dat = dlmread(rec_filename);
rec_pc = pointCloud(rec_dat);

% Compute accuracy
rec_to_ref = zeros(rec_pc.Count, 1);
for i = 1:rec_pc.Count
    point = rec_dat(i, :);
    [idx, dist] = findNearestNeighbors(ref_pc, point, 1);
    rec_to_ref(i) = dist;
end
rec_to_ref_mean = mean(rec_to_ref);
rec_to_ref_median = median(rec_to_ref);

accuracy_percentage = 90;
accuracy = prctile(rec_to_ref, accuracy_percentage);

% Compute completeness
ref_to_rec = zeros(ref_pc.Count, 1);
for i = 1:ref_pc.Count
    point = ref_dat(i, :);
    [idx, dist] = findNearestNeighbors(rec_pc, point, 1);
    ref_to_rec(i) = dist;
end
ref_to_rec_mean = mean(ref_to_rec);
ref_to_rec_median = median(ref_to_rec);

completeness_tolerance = 2 * accuracy;
completeness = sum(ref_to_rec < completeness_tolerance) / ref_pc.Count;

% Output results
rec_to_ref_mean
rec_to_ref_median
accuracy
ref_to_rec_mean
ref_to_rec_median
completeness

% Plot
figure(1); clf;
pcshow(ref_dat, 'blue');
hold on
pcshow(rec_dat, 'red');
hold off

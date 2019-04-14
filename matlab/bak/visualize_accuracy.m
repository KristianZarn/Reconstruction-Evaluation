
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

% Plot
colormap jet;
figure(1); clf;
pcshow(rec_dat, rec_to_ref);
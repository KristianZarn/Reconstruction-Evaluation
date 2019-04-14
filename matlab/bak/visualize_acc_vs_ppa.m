
ref_filename = 'Data/ref_pc.dat';
ref_dat = dlmread(ref_filename);
ref_pc = pointCloud(ref_dat);

rec_filename = 'Data/rec_pc_with_ppa.dat';
rec_dat = dlmread(rec_filename);
rec_pc = pointCloud(rec_dat(:, 1:3));

% Quality per point
quality = rec_dat(:, 4);

% Compute accuracy
rec_to_ref = zeros(rec_pc.Count, 1);
for i = 1:rec_pc.Count
    point = rec_dat(i, 1:3);
    [idx, dist] = findNearestNeighbors(ref_pc, point, 1);
    rec_to_ref(i) = dist;
end

% Plot point clouds
colormap('jet');
figure(1); clf;

% Show accuracy
% pcshow(rec_dat(:, 1:3), rec_to_ref);

% Show quality
pcshow(rec_dat(:, 1:3), quality);

% Check alignment
% pcshow(ref_dat, 'blue');
% hold on
% pcshow(rec_dat(:, 1:3), 'red');
% hold off

% Plot accuracy quality correlation
figure(2); clf;
scatter(quality, rec_to_ref, 'filled');

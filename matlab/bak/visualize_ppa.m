filename = 'Data/rec_pc_with_ppa.dat';
data = dlmread(filename);

points = data(:, 1:3);
ppa = data(:, 4);

% pc = pointCloud(points, 'Intensity', ppa);

% Plot
colormap jet;
figure(1); clf;
pcshow(points, ppa);
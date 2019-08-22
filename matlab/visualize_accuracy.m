% Read data
% filename = '../dataset/_other/006_ppa.dat';
% filename = '../dataset/_other/014_ppa.dat';
filename = '../dataset/_other/ex/007_pc.dat';

% data = dlmread(filename);
data = dlmread(filename, ' ', 1, 0);

points = data(:, 1:3);
accuracy = data(:, 5);

% Normalize accuracy
% Log and crop
% accuracy = -log(accuracy);
max_acc = prctile(accuracy, 90);
mask = (accuracy > max_acc);
accuracy(mask) = max_acc;

% Flip
accuracy = -accuracy;

% Transform data to per face accuracy
face_ids = data(:, 4);
face_accuracy = zeros(7681, 1);
face_normalization = zeros(7681, 1);
for i = 1:length(face_ids)
    face_id = face_ids(i) + 1;
    face_accuracy(face_id) = face_accuracy(face_id) + accuracy(i);
    face_normalization(face_id) = face_normalization(face_id) + 1;
end

face_accuracy = face_accuracy ./ face_normalization;
% filename_out = '../dataset/_other/ex/007.acc_crop';
% dlmwrite(filename_out, face_accuracy);

% Plot
% pc = pointCloud(points, 'Intensity', accuracy);
colormap jet;
figure(1); clf;
pcshow(points, accuracy);

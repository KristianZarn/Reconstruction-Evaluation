% Read data
I = dlmread('../resources/render_5.dat');

% Show image
colormap jet;
imagesc(I);
% set(gca, 'YDir', 'normal');
set(gca, 'XDir', 'reverse');
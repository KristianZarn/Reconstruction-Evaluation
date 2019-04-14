dataset = 'hydrant_gen';
input_filename = strcat('../dataset/', dataset, '/corr_', dataset, '.txt');
correlation = dlmread(input_filename);

% Plot 
figure(1); clf;
hold on;
subplot(3, 1, 1);
plot(correlation(:,1));
subplot(3, 1, 2);
plot(correlation(:,2));
subplot(3, 1, 3);
plot(correlation(:,3));
hold off;

% Output stats
mean(correlation(:,1))
mean(correlation(:,2))
mean(correlation(:,3))
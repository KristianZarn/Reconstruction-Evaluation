dataset_name = 'krava';
root_folder = strcat('../dataset/', dataset_name, '/');

ref_pc_filename = strcat(root_folder, 'ref_pc.dat');
data = dlmread(ref_pc_filename);

[coeff, score, latent] = pca(data);
# Evaluation of reconstructed 3D models

This code can be used to compare 3D models and compute quality measures such as accuracy and completeness.

The code was used for evaluation of [this](https://github.com/KristianZarn/Reconstruction) reconstruction software.

The models can be read from ply format as a mesh or point cloud. The meshes can be evenly resampled into point coulds. 
KDTree is used for fast computation of distances between points and consequentially fast computation of accuracy and completeness.


## Usage

- For basic example see `main_single_eval`

- To compare multiple models to the same reference see `main_batch_eval`

- Completeness measure requires additional threshold parameter. `main_pca` and `main_find_tolerance` can be used to find suitable threshold.



#include "EvaluationStats.h"

#include <iostream>
#include <fstream>

EvaluationStats::EvaluationStats(std::string name, int samples) :
        ref_name(std::move(name)), ref_samples(samples) {}

int EvaluationStats::Size() {
    return static_cast<int>(mesh_names.size());
}

void EvaluationStats::AddMeshComparison(const std::string& mesh_name,
                                        int samples,
                                        double rec_to_ref_mean,
                                        double accuracy,
                                        double ref_to_rec_mean,
                                        double completeness) {
    mesh_names.push_back(mesh_name);
    mesh_samples.push_back(samples);
    rec_to_ref_means.push_back(rec_to_ref_mean);
    accuracies.push_back(accuracy);
    ref_to_rec_means.push_back(ref_to_rec_mean);
    completenesses.push_back(completeness);
}

void EvaluationStats::WriteStatsToFile(const std::string& filename) {
    std::ofstream outfile(filename);
    if (!outfile) {
        std::cout << "RenderStats: cannot open file " << filename << " for writing." << std::endl;
        return;
    }

    outfile << "Reference: " << ref_name << "; samples: " << ref_samples << "\n";
    outfile << "Names,\t"
            << "Samples,\t"
            << "RecToRef,\t"
            << "Accuracy,\t"
            << "RefToRec,\t"
            << "Completeness\n";

    auto num_comparisons = mesh_names.size();
    for (int i = 0; i < num_comparisons; i++) {
        outfile << mesh_names[i] << ",\t"
                << mesh_samples[i] << ",\t"
                << rec_to_ref_means[i] << ",\t"
                << accuracies[i] << ",\t"
                << ref_to_rec_means[i] << ",\t"
                << completenesses[i] << "\n";
    }
}

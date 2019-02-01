#include "EvaluationStats.h"

#include <iostream>
#include <fstream>

EvaluationStats::EvaluationStats(std::string name,
                                 int samples,
                                 double accuracy_percentage,
                                 double completeness_tolerance) :
        ref_name_(std::move(name)),
        ref_samples_(samples),
        accuracy_percentage_(accuracy_percentage),
        completeness_tolerance_(completeness_tolerance) {}

int EvaluationStats::Size() {
    return static_cast<int>(mesh_names_.size());
}

void EvaluationStats::AddMeshComparison(const std::string& mesh_name,
                                        int samples,
                                        double rec_to_ref_mean,
                                        double accuracy,
                                        double ref_to_rec_mean,
                                        double completeness) {
    mesh_names_.push_back(mesh_name);
    mesh_samples_.push_back(samples);
    rec_to_ref_means_.push_back(rec_to_ref_mean);
    accuracies_.push_back(accuracy);
    ref_to_rec_means_.push_back(ref_to_rec_mean);
    completenesses_.push_back(completeness);
}

void EvaluationStats::WriteStatsToFile(const std::string& filename) {
    std::ofstream outfile(filename);
    if (!outfile) {
        std::cout << "RenderStats: cannot open file " << filename << " for writing." << std::endl;
        return;
    }

    outfile << "Reference: " << ref_name_
            << "; Samples: " << ref_samples_
            << "; Accuracy percent: " << accuracy_percentage_
            << "; Completeness tolerance: " << completeness_tolerance_ << "\n";

    outfile << "Names,\t"
            << "Samples,\t"
            << "RecToRef,\t"
            << "Accuracy,\t"
            << "RefToRec,\t"
            << "Completeness\n";

    auto num_comparisons = mesh_names_.size();
    for (int i = 0; i < num_comparisons; i++) {
        outfile << mesh_names_[i] << ",\t"
                << mesh_samples_[i] << ",\t"
                << rec_to_ref_means_[i] << ",\t"
                << accuracies_[i] << ",\t"
                << ref_to_rec_means_[i] << ",\t"
                << completenesses_[i] << "\n";
    }
}

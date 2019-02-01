#ifndef SANDBOX_EVALUATION_EVALUATIONSTATS_H
#define SANDBOX_EVALUATION_EVALUATIONSTATS_H

#include <vector>
#include <string>

class EvaluationStats {
public:
    EvaluationStats(std::string name,
                    int samples,
                    double accuracy_percentage,
                    double completeness_tolerance);

    // Utility functions
    int Size();

    // Add new mesh comparison
    void AddMeshComparison(const std::string& mesh_name,
                           int samples,
                           double rec_to_ref_mean,
                           double accuracy,
                           double ref_to_rec_mean,
                           double completeness);

    // Write to file
    void WriteStatsToFile(const std::string& filename);

private:
    std::string ref_name_;
    int ref_samples_;
    double accuracy_percentage_;
    double completeness_tolerance_;

    std::vector<std::string> mesh_names_;
    std::vector<int> mesh_samples_;

    std::vector<double> rec_to_ref_means_;
    std::vector<double> accuracies_;

    std::vector<double> ref_to_rec_means_;
    std::vector<double> completenesses_;
};


#endif //SANDBOX_EVALUATION_EVALUATIONSTATS_H

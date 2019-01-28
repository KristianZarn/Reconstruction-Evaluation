#ifndef SANDBOX_EVALUATION_EVALUATIONSTATS_H
#define SANDBOX_EVALUATION_EVALUATIONSTATS_H

#include <vector>
#include <string>

class EvaluationStats {
public:
    EvaluationStats(std::string name, int samples);

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
    std::string ref_name;
    int ref_samples;

    std::vector<std::string> mesh_names;
    std::vector<int> mesh_samples;

    std::vector<double> rec_to_ref_means;
    std::vector<double> accuracies;

    std::vector<double> ref_to_rec_means;
    std::vector<double> completenesses;
};


#endif //SANDBOX_EVALUATION_EVALUATIONSTATS_H

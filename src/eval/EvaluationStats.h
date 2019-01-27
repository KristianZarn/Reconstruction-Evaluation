#ifndef SANDBOX_EVALUATION_EVALUATIONSTATS_H
#define SANDBOX_EVALUATION_EVALUATIONSTATS_H

#include <vector>
#include <string>

class EvaluationStats {
public:
    int Size();

    // Add new mesh comparison
    void AddMeshComparison(const std::string& mesh_name,
                           double rec_to_ref_mean,
                           double accuracy,
                           double ref_to_rec_mean,
                           double completeness);

    // Write to file
    void WriteStatsToFile(const std::string& filename);

private:
    std::vector<std::string> mesh_names;

    std::vector<double> rec_to_ref_means;
    std::vector<double> accuracies;

    std::vector<double> ref_to_rec_means;
    std::vector<double> completenesses;
};


#endif //SANDBOX_EVALUATION_EVALUATIONSTATS_H

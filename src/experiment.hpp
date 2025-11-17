#pragma once

#include <vector>
#include <string>

struct TrialResult {
    int flips_per_trial;
    int heads_count;
};

struct ExperimentResult {
    int n;
    int m;
    double p;
    std::vector<TrialResult> trials;
    
    double mean_heads() const;
    double std_deviation() const;
};

class Experiment {
public:
    ExperimentResult run_trials(int n, int m, double p);
    
    static std::string format_results_table(const std::vector<ExperimentResult>& results);
    static void export_csv(const std::vector<ExperimentResult>& results, const std::string& filename);
};

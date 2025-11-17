#include <iostream>
#include <vector>
#include "src/experiment.hpp"

int main() {
    std::vector<int> n_values = {100, 500, 1000, 5000, 10000};
    std::vector<double> p_values = {0.3, 0.5, 0.7};
    int m = 10;
    
    Experiment experiment;
    std::vector<ExperimentResult> all_results;
    
    for (int n : n_values) {
        for (double p : p_values) {
            std::cout << "Running trial: n=" << n << ", m=" << m << ", p=" << p << "..." << std::endl;
            ExperimentResult result = experiment.run_trials(n, m, p);
            all_results.push_back(result);
        }
    }
    
    std::cout << Experiment::format_results_table(all_results);
    
    Experiment::export_csv(all_results, "experiment_results.csv");
    
    return 0;
}

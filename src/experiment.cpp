#include "experiment.hpp"
#include "coin.hpp"
#include <numeric>
#include <cmath>
#include <sstream>
#include <iomanip>
#include <fstream>
#include <iostream>

double ExperimentResult::mean_heads() const {
    if (trials.empty()) return 0.0;
    
    double sum = std::accumulate(trials.begin(), trials.end(), 0.0,
        [](double acc, const TrialResult& trial) {
            return acc + trial.heads_count;
        });
    
    return sum / trials.size();
}

double ExperimentResult::std_deviation() const {
    if (trials.empty()) return 0.0;
    
    double mean = mean_heads();
    double variance = std::accumulate(trials.begin(), trials.end(), 0.0,
        [mean](double acc, const TrialResult& trial) {
            double diff = trial.heads_count - mean;
            return acc + diff * diff;
        });
    
    return std::sqrt(variance / trials.size());
}

ExperimentResult Experiment::run_trials(int n, int m, double p) {
    ExperimentResult result;
    result.n = n;
    result.m = m;
    result.p = p;
    
    Coin coin(p);
    
    for (int trial = 0; trial < m; ++trial) {
        TrialResult trial_result;
        trial_result.flips_per_trial = n;
        trial_result.heads_count = 0;
        
        for (int flip = 0; flip < n; ++flip) {
            if (coin.flip()) {
                ++trial_result.heads_count;
            }
        }
        
        result.trials.push_back(trial_result);
    }
    
    return result;
}

std::string Experiment::format_results_table(const std::vector<ExperimentResult>& results) {
    std::ostringstream oss;
    
    oss << "\n" << std::string(80, '=') << "\n";
    oss << "BIASED COIN FLIP EXPERIMENT RESULTS\n";
    oss << std::string(80, '=') << "\n\n";
    
    oss << std::left << std::setw(10) << "n"
        << std::setw(10) << "m"
        << std::setw(10) << "p"
        << std::setw(15) << "Mean Heads"
        << std::setw(15) << "Std Dev"
        << std::setw(15) << "Expected"
        << std::setw(15) << "Error %"
        << "\n";
    oss << std::string(80, '-') << "\n";
    
    for (const auto& result : results) {
        double expected = result.n * result.p;
        double mean = result.mean_heads();
        double error_percent = std::abs((mean - expected) / expected) * 100.0;
        
        oss << std::left << std::setw(10) << result.n
            << std::setw(10) << result.m
            << std::setw(10) << std::fixed << std::setprecision(2) << result.p
            << std::setw(15) << std::fixed << std::setprecision(2) << mean
            << std::setw(15) << std::fixed << std::setprecision(2) << result.std_deviation()
            << std::setw(15) << std::fixed << std::setprecision(2) << expected
            << std::setw(15) << std::fixed << std::setprecision(2) << error_percent
            << "\n";
    }
    
    oss << std::string(80, '=') << "\n";
    
    return oss.str();
}

void Experiment::export_csv(const std::vector<ExperimentResult>& results, const std::string& filename) {
    std::ofstream file(filename);
    
    if (!file.is_open()) {
        std::cerr << "Error: Could not open file " << filename << " for writing\n";
        return;
    }
    
    file << "n,m,p,trial_number,heads_count,mean_heads,std_dev,expected_heads,error_percent\n";
    
    for (const auto& result : results) {
        double mean = result.mean_heads();
        double std_dev = result.std_deviation();
        double expected = result.n * result.p;
        double error_percent = std::abs((mean - expected) / expected) * 100.0;
        
        for (size_t i = 0; i < result.trials.size(); ++i) {
            file << result.n << ","
                 << result.m << ","
                 << std::fixed << std::setprecision(2) << result.p << ","
                 << (i + 1) << ","
                 << result.trials[i].heads_count << ","
                 << std::fixed << std::setprecision(2) << mean << ","
                 << std::fixed << std::setprecision(2) << std_dev << ","
                 << std::fixed << std::setprecision(2) << expected << ","
                 << std::fixed << std::setprecision(2) << error_percent << "\n";
        }
    }
    
    file.close();
    std::cout << "CSV data exported to: " << filename << "\n";
}

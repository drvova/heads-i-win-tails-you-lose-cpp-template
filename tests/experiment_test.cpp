#include <catch2/catch_test_macros.hpp>
#include "../src/experiment.hpp"

TEST_CASE("Experiment runs correct number of trials", "[experiment]") {
    Experiment exp;
    ExperimentResult result = exp.run_trials(100, 5, 0.5);
    
    REQUIRE(result.n == 100);
    REQUIRE(result.m == 5);
    REQUIRE(result.p == 0.5);
    REQUIRE(result.trials.size() == 5);
}

TEST_CASE("Experiment trial results have correct flip count", "[experiment]") {
    Experiment exp;
    ExperimentResult result = exp.run_trials(100, 3, 0.5);
    
    for (const auto& trial : result.trials) {
        REQUIRE(trial.flips_per_trial == 100);
        REQUIRE(trial.heads_count >= 0);
        REQUIRE(trial.heads_count <= 100);
    }
}

TEST_CASE("Experiment mean_heads calculates correctly", "[experiment]") {
    ExperimentResult result;
    result.n = 100;
    result.m = 3;
    result.p = 0.5;
    
    result.trials.push_back({100, 50});
    result.trials.push_back({100, 60});
    result.trials.push_back({100, 40});
    
    REQUIRE(result.mean_heads() == 50.0);
}

TEST_CASE("Experiment std_deviation calculates correctly", "[experiment]") {
    ExperimentResult result;
    result.n = 100;
    result.m = 3;
    result.p = 0.5;
    
    result.trials.push_back({100, 50});
    result.trials.push_back({100, 60});
    result.trials.push_back({100, 40});
    
    double std_dev = result.std_deviation();
    REQUIRE(std_dev > 8.16);
    REQUIRE(std_dev < 8.17);
}

TEST_CASE("Experiment with bias 1.0 returns all heads", "[experiment]") {
    Experiment exp;
    ExperimentResult result = exp.run_trials(100, 5, 1.0);
    
    for (const auto& trial : result.trials) {
        REQUIRE(trial.heads_count == 100);
    }
}

TEST_CASE("Experiment with bias 0.0 returns no heads", "[experiment]") {
    Experiment exp;
    ExperimentResult result = exp.run_trials(100, 5, 0.0);
    
    for (const auto& trial : result.trials) {
        REQUIRE(trial.heads_count == 0);
    }
}

TEST_CASE("Experiment format_results_table produces non-empty output", "[experiment]") {
    Experiment exp;
    std::vector<ExperimentResult> results;
    
    results.push_back(exp.run_trials(100, 10, 0.5));
    results.push_back(exp.run_trials(500, 10, 0.7));
    
    std::string output = Experiment::format_results_table(results);
    
    REQUIRE(!output.empty());
    REQUIRE(output.find("BIASED COIN FLIP EXPERIMENT RESULTS") != std::string::npos);
    REQUIRE(output.find("100") != std::string::npos);
    REQUIRE(output.find("500") != std::string::npos);
}

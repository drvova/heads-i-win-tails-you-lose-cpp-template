#pragma once

#include <random>

class Coin {
public:
    explicit Coin(double bias_probability);
    
    bool flip();
    
    double get_bias() const;

private:
    double bias_;
    std::mt19937 rng_;
    std::bernoulli_distribution distribution_;
};

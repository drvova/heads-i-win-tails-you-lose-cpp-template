#include "coin.hpp"

Coin::Coin(double bias_probability) 
    : bias_(bias_probability),
      rng_(std::random_device{}()),
      distribution_(bias_probability) {
}

bool Coin::flip() {
    return distribution_(rng_);
}

double Coin::get_bias() const {
    return bias_;
}

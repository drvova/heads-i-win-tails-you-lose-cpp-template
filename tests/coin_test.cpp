#include <catch2/catch_test_macros.hpp>
#include "../src/coin.hpp"

TEST_CASE("Coin with bias 0.0 always returns tails", "[coin]") {
    Coin coin(0.0);
    
    for (int i = 0; i < 100; ++i) {
        REQUIRE(coin.flip() == false);
    }
}

TEST_CASE("Coin with bias 1.0 always returns heads", "[coin]") {
    Coin coin(1.0);
    
    for (int i = 0; i < 100; ++i) {
        REQUIRE(coin.flip() == true);
    }
}

TEST_CASE("Coin with bias 0.5 returns approximately 50% heads", "[coin]") {
    Coin coin(0.5);
    int heads = 0;
    int trials = 10000;
    
    for (int i = 0; i < trials; ++i) {
        if (coin.flip()) {
            ++heads;
        }
    }
    
    double ratio = static_cast<double>(heads) / trials;
    REQUIRE(ratio > 0.45);
    REQUIRE(ratio < 0.55);
}

TEST_CASE("Coin stores bias correctly", "[coin]") {
    Coin coin(0.3);
    REQUIRE(coin.get_bias() == 0.3);
}

TEST_CASE("Coin with bias 0.7 returns approximately 70% heads", "[coin]") {
    Coin coin(0.7);
    int heads = 0;
    int trials = 10000;
    
    for (int i = 0; i < trials; ++i) {
        if (coin.flip()) {
            ++heads;
        }
    }
    
    double ratio = static_cast<double>(heads) / trials;
    REQUIRE(ratio > 0.65);
    REQUIRE(ratio < 0.75);
}

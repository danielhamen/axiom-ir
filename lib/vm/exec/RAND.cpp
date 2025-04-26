#include <random>
#include "../obj/Decimal.hpp"
#include "RAND.hpp"
#include "exec.hpp"
bool exec::RAND(Process& p) {
    static std::mt19937 rng{std::random_device{}()};
    std::uniform_real_distribution<double> dist(0.0,1.0);
    p.stack.push(std::make_shared<Decimal>(dist(rng)));
    return true;
}

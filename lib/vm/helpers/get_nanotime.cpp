#include <chrono>
#include "get_nanotime.hpp"

int64_t get_nanotime() {
    using namespace std::chrono;
    return duration_cast<nanoseconds>(
        high_resolution_clock::now().time_since_epoch()
    ).count();
}

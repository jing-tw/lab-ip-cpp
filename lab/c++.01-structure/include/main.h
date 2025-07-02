#pragma once

// Use constants instead of macros for type safety and scoping.
// constexpr int NUM_PGU_DEVICES = 3;
// constexpr int CURRENT_PGU_DEVICE = 2;
const int NUM_PGU_DEVICES = 3;
const int CURRENT_PGU_DEVICE = 2;

// C++ style struct definitions (no need for typedef)
struct LaserDevice {
    int RedMinMaxCurrent[2];   // [0]: min, [1]: max
    int GreenMinMaxCurrent[2];
    int BlueMinMaxCurrent[2];
};

struct PGUDeviceInfo {
    LaserDevice Left;
    LaserDevice Right;
};

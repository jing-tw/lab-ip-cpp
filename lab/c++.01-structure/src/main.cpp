#include <stdio.h>
#include "main.h"

const PGUDeviceInfo pguDeviceInfo[NUM_PGU_DEVICES] = {
    // PGU 0
    {/* Left */ {{11, 12}, {13, 14}, {15, 16}},
     /* Right */ {{17, 18}, {19, 110}, {111, 112}}},
    // PGU 1
    {/* Left */ {{21, 22}, {23, 24}, {25, 26}},
     /* Right */ {{27, 28}, {29, 210}, {211, 212}}},
    // PGU 2
    {/* Left */ {{31, 32}, {33, 34}, {35, 36}},
     /* Right */ {{37, 38}, {39, 310}, {311, 312}}}};

void printCurrentPGUInfo(const PGUDeviceInfo info[], int deviceIndex)
{
    if (deviceIndex < 0 || deviceIndex >= NUM_PGU_DEVICES)
    {
        printf("Error: deviceIndex %d is out of bounds.\n", deviceIndex);
        return;
    }
    const PGUDeviceInfo &device = info[deviceIndex];

    printf("--- PGU Device %d Info ---\n", deviceIndex + 1);
    printf("Left.Red  : min=%d, max=%d\n", device.Left.RedMinMaxCurrent[0], device.Left.RedMinMaxCurrent[1]);
    printf("Left.Green: min=%d, max=%d\n", device.Left.GreenMinMaxCurrent[0], device.Left.GreenMinMaxCurrent[1]);
    printf("Left.Blue : min=%d, max=%d\n", device.Left.BlueMinMaxCurrent[0], device.Left.BlueMinMaxCurrent[1]);
    printf("Right.Red  : min=%d, max=%d\n", device.Right.RedMinMaxCurrent[0], device.Right.RedMinMaxCurrent[1]);
    printf("Right.Green: min=%d, max=%d\n", device.Right.GreenMinMaxCurrent[0], device.Right.GreenMinMaxCurrent[1]);
    printf("Right.Blue : min=%d, max=%d\n", device.Right.BlueMinMaxCurrent[0], device.Right.BlueMinMaxCurrent[1]);
    printf("--------------------------\n");
}

int main()
{
    printCurrentPGUInfo(pguDeviceInfo, CURRENT_PGU_DEVICE);
    return 0;
}

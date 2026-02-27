#include "FileSystem.hpp"

// Define the global flag here (one definition only)
volatile bool pcHasDrive = false;

// Called when host wants to use the drive
bool driveReady(uint32_t)
{
    if (pcHasDrive)
        return true; // already granted

    // Ensure we are not using FatFS before giving it to the PC
    // (all files should be closed, no logging in progress).
    // Here we just assume it's safe:
    FatFS.end();
    pcHasDrive = true;
    return true;
}

// Called when host unmounts/ejects the drive
void onUnplug(uint32_t)
{
    pcHasDrive = false;
    FatFS.begin(); // remount for MCU use
}

void setupUSB()
{
    FatFSUSB.driveReady(driveReady);
    FatFSUSB.onUnplug(onUnplug);
    FatFS.begin();
    FatFSUSB.begin(); // sets up USB MSC interface
}

void loopUSB()
{
    if (!pcHasDrive)
    {
        // Safe to log
        auto f = FatFS.open("/log.csv", "a");
        if (f)
        {
            f.println("some,data,here");
            f.close();
        }
    }
}

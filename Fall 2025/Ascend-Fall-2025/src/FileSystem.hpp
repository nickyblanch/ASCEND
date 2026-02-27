#pragma once

#include <FatFS.h>
#include <FatFSUSB.h>

// Header-only declarations only. Implementations live in FileSystem.cpp

// Global flag indicating whether the host PC has taken the USB drive.
extern volatile bool pcHasDrive;

// Called when host wants to use the drive
bool driveReady(uint32_t);

// Called when host unmounts/ejects the drive
void onUnplug(uint32_t);

void setupUSB();

void loopUSB();

//
// Created by mechlon on 08.06.24.
//

#include "GlobalSettings.h"

GlobalSettings GlobalSettings::instance_; // Define the static instance

GlobalSettings& GlobalSettings::GetInstance() {
    return instance_;
}

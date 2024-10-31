//
// Created by Shreejit Murthy on 1/11/2024.
//

#pragma once

#include <filesystem>
#include <iostream>

namespace fs = std::filesystem;

namespace System {
    fs::path findEnginePath(const fs::path& startDir = fs::current_path());
    fs::path findPathUpwards(const fs::path& targetPath, const fs::path& startDir = fs::current_path());
}
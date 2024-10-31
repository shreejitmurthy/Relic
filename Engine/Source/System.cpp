//
// Created by Shreejit Murthy on 1/11/2024.
//

#include "System.hpp"
#include "log/log.h"

fs::path System::findEnginePath(const fs::path &startDir) {
    fs::path dir = startDir;
    while (true) {
        fs::path potentialEnginePath = dir / "Engine";
        if (fs::exists(potentialEnginePath) && fs::is_directory(potentialEnginePath)) {
            return fs::absolute(potentialEnginePath);
        }

        if (dir == dir.root_path()) {
            log_error("Engine directory not found!");
            exit(1);
        }

        // move up one level in the directory
        dir = dir.parent_path();
    }
}

fs::path System::findPathUpwards(const fs::path& targetPath, const fs::path& startDir) {
    fs::path dir = startDir;

    while (true) {
        fs::path potentialPath = dir / targetPath;
        if (fs::exists(potentialPath)) {
            return fs::absolute(potentialPath);
        }

        if (dir == dir.root_path()) {
            log_error("Target: %s not found", targetPath.c_str());
            exit(1);
        }

        // move up one level
        dir = dir.parent_path();
    }
}

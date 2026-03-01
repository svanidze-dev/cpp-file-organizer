#include <iostream>
#include <filesystem>
#include <unordered_map>
#include <vector>

namespace fs = std::filesystem;

// Get file extension in lowercase
std::string toLower(std::string s) {
    for (char& c : s) c = std::tolower(c);
    return s;
}

int main() {
    std::string path;
    std::cout << "Enter folder path: ";
    std::getline(std::cin, path);

    if (!fs::exists(path)) {
        std::cout << "Folder not found!\n";
        return 1;
    }

    std::unordered_map<std::string, std::string> folders = {
        {".jpg", "Images"}, {".png", "Images"}, {".jpeg", "Images"},
        {".mp4", "Videos"}, {".avi", "Videos"}, {".mkv", "Videos"},
        {".pdf", "Documents"}, {".docx", "Documents"}, {".txt", "Documents"},
        {".zip", "Archives"}, {".rar", "Archives"}
    };

    for (const auto& entry : fs::directory_iterator(path)) {
        if (!entry.is_regular_file()) continue;

        std::string ext = toLower(entry.path().extension().string());

        if (folders.count(ext)) {
            fs::path targetDir = fs::path(path) / folders[ext];

            if (!fs::exists(targetDir)) {
                fs::create_directory(targetDir);
            }

            fs::path targetPath = targetDir / entry.path().filename();

            try {
                fs::rename(entry.path(), targetPath);
                std::cout << "Moved: " << entry.path().filename() << std::endl;
            }
            catch (...) {
                std::cout << "Failed: " << entry.path().filename() << std::endl;
            }
        }
    }

    std::cout << "Done!\n";
    return 0;
}
#include <iostream>
#include <filesystem>
#include <unordered_map>
#include <vector>
#include <fstream>
#include <ctime>
#include <iomanip>

namespace fs = std::filesystem;

#ifdef _WIN32
#include <windows.h>
void setColor(int color) {
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleTextAttribute(hConsole, color);
}
void resetColor() {
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleTextAttribute(hConsole, 7);
}
#else
void setColor(int) {}
void resetColor() {}
#endif

#define GREEN 10
#define RED 12
#define YELLOW 14
#define BLUE 9
#define GRAY 8

std::string toLower(std::string s) {
    for (char& c : s) c = std::tolower(static_cast<unsigned char>(c));
    return s;
}

std::string getCurrentTime() {
    time_t now = time(0);
    char* dt = ctime(&now);
    std::string timeStr(dt);
    timeStr.pop_back();
    return timeStr;
}

std::string formatSize(uintmax_t size) {
    const char* units[] = { "B", "KB", "MB", "GB", "TB" };
    int unit = 0;
    double s = size;

    while (s >= 1024 && unit < 4) {
        s /= 1024;
        unit++;
    }

    char buffer[50];
    sprintf(buffer, "%.1f %s", s, units[unit]);
    return std::string(buffer);
}

int main() {
#ifdef _WIN32
    SetConsoleCP(1251);
    SetConsoleOutputCP(1251);
    SetConsoleTitle("C++ File Organizer");
#endif

    system("cls");

    setColor(GREEN);
    std::cout << "\n";
    std::cout << "         FILE ORGANIZER\n";
    std::cout << "         by Svanidze\n";
    std::cout << "\n\n";
    resetColor();

    std::string path;
    std::cout << "Enter folder path: ";
    std::getline(std::cin, path);

    if (path.size() >= 2 && path.front() == '"' && path.back() == '"') {
        path = path.substr(1, path.size() - 2);
    }

    if (!fs::exists(path)) {
        setColor(RED);
        std::cout << "Error: Folder not found!\n";
        resetColor();
        return 1;
    }

    std::unordered_map<std::string, std::string> folders = {
        {".jpg", "Images"}, {".jpeg", "Images"}, {".png", "Images"},
        {".gif", "Images"}, {".bmp", "Images"}, {".svg", "Images"},
        {".webp", "Images"}, {".ico", "Images"}, {".tiff", "Images"},
        {".mp4", "Videos"}, {".avi", "Videos"}, {".mkv", "Videos"},
        {".mov", "Videos"}, {".wmv", "Videos"}, {".flv", "Videos"},
        {".webm", "Videos"}, {".m4v", "Videos"}, {".mpg", "Videos"},
        {".pdf", "Documents"}, {".doc", "Documents"}, {".docx", "Documents"},
        {".txt", "Documents"}, {".rtf", "Documents"}, {".odt", "Documents"},
        {".xls", "Documents"}, {".xlsx", "Documents"}, {".ppt", "Documents"},
        {".pptx", "Documents"}, {".md", "Documents"}, {".csv", "Documents"},
        {".zip", "Archives"}, {".rar", "Archives"}, {".7z", "Archives"},
        {".tar", "Archives"}, {".gz", "Archives"}, {".bz2", "Archives"},
        {".xz", "Archives"}, {".iso", "Archives"},
        {".mp3", "Music"}, {".wav", "Music"}, {".flac", "Music"},
        {".aac", "Music"}, {".ogg", "Music"}, {".m4a", "Music"},
        {".wma", "Music"},
        {".exe", "Programs"}, {".msi", "Programs"}, {".bat", "Programs"},
        {".cmd", "Programs"}, {".sh", "Programs"},
        {".py", "Code"}, {".cpp", "Code"}, {".h", "Code"},
        {".js", "Code"}, {".html", "Code"}, {".css", "Code"},
        {".php", "Code"}, {".java", "Code"}, {".json", "Code"},
        {".torrent", "Torrents"}
    };

    std::vector<std::string> movedFiles;
    std::vector<std::string> failedFiles;
    std::unordered_map<std::string, int> categoryCount;
    std::unordered_map<std::string, uintmax_t> categorySize;
    uintmax_t totalSize = 0;
    int totalFiles = 0;
    int skippedFiles = 0;

    std::cout << "\nScanning directory: " << path << "\n";

    std::vector<fs::directory_entry> files;
    for (const auto& entry : fs::directory_iterator(path)) {
        if (entry.is_regular_file()) {
            files.push_back(entry);
        }
    }

    setColor(YELLOW);
    std::cout << "Found " << files.size() << " files\n\n";
    resetColor();

    int processed = 0;
    for (const auto& entry : files) {
        processed++;
        std::string filename = entry.path().filename().string();
        std::string ext = toLower(entry.path().extension().string());
        uintmax_t fileSize = entry.file_size();

        std::cout << "\rProcessing: [" << std::string(processed * 50 / files.size(), '=')
            << std::string(50 - (processed * 50 / files.size()), ' ') << "] "
            << (processed * 100 / files.size()) << "%" << std::flush;

        auto it = folders.find(ext);
        if (it != folders.end()) {
            fs::path targetDir = fs::path(path) / it->second;

            try {
                if (!fs::exists(targetDir)) {
                    fs::create_directory(targetDir);
                }

                fs::path targetPath = targetDir / filename;
                int copyNum = 1;

                while (fs::exists(targetPath)) {
                    std::string baseName = entry.path().stem().string();
                    std::string newName = baseName + "_" + std::to_string(copyNum) + ext;
                    targetPath = targetDir / newName;
                    copyNum++;
                }

                fs::rename(entry.path(), targetPath);

                movedFiles.push_back(filename);
                categoryCount[it->second]++;
                categorySize[it->second] += fileSize;
                totalSize += fileSize;
                totalFiles++;
            }
            catch (const fs::filesystem_error& e) {
                failedFiles.push_back(filename);
            }
        }
        else {
            skippedFiles++;
        }
    }

    std::cout << "\n\n";

    setColor(GREEN);
    std::cout << "\n";
    std::cout << "         ORGANIZATION COMPLETE          \n";
    std::cout << "\n";
    resetColor();

    std::cout << "Time: " << getCurrentTime() << "\n\n";

    std::cout << "STATISTICS:\n";
    std::cout << "  Moved: " << totalFiles << " files\n";
    if (skippedFiles > 0) {
        setColor(YELLOW);
        std::cout << "  Skipped: " << skippedFiles << " files (unknown types)\n";
        resetColor();
    }
    if (!failedFiles.empty()) {
        setColor(RED);
        std::cout << "  Failed: " << failedFiles.size() << " files\n";
        resetColor();
    }
    std::cout << "  Total size: " << formatSize(totalSize) << "\n\n";

    std::cout << "FILES BY CATEGORY:\n";
    for (const auto& [category, count] : categoryCount) {
        setColor(BLUE);
        std::cout << "  " << category << ":\n";
        resetColor();
        std::cout << "     Files: " << count << "\n";
        std::cout << "     Size:  " << formatSize(categorySize[category]) << "\n\n";
    }

    std::ofstream logFile("organizer_log.txt");
    if (logFile.is_open()) {
        logFile << "C++ FILE ORGANIZER LOG\n";
        logFile << "======================\n";
        logFile << "Time: " << getCurrentTime() << "\n";
        logFile << "Path: " << path << "\n";
        logFile << "Files moved: " << totalFiles << "\n";
        logFile << "Total size: " << formatSize(totalSize) << "\n\n";

        logFile << "MOVED FILES:\n";
        for (const auto& f : movedFiles) {
            logFile << "  " << f << "\n";
        }

        if (!failedFiles.empty()) {
            logFile << "\nFAILED FILES:\n";
            for (const auto& f : failedFiles) {
                logFile << "  " << f << "\n";
            }
        }

        logFile.close();
        setColor(GRAY);
        std::cout << "Log saved to: organizer_log.txt\n";
        resetColor();
    }

    setColor(GREEN);
    std::cout << "\nDone! Press any key to exit...\n";
    resetColor();

#ifdef _WIN32
    system("pause > nul");
#endif

    return 0;
}
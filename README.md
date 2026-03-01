# C++ File Organizer 🗂️

[![C++17](https://img.shields.io/badge/C++-17-blue.svg)](https://isocpp.org/)
[![License: MIT](https://img.shields.io/badge/License-MIT-yellow.svg)](https://opensource.org/licenses/MIT)
[![Windows](https://img.shields.io/badge/Platform-Windows-lightgrey)](https://github.com/svanidze-dev/cpp-file-organizer)

A fast, lightweight, and colorful command-line tool to automatically organize files into categorized folders. No more messy downloads folder!

---

## Features

-   ** Automatic Sorting:** Moves files into folders like `Images`, `Documents`, `Videos` based on their extension.
-   ** 50+ File Extensions:** Supports a wide range of image, video, document, archive, music, and code formats.
-   ** Colored Console Output:** Clean and easy-to-read interface with status indicators.
-   ** Detailed Statistics:** Shows you exactly how many files were moved, skipped, and the total size after organization.
-   ** Duplicate Handling:** If a file with the same name already exists, it automatically renames the new one (e.g., `image_copy1.jpg`).
-   ** Log File:** Creates an `organizer_log.txt` file with a complete record of all moved files.
-   ** Human-Readable Sizes:** Displays file and folder sizes in KB, MB, or GB.

---

##  Example

When you run the program, you'll see a clean and informative output like this:


        FILE ORGANIZER v2.0         
         by Svanidze                     


Enter folder path: C:\Users\Svanidze\Downloads

Scanning directory: C:\Users\Svanidze\Downloads
Found 42 files

Processing: [==================================================] 100%


         ORGANIZATION COMPLETE          

Time: Sun Mar  2 22:56:14 2026

STATISTICS:
  Moved: 38 files
  Skipped: 4 files (unknown types)
  Total size: 156.2 MB

FILES BY CATEGORY:
  Images:
     Files: 12
     Size:  45.3 MB
  Documents:
     Files: 8
     Size:  12.1 MB
  ... and so on ...

 Supported File Types

## Supported File Types

## Supported File Types

**Images:** .jpg, .jpeg, .png, .gif, .bmp, .svg, .webp, .ico, .tiff

**Videos:** .mp4, .avi, .mkv, .mov, .wmv, .flv, .webm, .m4v, .mpg

**Documents:** .pdf, .doc, .docx, .txt, .rtf, .odt, .xls, .xlsx, .ppt, .pptx, .md, .csv

**Archives:** .zip, .rar, .7z, .tar, .gz, .bz2, .xz, .iso

**Music:** .mp3, .wav, .flac, .aac, .ogg, .m4a, .wma

**Programs:** .exe, .msi, .bat, .cmd, .sh

**Code:** .py, .cpp, .h, .js, .html, .css, .php, .java, .json

**Torrents:** .torrent

## How to Use

1. Download the executable from the Releases page
2. Open a terminal in the download folder
3. Run: .\organizer.exe
4. Enter the path to the folder you want to organize

Or compile from source:
git clone https://github.com/svanidze-dev/cpp-file-organizer.git
cd cpp-file-organizer
g++ -std=c++17 main.cpp -o organizer.exe
.\organizer.exe

## Requirements

- Windows operating system
- C++17 compatible compiler (only if compiling from source)

## Author

Svanidze
GitHub: @svanidze-dev

#include "writer.h"

Writer::Writer() : file_handle(INVALID_HANDLE_VALUE), map_handle(nullptr), map_address(nullptr) {}

void Writer::ProjectFile() {
    if (file_handle == INVALID_HANDLE_VALUE && map_address == nullptr) {
        try {
            std::string file_name, map_name;

            std::cout << "Enter file name:\n";
            std::getline(std::cin, file_name);

            file_handle = CreateFileA(file_name.data(), GENERIC_READ | GENERIC_WRITE, 0, nullptr, CREATE_ALWAYS, 0, nullptr);
            if (file_handle == INVALID_HANDLE_VALUE) {
                throw GetLastError();
            }

            std::cout << "Enter map name:\n";
            std::getline(std::cin, map_name);

            map_handle = CreateFileMappingA(file_handle, nullptr, PAGE_READWRITE, 0, MAX_FILE_SIZE, map_name.data());
            if (map_handle == nullptr) {
                CloseHandle(file_handle);
                throw GetLastError();
            }

            map_address = MapViewOfFile(map_handle, FILE_MAP_WRITE, 0, 0, MAX_FILE_SIZE);
            if (map_address == nullptr) {
                CloseHandle(map_handle);
                CloseHandle(file_handle);
                throw GetLastError();
            }

            std::cout << "File projected successfully\n";

        } catch (const DWORD& error) {
            std::cout << "Error " << error << " ocurred\n";
            file_handle = INVALID_HANDLE_VALUE;
            map_address = nullptr;
        }
    } else {
        std::cout << "Unmap of last file by 3 menu item before projection\n";
    }
}

void Writer::Write() {
    if (file_handle != INVALID_HANDLE_VALUE && map_handle != nullptr && map_address != nullptr) {
        std::string data;

        std::cout << "Enter data:\n";
        std::getline(std::cin, data);

        if (data.length() <= MAX_FILE_SIZE) {
            memcpy(map_address, data.data(), data.length());
            std::cout << "Data written successfully\n";
        }
        else {
            std::cout << "Data size is too large for the file\n";
        }
    } else {
        std::cout << "Project file by 1 menu item after writing\n";
    }
}

void Writer::Close() {
    if (file_handle == INVALID_HANDLE_VALUE && map_handle == nullptr && map_address == nullptr) {
        std::cout << "Nothing to close\n";
    } else {
        if (map_address != nullptr) {
            UnmapViewOfFile(map_address);
        }
        if (map_handle != nullptr) {
            CloseHandle(map_handle);
        }
        if (file_handle != INVALID_HANDLE_VALUE) {
            CloseHandle(file_handle);
        }
        file_handle = INVALID_HANDLE_VALUE;
        map_handle = nullptr;
        map_address = nullptr;
        std::cout << "Projected file closed\n";
    }
}

Writer::~Writer() {
    Close();
}
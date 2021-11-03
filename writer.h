#pragma once

#ifndef WRITER_H
#define WRITER_H

#include <string>
#include <Windows.h>
#include <map>
#include <set>
#include <stdexcept>

#undef max

#include "incontrol.h"

// TODO
// - projecting more than one file
// - choosing the file size and adjusting it

class Writer {
public:
    Writer();
    void ProjectFile();
    void Write();
    void Close();
    ~Writer();

private:
    const DWORD MAX_FILE_SIZE = 256;
    HANDLE file_handle;
    HANDLE map_handle;
    void* map_address;
};

#endif // !WRITER_H



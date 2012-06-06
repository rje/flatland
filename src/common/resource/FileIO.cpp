//
//  FileIO.cpp
//  flatland
//
//  Created by Ryan Evans on 6/5/12.
//  Copyright (c) 2012 Mirror Match Games. All rights reserved.
//

#include "FileIO.h"
#include <fstream>
#include <stdio.h>
#include <sys/stat.h>
#include <sys/param.h>

GLboolean FileIO::FileExists(string& fullPath) {
    struct stat info;
    int err = stat(fullPath.c_str(), &info);
    if(err) {
        return false;
    }
    return S_ISREG(info.st_mode);
}

GLboolean FileIO::IsDirectory(string& path) {
    struct stat info;
    int err = stat(path.c_str(), &info);
    return !err && S_ISDIR(info.st_mode);
}

GLboolean FileIO::IsFile(string& path) {
    struct stat info;
    int err = stat(path.c_str(), &info);
    return err && S_ISREG(info.st_mode);
}

string FileIO::GetPathComponent(string& fullFilePath) {
    size_t loc = fullFilePath.find_last_of('/');
    if(loc == string::npos) {
        return "";
    }
    else {
        return fullFilePath.substr(0, loc);
    }
}

string FileIO::GetFileComponent(string& fullFilePath) {
    size_t loc = fullFilePath.find_last_of('/');
    size_t len = fullFilePath.length() - loc;
    if(loc == string::npos) {
        return "";
    }
    return fullFilePath.substr(loc + 1, len - 1);
}

void FileIO::SetWorkingDirectory(string& path) {
    if(!FileIO::IsDirectory(path)) {
        printf("CANNOT SET WORKING DIRECTORY, INVALID DIRECTORY: %s\n", path.c_str());
    }
    else {
        chdir(path.c_str());
    }
}

string FileIO::GetWorkingDirectory() {
    char wd[MAXPATHLEN];
    getcwd(wd, MAXPATHLEN);
    return string(wd);
}

string FileIO::GetTextFile(const string& relativePath) {
    string full_path = FileIO::GetWorkingDirectory() + "/" + relativePath;
    ifstream ifs(relativePath.c_str());
    return string(istreambuf_iterator<char>(ifs),istreambuf_iterator<char>());
}


FILE* FileIO::OpenFileDescriptor(const string& relativePath) {
    string full_path = FileIO::GetWorkingDirectory() + "/" + relativePath;
    return fopen(full_path.c_str(), "rb");
}
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
#include <sys/types.h>
#include <sys/mman.h>
#include <string.h>
#include <fcntl.h>
#ifndef WIN32
#include <sys/param.h>
#include <dirent.h>
#else
#include <Shlwapi.h>
#define S_ISREG(x) (_S_IFREG & x)
#define S_ISDIR(x) (_S_IFDIR & x)
#define MAXPATHLEN MAX_PATH
#endif
#include <stdlib.h>

using namespace std;

string* FileIO::m_exeDir = NULL;

#ifndef WIN32
const string FileIO::sep = "/";
#else
const string FileIO::sep = "\\";
#endif

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
    return !err && S_ISREG(info.st_mode);
}

string FileIO::GetPathComponent(string& fullFilePath) {
    size_t loc = fullFilePath.find_last_of(FileIO::sep);
    if(loc == string::npos) {
        return "";
    }
    else {
        return fullFilePath.substr(0, loc);
    }
}

string FileIO::GetFileComponent(string& fullFilePath) {
    size_t loc = fullFilePath.find_last_of(FileIO::sep);
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
#ifdef WIN32
		SetCurrentDirectoryA(path.c_str());
#else
        chdir(path.c_str());
#endif
    }
}

string FileIO::GetWorkingDirectory() {
    char wd[MAXPATHLEN];
#ifndef WIN32
    getcwd(wd, MAXPATHLEN);
#else
	GetCurrentDirectoryA(MAXPATHLEN, wd);
#endif
    return string(wd);
}

string FileIO::GetTextFile(string& relativePath) {
    string full_path = FileIO::GetExpandedPath(relativePath);
    ifstream ifs(relativePath.c_str());
    return string(istreambuf_iterator<char>(ifs),istreambuf_iterator<char>());
}

void searchAndReplace(std::string& value, std::string const& search, std::string const& replace) {
	string::size_type pos;
	for(pos = value.find(search); pos != string::npos; pos = value.find(search, pos)) {
		value.replace(pos, search.length(), replace);
		pos += search.length();
	}
}

string FileIO::GetExpandedPath(string& relativePath) {
#ifndef WIN32
    if(relativePath[0] == '/') {
        return relativePath;
    }
#else
	searchAndReplace(relativePath, "/", "\\");
	if(!PathIsRelativeA(relativePath.c_str())) {
		return relativePath;
	}
#endif
    string toReturn = FileIO::GetWorkingDirectory() + FileIO::sep + relativePath;
    return toReturn;
}

FILE* FileIO::OpenFileDescriptor(string& relativePath) {
    string full_path = FileIO::GetExpandedPath(relativePath);
    return fopen(full_path.c_str(), "rb");
}

void FileIO::DetermineExecutableDirectory(char* argv0) {
    char path[MAXPATHLEN];
    string toExpand(argv0);
    string expanded = GetExpandedPath(toExpand);
#ifndef WIN32
    realpath(expanded.c_str(), path);
#else
	PathCanonicalizeA(path, expanded.c_str());
#endif
    m_exeDir = new string(path);
}

StringVector FileIO::FindRequiredLibraryFiles() {
    StringVector results;
    string libdir = GetPathComponent(*m_exeDir) + FileIO::sep + "builtins";
#ifndef WIN32
    DIR* builtindir = opendir(libdir.c_str());
    struct dirent* entry;
    while((entry = readdir(builtindir)) != NULL) {
        string name(entry->d_name);
        if(name.rfind(".js") != string::npos) {
            results.push_back(libdir + FileIO::sep + name);
        }
    }
    closedir(builtindir);
#else
	string searchString = libdir + FileIO::sep + "*.js";
	WIN32_FIND_DATAA finddata;
	HANDLE dhandle;
	dhandle = FindFirstFileA(searchString.c_str(), &finddata);
	if(dhandle != INVALID_HANDLE_VALUE) {
		results.push_back(libdir + FileIO::sep + finddata.cFileName);
		while(FindNextFileA(dhandle, &finddata)) {
			results.push_back(libdir + FileIO::sep + string(finddata.cFileName));
		}
	}
	FindClose(dhandle);
#endif
    return results;
}

StringVector FileIO::GetScaffoldFiles() {
    StringVector results;
    string libdir = GetPathComponent(*m_exeDir) + FileIO::sep + "scaffold";
#ifndef WIN32
    DIR* builtindir = opendir(libdir.c_str());
    struct dirent* entry;
    while((entry = readdir(builtindir)) != NULL) {
        string name(entry->d_name);
        if(name.compare(".") && name.compare("..")) {
            results.push_back(libdir + FileIO::sep + name);
        }
    }
    closedir(builtindir);
#else
	string searchString = libdir + FileIO::sep + "*";
	WIN32_FIND_DATAA finddata;
	HANDLE dhandle;
	dhandle = FindFirstFileA(searchString.c_str(), &finddata);
	if(dhandle != INVALID_HANDLE_VALUE) {
		results.push_back(libdir + FileIO::sep + finddata.cFileName);
		while(FindNextFileA(dhandle, &finddata)) {
			results.push_back(libdir + FileIO::sep + string(finddata.cFileName));
		}
	}
	FindClose(dhandle);
#endif
    return results;
}

GLboolean FileIO::MakeDirectory(string& fullpath) {
    int err = mkdir(fullpath.c_str(), S_IRWXU|S_IRWXG);
    return !err;
}

void FileIO::CopyFile(string& src, string& dst) {
    int in, out;
    void* src_buf, *dst_buf;
    struct stat statbuf;
    
    in = open(src.c_str(), O_RDONLY);
    out = open(dst.c_str(), O_RDWR|O_CREAT|O_TRUNC, S_IRWXU|S_IRWXG);
    int err = fstat(in, &statbuf);
    err = lseek(out, statbuf.st_size - 1, SEEK_SET);
    write(out, "", 1);
    src_buf = mmap(0, statbuf.st_size, PROT_READ, MAP_SHARED, in, 0);
    dst_buf = mmap(0, statbuf.st_size, PROT_READ|PROT_WRITE, MAP_SHARED, out, 0);
    memcpy(dst_buf, src_buf, statbuf.st_size);
    munmap(src_buf, statbuf.st_size);
    munmap(dst_buf, statbuf.st_size);
    close(out);
    close(in);
}

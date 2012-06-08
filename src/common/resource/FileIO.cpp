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

string* FileIO::m_exeDir = NULL;

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
#ifndef WIN32
    size_t loc = fullFilePath.find_last_of('/');
#else
    size_t loc = fullFilePath.find_last_of('\\');
#endif
    if(loc == string::npos) {
        return "";
    }
    else {
        return fullFilePath.substr(0, loc);
    }
}

string FileIO::GetFileComponent(string& fullFilePath) {
#ifndef WIN32
    size_t loc = fullFilePath.find_last_of('/');
#else
    size_t loc = fullFilePath.find_last_of('\\');
#endif
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
    //printf("--> expanding %s\n", relativePath.c_str());
#ifndef WIN32
	string sep = "/";
    if(relativePath[0] == '/') {
        //printf("  --> already expanded, returning\n");
        return relativePath;
    }
#else
	string sep = "\\";
	searchAndReplace(relativePath, "/", "\\");
	if(!PathIsRelativeA(relativePath.c_str())) {
		return relativePath;
	}
#endif
    string toReturn = FileIO::GetWorkingDirectory() + sep + relativePath;
    //printf(" --> adding wd, now: %s\n", toReturn.c_str());
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
    //printf("FULLPATH: %s\n", path);
}

vector<string> FileIO::FindRequiredLibraryFiles() {
    vector<string> results;
#ifndef WIN32
    string libdir = GetPathComponent(*m_exeDir) + "/builtins";
    DIR* builtindir = opendir(libdir.c_str());
    struct dirent* entry;
    while((entry = readdir(builtindir)) != NULL) {
        string name(entry->d_name);
        if(name.rfind(".js") != string::npos) {
            results.push_back(libdir + "/" + name);
        }
    }
    closedir(builtindir);
#else
    string libdir = GetPathComponent(*m_exeDir) + "\\builtins";
	string searchString = libdir + "\\*.js";
	WIN32_FIND_DATAA finddata;
	HANDLE dhandle;
	dhandle = FindFirstFileA(searchString.c_str(), &finddata);
	if(dhandle != INVALID_HANDLE_VALUE) {
		results.push_back(libdir + "\\" + finddata.cFileName);
		while(FindNextFileA(dhandle, &finddata)) {
			results.push_back(libdir + "\\" + string(finddata.cFileName));
		}
	}
	FindClose(dhandle);
#endif
    return results;
}

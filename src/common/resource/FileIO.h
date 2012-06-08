//
//  FileIO.h
//  flatland
//
//  Created by Ryan Evans on 6/5/12.
//  Copyright (c) 2012 Mirror Match Games. All rights reserved.
//

#ifndef flatland_FileIO_h
#define flatland_FileIO_h

#include <SDL_opengl.h>
#include <string>
#include <vector>

using namespace std;

class FileIO {
public:
    static GLboolean FileExists(string& fullPath);
    static GLboolean IsDirectory(string& path);
    static GLboolean IsFile(string& path);
    static string GetPathComponent(string& fullFilePath);
    static string GetFileComponent(string& fullFilePath);
    static string GetWorkingDirectory();
    static void SetWorkingDirectory(string& path);
    static string GetTextFile(string& relativePath);
    static string GetExpandedPath(string& relativePath);
    static FILE* OpenFileDescriptor(string& relativePath);
    static void DetermineExecutableDirectory(char* argv0);
    static vector<string> FindRequiredLibraryFiles();
    
private:
    static string* m_exeDir;
};


#endif

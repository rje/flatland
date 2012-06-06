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
    static string GetTextFile(const string& relativePath);
    static FILE* OpenFileDescriptor(const string& relativePath);
};


#endif

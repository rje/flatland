//
//  FileIO.h
//  flatland
//
//  Created by Ryan Evans on 6/5/12.
//  Copyright (c) 2012 Mirror Match Games. All rights reserved.
//

#ifndef flatland_FileIO_h
#define flatland_FileIO_h

#include "flatland_common.h"

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
    static GLboolean MakeDirectory(string& fullpath);
    static void CopyFile(string& src, string& dst);
    static StringVector FindRequiredLibraryFiles();
    static StringVector GetScaffoldFiles();
    
    static const string sep;
private:
    static string* m_exeDir;
};


#endif



#ifndef _flatland_JSInterpreter_H_
#define _flatland_JSInterpreter_H_

#include <string>
#include <v8.h>

using namespace std;

class JSInterpreter {
public:
    JSInterpreter();
    virtual ~JSInterpreter();
    void InitializeVM();
    void LoadFile(string& path, const string& name = "");
    void RunString(string& contents, const string& name = "");
    
private:
    v8::Persistent<v8::ObjectTemplate> m_globalObjDef;
    v8::Persistent<v8::Context> m_context;
};

#endif


#ifndef _flatland_JSInterpreter_H_
#define _flatland_JSInterpreter_H_

#include <string>
#include <v8.h>

using namespace std;

class JSInterpreter {
public:
    static JSInterpreter* Instance();
    void LoadFile(string& path, const string& name = "");
    void RunString(string& contents, const string& name = "");
    
private:
    JSInterpreter();
    virtual ~JSInterpreter();
    void InitializeVM();
    v8::Persistent<v8::ObjectTemplate> m_globalObjDef;
    v8::Persistent<v8::Context> m_context;
    void RegisterConsole();
};

#endif
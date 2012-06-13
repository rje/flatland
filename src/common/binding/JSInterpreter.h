

#ifndef _flatland_JSInterpreter_H_
#define _flatland_JSInterpreter_H_

#include <string>
#include <v8.h>

using namespace std;

class JSInterpreter {
public:
    static JSInterpreter* Instance();
    v8::Handle<v8::Value> LoadFile(string& path, const string& name = "");
    v8::Handle<v8::Value> RunString(string& contents, const string& name = "");
    
    v8::Persistent<v8::Context> m_context;
    
    void CallMain();
private:
    JSInterpreter();
    virtual ~JSInterpreter();
    void InitializeVM();
    v8::Persistent<v8::ObjectTemplate> m_globalObjDef;
    void RegisterConsole();
    void BindBuiltins();
};

#endif


#include "JSInterpreter.h"
#include <fstream>

#include "WindowBindings.h"

using namespace v8;

JSInterpreter::JSInterpreter() {
    
}

JSInterpreter::~JSInterpreter() {
    
}

void JSInterpreter::InitializeVM() {
    HandleScope handle_scope;
    Handle<ObjectTemplate> global = ObjectTemplate::New();
    m_globalObjDef = Persistent<ObjectTemplate>::New(global);
    // BINDINGS BLOCK
    WindowBindings_BindToGlobal(m_globalObjDef);
    // BINDINGS BLOCK
    m_context = Context::New(NULL, m_globalObjDef);
    
}

void JSInterpreter::LoadFile(string& path, const string& name) {
    ifstream ifs(path.c_str());
    string content((istreambuf_iterator<char>(ifs)),istreambuf_iterator<char>());
    RunString(content, name);
}

void JSInterpreter::RunString(string& contents, const string& name) {
    HandleScope current_scope;
    Context::Scope context_scope(m_context);
    TryCatch trycatch;
    Handle<String> source = String::New(contents.c_str());
    Handle<Script> script = Script::Compile(source, String::New(name.c_str()));
    Handle<Value> val = script->Run();
    if(val.IsEmpty()) {
        Handle<Value> stack = trycatch.StackTrace();
        String::Utf8Value result(stack);
        printf("Stack trace:\n%s\n", *result);
    }
    else {
        String::Utf8Value result(val);
        printf("Result: %s\n", *result);
    }
}
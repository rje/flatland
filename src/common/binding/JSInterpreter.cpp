

#include "JSInterpreter.h"
#include "FileIO.h"

#include "WindowBindings.h"
#include "EntityBindings.h"
#include "MeshBindings.h"
#include "MeshRendererBindings.h"
#include "TransformBindings.h"
#include "ScriptableBindings.h"
#include "KeyboardBindings.h"
#include "ColliderBindings.h"
#include "BoxColliderBindings.h"
#include "CircleColliderBindings.h"
#include "TextureBindings.h"

using namespace v8;

JSInterpreter* JSInterpreter::Instance() {
    static JSInterpreter* sm_instance = NULL;
    if(sm_instance == NULL) {
        sm_instance = new JSInterpreter();
        sm_instance->InitializeVM();
    }
    
    return sm_instance;
}

JSInterpreter::JSInterpreter() {
    
}

JSInterpreter::~JSInterpreter() {
    
}

Handle<Value> _fl_jsi_console_log(const Arguments& args) {
    HandleScope handle_scope;
    String::Utf8Value toPrint(args[0]->ToString());
    printf("%s\n", *toPrint);
    return Undefined();
}

void JSInterpreter::RegisterConsole() {
    HandleScope handle_scope;
    Handle<ObjectTemplate> consoleObj = ObjectTemplate::New();
    consoleObj->Set("log", FunctionTemplate::New(_fl_jsi_console_log));
    this->m_globalObjDef->Set("console", consoleObj);
}

void JSInterpreter::InitializeVM() {
    Locker locker;
    HandleScope handle_scope;
    Handle<ObjectTemplate> global = ObjectTemplate::New();
    m_globalObjDef = Persistent<ObjectTemplate>::New(global);
    // BINDINGS BLOCK
    this->RegisterConsole();
    WindowBindings_BindToGlobal(m_globalObjDef);
    EntityBindings_BindToGlobal(m_globalObjDef);
    MeshBindings_BindToGlobal(m_globalObjDef);
    MeshRendererBindings_BindToGlobal(m_globalObjDef);
    TransformBindings_BindToGlobal(m_globalObjDef);
    ScriptableBindings_BindToGlobal(m_globalObjDef);
    KeyboardBindings_BindToGlobal(m_globalObjDef);
    ColliderBindings_BindToGlobal(m_globalObjDef);
    BoxColliderBindings_BindToGlobal(m_globalObjDef);
    CircleColliderBindings_BindToGlobal(m_globalObjDef);
    TextureBindings_BindToGlobal(m_globalObjDef);
    // BINDINGS BLOCK
    m_context = Context::New(NULL, m_globalObjDef);
    
}

void JSInterpreter::LoadFile(string& path, const string& name) {
    string content = FileIO::GetTextFile(path);
    RunString(content, name);
}

void JSInterpreter::RunString(string& contents, const string& name) {
    Locker locker;
    HandleScope current_scope;
    Context::Scope context_scope(m_context);
    TryCatch trycatch;
    Handle<String> source = String::New(contents.c_str());
    Handle<Script> script = Script::Compile(source, String::New(name.c_str()));
    if(script.IsEmpty()) {
        Handle<Value> stack = trycatch.StackTrace();
        String::Utf8Value result(stack);
        printf("Stack trace:\n%s\n", *result);
        return;
    }
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
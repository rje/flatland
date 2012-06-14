

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
#include "PhysicsSystemBindings.h"
#include "CameraBindings.h"
#include "ShaderBindings.h"
#include "FragmentShaderBindings.h"
#include "VertexShaderBindings.h"

#include <map>
typedef map<string, Persistent<Object> > ModuleMap;
typedef ModuleMap::iterator ModuleMapIter;

ModuleMap _sm_maps;

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

Handle<Value> _fl_jsi_loadfile(const Arguments& args) {
    HandleScope handle_scope;
    String::Utf8Value arg(args[0]);
    string path(*arg);
    if(args.Length() > 1 && !args[1]->IsUndefined()) {
        String::Utf8Value parentDir(args[1]);
        path = (*parentDir) + string("/") + path;
    }
    string fullPath = FileIO::GetExpandedPath(path);
    string directory = FileIO::GetPathComponent(fullPath);
    string file = FileIO::GetFileComponent(fullPath);
    printf("--> Trying to load file: %s\n", path.c_str());
    string prepend = "(function() { var module = { exports: {}, _path: \"" + directory + "\" }; var exports = module.exports;";
    string append = " return module.exports;})();";
    string content = FileIO::GetTextFile(path);
    content = prepend + content + append;
    
    Handle<Value> results = JSInterpreter::Instance()->RunString(content, path);
    return handle_scope.Close(results);
}

void JSInterpreter::BindBuiltins() {
    this->RegisterConsole();
    
    HandleScope handle_scope;
    this->m_globalObjDef->Set("_loadfile", FunctionTemplate::New(_fl_jsi_loadfile));
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
    PhysicsSystemBindings_BindToGlobal(m_globalObjDef);
    CameraBindings_BindToGlobal(m_globalObjDef);
    ShaderBindings_BindToGlobal(m_globalObjDef);
    FragmentShaderBindings_BindToGlobal(m_globalObjDef);
    VertexShaderBindings_BindToGlobal(m_globalObjDef);
    this->BindBuiltins();
    // BINDINGS BLOCK
    m_context = Context::New(NULL, m_globalObjDef);
}

Handle<Value> JSInterpreter::LoadFile(string& path, const string& name) {
    Locker locker;
    HandleScope handle_scope;
    string content = FileIO::GetTextFile(path);
    return RunString(content, name);
}


void JSInterpreter::CallMain() {
    Locker locker;
    HandleScope handle_scope;
    Context::Scope context_scope(m_context);
    string toCall = "main();";
    RunString(toCall, "entry");
}

Handle<Value> JSInterpreter::RunString(string& contents, const string& name) {
    Locker locker;
    HandleScope handle_scope;
    Context::Scope context_scope(m_context);
    TryCatch trycatch;
    Handle<String> source = String::New(contents.c_str());
    Handle<Script> script = Script::Compile(source, String::New(name.c_str()));
    if(script.IsEmpty()) {
        Handle<Value> stack = trycatch.StackTrace();
        String::Utf8Value result(stack);
        printf("Stack trace:\n%s\n", *result);
        return Undefined();
    }
    Handle<Value> val = script->Run();
    if(val.IsEmpty()) {
        Handle<Value> stack = trycatch.StackTrace();
        String::Utf8Value result(stack);
        printf("Stack trace:\n%s\n", *result);
    }
    return handle_scope.Close(val);
}
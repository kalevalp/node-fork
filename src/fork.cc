// hello.cc
#include <node.h>
#include <unistd.h>
#include <string> 
#include <sys/wait.h>

namespace nodefork {
  
  using v8::FunctionCallbackInfo;
  using v8::Isolate;
  using v8::Local;
  using v8::Object;
  using v8::Number;
  using v8::Value;
  
  void Fork(const FunctionCallbackInfo<Value>& args) {
    Isolate* isolate = args.GetIsolate();
    
    pid_t pid = fork();

    Local<Number> num = Number::New(isolate, pid);
    
    args.GetReturnValue().Set(num);    
    
  }
  
  void Wait(const FunctionCallbackInfo<Value>& args) {
    int status;

    wait(&status);
  }
  
  void init(Local<Object> exports) {
    NODE_SET_METHOD(exports, "fork", Fork);
    NODE_SET_METHOD(exports, "wait", Wait);
  }
  
  NODE_MODULE(hello_world, init)
  
}  // namespace fork

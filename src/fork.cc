// hello.cc
#include <node.h>
#include <unistd.h>
#include <string.h> 
#include <sys/wait.h>
#include <iostream>

namespace nodefork {
  
  using v8::FunctionCallbackInfo;
  using v8::Isolate;
  using v8::Local;
  using v8::Object;
  using v8::Number;
  using v8::String;
  using v8::Value;
  using v8::Exception;
  
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

  void Pipe(const FunctionCallbackInfo<Value>& args) {
    int pfds[2];

    pipe(pfds);
    
    Isolate* isolate = args.GetIsolate();

    Local<Object> obj = Object::New(isolate);
    
    obj->Set(String::NewFromUtf8(isolate, "write_end"), Number::New(isolate, pfds[1]));
    obj->Set(String::NewFromUtf8(isolate, "read_end"),  Number::New(isolate, pfds[0]));

    args.GetReturnValue().Set(obj);
  }
  
  void WriteToPipe(const FunctionCallbackInfo<Value>& args) {
//    Isolate* isolate = args.GetIsolate();
    
    int pipe = args[0]->NumberValue();
    
    char* message;
    
    v8::String::Utf8Value str(args[1]->ToString());
    message = *str;

    //char* message = *String::Utf8Value(args[1]->ToString());
    //char message[6] = "abcde";
    
    std::cout << message;std::cout << "\n";
    std::cout << "    ";std::cout << strlen(message);std::cout << "\n";    
    
    
    write(pipe, message, strlen(message));
    close(pipe);

  }

  void ReadFromPipe(const FunctionCallbackInfo<Value>& args) { 
    Isolate* isolate = args.GetIsolate();
    
    int pipe = args[0]->NumberValue();

    char buf[16];

    // while (read(pipe, &buf, 1) > 0) {
    //   std::cout << buf;
    //   //std::cout << "a";
    // }

    read(pipe, &buf, 16);
    
    std::cout << buf;
    //close(pipe);

    //read(pipe, buf, 20);

    args.GetReturnValue().Set(String::NewFromUtf8(isolate,buf));

  }
  

  void init(Local<Object> exports) {
    NODE_SET_METHOD(exports, "fork", Fork);
    NODE_SET_METHOD(exports, "wait", Wait);
    NODE_SET_METHOD(exports, "read", ReadFromPipe);
    NODE_SET_METHOD(exports, "write", WriteToPipe);
    NODE_SET_METHOD(exports, "pipe", Pipe);
  }
  
  NODE_MODULE(hello_world, init)
  
}  // namespace fork

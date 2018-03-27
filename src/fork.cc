// hello.cc
#include <node.h>
#include <unistd.h>
#include <string.h>
#include <sstream>
#include <sys/wait.h>
#include <iostream>

__asm__(".symver string,string@GLIBC_2.17");

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
    int pipe = args[0]->NumberValue();
    
    char* message;
    
    v8::String::Utf8Value str(args[1]->ToString());
    message = *str;

    write(pipe, message, strlen(message));

  }

  void ReadFromPipe(const FunctionCallbackInfo<Value>& args) { 
    Isolate* isolate = args.GetIsolate();
    
    int pipe = args[0]->NumberValue();

    char buf[100];
    
    char* res;
    char* tmpstr;

    int iter = 0;
    
    while (true) {
      int rcount = read(pipe, buf, 100);
      iter++;
      
      if (rcount > 0) {
        if (rcount < 100) {
          buf[rcount] = '\0';
        }
        
        if (iter == 1) {
          res = (char*) malloc(sizeof(char)*100*iter);
          *res = '\0';
        } else {
          tmpstr = res;
          res = (char*) malloc(sizeof(char)*100*iter);     
          strcpy(res,tmpstr);    
          free(tmpstr);
        }
        strcat(res, buf);
        
      } else break;
      



      // std::cout << res;
      // std::cout << buf;
    }
    
    // // std::string str = "";
    // std::ostringstream os;
    // // os << "dec: " << 15 << " hex: " << std::hex << 15 << endl;
    
    // // str.push_back(buf);

    // // while (true) {
    // //   int read_no = read(pipe, &buf, 1);
    // //   if (read_no > 0) {
    // //     str = str + buf;
    // //   } else {
    // //     break;
    // //   }
    // // }

    // while (read(pipe, &buf, 1) > 0) {
    //   // if (buf) {
    //   //str = str + buf;
    //   // } else {
    //   //   buf = 'a';
    //   // }
    //   // str.push_back(buf);

    //   // str.append(&buf);
    //   os << buf;
    // }

    args.GetReturnValue().Set(String::NewFromUtf8(isolate,res));//os.str().c_str()));//str.c_str()));//buf));
  }

  void Close(const FunctionCallbackInfo<Value>& args) { 
    int pipe = args[0]->NumberValue();

    close(pipe);
  }

  void init(Local<Object> exports) {
    NODE_SET_METHOD(exports, "fork", Fork);
    NODE_SET_METHOD(exports, "wait", Wait);
    NODE_SET_METHOD(exports, "read", ReadFromPipe);
    NODE_SET_METHOD(exports, "write", WriteToPipe);
    NODE_SET_METHOD(exports, "pipe", Pipe);
    NODE_SET_METHOD(exports, "close", Close);
  }
  
  NODE_MODULE(hello_world, init)
  
}  // namespace fork

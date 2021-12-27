#include<node/node.h>
void GLFW_Initialize(v8::Local<v8::Object> exports);
void Initialize(v8::Local<v8::Object> exports)
{
    GLFW_Initialize(exports);
}
NODE_MODULE(NODE_GYPE_MODULE_NAME, Initialize);
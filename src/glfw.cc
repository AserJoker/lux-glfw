#include <node/node.h>
#include <iostream>
#include "glfw/glfw3.h"
#include <functional>
#include <map>
#include "long.hpp"
#define EXPORT_WITH_NAME(NAME, FUNCTION) NODE_SET_METHOD(exports, NAME, FUNCTION)
#define EXPORT(FUNCTION) EXPORT_WITH_NAME(#FUNCTION, FUNCTION)
#define NODE_FUNC(FUNC) void FUNC(const v8::FunctionCallbackInfo<v8::Value> &info)

NODE_FUNC(CXX_glfwInit)
{
    info.GetReturnValue().Set(v8::Number::New(info.GetIsolate(), glfwInit()));
}
NODE_FUNC(CXX_glfwTerminate)
{
    glfwTerminate();
}
NODE_FUNC(CXX_glfwCreateWindow)
{
    GLFWwindow *win = 0;
    v8::Isolate *isolate = info.GetIsolate();
    v8::Local<v8::Context> context = isolate->GetCurrentContext();
    double width = info[0]->NumberValue(context).FromMaybe(0);
    double height = info[1]->NumberValue(context).FromMaybe(0);
    v8::Local<v8::String> title = info[2]->ToString(context).FromMaybe(v8::String::NewFromUtf8(isolate, "no title").ToLocalChecked());
    v8::String::Utf8Value value(isolate, title);
    v8::Local<v8::Object> monitor = info[3].As<v8::Object>();
    unsigned long lptr_monitor = monitor == v8::Undefined(isolate) ? 0 : fromJSLong(isolate, monitor);
    v8::Local<v8::Object> share = info[4].As<v8::Object>();
    unsigned long lptr_share = share == v8::Undefined(isolate) ? 0 : fromJSLong(isolate, share);
    win = glfwCreateWindow((int)width, (int)height, *value, (GLFWmonitor *)lptr_monitor, (GLFWwindow *)lptr_share);
    unsigned long lptr_win = (unsigned long)win;
    info.GetReturnValue().Set(JsLong(info.GetIsolate(), lptr_win));
}
NODE_FUNC(CXX_glfwPollEvents)
{
    glfwPollEvents();
}
NODE_FUNC(CXX_glfwWindowShouldClose)
{
    v8::Isolate *isolate = info.GetIsolate();
    GLFWwindow *win = 0;
    v8::Local<v8::Object> window = info[0].As<v8::Object>();
    unsigned long lptr_win = fromJSLong(isolate, window);
    win = (GLFWwindow *)lptr_win;
    info.GetReturnValue().Set(v8::Boolean::New(isolate, glfwWindowShouldClose(win)));
}

NODE_FUNC(CXX_glfwGetKey)
{
    v8::Isolate *isolate = info.GetIsolate();
    GLFWwindow *win = 0;
    v8::Local<v8::Object> window = info[0].As<v8::Object>();
    unsigned long lptr_win = fromJSLong(isolate, window);
    win = (GLFWwindow *)lptr_win;
    double key = info[1]->NumberValue(isolate->GetCurrentContext()).FromMaybe(0);
    info.GetReturnValue().Set(v8::Number::New(isolate, glfwGetKey(win, (int)key)));
}

NODE_FUNC(CXX_glfwGetMouseButton)
{
    v8::Isolate *isolate = info.GetIsolate();
    GLFWwindow *win = 0;
    v8::Local<v8::Object> window = info[0].As<v8::Object>();
    unsigned long lptr_win = fromJSLong(isolate, window);
    win = (GLFWwindow *)lptr_win;
    double key = info[1]->NumberValue(isolate->GetCurrentContext()).FromMaybe(0);
    info.GetReturnValue().Set(v8::Number::New(isolate, glfwGetMouseButton(win, (int)key)));
}

NODE_FUNC(CXX_glfwGetClipboardString)
{
    v8::Isolate *isolate = info.GetIsolate();
    GLFWwindow *win = 0;
    v8::Local<v8::Object> window = info[0].As<v8::Object>();
    unsigned long lptr_win = fromJSLong(isolate, window);
    win = (GLFWwindow *)lptr_win;
    info.GetReturnValue().Set(v8::String::NewFromUtf8(isolate, glfwGetClipboardString(win)).ToLocalChecked());
}

NODE_FUNC(CXX_glfwGetCurrentContext)
{
    v8::Isolate *isolate = info.GetIsolate();
    info.GetReturnValue().Set(JsLong(isolate, (unsigned long)glfwGetCurrentContext()));
}

NODE_FUNC(CXX_glfwGetCursorPos)
{
    v8::Isolate *isolate = info.GetIsolate();
    v8::Local<v8::Context> context = isolate->GetCurrentContext();
    double x, y;
    GLFWwindow *win = 0;
    v8::Local<v8::Object> window = info[0].As<v8::Object>();
    unsigned long lptr_win = fromJSLong(isolate, window);
    win = (GLFWwindow *)lptr_win;
    glfwGetCursorPos(win, &x, &y);
    v8::Local<v8::Object> res = v8::Object::New(isolate);
    res->Set(context, v8::String::NewFromUtf8(isolate, "x").ToLocalChecked(), v8::Number::New(isolate, x)).Check();
    res->Set(context, v8::String::NewFromUtf8(isolate, "y").ToLocalChecked(), v8::Number::New(isolate, x)).Check();
    info.GetReturnValue().Set(res);
}

NODE_FUNC(CXX_glfwGetError)
{
    v8::Isolate *isolate = info.GetIsolate();
    v8::Local<v8::Context> context = isolate->GetCurrentContext();
    char *desc = 0;
    int state = glfwGetError((const char **)&desc);
    v8::Local<v8::Object> res = v8::Object::New(isolate);
    res->Set(context, v8::String::NewFromUtf8(isolate, "state").ToLocalChecked(), v8::Number::New(isolate, state)).Check();
    if (desc)
    {
        res->Set(context, v8::String::NewFromUtf8(isolate, "description").ToLocalChecked(), v8::String::NewFromUtf8(isolate, desc).ToLocalChecked()).Check();
    }
    info.GetReturnValue().Set(res);
}

NODE_FUNC(CXX_glfwGetFramebufferSize)
{
    int width = 0, height = 0;
    v8::Isolate *isolate = info.GetIsolate();
    v8::Local<v8::Context> context = isolate->GetCurrentContext();
    GLFWwindow *win = 0;
    v8::Local<v8::Object> window = info[0].As<v8::Object>();
    unsigned long lptr_win = fromJSLong(isolate, window);
    win = (GLFWwindow *)lptr_win;
    glfwGetFramebufferSize(win, &width, &height);
    v8::Local<v8::Object> res = v8::Object::New(isolate);
    res->Set(context, v8::String::NewFromUtf8(isolate, "width").ToLocalChecked(), v8::Number::New(isolate, width)).Check();
    res->Set(context, v8::String::NewFromUtf8(isolate, "height").ToLocalChecked(), v8::Number::New(isolate, height)).Check();
    info.GetReturnValue().Set(res);
}

NODE_FUNC(CXX_glfwGetGamepadName)
{
    v8::Isolate *isolate = info.GetIsolate();
    v8::Local<v8::Context> context = isolate->GetCurrentContext();
    double jid = info[0]->NumberValue(context).FromMaybe(0);
    const char *name = glfwGetGamepadName((int)jid);
    info.GetReturnValue().Set(v8::String::NewFromUtf8(isolate, name == 0 ? "" : name).ToLocalChecked());
}

NODE_FUNC(CXX_glfwGetGamepadState)
{
    v8::Isolate *isolate = info.GetIsolate();
    v8::Local<v8::Context> context = isolate->GetCurrentContext();
    GLFWgamepadstate state;
    double jid = info[0]->NumberValue(context).FromMaybe(0);
    int result = glfwGetGamepadState(jid, &state);
    v8::Local<v8::Array> axes = v8::Array::New(isolate, 6);
    for (int i = 0; i < 6; i++)
    {
        axes->Set(context, i, v8::Number::New(isolate, state.axes[i])).Check();
    }
    v8::Local<v8::Array> buttons = v8::Array::New(isolate, 15);
    for (int i = 0; i < 15; i++)
    {
        buttons->Set(context, i, v8::Number::New(isolate, state.buttons[i])).Check();
    }
    v8::Local<v8::Object> res = v8::Object::New(isolate);
    res->Set(context, v8::String::NewFromUtf8(isolate, "axes").ToLocalChecked(), axes).Check();
    res->Set(context, v8::String::NewFromUtf8(isolate, "buttons").ToLocalChecked(), buttons).Check();
    res->Set(context, v8::String::NewFromUtf8(isolate, "result").ToLocalChecked(), v8::Number::New(isolate, result)).Check();
    info.GetReturnValue().Set(res);
}

NODE_FUNC(CXX_glfwGetGammaRamp)
{
    v8::Isolate *isolate = info.GetIsolate();
    v8::Local<v8::Context> context = isolate->GetCurrentContext();
    GLFWmonitor *monitor = 0;
    v8::Local<v8::Object> ptr = info[0].As<v8::Object>();
    unsigned long lptr = fromJSLong(isolate, ptr);
    monitor = (GLFWmonitor *)lptr;
    const GLFWgammaramp *g = glfwGetGammaRamp(monitor);
    v8::Local<v8::Object> result = v8::Object::New(isolate);
    v8::Local<v8::Array> red = v8::Array::New(isolate, g->size);
    v8::Local<v8::Array> blue = v8::Array::New(isolate, g->size);
    v8::Local<v8::Array> green = v8::Array::New(isolate, g->size);

    for (unsigned int i = 0; i < g->size; g++)
    {
        red->Set(context, i, v8::Number::New(isolate, g->red[i])).Check();
        green->Set(context, i, v8::Number::New(isolate, g->green[i])).Check();
        blue->Set(context, i, v8::Number::New(isolate, g->blue[i])).Check();
    }
    result->Set(context, v8::String::NewFromUtf8(isolate, "red").ToLocalChecked(), red).Check();
    result->Set(context, v8::String::NewFromUtf8(isolate, "green").ToLocalChecked(), green).Check();
    result->Set(context, v8::String::NewFromUtf8(isolate, "blue").ToLocalChecked(), blue).Check();
    info.GetReturnValue().Set(result);
}

NODE_FUNC(CXX_glfwGetInputMode)
{

    v8::Isolate *isolate = info.GetIsolate();
    GLFWwindow *win = 0;
    v8::Local<v8::Object> window = info[0].As<v8::Object>();
    unsigned long lptr_win = fromJSLong(isolate, window);
    win = (GLFWwindow *)lptr_win;
    double mode = info[1]->NumberValue(isolate->GetCurrentContext()).FromMaybe(0);
    info.GetReturnValue().Set(v8::Number::New(isolate, glfwGetInputMode(win, (int)mode)));
}

NODE_FUNC(CXX_glfwGetJoystickAxes)
{
    int count = 0;
    v8::Isolate *isolate = info.GetIsolate();
    v8::Local<v8::Context> context = isolate->GetCurrentContext();
    double jid = info[0]->NumberValue(context).FromMaybe(0);
    const float *data = glfwGetJoystickAxes(jid, &count);
    v8::Local<v8::Array> array = v8::Array::New(isolate, count);
    for (int i = 0; i < count; i++)
    {
        array->Set(context, i, v8::Number::New(isolate, data[i])).Check();
    }
    info.GetReturnValue().Set(array);
}

NODE_FUNC(CXX_glfwGetJoystickButtons)
{
    int count = 0;
    v8::Isolate *isolate = info.GetIsolate();
    v8::Local<v8::Context> context = isolate->GetCurrentContext();
    double jid = info[0]->NumberValue(context).FromMaybe(0);
    const unsigned char *data = glfwGetJoystickButtons(jid, &count);
    v8::Local<v8::Array> array = v8::Array::New(isolate, count);
    for (int i = 0; i < count; i++)
    {
        array->Set(context, i, v8::Number::New(isolate, data[i])).Check();
    }
    info.GetReturnValue().Set(array);
}

NODE_FUNC(CXX_glfwGetJoystickGUID)
{
    v8::Isolate *isolate = info.GetIsolate();
    v8::Local<v8::Context> context = isolate->GetCurrentContext();
    double jid = info[0]->NumberValue(context).FromMaybe(0);
    const char *guid = glfwGetJoystickGUID((int)jid);
    info.GetReturnValue().Set(v8::String::NewFromUtf8(isolate, guid).ToLocalChecked());
}

NODE_FUNC(CXX_glfwGetJoystickHats)
{
    int count = 0;
    v8::Isolate *isolate = info.GetIsolate();
    v8::Local<v8::Context> context = isolate->GetCurrentContext();
    double jid = info[0]->NumberValue(context).FromMaybe(0);
    const unsigned char *data = glfwGetJoystickHats(jid, &count);
    v8::Local<v8::Array> array = v8::Array::New(isolate, count);
    for (int i = 0; i < count; i++)
    {
        array->Set(context, i, v8::Number::New(isolate, data[i])).Check();
    }
    info.GetReturnValue().Set(array);
}

NODE_FUNC(CXX_glfwGetJoystickName)
{
    v8::Isolate *isolate = info.GetIsolate();
    v8::Local<v8::Context> context = isolate->GetCurrentContext();
    double jid = info[0]->NumberValue(context).FromMaybe(0);
    const char *name = glfwGetJoystickName((int)jid);
    info.GetReturnValue().Set(v8::String::NewFromUtf8(isolate, name).ToLocalChecked());
}

NODE_FUNC(CXX_glfwGetKeyName)
{
    v8::Isolate *isolate = info.GetIsolate();
    v8::Local<v8::Context> context = isolate->GetCurrentContext();
    double key = info[0]->NumberValue(context).FromMaybe(0);
    double scancode = info[1]->NumberValue(context).FromMaybe(0);
    const char *name = glfwGetKeyName(key, scancode);
    info.GetReturnValue().Set(v8::String::NewFromUtf8(isolate, name).ToLocalChecked());
}

NODE_FUNC(CXX_glfwGetKeyScancode)
{
    v8::Isolate *isolate = info.GetIsolate();
    v8::Local<v8::Context> context = isolate->GetCurrentContext();
    double key = info[0]->NumberValue(context).FromMaybe(0);
    info.GetReturnValue().Set(v8::Number::New(isolate, glfwGetKeyScancode(key)));
}

NODE_FUNC(CXX_glfwGetMonitorContentScale)
{
    v8::Isolate *isolate = info.GetIsolate();
    v8::Local<v8::Context> context = isolate->GetCurrentContext();
    float x = 1, y = 1;
    GLFWmonitor *monitor = 0;
    v8::Local<v8::Object> ptr = info[0].As<v8::Object>();
    unsigned long lptr = fromJSLong(isolate, ptr);
    monitor = (GLFWmonitor *)lptr;
    glfwGetMonitorContentScale(monitor, &x, &y);
    v8::Local<v8::Object> obj = v8::Object::New(isolate);
    obj->Set(context, v8::String::NewFromUtf8(isolate, "xscale").ToLocalChecked(), v8::Number::New(isolate, x)).Check();
    obj->Set(context, v8::String::NewFromUtf8(isolate, "yscale").ToLocalChecked(), v8::Number::New(isolate, y)).Check();
    info.GetReturnValue().Set(obj);
}

NODE_FUNC(CXX_glfwGetMonitorName)
{
    v8::Isolate *isolate = info.GetIsolate();
    GLFWmonitor *monitor = 0;
    v8::Local<v8::Object> ptr = info[0].As<v8::Object>();
    unsigned long lptr = fromJSLong(isolate, ptr);
    monitor = (GLFWmonitor *)lptr;
    info.GetReturnValue().Set(v8::String::NewFromUtf8(isolate, glfwGetMonitorName(monitor)).ToLocalChecked());
}

NODE_FUNC(CXX_glfwGetMonitorPhysicalSize)
{
    v8::Isolate *isolate = info.GetIsolate();
    v8::Local<v8::Context> context = isolate->GetCurrentContext();
    GLFWmonitor *monitor = 0;
    v8::Local<v8::Object> ptr = info[0].As<v8::Object>();
    unsigned long lptr = fromJSLong(isolate, ptr);
    monitor = (GLFWmonitor *)lptr;
    int w, h;
    glfwGetMonitorPhysicalSize(monitor, &w, &h);
    v8::Local<v8::Object> obj = v8::Object::New(isolate);
    obj->Set(context, v8::String::NewFromUtf8(isolate, "width").ToLocalChecked(), v8::Number::New(isolate, w)).Check();
    obj->Set(context, v8::String::NewFromUtf8(isolate, "height").ToLocalChecked(), v8::Number::New(isolate, h)).Check();
    info.GetReturnValue().Set(obj);
}

NODE_FUNC(CXX_glfwGetMonitorPos)
{
    v8::Isolate *isolate = info.GetIsolate();
    v8::Local<v8::Context> context = isolate->GetCurrentContext();
    GLFWmonitor *monitor = 0;
    v8::Local<v8::Object> ptr = info[0].As<v8::Object>();
    unsigned long lptr = fromJSLong(isolate, ptr);
    monitor = (GLFWmonitor *)lptr;
    int x, y;
    glfwGetMonitorPos(monitor, &x, &y);
    v8::Local<v8::Object> obj = v8::Object::New(isolate);
    obj->Set(context, v8::String::NewFromUtf8(isolate, "x").ToLocalChecked(), v8::Number::New(isolate, x)).Check();
    obj->Set(context, v8::String::NewFromUtf8(isolate, "y").ToLocalChecked(), v8::Number::New(isolate, y)).Check();
    info.GetReturnValue().Set(obj);
}

NODE_FUNC(CXX_glfwGetMonitors)
{
    v8::Isolate *isolate = info.GetIsolate();
    v8::Local<v8::Context> context = isolate->GetCurrentContext();
    int count = 0;
    GLFWmonitor **arr_m = glfwGetMonitors(&count);
    v8::Local<v8::Array> arrays = v8::Array::New(isolate, count);
    for (int i = 0; i < count; i++)
    {
        arrays->Set(context, i, JsLong(isolate, (unsigned long)(arr_m[i]))).Check();
    }
    info.GetReturnValue().Set(arrays);
}

NODE_FUNC(CXX_glfwGetMonitorWorkarea)
{
    v8::Isolate *isolate = info.GetIsolate();
    v8::Local<v8::Context> context = isolate->GetCurrentContext();
    GLFWmonitor *monitor = 0;
    v8::Local<v8::Object> ptr = info[0].As<v8::Object>();
    unsigned long lptr = fromJSLong(isolate, ptr);
    monitor = (GLFWmonitor *)lptr;
    int x, y, w, h;
    glfwGetMonitorWorkarea(monitor, &x, &y, &w, &h);
    v8::Local<v8::Object> obj = v8::Object::New(isolate);
    obj->Set(context, v8::String::NewFromUtf8(isolate, "x").ToLocalChecked(), v8::Number::New(isolate, x)).Check();
    obj->Set(context, v8::String::NewFromUtf8(isolate, "y").ToLocalChecked(), v8::Number::New(isolate, y)).Check();
    obj->Set(context, v8::String::NewFromUtf8(isolate, "width").ToLocalChecked(), v8::Number::New(isolate, w)).Check();
    obj->Set(context, v8::String::NewFromUtf8(isolate, "height").ToLocalChecked(), v8::Number::New(isolate, h)).Check();
    info.GetReturnValue().Set(obj);
}
NODE_FUNC(CXX_glfwGetPrimaryMonitor)
{
    v8::Isolate *isolate = info.GetIsolate();
    info.GetReturnValue().Set(JsLong(isolate, (unsigned long)glfwGetPrimaryMonitor()));
}

NODE_FUNC(CXX_glfwGetProcAddress)
{
    v8::Isolate *isolate = info.GetIsolate();
    v8::Local<v8::Context> context = isolate->GetCurrentContext();
    v8::Local<v8::String> title = info[0]->ToString(context).FromMaybe(v8::String::NewFromUtf8(isolate, "").ToLocalChecked());
    v8::String::Utf8Value value(isolate, title);
    GLFWglproc addr = glfwGetProcAddress(*value);
    info.GetReturnValue().Set(JsLong(isolate, (unsigned long)addr));
}

NODE_FUNC(CXX_glfwGetRequiredInstanceExtensions)
{
    v8::Isolate *isolate = info.GetIsolate();
    v8::Local<v8::Context> context = isolate->GetCurrentContext();
    uint32_t count = 0;
    const char **deps = glfwGetRequiredInstanceExtensions(&count);
    v8::Local<v8::Array> arr = v8::Array::New(isolate, count);
    for (unsigned int i = 0; i < count; i++)
    {
        arr->Set(context, i, v8::String::NewFromUtf8(isolate, deps[i]).ToLocalChecked()).Check();
    }
    info.GetReturnValue().Set(arr);
}
NODE_FUNC(CXX_glfwGetTime)
{
    v8::Isolate *isolate = info.GetIsolate();
    info.GetReturnValue().Set(v8::Number::New(isolate, glfwGetTime()));
}
NODE_FUNC(CXX_glfwGetTimerFrequency)
{
    v8::Isolate *isolate = info.GetIsolate();
    info.GetReturnValue().Set(v8::Number::New(isolate, glfwGetTimerFrequency()));
}

NODE_FUNC(CXX_glfwGetTimerValue)
{
    v8::Isolate *isolate = info.GetIsolate();
    info.GetReturnValue().Set(v8::Number::New(isolate, glfwGetTimerValue()));
}

NODE_FUNC(CXX_glfwGetVersion)
{
    v8::Isolate *isolate = info.GetIsolate();
    v8::Local<v8::Context> context = isolate->GetCurrentContext();
    int major, minor, revision;
    glfwGetVersion(&major, &minor, &revision);
    v8::Local<v8::Object> obj = v8::Object::New(isolate);
    obj->Set(context, v8::String::NewFromUtf8(isolate, "major").ToLocalChecked(), v8::Number::New(isolate, major)).Check();
    obj->Set(context, v8::String::NewFromUtf8(isolate, "minor").ToLocalChecked(), v8::Number::New(isolate, minor)).Check();
    obj->Set(context, v8::String::NewFromUtf8(isolate, "revision").ToLocalChecked(), v8::Number::New(isolate, revision)).Check();
    info.GetReturnValue().Set(obj);
}

NODE_FUNC(CXX_glfwGetVersionString)
{
    v8::Isolate *isolate = info.GetIsolate();
    info.GetReturnValue().Set(v8::String::NewFromUtf8(isolate, glfwGetVersionString()).ToLocalChecked());
}

NODE_FUNC(CXX_glfwGetVideoMode)
{
    v8::Isolate *isolate = info.GetIsolate();
    v8::Local<v8::Context> context = isolate->GetCurrentContext();
    GLFWmonitor *monitor = 0;
    v8::Local<v8::Object> ptr = info[0].As<v8::Object>();
    unsigned long lptr = fromJSLong(isolate, ptr);
    monitor = (GLFWmonitor *)lptr;
    const GLFWvidmode *mode = glfwGetVideoMode(monitor);
    v8::Local<v8::Object> obj = v8::Object::New(isolate);
    obj->Set(context, v8::String::NewFromUtf8(isolate, "redBits").ToLocalChecked(), v8::Number::New(isolate, mode->redBits)).Check();
    obj->Set(context, v8::String::NewFromUtf8(isolate, "greenBits").ToLocalChecked(), v8::Number::New(isolate, mode->greenBits)).Check();
    obj->Set(context, v8::String::NewFromUtf8(isolate, "blueBits").ToLocalChecked(), v8::Number::New(isolate, mode->blueBits)).Check();
    obj->Set(context, v8::String::NewFromUtf8(isolate, "refreshRate").ToLocalChecked(), v8::Number::New(isolate, mode->refreshRate)).Check();
    obj->Set(context, v8::String::NewFromUtf8(isolate, "width").ToLocalChecked(), v8::Number::New(isolate, mode->width)).Check();
    obj->Set(context, v8::String::NewFromUtf8(isolate, "height").ToLocalChecked(), v8::Number::New(isolate, mode->height)).Check();
    info.GetReturnValue().Set(obj);
}

NODE_FUNC(CXX_glfwGetVideoModes)
{
    v8::Isolate *isolate = info.GetIsolate();
    v8::Local<v8::Context> context = isolate->GetCurrentContext();
    GLFWmonitor *monitor = 0;
    v8::Local<v8::Object> ptr = info[0].As<v8::Object>();
    unsigned long lptr = fromJSLong(isolate, ptr);
    monitor = (GLFWmonitor *)lptr;
    int count = 0;
    const GLFWvidmode *modes = glfwGetVideoModes(monitor, &count);
    v8::Local<v8::Array> arr = v8::Array::New(isolate, count);
    for (int i = 0; i < count; i++)
    {
        const GLFWvidmode *mode = modes + i;
        v8::Local<v8::Object> obj = v8::Object::New(isolate);
        obj->Set(context, v8::String::NewFromUtf8(isolate, "redBits").ToLocalChecked(), v8::Number::New(isolate, mode->redBits)).Check();
        obj->Set(context, v8::String::NewFromUtf8(isolate, "greenBits").ToLocalChecked(), v8::Number::New(isolate, mode->greenBits)).Check();
        obj->Set(context, v8::String::NewFromUtf8(isolate, "blueBits").ToLocalChecked(), v8::Number::New(isolate, mode->blueBits)).Check();
        obj->Set(context, v8::String::NewFromUtf8(isolate, "refreshRate").ToLocalChecked(), v8::Number::New(isolate, mode->refreshRate)).Check();
        obj->Set(context, v8::String::NewFromUtf8(isolate, "width").ToLocalChecked(), v8::Number::New(isolate, mode->width)).Check();
        obj->Set(context, v8::String::NewFromUtf8(isolate, "height").ToLocalChecked(), v8::Number::New(isolate, mode->height)).Check();
        arr->Set(context, i, obj).Check();
    }
    info.GetReturnValue().Set(arr);
}

NODE_FUNC(CXX_glfwGetWindowAttrib)
{

    v8::Isolate *isolate = info.GetIsolate();
    v8::Local<v8::Context> context = isolate->GetCurrentContext();
    GLFWwindow *win = 0;
    v8::Local<v8::Object> ptr = info[0].As<v8::Object>();
    unsigned long lptr = fromJSLong(isolate, ptr);
    win = (GLFWwindow *)lptr;
    double attr = info[1]->NumberValue(context).FromMaybe(0);
    info.GetReturnValue().Set(v8::Number::New(isolate, attr));
}

NODE_FUNC(CXX_glfwGetWindowContentScale)
{
    v8::Isolate *isolate = info.GetIsolate();
    v8::Local<v8::Context> context = isolate->GetCurrentContext();
    GLFWwindow *win = 0;
    v8::Local<v8::Object> ptr = info[0].As<v8::Object>();
    unsigned long lptr = fromJSLong(isolate, ptr);
    win = (GLFWwindow *)lptr;
    float x, y;
    glfwGetWindowContentScale(win, &x, &y);
    v8::Local<v8::Object> obj = v8::Object::New(isolate);
    obj->Set(context, v8::String::NewFromUtf8(isolate, "xscale").ToLocalChecked(), v8::Number::New(isolate, x)).Check();
    obj->Set(context, v8::String::NewFromUtf8(isolate, "yscale").ToLocalChecked(), v8::Number::New(isolate, y)).Check();
    info.GetReturnValue().Set(obj);
}
NODE_FUNC(CXX_glfwGetWindowFrameSize)
{

    v8::Isolate *isolate = info.GetIsolate();
    v8::Local<v8::Context> context = isolate->GetCurrentContext();
    GLFWwindow *win = 0;
    v8::Local<v8::Object> ptr = info[0].As<v8::Object>();
    unsigned long lptr = fromJSLong(isolate, ptr);
    win = (GLFWwindow *)lptr;
    int l, t, r, b;
    glfwGetWindowFrameSize(win, &l, &t, &r, &b);
    v8::Local<v8::Object> obj = v8::Object::New(isolate);
    obj->Set(context, v8::String::NewFromUtf8(isolate, "left").ToLocalChecked(), v8::Number::New(isolate, l)).Check();
    obj->Set(context, v8::String::NewFromUtf8(isolate, "top").ToLocalChecked(), v8::Number::New(isolate, t)).Check();
    obj->Set(context, v8::String::NewFromUtf8(isolate, "right").ToLocalChecked(), v8::Number::New(isolate, r)).Check();
    obj->Set(context, v8::String::NewFromUtf8(isolate, "bottom").ToLocalChecked(), v8::Number::New(isolate, b)).Check();
    info.GetReturnValue().Set(obj);
}

NODE_FUNC(CXX_glfwGetWindowMonitor)
{

    v8::Isolate *isolate = info.GetIsolate();
    GLFWwindow *win = 0;
    v8::Local<v8::Object> ptr = info[0].As<v8::Object>();
    unsigned long lptr = fromJSLong(isolate, ptr);
    win = (GLFWwindow *)lptr;
    GLFWmonitor *monitor = glfwGetWindowMonitor(win);
    info.GetReturnValue().Set(JsLong(isolate, (unsigned long)monitor));
}

NODE_FUNC(CXX_glfwGetWindowOpacity)
{
    v8::Isolate *isolate = info.GetIsolate();
    GLFWwindow *win = 0;
    v8::Local<v8::Object> ptr = info[0].As<v8::Object>();
    unsigned long lptr = fromJSLong(isolate, ptr);
    win = (GLFWwindow *)lptr;
    info.GetReturnValue().Set(v8::Number::New(isolate, glfwGetWindowOpacity(win)));
}

NODE_FUNC(CXX_glfwGetWindowPos)
{
    v8::Isolate *isolate = info.GetIsolate();
    v8::Local<v8::Context> context = isolate->GetCurrentContext();
    GLFWwindow *win = 0;
    v8::Local<v8::Object> ptr = info[0].As<v8::Object>();
    unsigned long lptr = fromJSLong(isolate, ptr);
    win = (GLFWwindow *)lptr;
    int x, y;
    glfwGetWindowPos(win, &x, &y);
    v8::Local<v8::Object> obj = v8::Object::New(isolate);
    obj->Set(context, v8::String::NewFromUtf8(isolate, "x").ToLocalChecked(), v8::Number::New(isolate, x)).Check();
    obj->Set(context, v8::String::NewFromUtf8(isolate, "y").ToLocalChecked(), v8::Number::New(isolate, y)).Check();
    info.GetReturnValue().Set(obj);
}

NODE_FUNC(CXX_glfwGetWindowSize)
{
    v8::Isolate *isolate = info.GetIsolate();
    v8::Local<v8::Context> context = isolate->GetCurrentContext();
    GLFWwindow *win = 0;
    v8::Local<v8::Object> ptr = info[0].As<v8::Object>();
    unsigned long lptr = fromJSLong(isolate, ptr);
    win = (GLFWwindow *)lptr;
    int w, h;
    glfwGetWindowSize(win, &w, &h);
    v8::Local<v8::Object> obj = v8::Object::New(isolate);
    obj->Set(context, v8::String::NewFromUtf8(isolate, "width").ToLocalChecked(), v8::Number::New(isolate, w)).Check();
    obj->Set(context, v8::String::NewFromUtf8(isolate, "height").ToLocalChecked(), v8::Number::New(isolate, h)).Check();
    info.GetReturnValue().Set(obj);
}

NODE_FUNC(CXX_glfwCreateCursor)
{
    v8::Isolate *isolate = info.GetIsolate();
    v8::Local<v8::Object> ptr = info[0].As<v8::Object>();
    GLFWimage *img = (GLFWimage *)fromJSLong(isolate, ptr);
    double x = info[1]->NumberValue(isolate->GetCurrentContext()).FromMaybe(0);
    double y = info[2]->NumberValue(isolate->GetCurrentContext()).FromMaybe(0);
    GLFWcursor *cursor = glfwCreateCursor(img, x, y);
    info.GetReturnValue().Set(JsLong(isolate, (unsigned long)cursor));
}

NODE_FUNC(CXX_glfwCreateStandardCursor)
{
    v8::Isolate *isolate = info.GetIsolate();
    double shape = info[0]->NumberValue(isolate->GetCurrentContext()).FromMaybe(0);
    GLFWcursor *cursor = glfwCreateStandardCursor(shape);
    info.GetReturnValue().Set(JsLong(isolate, (unsigned long)cursor));
}

NODE_FUNC(CXX_glfwDefaultWindowHints)
{
    glfwDefaultWindowHints();
}

NODE_FUNC(CXX_glfwDestroyCursor)
{
    v8::Isolate *isolate = info.GetIsolate();
    v8::Local<v8::Object> ptr = info[0].As<v8::Object>();
    GLFWcursor *cursor = (GLFWcursor *)fromJSLong(isolate, ptr);
    glfwDestroyCursor(cursor);
}

NODE_FUNC(CXX_glfwDestroyWindow)
{
    v8::Isolate *isolate = info.GetIsolate();
    v8::Local<v8::Object> ptr = info[0].As<v8::Object>();
    GLFWwindow *win = (GLFWwindow *)fromJSLong(isolate, ptr);
    glfwDestroyWindow(win);
}

NODE_FUNC(CXX_glfwExtensionSupported)
{

    v8::Isolate *isolate = info.GetIsolate();
    v8::Local<v8::String> extension = info[0]->ToString(isolate->GetCurrentContext()).FromMaybe(v8::String::NewFromUtf8(isolate, "").ToLocalChecked());
    v8::String::Utf8Value value(isolate, extension);
    info.GetReturnValue().Set(v8::Number::New(isolate, glfwExtensionSupported(*value)));
}

NODE_FUNC(CXX_glfwFocusWindow)
{
    v8::Isolate *isolate = info.GetIsolate();
    v8::Local<v8::Object> ptr = info[0].As<v8::Object>();
    GLFWwindow *win = (GLFWwindow *)fromJSLong(isolate, ptr);
    glfwFocusWindow(win);
}

NODE_FUNC(CXX_glfwHideWindow)
{
    v8::Isolate *isolate = info.GetIsolate();
    v8::Local<v8::Object> ptr = info[0].As<v8::Object>();
    GLFWwindow *win = (GLFWwindow *)fromJSLong(isolate, ptr);
    glfwHideWindow(win);
}

NODE_FUNC(CXX_glfwIconifyWindow)
{
    v8::Isolate *isolate = info.GetIsolate();
    v8::Local<v8::Object> ptr = info[0].As<v8::Object>();
    GLFWwindow *win = (GLFWwindow *)fromJSLong(isolate, ptr);
    glfwIconifyWindow(win);
}

NODE_FUNC(CXX_glfwInitHint)
{

    v8::Isolate *isolate = info.GetIsolate();
    double hint = info[0]->NumberValue(isolate->GetCurrentContext()).FromMaybe(0);
    double value = info[1]->NumberValue(isolate->GetCurrentContext()).FromMaybe(0);
    glfwInitHint((int)hint, (int)value);
}

NODE_FUNC(CXX_glfwJoystickIsGamepad)
{

    v8::Isolate *isolate = info.GetIsolate();
    double jid = info[0]->NumberValue(isolate->GetCurrentContext()).FromMaybe(0);
    info.GetReturnValue().Set(v8::Number::New(isolate, glfwJoystickIsGamepad(jid)));
}

NODE_FUNC(CXX_glfwJoystickPresent)
{
    v8::Isolate *isolate = info.GetIsolate();
    double jid = info[0]->NumberValue(isolate->GetCurrentContext()).FromMaybe(0);
    info.GetReturnValue().Set(v8::Number::New(isolate, glfwJoystickPresent(jid)));
}

NODE_FUNC(CXX_glfwMakeContextCurrent)
{
    v8::Isolate *isolate = info.GetIsolate();
    v8::Local<v8::Object> ptr = info[0].As<v8::Object>();
    GLFWwindow *win = (GLFWwindow *)fromJSLong(isolate, ptr);
    glfwMakeContextCurrent(win);
}

NODE_FUNC(CXX_glfwMaximizeWindow)
{
    v8::Isolate *isolate = info.GetIsolate();
    v8::Local<v8::Object> ptr = info[0].As<v8::Object>();
    GLFWwindow *win = (GLFWwindow *)fromJSLong(isolate, ptr);
    glfwMaximizeWindow(win);
}

NODE_FUNC(CXX_glfwPostEmptyEvent)
{
    glfwPostEmptyEvent();
}

NODE_FUNC(CXX_glfwRawMouseMotionSupported)
{
    v8::Isolate *isolate = info.GetIsolate();
    info.GetReturnValue().Set(v8::Number::New(isolate, glfwRawMouseMotionSupported()));
}

NODE_FUNC(CXX_glfwRequestWindowAttention)
{
    v8::Isolate *isolate = info.GetIsolate();
    v8::Local<v8::Object> ptr = info[0].As<v8::Object>();
    GLFWwindow *win = (GLFWwindow *)fromJSLong(isolate, ptr);
    glfwRequestWindowAttention(win);
}

NODE_FUNC(CXX_glfwRestoreWindow)
{
    v8::Isolate *isolate = info.GetIsolate();
    v8::Local<v8::Object> ptr = info[0].As<v8::Object>();
    GLFWwindow *win = (GLFWwindow *)fromJSLong(isolate, ptr);
    glfwRestoreWindow(win);
}

NODE_FUNC(CXX_glfwSetClipboardString)
{
    v8::Isolate *isolate = info.GetIsolate();
    v8::Local<v8::Object> ptr = info[0].As<v8::Object>();
    GLFWwindow *win = (GLFWwindow *)fromJSLong(isolate, ptr);
    v8::Local<v8::String> strobj = info[1]->ToString(isolate->GetCurrentContext()).FromMaybe(v8::String::NewFromUtf8(isolate, "").ToLocalChecked());
    v8::String::Utf8Value str(isolate, strobj);
    glfwSetClipboardString(win, *str);
}

NODE_FUNC(CXX_glfwSetCursor)
{
    v8::Isolate *isolate = info.GetIsolate();
    v8::Local<v8::Object> ptr = info[0].As<v8::Object>();
    GLFWwindow *win = (GLFWwindow *)fromJSLong(isolate, ptr);
    v8::Local<v8::Object> ptr2 = info[1].As<v8::Object>();
    GLFWcursor *cursor = (GLFWcursor *)fromJSLong(isolate, ptr2);
    glfwSetCursor(win, cursor);
}

NODE_FUNC(CXX_glfwSetCursorPos)
{

    v8::Isolate *isolate = info.GetIsolate();
    v8::Local<v8::Object> ptr = info[0].As<v8::Object>();
    GLFWwindow *win = (GLFWwindow *)fromJSLong(isolate, ptr);
    glfwSetCursorPos(win, info[1]->NumberValue(isolate->GetCurrentContext()).FromMaybe(0), info[2]->NumberValue(isolate->GetCurrentContext()).FromMaybe(0));
}

NODE_FUNC(CXX_glfwSetGamma)
{
    v8::Isolate *isolate = info.GetIsolate();
    v8::Local<v8::Object> ptr = info[0].As<v8::Object>();
    GLFWmonitor *monitor = (GLFWmonitor *)fromJSLong(isolate, ptr);
    glfwSetGamma(monitor, info[1]->NumberValue(isolate->GetCurrentContext()).FromMaybe(0));
}

NODE_FUNC(CXX_glfwSetGammaRamp)
{
    v8::Isolate *isolate = info.GetIsolate();
    v8::Local<v8::Object> ptr = info[0].As<v8::Object>();
    GLFWmonitor *monitor = (GLFWmonitor *)fromJSLong(isolate, ptr);
    v8::Local<v8::Object> gammaramp = info[0].As<v8::Object>();
    GLFWgammaramp ramp;
    v8::Local<v8::Array> red = gammaramp->Get(isolate->GetCurrentContext(), v8::String::NewFromUtf8(isolate, "red").ToLocalChecked()).ToLocalChecked().As<v8::Array>();
    v8::Local<v8::Array> green = gammaramp->Get(isolate->GetCurrentContext(), v8::String::NewFromUtf8(isolate, "green").ToLocalChecked()).ToLocalChecked().As<v8::Array>();
    v8::Local<v8::Array> blue = gammaramp->Get(isolate->GetCurrentContext(), v8::String::NewFromUtf8(isolate, "blue").ToLocalChecked()).ToLocalChecked().As<v8::Array>();
    ramp.size = red->Length();
    ramp.red = new unsigned short[ramp.size];
    ramp.green = new unsigned short[ramp.size];
    ramp.blue = new unsigned short[ramp.size];
    for (unsigned i = 0; i < ramp.size; i++)
    {
        ramp.red[i] = red->Get(isolate->GetCurrentContext(), i).ToLocalChecked()->NumberValue(isolate->GetCurrentContext()).FromMaybe(0);
        ramp.green[i] = green->Get(isolate->GetCurrentContext(), i).ToLocalChecked()->NumberValue(isolate->GetCurrentContext()).FromMaybe(0);
        ramp.blue[i] = blue->Get(isolate->GetCurrentContext(), i).ToLocalChecked()->NumberValue(isolate->GetCurrentContext()).FromMaybe(0);
    }
    glfwSetGammaRamp(monitor, &ramp);
    delete[] ramp.red;
    delete[] ramp.green;
    delete[] ramp.blue;
}

NODE_FUNC(CXX_glfwSetInputMode)
{
    v8::Isolate *isolate = info.GetIsolate();
    v8::Local<v8::Object> ptr = info[0].As<v8::Object>();
    GLFWwindow *win = (GLFWwindow *)fromJSLong(isolate, ptr);
    double mode = info[1]->NumberValue(isolate->GetCurrentContext()).FromMaybe(0);
    double value = info[2]->NumberValue(isolate->GetCurrentContext()).FromMaybe(0);
    glfwSetInputMode(win, mode, value);
}

NODE_FUNC(CXX_glfwSetTime)
{
    v8::Isolate *isolate = info.GetIsolate();
    double time = info[0]->NumberValue(isolate->GetCurrentContext()).FromMaybe(0);
    glfwSetTime(time);
}

NODE_FUNC(CXX_glfwSetWindowAspectRatio)
{
    v8::Isolate *isolate = info.GetIsolate();
    v8::Local<v8::Object> ptr = info[0].As<v8::Object>();
    GLFWwindow *win = (GLFWwindow *)fromJSLong(isolate, ptr);
    double numer = info[1]->NumberValue(isolate->GetCurrentContext()).FromMaybe(0);
    double denom = info[2]->NumberValue(isolate->GetCurrentContext()).FromMaybe(0);
    glfwSetWindowAspectRatio(win, numer, denom);
}

NODE_FUNC(CXX_glfwSetWindowAttrib)
{
    v8::Isolate *isolate = info.GetIsolate();
    v8::Local<v8::Object> ptr = info[0].As<v8::Object>();
    GLFWwindow *win = (GLFWwindow *)fromJSLong(isolate, ptr);
    double attrib = info[1]->NumberValue(isolate->GetCurrentContext()).FromMaybe(0);
    double value = info[2]->NumberValue(isolate->GetCurrentContext()).FromMaybe(0);
    glfwSetWindowAttrib(win, attrib, value);
}

NODE_FUNC(CXX_glfwSetWindowIcon)
{
    v8::Isolate *isolate = info.GetIsolate();
    v8::Local<v8::Object> ptr = info[0].As<v8::Object>();
    GLFWwindow *win = (GLFWwindow *)fromJSLong(isolate, ptr);
    v8::Local<v8::Array> arr = info[1].As<v8::Array>();
    GLFWimage *img = new GLFWimage[arr->Length()];
    for (unsigned i = 0; i < arr->Length(); i++)
    {
        v8::Local<v8::Object> ptr = arr->Get(isolate->GetCurrentContext(), i).ToLocalChecked().As<v8::Object>();
        img[i] = *(GLFWimage *)fromJSLong(isolate, ptr);
    }
    glfwSetWindowIcon(win, arr->Length(), img);
    delete[] img;
}

NODE_FUNC(CXX_glfwSetWindowMonitor)
{
    v8::Isolate *isolate = info.GetIsolate();
    v8::Local<v8::Object> ptr = info[0].As<v8::Object>();
    GLFWwindow *win = (GLFWwindow *)fromJSLong(isolate, ptr);
    v8::Local<v8::Object> ptr2 = info[1].As<v8::Object>();
    GLFWmonitor *monitor = (GLFWmonitor *)fromJSLong(isolate, ptr2);
    int xpos = info[2]->NumberValue(isolate->GetCurrentContext()).FromMaybe(0);
    int ypos = info[3]->NumberValue(isolate->GetCurrentContext()).FromMaybe(0);
    int width = info[4]->NumberValue(isolate->GetCurrentContext()).FromMaybe(0);
    int height = info[5]->NumberValue(isolate->GetCurrentContext()).FromMaybe(0);
    int refreshRate = info[6]->NumberValue(isolate->GetCurrentContext()).FromMaybe(0);
    glfwSetWindowMonitor(win, monitor, xpos, ypos, width, height, refreshRate);
}

NODE_FUNC(CXX_glfwSetWindowOpacity)
{
    v8::Isolate *isolate = info.GetIsolate();
    v8::Local<v8::Object> ptr = info[0].As<v8::Object>();
    GLFWwindow *win = (GLFWwindow *)fromJSLong(isolate, ptr);
    double opacity = info[1]->NumberValue(isolate->GetCurrentContext()).FromMaybe(0);
    glfwSetWindowOpacity(win, opacity);
}

NODE_FUNC(CXX_glfwSetWindowPos)
{
    v8::Isolate *isolate = info.GetIsolate();
    v8::Local<v8::Object> ptr = info[0].As<v8::Object>();
    GLFWwindow *win = (GLFWwindow *)fromJSLong(isolate, ptr);
    double x = info[1]->NumberValue(isolate->GetCurrentContext()).FromMaybe(0);
    double y = info[2]->NumberValue(isolate->GetCurrentContext()).FromMaybe(0);
    glfwSetWindowPos(win, x, y);
}

NODE_FUNC(CXX_glfwSetWindowShouldClose)
{
    v8::Isolate *isolate = info.GetIsolate();
    v8::Local<v8::Object> ptr = info[0].As<v8::Object>();
    GLFWwindow *win = (GLFWwindow *)fromJSLong(isolate, ptr);
    bool value = info[1]->BooleanValue(isolate);
    glfwSetWindowShouldClose(win, value);
}

NODE_FUNC(CXX_glfwSetWindowSize)
{
    v8::Isolate *isolate = info.GetIsolate();
    v8::Local<v8::Object> ptr = info[0].As<v8::Object>();
    GLFWwindow *win = (GLFWwindow *)fromJSLong(isolate, ptr);
    double w = info[1]->NumberValue(isolate->GetCurrentContext()).FromMaybe(0);
    double h = info[2]->NumberValue(isolate->GetCurrentContext()).FromMaybe(0);
    glfwSetWindowSize(win, w, h);
}

NODE_FUNC(CXX_glfwSetWindowSizeLimits)
{
    v8::Isolate *isolate = info.GetIsolate();
    v8::Local<v8::Object> ptr = info[0].As<v8::Object>();
    GLFWwindow *win = (GLFWwindow *)fromJSLong(isolate, ptr);
    double w = info[1]->NumberValue(isolate->GetCurrentContext()).FromMaybe(0);
    double h = info[2]->NumberValue(isolate->GetCurrentContext()).FromMaybe(0);
    double mw = info[3]->NumberValue(isolate->GetCurrentContext()).FromMaybe(0);
    double mh = info[4]->NumberValue(isolate->GetCurrentContext()).FromMaybe(0);
    glfwSetWindowSizeLimits(win, w, h, mw, mh);
}

NODE_FUNC(CXX_glfwSetWindowTitle)
{
    v8::Isolate *isolate = info.GetIsolate();
    v8::Local<v8::Object> ptr = info[0].As<v8::Object>();
    GLFWwindow *win = (GLFWwindow *)fromJSLong(isolate, ptr);
    v8::Local<v8::String> _title = info[1]->ToString(isolate->GetCurrentContext()).FromMaybe(v8::String::NewFromUtf8(isolate, "").ToLocalChecked());
    v8::String::Utf8Value title(isolate, _title);
    glfwSetWindowTitle(win, *title);
}

NODE_FUNC(CXX_glfwShowWindow)
{
    v8::Isolate *isolate = info.GetIsolate();
    v8::Local<v8::Object> ptr = info[0].As<v8::Object>();
    GLFWwindow *win = (GLFWwindow *)fromJSLong(isolate, ptr);
    glfwShowWindow(win);
}

NODE_FUNC(CXX_glfwSwapBuffers)
{
    v8::Isolate *isolate = info.GetIsolate();
    v8::Local<v8::Object> ptr = info[0].As<v8::Object>();
    GLFWwindow *win = (GLFWwindow *)fromJSLong(isolate, ptr);
    glfwSwapBuffers(win);
}
NODE_FUNC(CXX_glfwSwapInterval)
{
    v8::Isolate *isolate = info.GetIsolate();
    glfwSwapInterval(info[0]->NumberValue(isolate->GetCurrentContext()).FromMaybe(0));
}

NODE_FUNC(CXX_glfwUpdateGamepadMappings)
{
    v8::Isolate *isolate = info.GetIsolate();
    v8::Local<v8::String> _name = info[0]->ToString(isolate->GetCurrentContext()).FromMaybe(v8::String::NewFromUtf8(isolate, "").ToLocalChecked());
    v8::String::Utf8Value name(isolate, _name);
    info.GetReturnValue().Set(v8::Number::New(isolate, glfwUpdateGamepadMappings(*name)));
}

NODE_FUNC(CXX_glfwVulkanSupported)
{
    v8::Isolate *isolate = info.GetIsolate();
    info.GetReturnValue().Set(v8::Number::New(isolate, glfwVulkanSupported()));
}

NODE_FUNC(CXX_glfwWaitEvents)
{
    glfwWaitEvents();
}

NODE_FUNC(CXX_glfwWaitEventsTimeout)
{
    v8::Isolate *isolate = info.GetIsolate();
    glfwWaitEventsTimeout(info[0]->NumberValue(isolate->GetCurrentContext()).FromMaybe(0));
}

NODE_FUNC(CXX_glfwWindowHint)
{
    v8::Isolate *isolate = info.GetIsolate();
    double hint = info[0]->NumberValue(isolate->GetCurrentContext()).FromMaybe(0);
    double value = info[1]->NumberValue(isolate->GetCurrentContext()).FromMaybe(0);
    glfwWindowHint((int)hint, (int)value);
}

NODE_FUNC(CXX_glfwWindowHintString)
{
    v8::Isolate *isolate = info.GetIsolate();
    double hint = info[0]->NumberValue(isolate->GetCurrentContext()).FromMaybe(0);
    v8::Local<v8::String> value = info[1]->ToString(isolate->GetCurrentContext()).FromMaybe(v8::String::NewFromUtf8(isolate, "").ToLocalChecked());
    v8::String::Utf8Value str(isolate, value);
    glfwWindowHintString(hint, *str);
}

std::map<GLFWwindow *, v8::Persistent<v8::Function>> _key_callbacks;

void onKey(GLFWwindow *win, int key, int scancode, int action, int modes)
{
    v8::Isolate *isolate = v8::Isolate::GetCurrent();
    if (_key_callbacks[win] == v8::Undefined(isolate))
    {
        return;
    }
    v8::Local<v8::Value> args[5];
    args[0] = JsLong(isolate, (unsigned long)win);
    args[1] = v8::Number::New(isolate, key);
    args[2] = v8::Number::New(isolate, scancode);
    args[3] = v8::Number::New(isolate, action);
    args[4] = v8::Number::New(isolate, modes);
    _key_callbacks[win].Get(isolate)->CallAsFunction(isolate->GetCurrentContext(), isolate->GetCurrentContext()->Global(), 5, args).ToLocalChecked();
}

NODE_FUNC(CXX_glfwSetKeyCallback)
{
    v8::Isolate *isolate = info.GetIsolate();
    GLFWwindow *win = 0;
    v8::Local<v8::Object> ptr = info[0].As<v8::Object>();
    unsigned long lptr = fromJSLong(isolate, ptr);
    win = (GLFWwindow *)lptr;
    v8::Local<v8::Function> func = info[1].As<v8::Function>();
    _key_callbacks[win].Reset(isolate, func);
    glfwSetKeyCallback(win, &onKey);
}

std::map<GLFWwindow *, v8::Persistent<v8::Function>> _char_callbacks;
void onChar(GLFWwindow *win, unsigned int value)
{
    v8::Isolate *isolate = v8::Isolate::GetCurrent();
    if (_char_callbacks[win] == v8::Undefined(isolate))
    {
        return;
    }
    v8::Local<v8::Value> args[2];
    args[0] = JsLong(isolate, (unsigned long)win);
    args[1] = v8::Number::New(isolate, value);
    _char_callbacks[win].Get(isolate)->CallAsFunction(isolate->GetCurrentContext(), isolate->GetCurrentContext()->Global(), 2, args).ToLocalChecked();
}

NODE_FUNC(CXX_glfwSetCharCallback)
{
    v8::Isolate *isolate = info.GetIsolate();
    GLFWwindow *win = 0;
    v8::Local<v8::Object> ptr = info[0].As<v8::Object>();
    unsigned long lptr = fromJSLong(isolate, ptr);
    win = (GLFWwindow *)lptr;
    v8::Local<v8::Function> func = info[1].As<v8::Function>();
    _char_callbacks[win].Reset(isolate, func);
    glfwSetCharCallback(win, onChar);
}

std::map<GLFWwindow *, v8::Persistent<v8::Function>> _char_mod_callbacks;

void onCharMods(GLFWwindow *win, unsigned int mod, int value)
{
    v8::Isolate *isolate = v8::Isolate::GetCurrent();
    if (_char_mod_callbacks[win] == v8::Undefined(isolate))
    {
        return;
    }
    v8::Local<v8::Value> args[3];
    args[0] = JsLong(isolate, (unsigned long)win);
    args[1] = v8::Number::New(isolate, mod);
    args[2] = v8::Number::New(isolate, value);
    _char_mod_callbacks[win].Get(isolate)->CallAsFunction(isolate->GetCurrentContext(), isolate->GetCurrentContext()->Global(), 3, args).ToLocalChecked();
}

NODE_FUNC(CXX_glfwSetCharModsCallback)
{
    v8::Isolate *isolate = info.GetIsolate();
    GLFWwindow *win = 0;
    v8::Local<v8::Object> ptr = info[0].As<v8::Object>();
    unsigned long lptr = fromJSLong(isolate, ptr);
    win = (GLFWwindow *)lptr;
    v8::Local<v8::Function> func = info[1].As<v8::Function>();
    _char_mod_callbacks[win].Reset(isolate, func);
    glfwSetCharModsCallback(win, onCharMods);
}

std::map<GLFWwindow *, v8::Persistent<v8::Function>> _cursor_enter_callbacks;
void onCursorEnter(GLFWwindow *win, int value)
{

    v8::Isolate *isolate = v8::Isolate::GetCurrent();
    if (_cursor_enter_callbacks[win] == v8::Undefined(isolate))
    {
        return;
    }
    v8::Local<v8::Value> args[2];
    args[0] = JsLong(isolate, (unsigned long)win);
    args[1] = v8::Number::New(isolate, value);
    _cursor_enter_callbacks[win].Get(isolate)->CallAsFunction(isolate->GetCurrentContext(), isolate->GetCurrentContext()->Global(), 2, args).ToLocalChecked();
}
NODE_FUNC(CXX_glfwSetCursorEnterCallback)
{
    v8::Isolate *isolate = info.GetIsolate();
    GLFWwindow *win = 0;
    v8::Local<v8::Object> ptr = info[0].As<v8::Object>();
    unsigned long lptr = fromJSLong(isolate, ptr);
    win = (GLFWwindow *)lptr;
    v8::Local<v8::Function> func = info[1].As<v8::Function>();
    _cursor_enter_callbacks[win].Reset(isolate, func);
    glfwSetCursorEnterCallback(win, onCursorEnter);
}

std::map<GLFWwindow *, v8::Persistent<v8::Function>> _cursor_pos_callbacks;
void onCursorPos(GLFWwindow *win, double x, double y)
{
    v8::Isolate *isolate = v8::Isolate::GetCurrent();
    if (_cursor_pos_callbacks[win] == v8::Undefined(isolate))
    {
        return;
    }
    v8::Local<v8::Value> args[3];
    args[0] = JsLong(isolate, (unsigned long)win);
    args[1] = v8::Number::New(isolate, x);
    args[2] = v8::Number::New(isolate, y);
    _cursor_pos_callbacks[win].Get(isolate)->CallAsFunction(isolate->GetCurrentContext(), isolate->GetCurrentContext()->Global(), 3, args).ToLocalChecked();
}

NODE_FUNC(CXX_glfwSetCursorPosCallback)
{

    v8::Isolate *isolate = info.GetIsolate();
    GLFWwindow *win = 0;
    v8::Local<v8::Object> ptr = info[0].As<v8::Object>();
    unsigned long lptr = fromJSLong(isolate, ptr);
    win = (GLFWwindow *)lptr;
    v8::Local<v8::Function> func = info[1].As<v8::Function>();
    _cursor_pos_callbacks[win].Reset(isolate, func);
    glfwSetCursorPosCallback(win, onCursorPos);
}

std::map<GLFWwindow *, v8::Persistent<v8::Function>> _drop_callbacks;
void onDrop(GLFWwindow *win, int count, const char **file)
{
    v8::Isolate *isolate = v8::Isolate::GetCurrent();
    if (_drop_callbacks[win] == v8::Undefined(isolate))
    {
        return;
    }
    v8::Local<v8::Value> args[2];
    args[0] = JsLong(isolate, (unsigned long)win);
    v8::Local<v8::Array> files;
    for (int i = 0; i < count; i++)
    {
        files->Set(isolate->GetCurrentContext(), i, v8::String::NewFromUtf8(isolate, file[i]).ToLocalChecked()).Check();
    }
    args[1] = files;
    _drop_callbacks[win].Get(isolate)->CallAsFunction(isolate->GetCurrentContext(), isolate->GetCurrentContext()->Global(), 2, args).ToLocalChecked();
}

NODE_FUNC(CXX_glfwSetDropCallback)
{
    v8::Isolate *isolate = info.GetIsolate();
    GLFWwindow *win = 0;
    v8::Local<v8::Object> ptr = info[0].As<v8::Object>();
    unsigned long lptr = fromJSLong(isolate, ptr);
    win = (GLFWwindow *)lptr;
    v8::Local<v8::Function> func = info[1].As<v8::Function>();
    _drop_callbacks[win].Reset(isolate, func);
    glfwSetDropCallback(win, onDrop);
}

v8::Persistent<v8::Function> _error_callback;
void onError(int id, const char *err)
{
    v8::Isolate *isolate = v8::Isolate::GetCurrent();
    if (_error_callback == v8::Undefined(isolate))
    {
        return;
    }
    v8::Local<v8::Value> args[2];
    args[0] = v8::Number::New(isolate, id);
    args[1] = v8::String::NewFromUtf8(isolate, err).ToLocalChecked();
    _error_callback.Get(isolate)->CallAsFunction(isolate->GetCurrentContext(), isolate->GetCurrentContext()->Global(), 2, args).ToLocalChecked();
}

NODE_FUNC(CXX_glfwSetErrorCallback)
{
    v8::Isolate *isolate = info.GetIsolate();
    GLFWwindow *win = 0;
    v8::Local<v8::Object> ptr = info[0].As<v8::Object>();
    unsigned long lptr = fromJSLong(isolate, ptr);
    win = (GLFWwindow *)lptr;
    v8::Local<v8::Function> func = info[1].As<v8::Function>();
    _error_callback.Reset(isolate, func);
    glfwSetErrorCallback(onError);
}

std::map<GLFWwindow *, v8::Persistent<v8::Function>> _set_framebuffer_size_callbacks;
void onSetFramebufferSize(GLFWwindow *win, int width, int height)
{
    v8::Isolate *isolate = v8::Isolate::GetCurrent();
    if (_set_framebuffer_size_callbacks[win] == v8::Undefined(isolate))
    {
        return;
    }
    v8::Local<v8::Value> args[3];
    args[0] = JsLong(isolate, (unsigned long)win);
    args[1] = v8::Number::New(isolate, width);
    args[2] = v8::Number::New(isolate, height);
    _set_framebuffer_size_callbacks[win].Get(isolate)->CallAsFunction(isolate->GetCurrentContext(), isolate->GetCurrentContext()->Global(), 3, args).ToLocalChecked();
}

NODE_FUNC(CXX_glfwSetFramebufferSizeCallback)
{
    v8::Isolate *isolate = info.GetIsolate();
    GLFWwindow *win = 0;
    v8::Local<v8::Object> ptr = info[0].As<v8::Object>();
    unsigned long lptr = fromJSLong(isolate, ptr);
    win = (GLFWwindow *)lptr;
    v8::Local<v8::Function> func = info[1].As<v8::Function>();
    _set_framebuffer_size_callbacks[win].Reset(isolate, func);
    glfwSetFramebufferSizeCallback(win, onSetFramebufferSize);
}

v8::Persistent<v8::Function> _set_joystick_size_callbacks;
void onSetJoystick(int jid, int id)
{
    v8::Isolate *isolate = v8::Isolate::GetCurrent();
    if (_set_joystick_size_callbacks == v8::Undefined(isolate))
    {
        return;
    }
    v8::Local<v8::Value> args[2];
    args[0] = v8::Number::New(isolate, jid);
    args[1] = v8::Number::New(isolate, id);
    _set_joystick_size_callbacks.Get(isolate)->CallAsFunction(isolate->GetCurrentContext(), isolate->GetCurrentContext()->Global(), 2, args).ToLocalChecked();
}

NODE_FUNC(CXX_glfwSetJoystickCallback)
{
    v8::Isolate *isolate = info.GetIsolate();
    GLFWwindow *win = 0;
    v8::Local<v8::Object> ptr = info[0].As<v8::Object>();
    unsigned long lptr = fromJSLong(isolate, ptr);
    win = (GLFWwindow *)lptr;
    v8::Local<v8::Function> func = info[1].As<v8::Function>();
    _set_joystick_size_callbacks.Reset(isolate, func);
    glfwSetJoystickCallback(onSetJoystick);
}

v8::Persistent<v8::Function> _set_monitor_callbacks;
void onSetMonitor(GLFWmonitor *monitor, int id)
{
    v8::Isolate *isolate = v8::Isolate::GetCurrent();
    if (_set_monitor_callbacks == v8::Undefined(isolate))
    {
        return;
    }
    v8::Local<v8::Value> args[2];
    args[0] = JsLong(isolate, (unsigned long)monitor);
    args[1] = v8::Number::New(isolate, id);
    _set_monitor_callbacks.Get(isolate)->CallAsFunction(isolate->GetCurrentContext(), isolate->GetCurrentContext()->Global(), 2, args).ToLocalChecked();
}

NODE_FUNC(CXX_glfwSetMonitorCallback)
{
    v8::Isolate *isolate = info.GetIsolate();
    GLFWwindow *win = 0;
    v8::Local<v8::Object> ptr = info[0].As<v8::Object>();
    unsigned long lptr = fromJSLong(isolate, ptr);
    win = (GLFWwindow *)lptr;
    v8::Local<v8::Function> func = info[1].As<v8::Function>();
    _set_monitor_callbacks.Reset(isolate, func);
    glfwSetMonitorCallback(onSetMonitor);
}

std::map<GLFWwindow *, v8::Persistent<v8::Function>> _set_mouse_button_callbacks;
void onSetMouseButton(GLFWwindow *win, int button, int action, int mods)
{
    v8::Isolate *isolate = v8::Isolate::GetCurrent();
    if (_set_mouse_button_callbacks[win] == v8::Undefined(isolate))
    {
        return;
    }
    v8::Local<v8::Value> args[4];
    args[0] = JsLong(isolate, (unsigned long)win);
    args[1] = v8::Number::New(isolate, button);
    args[2] = v8::Number::New(isolate, action);
    args[3] = v8::Number::New(isolate, mods);
    _set_mouse_button_callbacks[win].Get(isolate)->CallAsFunction(isolate->GetCurrentContext(), isolate->GetCurrentContext()->Global(), 4, args).ToLocalChecked();
}

NODE_FUNC(CXX_glfwSetMouseButtonCallback)
{
    v8::Isolate *isolate = info.GetIsolate();
    GLFWwindow *win = 0;
    v8::Local<v8::Object> ptr = info[0].As<v8::Object>();
    unsigned long lptr = fromJSLong(isolate, ptr);
    win = (GLFWwindow *)lptr;
    v8::Local<v8::Function> func = info[1].As<v8::Function>();
    _set_mouse_button_callbacks[win].Reset(isolate, func);
    glfwSetMouseButtonCallback(win, onSetMouseButton);
}

std::map<GLFWwindow *, v8::Persistent<v8::Function>> _set_scroll_callbacks;
void onSetScrollCallback(GLFWwindow *win, double x, double y)
{
    v8::Isolate *isolate = v8::Isolate::GetCurrent();
    if (_set_scroll_callbacks[win] == v8::Undefined(isolate))
    {
        return;
    }
    v8::Local<v8::Value> args[3];
    args[0] = JsLong(isolate, (unsigned long)win);
    args[1] = v8::Number::New(isolate, x);
    args[2] = v8::Number::New(isolate, y);
    _set_scroll_callbacks[win].Get(isolate)->CallAsFunction(isolate->GetCurrentContext(), isolate->GetCurrentContext()->Global(), 3, args).ToLocalChecked();
}

NODE_FUNC(CXX_glfwSetScrollCallback)
{
    v8::Isolate *isolate = info.GetIsolate();
    GLFWwindow *win = 0;
    v8::Local<v8::Object> ptr = info[0].As<v8::Object>();
    unsigned long lptr = fromJSLong(isolate, ptr);
    win = (GLFWwindow *)lptr;
    v8::Local<v8::Function> func = info[1].As<v8::Function>();
    _set_scroll_callbacks[win].Reset(isolate, func);
    glfwSetScrollCallback(win, onSetScrollCallback);
}

std::map<GLFWwindow *, v8::Persistent<v8::Function>> _set_window_close_callbacks;
void onSetWindowClose(GLFWwindow *win)
{
    v8::Isolate *isolate = v8::Isolate::GetCurrent();
    if (_set_window_close_callbacks[win] == v8::Undefined(isolate))
    {
        return;
    }
    v8::Local<v8::Value> args[1];
    args[0] = JsLong(isolate, (unsigned long)win);
    _set_window_close_callbacks[win].Get(isolate)->CallAsFunction(isolate->GetCurrentContext(), isolate->GetCurrentContext()->Global(), 1, args).ToLocalChecked();
}

NODE_FUNC(CXX_glfwSetWindowCloseCallback)
{
    v8::Isolate *isolate = info.GetIsolate();
    GLFWwindow *win = 0;
    v8::Local<v8::Object> ptr = info[0].As<v8::Object>();
    unsigned long lptr = fromJSLong(isolate, ptr);
    win = (GLFWwindow *)lptr;
    v8::Local<v8::Function> func = info[1].As<v8::Function>();
    _set_window_close_callbacks[win].Reset(isolate, func);
    glfwSetWindowCloseCallback(win, onSetWindowClose);
}

std::map<GLFWwindow *, v8::Persistent<v8::Function>> _set_window_content_scale_callbacks;
void onSetWindowContentScale(GLFWwindow *win, float x, float y)
{
    v8::Isolate *isolate = v8::Isolate::GetCurrent();
    if (_set_window_content_scale_callbacks[win] == v8::Undefined(isolate))
    {
        return;
    }
    v8::Local<v8::Value> args[3];
    args[0] = JsLong(isolate, (unsigned long)win);
    args[1] = v8::Number::New(isolate, x);
    args[2] = v8::Number::New(isolate, y);
    _set_window_content_scale_callbacks[win].Get(isolate)->CallAsFunction(isolate->GetCurrentContext(), isolate->GetCurrentContext()->Global(), 3, args).ToLocalChecked();
}

NODE_FUNC(CXX_glfwSetWindowContentScaleCallback)
{
    v8::Isolate *isolate = info.GetIsolate();
    GLFWwindow *win = 0;
    v8::Local<v8::Object> ptr = info[0].As<v8::Object>();
    unsigned long lptr = fromJSLong(isolate, ptr);
    win = (GLFWwindow *)lptr;
    v8::Local<v8::Function> func = info[1].As<v8::Function>();
    _set_window_content_scale_callbacks[win].Reset(isolate, func);
    glfwSetWindowContentScaleCallback(win, onSetWindowContentScale);
}

std::map<GLFWwindow *, v8::Persistent<v8::Function>> _set_window_focus_callbacks;
void onSetWindowFocus(GLFWwindow *win, int value)
{
    v8::Isolate *isolate = v8::Isolate::GetCurrent();
    if (_set_window_focus_callbacks[win] == v8::Undefined(isolate))
    {
        return;
    }
    v8::Local<v8::Value> args[2];
    args[0] = JsLong(isolate, (unsigned long)win);
    args[1] = v8::Number::New(isolate, value);
    _set_window_focus_callbacks[win].Get(isolate)->CallAsFunction(isolate->GetCurrentContext(), isolate->GetCurrentContext()->Global(), 2, args).ToLocalChecked();
}

NODE_FUNC(CXX_glfwSetWindowFocusCallback)
{
    v8::Isolate *isolate = info.GetIsolate();
    GLFWwindow *win = 0;
    v8::Local<v8::Object> ptr = info[0].As<v8::Object>();
    unsigned long lptr = fromJSLong(isolate, ptr);
    win = (GLFWwindow *)lptr;
    v8::Local<v8::Function> func = info[1].As<v8::Function>();
    _set_window_focus_callbacks[win].Reset(isolate, func);
    glfwSetWindowFocusCallback(win, onSetWindowFocus);
}

std::map<GLFWwindow *, v8::Persistent<v8::Function>> _set_window_iconify_callbacks;
void onSetWindowIconify(GLFWwindow *win, int value)
{
    v8::Isolate *isolate = v8::Isolate::GetCurrent();
    if (_set_window_iconify_callbacks[win] == v8::Undefined(isolate))
    {
        return;
    }
    v8::Local<v8::Value> args[2];
    args[0] = JsLong(isolate, (unsigned long)win);
    args[1] = v8::Number::New(isolate, value);
    _set_window_iconify_callbacks[win].Get(isolate)->CallAsFunction(isolate->GetCurrentContext(), isolate->GetCurrentContext()->Global(), 2, args).ToLocalChecked();
}

NODE_FUNC(CXX_glfwSetWindowIconifyCallback)
{
    v8::Isolate *isolate = info.GetIsolate();
    GLFWwindow *win = 0;
    v8::Local<v8::Object> ptr = info[0].As<v8::Object>();
    unsigned long lptr = fromJSLong(isolate, ptr);
    win = (GLFWwindow *)lptr;
    v8::Local<v8::Function> func = info[1].As<v8::Function>();
    _set_window_iconify_callbacks[win].Reset(isolate, func);
    glfwSetWindowIconifyCallback(win, onSetWindowIconify);
}

std::map<GLFWwindow *, v8::Persistent<v8::Function>> _set_window_maximize_callbacks;
void onSetWindowMaximize(GLFWwindow *win, int value)
{
    v8::Isolate *isolate = v8::Isolate::GetCurrent();
    if (_set_window_maximize_callbacks[win] == v8::Undefined(isolate))
    {
        return;
    }
    v8::Local<v8::Value> args[2];
    args[0] = JsLong(isolate, (unsigned long)win);
    args[1] = v8::Number::New(isolate, value);
    _set_window_maximize_callbacks[win].Get(isolate)->CallAsFunction(isolate->GetCurrentContext(), isolate->GetCurrentContext()->Global(), 2, args).ToLocalChecked();
}
NODE_FUNC(CXX_glfwSetWindowMaximizeCallback)
{
    v8::Isolate *isolate = info.GetIsolate();
    GLFWwindow *win = 0;
    v8::Local<v8::Object> ptr = info[0].As<v8::Object>();
    unsigned long lptr = fromJSLong(isolate, ptr);
    win = (GLFWwindow *)lptr;
    v8::Local<v8::Function> func = info[1].As<v8::Function>();
    _set_window_maximize_callbacks[win].Reset(isolate, func);
    glfwSetWindowMaximizeCallback(win, onSetWindowMaximize);
}

std::map<GLFWwindow *, v8::Persistent<v8::Function>> _set_window_pos_callbacks;
void onSetWindowPosCallback(GLFWwindow *win, int x, int y)
{
    v8::Isolate *isolate = v8::Isolate::GetCurrent();
    if (_set_window_pos_callbacks[win] == v8::Undefined(isolate))
    {
        return;
    }
    v8::Local<v8::Value> args[3];
    args[0] = JsLong(isolate, (unsigned long)win);
    args[1] = v8::Number::New(isolate, x);
    args[2] = v8::Number::New(isolate, y);
    _set_window_pos_callbacks[win].Get(isolate)->CallAsFunction(isolate->GetCurrentContext(), isolate->GetCurrentContext()->Global(), 3, args).ToLocalChecked();
}
NODE_FUNC(CXX_glfwSetWindowPosCallback)
{
    v8::Isolate *isolate = info.GetIsolate();
    GLFWwindow *win = 0;
    v8::Local<v8::Object> ptr = info[0].As<v8::Object>();
    unsigned long lptr = fromJSLong(isolate, ptr);
    win = (GLFWwindow *)lptr;
    v8::Local<v8::Function> func = info[1].As<v8::Function>();
    _set_window_pos_callbacks[win].Reset(isolate, func);
    glfwSetWindowPosCallback(win, onSetWindowPosCallback);
}

std::map<GLFWwindow *, v8::Persistent<v8::Function>> _set_window_refresh_callbacks;
void onSetWindowRefreshCallback(GLFWwindow *win)
{
    v8::Isolate *isolate = v8::Isolate::GetCurrent();
    if (_set_window_refresh_callbacks[win] == v8::Undefined(isolate))
    {
        return;
    }
    v8::Local<v8::Value> args[1];
    args[0] = JsLong(isolate, (unsigned long)win);
    _set_window_refresh_callbacks[win].Get(isolate)->CallAsFunction(isolate->GetCurrentContext(), isolate->GetCurrentContext()->Global(), 1, args).ToLocalChecked();
}
NODE_FUNC(CXX_glfwSetWindowRefreshCallback)
{
    v8::Isolate *isolate = info.GetIsolate();
    GLFWwindow *win = 0;
    v8::Local<v8::Object> ptr = info[0].As<v8::Object>();
    unsigned long lptr = fromJSLong(isolate, ptr);
    win = (GLFWwindow *)lptr;
    v8::Local<v8::Function> func = info[1].As<v8::Function>();
    _set_window_refresh_callbacks[win].Reset(isolate, func);
    glfwSetWindowRefreshCallback(win, onSetWindowRefreshCallback);
}

std::map<GLFWwindow *, v8::Persistent<v8::Function>> _set_window_size_callbacks;
void onSetWindowSizeCallback(GLFWwindow *win, int x, int y)
{
    v8::Isolate *isolate = v8::Isolate::GetCurrent();
    if (_set_window_size_callbacks[win] == v8::Undefined(isolate))
    {
        return;
    }
    v8::Local<v8::Value> args[3];
    args[0] = JsLong(isolate, (unsigned long)win);
    args[1] = v8::Number::New(isolate, x);
    args[2] = v8::Number::New(isolate, y);
    _set_window_size_callbacks[win].Get(isolate)->CallAsFunction(isolate->GetCurrentContext(), isolate->GetCurrentContext()->Global(), 3, args).ToLocalChecked();
}
NODE_FUNC(CXX_glfwSetWindowSizeCallback)
{
    v8::Isolate *isolate = info.GetIsolate();
    GLFWwindow *win = 0;
    v8::Local<v8::Object> ptr = info[0].As<v8::Object>();
    unsigned long lptr = fromJSLong(isolate, ptr);
    win = (GLFWwindow *)lptr;
    v8::Local<v8::Function> func = info[1].As<v8::Function>();
    _set_window_size_callbacks[win].Reset(isolate, func);
    glfwSetWindowSizeCallback(win, onSetWindowSizeCallback);
}
NODE_FUNC(CXX_createImage)
{
    v8::Isolate *isolate = info.GetIsolate();
    int width = info[0]->NumberValue(isolate->GetCurrentContext()).FromMaybe(0);
    int height = info[1]->NumberValue(isolate->GetCurrentContext()).FromMaybe(0);
    v8::Local<v8::Int32Array> buf = info[2].As<v8::Int32Array>();
    GLFWimage *img = new GLFWimage;
    img->width = width;
    img->height = height;
    unsigned int *_buf = new unsigned int[width * height];
    for (int y = 0; y < height; y++)
    {
        for (int x = 0; x < width; x++)
        {
            v8::Local<v8::Value> value = buf->Get(isolate->GetCurrentContext(), y * width + x).ToLocalChecked();
            _buf[y * width + x] = value->NumberValue(isolate->GetCurrentContext()).FromMaybe(0);
        }
    }
    img->pixels = (unsigned char *)_buf;
    info.GetReturnValue().Set(JsLong(isolate, (unsigned long)img));
}
NODE_FUNC(CXX_deleteImage)
{
    v8::Isolate *isolate = info.GetIsolate();
    GLFWimage *img = 0;
    v8::Local<v8::Object> ptr = info[0].As<v8::Object>();
    unsigned long lptr = fromJSLong(isolate, ptr);
    img = (GLFWimage *)lptr;
    if (img)
    {
        delete[] img->pixels;
        delete img;
    }
}
void GLFW_Initialize(v8::Local<v8::Object> exports)
{

    /*
    glfwGetJoystickUserPointer;
    glfwGetMonitorUserPointer;
    glfwGetWindowUserPointer;
    glfwSetJoystickUserPointer;
    glfwSetMonitorUserPointer;
    glfwSetWindowUserPointer;
    */
    EXPORT(CXX_glfwInit);
    EXPORT(CXX_glfwTerminate);
    EXPORT(CXX_glfwCreateWindow);
    EXPORT(CXX_glfwPollEvents);
    EXPORT(CXX_glfwWindowShouldClose);
    EXPORT(CXX_glfwGetKey);
    EXPORT(CXX_glfwGetMouseButton);
    EXPORT(CXX_glfwGetClipboardString);
    EXPORT(CXX_glfwGetCurrentContext);
    EXPORT(CXX_glfwGetCursorPos);
    EXPORT(CXX_glfwGetError);
    EXPORT(CXX_glfwGetFramebufferSize);
    EXPORT(CXX_glfwGetGamepadName);
    EXPORT(CXX_glfwGetGamepadState);
    EXPORT(CXX_glfwGetGammaRamp);
    EXPORT(CXX_glfwGetInputMode);
    EXPORT(CXX_glfwGetJoystickAxes);
    EXPORT(CXX_glfwGetJoystickButtons);
    EXPORT(CXX_glfwGetJoystickGUID);
    EXPORT(CXX_glfwGetJoystickHats);
    EXPORT(CXX_glfwGetJoystickName);
    EXPORT(CXX_glfwGetKeyName);
    EXPORT(CXX_glfwGetKeyScancode);
    EXPORT(CXX_glfwGetMonitorContentScale);
    EXPORT(CXX_glfwGetMonitorName);
    EXPORT(CXX_glfwGetMonitorPhysicalSize);
    EXPORT(CXX_glfwGetMonitorPos);
    EXPORT(CXX_glfwGetMonitors);
    EXPORT(CXX_glfwGetMonitorWorkarea);
    EXPORT(CXX_glfwGetPrimaryMonitor);
    EXPORT(CXX_glfwGetProcAddress);
    EXPORT(CXX_glfwGetRequiredInstanceExtensions);
    EXPORT(CXX_glfwGetTime);
    EXPORT(CXX_glfwGetTimerFrequency);
    EXPORT(CXX_glfwGetTimerValue);
    EXPORT(CXX_glfwGetVersion);
    EXPORT(CXX_glfwGetVersionString);
    EXPORT(CXX_glfwGetVideoMode);
    EXPORT(CXX_glfwGetVideoModes);
    EXPORT(CXX_glfwGetWindowContentScale);
    EXPORT(CXX_glfwGetWindowFrameSize);
    EXPORT(CXX_glfwGetWindowMonitor);
    EXPORT(CXX_glfwGetWindowOpacity);
    EXPORT(CXX_glfwGetWindowPos);
    EXPORT(CXX_glfwGetWindowSize);
    EXPORT(CXX_glfwSetKeyCallback);
    EXPORT(CXX_glfwCreateCursor);
    EXPORT(CXX_glfwCreateStandardCursor);
    EXPORT(CXX_glfwDefaultWindowHints);
    EXPORT(CXX_glfwDestroyCursor);
    EXPORT(CXX_glfwDestroyWindow);
    EXPORT(CXX_glfwExtensionSupported);
    EXPORT(CXX_glfwHideWindow);
    EXPORT(CXX_glfwIconifyWindow);
    EXPORT(CXX_glfwInitHint);
    EXPORT(CXX_glfwJoystickIsGamepad);
    EXPORT(CXX_glfwJoystickPresent);
    EXPORT(CXX_glfwMakeContextCurrent);
    EXPORT(CXX_glfwMaximizeWindow);
    EXPORT(CXX_glfwPostEmptyEvent);
    EXPORT(CXX_glfwRawMouseMotionSupported);
    EXPORT(CXX_glfwRequestWindowAttention);
    EXPORT(CXX_glfwRestoreWindow);
    EXPORT(CXX_glfwSetClipboardString);
    EXPORT(CXX_glfwSetCursor);
    EXPORT(CXX_glfwSetCursorPos);
    EXPORT(CXX_glfwSetGamma);
    EXPORT(CXX_glfwSetGammaRamp);
    EXPORT(CXX_glfwSetInputMode);
    EXPORT(CXX_glfwSetTime);
    EXPORT(CXX_glfwSetWindowAspectRatio);
    EXPORT(CXX_glfwSetWindowAttrib);
    EXPORT(CXX_glfwSetWindowIcon);
    EXPORT(CXX_glfwSetWindowMonitor);
    EXPORT(CXX_glfwSetWindowOpacity);
    EXPORT(CXX_glfwSetWindowPos);
    EXPORT(CXX_glfwSetWindowShouldClose);
    EXPORT(CXX_glfwSetWindowSize);
    EXPORT(CXX_glfwSetWindowSizeLimits);
    EXPORT(CXX_glfwSetWindowTitle);
    EXPORT(CXX_glfwShowWindow);
    EXPORT(CXX_glfwSwapBuffers);
    EXPORT(CXX_glfwSwapInterval);
    EXPORT(CXX_glfwUpdateGamepadMappings);
    EXPORT(CXX_glfwVulkanSupported);
    EXPORT(CXX_glfwWaitEvents);
    EXPORT(CXX_glfwWaitEventsTimeout);
    EXPORT(CXX_glfwWindowHint);
    EXPORT(CXX_glfwWindowHintString);
    EXPORT(CXX_glfwSetCharCallback);
    EXPORT(CXX_glfwSetCharModsCallback);
    EXPORT(CXX_glfwSetCursorEnterCallback);
    EXPORT(CXX_glfwSetCursorPosCallback);
    EXPORT(CXX_glfwSetDropCallback);
    EXPORT(CXX_glfwSetErrorCallback);
    EXPORT(CXX_glfwSetFramebufferSizeCallback);
    EXPORT(CXX_glfwSetJoystickCallback);
    EXPORT(CXX_glfwSetMonitorCallback);
    EXPORT(CXX_glfwSetMouseButtonCallback);
    EXPORT(CXX_glfwSetScrollCallback);
    EXPORT(CXX_glfwSetWindowCloseCallback);
    EXPORT(CXX_glfwSetWindowContentScaleCallback);
    EXPORT(CXX_glfwSetWindowFocusCallback);
    EXPORT(CXX_glfwSetWindowIconifyCallback);
    EXPORT(CXX_glfwSetWindowMaximizeCallback);
    EXPORT(CXX_glfwSetWindowPosCallback);
    EXPORT(CXX_glfwSetWindowRefreshCallback);
    EXPORT(CXX_glfwSetWindowSizeCallback);

    EXPORT(CXX_createImage);
    EXPORT(CXX_deleteImage);
}
#pragma once
#include <node/node.h>
#include <iostream>
v8::Local<v8::Object> JsLong(v8::Isolate *isolate, unsigned long value)
{
    v8::Local<v8::Object> obj = v8::Object::New(isolate);
    unsigned int *pvalue = (unsigned int *)&value;
    obj->Set(isolate->GetCurrentContext(), v8::String::NewFromUtf8(isolate, "low").ToLocalChecked(), v8::Number::New(isolate, pvalue[0])).Check();
    obj->Set(isolate->GetCurrentContext(), v8::String::NewFromUtf8(isolate, "high").ToLocalChecked(), v8::Number::New(isolate, pvalue[1])).Check();
    return obj;
}
unsigned long fromJSLong(v8::Isolate *isolate, v8::Local<v8::Object> &v8long)
{
    v8::Local<v8::Context> context = isolate->GetCurrentContext();
    double low = v8long->Get(context, v8::String::NewFromUtf8(isolate, "low").ToLocalChecked()).ToLocalChecked()->NumberValue(context).FromMaybe(0);
    double high = v8long->Get(context, v8::String::NewFromUtf8(isolate, "high").ToLocalChecked()).ToLocalChecked()->NumberValue(context).FromMaybe(0);
    unsigned long lptr = 0;
    unsigned int *_ptr_lptr = (unsigned int *)&lptr;
    _ptr_lptr[0] = (unsigned int)low;
    _ptr_lptr[1] = (unsigned int)high;
    return lptr;
}

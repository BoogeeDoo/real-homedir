/*
 * =====================================================================================
 *
 *       Filename:  entry.cpp
 *
 *    Description:  Entry file for real homedir.
 *
 *        Version:  1.0
 *        Created:  2016/03/03 17时00分42秒
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  XadillaX (ZKD), zhukaidi@souche.com
 *   Organization:  Design & Development Center, Souche Car Service Co., Ltd, HANGZHOU
 *
 * =====================================================================================
 */
#include <nan.h>
#include "homedir.h"

NAN_METHOD(GetTrueHomeDir)
{
    char buf[PATH_MAX];
    size_t len = sizeof(buf);
    const int err = __GetTrueHomeDir(buf, &len);
    if(err)
    {
        return Nan::ThrowError("uv_os_homedir");
    }

    info.GetReturnValue().Set(Nan::New<v8::String>(buf).ToLocalChecked());
}

NAN_MODULE_INIT(InitAll)
{
    Nan::Set(target, Nan::New<v8::String>("homedir").ToLocalChecked(),
            Nan::GetFunction(Nan::New<v8::FunctionTemplate>(GetTrueHomeDir)).ToLocalChecked());
}

NODE_MODULE(homedir, InitAll);

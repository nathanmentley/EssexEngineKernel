/* 
 * Essex Engine
 * 
 * Copyright (C) 2018 Nathan Mentley - All Rights Reserved
 * You may use, distribute and modify this code under the
 * terms of the BSD license.
 *
 * You should have received a copy of the BSD license with
 * this file. If not, please visit: https://github.com/nathanmentley/EssexEngine
 */

#include <EssexEngineCore/WeakPointer.h>
#include <EssexEngineKernel/Kernel.h>

using EssexEngine::WeakPointer;
using EssexEngine::Context;

using EssexEngine::Kernel;

extern "C" {
    void* kernel_init(WeakPointer<Context> context, std::string dataFilename) {
        return new Kernel(context, dataFilename);
    }
}

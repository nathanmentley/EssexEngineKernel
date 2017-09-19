/* 
 * Essex Engine
 * 
 * Copyright (C) 2017 Nathan Mentley - All Rights Reserved
 * You may use, distribute and modify this code under the
 * terms of the BSD license.
 *
 * You should have received a copy of the BSD license with
 * this file. If not, please visit: https://github.com/nathanmentley/EssexEngine
 */

#include <EssexEngineKernel/Kernel.h>

extern "C" {
    void kernel_init(EssexEngine::Context* context, std::string dataFilename) {
	    EssexEngine::Kernel(context, dataFilename).Start();
    }
}
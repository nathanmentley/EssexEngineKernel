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
#pragma once

#include <EssexEngineCore/WeakPointer.h>
#include <EssexEngineCore/EssexEnvironment.h>
#include <EssexEngineCore/Context.h>
#include <EssexEngineCore/IKernel.h>
#include <EssexEngineCore/LogDaemon.h>

#include <EssexEngineFileSystemDaemon/FileSystemDaemon.h>
#include <EssexEngineSystemDaemon/SystemDaemon.h>

namespace EssexEngine {
    class Kernel: public Core::IKernel
    {
        public:
            Kernel(WeakPointer<Context> _context, std::string filename);
            ~Kernel();

            std::string GetKernelVersion() { return ESSEX_ENGINE_VERSION; }
            
            void Start();
            void Stop();
            
            void RunApp(WeakPointer<Core::IApp> app);
        private:
            WeakPointer<Context> context;
            bool running;
    };
};

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
#include <EssexEngineCore/WeakPointer.h>
#include <EssexEngineCore/EssexEnvironment.h>
#include <EssexEngineCore/Context.h>
#include <EssexEngineCore/StateStack.h>
#include <EssexEngineCore/State.h>

#include <EssexEngineCore/LogDaemon.h>
#include <EssexEngineFileSystemDaemon/FileSystemDaemon.h>
#include <EssexEngineGfxDaemon/GfxDaemon.h>
#include <EssexEngineConfigDaemon/ConfigDaemon.h>
#include <EssexEngineSystemDaemon/SystemDaemon.h>
#include <EssexEngineWindowDaemon/WindowDaemon.h>

namespace EssexEngine {
    class Kernel
    {
        public:
            Kernel(WeakPointer<Context> _context, std::string filename);
            ~Kernel();

            std::string GetKernelVersion() { return ESSEX_ENGINE_VERSION; }
            
            void Start();
        private:
            WeakPointer<Context> context;

            UniquePointer<Daemons::Window::WindowDef> windowDef;
            UniquePointer<Daemons::Window::CanvasDef> canvasDef;
            UniquePointer<Daemons::Window::IWindow> mainWindow;
            UniquePointer<Daemons::Window::IRenderContext> mainRenderContext;
    };
};

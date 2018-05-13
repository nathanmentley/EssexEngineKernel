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

#include <EssexEngineKernel/Kernel.h>

using EssexEngine::WeakPointer;

using EssexEngine::Core::IApp;
using EssexEngine::Core::IKernel;
using EssexEngine::Core::Logging::LogDaemon;

using EssexEngine::Daemons::FileSystem::FileSystemDaemon;
using EssexEngine::Daemons::System::SystemDaemon;

using EssexEngine::Kernel;

Kernel::Kernel(
    WeakPointer<Context> _context,
    std::string filename
): IKernel() {
    context = _context;
    running = true;
    
    context->GetDaemon<LogDaemon>()->LogLine(
        "Starting Kernel [%s]",
        GetKernelVersion().c_str()
    );
    
    context->GetDaemon<FileSystemDaemon>()->LoadZipArchive(filename);
}

Kernel::~Kernel()
{
    context->GetDaemon<FileSystemDaemon>()->CloseZipArchive();
}

void Kernel::Start() {
    while(running) {
        context->GetDaemon<SystemDaemon>()->Sleep(500);
    }
}

void Kernel::Stop() {
    running = false;
}

void Kernel::RunApp(WeakPointer<IApp> app) {
    //thread appThread(&IApp::Execute, app.Get());
    
    app->Execute();
    //appThread.join();

    Stop();
}

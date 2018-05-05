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

using EssexEngine::UniquePointer;
using EssexEngine::Core::Logging::LogDaemon;

using EssexEngine::Daemons::Window::WindowDef;
using EssexEngine::Daemons::Window::CanvasDef;

using EssexEngine::Daemons::FileSystem::FileSystemDaemon;
using EssexEngine::Daemons::Window::WindowDaemon;
using EssexEngine::Daemons::Gfx::GfxDaemon;
using EssexEngine::Daemons::System::SystemDaemon;

using EssexEngine::Kernel;

Kernel::Kernel(
    WeakPointer<Context> _context,
    std::string filename
): windowDef(
    UniquePointer<WindowDef>(
        new WindowDef(
            "Game Window",
            100,
            100,
            1024,
            768,
            [this]() {
                while(!context->GetStateStack()->IsEmpty()) {
                    context->GetStateStack()->Pop();
                }
            }
        )
    )
), canvasDef(
    UniquePointer<CanvasDef>(
        new CanvasDef(
            0,
            0,
            1024,
            768
        )
    )
), mainWindow(
    _context->GetDaemon<WindowDaemon>()->CreateWindow(
        windowDef.ToWeakPointer()
    )
), mainRenderContext(
    _context->GetDaemon<WindowDaemon>()->AddCanvas(
        mainWindow.ToWeakPointer(),
        canvasDef.ToWeakPointer()
    )
) {
    context = _context;
    
    context->GetDaemon<FileSystemDaemon>()->LoadZipArchive(filename);
    context->GetDaemon<GfxDaemon>()->Setup(mainRenderContext.ToWeakPointer());
    
    context->GetStateStack()->Push(context->GetBaseApp()->GetInitState());
    
    context->GetDaemon<LogDaemon>()->LogLine(
        "Starting Kernel [%s]",
        GetKernelVersion().c_str()
    );
    context->GetDaemon<LogDaemon>()->LogLine(
        "Starting Starting App [%s] [%s]",
        context->GetBaseApp()->GetAppName().c_str(),
        context->GetBaseApp()->GetAppVersion().c_str()
    );
    
}

Kernel::~Kernel()
{
    context->GetDaemon<FileSystemDaemon>()->CloseZipArchive();
    
    while(!context->GetStateStack()->IsEmpty()) {
        context->GetStateStack()->Pop();
    }
}

void Kernel::Start() {
    bool doLogic = false;
    bool doRedraw = false;

    context->GetDaemon<SystemDaemon>()->StartTimer();
    
    while(!context->GetStateStack()->IsEmpty()) {
        context->GetDaemon<WindowDaemon>()->RepaintWindows();

        int milliseconds = context->GetDaemon<SystemDaemon>()->GetElapsedTime();
        if (milliseconds >= 16) {//TODO: make this smarter
            doLogic = true;
            doRedraw = true;
            context->GetDaemon<SystemDaemon>()->StartTimer();
        } else {
            context->GetDaemon<SystemDaemon>()->Sleep(1);
        }
        
        if(doLogic) {
            for(int i = context->GetStateStack()->GetLength() - 1; i >= 0; i--) {
                context->GetStateStack()->GetRawData()[i]->Logic();
                
                if(context->GetStateStack()->GetRawData()[i]->PauseUnder()) {
                    break;
                }
            }
            doLogic = false;
        }
        
        if(doRedraw) {
            context->GetDaemon<GfxDaemon>()->StartRender(mainRenderContext.ToWeakPointer());
        
            for(int i = context->GetStateStack()->GetLength() - 1; i >= 0; i--) {
                context->GetStateStack()->GetRawData()[i]->Render();
                
                if(context->GetStateStack()->GetRawData()[i]->PauseUnder()) {
                    break;
                }
            }
        
            context->GetDaemon<GfxDaemon>()->FinishRender(mainRenderContext.ToWeakPointer());
            context->GetDaemon<WindowDaemon>()->RepaintCanvas(mainRenderContext.ToWeakPointer());
            
            doRedraw = false;
        }
        
        //check if state is complete.
        if(context->GetStateStack()->TopStateComplete()) {
            context->GetStateStack()->Pop();
        }
    }
}

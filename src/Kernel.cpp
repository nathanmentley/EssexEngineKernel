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

EssexEngine::Kernel::Kernel(WeakPointer<Context> _context, std::string filename)
{
    context = _context;
    initState = context->GetBaseApp()->GetInitState();
    
    context->GetDaemon<EssexEngine::Daemons::FileSystem::FileSystemDaemon>()->LoadZipArchive(filename);
    context->GetDaemon<EssexEngine::Daemons::Gfx::GfxDaemon>()->Setup();
	
	context->GetStateStack()->Push(initState);
    
    context->GetDaemon<EssexEngine::Core::Logging::LogDaemon>()->LogLine(
        "Starting Kernel [%s]",
        GetKernelVersion().c_str()
    );
    context->GetDaemon<EssexEngine::Core::Logging::LogDaemon>()->LogLine(
        "Starting Starting App [%s] [%s]",
        context->GetBaseApp()->GetAppName().c_str(),
        context->GetBaseApp()->GetAppVersion().c_str()
    );
    
}

EssexEngine::Kernel::~Kernel()
{
    context->GetDaemon<EssexEngine::Daemons::FileSystem::FileSystemDaemon>()->CloseZipArchive();
	
	while(!context->GetStateStack()->IsEmpty()) {
		context->GetStateStack()->Pop();
	}
}

void EssexEngine::Kernel::Start() {
    bool doLogic = false;
    bool doRedraw = false;
    
    context->GetDaemon<EssexEngine::Daemons::System::SystemDaemon>()->StartTimer();
    
    while(!context->GetStateStack()->IsEmpty()) {
        context->GetDaemon<EssexEngine::Daemons::Window::WindowDaemon>()->RepaintWindows();

        int milliseconds = context->GetDaemon<EssexEngine::Daemons::System::SystemDaemon>()->GetElapsedTime();
        if (milliseconds >= 16) {//TODO: make this smarter
            doLogic = true;
            doRedraw = true;
            context->GetDaemon<EssexEngine::Daemons::System::SystemDaemon>()->StartTimer();
        } else {
            context->GetDaemon<EssexEngine::Daemons::System::SystemDaemon>()->Sleep(1);
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
            context->GetDaemon<EssexEngine::Daemons::Gfx::GfxDaemon>()->StartRender();
        
            for(int i = context->GetStateStack()->GetLength() - 1; i >= 0; i--) {
                context->GetStateStack()->GetRawData()[i]->Render();
                
                if(context->GetStateStack()->GetRawData()[i]->PauseUnder()) {
                    break;
                }
            }
		
            context->GetDaemon<EssexEngine::Daemons::Gfx::GfxDaemon>()->FinishRender();
            
            doRedraw = false;
        }
        
        //check if state is complete.
        if(context->GetStateStack()->TopStateComplete()) {
            context->GetStateStack()->Pop();
        }
	}
}

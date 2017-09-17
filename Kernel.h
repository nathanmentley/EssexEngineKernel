#ifndef ENGINE_H
#define ENGINE_H

#include <EssexEngineCore/UniquePointer.h>
#include <EssexEngineCore/WeakPointer.h>
#include <EssexEngineCore/EssexEnvironment.h>
#include <EssexEngineCore/Context.h>
#include <EssexEngineCore/StateStack.h>
#include <EssexEngineCore/State.h>

#include <EssexEngineCore/LogDaemon.h>
#include <EssexEngineFileSystemDaemon/FileSystemDaemon.h>
#include <EssexEngineGfxDaemon/GfxDaemon.h>
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
			UniquePointer<Core::Models::IState> initState;
	};
};

#endif

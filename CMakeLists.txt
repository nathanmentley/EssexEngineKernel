ee_setup_project("EssexEngineKernel" "src/System/Kernel/")
target_link_libraries(EssexEngineKernel EssexEngineCore)
target_link_libraries(EssexEngineKernel EssexEngineFileSystemDaemon)

#files

file(GLOB EssexEngineKernel_HEADERS
    "src/System/Kernel/*.h"
)
file(GLOB EssexEngineKernel_SRC
    ${EssexEngineCore_HEADERS}
    "src/System/Kernel/*.cpp"
)

#setup headers

file(COPY ${EssexEngineKernel_HEADERS} DESTINATION "${CMAKE_BINARY_DIR}/lib/include/EssexEngineKernel/")

#setup build

add_library(EssexEngineKernel SHARED ${EssexEngineKernel_SRC})
target_link_libraries(EssexEngineKernel EssexEngineCore)
target_link_libraries(EssexEngineKernel EssexEngineSystemDaemon)
target_link_libraries(EssexEngineKernel EssexEngineFileSystemDaemon)
target_link_libraries(EssexEngineKernel EssexEngineGfxDaemon)
target_link_libraries(EssexEngineKernel EssexEngineWindowDaemon)
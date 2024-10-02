cmake_minimum_required(VERSION 3.10)

project(VoxelEngineSrc)

set(CMAKE_CXX_STANDARD 17)

file(GLOB_RECURSE HEADERS ${CMAKE_CURRENT_SOURCE_DIR}/*.hpp)
file(GLOB_RECURSE SOURCES ${CMAKE_CURRENT_SOURCE_DIR}/*.cpp)
list(REMOVE_ITEM SOURCES ${CMAKE_CURRENT_SOURCE_DIR}/voxel_engine.cpp)

add_library(${PROJECT_NAME} ${SOURCES} ${HEADERS})

option(VOXELENGINE_BUILD_WINDOWS_VCPKG "Build with vcpkg on Windows" ON)

find_package(OpenGL REQUIRED)
find_package(GLEW REQUIRED)
find_package(OpenAL REQUIRED)
find_package(CURL REQUIRED) 
find_package(ZLIB REQUIRED)
find_package(LibArchive REQUIRED)
find_package(jsoncpp REQUIRED)

if (NOT APPLE)
    find_package(EnTT REQUIRED)
endif()

if (WIN32)
    if(VOXELENGINE_BUILD_WINDOWS_VCPKG)
        set(LUA_LIBRARIES "${CMAKE_CURRENT_SOURCE_DIR}/../vcpkg/packages/luajit_x64-windows/lib/lua51.lib")
        set(LUA_INCLUDE_DIR "${CMAKE_CURRENT_SOURCE_DIR}/../vcpkg/packages/luajit_x64-windows/include/luajit")
        find_package(glfw3 REQUIRED)
        find_package(spng REQUIRED)
        find_package(glm REQUIRED)
        find_package(vorbis REQUIRED)
        set(PNGLIB spng::spng)
        set(VORBISLIB Vorbis::vorbis Vorbis::vorbisfile)
    else()
        find_package(Lua REQUIRED)
        set(PNGLIB spng)
        set(VORBISLIB vorbis vorbisfile)
        add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/libs/glfw)
    endif()
elseif(APPLE)
    find_package(PkgConfig REQUIRED)
    pkg_check_modules(JSONCPP REQUIRED jsoncpp)
    pkg_check_modules(LUAJIT REQUIRED luajit)
    pkg_check_modules(VORBIS REQUIRED vorbis vorbisfile)
    set(LUA_INCLUDE_DIR "/opt/homebrew/include/luajit-2.1")
    set(LUA_LIBRARIES "/opt/homebrew/lib/libluajit-5.1.a")
    find_package(PNG REQUIRED)
    set(PNGLIB PNG::PNG)
    set(VORBISLIB ${VORBIS_LDFLAGS})
else()
    find_package(PkgConfig REQUIRED)
    pkg_check_modules(JSONCPP REQUIRED jsoncpp)
    pkg_check_modules(LUAJIT REQUIRED luajit)
    pkg_check_modules(VORBIS REQUIRED vorbis vorbisfile)
    set(LUA_LIBRARIES ${LUAJIT_LIBRARIES})
    set(LUA_INCLUDE_DIR ${LUAJIT_INCLUDE_DIRS})
    find_package(PNG REQUIRED)
    find_package(CURL REQUIRED)
    set(PNGLIB PNG::PNG)
    set(VORBISLIB ${VORBIS_LDFLAGS})
endif()

set(LIBS "")

if(UNIX)
    find_package(glfw3 3.3 REQUIRED)
    find_package(Threads REQUIRED)
    set(LIBS ${LIBS} Threads::Threads)
endif()

include_directories(${LUA_INCLUDE_DIR} ${CURL_INCLUDE_DIR} ${JSONCPP_INCLUDE_DIRS})
target_include_directories(${PROJECT_NAME} PRIVATE ${CMAKE_CURRENT_SOURCE_DIR})

target_link_libraries(${PROJECT_NAME} 
    ${LIBS} 
    glfw 
    OpenGL::GL 
    ${OPENAL_LIBRARY} 
    GLEW::GLEW 
    ZLIB::ZLIB 
    ${VORBISLIB} 
    ${PNGLIB} 
    ${LUA_LIBRARIES} 
    ${CMAKE_DL_LIBS} 
    ${JSONCPP_LIBRARIES} 
    ${CURL_LIBRARIES} 
    LibArchive::LibArchive
)

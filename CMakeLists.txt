cmake_minimum_required(VERSION 3.30)
project(ReportBuilder)

set(CMAKE_CXX_STANDARD 20)

add_subdirectory(external/OpenXLSX)

add_executable(ReportBuilder src/main.cpp
        src/UI/UI.cpp
        src/UI/UI.h
        src/UI/Key.h
        src/UI/Color.h
        src/Configurations/MenuOptions.h
        src/Configurations/SizePriority.h
)

target_link_libraries(ReportBuilder PRIVATE OpenXLSX::OpenXLSX)
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
        src/Product/Product.h
        src/Product/ProductSize.h
        src/Product/TargetGroup.h
        src/XlsxHandler/XlsxHandler.cpp
        src/XlsxHandler/XlsxHandler.h
        src/Configurations/XlsxConfiguration.h
        src/Product/DataHandler/DataHandler.cpp
        src/Product/DataHandler/DataHandler.h
        src/ReportBuilder/Textile/Builder.cpp
        src/ReportBuilder/Textile/Builder.h
        src/Configurations/ReportConfigurations.h
        src/ReportBuilder/Priority/Priority.cpp
        src/ReportBuilder/Priority/Priority.h
        src/ReportBuilder/Validation/Validation.cpp
        src/ReportBuilder/Validation/Validation.h
)

target_link_libraries(ReportBuilder PRIVATE OpenXLSX::OpenXLSX)
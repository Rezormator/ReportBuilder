cmake_minimum_required(VERSION 3.30)
project(ReportBuilder)

set(CMAKE_CXX_STANDARD 20)

add_subdirectory(external/OpenXLSX)

add_executable(ReportBuilder src/main.cpp
        src/UI/UI.cpp
        src/UI/UI.h
        src/UI/Key.h
        src/UI/Color.h
        src/UI/MenuOptions.h
        src/ReportBuilder/Priority/SizePriority.h
        src/Product/Product.h
        src/Product/ProductSize.h
        src/Product/TargetGroup.h
        src/XlsxHandler/XlsxHandler.cpp
        src/XlsxHandler/XlsxHandler.h
        src/XlsxHandler/XlsxConfiguration.h
        src/Product/DataHandler/DataHandler.cpp
        src/Product/DataHandler/DataHandler.h
        src/ReportBuilder/Builder/Builder.cpp
        src/ReportBuilder/Builder/Builder.h
        src/ReportBuilder/ReportConfigurations.h
        src/ReportBuilder/Priority/Priority.cpp
        src/ReportBuilder/Priority/Priority.h
        src/ReportBuilder/Validation/Validation.cpp
        src/ReportBuilder/Validation/Validation.h
        src/ReportBuilder/ReportPresets.h
        src/ReportBuilder/ReportService/ReportService.cpp
        src/ReportBuilder/ReportService/ReportService.h
)

target_link_libraries(ReportBuilder PRIVATE OpenXLSX::OpenXLSX)
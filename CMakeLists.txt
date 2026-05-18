cmake_minimum_required(VERSION 3.30)
project(ReportBuilder)

set(CMAKE_CXX_STANDARD 20)

find_package(Qt6 REQUIRED COMPONENTS
        Core
        Widgets
        Concurrent
        PrintSupport
)

qt_standard_project_setup()

add_subdirectory(external/OpenXLSX)

qt_add_executable(ReportBuilder
        src/main.cpp

        # Application
        src/Application/Pipeline/ReportPipeline.cpp
        src/Application/Pipeline/ReportPipeline.h
        src/Application/Config/ReportDef.h
        src/Application/Config/StoreConfig.h
        src/Application/Config/TextileConfig.cpp
        src/Application/Config/FootwearConfig.cpp
        src/Application/XlsxLoader/XlsxLoader.cpp
        src/Application/XlsxLoader/XlsxLoader.h
        src/Application/PrintService/PrintService.cpp
        src/Application/PrintService/PrintService.h

        # Domain
        src/Domain/Product.h
        src/Domain/ProductSize.h
        src/Domain/TargetGroup.h
        src/Domain/SizeGrid/SizeGrid.cpp
        src/Domain/SizeGrid/SizeGrid.h
        src/Domain/Builders/Builders.cpp
        src/Domain/Builders/Builders.h
        src/Domain/Validation/Validation.cpp
        src/Domain/Validation/Validation.h

        # Infrastructure
        src/Infrastructure/AppConfiguration.h
        src/Infrastructure/AppSettings.h
        src/Infrastructure/DataHandler/DataHandler.cpp
        src/Infrastructure/DataHandler/DataHandler.h
        src/Infrastructure/SizePriority/SizePriority.cpp
        src/Infrastructure/SizePriority/SizePriority.h
        src/Infrastructure/XlsxReader/XlsxReader.cpp
        src/Infrastructure/XlsxReader/XlsxReader.h
        src/Infrastructure/XlsxWriter/XlsxWriter.cpp
        src/Infrastructure/XlsxWriter/XlsxWriter.h
        src/Infrastructure/PresetStorage/PresetStorage.cpp
        src/Infrastructure/PresetStorage/PresetStorage.h

        # UI
        src/UI/MainWindow/MainWindow.cpp
        src/UI/MainWindow/MainWindow.h
        src/UI/Widgets/ActionBar/ActionBar.cpp
        src/UI/Widgets/ActionBar/ActionBar.h
        src/UI/Widgets/PresetButton/PresetButton.cpp
        src/UI/Widgets/PresetButton/PresetButton.h
        src/UI/Widgets/PresetButton/PresetSettingsDialog.cpp
        src/UI/Widgets/PresetButton/PresetSettingsDialog.h
        src/UI/Widgets/CategoryTabs/CategoryTabs.cpp
        src/UI/Widgets/CategoryTabs/CategoryTabs.h
        src/UI/Widgets/SheetView/SheetView.cpp
        src/UI/Widgets/SheetView/SheetView.h
        src/UI/Widgets/SheetView/SheetTable.cpp
        src/UI/Widgets/SheetView/SheetTable.h
        src/UI/Widgets/StatusBar/StatusBar.cpp
        src/UI/Widgets/StatusBar/StatusBar.h
        src/UI/Theme/Theme.cpp
        src/UI/Theme/Theme.h
)

target_link_libraries(ReportBuilder PRIVATE
        Qt6::Core
        Qt6::Widgets
        Qt6::Concurrent
        Qt6::PrintSupport
        OpenXLSX::OpenXLSX
)

set_target_properties(ReportBuilder PROPERTIES
        WIN32_EXECUTABLE ON
)
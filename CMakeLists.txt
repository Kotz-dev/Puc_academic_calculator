cmake_minimum_required(VERSION 3.31)
project(EduMetrics)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_AUTOUIC ON)


# -------------------------
# Flags de compilação (compatível Windows/Linux)
# -------------------------
if(MSVC)
    # Define arquitetura x64 para MSVC
    add_compile_definitions(_WIN64 _AMD64_)

    # Debug com Visual Studio
    add_compile_options(/Zi /Od)
else()
    # Debug com GCC/Clang (Linux/Mac/MinGW)
    add_compile_options(-g -O0)
endif()



# -------------------------
# Bibliotecas externas
# -------------------------
find_package(fmt CONFIG REQUIRED)
find_package(Qt6 COMPONENTS Core Gui Widgets REQUIRED)
find_package(nlohmann_json CONFIG REQUIRED)

# -------------------------
# Includes
# -------------------------
include_directories(
        ${CMAKE_SOURCE_DIR}/include
        ${CMAKE_SOURCE_DIR}/include/core
        ${CMAKE_SOURCE_DIR}/include/data
        ${CMAKE_SOURCE_DIR}/include/io
        ${CMAKE_SOURCE_DIR}/include/managers
        ${CMAKE_SOURCE_DIR}/include/utils
        ${CMAKE_SOURCE_DIR}/include/windows
        ${CMAKE_CURRENT_BINARY_DIR}
)

# Definição do caminho das UI (Qt)
set(CMAKE_AUTOUIC_SEARCH_PATHS
        ${CMAKE_SOURCE_DIR}/forms
)

# -------------------------
# Executável
# -------------------------
add_executable(EduMetrics
        # UI/QRC
        ${CMAKE_SOURCE_DIR}/forms/MainWindow.ui
        ${CMAKE_SOURCE_DIR}/forms/option.ui
        ${CMAKE_SOURCE_DIR}/forms/aboutdialog.ui
        ${CMAKE_SOURCE_DIR}/resources/resources.qrc
        ${CMAKE_SOURCE_DIR}/forms/system_evaluation.ui

        # Entry point
        src/main.cpp

        # Core
        src/core/GradeSystem.cpp
        include/core/GradeSystem.h

        # Data
        src/data/StudentRecord.cpp
        include/data/StudentRecord.h

        # IO
        src/io/FileManager.cpp
        include/io/FileManager.h
        src/io/JsonParser.cpp
        include/io/JsonParser.h
        # Managers
        src/managers/UIManager.cpp
        include/managers/UIManager.h
        src/managers/LanguageManager.cpp
        include/managers/LanguageManager.h

        # Windows
        src/windows/MainWindow.cpp
        include/windows/MainWindow.h
        src/windows/PreferencesWindow.cpp
        include/windows/PreferencesWindow.h
        src/windows/system_evaluation.cpp
        include/windows/system_evaluation.h

        # Utils
        src/utils/GlobalAccess.cpp
        include/utils/GlobalAccess.h
        src/windows/aboutdialog.cpp
        include/windows/aboutdialog.h
        forms/aboutdialog.ui
        src/data/item_system_evaluation.cpp
        include/data/item_system_evaluation.h
)

# -------------------------
# Linkagem
# -------------------------

target_link_libraries(EduMetrics PRIVATE
        Qt::Core
        Qt::Gui
        Qt::Widgets
        fmt::fmt
        nlohmann_json::nlohmann_json
)

# Linux
if(UNIX AND NOT APPLE)

    get_target_property(QT_CORE_LOCATION Qt6::Core LOCATION)
    get_filename_component(QT_INSTALL_PATH "${QT_CORE_LOCATION}" DIRECTORY)
    get_filename_component(QT_INSTALL_PATH "${QT_INSTALL_PATH}/.." ABSOLUTE)

    set_target_properties(${PROJECT_NAME} PROPERTIES
            INSTALL_RPATH "$ORIGIN;${QT_INSTALL_PATH}/lib"
            BUILD_WITH_INSTALL_RPATH TRUE
    )

    if(EXISTS "${QT_INSTALL_PATH}/plugins/platforms/libqxcb.so")
        add_custom_command(TARGET ${PROJECT_NAME} POST_BUILD
                COMMAND ${CMAKE_COMMAND} -E make_directory
                "$<TARGET_FILE_DIR:${PROJECT_NAME}>/plugins/platforms/")
        add_custom_command(TARGET ${PROJECT_NAME} POST_BUILD
                COMMAND ${CMAKE_COMMAND} -E copy_if_different
                "${QT_INSTALL_PATH}/plugins/platforms/libqxcb.so"
                "$<TARGET_FILE_DIR:${PROJECT_NAME}>/plugins/platforms/")
    endif()
endif()

if(WIN32)
    set(DEBUG_SUFFIX "")
    if(MSVC AND CMAKE_BUILD_TYPE MATCHES "Debug")
        set(DEBUG_SUFFIX "d")
    endif()

    get_target_property(QT_CORE_LOCATION Qt6::Core LOCATION)
    get_filename_component(QT_INSTALL_PATH "${QT_CORE_LOCATION}" DIRECTORY)
    get_filename_component(QT_INSTALL_PATH "${QT_INSTALL_PATH}/.." ABSOLUTE)

    if(EXISTS "${QT_INSTALL_PATH}/bin")
        add_custom_command(TARGET ${PROJECT_NAME} POST_BUILD
                COMMAND ${CMAKE_COMMAND} -E copy_if_different
                "${QT_INSTALL_PATH}/bin/Qt6Core${DEBUG_SUFFIX}.dll"
                "${QT_INSTALL_PATH}/bin/Qt6Gui${DEBUG_SUFFIX}.dll"
                "${QT_INSTALL_PATH}/bin/Qt6Widgets${DEBUG_SUFFIX}.dll"
                "$<TARGET_FILE_DIR:${PROJECT_NAME}>/"
        )
    endif()

    if(EXISTS "${QT_INSTALL_PATH}/plugins/platforms/qwindows${DEBUG_SUFFIX}.dll")
        add_custom_command(TARGET ${PROJECT_NAME} POST_BUILD
                COMMAND ${CMAKE_COMMAND} -E make_directory
                "$<TARGET_FILE_DIR:${PROJECT_NAME}>/plugins/platforms/")
        add_custom_command(TARGET ${PROJECT_NAME} POST_BUILD
                COMMAND ${CMAKE_COMMAND} -E copy_if_different
                "${QT_INSTALL_PATH}/plugins/platforms/qwindows${DEBUG_SUFFIX}.dll"
                "$<TARGET_FILE_DIR:${PROJECT_NAME}>/plugins/platforms/")
    endif()
endif()
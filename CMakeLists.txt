# Большинство команд было скопировано из лекции, однако все равно опишу

# проверка на совместимость версии CMake
cmake_minimum_required(VERSION 3.28)
# название проекта и язык C++
project(CMakeSFMLProject LANGUAGES CXX)
# подключение модуля для скачки библиотеки
include(FetchContent)
# устанавливаем команду на скачивание статической библиотеки
set(BUILD_SHARED_LIBS OFF)
# скачать SFML с гитхаба определенной версии
FetchContent_Declare(SFML GIT_REPOSITORY https://github.com/SFML/SFML.git GIT_TAG 3.0.2)
# команда, ответственная за сборку SFML
FetchContent_MakeAvailable(SFML)
# указание на создание исполняемого файла
add_executable(proga source/main.cpp source/captcha.cpp)
# привязываем библиотеки SFML приватно к программе  
target_link_libraries(proga PRIVATE SFML::System SFML::Window SFML::Graphics)
# указываем где искать заголовочные файлы 
target_include_directories(proga PRIVATE include)
# копирование папки assets в 
add_custom_command(TARGET proga POST_BUILD COMMAND ${CMAKE_COMMAND} -E copy_directory "${CMAKE_CURRENT_SOURCE_DIR}/assets"   "${CMAKE_CURRENT_BINARY_DIR}/assets")
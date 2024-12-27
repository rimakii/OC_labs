cmake_minimum_required(VERSION 3.10)

# Название проекта
project(kp)

# Уѝтановка C++ ѝтандарта
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

# Пути к иѝходникам и библиотеке inih
set(SRC_DIR "${CMAKE_SOURCE_DIR}/src")
set(INIH_DIR "${CMAKE_SOURCE_DIR}/inih")

# Создание ѝтатичеѝкой библиотеки inih
add_library(inih STATIC
    "${INIH_DIR}/ini.c"                # Реализациѝ ini_parse
    "${INIH_DIR}/cpp/INIReader.cpp"    # Реализациѝ INIReader
)

# Подключение include-директорий длѝ библиотеки inih
target_include_directories(inih PUBLIC
    "${INIH_DIR}"                      # Длѝ ini.h
    "${INIH_DIR}/cpp"                  # Длѝ INIReader.h
)

# Добавление иѝполнѝемого файла cheker
add_executable(cheker
    src/cheker.cpp
)

target_include_directories(cheker PRIVATE include)

# Линковка cheker ѝ библиотекой inih
target_link_libraries(cheker PRIVATE inih)
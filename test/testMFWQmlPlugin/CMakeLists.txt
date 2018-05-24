set(CMAKE_AUTOMOC ON)

set(CMAKE_INCLUDE_CURRENT_DIR ON)

find_package(Qt5 REQUIRED COMPONENTS
    Core
    Widgets
    Quick
    )

add_executable(testMFWQmlPlugin testMFWQmlPlugin.cpp)
target_link_libraries(testMFWQmlPlugin Qt5::Core Qt5::Widgets Qt5::Quick)
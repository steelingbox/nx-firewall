enable_testing()

set(CMAKE_AUTOMOC ON)

set(CMAKE_INCLUDE_CURRENT_DIR ON)

find_package(Qt5Test REQUIRED)

add_executable(testEntities TestEntities.cpp $<TARGET_OBJECTS:entities>)
target_link_libraries(testEntities Qt5::Test)

add_executable(testGateways TestIptablesRulesComposer.cpp $<TARGET_OBJECTS:entities> $<TARGET_OBJECTS:gateways>)
target_link_libraries(testGateways Qt5::Test)

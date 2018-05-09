enable_testing()

# Tell CMake to run moc when necessary:
set(CMAKE_AUTOMOC ON)

# As moc files are generated in the binary dir, tell CMake
# to always look for includes there:
set(CMAKE_INCLUDE_CURRENT_DIR ON)

find_package(Qt5Test REQUIRED)

add_executable(testEntities TestEntities.cpp $<TARGET_OBJECTS:entities>)
target_link_libraries(testEntities Qt5::Test)

add_executable(testGateways TestIptablesRulesComposer.cpp $<TARGET_OBJECTS:entities> $<TARGET_OBJECTS:gateways>)
target_link_libraries(testGateways Qt5::Test)

#find_package(PkgConfig REQUIRED)
#
#pkg_check_modules(mnl libmnl IMPORTED_TARGET)
#pkg_check_modules(nftnl libnftnl IMPORTED_TARGET)
#
#add_executable(testLibnftnl TestLibnftnl.cpp)
#target_link_libraries(testLibnftnl Qt5::Test PkgConfig::nftnl PkgConfig::mnl)
#
#add_test(testLibnftnl testLibnftnl)

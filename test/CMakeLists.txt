enable_testing()

set(CMAKE_AUTOMOC ON)

set(CMAKE_INCLUDE_CURRENT_DIR ON)

find_package(Qt5Test REQUIRED)

add_executable(testEntities TestEntities.cpp $<TARGET_OBJECTS:entities>)
target_link_libraries(testEntities Qt5::Test)

add_executable(testIptablesRuleGenerator TestIptablesRuleGenerator.cpp $<TARGET_OBJECTS:entities> $<TARGET_OBJECTS:gateways>)
target_link_libraries(testIptablesRuleGenerator Qt5::Test)

add_executable(testIptable TestIptables.cpp $<TARGET_OBJECTS:entities> $<TARGET_OBJECTS:gateways>)
target_link_libraries(testIptable Qt5::Test)

add_executable(testQVariantRuleSetConverter $<TARGET_OBJECTS:entities> TestQVariantRuleSetConverter.cpp)
target_link_libraries(testQVariantRuleSetConverter Qt5::Test)

find_package(Qt5Network REQUIRED)
add_executable(testThreeStepsFirewall $<TARGET_OBJECTS:entities> $<TARGET_OBJECTS:gateways> TestTreeStepsFirewall.cpp)
target_link_libraries(testThreeStepsFirewall Qt5::Test Qt5::Network)

add_subdirectory(testNomadFirewallQmlPlugin)
set(CMAKE_AUTOMOC ON)

set(CMAKE_INCLUDE_CURRENT_DIR ON)

find_package(Qt5 REQUIRED COMPONENTS
    Core
    Widgets
    Quick
    )

add_executable(testNomadFirewallQmlPlugin testNomadFirewallQmlPlugin.cpp)
target_link_libraries(testNomadFirewallQmlPlugin Qt5::Core Qt5::Widgets Qt5::Quick)


find_package(KF5 ${KF5_MIN_VERSION} REQUIRED COMPONENTS
    I18n
    Auth
    )

add_executable(testKAuthHelper TestKAuthHelper.cpp)
target_link_libraries(testKAuthHelper Qt5::Core KF5::I18n KF5::Auth)


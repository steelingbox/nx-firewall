find_package(Qt5 CONFIG REQUIRED COMPONENTS Core Quick)

find_package(KF5 ${KF5_MIN_VERSION} REQUIRED COMPONENTS
    CoreAddons
    I18n
    Auth)

set(MFW_PLUGIN_SRC
    NomadFirewallQmlPlugin.cpp
    NomadFirewallQmlPlugin.h
    NetFilterToolKauthInterface.cpp
    NetFilterToolKauthInterface.h
    SettingsManagerKauthInterface.cpp
    SettingsManagerKauthInterface.h
    RuleListModel.cpp
    RuleListModel.h
    ModuleController.cpp
    ModuleController.h)

add_library(nomad_firewall_qml_plugin SHARED ${MFW_PLUGIN_SRC} $<TARGET_OBJECTS:entities> $<TARGET_OBJECTS:gateways>)

target_include_directories(nomad_firewall_qml_plugin PUBLIC ${PROJECT_SOURCE_DIR})

target_link_libraries(nomad_firewall_qml_plugin
    Qt5::Core
    Qt5::Quick
    KF5::CoreAddons
    KF5::Auth
    KF5::I18n)

set(INSTALL_PATH ${QML_INSTALL_DIR}/org/nomad/firewall)

install(TARGETS nomad_firewall_qml_plugin DESTINATION ${INSTALL_PATH})
install(FILES qmldir DESTINATION ${INSTALL_PATH})

add_subdirectory(helper)
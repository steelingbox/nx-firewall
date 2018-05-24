find_package(Qt5 CONFIG REQUIRED COMPONENTS Core Quick)

find_package(KF5 ${KF5_MIN_VERSION} REQUIRED COMPONENTS
    CoreAddons
    I18n
    Auth)

set(MFW_PLUGIN_SRC
    MFWQmlPlugin.cpp
    MFWQmlPlugin.h
    NetFilterToolKauthInterface.cpp
    NetFilterToolKauthInterface.h
    SettingsManagerKauthInterface.cpp
    SettingsManagerKauthInterface.h )

add_library(mfw_plugin SHARED ${MFW_PLUGIN_SRC} $<TARGET_OBJECTS:entities> $<TARGET_OBJECTS:gateways>)

target_include_directories(mfw_plugin PUBLIC ${PROJECT_SOURCE_DIR})

target_link_libraries(mfw_plugin
    Qt5::Core
    Qt5::Quick
    KF5::CoreAddons
    KF5::Auth
    KF5::I18n)

set(INSTALL_PATH ${QML_INSTALL_DIR}/org/maui/mfw)

install(TARGETS mfw_plugin DESTINATION ${INSTALL_PATH})
install(FILES qmldir DESTINATION ${INSTALL_PATH})

add_subdirectory(helper)
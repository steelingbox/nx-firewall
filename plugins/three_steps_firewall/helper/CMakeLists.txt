# Find includes in corresponding build directories
include_directories(${CMAKE_BINARY_DIR})

# Instruct CMake to run moc automatically when needed.
set(CMAKE_AUTOMOC ON)

find_package(Qt5 ${QT_MIN_VERSION} CONFIG REQUIRED COMPONENTS
    Core
    )


find_package(KF5 ${KF5_MIN_VERSION} REQUIRED COMPONENTS
    I18n
    Auth
    )


add_executable(mfw_helper MFW_helper.cpp MFW_helper.h $<TARGET_OBJECTS:entities> $<TARGET_OBJECTS:gateways>)
target_link_libraries(mfw_helper Qt5::Core KF5::I18n KF5::Auth )
target_include_directories(mfw_helper PUBLIC ${PROJECT_SOURCE_DIR})

kauth_install_actions(org.maui.mfw org.maui.mfw.actions)

install(TARGETS mfw_helper DESTINATION ${KAUTH_HELPER_INSTALL_DIR})
kauth_install_helper_files(mfw_helper org.maui.mfw root)


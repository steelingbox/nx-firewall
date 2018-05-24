set(CMAKE_AUTOMOC ON)

set(CMAKE_INCLUDE_CURRENT_DIR ON)

find_package(Qt5Test REQUIRED)

add_executable(mfw-service main.cpp $<TARGET_OBJECTS:entities> $<TARGET_OBJECTS:gateways>)
target_link_libraries(mfw-service Qt5::Test)

install(TARGETS mfw-service RUNTIME DESTINATION bin)
install(FILES org.maui.mfw.service DESTINATION /etc/systemd/system/)
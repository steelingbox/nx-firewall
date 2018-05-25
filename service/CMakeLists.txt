set(CMAKE_AUTOMOC ON)

set(CMAKE_INCLUDE_CURRENT_DIR ON)

find_package(Qt5Test REQUIRED)

add_executable(nomad-service main.cpp $<TARGET_OBJECTS:entities> $<TARGET_OBJECTS:gateways>)
target_link_libraries(nomad-service Qt5::Test)

install(TARGETS nomad-service RUNTIME DESTINATION bin)
install(FILES org.nomad.firewall.service DESTINATION /etc/systemd/system/)
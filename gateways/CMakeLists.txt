set(GATEWAYS_SRCS
    IptablesRuleGenerator.cpp
    IptablesRuleGenerator.h
    Iptables.cpp
    Iptables.h
    JsonSettings.cpp
    JsonSettings.h)

add_library(gateways OBJECT ${GATEWAYS_SRCS})

target_compile_options(gateways PUBLIC -fPIC -fexceptions)
target_include_directories(gateways PUBLIC ${Qt5Core_INCLUDE_DIRS})
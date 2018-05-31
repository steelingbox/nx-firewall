set(ENTITIES_SRCS
    Rule.cpp
    Rule.h
    RuleSet.cpp
    RuleSet.h
    Service.cpp
    Service.h
    NetFilterTool.cpp
    NetFilterTool.h
    Firewall.cpp
    Firewall.h
    SettingsManager.h
    QVariantRuleSetConverter.cpp
    QVariantRuleSetConverter.h)

add_library(entities OBJECT ${ENTITIES_SRCS})

target_compile_options(entities PUBLIC -fPIC -fexceptions)
target_include_directories(entities PUBLIC ${Qt5Core_INCLUDE_DIRS})
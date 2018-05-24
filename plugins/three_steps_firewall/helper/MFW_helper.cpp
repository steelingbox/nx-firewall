//
// Created by alexis on 5/23/18.
//

#include <entities/QVariantRuleSetConverter.h>

#include <gateways/JsonSettings.h>
#include <gateways/Iptables.h>
#include "MFW_helper.h"

ActionReply MFW_helper::apply(const QVariantMap settings)
{
    KAuth::ActionReply reply;

    auto ruleset = QVariantRuleSetConverter::toRuleSet(settings.value("ruleset").toMap());
    Iptables iptables;
    iptables.apply(ruleset);

    return reply;
}

ActionReply MFW_helper::save(const QVariantMap settings)
{
    KAuth::ActionReply reply;

    JsonSettings jsonSettings("/etc/mfw_rules.json");
    jsonSettings.save(settings);

    return reply;
}

KAUTH_HELPER_MAIN("org.maui.mfw", MFW_helper)
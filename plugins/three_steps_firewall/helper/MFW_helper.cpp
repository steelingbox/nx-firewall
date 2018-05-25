//
// Created by alexis on 5/23/18.
//

#include <QDebug>

#include <entities/QVariantRuleSetConverter.h>

#include <gateways/JsonSettings.h>
#include <gateways/Iptables.h>
#include "MFW_helper.h"

ActionReply MFW_helper::apply(const QVariantMap data)
{
    try {
        auto ruleset = QVariantRuleSetConverter::toRuleSet(data);
        Iptables iptables;
        iptables.apply(ruleset);
    } catch (QVariantRuleSetConverter::ConversionException ex) {
        qWarning() << "Unable to parse input ruleset" << data;
        return ActionReply::HelperErrorReply();
    }

    return ActionReply::SuccessReply();
}

ActionReply MFW_helper::save(const QVariantMap settings)
{
    JsonSettings jsonSettings("/etc/mfw_rules.json");
    jsonSettings.save(settings);

    return ActionReply::SuccessReply();
}
MFW_helper::MFW_helper() { }

KAUTH_HELPER_MAIN("org.maui.mfw", MFW_helper)
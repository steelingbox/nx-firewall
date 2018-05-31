//
// Created by alexis on 5/23/18.
//

#include <QDebug>

#include <entities/QVariantRuleSetConverter.h>

#include <entities/ThreeStepsFirewall.h>
#include <gateways/JsonSettings.h>
#include <gateways/Iptables.h>
#include "NomadFirewallKAuthHelper.h"

ActionReply NomadFirewallKAuthHelper::apply(const QVariantMap data)
{
    try {
        Iptables iptables;
        auto ruleset = QVariantRuleSetConverter::toRuleSet(data);
        iptables.apply(ruleset);
    } catch (QVariantRuleSetConverter::ConversionException ex) {
        qCritical() << "Unable to parse input ruleset" << data;
        return ActionReply::HelperErrorReply();
    }

    return ActionReply::SuccessReply();
}

ActionReply NomadFirewallKAuthHelper::save(const QVariantMap settings)
{
    JsonSettings jsonSettings("/etc/nomad_firewall_rules.json");
    jsonSettings.save(settings);

    Iptables iptables;

    ThreeStepsFirewall fw;
    fw.setNetfilterTool(&iptables);
    fw.loadSettings(settings);
    fw.applySettings();

    return ActionReply::SuccessReply();
}
NomadFirewallKAuthHelper::NomadFirewallKAuthHelper() { }

KAUTH_HELPER_MAIN("org.nomad.firewall", NomadFirewallKAuthHelper)
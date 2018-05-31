//
// Created by alexis on 5/23/18.
//

#include <QDebug>

#include <entities/QVariantRuleSetConverter.h>

#include <entities/Firewall.h>
#include <gateways/JsonSettings.h>
#include <gateways/Iptables.h>
#include "NomadFirewallKAuthHelper.h"

ActionReply NomadFirewallKAuthHelper::apply(const QVariantMap settings)
{
    JsonSettings jsonSettings;
    jsonSettings.save(settings);

    Firewall fw;
    fw.setSettings(settings);
    auto ruleSet  = fw.getRuleSet();

    Iptables iptables;
    iptables.apply(ruleSet);

    return ActionReply::SuccessReply();
}
NomadFirewallKAuthHelper::NomadFirewallKAuthHelper() { }

KAUTH_HELPER_MAIN("org.nomad.firewall", NomadFirewallKAuthHelper)
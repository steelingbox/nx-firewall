//
// Created by alexis on 5/9/18.
//

#include <QStandardPaths>
#include <QProcess>
#include <QDebug>

#include "IptablesRuleGenerator.h"
#include "Iptables.h"
#include "Iptables.h"
#include <QProcess>
#include <QStandardPaths>
#include "NetworkFilteringManagementTool.h"

bool Iptables::isAvailable()
{
    QString binPath = getBinaryPath();
    return !binPath.isEmpty();
}

void Iptables::apply(const RuleSet& ruleSet)
{
    auto instructions = generateIptablesInstructions(ruleSet);
    runIptableInstructions(instructions);
}

void Iptables::runIptableInstructions(const QStringList& iptablesInstructions) const
{
    auto iptables = new QProcess();
    iptables->setProgram(getBinaryPath());

    for (const QString& instruction: iptablesInstructions) {
        iptables->setArguments(instruction.split(" "));
        iptables->start();
        iptables->waitForFinished();
        if (iptables->exitCode()!=0)
            qCritical() << "Unable to run:" << getBinaryPath() << instruction
                        << iptables->readAllStandardError();
        iptables->close();
    }
}

QStringList Iptables::generateIptablesInstructions(const RuleSet& ruleSet) const
{
    QStringList iptablesInstructions;

    iptablesInstructions << "--flush";

    iptablesInstructions << IptablesRuleGenerator::generateDefaultPolicy("INPUT", ruleSet.getDefaultIncomingPolicy());
    iptablesInstructions << IptablesRuleGenerator::generateDefaultPolicy("OUTPUT", ruleSet.getDefaultOutgoingPolicy());

    iptablesInstructions << generateIptableRules(ruleSet);

    return iptablesInstructions;
}

QStringList Iptables::generateIptableRules(const RuleSet& ruleSet) const
{
    const auto incomingPolicy = ruleSet.getDefaultIncomingPolicy();
    const auto outgoingPolicy = ruleSet.getDefaultOutgoingPolicy();
    const QList<Rule>& ruleList = ruleSet.getRules();

    QStringList rulesInstructions;
    for (const Rule& rule: ruleList) {
        auto oppositeChainPolicy = getOppositeChainPolicy(incomingPolicy, outgoingPolicy, rule);

        if (areReverseConnectionsPossible(oppositeChainPolicy))
            rulesInstructions << IptablesRuleGenerator::generateRule(rule);
        else
            rulesInstructions << IptablesRuleGenerator::generateTwoWayCommunicationRules(rule);
    }
    return rulesInstructions;
}

bool Iptables::areReverseConnectionsPossible(const Rule::Action& oppositeChainPolicy) const
{
    return oppositeChainPolicy==Rule::ALLOW;
}

Rule::Action Iptables::getOppositeChainPolicy(const Rule::Action& incomingPolicy, const Rule::Action& outgoingPolicy,
        const Rule& rule) const
{
    Rule::Action oppositeChainPolicy;
    if (rule.getDirection()==Rule::INCOMING)
        oppositeChainPolicy = outgoingPolicy;
    else
        oppositeChainPolicy = incomingPolicy;
    return oppositeChainPolicy;
}

QString Iptables::getBinaryPath() const
{
    auto binPath = QStandardPaths::findExecutable("iptables");
    return binPath;
}

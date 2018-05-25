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
#include "../entities/NetFilterTool.h"

bool Iptables::isAvailable()
{
    return !executablePath.isEmpty();
}

void Iptables::apply(const RuleSet& ruleSet)
{
    if (isAvailable()) {
        auto instructions = generateIptablesInstructions(ruleSet);
        runIptableInstructions(instructions);
    }
    else
        qCritical() << "Unable to locate iptables executable";
}

void Iptables::runIptableInstructions(const QStringList& iptablesInstructions) const
{
    auto iptables = new QProcess();
    iptables->setProgram(executablePath);

    for (const QString& instruction: iptablesInstructions) {
        iptables->setArguments(instruction.split(" "));
        iptables->start();
        iptables->waitForFinished();
        if (iptables->exitCode()!=0)
            qCritical() << "Unable to run:" << executablePath << instruction
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
    const QList<Rule*>& ruleList = ruleSet.getRules();

    QStringList rulesInstructions;
    for (const Rule* rule: ruleList) {
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
        const Rule* rule) const
{
    Rule::Action oppositeChainPolicy;
    if (rule->getDirection()==Rule::INCOMING)
        oppositeChainPolicy = outgoingPolicy;
    else
        oppositeChainPolicy = incomingPolicy;
    return oppositeChainPolicy;
}

Iptables::Iptables()
{
    executablePath = QStandardPaths::findExecutable("iptables");
    if (executablePath.isEmpty())
        executablePath = QStandardPaths::findExecutable("iptables",
                {"/sbin/", "/usr/bin/", "/usr/sbin"});
}

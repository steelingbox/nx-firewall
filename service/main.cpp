#include <QCoreApplication>
#include <QCommandLineParser>

#include "../gateways/JsonSettings.h"
#include "../gateways/Iptables.h"
#include "../entities/Firewall.h"

QCommandLineParser* getParser(const QCoreApplication& app);
QVariantMap readSettings();
RuleSet getRuleSet(const QVariantMap& settings);
int main(int argc, char** argv)
{
    QCoreApplication app(argc, argv);
    QCoreApplication::setApplicationName("nomad-firewall-cli");
    QCoreApplication::setApplicationVersion("1.0");

    auto parser = getParser(app);

    if (parser->isSet("restore")) {
        auto settings = readSettings();
        RuleSet ruleSet = getRuleSet(settings);

        auto iptables = new Iptables();
        iptables->apply(ruleSet);

        return 0;
    }
    else parser->showHelp(1);
}
RuleSet getRuleSet(const QVariantMap& settings)
{
    Firewall fw;
    fw.setSettings(settings);

    auto ruleSet = fw.getRuleSet();
    return ruleSet;
}
QVariantMap readSettings()
{
    auto settingsManager = new JsonSettings();
    auto settings = settingsManager->load();
    delete(settingsManager);
    return settings;
}

QCommandLineParser* getParser(const QCoreApplication& app)
{
    auto parser = new QCommandLineParser();
    parser->setApplicationDescription("Maui Firewall Service helper");
    QCommandLineOption restoreOption{"restore", "Read firewall config and applies to the system."};
    parser->addOption(restoreOption);

    parser->process(app);
    return parser;
}
#include <QCoreApplication>
#include <QCommandLineParser>

#include "../gateways/JsonSettings.h"
#include "../gateways/Iptables.h"
#include "../entities/ThreeStepsFirewall.h"

QCommandLineParser* getParser(const QCoreApplication& app);
int main(int argc, char** argv)
{
    QCoreApplication app(argc, argv);
    QCoreApplication::setApplicationName("nomad-firewall-cli");
    QCoreApplication::setApplicationVersion("1.0");

    auto parser = getParser(app);

    if (parser->isSet("restore")) {
        auto settings = new JsonSettings("/etc/nomad_firewall_rules.json");
        auto iptables = new Iptables();

        ThreeStepsFirewall fw;
        fw.setSettingsManager(settings);
        fw.setNetfilterTool(iptables);

        fw.loadSettings();
        fw.resetProfile();

        return 0;
    }
    else parser->showHelp(1);
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
//
// Created by alexis on 5/22/18.
//

#ifndef NOMAD_FIREWALL_NETFILTERTOOLKAUTHINTERFACE_H
#define NOMAD_FIREWALL_NETFILTERTOOLKAUTHINTERFACE_H

#include <entities/NetFilterTool.h>

class NetFilterToolKauthInterface : public NetFilterTool {
public:
    NetFilterToolKauthInterface();

    bool isAvailable() override;
    void apply(const RuleSet& ruleSet) override;

};

#endif //NOMAD_FIREWALL_NETFILTERTOOLKAUTHINTERFACE_H

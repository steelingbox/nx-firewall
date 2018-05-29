import QtQuick 2.0
import QtQuick.Controls 1.4
import QtQuick.Layouts 1.0

import org.kde.plasma.components 2.0 as PlasmaComponents

import org.nomad.firewall 1.0 as NomadFirewall

ColumnLayout  {
    height: 400
    width: 400

    ListView {
        id: listView
        Layout.fillWidth: true
        Layout.fillHeight: true
        model: NomadFirewall.Controller.rules

        delegate: RowLayout {
            height: 30
            width: 400
            Text { text: direction }
            Text { text: sourceAddr }
            Text { text: sourcePorts }
            Text { text: destinationAddr }
            Text { text: destinationPorts }
            Text { text: iface }
            Text { text: action }

            Component.onCompleted: console.warn(" " + index + " " + iface)
        }
    }
    Button {
        Layout.fillWidth: true
        text: "Add Rule"
        onClicked: {
            var newRule = ruleFactory.createObject(parent, {
                direction: "INCOMING",
                sourceAddr: "10.0.0.2",
                sourcePorts: [80,443],
                destinationAddr: "10.0.0.2",
                destinationPorts: [80,443],
                iface: "lo",
                action: "DROP",
            })

            NomadFirewall.Controller.rules.append(newRule);
        }
    }

    Component {
        id: ruleFactory
        NomadFirewall.Rule {}
    }


}
import QtQuick 2.0
import QtQuick.Controls 1.4
import QtQuick.Layouts 1.0

import org.kde.plasma.components 2.0 as PlasmaComponents

import org.nomad.firewall 1.0

ColumnLayout  {
    height: 400
    width: 300

    ListView {
        model: ThreeStepsFirewall.rules

        delegate: Rectangle {
            height: 30

        }
    }
    Button {
        onClicked: {}
    }
}
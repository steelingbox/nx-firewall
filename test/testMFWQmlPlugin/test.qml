import QtQuick 2.0
import QtQuick.Controls 1.4
import QtQuick.Layouts 1.0
import org.kde.plasma.components 2.0 as PlasmaComponents

import org.maui.mfw 1
ColumnLayout {
    height: 100
    width: 200
    Text {
        id: t1;
        text: {
            var res = "Firewall mode: "
            if (ThreeStepsFirewall.profile == 0)
                return res + "Permissive";
            if (ThreeStepsFirewall.profile == 1)
                return res + "Stealth";
            if (ThreeStepsFirewall.profile == 2)
                return res + "Paranoid";
        }
    }

    PlasmaComponents.Slider {
        Layout.fillWidth: true
        maximumValue: 2
        minimumValue: 0
        stepSize: 1.0
        tickmarksEnabled: true

        height: 20

        onValueChanged: ThreeStepsFirewall.profile = value

        Component.onCompleted: {value = ThreeStepsFirewall.profile}
    }


    Component.onCompleted: {
        ThreeStepsFirewall.loadSettings()
    }

     Timer {
            interval: 500; running: true; repeat: false
            onTriggered: ThreeStepsFirewall.profile = 0
        }
}
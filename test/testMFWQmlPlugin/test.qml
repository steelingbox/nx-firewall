import QtQuick 2.0
import QtQuick.Controls 1.4
import QtQuick.Layouts 1.0

import org.kde.plasma.components 2.0 as PlasmaComponents

import org.maui.mfw 1
RowLayout {
    height: 100
    width: 300
    spacing: 12

    Image {
        Layout.maximumHeight: 68; Layout.maximumWidth: 68;
        Layout.minimumHeight: 68; Layout.minimumWidth: 68;
        fillMode: Image.PreserveAspectFit
        source: "http://pfsensesetup.com/wp-content/uploads/2013/11/77-Free-Clipart-Illustration-Of-A-Computer-Firewall.jpg"
    }

    ColumnLayout {
        Layout.fillWidth: true

        PlasmaComponents.Slider {
            Layout.maximumHeight: 20
            Layout.fillWidth: true
            maximumValue: 2
            minimumValue: 0
            stepSize: 1.0
            tickmarksEnabled: true

            height: 20

            value: ThreeStepsFirewall.profile
            onValueChanged: ThreeStepsFirewall.profile != value ? ThreeStepsFirewall.profile = value : ThreeStepsFirewall.profile
        }

        RowLayout {
            Layout.fillWidth: true;
            Text { Layout.fillWidth: true; text: "Permissive"; font.pointSize: 7; horizontalAlignment: Text.AlignLeft}
            Text { Layout.fillWidth: true; text: "Stealth"; font.pointSize: 7; horizontalAlignment: Text.AlignCenter }
            Text { Layout.fillWidth: true; text: "Paranoid"; font.pointSize: 7; horizontalAlignment: Text.AlignRight }
        }



        Component.onCompleted: {
            ThreeStepsFirewall.loadSettings()
        }

         Timer {
                interval: 500; running: true; repeat: false
                onTriggered: ThreeStepsFirewall.profile = 0
            }
    }

    PlasmaComponents.ToolButton {
        iconSource: "application-menu"

    }
}

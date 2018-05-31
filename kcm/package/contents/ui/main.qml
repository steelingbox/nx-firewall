import QtQuick 2.6
import QtQuick.Layouts 1.3
import QtQuick.Controls 2.0

import org.kde.plasma.core 2.0 as PlasmaCore
import org.kde.plasma.components 2.0 as PlasmaComponents
import org.kde.plasma.extras 2.0 as PlasmaExtras

import org.kde.kcm 1.0
import org.nomad.firewall 1.0 as NomadFirewall

Item {
    id: mainWindow

    implicitWidth: units.gridUnit * 44
    implicitHeight: units.gridUnit * 50
    clip: true

    Component.onCompleted: {
        console.warn("ConfigModule: " + ConfigModule)
        ConfigModule.quickHelp = i18nd(
                    "org.nxos.firewall",
                    "This module lets you configure your system firewall policies.")

        ConfigModule.onSaveRequested.connect(
                    NomadFirewall.Controller.applyConfig)
        ConfigModule.onLoadRequested.connect(
                    NomadFirewall.Controller.resetConfig)
        ConfigModule.needsSave = Qt.binding(function () {
            return !NomadFirewall.Controller.isInSync
        })
    }

    function isSaveRequired() {
        var profileChanged = profileSlider.value !== NomadFirewall.Controller.profile
        var rulesChanged = NomadFirewall.Controller.ru
    }

    PlasmaCore.FrameSvgItem {
        anchors.fill: parent
        imagePath: "dialogs/background"
        enabledBorders: PlasmaCore.FrameSvg.NoBorder
    }

    GridLayout {
        anchors.fill: parent
        columns: 3

        PlasmaComponents.Label {
            Layout.fillWidth: true
            Layout.topMargin: 20
            Layout.leftMargin: 40
            Layout.rightMargin: 80
            Layout.columnSpan: 3

            text: "Base Profile"
            font.pointSize: 12
        }

        PlasmaComponents.Slider {
            id: profileSlider
            Layout.maximumHeight: 20
            Layout.fillWidth: true
            Layout.topMargin: 12
            Layout.leftMargin: 60
            Layout.rightMargin: 80
            Layout.columnSpan: 3

            maximumValue: 2
            minimumValue: 0
            stepSize: 1.0
            tickmarksEnabled: true

            height: 20

            value: NomadFirewall.Controller.profile
            onValueChanged: if (NomadFirewall.Controller.profile !== value) {
                                NomadFirewall.Controller.profile = value
                            }
        }

        PlasmaComponents.Label {
            text: "Permissive"
            font.bold: profileSlider.value == 0
            horizontalAlignment: Text.AlignLeft

            Layout.fillWidth: true
            Layout.leftMargin: 40
        }

        PlasmaComponents.Label {
            text: "Stealth"
            font.bold: profileSlider.value == 1
            horizontalAlignment: Text.AlignHCenter

            Layout.fillWidth: true
        }

        PlasmaComponents.Label {
            text: "Paranoid"
            font.bold: profileSlider.value == 2
            horizontalAlignment: Text.AlignRight

            Layout.fillWidth: true
            Layout.rightMargin: 60
        }

        PlasmaCore.FrameSvgItem {
            Layout.topMargin: 30
            Layout.fillHeight: true
            Layout.fillWidth: true
            Layout.columnSpan: 3

            imagePath: "dialogs/background"

            ListView {
                anchors.fill: parent
                headerPositioning: ListView.OverlayHeader
                header: RowLayout {
                    PlasmaComponents.Label {
                        Layout.fillWidth: true
                        Layout.leftMargin: 12
                        Layout.topMargin: 6

                        text: "Custom Rules:"
                        font.pointSize: 12
                    }
                }

                model: NomadFirewall.Controller.rules
                delegate: RuleListItem {
                }
            }
        }
    }
}

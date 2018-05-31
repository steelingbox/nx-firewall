import QtQuick 2.0
import QtQuick.Controls 1.4
import QtQuick.Layouts 1.0

import org.kde.plasma.components 2.0 as PlasmaComponents

import org.nomad.firewall 1
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

    ComboBox {
        Layout.fillWidth: true
        currentIndex: Firewall.profile
        model: ListModel {
            id: cbItems
            ListElement { text: "Permissive"; }
            ListElement { text: "Stealth"; }
            ListElement { text: "Paranoid"; }
        }
        width: 200
        onCurrentIndexChanged: Firewall.profile != currentIndex ? Firewall.profile = currentIndex : Firewall.profile
    }

    PlasmaComponents.ToolButton {
        iconSource: "application-menu"

    }
}

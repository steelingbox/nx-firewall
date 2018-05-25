import QtQuick 2.0

import org.maui.mfw 1
Item {
    Text {
        id: t1;
        text: ThreeStepsFirewall.profile
    }
    Component.onCompleted: {
        ThreeStepsFirewall.loadSettings()
    }

     Timer {
            interval: 500; running: true; repeat: false
            onTriggered: ThreeStepsFirewall.profile = 0
        }
}
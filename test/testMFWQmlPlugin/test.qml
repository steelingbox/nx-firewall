import QtQuick 2.0

import org.maui.mfw 1
Item {

    Component.onCompleted: {
        console.log("Current profile: " + ThreeStepsFirewall.profile)
        ThreeStepsFirewall.loadSettings()
    }
}
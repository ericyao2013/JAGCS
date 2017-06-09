import QtQuick 2.6
import QtQuick.Controls 2.0
import QtQuick.Layouts 1.3
import JAGCS 1.0

import "qrc:/Controls"

ColumnLayout {
    id: root

    property var instruments

    Repeater {
        model: instruments

        Loader {
            Layout.fillWidth: true
            sourceComponent: createInstrument(modelData)
            onItemChanged: if (item) item.objectName = modelData
        }
    }

    Item { Layout.fillHeight: truev}

    function createInstrument(modelData) {
        switch (modelData) {
        case "af": return Qt.createComponent("qrc:/Indicators/ArtificialHorizon.qml");
        case "fd": return Qt.createComponent("qrc:/Indicators/FlightDirector.qml");
        case "compas": return Qt.createComponent("qrc:/Indicators/Compass.qml");
        case "hsi": return Qt.createComponent("qrc:/Indicators/SituationIndicator.qml");
        default: return null
        }
    }
}

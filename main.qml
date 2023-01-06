import QtQuick
import QtQuick.Controls 6.2
import Models 1.0

Window {
    id: window
    width: 640
    height: 480
    visible: true
    title: qsTr("Hello World")

    GenericModel {
        id: specializedModel
        itemList: specialicedList
    }

    ListView {
        anchors.left: parent.left
        anchors.right: parent.right
        anchors.top: parent.top
        anchors.bottom: appendButton.top
        anchors.topMargin: 0
        anchors.bottomMargin: 8
                model: specializedModel
        delegate: Text {
            height: 20
            anchors.left: parent.left
            anchors.right: parent.right
            text: name
            }

    }

    Button {
        id: appendButton
        width: 200
        height: 40
        anchors.bottom: parent.bottom
        anchors.horizontalCenter: parent.horizontalCenter
        anchors.bottomMargin: 8
        text: "append"
        onClicked: {
            console.log("append button clicked")
            specialicedList.appendItem("item (%1)".arg(specialicedList.count()+1))
        }
    }
}

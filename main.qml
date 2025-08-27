import QtQuick 2.12
import QtQuick.Controls 2.12
import QtQuick.Layouts 1.12
import QtQuick.Window 2.12
import QtMultimedia
import communication 1.0  // Import untuk SerialHandler



ApplicationWindow
{
    visible: true
    width: 600
    height: 400
    title: "Fire Control System"

    SerialHandler 
    {
        id: serialHandler
        onConnectionChanged: 
        {
            console.log("Status koneksi serial: " + (isConnected ? "Terkoneksi" : "Terputus"))
            if (isConnected) 
            {
                console.log("Port: " + serialHandler.portName + ", Baud: " + serialHandler.baudRate)
            }
        }
        onDataSent: 
        {
            console.log("Data terkirim: " + data)
        }
        onErrorOccurred: 
        {
            console.log("Error serial: " + error)
        }
    }

    function sendSerialCommand(command) 
    {
        console.log("Mengirim perintah: " + command)
        if (serialHandler.isConnected) 
        {
            serialHandler.sendCommand(command)
        } 
        else 
        {
            console.log("Serial tidak terkoneksi, mencoba membuka koneksi...")
            serialHandler.openConnection()
            Qt.callLater(function() 
            {
                if (serialHandler.isConnected) 
                {
                    serialHandler.sendCommand(command)
                } 
                else 
                {
                    console.log("Gagal membuka koneksi serial")
                }
            })
        }
    }
    Component.onCompleted: 
    {
        serialHandler.openConnection()
        console.log("Menghubungkan ke " + networkHandler.ipAddress + ":" + networkHandler.port)
        networkHandler.connectToDevice()
    }

    Rectangle
    {
        x:70
        y:120
        width: 20
        height: 20
        radius: 3
        color: mouseArea5.pressed ? "#01579b" : "#0277bd" 
        MouseArea
        {
            id: mouseArea5
            anchors.fill: parent
            onPressed: parent.scale = 0.90   
            onReleased: parent.scale = 1.0   
            onClicked:
            {
                console.log("Move Down")
                sendSerialCommand("MOVE:DOWN")  
            }
        }
        Behavior on scale { NumberAnimation { duration: 100 } }
        Behavior on color { ColorAnimation { duration: 100 } }
    }
    Rectangle
    {
        x:70
        y:60
        width: 20
        height: 20
        radius: 3
        color: mouseArea6.pressed ? "#01579b" : "#0277bd" 
        MouseArea
        {
            id: mouseArea6
            anchors.fill: parent
            onPressed: parent.scale = 0.90  
            onReleased: parent.scale = 1.0   
            onClicked:
            {
                console.log("Move Up")
                sendSerialCommand("MOVE:UP")  
            }
        }
        Behavior on scale { NumberAnimation { duration: 100 } }
        Behavior on color { ColorAnimation { duration: 100 } }
    }
    Rectangle
    {
        x:100
        y:90
        width: 20
        height: 20
        radius: 3
        color: mouseArea7.pressed ? "#01579b" : "#0277bd" 
        MouseArea
        {
            id: mouseArea7
            anchors.fill: parent
            onPressed: parent.scale = 0.90  
            onReleased: parent.scale = 1.0   
            onClicked:
            {
                console.log("Move Right")
                sendSerialCommand("MOVE:RIGHT")  
            }
        }
        Behavior on scale { NumberAnimation { duration: 100 } }
        Behavior on color { ColorAnimation { duration: 100 } }
    }
    Rectangle
    {
        x:40
        y:90
        width: 20
        height: 20
        radius: 3
        color: mouseArea8.pressed ? "#01579b" : "#0277bd" 
        MouseArea
        {
            id: mouseArea8
            anchors.fill: parent
            onPressed: parent.scale = 0.90   
            onReleased: parent.scale = 1.0   
            onClicked:
            {
                 console.log("Move Left")
                 sendSerialCommand("MOVE:LEFT")  
            }
        }
        Behavior on scale { NumberAnimation { duration: 100 } }
        Behavior on color { ColorAnimation { duration: 100 } }
    }

}

#include "serialhandler.h"
#include <QDebug>
#include <QTimer>

SerialHandler::SerialHandler(QObject *parent) : QObject(parent),
    m_serialPort(new QSerialPort(this)),
    m_connected(false),
    m_portName("/dev/ttyUSB0"), 
    m_baudRate(9600) // Default value
{
}

SerialHandler::~SerialHandler()
{
    closeConnection();
}

QString SerialHandler::portName() const
{
    return m_portName;
}

void SerialHandler::setPortName(const QString &portName)
{
    if (m_portName != portName) {
        m_portName = portName;
        emit portNameChanged();
    }
}

int SerialHandler::baudRate() const
{
    return m_baudRate;
}

void SerialHandler::setBaudRate(int baudRate)
{
    if (m_baudRate != baudRate) {
        m_baudRate = baudRate;
        emit baudRateChanged();
    }
}

bool SerialHandler::openConnection()
{
   
    if (m_serialPort->isOpen()) {
        m_serialPort->close();
    }

    // Configure serial port
    m_serialPort->setPortName("/dev/ttyUSB0");
    m_serialPort->setBaudRate(QSerialPort::Baud9600);
    m_serialPort->setDataBits(QSerialPort::Data8);
    m_serialPort->setParity(QSerialPort::NoParity);
    m_serialPort->setStopBits(QSerialPort::OneStop);
    m_serialPort->setFlowControl(QSerialPort::NoFlowControl);

    if (m_serialPort->open(QIODevice::ReadWrite)) {
        m_connected = true;
        emit connectionChanged();
        qDebug() << "Serial port opened successfully:" << m_portName << "at" << m_baudRate << "baud";
        return true;
    } else {
        qDebug() << "Failed to open serial port:" << m_serialPort->errorString();
        emit errorOccurred(m_serialPort->errorString());
        return false;
    }
}

void SerialHandler::closeConnection()
{
    if (m_serialPort->isOpen()) {
        m_serialPort->close();
        m_connected = false;
        emit connectionChanged();
        qDebug() << "Serial port closed";
    }
}

void SerialHandler::sendCommand(const QString &command)
{
    if (!m_serialPort->isOpen() || !m_serialPort->isWritable()) {
        qDebug() << "Cannot send command, serial port is not open or writable";
        emit errorOccurred("Serial port is not open or writable");
        return;
    }

    QByteArray data = command.toUtf8() + "\r\n"; 
    qint64 bytesWritten = m_serialPort->write(data);

    if (bytesWritten == -1) {
        qDebug() << "Failed to write to serial port:" << m_serialPort->errorString();
        emit errorOccurred(m_serialPort->errorString());
    } else if (bytesWritten != data.size()) {
        qDebug() << "Failed to write all data to serial port";
        emit errorOccurred("Failed to write all data");
    } else {
       
        m_serialPort->flush();
        emit dataSent(command);
        qDebug() << "Command sent via serial:" << command;
    }
}

bool SerialHandler::isConnected() const
{
    return m_connected && m_serialPort->isOpen();
}

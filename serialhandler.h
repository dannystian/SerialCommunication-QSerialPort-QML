#ifndef SERIALHANDLER_H
#define SERIALHANDLER_H

#include <QObject>
#include <QString>
#include <QSerialPort>
#include <QSerialPortInfo>

class SerialHandler : public QObject
{
    Q_OBJECT
    Q_PROPERTY(bool isConnected READ isConnected NOTIFY connectionChanged)
    Q_PROPERTY(QString portName READ portName WRITE setPortName NOTIFY portNameChanged)
    Q_PROPERTY(int baudRate READ baudRate WRITE setBaudRate NOTIFY baudRateChanged)

public:
    explicit SerialHandler(QObject *parent = nullptr);
    ~SerialHandler();

    Q_INVOKABLE bool openConnection();
    Q_INVOKABLE void closeConnection();
    Q_INVOKABLE void sendCommand(const QString &command);
    bool isConnected() const;

    QString portName() const;
    void setPortName(const QString &portName);

    int baudRate() const;
    void setBaudRate(int baudRate);

signals:
    void connectionChanged();
    void dataSent(const QString &data);
    void errorOccurred(const QString &error);
    void portNameChanged();
    void baudRateChanged();

private:
    QSerialPort *m_serialPort;
    bool m_connected;
    QString m_portName;
    int m_baudRate;
};

#endif // SERIALHANDLER_H

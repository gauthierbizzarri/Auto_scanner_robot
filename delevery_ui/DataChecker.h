#ifndef DATACHECKER_H
#define DATACHECKER_H

#include <QVariant>


class DataChecker : public QObject{
    Q_OBJECT
protected:
    QVariant data;
    QString lastError;
    DataChecker(QVariant data)
    {
        this->data=data;
    };
public:
    virtual bool check() = 0;
    virtual QString checks() = 0;
    virtual QString getLastError() {return lastError;};

signals:
    void validate();
    void refute(QString, QString);
};

#endif // DATACHECKER_H

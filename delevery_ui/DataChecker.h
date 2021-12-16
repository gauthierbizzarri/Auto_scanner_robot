#ifndef DATACHECKER_H
#define DATACHECKER_H

#include <QVariant>

/**
 * @brief The DataChecker class
 * Base class of a value checker
 */
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
    /**
     * @brief check
     * Main method, checks if the value in constructor is valid
     * @return
     */
    virtual bool check() = 0;

    /**
     * @brief checks
     * Used to providde informations about what this class extension checks exactly
     * @return
     */
    virtual QString checks() = 0;

    /**
     * @brief getLastError
     * Return the last error encountered by this class
     * @return
     */
    virtual QString getLastError() {return lastError;};

signals:
    void validate();
    void refute(QString, QString);
};

#endif // DATACHECKER_H

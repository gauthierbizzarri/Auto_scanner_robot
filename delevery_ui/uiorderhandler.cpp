#include "uiorderhandler.h"

UiOrderHandler::UiOrderHandler(UiOrderModel *view)
{
    this->view = view;
}

void UiOrderHandler::handle(QJsonObject data, bool dataEmpty, QMap<QString, QVariant> meta)
{
    if(!dataEmpty && meta.contains("id"))
    {
        data.insert("id", meta.value("id").toInt());
        data.insert("date", QDateTime::currentDateTime().toString("dd/MM/yyyy hh:mm"));
        view->append(data);//append data to view model
    }
}

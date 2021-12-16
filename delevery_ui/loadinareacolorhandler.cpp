#include "loadinareacolorhandler.h"

#include <colors.h>

LoadinAreaColorHandler::LoadinAreaColorHandler(QList<IconLabel *> loadings, FieldModel *model)
{
    this->loadings = loadings;
    this->model=model;
}

void LoadinAreaColorHandler::handle(QJsonObject data, bool dataEmpty, QMap<QString, QVariant> meta)
{
    if(!dataEmpty && data.contains("color") && meta.contains("loadingareaid"))
    {
        int id = meta.value("loadingareaid").toInt();
        model->ColorFound(id, data.value("color").toString());

        loadings.at(id-1)->setText(data.value("color").toString());
        loadings.at(id-1)->setColor(colors.value(data.value("color").toString()));
    }
}

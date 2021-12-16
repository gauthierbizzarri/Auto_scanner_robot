#ifndef UIORDERMODEL_H
#define UIORDERMODEL_H

#include <QAbstractItemModel>
#include <QJsonObject>
#include <QBrush>
#include <colors.h>
#include <QPainter>
#include <QSortFilterProxyModel>
#include <QIcon>
#include <QPainterPath>

/**
 * @brief The ColumnData class
 * Class storing column header data
 */
class ColumnData
{
public:
    QString jsonName;
    QString name;
};

class UiOrderModel : public QAbstractTableModel
{
private:
    QList<QList<QVariant>> m_data;
    QList<ColumnData> headerMap;
    // QAbstractItemModel interface
public:
    UiOrderModel()
    {
        headerMap = {
            {"date","date"},
            {"id", "id client"},
            {"loadingArea", "zone de chargement"},
            {"depositArea", "zone de dépot"},
            {"color", "couleur du colis"},
            {"robotId", "robot"}
        };
    };
    /**
     * @brief append
     * Add a new value to the model
     * @param data
     */
    void append(QJsonObject data)
    {
        beginInsertRows(QModelIndex() , m_data.count()-1, m_data.count()-1);
        QList<QVariant> map;
        Q_FOREACH(ColumnData field, headerMap)
        {
            map.append(data.value(field.jsonName));
        }
        m_data.append(map);
        endInsertRows();
    }
    int rowCount(const QModelIndex &parent) const{
        Q_UNUSED(parent);
        return m_data.count();
    };
    int columnCount(const QModelIndex &parent) const{
        Q_UNUSED(parent);
        return headerMap.count();
    };
    /**
     * @brief data
     * Return a specific facet of the columns data accurding to their roles
     * @param index
     * @param role
     * @return
     */
    QVariant data(const QModelIndex &index, int role) const{
        if(index.isValid())
        {
            if(role == Qt::DisplayRole)//to display it
            {
                QList<QVariant> data = m_data.at(index.row());
                return data.at(index.column());
            }
            if(headerMap.at(index.column()).jsonName == "color" && role == Qt::DecorationRole)//to decorate it
            {
                //add a colored icon to a cell
                QList<QVariant> data = m_data.at(index.row());
                QString colorString = data.at(index.column()).toString();
                int size = 20;
                QPixmap rounded = QPixmap(size, size);
                rounded.fill(Qt::transparent);

                // creating circle clip area
                QPainterPath path;
                path.addEllipse(rounded.rect());

                QPainter painter(&rounded);
                painter.setClipPath(path);

                // filling rounded area if needed
                painter.fillRect(rounded.rect(), colors.value(colorString));

                return QIcon(rounded);
            }
        }
        return QVariant();
    };
    bool insertRows(int row, int count, const QModelIndex &parent){
        beginInsertRows(parent, m_data.count()-1, m_data.count()+count-1);
        for(int i = 0; i<count-row; i++)
        {
            QJsonObject o = parent.data().value<QJsonObject>();
            append(o);
        }
        endInsertRows();
        return true;
    };
    /**
     * @brief headerData
     * Specified how the header will be arranged
     * @param section
     * @param orientation
     * @param role
     * @return
     */
    QVariant headerData(int section, Qt::Orientation orientation, int role) const{
        if(role == Qt::TextAlignmentRole)
        {
            return Qt::AlignCenter;
        }
        else if(role == Qt::FontRole)
        {
            QFont serifFont("Times", 10, QFont::Bold, true);
            return serifFont;
        }
        if(orientation == Qt::Horizontal)
        {
            if(role == Qt::DisplayRole)
            {
                return headerMap.at(section).name;
            }
        }
        return QVariant();
    };
};

#endif // UIORDERMODEL_H

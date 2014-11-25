/**
 * Copyright (c) 2014 Ralph Janke. All rights reserved.
 *
 * Author: Ralph Janke hexnosis@jankeconsulting.ca
 */

#include "./hexnosiswindow.h"
#include "./hexfilemodel.h"
#include <QDebug>

/**
 * @brief constructs the model for the views
 * @param parent of the object
 * @param newfile - file to be opened in view
 */
HexFileModel::HexFileModel(QObject *parent, QFile *newfile) :
//    QStandardItemModel(parent),
  QAbstractTableModel(parent),
  file(newfile),
  tablewidth(16)
{
}

/**
 * @brief destroys the model
 *
 * Before the object is destroyed,  the file handler
 * is deleted and the filebuffer is cleared.
 */
HexFileModel::~HexFileModel()
{
    delete file;
    filebuffer.clear();
}

/**
 * @brief provides the row count of the model
 * @return the row count of the model
 *
 * Calculates the number of rows required in the model
 * in order to present the data in the view.
 */
int HexFileModel::rowCount(const QModelIndex & /* index */) const
{
// TODO(txwikinger): store count in class variable
    if ((filebuffer.size() / tablewidth) * tablewidth == filebuffer.size())
    {
        return filebuffer.size() / tablewidth;
    }
    else
    {
        return (filebuffer.size() / tablewidth) + 1;
    }
}

/**
 * @brief provides the (max) number of columns in the model
 * @param index - currently not used
 * @return the max number of columns in the model
 */
int HexFileModel::columnCount(const QModelIndex &index) const
{
    Q_UNUSED(index);
//    if(parent.row() < rowCount())
        return tablewidth;
//    else
//        return filebuffer.size() - ((filebuffer.size() / tablewidth) * tablewidth) - 1;
}

/**
 * @brief provides data from the model
 * @param index
 * @param role
 * @return the requested data
 *
 * According to the given index, the responding item is requested
 * to provid the data associated with the given role.
 *
 * The DisplayRole and EditRole return the file data for the particular
 * item.
 */
QVariant HexFileModel::data(const QModelIndex &index, int role) const
{
    if (not(index.isValid()) || (role != Qt::DisplayRole && role != Qt::EditRole))
    {
        return QVariant();
    }
    if (index.row()*columnCount()+index.column() >= filebuffer.size())
    {
        return QVariant();
    }
    return filebuffer.at(index.row()*columnCount()+index.column());
}

/**
 * @brief provides multiple bytes of data
 * @param length of data requested
 * @param index of first data item requested
 * @param role - type of data requested
 * @return QByteArray containing the requested data
 *
 * Only DisplayRole will return data for this method. All
 * other roles will return an empty QByteArray. If the index
 * length combination would reach over the end of the file,
 * the return QByteArray will be shorten than length.
 */
QByteArray HexFileModel::data( int length, const QModelIndex &index, int role) const
{
    if (not(index.isValid()) || (role != Qt::DisplayRole))
    {
        return QByteArray();
    }
    if (index.row()*columnCount()+index.column() >= filebuffer.size())
    {
        return QByteArray();
    }
    int len = filebuffer.size() - (index.row()*columnCount()+index.column());
    if (len < length)
    {
        length = len;
    }
    QByteArray data = QByteArray();
    data.resize(length);
    for (int i=0; i<length; i++)
    {
        data[i] = filebuffer.at(index.row()*columnCount()+index.column()+i);
    }
    return data;
}

/**
 * @brief sets data in the model
 * @param index of the item to be set
 * @param value the item is to be set to
 * @param role
 * @return true if data was set, otherwise false
 *
 * Only EditRole will set any data, all other roles will
 * return false. If data is set, the dataChange signal for
 * the model is emmitted.
 */
bool HexFileModel::setData(const QModelIndex &index, const QVariant &value, int role)
{
    if (index.isValid() && role == Qt::EditRole)
    {
        filebuffer.replace(index.row()*columnCount()+index.column(), 1, value.toByteArray());
        emit dataChanged(index, index);
        return true;
    }
    return false;
}

/**
 * @brief sets multiple bytes of data in the model
 * @param index of the item of the first byte to be set
 * @param values to be set in the model
 * @param role
 * @return true if the data was set, otherwise false
 *
 * Only EditRole will set the data, all other roles will return false
 */
bool HexFileModel::setData(const QModelIndex &index, const QByteArray &values, int role)
{
    QModelIndex index2;
    if ((index.column() + values.size()) < columnCount())
    {
        index2 = QAbstractItemModel::createIndex(index.row(), index.column()+values.size()-1);
    }
    else
    {
        int row = (index.row() + (values.size() / tablewidth)) + 1;
        int column = (index.column()+values.size()-1) % tablewidth;
        index2 = QAbstractItemModel::createIndex(row, column);
    }

    if (index.isValid() && role == Qt::EditRole)
    {
        filebuffer.replace(index.row()*columnCount()+index.column(), values.size(), values);
        emit dataChanged(index, index2);
        return true;
    }
    return false;
}

/**
 * @brief provides the flags of the item associated with index
 * @param index
 * @return flags of the item associated with index
 *
 * If the index is valid, the ItemIsEditable flag is returned.
 */
Qt::ItemFlags HexFileModel::flags(const QModelIndex &index) const
{
    if (not(index.isValid()))
    {
        return Qt::ItemIsEnabled;
    }
    return QAbstractItemModel::flags(index) | Qt::ItemIsEditable;
    //    return Qt::ItemIsEnabled | Qt::ItemIsSelectable | Qt::ItemIsEditable;
}

/**
 * @brief sets the header data for the model
 * @param section
 * @param orientation
 * @param value
 * @param role
 * @return true
 *
 * This function must be implemented to make this class instantiable.
 * Currently it will always true, and has no real functionality.
 */
bool HexFileModel::setHeaderData(int section, Qt::Orientation orientation,
                                 const QVariant &value, int role)
{
    Q_UNUSED(section);
    Q_UNUSED(orientation);
    Q_UNUSED(value);
    Q_UNUSED(role);
//  Headers are automatically set, cannot be set from outside
    return true;
}

/**
 * @brief provides the information for the headers
 * @param section
 * @param orientation
 * @param role
 * @return the data represented in the headers
 */
QVariant HexFileModel::headerData(int section, Qt::Orientation orientation, int role) const
{
    if (role == Qt::DisplayRole)
    {
//        TODO: Should representation of header be located in Delegate?
        if (orientation == Qt::Horizontal)
        {
            return QString("%1").arg(QByteArray(1, section).toHex().toUpper().data()[1]);
        }
        if (orientation == Qt::Vertical)
        {
            return QString("%1h").arg(QByteArray(3, 0).setNum(section * tablewidth, 16).
                                      toUpper().data());
        }
    }
    return QVariant();
}

/**
 * @brief loads the data from the file
 * @param length of the data loaded
 * @param offset in the model to place the data to
 *
 * Reads the data of the file and places it into the model.
 * Currently length and offset are not used, they are placed
 * for future use, to read the file in chunks.
 */
void HexFileModel::loadDatafromFile(int length, int offset)
{
    Q_UNUSED(length);
    Q_UNUSED(offset);
    if (file)
    {
        filebuffer = file->readAll();
        file->close();
    }
}

/**
 * @brief saves the data from the model into the file
 * @param file_name of the file
 * @param length of the data to be saved
 * @param offset in the model from which the data is to be saved
 * @return true if saving the data succeeds, otherwise false
 *
 * Currently, length and offset are not used, the whole model will
 * always be saved into the file. In the future it will be possible
 * to save chunks of the model to the right place into the file.
 */
bool HexFileModel::saveDatatoFile(QString file_name, int length, int offset)
{
    Q_UNUSED(length);
    Q_UNUSED(offset);

    if (not(file_name.isEmpty()))
    {
        file = new QFile(file_name);

        if (file->open(QIODevice::WriteOnly))
        {
            file->write(filebuffer);
            file->close();
            return true;
        }
    }
    return false;
}

/**
 * @brief creates the buffer that contains the data for the model
 * @param len - length of the buffer to be created.
 * @param fillchar - character to fill the buffer with
 */
void HexFileModel::createBuffer(int len, char fillchar)
{
    emit beginResetModel();
    filebuffer = QByteArray(len, fillchar);
    emit endResetModel();
}

/**
 * @brief sets the header for the view
 *
 * Currently this method is not functional.
 */
void HexFileModel::setColumnHeaders()
{
    for (int i=0; i<16; i++)
    {
//        QStandardItem *item = new QStandardItem(QString().number(i,16).toUpper());
        //setHorizontalHeaderItem(i, item);
        //setHorizontalHeaderItem(i+16, item);
    }
}

/**
 * @brief provides the meta information of the file
 * @return information in rich text format
 *
 * File name, path and size are provided in rich text format to
 * be displayed in a panel.
 */
QString HexFileModel::fileInfo()
{
// TODO(txwikinger): Refactor - representation from of data should not be done in model
    QString info = QString();
    QFileInfo fi(*file);
    info.append(tr("<strong>Name:</strong> %1<br/>").arg(fi.fileName()));
    info.append(tr("<strong>Path:</strong> %1<br/>").arg(fi.path()));
    info.append(tr("<strong>Size:</strong> %1<br/>").arg(filebuffer.size()));
    return info;
}

/**
 * @brief sets the cursor information in the status line
 * @param current index
 * @param previous index
 */
void HexFileModel::updateCursorInfo(QModelIndex current, QModelIndex previous)
{
    Q_UNUSED(previous);
    if (current.isValid())
    {
        HexnosisWindow::updateCursorInfo(current.row()*columnCount()+current.column(),
                                         data(current, Qt::DisplayRole).toInt());
    }
    else
    {
        HexnosisWindow::clearCursorInfo();
    }
}

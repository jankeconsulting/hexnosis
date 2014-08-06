/**
 * Copyright (c) 2014 Ralph Janke. All rights reserved.
 *
 * Author: Ralph Janke hexnosis@jankeconsulting.ca
 */

#ifndef HEXFILEMODEL_H
#define HEXFILEMODEL_H

#include <QStandardItemModel>
#include <QString>
#include <QFile>
#include <QFileDialog>
#include <QMessageBox>

//class HexFileModel : public QStandardItemModel
class HexFileModel : public QAbstractTableModel
{
    Q_OBJECT
public:
    explicit HexFileModel(QObject *parent = 0, QFile *file = 0);
    ~HexFileModel();

    int rowCount(const QModelIndex &parent = QModelIndex()) const;
    int columnCount(const QModelIndex &parent = QModelIndex()) const;
    QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const;
    QVariant headerData(int section, Qt::Orientation orientation, int role = Qt::DisplayRole) const;
    bool setData(const QModelIndex & index, const QVariant & value, int role = Qt::EditRole);
    Qt::ItemFlags flags(const QModelIndex &index) const;
    bool setHeaderData(int section, Qt::Orientation orientation, const QVariant &value, int role);

    void loadDatafromFile(int length = 0, int offset = 0);
    bool saveDatatoFile(QString filename, int length = 0, int offset = 0);
    void createBuffer(int len = 0, char fillchar = 0);
    void setColumnHeaders();
    QString fileName(bool with_path = false);

signals:

public slots:

private:
    QWidget *widget;
    QFile *file;
    QByteArray filebuffer;
    int tablewidth;

protected slots:
};

#endif // HEXFILEMODEL_H

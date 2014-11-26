/**
 * Copyright (c) 2014 Ralph Janke. All rights reserved.
 *
 * Author: Ralph Janke hexnosis@jankeconsulting.ca
 */

#ifndef SRC_TEXTPANEL_H_
#define SRC_TEXTPANEL_H_

#include "./hexfilemodelpanel.h"
#include "./textpanelitemdelegate.h"

// TODO(txwikinger): Make width more flexible due to font etc
#define TEXTPANEL_DEFAULT_COLUMN_WIDTH 13

/**
 * @brief The TextPanel class
 */
class TextPanel : public HexFileModelPanel
{
    Q_OBJECT
 public:
    explicit TextPanel(QWidget *parent = 0);
    ~TextPanel();

 signals:

 public slots:

 private:
    void formatPanel();
};

#endif  // SRC_TEXTPANEL_H_

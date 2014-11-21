/**
 * Copyright (c) 2014 Ralph Janke. All rights reserved.
 *
 * Author: Ralph Janke hexnosis@jankeconsulting.ca
 */

#include <QApplication>
#include "./hexnosiswindow.h"

/**
 * @fn main
 * @brief the main function of the executable
 * @param argc
 * @param argv
 * @return the error code for the exit of the application
 *
 * It sets application wide settings, launces the main window
 * and executes the main loop.
 */
int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    a.setOrganizationName("Janke Consulting");
    a.setOrganizationDomain("jankeconsulting.ca");
    a.setApplicationName("Hexnosis");
    a.setApplicationVersion("1.0");
    HexnosisWindow w;
    w.show();

    return a.exec();
}

/***************************************************************************
**                                                                        **
**  This file is part of the program 'Launcher'.                          **
**  Copyright (C) 2013 Maxime Bellier                                     **
**                                                                        **
**  This program is free software: you can redistribute it and/or modify  **
**  it under the terms of the GNU General Public License as published by  **
**  the Free Software Foundation, either version 3 of the License, or     **
**  (at your option) any later version.                                   **
**                                                                        **
**  This program is distributed in the hope that it will be useful,       **
**  but WITHOUT ANY WARRANTY; without even the implied warranty of        **
**  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the         **
**  GNU General Public License for more details.                          **
**                                                                        **
**  You should have received a copy of the GNU General Public License     **
**  along with this program.  If not, see http://www.gnu.org/licenses/.   **
**                                                                        **
****************************************************************************
**           Author: Maxime Bellier                                       **
**  Website/Contact: http://puissance.m4x.free.fr                         **
**             Date: 05.2013                                              **
****************************************************************************/

#ifndef LAUNCHER_H_
#define LAUNCHER_H_

#include "link.h"
#include "statistics.h"
#include "statistics_dialog.h"
#include "settings.h"

#include <QtWidgets/QApplication>
#include <QtWidgets/QWidget>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QButtonGroup>
#include <QIcon>
#include <QDir>
#include <QFocusEvent>

#include <vector>

class Launcher : public QWidget {
  Q_OBJECT
public:
  Launcher                 (Statistics &m_stats,
                            StatisticsDialog &m_statDialog,
                            Settings &settings);
  ~Launcher();
  void  setLaunchButton    (QPushButton &button,
                            QString &name,
                            QIcon &icon) const;
  int   getTaskbarPosition ();
  void  setPosition        ();
  void  contextMenuEvent   (QContextMenuEvent *event);
  int   getButtonIdFromPos (const QPoint &pos);
  Link *launchButton       (QPushButton &button,
                            const QString &filePath) const;
  void  allowFocusLoss     (bool value);

public slots:
  void openFileLocation ();
  void openLinksFolder  ();
  void openStatistics   ();
  void openSettings     ();
  void rename           ();
  void click            (int);
  void focusOutEvent    (QFocusEvent *event);
  void keyPressEvent    (QKeyEvent *event);

private:
  QButtonGroup *      m_buttons;
  QString             m_path;
  bool                m_quitIfNoFocus;
  unsigned int        m_buttonWidth;
  unsigned int        m_buttonHeight;
  unsigned int        m_columnSize;
  unsigned int        m_maxColumnSize;
  unsigned int        m_rowSize;
  int                 m_contextMenuButtonId;
  std::vector<Link *> m_links;
  QDir *              m_dir;
  Statistics &        m_stats;
  StatisticsDialog &  m_statDialog;
  Settings &          m_settings;
};

#endif // LAUNCHER_H_
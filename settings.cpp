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
**             Date: 05.2013                                            **
****************************************************************************/

/*!
 * \file settings.cpp
 * \brief Settings window
 * \author Maxime Bellier
 * \version 0.2
 * \date 05.2013
 * \copyright This project is released under the GNU Public License.
 */

#include "settings.h"
#include "ui_settings.h"

#include <QSettings>

Settings::Settings(const QString &settingsFile, QWidget *parent):
  QDialog(parent, Qt::WindowCloseButtonHint),
  ui(new Ui::Settings),
  m_settingsFile(settingsFile)
{
  ui->setupUi(this);
  loadSettings();
}

Settings::~Settings()
{
  saveSettings();
  delete ui;
}

void Settings::loadSettings()
{
  QSettings settings(m_settingsFile,QSettings::IniFormat);
  m_settingSorted = settings.value("sorted", false).toBool();
  m_settingMaxColumnSize = settings.value("maxColumnSize", 8).toUInt();

  // update ui
  if (ui->optionSortedTrue && m_settingSorted)
    ui->optionSortedTrue->toggle();
  if (ui->sliderWidth)
    ui->sliderWidth->setValue(m_settingMaxColumnSize);
}

void Settings::saveSettings()
{
  QSettings settings(m_settingsFile,QSettings::IniFormat);
  settings.setValue("sorted", m_settingSorted);
  settings.setValue("maxColumnSize", m_settingMaxColumnSize);
}

bool Settings::settingSorted() const
{
  return m_settingSorted;
}

unsigned int Settings::settingMaxColumnSize() const
{
  return m_settingMaxColumnSize;
}


void Settings::on_optionSortedTrue_toggled(bool checked)
{
  m_settingSorted = checked;
}

void Settings::on_sliderWidth_valueChanged(int value)
{
  m_settingMaxColumnSize = value;
  if (ui->labelWidth)
    ui->labelWidth->setText(QString::number(m_settingMaxColumnSize));
}

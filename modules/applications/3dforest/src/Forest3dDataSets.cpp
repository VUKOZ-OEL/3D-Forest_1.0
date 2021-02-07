/*
    Copyright 2020 VUKOZ

    This file is part of 3D Forest.

    3D Forest is free software: you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation, either version 3 of the License, or
    (at your option) any later version.

    3D Forest is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with 3D Forest.  If not, see <https://www.gnu.org/licenses/>.
*/

/**
    @file Forest3dDataSets.cpp
*/

#include <Forest3dDataSets.hpp>
#include <Project.hpp>
#include <ProjectDataSet.hpp>
#include <QTreeWidget>
#include <QVBoxLayout>

Forest3dDataSets::Forest3dDataSets(QWidget *parent) : QWidget(parent)
{
    // Table
    dataSets_ = new QTreeWidget();

    connect(dataSets_,
            &QTreeWidget::itemChanged,
            this,
            &Forest3dDataSets::itemChanged);

    // Layout
    QVBoxLayout *mainLayout = new QVBoxLayout;
    mainLayout->setContentsMargins(1, 1, 1, 1);
    mainLayout->addWidget(dataSets_);
    setLayout(mainLayout);
}

Forest3dDataSets::~Forest3dDataSets()
{
}

void Forest3dDataSets::itemChanged(QTreeWidgetItem *item, int column)
{
    if (column == COLUMN_CHECKED)
    {
        // #id is now checked or unchecked
        size_t id = item->text(COLUMN_ID).toULong();
        bool checked = (item->checkState(COLUMN_CHECKED) == Qt::Checked);
        emit itemChangedCheckState(id, checked);
    }
}

void Forest3dDataSets::updateEditor(const Editor &editor)
{
    (void)blockSignals(true);
    dataSets_->clear();

    // Header
    dataSets_->setColumnCount(COLUMN_LAST);
    QStringList labels;
    labels << tr("Index") << tr("Select") << tr("File name")
           << tr("Date Created");
    dataSets_->setHeaderLabels(labels);

    // Content
    const Project &project = editor.project();
    QList<QTreeWidgetItem *> items;
    for (size_t i = 0; i < project.dataSetSize(); i++)
    {
        QTreeWidgetItem *item = new QTreeWidgetItem(dataSets_);
        const ProjectDataSet &dataSet = project.dataSet(i);

        item->setText(COLUMN_ID, QString::number(i));
        if (dataSet.visible)
        {
            item->setCheckState(COLUMN_CHECKED, Qt::Checked);
        }
        else
        {
            item->setCheckState(COLUMN_CHECKED, Qt::Unchecked);
        }
        item->setText(COLUMN_FILE_NAME,
                      QString::fromStdString(dataSet.fileName));
        item->setText(COLUMN_DATE_CREATED,
                      QString::fromStdString(dataSet.dateCreated));
    }

    // Resize Columns to the minimum space
    for (int i = 0; i < COLUMN_LAST; i++)
    {
        dataSets_->resizeColumnToContents(i);
    }

    // Sort Content
    dataSets_->setSortingEnabled(true);
    dataSets_->sortItems(COLUMN_ID, Qt::AscendingOrder);
    (void)blockSignals(false);
}

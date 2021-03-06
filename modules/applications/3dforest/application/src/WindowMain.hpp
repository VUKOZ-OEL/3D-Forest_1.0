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

/** @file WindowMain.hpp */

#ifndef WINDOW_MAIN_HPP
#define WINDOW_MAIN_HPP

#include <Editor.hpp>
#include <QIcon>
#include <QMainWindow>
#include <WindowViewports.hpp>
#include <vector>

class QAction;
class QTextEdit;
class QToolButton;
class PluginFile;
class PluginTool;
class Ribbon;
class WindowDock;
class WindowClassification;
class WindowClipFilter;
class WindowDataSets;
class WindowLayers;
class WindowSettingsView;

/** Window Main. */
class WindowMain : public QMainWindow
{
    Q_OBJECT

public:
    static const QString APPLICATION_NAME;
    static const QString APPLICATION_VERSION;
    static QTextEdit *log;

    explicit WindowMain(QWidget *parent = nullptr);
    ~WindowMain();

    QSize minimumSizeHint() const override;
    QSize sizeHint() const override;

public slots:
    // Project
    void actionProjectNew();
    void actionProjectOpen();
    void actionProjectSave();
    void actionProjectSaveAs();
    void actionProjectImport();
    void actionProjectExportAs();

    // Viewports
    void actionViewOrthographic();
    void actionViewPerspective();
    void actionViewTop();
    void actionViewFront();
    void actionViewRight();
    void actionView3d();
    void actionViewResetDistance();
    void actionViewResetCenter();

    void actionViewLayoutSingle();
    void actionViewLayout2Columns();
    void actionViewLayoutGrid();
    void actionViewLayout3RowsRight();
    void actionViewLayout(WindowViewports::ViewLayout layout);

    // Plugins
    void actionPluginToolShow();

    // Windows
    void actionDataSetVisible(size_t id, bool checked);
    void actionClassification();
    void actionLayers();
    void actionClipFilter(const ClipFilter &clipFilter);
    void actionClipFilterReset();
    void actionSettingsView();
    void actionSettingsViewColor();

    void actionScreenshot();

    void actionAbout();
    void actionHelp();

    // Editor
    void actionEditorRender();
    void actionCameraChanged(size_t viewportId);

protected:
    // Editor
    Editor editor_;

    // Plugins
    std::vector<PluginFile *> pluginsFile_;
    std::vector<PluginTool *> pluginsTool_;

    // Windows
    WindowClassification *windowClassification_;
    WindowClipFilter *windowClipFilter_;
    WindowDataSets *windowDataSets_;
    WindowLayers *windowLayers_;
    WindowSettingsView *windowSettingsView_;
    WindowViewports *windowViewports_;

    // Actions
    Ribbon *ribbon_;

    // Initialization
    void initializeWindow();
    void createEditor();
    void createViewer();
    void createMenus();
    void createWindows();
    void createPlugins();

    // Project
    bool projectOpen(const QString &path);
    bool projectClose();
    bool projectSave(const QString &path = "");
    bool projectOpenFile(const QString &path);
    bool projectCreateIndex(const QString &path);

    // Update
    void updateProject();
    void updateViewer();

    // Utilities
    void showError(const char *message);
    void updateWindowTitle(const QString &path);
    QToolButton *createMenuButton(const QString &text,
                                  const QString &toolTip,
                                  const QIcon &icon);
    QToolButton *createMenuButton(const QString &text,
                                  const QString &toolTip,
                                  const QString &icon);
    QToolButton *createMenuButton(const QString &title,
                                  const QString &text,
                                  const QString &toolTip,
                                  const QString &icon,
                                  QDockWidget *dockWidget);
    WindowDock *createMenuTool(
        const QString &windowTitle,
        const QString &text,
        const QString &toolTip,
        const QString &icon,
        QWidget *dockWidget,
        Qt::DockWidgetAreas areas = Qt::RightDockWidgetArea,
        Qt::DockWidgetArea area = Qt::RightDockWidgetArea,
        bool floating = true);

    // Events
    void closeEvent(QCloseEvent *event) override;
};

#endif /* WINDOW_MAIN_HPP */

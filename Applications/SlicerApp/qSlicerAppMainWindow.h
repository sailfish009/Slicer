/*==============================================================================

  Program: 3D Slicer

  Copyright (c) Kitware Inc.

  See COPYRIGHT.txt
  or http://www.slicer.org/copyright/copyright.txt for details.

  Unless required by applicable law or agreed to in writing, software
  distributed under the License is distributed on an "AS IS" BASIS,
  WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
  See the License for the specific language governing permissions and
  limitations under the License.

  This file was originally developed by Jean-Christophe Fillion-Robin, Kitware Inc.
  and was partially funded by NIH grant 3P41RR013218-12S1

==============================================================================*/

#ifndef __qSlicerAppMainWindow_h
#define __qSlicerAppMainWindow_h

// Qt includes
#include <QMainWindow>
#include <QVariantMap>

// CTK includes
#include <ctkErrorLogModel.h>
class ctkErrorLogWidget;
class ctkPythonConsole;

// Slicer includes
#include "qSlicerAppExport.h"
#include "qSlicerIO.h"
#include "vtkSlicerConfigure.h" // For Slicer_BUILD_DICOM_SUPPORT, Slicer_USE_PYTHONQT, Slicer_USE_QtTesting

class qSlicerModuleSelectorToolBar;
class qSlicerAppMainWindowPrivate;

// VTK includes
class vtkObject;

class Q_SLICER_APP_EXPORT qSlicerAppMainWindow : public QMainWindow
{
  Q_OBJECT
public:
  typedef QMainWindow Superclass;

  qSlicerAppMainWindow(QWidget *parent=0);
  virtual ~qSlicerAppMainWindow();

  /// Return a pointer to the module selector toolbar that can change the
  /// current module.
  /// \sa pythonConsole(), errorLogWidget()
  Q_INVOKABLE qSlicerModuleSelectorToolBar* moduleSelector()const;

#ifdef Slicer_USE_PYTHONQT
  /// Return a pointer to the python console.
  /// \sa moduleSelector(), errorLogWidget()
  Q_INVOKABLE ctkPythonConsole* pythonConsole()const;
#endif
  /// Return a pointer to the error log widget.
  /// \sa moduleSelector(), pythonConsole()
  Q_INVOKABLE ctkErrorLogWidget* errorLogWidget()const;

public slots:
  virtual void setHomeModuleCurrent();
  virtual void restoreToolbars();

  virtual void on_FileAddDataAction_triggered();
  virtual void on_FileLoadDataAction_triggered();
  virtual void on_FileImportSceneAction_triggered();
  virtual void on_FileLoadSceneAction_triggered();
  virtual void on_FileAddVolumeAction_triggered();
  virtual void on_FileAddTransformAction_triggered();
  virtual void on_FileSaveSceneAction_triggered();
  virtual void on_FileExitAction_triggered();
  virtual void onFileRecentLoadedActionTriggered();
  virtual void on_SDBSaveToDirectoryAction_triggered();
  virtual void on_SDBSaveToMRBAction_triggered();
  virtual void on_SDBSaveToDCMAction_triggered();
  virtual void on_FileCloseSceneAction_triggered();
  virtual void on_LoadDICOMAction_triggered();

  virtual void on_EditRecordMacroAction_triggered();
  virtual void on_EditPlayMacroAction_triggered();
  virtual void on_EditUndoAction_triggered();
  virtual void on_EditRedoAction_triggered();

  virtual void on_ModuleHomeAction_triggered();

  virtual void onLayoutActionTriggered(QAction* action);
  virtual void onLayoutCompareActionTriggered(QAction* action);
  virtual void onLayoutCompareWidescreenActionTriggered(QAction* action);
  virtual void onLayoutCompareGridActionTriggered(QAction* action);

  virtual void setLayout(int);
  virtual void setLayoutNumberOfCompareViewRows(int);
  virtual void setLayoutNumberOfCompareViewColumns(int);

  virtual void onPythonConsoleToggled(bool);

  virtual void on_WindowErrorLogAction_triggered();
  virtual void on_WindowToolbarsResetToDefaultAction_triggered();

  virtual void on_HelpKeyboardShortcutsAction_triggered();
  virtual void on_HelpBrowseTutorialsAction_triggered();
  virtual void on_HelpInterfaceDocumentationAction_triggered();
  virtual void on_HelpSlicerPublicationsAction_triggered();
  virtual void on_HelpVisualBlogAction_triggered();

  virtual void on_HelpReportBugOrFeatureRequestAction_triggered();
  virtual void on_HelpAboutSlicerAppAction_triggered();

  virtual void on_EditApplicationSettingsAction_triggered();
  virtual void on_CutAction_triggered();
  virtual void on_CopyAction_triggered();
  virtual void on_PasteAction_triggered();
  virtual void on_ViewExtensionsManagerAction_triggered();

protected slots:
  virtual void onModuleLoaded(const QString& moduleName);
  virtual void onModuleAboutToBeUnloaded(const QString& moduleName);
  virtual void onNewFileLoaded(const qSlicerIO::IOProperties &fileProperties);

  virtual void onMRMLSceneModified(vtkObject*);
  virtual void onLayoutChanged(int);
  virtual void onWarningsOrErrorsOccurred(ctkErrorLogLevel::LogLevel logLevel);

#ifdef Slicer_USE_PYTHONQT
  virtual void onPythonConsoleUserInput(const QString&);
#endif

protected:
  /// Connect MainWindow action with slots defined in MainWindowCore
  virtual void setupMenuActions();

  /// Open Python interactor if it was requested
  virtual void pythonConsoleInitialDisplay();

  /// Open a popup to warn the user Slicer is not for clinical use.
  virtual void disclaimer();

  /// Forward the dragEnterEvent to the IOManager which will
  /// decide if it could accept a drag/drop or not.
  /// \sa dropEvent()
  virtual void dragEnterEvent(QDragEnterEvent *event);

  /// Forward the dropEvent to the IOManager.
  /// \sa dragEnterEvent()
  virtual void dropEvent(QDropEvent *event);

  /// Reimplemented to catch activationChange/show/hide events.
  /// More specifically it allows to:
  ///  1. update the state of the errorLog and python console QAction when
  ///  associated dialog are visible or not.
  ///  2. set the state of ErrorLog button based on the activation state of
  ///  the error log dialog.
  virtual bool eventFilter(QObject* object, QEvent* event);

  virtual void closeEvent(QCloseEvent *event);
  virtual void showEvent(QShowEvent *event);

protected:
  QScopedPointer<qSlicerAppMainWindowPrivate> d_ptr;

  qSlicerAppMainWindow(qSlicerAppMainWindowPrivate* pimpl, QWidget* parent);

private:
  Q_DECLARE_PRIVATE(qSlicerAppMainWindow);
  Q_DISABLE_COPY(qSlicerAppMainWindow);
};

#endif

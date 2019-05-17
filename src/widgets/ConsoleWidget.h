#ifndef CONSOLEWIDGET_H
#define CONSOLEWIDGET_H

#include "core/MainWindow.h"
#include "CutterDockWidget.h"
#include "common/CommandTask.h"

#include <QStringListModel>

#include <memory>

class QCompleter;

namespace Ui {
class ConsoleWidget;
}

class ConsoleWidget : public CutterDockWidget
{
    Q_OBJECT

public:
    explicit ConsoleWidget(MainWindow *main, QAction *action = nullptr);

    ~ConsoleWidget();

    void setDebugOutputEnabled(bool enabled)
    {
        debugOutputEnabled = enabled;
    }

    void setMaxHistoryEntries(int max)
    {
        maxHistoryEntries = max;
    }

public slots:
    void focusInputLineEdit();

    void addOutput(const QString &msg);
    void addDebugOutput(const QString &msg);

private slots:
    void setupFont();

    void on_inputLineEdit_returnPressed();

    void on_execButton_clicked();

    void showCustomContextMenu(const QPoint &pt);

    void historyNext();
    void historyPrev();

    void updateCompletion();

    void clear();

private:
    void scrollOutputToEnd();
    void historyAdd(const QString &input);
    void invalidateHistoryPosition();
    void removeLastLine();
    void executeCommand(const QString &command);
    void setWrap(bool wrap);

    QSharedPointer<CommandTask> commandTask;

    std::unique_ptr<Ui::ConsoleWidget> ui;
    QAction *actionWrapLines;
    QList<QAction *> actions;
    bool debugOutputEnabled;
    int maxHistoryEntries;
    int lastHistoryPosition;
    QStringList history;
    QStringListModel completionModel;
    QCompleter *completer;
};

#endif // CONSOLEWIDGET_H

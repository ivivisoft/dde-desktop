#ifndef DBUSCONTROLLER_H
#define DBUSCONTROLLER_H

#include <QtCore>
#include <QtDBus>

#include "dbusinterface/dbustype.h"

class MonitorManagerInterface;
class FileMonitorInstanceInterface;
class ClipboardInterface;
class WatcherInstanceInterface;
class FileInfoInterface;
class DesktopDaemonInterface;
class FileOperationsInterface;
class CreateDirJobInterface;
class CreateFileJobInterface;
class CreateFileFromTemplateJobInterface;
class FileMonitor;
class QTimer;
class DBusDockSetting;


#define FileMonitor_service "com.deepin.filemanager.Backend.Monitor"
#define FileMonitor_path "/com/deepin/filemanager/Backend/MonitorManager"
#define FileOperations_path "/com/deepin/filemanager/Backend/Operations"
#define TrashMonitor_path "/com/deepin/filemanager/Backend/Monitor/TrashMonitor"
#define Clipboard_path "/com/deepin/filemanager/Backend/Clipboard"

#define FileInfo_service "com.deepin.filemanager.Backend.FileInfo"
#define FileInfo_path "/com/deepin/filemanager/Backend/FileInfo"

#define DesktopDaemon_service "com.deepin.dde.daemon.Desktop"
#define DesktopDaemon_path "/com/deepin/dde/daemon/Desktop"

#define Watcher_service "com.deepin.filemanager.Backend.Watcher"

typedef QSharedPointer<FileMonitorInstanceInterface> FileMonitorInstanceInterfacePointer;


class DBusController : public QObject
{
    Q_OBJECT

    enum G_FILE_MONITOR_EVENT{
        G_FILE_MONITOR_EVENT_CHANGED,
        G_FILE_MONITOR_EVENT_CHANGES_DONE_HINT,
        G_FILE_MONITOR_EVENT_DELETED,
        G_FILE_MONITOR_EVENT_CREATED,
        G_FILE_MONITOR_EVENT_ATTRIBUTE_CHANGED,
        G_FILE_MONITOR_EVENT_PRE_UNMOUNT,
        G_FILE_MONITOR_EVENT_UNMOUNTED,
        G_FILE_MONITOR_EVENT_MOVED
    };

    enum G_FILE_MONITOR_FLAG{
        G_FILE_MONITOR_NONE = 0x0,
        G_FILE_MONITOR_WATCH_MOUNTS = 0x01,
        G_FILE_MONITOR_SEND_MOVED = 0x02,
        G_FILE_MONITOR_WATCH_HARD_LINKS = 0x04
    };

public:
    DBusController(QObject *parent = 0);
    ~DBusController();
    void init();
    void initConnect();
//    void monitorDesktop();
//    void watchDesktop();
    void requestDesktopItems();
    void requestIconByUrl(QString scheme, uint size);
    void requestThumbnail(QString scheme, uint size);

    FileOperationsInterface* getFileOperationsInterface();
    FileInfoInterface* getFileInfoInterface();

    QMap<QString, DesktopItemInfoMap> getAppGroups();

    DesktopItemInfoMap getDesktopItemInfoMap();
    void asyncRenameDesktopItemByUrl(QString url);
    void asyncCreateDesktopItemByUrl(QString url);

    DesktopDaemonInterface* getDesktopDaemonInterface();

    void updateDesktopItemInfoMap(DesktopItemInfo desktopItemInfo);
    void updateDesktopItemInfoMap_moved(DesktopItemInfo desktopItemInfo);
    void removeDesktopItemInfoByUrl(QString url);

    int getDockMode();

signals:

public slots:
    void loadDesktopSettings();
    void loadDesktopItems();

    void handleFileCreated(const QString& path);
    void handleFileDeleted(const QString& path);
    void handleFileMovedIn(const QString& path);
    void handleFileMovedOut(const QString& path);
    void handleFileRenamed(const QString& oldPath, const QString& newPath);

    void asyncRenameDesktopItemByUrlFinished(QDBusPendingCallWatcher* call);
    void asyncCreateDesktopItemByUrlFinished(QDBusPendingCallWatcher* call);

    void openFiles(QStringList files, IntList intFlags);
    void openFiles(DesktopItemInfo destinationDesktopItemInfo, QStringList urls);
    void openFiles(DesktopItemInfo destinationDesktopItemInfo, QList<DesktopItemInfo> desktopItemInfos);
    void openFile(DesktopItemInfo desktopItemInfo);

    /*create file*/
    void createDirectory();
    void createDirectoryFinished(QString dirName);
    void createFile();
    void createFileFinished(QString filename);
    void createFileFromTemplate(QString templatefile);
    void createFileFromTemplateFinished(QString filename);
    void sortByKey(QString key);

    /*app group*/
    void requestCreatingAppGroup(QStringList urls);
    void getAppGroupItemsByUrl(QString group_url);
    void createAppGroup(QString group_url, QStringList urls);
    void mergeIntoAppGroup(QStringList urls, QString group_url);

    /*paste files*/
    void pasteFiles(QString action, QStringList files, QString destination);

    /*delay get thumbnail*/
    void delayGetThumbnail();

private:
    FileMonitor* m_fileMonitor = NULL;
    FileMonitorInstanceInterface* m_desktopMonitorInterface = NULL;
    ClipboardInterface* m_clipboardInterface = NULL;
    QMap<QString, FileMonitorInstanceInterfacePointer> m_appGroupMonitorInterfacePointers;
    FileInfoInterface* m_fileInfoInterface = NULL;
    DesktopDaemonInterface* m_desktopDaemonInterface = NULL;
    FileOperationsInterface* m_fileOperationsInterface = NULL;

    CreateDirJobInterface* m_createDirJobInterface = NULL;
    CreateFileJobInterface* m_createFileJobInterface = NULL;
    CreateFileFromTemplateJobInterface* m_createFileFromTemplateJobInterface = NULL;

    DBusDockSetting* m_dockSettingInterface = NULL;

    DesktopItemInfoMap m_desktopItemInfoMap;
    QMap<QString, DesktopItemInfoMap> m_appGroups;

    QString m_itemShoudBeMoved;

    QTimer* m_thumbnailTimer;
    QString m_currentThumbnail;
    QStringList m_thumbnails;

    Q_DISABLE_COPY(DBusController)

};

#endif // DBUSCONTROLLER_H
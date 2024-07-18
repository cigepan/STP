#pragma once

#include <QObject>
#include <QMap>
#include <QHash>
#include <QPair>
#include <QVector>
#include <QLabel>
#include <QSharedPointer>
#include <QImage>
#include <QDir>
#include <QFile>
#include <QFileInfoList>
#include <QDesktopServices>
#include <QFileDialog>
#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonArray>
#include <QGroupBox>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QGridLayout>
#include <QFormLayout>
#include <QScrollBar>
#include <QComboBox>
#include <QPushButton>
#include <QRadioButton>
#include <QCheckBox>
#include <QLineEdit>
#include <QSpinBox>
#include <QDoubleSpinBox>
#include <QMessageBox>
#include <QTextBrowser>
#include <QInputDialog>
#include <QKeyEvent>
#include <QSqlDatabase>
#include <QSqlError>
#include <QDateTime>
#include <QMutex>
#include <QReadWriteLock>
#include <QThread>
#include <QTableView>
#include <QDateTime>
#include <QAbstractTableModel>

using namespace std;

template<typename ET>
struct StMap : public QMap<ET,QPair<QString, QString>>
{
    QMap<QString, ET> entp;
    QMap<QString, QString> enzh;
    QVector<ET> tps;
    QStringList ens;
    QStringList zhs;
    QStringList ezs;
    StMap(const QMap<ET,QPair<QString, QString>>& map={{}})
        : QMap<ET,QPair<QString, QString>>(map){
        entp.clear(); enzh.clear(); ens.clear(); zhs.clear(); tps.clear();
        for (auto it=map.begin();it!=map.end();it++) {
            tps << it.key();
            ens << it.value().first;
            zhs << it.value().second;
            ezs << QString("%1|%2").arg(ens.last()).arg(zhs.last());
            entp[ens.last()] = tps.last();
            enzh[ens.last()] = zhs.last();
        }
    }
    const QMap<ET,QPair<QString, QString>>& Map() const { return *this; }
    ET Type(const QString& en) const { return entp.value(en); }
    QString EN(ET key) const { return Map().value(key).first; }
    QString ZH(ET key) const { return Map().value(key).second; }
    QString ZH(const QString& en) const { return enzh.value(en); }
    int IDX(const QString& en) const { return ens.indexOf(en); }
};

#define SPIMG QSharedPointer<QImage>

enum EMsgType : char
{
    MSG_NULL=0,
    MSG_OK = 1,
    MSG_YES = 1,
    MSG_FAIL = 2,
    MSG_NO = 2,
    MSG_ENDF
};

const StMap<EMsgType> g_smEMsgType{{
    {MSG_NULL,{"NULL","NULL"}},
    {MSG_OK,{"OK","OK"}},
    {MSG_FAIL,{"FAIL","FAIL"}},
    {MSG_ENDF,{"ENDF","ENDF"}}
}};
#define SMT g_smEMsgType

struct StMsg
{
    QByteArray body;
    EMsgType type{MSG_NULL};

    static QTextBrowser* pLog;
    static QMutex qLock;
    StMsg(const QString& str, EMsgType tp=MSG_NULL){
        if (!str.isEmpty()) { body = str.toLocal8Bit(); }
        type = tp;
    }
    StMsg(const char* str, EMsgType tp=MSG_NULL){
        if (str) { body = QByteArray(str); }
        type = tp;
    }
    StMsg(const StMsg& st){
        body = st.body; type = st.type;
    }
    void log(bool pop=false) const {
        qDebug() << body;
        const QColor clr = [&](){
            switch(type){
            case MSG_NULL: return Qt::darkGray;
            case MSG_OK: return Qt::darkGreen;
            case MSG_FAIL: return Qt::darkRed;
            default: return Qt::darkYellow;
            }
        }();
        if(pLog) {
            QMutexLocker lock(&qLock);
            pLog->setTextColor(clr);
            pLog->append(body);
            pLog->moveCursor(QTextCursor::End);
        }
        if (pop){
            switch(type){
            case MSG_FAIL: QMessageBox::warning(NULL, "", body);
            default: break;
            }
        }
    }
    bool null() const { return (type==MSG_NULL); }
    bool ok() const { return (type==MSG_OK); }
    bool yes() const { return (type==MSG_YES); }
    bool fail() const { return (type==MSG_FAIL); }
    bool no() const { return (type==MSG_NO); }
};

#define SPMSG QSharedPointer<StMsg>
#define SPNULL(XXX) SPMSG(new StMsg(XXX, MSG_NULL))
#define _null SPNULL("")
#define _unknow SPNULL("")
#define SPOK(XXX) SPMSG(new StMsg(XXX, MSG_OK))
#define _ok SPOK("")
#define _yes SPOK("")
#define SPFAIL(XXX) SPMSG(new StMsg(XXX, MSG_FAIL))
#define _fail SPFAIL("")
#define _no SPFAIL("")

struct StLog
{
    SPMSG operator <<(SPMSG sp){ sp->log(true); return sp; }
    SPMSG operator <<(const char* p) { return (*this<<SPNULL(p)); }
    SPMSG operator <<(StMsg& st) { return (*this<<SPMSG(new StMsg(st))); }
};
extern StLog g_stLog;
#define LOG g_stLog

inline QString GSS_BORDER(const QString& rgba) { return QString("border:1px solid %1;").arg(rgba); }
inline QString GSS_COLOR(const QString& rgba) { return QString("color:%1;").arg(rgba); }
inline QString GSS_GPB_BORDER(const QString& rgba) { return QString("QGroupBox{border:1px solid %1;}").arg(rgba); }
inline QString GSS_GPB_COLOR(const QString& rgba) { return QString("QGroupBox{color:%1;}").arg(rgba); }


#define SPPOS QSharedPointer<QPoint>
#define SPXY(XY) SPPOS(new QPoint(XY))

#pragma once

#include <QObject>
#include <CMyDef.h>

#include "ThostFtdcMdApi.h"
#include "ThostFtdcUserApiDataType.h"
#include "ThostFtdcUserApiStruct.h"

#define RSP_ISFAIL(RSP) ((RSP && RSP->ErrorID!=0 && RSP->ErrorMsg[0] > 0))

class CTabMarket : public QTableView
{
    Q_OBJECT
public:
    explicit CTabMarket(QWidget *parent = nullptr):QTableView(parent){}
};


class CModelMarket : public CThostFtdcMdSpi
{
    CThostFtdcMdApi* m_pApi;
    CThostFtdcReqUserLoginField m_stUser;
public:
    CModelMarket(QObject *parent = nullptr);
    ~CModelMarket();

    // class CThreadMD : public QThread
    // {
    //     CThostFtdcMdApi* api;
    //     CThreadMD(QObject *parent = nullptr):QThread(parent){
    //         start();
    //     }
    //     void Start(CThostFtdcMdApi* p){
    //         api=p; start();
    //     }
    //     virtual void run()
    //     {

    //         m_pApi->Join();

    //     }
    // } MD;

    ///当客户端与交易后台建立起通信连接时（还未登录前），该方法被调用。
    virtual void OnFrontConnected();

    ///当客户端与交易后台通信连接断开时，该方法被调用。当发生这个情况后，API会自动重新连接，客户端可不做处理。
    ///@param nReason 错误原因
    ///        0x1001 网络读失败
    ///        0x1002 网络写失败
    ///        0x2001 接收心跳超时
    ///        0x2002 发送心跳失败
    ///        0x2003 收到错误报文
    virtual void OnFrontDisconnected(int nReason){ qDebug() << "OnFrontDisconnected"; }

    ///心跳超时警告。当长时间未收到报文时，该方法被调用。
    ///@param nTimeLapse 距离上次接收报文的时间
    virtual void OnHeartBeatWarning(int nTimeLapse){ qDebug() << "OnHeartBeatWarning"; }

    ///登录请求响应
    virtual void OnRspUserLogin(CThostFtdcRspUserLoginField *pRspUserLogin, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast);

    ///登出请求响应
    virtual void OnRspUserLogout(CThostFtdcUserLogoutField *pUserLogout, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast) {};

    ///错误应答
    virtual void OnRspError(CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast) {};

    ///订阅行情应答
    virtual void OnRspSubMarketData(CThostFtdcSpecificInstrumentField *pSpecificInstrument, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast) {};

    ///取消订阅行情应答
    virtual void OnRspUnSubMarketData(CThostFtdcSpecificInstrumentField *pSpecificInstrument, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast) {};

    ///订阅询价应答
    virtual void OnRspSubForQuoteRsp(CThostFtdcSpecificInstrumentField *pSpecificInstrument, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast) {};

    ///取消订阅询价应答
    virtual void OnRspUnSubForQuoteRsp(CThostFtdcSpecificInstrumentField *pSpecificInstrument, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast) {};

    ///深度行情通知
    virtual void OnRtnDepthMarketData(CThostFtdcDepthMarketDataField *pDepthMarketData) {};

    ///分价表通知
    virtual void OnRtnMBLMarketData(CThostFtdcMBLMarketDataField *pMBLMarketData) {};

    ///询价通知
    virtual void OnRtnForQuoteRsp(CThostFtdcForQuoteRspField *pForQuoteRsp) {};

};


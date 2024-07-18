#include "CTabMarket.h"


CModelMarket::CModelMarket(QObject *parent)
{
    m_pApi = CThostFtdcMdApi::CreateFtdcMdApi();
    m_pApi->RegisterSpi(this);
    m_pApi->RegisterFront("xxx");
    m_pApi->Init();
}
CModelMarket::~CModelMarket(){
    m_pApi->Release();
}

void CModelMarket::OnFrontConnected()
{
    qDebug() << "OnFrontConnected";
    m_stUser = CThostFtdcReqUserLoginField{"","","xxx","888"};
    m_pApi->ReqUserLogin(&m_stUser, QDateTime::currentMSecsSinceEpoch());
}

void CModelMarket::OnRspUserLogin(CThostFtdcRspUserLoginField *pRspUserLogin, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast)
{
    qDebug() << "OnRspUserLogin";
    if (RSP_ISFAIL(pRspInfo)){
        LOG << pRspInfo->ErrorMsg; return;
    }
}

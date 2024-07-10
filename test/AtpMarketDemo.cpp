#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "ThostFtdcMdApi.h"


class MdSpi : public CThostFtdcMdSpi
{
private:
    CThostFtdcMdApi *mdapi;
public:
    MdSpi(CThostFtdcMdApi *_api)
    {
        mdapi = _api;
    }

    void OnFrontConnected()
    {
        printf("Connected\n");
        CThostFtdcReqUserLoginField loginField = {0};
        strcpy(loginField.BrokerID, "");
        strcpy(loginField.UserID, "");
        strcpy(loginField.Password, "");
        mdapi->ReqUserLogin(&loginField, 0);
    }

    void OnRspUserLogin(CThostFtdcRspUserLoginField *pRspUserLogin, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast)
    {
        bool res = pRspInfo && (pRspInfo->ErrorID != 0);
        if (!res)
        {
            printf("Login\n");
            char **t_InstrumentId =  new char *[1];
            t_InstrumentId[0] = "GC2408-CME";
            mdapi->SubscribeMarketData(t_InstrumentId, 1);
        }else{
            printf("%s\n", pRspInfo->ErrorMsg);
        }
        
    }

    void OnRspUserLogout(CThostFtdcUserLogoutField *pUserLogout, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast)
    {
        bool res = pRspInfo && (pRspInfo->ErrorID != 0);
        if (!res)
        {
            printf("Logout\n");
        }else{
            printf("%s\n", pRspInfo->ErrorMsg);
        }
    }

    void OnRspSubMarketData(CThostFtdcSpecificInstrumentField *pSpecificInstrument, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast)
    {
        printf("OnRspSubMarketData\n");
        bool res = pRspInfo && (pRspInfo->ErrorID != 0);
        if (res)
        {
            printf("%s\n", pRspInfo->ErrorMsg);
        }
        if ((pRspInfo == NULL || pRspInfo->ErrorID == 0) && pSpecificInstrument != NULL)
        {
            printf("Subscribe md[%s]\n", pSpecificInstrument->InstrumentID);
        }
    }

    void OnRtnDepthMarketData(CThostFtdcDepthMarketDataField *pDepthMarketData)
    {
        printf("MD[%s.%d][%s]: p=%f, v=%d, ask1=%f, bid1=%f, TD=%s, EX=%s\n", 
                pDepthMarketData->UpdateTime, 
                pDepthMarketData->UpdateMillisec, 
                pDepthMarketData->InstrumentID, 
                pDepthMarketData->LastPrice, 
                pDepthMarketData->Volume,
                pDepthMarketData->AskPrice1,
                pDepthMarketData->BidPrice1,
                pDepthMarketData->TradingDay,
                pDepthMarketData->ExchangeID);
    }
};

int main(int argc, char *argv[])
{
    char* frontAddr = "tcp://127.0.0.1:0023";
    CThostFtdcMdApi* mdapi = CThostFtdcMdApi::CreateFtdcMdApi("");
    MdSpi* mdspi = new MdSpi(mdapi);
    mdapi->RegisterSpi(mdspi);
    mdapi->RegisterFront(frontAddr);

    mdapi->Init();
    mdapi->Join();

    return 0;
}

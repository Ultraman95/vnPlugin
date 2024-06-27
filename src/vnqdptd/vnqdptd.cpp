// vnctpmd.cpp : ���� DLL Ӧ�ó���ĵ���������
//

#include "vnqdptd.h"


///-------------------------------------------------------------------------------------
///C++�Ļص����������ݱ��浽������
///-------------------------------------------------------------------------------------

void TdApi::OnFrontConnected()
{
    Task task = Task();
    task.task_name = ONFRONTCONNECTED;
    this->task_queue.push(task);
};

void TdApi::OnFrontDisconnected(int nReason)
{
    Task task = Task();
    task.task_name = ONFRONTDISCONNECTED;
    task.task_id = nReason;
    this->task_queue.push(task);
};

void TdApi::OnHeartBeatWarning(int nTimeLapse)
{
    Task task = Task();
    task.task_name = ONHEARTBEATWARNING;
    task.task_id = nTimeLapse;
    this->task_queue.push(task);
};

void TdApi::OnRspUserLogin(CQdpFtdcRspUserLoginField *pRspUserLogin, CQdpFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast)
{
    Task task = Task();
    task.task_name = ONRSPUSERLOGIN;
    if (pRspUserLogin)
    {
        CQdpFtdcRspUserLoginField *task_data = new CQdpFtdcRspUserLoginField();
        *task_data = *pRspUserLogin;
        task.task_data = task_data;
    }
    if (pRspInfo)
    {
        CQdpFtdcRspInfoField *task_error = new CQdpFtdcRspInfoField();
        *task_error = *pRspInfo;
        task.task_error = task_error;
    }
    task.task_id = nRequestID;
    task.task_last = bIsLast;
    this->task_queue.push(task);
};

void TdApi::OnRspUserLogout(CQdpFtdcRspUserLogoutField *pUserLogout, CQdpFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast)
{
    Task task = Task();
    task.task_name = ONRSPUSERLOGOUT;
    if (pUserLogout)
    {
        CQdpFtdcRspUserLogoutField *task_data = new CQdpFtdcRspUserLogoutField();
        *task_data = *pUserLogout;
        task.task_data = task_data;
    }
    if (pRspInfo)
    {
        CQdpFtdcRspInfoField *task_error = new CQdpFtdcRspInfoField();
        *task_error = *pRspInfo;
        task.task_error = task_error;
    }
    task.task_id = nRequestID;
    task.task_last = bIsLast;
    this->task_queue.push(task);
};

void TdApi::OnRspOrderInsert(CQdpFtdcInputOrderField *pInputOrder, CQdpFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast)
{
    Task task = Task();
    task.task_name = ONRSPORDERINSERT;
    if (pInputOrder)
    {
        CQdpFtdcInputOrderField *task_data = new CQdpFtdcInputOrderField();
        *task_data = *pInputOrder;
        task.task_data = task_data;
    }
    if (pRspInfo)
    {
        CQdpFtdcRspInfoField *task_error = new CQdpFtdcRspInfoField();
        *task_error = *pRspInfo;
        task.task_error = task_error;
    }
    task.task_id = nRequestID;
    task.task_last = bIsLast;
    this->task_queue.push(task);
};

void TdApi::OnRspOrderAction(CQdpFtdcOrderActionField *pInputOrderAction, CQdpFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast)
{
    Task task = Task();
    task.task_name = ONRSPORDERACTION;
    if (pInputOrderAction)
    {
        CQdpFtdcOrderActionField *task_data = new CQdpFtdcOrderActionField();
        *task_data = *pInputOrderAction;
        task.task_data = task_data;
    }
    if (pRspInfo)
    {
        CQdpFtdcRspInfoField *task_error = new CQdpFtdcRspInfoField();
        *task_error = *pRspInfo;
        task.task_error = task_error;
    }
    task.task_id = nRequestID;
    task.task_last = bIsLast;
    this->task_queue.push(task);
};

void TdApi::OnRspQryOrder(CQdpFtdcOrderField *pOrder, CQdpFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast)
{
    Task task = Task();
    task.task_name = ONRSPQRYORDER;
    if (pOrder)
    {
        CQdpFtdcOrderField *task_data = new CQdpFtdcOrderField();
        *task_data = *pOrder;
        task.task_data = task_data;
    }
    if (pRspInfo)
    {
        CQdpFtdcRspInfoField *task_error = new CQdpFtdcRspInfoField();
        *task_error = *pRspInfo;
        task.task_error = task_error;
    }
    task.task_id = nRequestID;
    task.task_last = bIsLast;
    this->task_queue.push(task);
};

void TdApi::OnRspQryTrade(CQdpFtdcTradeField *pTrade, CQdpFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast)
{
    Task task = Task();
    task.task_name = ONRSPQRYTRADE;
    if (pTrade)
    {
        CQdpFtdcTradeField *task_data = new CQdpFtdcTradeField();
        *task_data = *pTrade;
        task.task_data = task_data;
    }
    if (pRspInfo)
    {
        CQdpFtdcRspInfoField *task_error = new CQdpFtdcRspInfoField();
        *task_error = *pRspInfo;
        task.task_error = task_error;
    }
    task.task_id = nRequestID;
    task.task_last = bIsLast;
    this->task_queue.push(task);
};

void TdApi::OnRspQryInvestorAccount(CQdpFtdcRspInvestorAccountField *pInvestorAccount, CQdpFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast)
{
    Task task = Task();
    task.task_name = ONRSPQRYINVESTORACCOUNT;
    if (pInvestorAccount)
    {
        CQdpFtdcRspInvestorAccountField *task_data = new CQdpFtdcRspInvestorAccountField();
        *task_data = *pInvestorAccount;
        task.task_data = task_data;
    }
    if (pRspInfo)
    {
        CQdpFtdcRspInfoField *task_error = new CQdpFtdcRspInfoField();
        *task_error = *pRspInfo;
        task.task_error = task_error;
    }
    task.task_id = nRequestID;
    task.task_last = bIsLast;
    this->task_queue.push(task);
};

void TdApi::OnRspQryInvestorPosition(CQdpFtdcRspInvestorPositionField *pInvestorPosition, CQdpFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast)
{
    Task task = Task();
    task.task_name = ONRSPQRYINVESTORPOSITION;
    if (pInvestorPosition)
    {
        CQdpFtdcRspInvestorPositionField *task_data = new CQdpFtdcRspInvestorPositionField();
        *task_data = *pInvestorPosition;
        task.task_data = task_data;
    }
    if (pRspInfo)
    {
        CQdpFtdcRspInfoField *task_error = new CQdpFtdcRspInfoField();
        *task_error = *pRspInfo;
        task.task_error = task_error;
    }
    task.task_id = nRequestID;
    task.task_last = bIsLast;
    this->task_queue.push(task);
};

void TdApi::OnRspError(CQdpFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast)
{
    Task task = Task();
    task.task_name = ONRSPERROR;
    if (pRspInfo)
    {
        CQdpFtdcRspInfoField *task_error = new CQdpFtdcRspInfoField();
        *task_error = *pRspInfo;
        task.task_error = task_error;
    }
    task.task_id = nRequestID;
    task.task_last = bIsLast;
    this->task_queue.push(task);
};

void TdApi::OnRtnOrder(CQdpFtdcOrderField *pOrder)
{
    Task task = Task();
    task.task_name = ONRTNORDER;
    if (pOrder)
    {
        CQdpFtdcOrderField *task_data = new CQdpFtdcOrderField();
        *task_data = *pOrder;
        task.task_data = task_data;
    }
    this->task_queue.push(task);
};

void TdApi::OnRtnTrade(CQdpFtdcTradeField *pTrade)
{
    Task task = Task();
    task.task_name = ONRTNTRADE;
    if (pTrade)
    {
        CQdpFtdcTradeField *task_data = new CQdpFtdcTradeField();
        *task_data = *pTrade;
        task.task_data = task_data;
    }
    this->task_queue.push(task);
};

void TdApi::OnErrRtnOrderInsert(CQdpFtdcInputOrderField *pInputOrder, CQdpFtdcRspInfoField *pRspInfo)
{
    Task task = Task();
    task.task_name = ONERRRTNORDERINSERT;
    if (pInputOrder)
    {
        CQdpFtdcInputOrderField *task_data = new CQdpFtdcInputOrderField();
        *task_data = *pInputOrder;
        task.task_data = task_data;
    }
    if (pRspInfo)
    {
        CQdpFtdcRspInfoField *task_error = new CQdpFtdcRspInfoField();
        *task_error = *pRspInfo;
        task.task_error = task_error;
    }
    this->task_queue.push(task);
};

void TdApi::OnErrRtnOrderAction(CQdpFtdcOrderActionField *pOrderAction, CQdpFtdcRspInfoField *pRspInfo)
{
    Task task = Task();
    task.task_name = ONERRRTNORDERACTION;
    if (pOrderAction)
    {
        CQdpFtdcOrderActionField *task_data = new CQdpFtdcOrderActionField();
        *task_data = *pOrderAction;
        task.task_data = task_data;
    }
    if (pRspInfo)
    {
        CQdpFtdcRspInfoField *task_error = new CQdpFtdcRspInfoField();
        *task_error = *pRspInfo;
        task.task_error = task_error;
    }
    this->task_queue.push(task);
};

void TdApi::OnRtnInstrumentStatus(CQdpFtdcInstrumentStatusField *pInstrumentStatus)
{
    Task task = Task();
    task.task_name = ONRTNINSTRUMENTSTATUS;
    if (pInstrumentStatus)
    {
        CQdpFtdcInstrumentStatusField *task_data = new CQdpFtdcInstrumentStatusField();
        *task_data = *pInstrumentStatus;
        task.task_data = task_data;
    }
    this->task_queue.push(task);
};


///-------------------------------------------------------------------------------------
///�����̴߳Ӷ�����ȡ�����ݣ�ת��Ϊpython����󣬽�������
///-------------------------------------------------------------------------------------

void TdApi::processTask()
{
    try
    {
        while (this->active)
        {
            Task task = this->task_queue.pop();

            switch (task.task_name)
            {
            case ONFRONTCONNECTED:
            {
                this->processFrontConnected(&task);
                break;
            }

            case ONFRONTDISCONNECTED:
            {
                this->processFrontDisconnected(&task);
                break;
            }

            case ONHEARTBEATWARNING:
            {
                this->processHeartBeatWarning(&task);
                break;
            }

            case ONRSPUSERLOGIN:
            {
                this->processRspUserLogin(&task);
                break;
            }

            case ONRSPUSERLOGOUT:
            {
                this->processRspUserLogout(&task);
                break;
            }

            case ONRSPORDERINSERT:
            {
                this->processRspOrderInsert(&task);
                break;
            }

            case ONRSPORDERACTION:
            {
                this->processRspOrderAction(&task);
                break;
            }

            case ONRSPQRYORDER:
            {
                this->processRspQryOrder(&task);
                break;
            }

            case ONRSPQRYTRADE:
            {
                this->processRspQryTrade(&task);
                break;
            }

            case ONRSPQRYINVESTORACCOUNT:
            {
                this->processRspQryInvestorAccount(&task);
                break;
            }

            case ONRSPQRYINVESTORPOSITION:
            {
                this->processRspQryInvestorPosition(&task);
                break;
            }

            case ONRSPERROR:
            {
                this->processRspError(&task);
                break;
            }

            case ONRTNORDER:
            {
                this->processRtnOrder(&task);
                break;
            }

            case ONRTNTRADE:
            {
                this->processRtnTrade(&task);
                break;
            }

            case ONERRRTNORDERINSERT:
            {
                this->processErrRtnOrderInsert(&task);
                break;
            }

            case ONERRRTNORDERACTION:
            {
                this->processErrRtnOrderAction(&task);
                break;
            }

            case ONRTNINSTRUMENTSTATUS:
            {
                this->processRtnInstrumentStatus(&task);
                break;
            }
            };
        }
    }
    catch (const TerminatedError&)
    {
    }
};

void TdApi::processFrontConnected(Task *task)
{
    gil_scoped_acquire acquire;
    this->onFrontConnected();
};

void TdApi::processFrontDisconnected(Task *task)
{
    gil_scoped_acquire acquire;
    this->onFrontDisconnected(task->task_id);
};

void TdApi::processHeartBeatWarning(Task *task)
{
    gil_scoped_acquire acquire;
    this->onHeartBeatWarning(task->task_id);
};

void TdApi::processRspUserLogin(Task *task)
{
    gil_scoped_acquire acquire;
    dict data;
    if (task->task_data)
    {
        CQdpFtdcRspUserLoginField *task_data = (CQdpFtdcRspUserLoginField*)task->task_data;
        data["TradingDay"] = toUtf(task_data->TradingDay);
        data["BrokerID"] = toUtf(task_data->BrokerID);
        data["UserID"] = toUtf(task_data->UserID);
        data["LoginTime"] = toUtf(task_data->LoginTime);
        data["MaxOrderLocalID"] = toUtf(task_data->MaxOrderLocalID);
        data["TradingSystemName"] = toUtf(task_data->TradingSystemName);
        data["DataCenterID"] = task_data->DataCenterID;
        data["PrivateFlowSize"] = task_data->PrivateFlowSize;
        data["UserFlowSize"] = task_data->UserFlowSize;
        data["SessionID"] = task_data->SessionID;
        data["FrontID"] = task_data->FrontID;
        data["KeyValue"] = toUtf(task_data->KeyValue);
        delete task_data;
    }
    dict error;
    if (task->task_error)
    {
        CQdpFtdcRspInfoField *task_error = (CQdpFtdcRspInfoField*)task->task_error;
        error["ErrorID"] = task_error->ErrorID;
        error["ErrorMsg"] = toUtf(task_error->ErrorMsg);
        delete task_error;
    }
    this->onRspUserLogin(data, error, task->task_id, task->task_last);
};

void TdApi::processRspUserLogout(Task *task)
{
    gil_scoped_acquire acquire;
    dict data;
    if (task->task_data)
    {
        CQdpFtdcRspUserLogoutField *task_data = (CQdpFtdcRspUserLogoutField*)task->task_data;
        data["BrokerID"] = toUtf(task_data->BrokerID);
        data["UserID"] = toUtf(task_data->UserID);
        data["LogoutReason"] = task_data->LogoutReason;
        delete task_data;
    }
    dict error;
    if (task->task_error)
    {
        CQdpFtdcRspInfoField *task_error = (CQdpFtdcRspInfoField*)task->task_error;
        error["ErrorID"] = task_error->ErrorID;
        error["ErrorMsg"] = toUtf(task_error->ErrorMsg);
        delete task_error;
    }
    this->onRspUserLogout(data, error, task->task_id, task->task_last);
};

void TdApi::processRspOrderInsert(Task *task)
{
    gil_scoped_acquire acquire;
    dict data;
    if (task->task_data)
    {
        CQdpFtdcInputOrderField *task_data = (CQdpFtdcInputOrderField*)task->task_data;
        data["BrokerID"] = toUtf(task_data->BrokerID);
        data["ExchangeID"] = toUtf(task_data->ExchangeID);
        data["OrderSysID"] = toUtf(task_data->OrderSysID);
        data["InvestorID"] = toUtf(task_data->InvestorID);
        data["UserID"] = toUtf(task_data->UserID);
        data["InstrumentID"] = toUtf(task_data->InstrumentID);
        data["UserOrderLocalID"] = toUtf(task_data->UserOrderLocalID);
        data["OrderPriceType"] = task_data->OrderPriceType;
        data["Direction"] = task_data->Direction;
        data["OffsetFlag"] = task_data->OffsetFlag;
        data["HedgeFlag"] = task_data->HedgeFlag;
        data["LimitPrice"] = task_data->LimitPrice;
        data["Volume"] = task_data->Volume;
        data["TimeCondition"] = task_data->TimeCondition;
        data["GTDDate"] = toUtf(task_data->GTDDate);
        data["VolumeCondition"] = task_data->VolumeCondition;
        data["MinVolume"] = task_data->MinVolume;
        data["StopPrice"] = task_data->StopPrice;
        data["ForceCloseReason"] = task_data->ForceCloseReason;
        data["IsAutoSuspend"] = task_data->IsAutoSuspend;
        data["BusinessUnit"] = toUtf(task_data->BusinessUnit);
        data["UserCustom"] = toUtf(task_data->UserCustom);
        data["BranchID"] = toUtf(task_data->BranchID);
        data["RecNum"] = task_data->RecNum;
        data["BusinessType"] = task_data->BusinessType;
        delete task_data;
    }
    dict error;
    if (task->task_error)
    {
        CQdpFtdcRspInfoField *task_error = (CQdpFtdcRspInfoField*)task->task_error;
        error["ErrorID"] = task_error->ErrorID;
        error["ErrorMsg"] = toUtf(task_error->ErrorMsg);
        delete task_error;
    }
    this->onRspOrderInsert(data, error, task->task_id, task->task_last);
};

void TdApi::processRspOrderAction(Task *task)
{
    gil_scoped_acquire acquire;
    dict data;
    if (task->task_data)
    {
        CQdpFtdcOrderActionField *task_data = (CQdpFtdcOrderActionField*)task->task_data;
        data["ExchangeID"] = toUtf(task_data->ExchangeID);
        data["OrderSysID"] = toUtf(task_data->OrderSysID);
        data["BrokerID"] = toUtf(task_data->BrokerID);
        data["InvestorID"] = toUtf(task_data->InvestorID);
        data["UserID"] = toUtf(task_data->UserID);
        data["InstrumentID"] = toUtf(task_data->InstrumentID);
        data["UserOrderActionLocalID"] = task_data->UserOrderActionLocalID;
        data["UserOrderLocalID"] = toUtf(task_data->UserOrderLocalID);
        data["ActionFlag"] = task_data->ActionFlag;
        data["LimitPrice"] = task_data->LimitPrice;
        data["VolumeChange"] = task_data->VolumeChange;
        data["RecNum"] = task_data->RecNum;
        data["FrontID"] = task_data->FrontID;
        data["SessionID"] = task_data->SessionID;
        delete task_data;
    }
    dict error;
    if (task->task_error)
    {
        CQdpFtdcRspInfoField *task_error = (CQdpFtdcRspInfoField*)task->task_error;
        error["ErrorID"] = task_error->ErrorID;
        error["ErrorMsg"] = toUtf(task_error->ErrorMsg);
        delete task_error;
    }
    this->onRspOrderAction(data, error, task->task_id, task->task_last);
};

void TdApi::processRspQryOrder(Task *task)
{
    gil_scoped_acquire acquire;
    dict data;
    if (task->task_data)
    {
        CQdpFtdcOrderField *task_data = (CQdpFtdcOrderField*)task->task_data;
        data["BrokerID"] = toUtf(task_data->BrokerID);
        data["ExchangeID"] = toUtf(task_data->ExchangeID);
        data["OrderSysID"] = toUtf(task_data->OrderSysID);
        data["InvestorID"] = toUtf(task_data->InvestorID);
        data["UserID"] = toUtf(task_data->UserID);
        data["InstrumentID"] = toUtf(task_data->InstrumentID);
        data["UserOrderLocalID"] = toUtf(task_data->UserOrderLocalID);
        data["OrderPriceType"] = task_data->OrderPriceType;
        data["Direction"] = task_data->Direction;
        data["OffsetFlag"] = task_data->OffsetFlag;
        data["HedgeFlag"] = task_data->HedgeFlag;
        data["LimitPrice"] = task_data->LimitPrice;
        data["Volume"] = task_data->Volume;
        data["TimeCondition"] = task_data->TimeCondition;
        data["GTDDate"] = toUtf(task_data->GTDDate);
        data["VolumeCondition"] = task_data->VolumeCondition;
        data["MinVolume"] = task_data->MinVolume;
        data["StopPrice"] = task_data->StopPrice;
        data["ForceCloseReason"] = task_data->ForceCloseReason;
        data["IsAutoSuspend"] = task_data->IsAutoSuspend;
        data["BusinessUnit"] = toUtf(task_data->BusinessUnit);
        data["UserCustom"] = toUtf(task_data->UserCustom);
        data["BranchID"] = toUtf(task_data->BranchID);
        data["RecNum"] = task_data->RecNum;
        data["BusinessType"] = task_data->BusinessType;
        data["TradingDay"] = toUtf(task_data->TradingDay);
        data["ParticipantID"] = toUtf(task_data->ParticipantID);
        data["ClientID"] = toUtf(task_data->ClientID);
        data["SeatID"] = toUtf(task_data->SeatID);
        data["InsertTime"] = toUtf(task_data->InsertTime);
        data["OrderLocalID"] = toUtf(task_data->OrderLocalID);
        data["OrderSource"] = task_data->OrderSource;
        data["OrderStatus"] = task_data->OrderStatus;
        data["CancelTime"] = toUtf(task_data->CancelTime);
        data["CancelUserID"] = toUtf(task_data->CancelUserID);
        data["VolumeTraded"] = task_data->VolumeTraded;
        data["VolumeRemain"] = task_data->VolumeRemain;
        data["FrontID"] = task_data->FrontID;
        data["SessionID"] = task_data->SessionID;
        delete task_data;
    }
    dict error;
    if (task->task_error)
    {
        CQdpFtdcRspInfoField* task_error = (CQdpFtdcRspInfoField*)task->task_error;
        error["ErrorID"] = task_error->ErrorID;
        error["ErrorMsg"] = toUtf(task_error->ErrorMsg);
        delete task_error;
    }
    this->onRspQryOrder(data, error, task->task_id, task->task_last);
};

void TdApi::processRspQryTrade(Task *task)
{
    gil_scoped_acquire acquire;
    dict data;
    if (task->task_data)
    {
        CQdpFtdcTradeField *task_data = (CQdpFtdcTradeField*)task->task_data;
        data["TradingDay"] = toUtf(task_data->TradingDay);
        data["BrokerID"] = toUtf(task_data->BrokerID);
        data["ExchangeID"] = toUtf(task_data->ExchangeID);
        data["ParticipantID"] = toUtf(task_data->ParticipantID);
        data["SeatID"] = toUtf(task_data->SeatID);
        data["InvestorID"] = toUtf(task_data->InvestorID);
        data["ClientID"] = toUtf(task_data->ClientID);
        data["UserID"] = toUtf(task_data->UserID);
        data["TradeID"] = toUtf(task_data->TradeID);
        data["OrderSysID"] = toUtf(task_data->OrderSysID);
        data["UserOrderLocalID"] = toUtf(task_data->UserOrderLocalID);
        data["InstrumentID"] = toUtf(task_data->InstrumentID);
        data["Direction"] = task_data->Direction;
        data["OffsetFlag"] = task_data->OffsetFlag;
        data["HedgeFlag"] = task_data->HedgeFlag;
        data["TradePrice"] = task_data->TradePrice;
        data["TradeVolume"] = task_data->TradeVolume;
        data["TradeTime"] = toUtf(task_data->TradeTime);
        data["ClearingPartID"] = toUtf(task_data->ClearingPartID);
        data["TradeAmnt"] = task_data->TradeAmnt;
        data["RecNum"] = task_data->RecNum;
        data["TradeType"] = task_data->TradeType;
        delete task_data;
    }
    dict error;
    if (task->task_error)
    {
        CQdpFtdcRspInfoField *task_error = (CQdpFtdcRspInfoField*)task->task_error;
        error["ErrorID"] = task_error->ErrorID;
        error["ErrorMsg"] = toUtf(task_error->ErrorMsg);
        delete task_error;
    }
    this->onRspQryTrade(data, error, task->task_id, task->task_last);
};

void TdApi::processRspQryInvestorAccount(Task *task)
{
    gil_scoped_acquire acquire;
    dict data;
    if (task->task_data)
    {
        CQdpFtdcRspInvestorAccountField *task_data = (CQdpFtdcRspInvestorAccountField*)task->task_data;
        data["BrokerID"] = toUtf(task_data->BrokerID);
        data["InvestorID"] = toUtf(task_data->InvestorID);
        data["AccountID"] = toUtf(task_data->AccountID);
        data["PreBalance"] = task_data->PreBalance;
        data["PreAvailable"] = task_data->PreAvailable;
        data["Deposit"] = task_data->Deposit;
        data["Withdraw"] = task_data->Withdraw;
        data["Margin"] = task_data->Margin;
        data["Premium"] = task_data->Premium;
        data["Fee"] = task_data->Fee;
        data["FrozenMargin"] = task_data->FrozenMargin;
        data["FrozenPremium"] = task_data->FrozenPremium;
        data["FrozenFee"] = task_data->FrozenFee;
        data["CloseProfit"] = task_data->CloseProfit;
        data["PositionProfit"] = task_data->PositionProfit;
        data["Available"] = task_data->Available;
        data["Balance"] = task_data->Balance;
        data["LongMargin"] = task_data->LongMargin;
        data["ShortMargin"] = task_data->ShortMargin;
        data["LongFrozenMargin"] = task_data->LongFrozenMargin;
        data["ShortFrozenMargin"] = task_data->ShortFrozenMargin;
        data["DynamicRights"] = task_data->DynamicRights;
        data["Risk"] = task_data->Risk;
        data["OtherFee"] = task_data->OtherFee;
        data["Mortgage"] = task_data->Mortgage;
        data["Currency"] = toUtf(task_data->Currency);
        delete task_data;
    }
    dict error;
    if (task->task_error)
    {
        CQdpFtdcRspInfoField *task_error = (CQdpFtdcRspInfoField*)task->task_error;
        error["ErrorID"] = task_error->ErrorID;
        error["ErrorMsg"] = toUtf(task_error->ErrorMsg);
        delete task_error;
    }
    this->onRspQryInvestorAccount(data, error, task->task_id, task->task_last);
};

void TdApi::processRspQryInvestorPosition(Task *task)
{
    gil_scoped_acquire acquire;
    dict data;
    if (task->task_data)
    {
        CQdpFtdcRspInvestorPositionField *task_data = (CQdpFtdcRspInvestorPositionField*)task->task_data;
        data["BrokerID"] = toUtf(task_data->BrokerID);
        data["ExchangeID"] = toUtf(task_data->ExchangeID);
        data["InvestorID"] = toUtf(task_data->InvestorID);
        data["ParticipantID"] = toUtf(task_data->ParticipantID);
        data["ClientID"] = toUtf(task_data->ClientID);
        data["InstrumentID"] = toUtf(task_data->InstrumentID);
        data["Direction"] = task_data->Direction;
        data["HedgeFlag"] = task_data->HedgeFlag;
        data["UsedMargin"] = task_data->UsedMargin;
        data["Position"] = task_data->Position;
        data["PositionCost"] = task_data->PositionCost;
        data["YdPosition"] = task_data->YdPosition;
        data["YdPositionCost"] = task_data->YdPositionCost;
        data["FrozenMargin"] = task_data->FrozenMargin;
        data["FrozenPosition"] = task_data->FrozenPosition;
        data["FrozenClosing"] = task_data->FrozenClosing;
        data["FrozenPremium"] = task_data->FrozenPremium;
        data["LastTradeID"] = toUtf(task_data->LastTradeID);
        data["LastOrderLocalID"] = toUtf(task_data->LastOrderLocalID);
        data["Currency"] = toUtf(task_data->Currency);
        data["PositionProfit"] = task_data->PositionProfit;
        data["TodayPosition"] = task_data->TodayPosition;
        data["FrozenTodayClosing"] = task_data->FrozenTodayClosing;
        delete task_data;
    }
    dict error;
    if (task->task_error)
    {
        CQdpFtdcRspInfoField *task_error = (CQdpFtdcRspInfoField*)task->task_error;
        error["ErrorID"] = task_error->ErrorID;
        error["ErrorMsg"] = toUtf(task_error->ErrorMsg);
        delete task_error;
    }
    this->onRspQryInvestorPosition(data, error, task->task_id, task->task_last);
};

void TdApi::processRspError(Task *task)
{
    gil_scoped_acquire acquire;
    dict error;
    if (task->task_error)
    {
        CQdpFtdcRspInfoField *task_error = (CQdpFtdcRspInfoField*)task->task_error;
        error["ErrorID"] = task_error->ErrorID;
        error["ErrorMsg"] = toUtf(task_error->ErrorMsg);
        delete task_error;
    }
    this->onRspError(error, task->task_id, task->task_last);
};

void TdApi::processRtnOrder(Task *task)
{
    gil_scoped_acquire acquire;
    dict data;
    if (task->task_data)
    {
        CQdpFtdcOrderField *task_data = (CQdpFtdcOrderField*)task->task_data;
        data["BrokerID"] = toUtf(task_data->BrokerID);
        data["ExchangeID"] = toUtf(task_data->ExchangeID);
        data["OrderSysID"] = toUtf(task_data->OrderSysID);
        data["InvestorID"] = toUtf(task_data->InvestorID);
        data["UserID"] = toUtf(task_data->UserID);
        data["InstrumentID"] = toUtf(task_data->InstrumentID);
        data["UserOrderLocalID"] = toUtf(task_data->UserOrderLocalID);
        data["OrderPriceType"] = task_data->OrderPriceType;
        data["Direction"] = task_data->Direction;
        data["OffsetFlag"] = task_data->OffsetFlag;
        data["HedgeFlag"] = task_data->HedgeFlag;
        data["LimitPrice"] = task_data->LimitPrice;
        data["Volume"] = task_data->Volume;
        data["TimeCondition"] = task_data->TimeCondition;
        data["GTDDate"] = toUtf(task_data->GTDDate);
        data["VolumeCondition"] = task_data->VolumeCondition;
        data["MinVolume"] = task_data->MinVolume;
        data["StopPrice"] = task_data->StopPrice;
        data["ForceCloseReason"] = task_data->ForceCloseReason;
        data["IsAutoSuspend"] = task_data->IsAutoSuspend;
        data["BusinessUnit"] = toUtf(task_data->BusinessUnit);
        data["UserCustom"] = toUtf(task_data->UserCustom);
        data["BranchID"] = toUtf(task_data->BranchID);
        data["RecNum"] = task_data->RecNum;
        data["BusinessType"] = task_data->BusinessType;
        data["TradingDay"] = toUtf(task_data->TradingDay);
        data["ParticipantID"] = toUtf(task_data->ParticipantID);
        data["ClientID"] = toUtf(task_data->ClientID);
        data["SeatID"] = toUtf(task_data->SeatID);
        data["InsertTime"] = toUtf(task_data->InsertTime);
        data["OrderLocalID"] = toUtf(task_data->OrderLocalID);
        data["OrderSource"] = task_data->OrderSource;
        data["OrderStatus"] = task_data->OrderStatus;
        data["CancelTime"] = toUtf(task_data->CancelTime);
        data["CancelUserID"] = toUtf(task_data->CancelUserID);
        data["VolumeTraded"] = task_data->VolumeTraded;
        data["VolumeRemain"] = task_data->VolumeRemain;
        data["FrontID"] = task_data->FrontID;
        data["SessionID"] = task_data->SessionID;
        delete task_data;
    }
    this->onRtnOrder(data);
};

void TdApi::processRtnTrade(Task *task)
{
    gil_scoped_acquire acquire;
    dict data;
    if (task->task_data)
    {
        CQdpFtdcTradeField *task_data = (CQdpFtdcTradeField*)task->task_data;
        data["TradingDay"] = toUtf(task_data->TradingDay);
        data["BrokerID"] = toUtf(task_data->BrokerID);
        data["ExchangeID"] = toUtf(task_data->ExchangeID);
        data["ParticipantID"] = toUtf(task_data->ParticipantID);
        data["SeatID"] = toUtf(task_data->SeatID);
        data["InvestorID"] = toUtf(task_data->InvestorID);
        data["ClientID"] = toUtf(task_data->ClientID);
        data["UserID"] = toUtf(task_data->UserID);
        data["TradeID"] = toUtf(task_data->TradeID);
        data["OrderSysID"] = toUtf(task_data->OrderSysID);
        data["UserOrderLocalID"] = toUtf(task_data->UserOrderLocalID);
        data["InstrumentID"] = toUtf(task_data->InstrumentID);
        data["Direction"] = task_data->Direction;
        data["OffsetFlag"] = task_data->OffsetFlag;
        data["HedgeFlag"] = task_data->HedgeFlag;
        data["TradePrice"] = task_data->TradePrice;
        data["TradeVolume"] = task_data->TradeVolume;
        data["TradeTime"] = toUtf(task_data->TradeTime);
        data["ClearingPartID"] = toUtf(task_data->ClearingPartID);
        data["TradeAmnt"] = task_data->TradeAmnt;
        data["RecNum"] = task_data->RecNum;
        data["TradeType"] = task_data->TradeType;
        delete task_data;
    }
    this->onRtnTrade(data);
};

void TdApi::processErrRtnOrderInsert(Task *task)
{
    gil_scoped_acquire acquire;
    dict data;
    if (task->task_data)
    {
        CQdpFtdcInputOrderField *task_data = (CQdpFtdcInputOrderField*)task->task_data;
        data["BrokerID"] = toUtf(task_data->BrokerID);
        data["ExchangeID"] = toUtf(task_data->ExchangeID);
        data["OrderSysID"] = toUtf(task_data->OrderSysID);
        data["InvestorID"] = toUtf(task_data->InvestorID);
        data["UserID"] = toUtf(task_data->UserID);
        data["InstrumentID"] = toUtf(task_data->InstrumentID);
        data["UserOrderLocalID"] = toUtf(task_data->UserOrderLocalID);
        data["OrderPriceType"] = task_data->OrderPriceType;
        data["Direction"] = task_data->Direction;
        data["OffsetFlag"] = task_data->OffsetFlag;
        data["HedgeFlag"] = task_data->HedgeFlag;
        data["LimitPrice"] = task_data->LimitPrice;
        data["Volume"] = task_data->Volume;
        data["TimeCondition"] = task_data->TimeCondition;
        data["GTDDate"] = toUtf(task_data->GTDDate);
        data["VolumeCondition"] = task_data->VolumeCondition;
        data["MinVolume"] = task_data->MinVolume;
        data["StopPrice"] = task_data->StopPrice;
        data["ForceCloseReason"] = task_data->ForceCloseReason;
        data["IsAutoSuspend"] = task_data->IsAutoSuspend;
        data["BusinessUnit"] = toUtf(task_data->BusinessUnit);
        data["UserCustom"] = toUtf(task_data->UserCustom);
        data["BranchID"] = toUtf(task_data->BranchID);
        data["RecNum"] = task_data->RecNum;
        data["BusinessType"] = task_data->BusinessType;
        delete task_data;
    }
    dict error;
    if (task->task_error)
    {
        CQdpFtdcRspInfoField *task_error = (CQdpFtdcRspInfoField*)task->task_error;
        error["ErrorID"] = task_error->ErrorID;
        error["ErrorMsg"] = toUtf(task_error->ErrorMsg);
        delete task_error;
    }
    this->onErrRtnOrderInsert(data, error);
};

void TdApi::processErrRtnOrderAction(Task *task)
{
    gil_scoped_acquire acquire;
    dict data;
    if (task->task_data)
    {
        CQdpFtdcOrderActionField *task_data = (CQdpFtdcOrderActionField*)task->task_data;
        data["ExchangeID"] = toUtf(task_data->ExchangeID);
        data["OrderSysID"] = toUtf(task_data->OrderSysID);
        data["BrokerID"] = toUtf(task_data->BrokerID);
        data["InvestorID"] = toUtf(task_data->InvestorID);
        data["UserID"] = toUtf(task_data->UserID);
        data["InstrumentID"] = toUtf(task_data->InstrumentID);
        data["UserOrderActionLocalID"] = toUtf(task_data->UserOrderActionLocalID);
        data["UserOrderLocalID"] = toUtf(task_data->UserOrderLocalID);
        data["ActionFlag"] = task_data->ActionFlag;
        data["LimitPrice"] = task_data->LimitPrice;
        data["VolumeChange"] = task_data->VolumeChange;
        data["RecNum"] = task_data->RecNum;
        data["FrontID"] = task_data->FrontID;
        data["SessionID"] = task_data->SessionID;
        delete task_data;
    }
    dict error;
    if (task->task_error)
    {
        CQdpFtdcRspInfoField *task_error = (CQdpFtdcRspInfoField*)task->task_error;
        error["ErrorID"] = task_error->ErrorID;
        error["ErrorMsg"] = toUtf(task_error->ErrorMsg);
        delete task_error;
    }
    this->onErrRtnOrderAction(data, error);
};

void TdApi::processRtnInstrumentStatus(Task *task)
{
    gil_scoped_acquire acquire;
    dict data;
    if (task->task_data)
    {
        CQdpFtdcInstrumentStatusField *task_data = (CQdpFtdcInstrumentStatusField*)task->task_data;
        data["ExchangeID"] = toUtf(task_data->ExchangeID);
        data["ProductID"] = toUtf(task_data->ProductID);
        data["ProductName"] = toUtf(task_data->ProductName);
        data["InstrumentID"] = toUtf(task_data->InstrumentID);
        data["InstrumentName"] = toUtf(task_data->InstrumentName);
        data["DeliveryYear"] = task_data->DeliveryYear;
        data["DeliveryMonth"] = task_data->DeliveryMonth;
        data["MaxLimitOrderVolume"] = task_data->MaxLimitOrderVolume;
        data["MinLimitOrderVolume"] = task_data->MinLimitOrderVolume;
        data["MaxMarketOrderVolume"] = task_data->MaxMarketOrderVolume;
        data["MinMarketOrderVolume"] = task_data->MinMarketOrderVolume;
        data["VolumeMultiple"] = task_data->VolumeMultiple;
        data["PriceTick"] = task_data->PriceTick;
        data["Currency"] = task_data->Currency;
        data["LongPosLimit"] = task_data->LongPosLimit;
        data["ShortPosLimit"] = task_data->ShortPosLimit;
        data["LowerLimitPrice"] = task_data->LowerLimitPrice;
        data["UpperLimitPrice"] = task_data->UpperLimitPrice;
        data["PreSettlementPrice"] = task_data->PreSettlementPrice;
        data["InstrumentStatus"] = task_data->InstrumentStatus;
        data["CreateDate"] = toUtf(task_data->CreateDate);
        data["OpenDate"] = toUtf(task_data->OpenDate);
        data["ExpireDate"] = toUtf(task_data->ExpireDate);
        data["StartDelivDate"] = toUtf(task_data->StartDelivDate);
        data["EndDelivDate"] = toUtf(task_data->EndDelivDate);
        data["BasisPrice"] = task_data->BasisPrice;
        data["IsTrading"] = task_data->IsTrading;
        data["UnderlyingInstrID"] = toUtf(task_data->UnderlyingInstrID);
        data["UnderlyingMultiple"] = task_data->UnderlyingMultiple;
        data["PositionType"] = task_data->PositionType;
        data["StrikePrice"] = task_data->StrikePrice;
        data["OptionsType"] = task_data->OptionsType;
        data["ProductClass"] = task_data->ProductClass;
        data["OptionsMode"] = task_data->OptionsMode;
        delete task_data;
    }
    this->onRtnInstrumentStatus(data);
};


///-------------------------------------------------------------------------------------
///��������
///-------------------------------------------------------------------------------------

void TdApi::createFtdcTraderApi(string pszFlowPath)
{
    int dummy;
    cout << CQdpFtdcTraderApi::GetVersion(dummy, dummy) << endl;
    this->api = CQdpFtdcTraderApi::CreateFtdcTraderApi(pszFlowPath.c_str());
    this->api->RegisterSpi(this);
};

void TdApi::release()
{
    this->api->Release();
};

void TdApi::init()
{
    this->active = true;
    this->task_thread = thread(&TdApi::processTask, this);

    this->api->Init();
};

int TdApi::join()
{
    int i = this->api->Join();
    return i;
};

int TdApi::exit()
{
    this->active = false;
    this->task_queue.terminate();
    this->task_thread.join();

    this->api->RegisterSpi(NULL);
    this->api->Release();
    this->api = NULL;
    return 1;
};

string TdApi::getTradingDay()
{
    string day = this->api->GetTradingDay();
    return day;
};

void TdApi::registerFront(string pszFrontAddress)
{
    this->api->RegisterFront((char*)pszFrontAddress.c_str());
};

void TdApi::subscribePrivateTopic(int nType)
{
    this->api->SubscribePrivateTopic((QDP_TE_RESUME_TYPE) nType);
};

void TdApi::subscribePublicTopic(int nType)
{
    this->api->SubscribePublicTopic((QDP_TE_RESUME_TYPE)nType);
};

int TdApi::reqUserLogin(const dict &req, int reqid)
{
    CQdpFtdcReqUserLoginField myreq = CQdpFtdcReqUserLoginField();
    memset(&myreq, 0, sizeof(myreq));
    getString(req, "TradingDay", myreq.TradingDay);
    getString(req, "UserID", myreq.UserID);
    getString(req, "BrokerID", myreq.BrokerID);
    getString(req, "Password", myreq.Password);
    getString(req, "UserProductInfo", myreq.UserProductInfo);
    getString(req, "InterfaceProductInfo", myreq.InterfaceProductInfo);
    getString(req, "ProtocolInfo", myreq.ProtocolInfo);
    getString(req, "IPAddress", myreq.IPAddress);
    getString(req, "MacAddress", myreq.MacAddress);
    getInt(req, "DataCenterID", &myreq.DataCenterID);
    getString(req, "OneTimePassword", myreq.OneTimePassword);
    getString(req, "ClientIPAddress", myreq.ClientIPAddress);
    int i = this->api->ReqUserLogin(&myreq, reqid);
    return i;
};

int TdApi::reqUserLogout(const dict &req, int reqid)
{
    CQdpFtdcReqUserLogoutField myreq = CQdpFtdcReqUserLogoutField();
    memset(&myreq, 0, sizeof(myreq));
    getString(req, "BrokerID", myreq.BrokerID);
    getString(req, "UserID", myreq.UserID);
    getInt(req, "LogoutReason", &myreq.LogoutReason);
    int i = this->api->ReqUserLogout(&myreq, reqid);
    return i;
};

int TdApi::reqOrderInsert(const dict &req, int reqid)
{
    CQdpFtdcInputOrderField myreq = CQdpFtdcInputOrderField();
    memset(&myreq, 0, sizeof(myreq));
    getString(req, "BrokerID", myreq.BrokerID);
    getString(req, "ExchangeID", myreq.ExchangeID);
    getString(req, "OrderSysID", myreq.OrderSysID);
    getString(req, "InvestorID", myreq.InvestorID);
    getString(req, "UserID", myreq.UserID);
    getString(req, "InstrumentID", myreq.InstrumentID);
    getString(req, "UserOrderLocalID", myreq.UserOrderLocalID);
    getChar(req, "OrderPriceType", &myreq.OrderPriceType);
    getChar(req, "Direction", &myreq.Direction);
    getChar(req, "OffsetFlag", &myreq.OffsetFlag);
    getChar(req, "HedgeFlag", &myreq.HedgeFlag);
    getDouble(req, "LimitPrice", &myreq.LimitPrice);
    getInt(req, "Volume", &myreq.Volume);
    getChar(req, "TimeCondition", &myreq.TimeCondition);
    getString(req, "GTDDate", myreq.GTDDate);
    getChar(req, "VolumeCondition", &myreq.VolumeCondition);
    getInt(req, "MinVolume", &myreq.MinVolume);
    getDouble(req, "StopPrice", &myreq.StopPrice);
    getChar(req, "ForceCloseReason", &myreq.ForceCloseReason);
    getInt(req, "IsAutoSuspend", &myreq.IsAutoSuspend);
    getString(req, "BusinessUnit", myreq.BusinessUnit);
    getString(req, "UserCustom", myreq.UserCustom);
    getString(req, "BranchID", myreq.BranchID);
    getInt(req, "RecNum", &myreq.RecNum);
    getChar(req, "BusinessType", &myreq.BusinessType);
    int i = this->api->ReqOrderInsert(&myreq, reqid);
    return i;
};

int TdApi::reqOrderAction(const dict &req, int reqid)
{
    CQdpFtdcOrderActionField myreq = CQdpFtdcOrderActionField();
    memset(&myreq, 0, sizeof(myreq));
    getString(req, "ExchangeID", myreq.ExchangeID);
    getString(req, "OrderSysID", myreq.OrderSysID);
    getString(req, "BrokerID", myreq.BrokerID);
    getString(req, "InvestorID", myreq.InvestorID);
    getString(req, "UserID", myreq.UserID);
    getString(req, "InstrumentID", myreq.InstrumentID);
    getString(req, "UserOrderActionLocalID", myreq.UserOrderActionLocalID);
    getString(req, "UserOrderLocalID", myreq.UserOrderLocalID);
    getChar(req, "ActionFlag", &myreq.ActionFlag);
    getDouble(req, "LimitPrice", &myreq.LimitPrice);
    getInt(req, "VolumeChange", &myreq.VolumeChange);
    getInt(req, "RecNum", &myreq.RecNum);
    getInt(req, "FrontID", &myreq.FrontID);
    getInt(req, "SessionID", &myreq.SessionID);
    int i = this->api->ReqOrderAction(&myreq, reqid);
    return i;
};

int TdApi::reqQryOrder(const dict &req, int reqid)
{
    CQdpFtdcQryOrderField myreq = CQdpFtdcQryOrderField();
    memset(&myreq, 0, sizeof(myreq));
    getString(req, "BrokerID", myreq.BrokerID);
    getString(req, "UserID", myreq.UserID);
    getString(req, "ExchangeID", myreq.ExchangeID);
    getString(req, "InvestorID", myreq.InvestorID);
    getString(req, "OrderSysID", myreq.OrderSysID);
    getString(req, "InstrumentID", myreq.InstrumentID);
    int i = this->api->ReqQryOrder(&myreq, reqid);
    return i;
};

int TdApi::reqQryTrade(const dict &req, int reqid)
{
    CQdpFtdcQryTradeField myreq = CQdpFtdcQryTradeField();
    memset(&myreq, 0, sizeof(myreq));
    getString(req, "BrokerID", myreq.BrokerID);
    getString(req, "UserID", myreq.UserID);
    getString(req, "ExchangeID", myreq.ExchangeID);
    getString(req, "InvestorID", myreq.InvestorID);
    getString(req, "TradeID", myreq.TradeID);
    getString(req, "InstrumentID", myreq.InstrumentID);
    int i = this->api->ReqQryTrade(&myreq, reqid);
    return i;
};

int TdApi::reqQryInvestorAccount(const dict &req, int reqid)
{
    CQdpFtdcQryInvestorAccountField myreq = CQdpFtdcQryInvestorAccountField();
    memset(&myreq, 0, sizeof(myreq));
    getString(req, "BrokerID", myreq.BrokerID);
    getString(req, "UserID", myreq.UserID);
    getString(req, "InvestorID", myreq.InvestorID);
    int i = this->api->ReqQryInvestorAccount(&myreq, reqid);
    return i;
};

int TdApi::reqQryInvestorPosition(const dict &req, int reqid)
{
    CQdpFtdcQryInvestorPositionField myreq = CQdpFtdcQryInvestorPositionField();
    memset(&myreq, 0, sizeof(myreq));
    getString(req, "BrokerID", myreq.BrokerID);
    getString(req, "UserID", myreq.UserID);
    getString(req, "ExchangeID", myreq.ExchangeID);
    getString(req, "InvestorID", myreq.InvestorID);
    getString(req, "InstrumentID", myreq.InstrumentID);
    int i = this->api->ReqQryInvestorPosition(&myreq, reqid);
    return i;
};


///-------------------------------------------------------------------------------------
///Boost.Python��װ
///-------------------------------------------------------------------------------------

class PyTdApi : public TdApi
{
public:
    using TdApi::TdApi;
    
    void onFrontConnected() override
    {
        try
        {
            PYBIND11_OVERLOAD(void, TdApi, onFrontConnected);
        }
        catch (const error_already_set &e)
        {
            cout << e.what() << endl;
        }
    };

    void onFrontDisconnected(int reqid) override
    {
        try
        {
            PYBIND11_OVERLOAD(void, TdApi, onFrontDisconnected, reqid);
        }
        catch (const error_already_set &e)
        {
            cout << e.what() << endl;
        }
    };

    void onHeartBeatWarning(int reqid) override
    {
        try
        {
            PYBIND11_OVERLOAD(void, TdApi, onHeartBeatWarning, reqid);
        }
        catch (const error_already_set &e)
        {
            cout << e.what() << endl;
        }
    };

    void onRspUserLogin(const dict &data, const dict &error, int reqid, bool last) override
    {
        try
        {
            PYBIND11_OVERLOAD(void, TdApi, onRspUserLogin, data, error, reqid, last);
        }
        catch (const error_already_set &e)
        {
            cout << e.what() << endl;
        }
    };

    void onRspUserLogout(const dict &data, const dict &error, int reqid, bool last) override
    {
        try
        {
            PYBIND11_OVERLOAD(void, TdApi, onRspUserLogout, data, error, reqid, last);
        }
        catch (const error_already_set &e)
        {
            cout << e.what() << endl;
        }
    };

    void onRspOrderInsert(const dict &data, const dict &error, int reqid, bool last) override
    {
        try
        {
            PYBIND11_OVERLOAD(void, TdApi, onRspOrderInsert, data, error, reqid, last);
        }
        catch (const error_already_set &e)
        {
            cout << e.what() << endl;
        }
    };

    void onRspOrderAction(const dict &data, const dict &error, int reqid, bool last) override
    {
        try
        {
            PYBIND11_OVERLOAD(void, TdApi, onRspOrderAction, data, error, reqid, last);
        }
        catch (const error_already_set &e)
        {
            cout << e.what() << endl;
        }
    };

    void onRspQryOrder(const dict &data, const dict &error, int reqid, bool last) override
    {
        try
        {
            PYBIND11_OVERLOAD(void, TdApi, onRspQryOrder, data, error, reqid, last);
        }
        catch (const error_already_set &e)
        {
            cout << e.what() << endl;
        }
    };

    void onRspQryTrade(const dict &data, const dict &error, int reqid, bool last) override
    {
        try
        {
            PYBIND11_OVERLOAD(void, TdApi, onRspQryTrade, data, error, reqid, last);
        }
        catch (const error_already_set &e)
        {
            cout << e.what() << endl;
        }
    };

    void onRspQryInvestorAccount(const dict &data, const dict &error, int reqid, bool last) override
    {
        try
        {
            PYBIND11_OVERLOAD(void, TdApi, onRspQryInvestorAccount, data, error, reqid, last);
        }
        catch (const error_already_set &e)
        {
            cout << e.what() << endl;
        }
    };

    void onRspQryInvestorPosition(const dict &data, const dict &error, int reqid, bool last) override
    {
        try
        {
            PYBIND11_OVERLOAD(void, TdApi, onRspQryInvestorPosition, data, error, reqid, last);
        }
        catch (const error_already_set &e)
        {
            cout << e.what() << endl;
        }
    };

    void onRspError(const dict &error, int reqid, bool last) override
    {
        try
        {
            PYBIND11_OVERLOAD(void, TdApi, onRspError, error, reqid, last);
        }
        catch (const error_already_set &e)
        {
            cout << e.what() << endl;
        }
    };

    void onRtnOrder(const dict &data) override
    {
        try
        {
            PYBIND11_OVERLOAD(void, TdApi, onRtnOrder, data);
        }
        catch (const error_already_set &e)
        {
            cout << e.what() << endl;
        }
    };

    void onRtnTrade(const dict &data) override
    {
        try
        {
            PYBIND11_OVERLOAD(void, TdApi, onRtnTrade, data);
        }
        catch (const error_already_set &e)
        {
            cout << e.what() << endl;
        }
    };

    void onErrRtnOrderInsert(const dict &data, const dict &error) override
    {
        try
        {
            PYBIND11_OVERLOAD(void, TdApi, onErrRtnOrderInsert, data, error);
        }
        catch (const error_already_set &e)
        {
            cout << e.what() << endl;
        }
    };

    void onErrRtnOrderAction(const dict &data, const dict &error) override
    {
        try
        {
            PYBIND11_OVERLOAD(void, TdApi, onErrRtnOrderAction, data, error);
        }
        catch (const error_already_set &e)
        {
            cout << e.what() << endl;
        }
    };

    void onRtnInstrumentStatus(const dict &data) override
    {
        try
        {
            PYBIND11_OVERLOAD(void, TdApi, onRtnInstrumentStatus, data);
        }
        catch (const error_already_set &e)
        {
            cout << e.what() << endl;
        }
    };


};


PYBIND11_MODULE(vnqdptd, m)
{
    class_<TdApi, PyTdApi> TdApi(m, "TdApi", module_local());
    TdApi
        .def(init<>())
        .def("createFtdcTraderApi", &TdApi::createFtdcTraderApi, R"pbdoc(
            Create TraderApi

            Parameters:
                arg0: Directory for storing subscription information files, defaulting to the current directory
        )pbdoc")
        .def("release", &TdApi::release, "Delete the interface object itself")
        .def("init", &TdApi::init, "Initialize")
        .def("join", &TdApi::join, "Waiting for the interface thread to finish running")
        .def("exit", &TdApi::exit, "Terminate program")
        .def("getTradingDay", &TdApi::getTradingDay, R"pbdoc(
            Get the current trading day

            Return:
                The retrieved trading day
        )pbdoc")
        .def("registerFront", &TdApi::registerFront, R"pbdoc(
            Register the network address of the front server

            Parameters:
                arg0: Front-end server network address
                      The format of the network address is "protocol://ipaddress:port", for example: "tcp://127.0.0.1:17001"
                      "tcp" represents the transmission protocol, "127.0.0.1" represents the server address and "17001" represents the server port number
        )pbdoc")
        .def("subscribePublicTopic", &TdApi::subscribePublicTopic, R"pbdoc(
            Subscribe to public stream

            Parameters:
                arg0: Public stream retransmission method
                      QDP_TERT_RESTART: Restart from the current trading day
                      QDP_TERT_RESUME: Resume from the last received packet
                      QDP_TERT_QUICK: Only transmit the contents of the private stream after login
                      This method should be called before Init. If not called, public stream data will not be received.
        )pbdoc")
        .def("subscribePrivateTopic", &TdApi::subscribePrivateTopic, R"pbdoc(
            Subscribe to private stream

            Parameters:
                arg0: Private stream retransmission method
                      QDP_TERT_RESTART: Restart from the current trading day
                      QDP_TERT_RESUME: Resume from the last received packet
                      QDP_TERT_QUICK: Only transmit the contents of the private stream after login
                      This method should be called before Init. If not called, private stream data will not be received.
        )pbdoc")

        .def("reqUserLogin", &TdApi::reqUserLogin, R"pbdoc(
            User login request

            Parameters:
                arg0: CQdpFtdcReqUserLoginField
                arg1: Request ID
        )pbdoc")
        .def("reqUserLogout", &TdApi::reqUserLogout, R"pbdoc(
            User logout request

            Parameters:
                arg0: CQdpFtdcReqUserLogoutField
                arg1: Request ID
        )pbdoc")
        .def("reqOrderInsert", &TdApi::reqOrderInsert, R"pbdoc(
            Order Entry Request

            Parameters:
                arg0: CQdpFtdcInputOrderField
                arg1: Request ID
        )pbdoc")
        .def("reqOrderAction", &TdApi::reqOrderAction, R"pbdoc(
            Order Action Request

            Parameters:
                arg0: CQdpFtdcOrderActionField
                arg1: Request ID
        )pbdoc")
        .def("reqQryOrder", &TdApi::reqQryOrder, R"pbdoc(
            Order Inquiry Request

            Parameters:
                arg0: CQdpFtdcQryOrderField
                arg1: Request ID
        )pbdoc")
        .def("reqQryTrade", &TdApi::reqQryTrade, R"pbdoc(
            Filled Order Inquiry Request

            Parameters:
                arg0: CQdpFtdcQryTradeField
                arg1: Request ID
        )pbdoc")
        .def("reqQryInvestorAccount", &TdApi::reqQryInvestorAccount, R"pbdoc(
            Investor Account Inquiry Request

            Parameters:
                arg0: CQdpFtdcQryInvestorAccountField
                arg1: Request ID
        )pbdoc")
        .def("reqQryInvestorPosition", &TdApi::reqQryInvestorPosition, R"pbdoc(
            Investor Position Inquiry Request

            Parameters:
                arg0: CQdpFtdcQryInvestorPositionField
                arg1: Request ID
        )pbdoc")

        .def("onFrontConnected", &TdApi::onFrontConnected, "When the client establishes a communication connection with the trading backend (before logging in), this method is called.")
        .def("onFrontDisconnected", &TdApi::onFrontDisconnected, R"pbdoc(
            When the client's communication connection with the trading backend is disconnected, this method is called.
            After this event occurs, the API will automatically reconnect, and the client does not need to take any action.

            Parameters:
                arg0: Error reason
                      0x1001 Network read failure
                      0x1002 Network write failure
                      0x2001 Heartbeat receive timeout
                      0x2002 Heartbeat send failure
                      0x2003 Received error message
        )pbdoc")
        .def("onHeartBeatWarning", &TdApi::onHeartBeatWarning, R"pbdoc(
            Heartbeat timeout warning. When no messages are received for an extended period, this method is called.

            Parameters:
                arg0: Time since last message received
        )pbdoc")
        .def("onRspUserLogin", &TdApi::onRspUserLogin, R"pbdoc(
            User login response

            Parameters:
                arg0: CQdpFtdcRspUserLoginField
                arg1: CQdpFtdcRspInfoField
                arg2: Request ID
                arg3: Is last
        )pbdoc")
        .def("onRspUserLogout", &TdApi::onRspUserLogout, R"pbdoc(
            User logout response

            Parameters:
                arg0: CQdpFtdcRspUserLogoutField
                arg1: CQdpFtdcRspInfoField
                arg2: Request ID
                arg3: Is last
        )pbdoc")
        .def("onRspOrderInsert", &TdApi::onRspOrderInsert, R"pbdoc(
            Order Entry Response

            Parameters:
                arg0: CQdpFtdcInputOrderField
                arg1: CQdpFtdcRspInfoField
                arg2: Request ID
                arg3: Is last
        )pbdoc")
        .def("onRspOrderAction", &TdApi::onRspOrderAction, R"pbdoc(
            Order Action Response

            Parameters:
                arg0: CQdpFtdcOrderActionField
                arg1: CQdpFtdcRspInfoField
                arg2: Request ID
                arg3: Is last
        )pbdoc")
        .def("onRspQryOrder", &TdApi::onRspQryOrder, R"pbdoc(
            Order Inquiry Response

            Parameters:
                arg0: CQdpFtdcOrderField
                arg1: CQdpFtdcRspInfoField
                arg2: Request ID
                arg3: Is last
        )pbdoc")
        .def("onRspQryTrade", &TdApi::onRspQryTrade, R"pbdoc(
            Filled Order Inquiry Response

            Parameters:
                arg0: CQdpFtdcTradeField
                arg1: CQdpFtdcRspInfoField
                arg2: Request ID
                arg3: Is last
        )pbdoc")
        .def("onRspQryInvestorAccount", &TdApi::onRspQryInvestorAccount, R"pbdoc(
            Investor Account Inquiry Response

            Parameters:
                arg0: CQdpFtdcRspInvestorAccountField
                arg1: CQdpFtdcRspInfoField
                arg2: Request ID
                arg3: Is last
        )pbdoc")
        .def("onRspQryInvestorPosition", &TdApi::onRspQryInvestorPosition, R"pbdoc(
            Investor Position Inquiry Response

            Parameters:
                arg0: CQdpFtdcRspInvestorPositionField
                arg1: CQdpFtdcRspInfoField
                arg2: Request ID
                arg3: Is last
        )pbdoc")
        .def("onRspError", &TdApi::onRspError, R"pbdoc(
            Error response

            Parameters:
                arg0: CQdpFtdcRspInfoField
                arg1: Request ID
                arg2: Is last
        )pbdoc")
        .def("onRtnOrder", &TdApi::onRtnOrder, R"pbdoc(
            Order Execution Report

            Parameters:
                arg0: CQdpFtdcOrderField
        )pbdoc")
        .def("onRtnTrade", &TdApi::onRtnTrade, R"pbdoc(
            Trade Execution Report

            Parameters:
                arg0: CQdpFtdcTradeField
        )pbdoc")
        .def("onErrRtnOrderInsert", &TdApi::onErrRtnOrderInsert, R"pbdoc(
            Order Entry Error Report

            Parameters:
                arg0: CQdpFtdcInputOrderField
                arg1: CQdpFtdcRspInfoField
        )pbdoc")
        .def("onErrRtnOrderAction", &TdApi::onErrRtnOrderAction, R"pbdoc(
            Order Action Error Report

            Parameters:
                arg0: CQdpFtdcOrderActionField
                arg1: CQdpFtdcRspInfoField
        )pbdoc")
        .def("onRtnInstrumentStatus", &TdApi::onRtnInstrumentStatus, R"pbdoc(
            Contract Trading Status Notification

            Parameters:
                arg0: CQdpFtdcInstrumentStatusField
        )pbdoc")
        ;
}

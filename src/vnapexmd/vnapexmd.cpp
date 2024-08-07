// vnapexmd.cpp : ���� DLL Ӧ�ó���ĵ���������
//

#include "vnapexmd.h"

///-------------------------------------------------------------------------------------
///C++�Ļص����������ݱ��浽������
///-------------------------------------------------------------------------------------

void MdApi::OnFrontConnected()
{
    Task task = Task();
    task.task_name = ONFRONTCONNECTED;
    this->task_queue.push(task);
};

void MdApi::OnFrontDisconnected(int nReason)
{
    Task task = Task();
    task.task_name = ONFRONTDISCONNECTED;
    task.task_id = nReason;
    this->task_queue.push(task);
};

void MdApi::OnHeartBeatWarning(int nTimeLapse)
{
    Task task = Task();
    task.task_name = ONHEARTBEATWARNING;
    task.task_id = nTimeLapse;
    this->task_queue.push(task);
};

void MdApi::OnRspUserLogin(CApexFtdcRspUserLoginField *pRspUserLogin, CApexFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast)
{
    Task task = Task();
    task.task_name = ONRSPUSERLOGIN;
    if (pRspUserLogin)
    {
        CApexFtdcRspUserLoginField *task_data = new CApexFtdcRspUserLoginField();
        *task_data = *pRspUserLogin;
        task.task_data = task_data;
    }
    if (pRspInfo)
    {
        CApexFtdcRspInfoField *task_error = new CApexFtdcRspInfoField();
        *task_error = *pRspInfo;
        task.task_error = task_error;
    }
    task.task_id = nRequestID;
    task.task_last = bIsLast;
    this->task_queue.push(task);
};

void MdApi::OnRspUserLogout(CApexFtdcRspUserLogoutField *pUserLogout, CApexFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast)
{
    Task task = Task();
    task.task_name = ONRSPUSERLOGOUT;
    if (pUserLogout)
    {
        CApexFtdcRspUserLogoutField *task_data = new CApexFtdcRspUserLogoutField();
        *task_data = *pUserLogout;
        task.task_data = task_data;
    }
    if (pRspInfo)
    {
        CApexFtdcRspInfoField *task_error = new CApexFtdcRspInfoField();
        *task_error = *pRspInfo;
        task.task_error = task_error;
    }
    task.task_id = nRequestID;
    task.task_last = bIsLast;
    this->task_queue.push(task);
};

void MdApi::OnRspError(CApexFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast)
{
    Task task = Task();
    task.task_name = ONRSPERROR;
    if (pRspInfo)
    {
        CApexFtdcRspInfoField *task_error = new CApexFtdcRspInfoField();
        *task_error = *pRspInfo;
        task.task_error = task_error;
    }
    task.task_id = nRequestID;
    task.task_last = bIsLast;
    this->task_queue.push(task);
};
/*TODO
void MdApi::OnRspSubMarketData(CQdFtdcSpecificInstrumentField *pSpecificInstrument, CQdFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast)
{
    Task task = Task();
    task.task_name = ONRSPSUBMARKETDATA;
    if (pSpecificInstrument)
    {
        CQdFtdcSpecificInstrumentField *task_data = new CQdFtdcSpecificInstrumentField();
        *task_data = *pSpecificInstrument;
        task.task_data = task_data;
    }
    if (pRspInfo)
    {
        CQdFtdcRspInfoField *task_error = new CQdFtdcRspInfoField();
        *task_error = *pRspInfo;
        task.task_error = task_error;
    }
    task.task_id = nRequestID;
    task.task_last = bIsLast;
    this->task_queue.push(task);
};*/
/*TODO
void MdApi::OnRspUnSubMarketData(CQdFtdcSpecificInstrumentField *pSpecificInstrument, CQdFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast)
{
    Task task = Task();
    task.task_name = ONRSPUNSUBMARKETDATA;
    if (pSpecificInstrument)
    {
        CQdFtdcSpecificInstrumentField *task_data = new CQdFtdcSpecificInstrumentField();
        *task_data = *pSpecificInstrument;
        task.task_data = task_data;
    }
    if (pRspInfo)
    {
        CQdFtdcRspInfoField *task_error = new CQdFtdcRspInfoField();
        *task_error = *pRspInfo;
        task.task_error = task_error;
    }
    task.task_id = nRequestID;
    task.task_last = bIsLast;
    this->task_queue.push(task);
};*/

void MdApi::OnRtnDepthMarketData(CApexFtdcDepthMarketDataField *pDepthMarketData)
{
    Task task = Task();
    task.task_name = ONRTNDEPTHMARKETDATA;
    if (pDepthMarketData)
    {
        CApexFtdcDepthMarketDataField *task_data = new CApexFtdcDepthMarketDataField();
        *task_data = *pDepthMarketData;
        task.task_data = task_data;
    }
    this->task_queue.push(task);
};



///-------------------------------------------------------------------------------------
///�����̴߳Ӷ�����ȡ�����ݣ�ת��Ϊpython����󣬽�������
///-------------------------------------------------------------------------------------

void MdApi::processTask()
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

            case ONRSPERROR:
            {
                this->processRspError(&task);
                break;
            }
/*TODO
            case ONRSPSUBMARKETDATA:
            {
                this->processRspSubMarketData(&task);
                break;
            }*/
/*TODO
            case ONRSPUNSUBMARKETDATA:
            {
                this->processRspUnSubMarketData(&task);
                break;
            }*/

            case ONRTNDEPTHMARKETDATA:
            {
                this->processRtnDepthMarketData(&task);
                break;
            }
            };
        }
    }
    catch (const TerminatedError&)
    {
    }
};

void MdApi::processFrontConnected(Task *task)
{
    gil_scoped_acquire acquire;
    this->onFrontConnected();
};

void MdApi::processFrontDisconnected(Task *task)
{
    gil_scoped_acquire acquire;
    this->onFrontDisconnected(task->task_id);
};

void MdApi::processHeartBeatWarning(Task *task)
{
    gil_scoped_acquire acquire;
    this->onHeartBeatWarning(task->task_id);
};

void MdApi::processRspUserLogin(Task *task)
{
    gil_scoped_acquire acquire;
    dict data;
    if (task->task_data)
    {
        CApexFtdcRspUserLoginField *task_data = (CApexFtdcRspUserLoginField *)task->task_data;
        data["TradingDay"] = toUtf(task_data->TradingDay);
        data["LoginTime"] = toUtf(task_data->LoginTime);
        data["MaxOrderLocalID"] = toUtf(task_data->MaxOrderLocalID);
        data["UserID"] = toUtf(task_data->UserID);
        data["ParticipantID"] = toUtf(task_data->ParticipantID);
        data["TradingSystemName"] = toUtf(task_data->TradingSystemName);
        data["DataCenterID"] = task_data->DataCenterID;
        data["PrivateFlowSize"] = task_data->PrivateFlowSize;
        data["UserFlowSize"] = task_data->UserFlowSize;
        delete task_data;
    }
    dict error;
    if (task->task_error)
    {
        CApexFtdcRspInfoField *task_error = (CApexFtdcRspInfoField *)task->task_error;
        error["ErrorID"] = task_error->ErrorID;
        error["ErrorMsg"] = toUtf(task_error->ErrorMsg);
        delete task_error;
    }
    this->onRspUserLogin(data, error, task->task_id, task->task_last);
};

void MdApi::processRspUserLogout(Task *task)
{
    gil_scoped_acquire acquire;
    dict data;
    if (task->task_data)
    {
        CApexFtdcRspUserLogoutField *task_data = (CApexFtdcRspUserLogoutField *)task->task_data;
        data["UserID"] = toUtf(task_data->UserID);
        data["ParticipantID"] = toUtf(task_data->ParticipantID);
        delete task_data;
    }
    dict error;
    if (task->task_error)
    {
        CApexFtdcRspInfoField *task_error = (CApexFtdcRspInfoField *)task->task_error;
        error["ErrorID"] = task_error->ErrorID;
        error["ErrorMsg"] = toUtf(task_error->ErrorMsg);
        delete task_error;
    }
    this->onRspUserLogout(data, error, task->task_id, task->task_last);
};

void MdApi::processRspError(Task *task)
{
    gil_scoped_acquire acquire;
    dict error;
    if (task->task_error)
    {
        CApexFtdcRspInfoField *task_error = (CApexFtdcRspInfoField *)task->task_error;
        error["ErrorID"] = task_error->ErrorID;
        error["ErrorMsg"] = toUtf(task_error->ErrorMsg);
        delete task_error;
    }
    this->onRspError(error, task->task_id, task->task_last);
};
/*TODO
void MdApi::processRspSubMarketData(Task *task)
{
    gil_scoped_acquire acquire;
    dict data;
    if (task->task_data)
    {
        CQdFtdcSpecificInstrumentField *task_data = (CQdFtdcSpecificInstrumentField *)task->task_data;
        data["InstrumentID"] = toUtf(task_data->InstrumentID);
        delete task->task_data;
    }
    dict error;
    if (task->task_error)
    {
        CQdFtdcRspInfoField *task_error = (CQdFtdcRspInfoField *)task->task_error;
        error["ErrorID"] = task_error->ErrorID;
        error["ErrorMsg"] = toUtf(task_error->ErrorMsg);
        delete task->task_error;
    }
    this->onRspSubMarketData(data, error, task->task_id, task->task_last);
};*/
/*TODO
void MdApi::processRspUnSubMarketData(Task *task)
{
    gil_scoped_acquire acquire;
    dict data;
    if (task->task_data)
    {
        CQdFtdcSpecificInstrumentField *task_data = (CQdFtdcSpecificInstrumentField *)task->task_data;
        data["InstrumentID"] = toUtf(task_data->InstrumentID);
        delete task->task_data;
    }
    dict error;
    if (task->task_error)
    {
        CQdFtdcRspInfoField *task_error = (CQdFtdcRspInfoField *)task->task_error;
        error["ErrorID"] = task_error->ErrorID;
        error["ErrorMsg"] = toUtf(task_error->ErrorMsg);
        delete task->task_error;
    }
    this->onRspUnSubMarketData(data, error, task->task_id, task->task_last);
};*/

void MdApi::processRtnDepthMarketData(Task *task)
{
    gil_scoped_acquire acquire;
    dict data;
    if (task->task_data)
    {
        CApexFtdcDepthMarketDataField *task_data = (CApexFtdcDepthMarketDataField *)task->task_data;
        data["TradingDay"] = toUtf(task_data->TradingDay);
        data["SettlementGroupID"] = toUtf(task_data->SettlementGroupID);
        data["SettlementID"] = task_data->SettlementID;
        data["LastPrice"] = task_data->LastPrice;
        data["PreSettlementPrice"] = task_data->PreSettlementPrice;
        data["PreClosePrice"] = task_data->PreClosePrice;
        data["PreOpenInterest"] = task_data->PreOpenInterest;
        data["OpenPrice"] = task_data->OpenPrice;
        data["HighestPrice"] = task_data->HighestPrice;
        data["LowestPrice"] = task_data->LowestPrice;
        data["Volume"] = task_data->Volume;
        data["Turnover"] = task_data->Turnover;
        data["OpenInterest"] = task_data->OpenInterest;
        data["ClosePrice"] = task_data->ClosePrice;
        data["SettlementPrice"] = task_data->SettlementPrice;
        data["UpperLimitPrice"] = task_data->UpperLimitPrice;
        data["LowerLimitPrice"] = task_data->LowerLimitPrice;
        data["PreDelta"] = task_data->PreDelta;
        data["CurrDelta"] = task_data->CurrDelta;
        data["UpdateTime"] = toUtf(task_data->UpdateTime);
        data["UpdateMillisec"] = task_data->UpdateMillisec;
        data["InstrumentID"] = toUtf(task_data->InstrumentID);
        data["BidPrice1"] = task_data->BidPrice1;
        data["BidVolume1"] = task_data->BidVolume1;
        data["AskPrice1"] = task_data->AskPrice1;
        data["AskVolume1"] = task_data->AskVolume1;
        data["BidPrice2"] = task_data->BidPrice2;
        data["BidVolume2"] = task_data->BidVolume2;
        data["AskPrice2"] = task_data->AskPrice2;
        data["AskVolume2"] = task_data->AskVolume2;
        data["BidPrice3"] = task_data->BidPrice3;
        data["BidVolume3"] = task_data->BidVolume3;
        data["AskPrice3"] = task_data->AskPrice3;
        data["AskVolume3"] = task_data->AskVolume3;
        data["BidPrice4"] = task_data->BidPrice4;
        data["BidVolume4"] = task_data->BidVolume4;
        data["AskPrice4"] = task_data->AskPrice4;
        data["AskVolume4"] = task_data->AskVolume4;
        data["BidPrice5"] = task_data->BidPrice5;
        data["BidVolume5"] = task_data->BidVolume5;
        data["AskPrice5"] = task_data->AskPrice5;
        data["AskVolume5"] = task_data->AskVolume5;
        data["BandingUpperPrice"] = task_data->BandingUpperPrice;
        data["BandingLowerPrice"] = task_data->BandingLowerPrice;
        data["ReferencePrice"] = task_data->ReferencePrice;
        data["CalendarDate"] = toUtf(task_data->CalendarDate);
        delete task_data;
    }
    this->onRtnDepthMarketData(data);
};

///-------------------------------------------------------------------------------------
///��������
///-------------------------------------------------------------------------------------

void MdApi::createFtdcMduserApi(string pszFlowPath)
{
    cout << CApexFtdcMduserApi::GetVersion() << endl;
    this->api = CApexFtdcMduserApi::CreateFtdcMduserApi(pszFlowPath.c_str());
    this->api->RegisterSpi(this);
};

void MdApi::release()
{
    this->api->Release();
};

void MdApi::init()
{
    this->active = true;
    this->task_thread = thread(&MdApi::processTask, this);

    this->api->Init();
};

int MdApi::join()
{
    int i = this->api->Join();
    return i;
};

int MdApi::exit()
{
    this->active = false;
    this->task_queue.terminate();
    this->task_thread.join();

    this->api->RegisterSpi(NULL);
    this->api->Release();
    this->api = NULL;
    return 1;
};

string MdApi::getTradingDay()
{
    string day = this->api->GetTradingDay();
    return day;
};

void MdApi::registerFront(string pszFrontAddress)
{
    this->api->RegisterFront((char*)pszFrontAddress.c_str());
};

/*TODO
int MdApi::subscribeMarketData(string instrumentID)
{
    char* buffer = (char*) instrumentID.c_str();
    char* myreq[1] = { buffer };
    int i = this->api->SubMarketData(myreq, 1);
    return i;
};*/

/*TODO
int MdApi::unSubscribeMarketData(string instrumentID)
{
    char* buffer = (char*)instrumentID.c_str();
    char* myreq[1] = { buffer };;
    int i = this->api->UnSubMarketData(myreq, 1);
    return i;
};*/

int MdApi::reqUserLogin(const dict &req, int reqid)
{
    CApexFtdcReqUserLoginField myreq = CApexFtdcReqUserLoginField();
    memset(&myreq, 0, sizeof(myreq));
    getString(req, "TradingDay", myreq.TradingDay);
    getString(req, "UserID", myreq.UserID);
    getString(req, "ParticipantID", myreq.ParticipantID);
    getString(req, "Password", myreq.Password);
    getString(req, "UserProductInfo", myreq.UserProductInfo);
    getString(req, "InterfaceProductInfo", myreq.InterfaceProductInfo);
    getString(req, "ProtocolInfo", myreq.ProtocolInfo);
    getInt(req, "DataCenterID", &myreq.DataCenterID);
    int i = this->api->ReqUserLogin(&myreq, reqid);
    return i;
};

int MdApi::reqUserLogout(const dict &req, int reqid)
{
    CApexFtdcReqUserLogoutField myreq = CApexFtdcReqUserLogoutField();
    memset(&myreq, 0, sizeof(myreq));
    getString(req, "UserID", myreq.UserID);
    getString(req, "ParticipantID", myreq.ParticipantID);
    int i = this->api->ReqUserLogout(&myreq, reqid);
    return i;
};


///-------------------------------------------------------------------------------------
///Boost.Python��װ
///-------------------------------------------------------------------------------------

class PyMdApi: public MdApi
{
public:
    using MdApi::MdApi;

    void onFrontConnected() override
    {
        try
        {
            PYBIND11_OVERLOAD(void, MdApi, onFrontConnected);
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
            PYBIND11_OVERLOAD(void, MdApi, onFrontDisconnected, reqid);
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
            PYBIND11_OVERLOAD(void, MdApi, onHeartBeatWarning, reqid);
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
            PYBIND11_OVERLOAD(void, MdApi, onRspUserLogin, data, error, reqid, last);
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
            PYBIND11_OVERLOAD(void, MdApi, onRspUserLogout, data, error, reqid, last);
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
            PYBIND11_OVERLOAD(void, MdApi, onRspError, error, reqid, last);
        }
        catch (const error_already_set &e)
        {
            cout << e.what() << endl;
        }
    };

/*TODO
    void onRspSubMarketData(const dict &data, const dict &error, int reqid, bool last) override
    {
        try
        {
            PYBIND11_OVERLOAD(void, MdApi, onRspSubMarketData, data, error, reqid, last);
        }
        catch (const error_already_set &e)
        {
            cout << e.what() << endl;
        }
    };*/

/*TODO
    void onRspUnSubMarketData(const dict &data, const dict &error, int reqid, bool last) override
    {
        try
        {
            PYBIND11_OVERLOAD(void, MdApi, onRspUnSubMarketData, data, error, reqid, last);
        }
        catch (const error_already_set &e)
        {
            cout << e.what() << endl;
        }
    };*/

    void onRtnDepthMarketData(const dict &data) override
    {
        try
        {
            PYBIND11_OVERLOAD(void, MdApi, onRtnDepthMarketData, data);
        }
        catch (const error_already_set &e)
        {
            cout << e.what() << endl;
        }
    };
};


PYBIND11_MODULE(vnapexmd, m)
{
    class_<MdApi, PyMdApi> mdapi(m, "MdApi", module_local());
    mdapi
        .def(init<>())
        .def("createFtdcMduserApi", &MdApi::createFtdcMduserApi, R"pbdoc(
            Create MduserApi

            Parameters:
                arg0: Directory for storing subscription information files, defaulting to the current directory
        )pbdoc")
        .def("release", &MdApi::release, "Delete the interface object itself")
        .def("init", &MdApi::init, "Initialize")
        .def("join", &MdApi::join, "Waiting for the interface thread to finish running")
        .def("exit", &MdApi::exit, "Terminate program")
        .def("getTradingDay", &MdApi::getTradingDay, R"pbdoc(
            Get the current trading day

            Return:
                The retrieved trading day
        )pbdoc")
        .def("registerFront", &MdApi::registerFront, R"pbdoc(
            Register the network address of the front server

            Parameters:
                arg0: Front-end server network address
                      The format of the network address is "protocol://ipaddress:port", for example: "tcp://127.0.0.1:17001"
                      "tcp" represents the transmission protocol, "127.0.0.1" represents the server address and "17001" represents the server port number
        )pbdoc")
        /*TODO
        .def("subscribeMarketData", &MdApi::subscribeMarketData, R"pbdoc(
            Subscribe to contract market data

            Parameters:
                arg0: Contract ID
        )pbdoc")*/
        /*TODO
        .def("unSubscribeMarketData", &MdApi::unSubscribeMarketData, R"pbdoc(
            Unsubscribe from contract market data

            Parameters:
                arg0: Contract ID
        )pbdoc")*/
        .def("reqUserLogin", &MdApi::reqUserLogin, R"pbdoc(
            User login request

            Parameters:
                arg0: CQdFtdcReqUserLoginField
                arg1: Request ID
        )pbdoc")
        .def("reqUserLogout", &MdApi::reqUserLogout, R"pbdoc(
            User logout request

            Parameters:
                arg0: CQdFtdcReqUserLogoutField
                arg1: Request ID
        )pbdoc")

        .def("onFrontConnected", &MdApi::onFrontConnected, "When the client establishes a communication connection with the trading backend (before logging in), this method is called.")
        .def("onFrontDisconnected", &MdApi::onFrontDisconnected, R"pbdoc(
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
        .def("onHeartBeatWarning", &MdApi::onHeartBeatWarning, R"pbdoc(
            Heartbeat timeout warning. When no messages are received for an extended period, this method is called.

            Parameters:
                arg0: Time since last message received
        )pbdoc")
        .def("onRspUserLogin", &MdApi::onRspUserLogin, R"pbdoc(
            User login response

            Parameters:
                arg0: CQdFtdcRspUserLoginField
                arg1: CQdFtdcRspInfoField
                arg2: Request ID
                arg3: Is last
        )pbdoc")
        .def("onRspUserLogout", &MdApi::onRspUserLogout, R"pbdoc(
            User logout response

            Parameters:
                arg0: CQdFtdcRspUserLogoutField
                arg1: CQdFtdcRspInfoField
                arg2: Request ID
                arg3: Is last
        )pbdoc")
        .def("onRspError", &MdApi::onRspError, R"pbdoc(
            Error response

            Parameters:
                arg0: CQdFtdcRspInfoField
                arg1: Request ID
                arg2: Is last
        )pbdoc")
        /*TODO
        .def("onRspSubMarketData", &MdApi::onRspSubMarketData, R"pbdoc(
            Subscription contract details

            Parameters:
                arg0: CQdFtdcSpecificInstrumentField
                arg1: CQdFtdcRspInfoField
                arg2: Request ID
                arg3: Is last
        )pbdoc")*/
        /*TODO
        .def("onRspUnSubMarketData", &MdApi::onRspUnSubMarketData, R"pbdoc(
            Unsubscribe contract details

            Parameters:
                arg0: CQdFtdcSpecificInstrumentField
                arg1: CQdFtdcRspInfoField
                arg2: Request ID
                arg3: Is last
        )pbdoc")*/
        .def("onRtnDepthMarketData", &MdApi::onRtnDepthMarketData, R"pbdoc(
            Depth market notification

            Parameters:
                arg0: CQdFtdcDepthMarketDataField
        )pbdoc")
        ;
}

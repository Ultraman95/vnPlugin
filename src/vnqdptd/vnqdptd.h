#include "../vnqdp.h"
#include "pybind11/pybind11.h"
#include "qdp/QdpFtdcTraderApi.h"

using namespace pybind11;

//����

#define ONFRONTCONNECTED 0
#define ONFRONTDISCONNECTED 1
#define ONHEARTBEATWARNING 2
#define ONRSPUSERLOGIN 4
#define ONRSPUSERLOGOUT 5
#define ONRSPORDERINSERT 11
#define ONRSPORDERACTION 14
#define ONRSPQRYORDER 28
#define ONRSPQRYTRADE 29
#define ONRSPQRYINVESTORPOSITION 30
#define ONRSPQRYINVESTORACCOUNT 31
#define ONRSPERROR 72
#define ONRTNORDER 73
#define ONRTNTRADE 74
#define ONERRRTNORDERINSERT 75
#define ONERRRTNORDERACTION 76
#define ONRTNINSTRUMENTSTATUS 77

///-------------------------------------------------------------------------------------
///C++ SPI�Ļص���������ʵ��
///-------------------------------------------------------------------------------------

//API�ļ̳�ʵ��
class TdApi : public CQdpFtdcTraderSpi
{
private:
    CQdpFtdcTraderApi* api;            //API����
    thread task_thread;                    //�����߳�ָ�루��python���������ݣ�
    TaskQueue task_queue;                //�������?
    bool active = false;                //����״̬

public:
    TdApi()
    {
    };

    ~TdApi()
    {
        if (this->active)
        {
            this->exit();
        }
    };

    //-------------------------------------------------------------------------------------
    //API�ص�����
    //-------------------------------------------------------------------------------------

    ///���ͻ����뽻�׺�̨������ͨ������ʱ����δ��¼ǰ�����÷��������á�
    virtual void OnFrontConnected();

    ///���ͻ����뽻�׺�̨ͨ�����ӶϿ�ʱ���÷��������á���������������API���Զ��������ӣ��ͻ��˿ɲ���������
    ///@param nReason ����ԭ��
    ///        0x1001 �����ʧ��?
    ///        0x1002 ����дʧ��
    ///        0x2001 ����������ʱ
    ///        0x2002 ��������ʧ��
    ///        0x2003 �յ�������
    virtual void OnFrontDisconnected(int nReason);

    ///������ʱ���档����ʱ��δ�յ�����ʱ���÷��������á�
    ///@param nTimeLapse �����ϴν��ձ��ĵ�ʱ��
    virtual void OnHeartBeatWarning(int nTimeLapse);


    ///��¼������Ӧ
    virtual void OnRspUserLogin(CQdpFtdcRspUserLoginField *pRspUserLogin, CQdpFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast);

    ///�ǳ�������Ӧ
    virtual void OnRspUserLogout(CQdpFtdcRspUserLogoutField *pUserLogout, CQdpFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast);

    ///����¼��������Ӧ
    virtual void OnRspOrderInsert(CQdpFtdcInputOrderField *pInputOrder, CQdpFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast);

    ///��������������Ӧ
    virtual void OnRspOrderAction(CQdpFtdcOrderActionField *pInputOrderAction, CQdpFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast);

    ///������?������Ӧ
    virtual void OnRspQryOrder(CQdpFtdcOrderField *pOrder, CQdpFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast);

    ///������?�ɽ���Ӧ
    virtual void OnRspQryTrade(CQdpFtdcTradeField *pTrade, CQdpFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast);
    
    ///Ͷ�����ʽ��˻���ѯӦ��
	virtual void OnRspQryInvestorAccount(CQdpFtdcRspInvestorAccountField *pRspInvestorAccount, CQdpFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast);

    ///������?Ͷ���ֲ߳���Ӧ
    virtual void OnRspQryInvestorPosition(CQdpFtdcRspInvestorPositionField *pInvestorPosition, CQdpFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast);

    ///����Ӧ��
    virtual void OnRspError(CQdpFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast);

    ///����֪ͨ
    virtual void OnRtnOrder(CQdpFtdcOrderField *pOrder);

    ///�ɽ�֪ͨ
    virtual void OnRtnTrade(CQdpFtdcTradeField *pTrade);

    ///����¼�����ر�
    virtual void OnErrRtnOrderInsert(CQdpFtdcInputOrderField *pInputOrder, CQdpFtdcRspInfoField *pRspInfo);

    ///������������ر�?
    virtual void OnErrRtnOrderAction(CQdpFtdcOrderActionField *pOrderAction, CQdpFtdcRspInfoField *pRspInfo);

    ///��Լ����״̬֪ͨ
    virtual void OnRtnInstrumentStatus(CQdpFtdcInstrumentStatusField *pInstrumentStatus);

    //-------------------------------------------------------------------------------------
    //task������
    //-------------------------------------------------------------------------------------
    void processTask();

    void processFrontConnected(Task *task);

    void processFrontDisconnected(Task *task);

    void processHeartBeatWarning(Task *task);

    void processRspUserLogin(Task *task);

    void processRspUserLogout(Task *task);

    void processRspOrderInsert(Task *task);

    void processRspOrderAction(Task *task);

    void processRspQryOrder(Task *task);

    void processRspQryTrade(Task *task);
    
    void processRspQryInvestorAccount(Task *task);

    void processRspQryInvestorPosition(Task *task);

    void processRspError(Task *task);

    void processRtnOrder(Task *task);

    void processRtnTrade(Task *task);

    void processErrRtnOrderInsert(Task *task);

    void processErrRtnOrderAction(Task *task);

    void processRtnInstrumentStatus(Task *task);

    //-------------------------------------------------------------------------------------
    //data���ص������������ֵ�
    //error���ص������Ĵ����ֵ�
    //id������id
    //last���Ƿ�Ϊ��󷵻�?
    //i������
    //-------------------------------------------------------------------------------------
    
    virtual void onFrontConnected() {};

    virtual void onFrontDisconnected(int reqid) {};

    virtual void onHeartBeatWarning(int reqid) {};

    virtual void onRspUserLogin(const dict &data, const dict &error, int reqid, bool last) {};

    virtual void onRspUserLogout(const dict &data, const dict &error, int reqid, bool last) {};

    virtual void onRspOrderInsert(const dict &data, const dict &error, int reqid, bool last) {};

    virtual void onRspOrderAction(const dict &data, const dict &error, int reqid, bool last) {};

    virtual void onRspQryOrder(const dict &data, const dict &error, int reqid, bool last) {};

    virtual void onRspQryTrade(const dict &data, const dict &error, int reqid, bool last) {};

    virtual void onRspQryInvestorAccount(const dict &data, const dict &error, int reqid, bool last) {};

    virtual void onRspQryInvestorPosition(const dict &data, const dict &error, int reqid, bool last) {};

    virtual void onRspError(const dict &error, int reqid, bool last) {};

    virtual void onRtnOrder(const dict &data) {};

    virtual void onRtnTrade(const dict &data) {};

    virtual void onErrRtnOrderInsert(const dict &data, const dict &error) {};

    virtual void onErrRtnOrderAction(const dict &data, const dict &error) {};

    virtual void onRtnInstrumentStatus(const dict &data) {};

    //-------------------------------------------------------------------------------------
    //req:���������������ֵ�
    //-------------------------------------------------------------------------------------

    void createFtdcTraderApi(string pszFlowPath = "");

    void release();

    void init();

    int join();

    int exit();

    string getTradingDay();

    void registerFront(string pszFrontAddress);

    void subscribePrivateTopic(int nType);

    void subscribePublicTopic(int nType);

    int reqUserLogin(const dict &req, int reqid);

    int reqUserLogout(const dict &req, int reqid);

    int reqOrderInsert(const dict &req, int reqid);

    int reqOrderAction(const dict &req, int reqid);

    int reqQryOrder(const dict &req, int reqid);

    int reqQryTrade(const dict &req, int reqid);

    int reqQryInvestorAccount(const dict &req, int reqid);

    int reqQryInvestorPosition(const dict &req, int reqid);
};

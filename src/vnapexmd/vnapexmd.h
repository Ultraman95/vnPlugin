#include "../vnapex.h"
#include "pybind11/pybind11.h"
#include "apex/ApexFtdcMduserApi.h"

using namespace pybind11;

//����
#define ONFRONTCONNECTED 0
#define ONFRONTDISCONNECTED 1
#define ONHEARTBEATWARNING 2
#define ONRSPUSERLOGIN 3
#define ONRSPUSERLOGOUT 4
#define ONRSPERROR 5
#define ONRSPSUBMARKETDATA 6
#define ONRSPUNSUBMARKETDATA 7
#define ONRTNDEPTHMARKETDATA 10


///-------------------------------------------------------------------------------------
///C++ SPI�Ļص���������ʵ��
///-------------------------------------------------------------------------------------

//API�ļ̳�ʵ��
class MdApi : public CApexFtdcMduserSpi
{
private:
    CApexFtdcMduserApi* api;                //API����
    thread task_thread;                    //�����߳�ָ�루��python���������ݣ�
    TaskQueue task_queue;                //�������
    bool active = false;                //����״̬

public:
    MdApi()
    {
    };

    ~MdApi()
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
    virtual void OnFrontConnected() ;

    ///���ͻ����뽻�׺�̨ͨ�����ӶϿ�ʱ���÷��������á���������������API���Զ��������ӣ��ͻ��˿ɲ���������
    ///@param nReason ����ԭ��
    ///        0x1001 �����ʧ��
    ///        0x1002 ����дʧ��
    ///        0x2001 ����������ʱ
    ///        0x2002 ��������ʧ��
    ///        0x2003 �յ�������
    virtual void OnFrontDisconnected(int nReason) ;

    ///������ʱ���档����ʱ��δ�յ�����ʱ���÷��������á�
    ///@param nTimeLapse �����ϴν��ձ��ĵ�ʱ��
    virtual void OnHeartBeatWarning(int nTimeLapse) ;


    ///��¼������Ӧ
    virtual void OnRspUserLogin(CApexFtdcRspUserLoginField *pRspUserLogin, CApexFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast) ;

    ///�ǳ�������Ӧ
    virtual void OnRspUserLogout(CApexFtdcRspUserLogoutField *pUserLogout, CApexFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast) ;

    ///����Ӧ��
    virtual void OnRspError(CApexFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast) ;

    ///��������Ӧ��
    //TODO virtual void OnRspSubMarketData(CQdFtdcSpecificInstrumentField *pSpecificInstrument, CApexFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast) ;

    ///ȡ����������Ӧ��
    //TODO virtual void OnRspUnSubMarketData(CQdFtdcSpecificInstrumentField *pSpecificInstrument, CApexFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast) ;

    ///�������֪ͨ
    virtual void OnRtnDepthMarketData(CApexFtdcDepthMarketDataField *pDepthMarketData) ;

    //-------------------------------------------------------------------------------------
    //task������
    //-------------------------------------------------------------------------------------

    void processTask();

    void processFrontConnected(Task *task);

    void processFrontDisconnected(Task *task);

    void processHeartBeatWarning(Task *task);

    void processRspUserLogin(Task *task);

    void processRspUserLogout(Task *task);

    void processRspError(Task *task);

    //TODO void processRspSubMarketData(Task *task);

    //TODO void processRspUnSubMarketData(Task *task);

    void processRtnDepthMarketData(Task *task);


    //-------------------------------------------------------------------------------------
    //data���ص������������ֵ�
    //error���ص������Ĵ����ֵ�
    //id������id
    //last���Ƿ�Ϊ��󷵻�
    //i������
    //-------------------------------------------------------------------------------------

    virtual void onFrontConnected() {};

    virtual void onFrontDisconnected(int reqid) {};

    virtual void onHeartBeatWarning(int reqid) {};

    virtual void onRspUserLogin(const dict &data, const dict &error, int reqid, bool last) {};

    virtual void onRspUserLogout(const dict &data, const dict &error, int reqid, bool last) {};

    virtual void onRspError(const dict &error, int reqid, bool last) {};

    //TODO virtual void onRspSubMarketData(const dict &data, const dict &error, int reqid, bool last) {};

    //TODO virtual void onRspUnSubMarketData(const dict &data, const dict &error, int reqid, bool last) {};

    virtual void onRtnDepthMarketData(const dict &data) {};

    //-------------------------------------------------------------------------------------
    //req:���������������ֵ�
    //-------------------------------------------------------------------------------------

    void createFtdcMduserApi(string pszFlowPath = "");

    void release();

    void init();

    int join();

    int exit();

    string getTradingDay();

    void registerFront(string pszFrontAddress);

    int subscribeMarketData(string instrumentID);

    int unSubscribeMarketData(string instrumentID);

    int reqUserLogin(const dict &req, int reqid);

    int reqUserLogout(const dict &req, int reqid);
};

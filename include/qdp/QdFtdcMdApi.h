/////////////////////////////////////////////////////////////////////////
///@system QuantDo Platform
///@company �Ϻ���Ͷ����Ƽ����޹�˾
///@file QdFtdcMduserApi.h
///@brief �����˿ͻ��˽ӿ�
///@history 
///20130520	���һ�	�������ļ�
/////////////////////////////////////////////////////////////////////////

#ifndef QD_FTDCMDUSERAPI_H
#define QD_FTDCMDUSERAPI_H

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "QdFtdcUserApiStruct.h"

#if defined(ISLIB) && defined(WIN32)
#ifdef LIB_MDUSER_API_EXPORT
#define MDUSER_API_EXPORT __declspec(dllexport)
#else
#define MDUSER_API_EXPORT __declspec(dllimport)
#endif
#else
#define MDUSER_API_EXPORT 
#endif

class CQdFtdcMduserSpi
{
public:
	///���ͻ����뽻�׺�̨������ͨ������ʱ����δ��¼ǰ�����÷��������á�
	virtual void OnFrontConnected(){};
	
	///���ͻ����뽻�׺�̨ͨ�����ӶϿ�ʱ���÷��������á���������������API���Զ��������ӣ��ͻ��˿ɲ��������
	///@param nReason ����ԭ��
	///        0x1001 �����ʧ��
	///        0x1002 ����дʧ��
	///        0x2001 ����������ʱ
	///        0x2002 ��������ʧ��
	///        0x2003 �յ�������
	virtual void OnFrontDisconnected(int nReason){};
		
	///������ʱ���档����ʱ��δ�յ�����ʱ���÷��������á�
	///@param nTimeLapse �����ϴν��ձ��ĵ�ʱ��
	virtual void OnHeartBeatWarning(int nTimeLapse){};
	
	///���Ļص���ʼ֪ͨ����API�յ�һ�����ĺ����ȵ��ñ�������Ȼ���Ǹ�������Ļص�������Ǳ��Ļص�����֪ͨ��
	///@param nTopicID ������루��˽���������������������ȣ�
	///@param nSequenceNo �������
	virtual void OnPackageStart(int nTopicID, int nSequenceNo){};
	
	///���Ļص�����֪ͨ����API�յ�һ�����ĺ����ȵ��ñ��Ļص���ʼ֪ͨ��Ȼ���Ǹ�������Ļص��������ñ�������
	///@param nTopicID ������루��˽���������������������ȣ�
	///@param nSequenceNo �������
	virtual void OnPackageEnd(int nTopicID, int nSequenceNo){};

	//�����ಥ�����ӿ� add by zbz 20150304
	virtual void  OnMultiHeartbeat(char *CurrTime,char *MultiCastIP) {};

	//�û��ɼ̳д˽ӿڽ����������鲥ԭʼ����
	virtual void OnMutiData(char *data, int len){};
	
	//������������鲥����
	virtual void OnRtnShfeMultiMarketData(CQdFtdcDepthMarketDataField * pMarketData){};

	///����Ӧ��
	virtual void OnRspError(CQdFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast) {};

	///�û���¼Ӧ��
	virtual void OnRspUserLogin(CQdFtdcRspUserLoginField *pRspUserLogin, CQdFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast) {};

	///�û��˳�Ӧ��
	virtual void OnRspUserLogout(CQdFtdcRspUserLogoutField *pRspUserLogout, CQdFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast) {};

	///�������֪ͨ
	virtual void OnRtnDepthMarketData(CQdFtdcDepthMarketDataField *pDepthMarketData) {};

	///qmarket�Լ��鲥���������֪ͨ
	virtual void OnRtnMultiDepthMarketData(CQdFtdcDepthMarketDataField *pDepthMarketData) {};

	///���ĺ�Լ�������Ϣ
	virtual void OnRspSubMarketData(CQdFtdcSpecificInstrumentField *pSpecificInstrument, CQdFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast) {};

	///�˶���Լ�������Ϣ
	virtual void OnRspUnSubMarketData(CQdFtdcSpecificInstrumentField *pSpecificInstrument, CQdFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast) {};

	///�ּ�����
	virtual void OnRtnMBLMarketData(CQdFtdcMBLMarketDataField *pMBLMarketData) {};

	///֣�ݺ�Լ״̬
	virtual void OnRtnQmdInstrumentStatu(CQdFtdcQmdInstrumentStateField *pQmdInstrumentState) {};

	///��������Ӧ��
	virtual void OnRspSubscribeTopic(CQdFtdcDisseminationField *pDissemination, CQdFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast) {};

	///�����ѯӦ��
	virtual void OnRspQryTopic(CQdFtdcDisseminationField *pDissemination, CQdFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast) {};

	///��Լ����Ӧ��
	virtual void OnRspQryMarketData(CQdFtdcRspMarketDataField *pRspMarketData, CQdFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast) {};

	///�г���Լ�б��ѯӦ��
	virtual void OnRspQryInstrumentList(CQdFtdcSpecificInstrumentField *pSpecificInstrument, CQdFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast) {};

	///DCE��Level2�������֪ͨ
	virtual void OnRtnTenEntrust(CQdFtdcMDTenDepthMarketDataField *pMDTenDepthMarketData) {};

	///��Ȩ����֪ͨ
	virtual void OnRtnOptionIndexData(CQdFtdcOptionIndexDataField *pOptionIndexData) {};

	///�鲥����֪ͨ
	virtual void OnRtnShfeMultiLevel(CQdFtdcShfeMultiLevelField *pShfeMultiLevel) {};

	///�鲥����֪ͨ
	virtual void OnRtnShfeMultiParameters(CQdFtdcShfeMultiParametersField *pShfeMultiParameters) {};

	///���������ѯӦ��
	virtual void OnRspQryDepthMarketData(CQdFtdcDepthMarketDataField *pDepthMarketData, CQdFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast) {};
};

class MDUSER_API_EXPORT CQdFtdcMduserApi
{
public:
	///����MduserApi
	///@param pszFlowPath ����������Ϣ�ļ���Ŀ¼��Ĭ��Ϊ��ǰĿ¼
	///@return ��������UserApi
	static CQdFtdcMduserApi *CreateFtdcMduserApi(const char *pszFlowPath = "");
	
	///��ȡϵͳ�汾��
	///@param nMajorVersion ���汾��
	///@param nMinorVersion �Ӱ汾��
	///@return ϵͳ��ʶ�ַ���
	static const char *GetVersion();
	
	///ɾ���ӿڶ�����
	///@remark ����ʹ�ñ��ӿڶ���ʱ,���øú���ɾ���ӿڶ���
	virtual void Release() = 0;
	
	//�ಥ���ÿ���
	virtual void SetMultiCast(bool bMultiCast=false) = 0;
	
	//�Ƿ����û��Լ����������鲥����
	virtual void SetUserFreedom(bool userfree=false) = 0;

	//�����鲥��λ�����Ϣ
	virtual void SetMultiLevel(int level) = 0;

	//ע��ಥ��ַ
	///@param pMultiAddr���ಥ�����ַ��
	///@remark �ಥ�����ַ�ĸ�ʽΪ����topic,multi://����ip@�鲥��ַ:�鲥�˿�#�鲥����Դip����
	///�磺��5000,multi://10.252.3.101@239.4.42.72:25000#192.168.80.72���� 
	///@remark ��5000��������������ţ���multi���������Э�飬��10.252.3.101�������������������
	///@remark ��239.4.42.72:25000�������鲥��ַ�Ͷ˿ںš���192.168.80.72�������鲥���ͷ�����ip��ַ��	
	virtual void RegTopicMultiAddr(char *pMultiAddr)=0;
	
	
	///��ʼ��
	///@remark ��ʼ�����л���,ֻ�е��ú�,�ӿڲſ�ʼ����
	virtual void Init() = 0;
	
	///�ȴ��ӿ��߳̽�������
	///@return �߳��˳�����
	virtual int Join() = 0;
	
	///��ȡ��ǰ������
	///@retrun ��ȡ���Ľ�����
	///@remark ֻ�е�¼�ɹ���,���ܵõ���ȷ�Ľ�����
	virtual const char *GetTradingDay() = 0;
	
	///ע��ǰ�û������ַ
	///@param pszFrontAddress��ǰ�û������ַ��
	///@remark �����ַ�ĸ�ʽΪ����protocol://ipaddress:port�����磺��tcp://127.0.0.1:17001���� 
	///@remark ��tcp���������Э�飬��127.0.0.1�������������ַ����17001������������˿ںš�
	virtual void RegisterFront(char *pszFrontAddress) = 0;
	
	///ע�����ַ����������ַ
	///@param pszNsAddress�����ַ����������ַ��
	///@remark �����ַ�ĸ�ʽΪ����protocol://ipaddress:port�����磺��tcp://127.0.0.1:12001���� 
	///@remark ��tcp���������Э�飬��127.0.0.1�������������ַ����12001������������˿ںš�
	///@remark RegisterFront������RegisterNameServer
	virtual void RegisterNameServer(char *pszNsAddress) = 0;
	
	///ע��ص��ӿ�
	///@param pSpi �����Իص��ӿ����ʵ��
	virtual void RegisterSpi(CQdFtdcMduserSpi *pSpi) = 0;

	///�����г����顣
	///@param nTopicID �г���������  
	///@param nResumeType �г������ش���ʽ  
	///        QD_TERT_RESTART:�ӱ������տ�ʼ�ش�
	///        QD_TERT_RESUME:���ϴ��յ�������(�Ƕ���ȫ����Լʱ����֧������ģʽ)
	///        QD_TERT_QUICK:�ȴ��͵�ǰ�������,�ٴ��͵�¼���г����������
	///@remark �÷���Ҫ��Init����ǰ���á���������򲻻��յ�˽���������ݡ�
	virtual void SubscribeMarketDataTopic(int nTopicID, QD_TE_RESUME_TYPE nResumeType) = 0;

	///���ĺ�Լ���顣
	///@param ppInstrumentID ��ԼID  
	///@param nCount Ҫ����/�˶�����ĺ�Լ����
	///@remark 
	virtual int SubMarketData(char *ppInstrumentID[], int nCount)=0;

	///�˶���Լ���顣
	///@param ppInstrumentID ��ԼID  
	///@param nCount Ҫ����/�˶�����ĺ�Լ����
	///@remark 
	virtual int UnSubMarketData(char *ppInstrumentID[], int nCount)=0;		
	
	///����������ʱʱ�䡣
	///@param timeout ������ʱʱ��(��)  
	virtual void SetHeartbeatTimeout(unsigned int timeout) = 0;

	
	///�����ڴ�ȡֵ
	///@param CQdFtdcShmDepthMarketDataField  �������
	///@param CQdFtdcDepthMarketDataField ��ѯ��������ֵ
	///@return 0 �����ɹ�
	///@return -1 ����־�ļ�ʧ��
	virtual void ShmMarketData(CQdFtdcShmDepthMarketDataField *reqfield,CQdFtdcDepthMarketDataField *defdata) = 0;
	

	///�û���¼����
	virtual int ReqUserLogin(CQdFtdcReqUserLoginField *pReqUserLogin, int nRequestID) = 0;

	///�û��˳�����
	virtual int ReqUserLogout(CQdFtdcReqUserLogoutField *pReqUserLogout, int nRequestID) = 0;

	///���ĺ�Լ�������Ϣ
	virtual int ReqSubMarketData(CQdFtdcSpecificInstrumentField *pSpecificInstrument, int nRequestID) = 0;

	///�˶���Լ�������Ϣ
	virtual int ReqUnSubMarketData(CQdFtdcSpecificInstrumentField *pSpecificInstrument, int nRequestID) = 0;

	///������������
	virtual int ReqSubscribeTopic(CQdFtdcDisseminationField *pDissemination, int nRequestID) = 0;

	///�����ѯ����
	virtual int ReqQryTopic(CQdFtdcDisseminationField *pDissemination, int nRequestID) = 0;

	///��Լ�����ѯ
	virtual int ReqQryMarketData(CQdFtdcQryMarketDataField *pQryMarketData, int nRequestID) = 0;

	///�г���Լ�б��ѯ����
	virtual int ReqQryInstrumentList(CQdFtdcMarketDataExchangeIDField *pMarketDataExchangeID, int nRequestID) = 0;

	///�����鲥��Ϣ��ѯ
	virtual int ReqQrySHFEMultiInfo(CQdFtdcQryShfeMultiInfoField *pQryShfeMultiInfo, int nRequestID) = 0;

	///���������ѯ
	virtual int ReqQryDepthMarketData(CQdFtdcQryMarketDataField *pQryMarketData, int nRequestID) = 0;

	//����ಥ
	//���޷���¼qmarket������������£����ô˽ӿڿ��Խ����鲥����
	//�ڿ��Ե�¼�������������ô˽ӿ�
	//@param TradingDay �����գ���û�е�¼������£���������Ȼ�գ�����Ҫע�⽻�����Ľ�����
	virtual void ActiveMultiMarketData(char * TradingDay) = 0;
protected:
	~CQdFtdcMduserApi(){};
};

#endif

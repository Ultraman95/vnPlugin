/////////////////////////////////////////////////////////////////////////
///@system QuantDo Trade Engine
///@company Shanghai Quantdo Network Technology Co., Ltd.
///@file ApexFtdcMduserApi.h
///@brief Defines Client Side Interface
///@history
///20161212	Xu Zhonghua		Creation
/////////////////////////////////////////////////////////////////////////

#ifndef APEX_FTDCMDUSERAPI_H
#define APEX_FTDCMDUSERAPI_H

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "ApexFtdcUserApiStruct.h"

#if defined(ISLIB) && defined(WIN32)
#ifdef LIB_MDUSER_API_EXPORT
#define MDUSER_API_EXPORT __declspec(dllexport)
#else
#define MDUSER_API_EXPORT __declspec(dllimport)
#endif
#else
#define MDUSER_API_EXPORT 
#endif

class CApexFtdcMduserSpi
{
public:
	///Invoked when connection is established between client and server (which is before login)
	virtual void OnFrontConnected(){};
	
	///Invoked on disconnected. API automatically tries to reconnect when it happens. No special handling required on client side
	///@param nReason Reason of error
	///        0x1001 Network Read Failure
	///        0x1002 Network Write Failure
	///        0x2001 Heartbeat Answer Timeout
	///        0x2002 Failed Sending Heartbeat
	///        0x2003 Incorrect Response Received
	virtual void OnFrontDisconnected(int nReason){};
		
	///Heartbeat Timeout Warning. Invoked when response is not received in a long time.
	///@param nTimeLapse: Timespan(in seconds) after last response is received
	virtual void OnHeartBeatWarning(int nTimeLapse){};
	
	///Invoked on Return Package Starts. This is the first function invoked when a return is received. Followed by callbacks of various data fields. Ends with "OnPackageEnd"
	///@param nTopicID: Topic ID (e.g. Private Stream, Public Stream or Market Data Stream)
	///@param nSequenceNo: Sequence Number
	virtual void OnPackageStart(int nTopicID, int nSequenceNo){};
	
	///Invoked on Return Package Ends. When a return is received. "OnPackageStart" is invoked first. Followed by callbacks of various data fields. Finally this function.
	///@param nTopicID: Topic ID (e.g. Private Stream, Public Stream or Market Data Stream)
	///@param nSequenceNo: Sequence Number
	virtual void OnPackageEnd(int nTopicID, int nSequenceNo){};


	///Error Response
	virtual void OnRspError(CApexFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast) {};

	///User Login Response
	virtual void OnRspUserLogin(CApexFtdcRspUserLoginField *pRspUserLogin, CApexFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast) {};

	///User Logout Response
	virtual void OnRspUserLogout(CApexFtdcRspUserLogoutField *pRspUserLogout, CApexFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast) {};

	///Topic Subscription Response
	virtual void OnRspSubscribeTopic(CApexFtdcDisseminationField *pDissemination, CApexFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast) {};

	///Instrument Query Response
	virtual void OnRspQryInstrument(CApexFtdcRspInstrumentField *pRspInstrument, CApexFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast) {};

	///Instrument Status Query Response
	virtual void OnRspQryInstrumentStatus(CApexFtdcInstrumentStatusField *pInstrumentStatus, CApexFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast) {};

	///Bulletin Query Response
	virtual void OnRspQryBulletin(CApexFtdcBulletinField *pBulletin, CApexFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast) {};

	///Topic Query Response
	virtual void OnRspQryTopic(CApexFtdcDisseminationField *pDissemination, CApexFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast) {};

	///CombInstrument Query Response
	virtual void OnRspQryCombinationLeg(CApexFtdcRspCombinationLegField *pRspCombinationLeg, CApexFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast) {};

	///Instrument Status Return Object
	virtual void OnRtnInstrumentStatus(CApexFtdcInstrumentStatusField *pInstrumentStatus) {};

	///Bulletin Return Object
	virtual void OnRtnBulletin(CApexFtdcBulletinField *pBulletin) {};

	///Full Market Data Return Object
	virtual void OnRtnDepthMarketData(CApexFtdcDepthMarketDataField *pDepthMarketData) {};

	///MultiCast Heartbeat
	virtual void OnRtnMultiHeartbeat(CApexFtdcMultiHeartbeatField *pMultiHeartbeat) {};
};

class MDUSER_API_EXPORT CApexFtdcMduserApi
{
public:
	///Create MduserApi
	///@param pszFlowPath: Directory to store subscription file. Default to current direction
	///@return API Instance created
	static CApexFtdcMduserApi *CreateFtdcMduserApi(const char *pszFlowPath = "");
	
	///Obtain System Version
	///@param nMajorVersion
	///@param nMinorVersion
	///@return System Identification String
	static const char *GetVersion();
	
	///Release API instance
	///@remark Use this function to release API instance after usage
	virtual void Release() = 0;
	
	//Switch for Multicast
	//@remark Call SetMultiCast(true) before RegTopicMultiAddr if want to use MultiCast
	virtual void SetMultiCast(bool bMultiCast=false) = 0;

	//Regiester Multicast Addresses
	///@param pMultiAddr MultiNetwork address of Market front
	///@remark Format of address being: "topic,multi://subnet@multiAddr:port", for e.g. "100,multi://192.168.92@224.0.23.22:17001"
	///@remark Call SetMultiCast(true) before RegTopicMultiAddr if want to use MultiCast
	virtual void RegTopicMultiAddr(char *pMultiAddr)=0;
	
	
	///Initialization Function
	///@remark Launch an API thread to connect to server, API starts working upon invokation of this function
	virtual void Init() = 0;
	
	///Join Current Thread to API Thread
	///@return Thread exit code
	virtual int Join() = 0;
	
	///Obtain System Trading Day
	///@retrun: Trading day obtained
	///@remark Only works after login
	virtual const char *GetTradingDay() = 0;
	
	///Register Front-End
	///@param pszFrontAddress Network address of trading front
	///@remark Format of address being: "protocol://ipaddress:port", for e.g. "tcp://127.0.0.1:17001" 
	///@remark "tcp" represents transportation protocal, "127.0.0.1" represents server address, "17001" represents port number
	virtual void RegisterFront(char *pszFrontAddress) = 0;
	
	//Register Front-End against Nameserver
	///@param pszNsAddress Network address of nameserver
	///@remark Format of address being: "protocol://ipaddress:port", for e.g. "tcp://ns1.example.com:17001" 
	///@remark "tcp" represents transportation protocal, "ns1.example.com" represents server address, "17001" represents port number
	///@remark RegisterFront has priority over RegisterNameServer
	virtual void RegisterNameServer(char *pszNsAddress) = 0;
	
	///Register Service Provider Interface
	///@param pSpi: Pointer against an instance inherited from SPI
	virtual void RegisterSpi(CApexFtdcMduserSpi *pSpi) = 0;
	
	///Register Certificate
	///@param pszCertFileName: Certificate filename
	///@param pszKeyFileName: User private key filename
	///@param pszCaFileName: Trusted CA Certificate filename
	///@param pszKeyFilePassword: User private key file password
	///@return 0 Success
	///@return -1 Failed loading trusted CA certificate file
	///@return -2 Failed loading user certificate
	///@return -3 Failed loading user private key file
	///@return -4 User certificate authentication failure
	virtual int RegisterCertificateFile(const char *pszCertFileName, const char *pszKeyFileName, 
		const char *pszCaFileName, const char *pszKeyFilePassword) = 0;

	///Subscribe Market Data Topic
	///@param nTopicID: Market Data Topic  
	///@param nResumeType: Resending Type  
	///        APEX_TERT_RESTART: Resend from beginning of day
	///        APEX_TERT_RESUME: Resend from last received mesage
	///        APEX_TERT_QUICK: Don't Resend
	///@remark This function has to be invoked before "Init" function if you wish to receive messages from market data topic
	virtual void SubscribeMarketDataTopic(int nTopicID, APEX_TE_RESUME_TYPE nResumeType) = 0;

	///Subscribe Public Topic
	///@param nResumeType: Topic resending type   
	///        APEX_TERT_RESTART: Resend from beginning of day
	///        APEX_TERT_RESUME: Resend from last received mesage
	///        APEX_TERT_QUICK: Don't resend
	///@remark This function has to be invoked before "Init" function if you wish to receive messages from public topic
	virtual void SubscribePublicTopic(APEX_TE_RESUME_TYPE nResumeType) = 0;

	///Set Heartbeat Timeout
	///@param timeout: Heartbeat timeout (Second)  
	virtual void SetHeartbeatTimeout(unsigned int timeout) = 0;


	///User Login Request
	virtual int ReqUserLogin(CApexFtdcReqUserLoginField *pReqUserLogin, int nRequestID) = 0;

	///User Logout Request
	virtual int ReqUserLogout(CApexFtdcReqUserLogoutField *pReqUserLogout, int nRequestID) = 0;

	///Topic Subscription Request
	virtual int ReqSubscribeTopic(CApexFtdcDisseminationField *pDissemination, int nRequestID) = 0;

	///Instrument Query Request
	virtual int ReqQryInstrument(CApexFtdcQryInstrumentField *pQryInstrument, int nRequestID) = 0;

	///Instrument Status Query Request
	virtual int ReqQryInstrumentStatus(CApexFtdcQryInstrumentStatusField *pQryInstrumentStatus, int nRequestID) = 0;

	///Bulletin Query Request
	virtual int ReqQryBulletin(CApexFtdcQryBulletinField *pQryBulletin, int nRequestID) = 0;

	///Topic Query Request
	virtual int ReqQryTopic(CApexFtdcDisseminationField *pDissemination, int nRequestID) = 0;

	///CombInstrument Query Request
	virtual int ReqQryCombinationLeg(CApexFtdcQryCombinationLegField *pQryCombinationLeg, int nRequestID) = 0;
protected:
	~CApexFtdcMduserApi(){};
};

#endif

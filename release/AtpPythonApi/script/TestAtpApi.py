import os
import sys
import time

from vnatpmd import MdApi
from vnatptd import TdApi

##Pythn AtpMdApi 行情Api###################################################################
class AtpMdApi(MdApi):
    def __init__(self)->None:
        super().__init__()
        self.reqid: int = 0
        self.connect_status:bool = False
        self.login_status:bool = False
        self.subscribed: set = set()

        self.userid: str = ""
        self.password: str = ""
        self.brokerid: str = ""

    
    def connect(self, address: str, userid: str, password: str, brokerid: str)->None:
        self.userid = userid
        self.password = password
        self.brokerid = brokerid
        if not self.connect_status:
            path = os.path.dirname(os.path.abspath(__file__))
            print(path)
            self.createFtdcMdApi((str(path) + "\\Md").encode("GBK"))
            self.registerFront(address)
            self.init()
            self.connect_status = True


    def login(self) -> None:
        atp_req:dict = {
            "UserProductInfo": "TestATP",
            "UserID": self.userid,
            "Password": self.password,
            "BrokerID": self.brokerid
        }
        self.reqid += 1
        self.reqUserLogin(atp_req,self.reqid)

    
    def subscribe(self,instrumentID:str):
        if self.login_status:
            self.subscribeMarketData(instrumentID)
        self.subscribed.add(instrumentID)

    
    def close(self)->None:
        if self.connect_status:
            self.exit()

    
    def onFrontConnected(self)->None:
        print("MdApi Connected, Start Login")
        self.login()

    
    def onFrontDisconnected(self,reason:int)->None:
        print("MdApi Disconnected")
        self.login_status = False

    
    def onRspUserLogin(self,data:dict,error:dict,reqid:int,last:bool)->None:
        ##data对应CThostFtdcRspUserLoginField，error对应CThostFtdcRspInfoField
        print("MdApi RspUserLogin")
        if not error['ErrorID']:
            self.login_status = True
            for symbol in self.subscribed:
                print("InstrumentID Subscribe:",symbol)
                self.subscribeMarketData(symbol)
        else:
            print(f"行情服务器登录失败。{error['ErrorID']}.{error['ErrorMsg']}")

    
    def onRspError(self, error: dict, reqid: int, last: bool)->None:
        ##error对应CThostFtdcRspInfoField
        print('行情接口报错。',error['ErrorID'],error['ErrorMsg'])
    
    
    def onRspSubMarketData(self, data: dict, error: dict, reqid: int, last: bool)->None:
        ##data对应CThostFtdcSpecificInstrumentField，error对应CThostFtdcRspInfoField
        if not error or not error['ErrorID']:
            return
        print('行情订阅失败。',error['ErrorID'],error['ErrorMsg'])
    

    def onRtnDepthMarketData(self,data:dict)->None:
        ##data对应CThostFtdcDepthMarketDataField
        if not data['UpdateTime']:
            return
        print('tick返回:InstrumentID[',data['InstrumentID'],'],','LastPrice=',data['LastPrice'])



##Pythn AtpTdApi 交易Api###################################################################
class AtpTdApi(TdApi):
    def __init__(self)->None:
        super().__init__()

        self.reqid: int = 0
        self.order_ref: int = 0

        self.connect_status: bool = False
        self.login_status: bool = False
        self.login_failed: bool = False
        self.contract_inited: bool = False

        self.userid: str = ""
        self.password: str = ""
        self.brokerid: str = ""
        self.auth_code: str = ""
        self.appid: str = ""

        self.frontid: int = 0
        self.sessionid: int = 0


    def connect(self,address:str,userid:str,password:str,brokerid:str)->None:
        self.userid = userid
        self.password = password
        self.brokerid = brokerid
        if not self.connect_status:
            path = os.path.dirname(os.path.abspath(__file__))
            print(path)
            self.createFtdcTraderApi((str(path) + "\\Td").encode("GBK"))
            self.subscribePrivateTopic(0)
            self.subscribePublicTopic(0)
            self.registerFront(address)
            self.init()
            self.connect_status = True
    
    
    def login(self)->None:
        if self.login_failed:
            return
        atp_req: dict = {
            "UserID": self.userid,
            "Password": self.password,
            "BrokerID": self.brokerid,
            "AppID": self.appid
        }

        self.reqid += 1
        self.reqUserLogin(atp_req, self.reqid)


    def close(self)->None:
        if self.connect_status:
            self.exit()


    def orderInsert(self)->None:
        if self.login_failed:
            return
        print('执行OrderInsert')
        ##其中的OrderRef自己定义，撤单的时候OrderRef要对应起来
        atp_req: dict = {
            "BrokerID": self.brokerid,
            "InvestorID": self.userid,
            "UserID": self.userid,
            "OrderPriceType":"2",
            "CombHedgeFlag":"1",
            "TimeCondition":"3",
            "VolumeCondition":"1",
            "CombOffsetFlag":"0",
            "InstrumentID":"HC2411-SH",
            "Direction":"0",
            "LimitPrice":3745.0,
            "VolumeTotalOriginal":7,
            "OrderRef":"0009",
            "MinVolume":0,
            "ContingentCondition":"1",
            "StopPrice":0.0,
            "ForceCloseReason":"0",
            "IsAutoSuspend":0,
            "UserForceClose":0,
            "IsSwapOrder":0,
            "BusinessUnit":"customized-data",
            "GTDDate":""
        }
        self.reqid += 1
        self.reqOrderInsert(atp_req, self.reqid)  


    def orderCancel(self)->None:
        if self.login_failed:
            return
        print('执行OrderCancel')
        atp_req: dict = {
            "BrokerID": self.brokerid,
            "InvestorID": self.userid,
            "UserID": self.userid,
            "ActionFlag": "0",
            "OrderRef":"0010",
            "FrontID": self.frontid,
            "SessionID": self.sessionid
        }
        self.reqid += 1
        self.reqOrderAction(atp_req, self.reqid) 
        

    def qryInvestorPosition(self)->None:
        if self.login_failed:
            return
        print('执行QryInvestorPosition')
        atp_req: dict = {
            "BrokerID": self.brokerid,
            "InvestorID": self.userid
        }
        self.reqid += 1
        self.reqQryInvestorPosition(atp_req, self.reqid)


    def qryTradingAccount(self)->None:
        if self.login_failed:
            return
        print('qryTradingAccount')
        atp_req: dict = {
            "BrokerID": self.brokerid,
            "InvestorID": self.userid
        }
        self.reqid += 1
        self.reqQryTradingAccount(atp_req, self.reqid)



    def onFrontConnected(self)->None:
        print('TdApi Connecte, Start Login')
        if self.auth_code:
            self.authenticate()
        else:
            self.login()
    
    
    def onFrontDisconnected(self,reason:int)->None:
        self.login_status = False
        print('onFrontDisconnected',reason)


    def onRspUserLogin(self, data: dict, error: dict, reqid: int, last: bool) -> None:
        ##data对应CThostFtdcRspUserLoginField, error对应CThostFtdcRspInfoField
        print('onRspUserLogin')
        if not error["ErrorID"]:
            self.frontid = data["FrontID"]
            self.sessionid = data["SessionID"]
            self.login_status = True

            print('开始合约信息查询')
            while True:
                self.reqid += 1
                n: int = self.reqQryInstrument({}, self.reqid)
                if not n:
                    break
                else:
                    time.sleep(1)
        else:
            self.login_failed = True
            print("交易服务器登录失败", error['ErrorID'],error['ErrorMsg'])
    

    def onRspQryInstrument(self, data: dict, error: dict, reqid: int, last: bool) -> None:
        ##data对应CThostFtdcInstrumentField, error对应CThostFtdcRspInfoField
        print(data['ProductClass'],data['InstrumentID'],data['ProductID'],reqid,last)
        if last:
            self.contract_inited = True
            print('合约信息查询完毕')


    def onRspOrderInsert(self, data: dict, error: dict, reqid: int, last: bool) -> None:
        print('onRspOrderInsert')


    def OnRspOrderAction(self, data: dict, error: dict, reqid: int, last: bool)-> None:
        print('OnRspOrderAction')


    def onRspError(self, error: dict, reqid: int, last: bool)->None:
        ##error对应CThostFtdcRspInfoField结构
        print('交易接口报错。',error['ErrorID'],error['ErrorMsg'])


    def OnErrRtnOrderAction(self, data: dict, error: dict)->None:
        print('交易接口报错。',error['ErrorID'],error['ErrorMsg'])

    
    def onRtnOrder(self, data: dict)->None:
        ##data对应CThostFtdcOrderField结构
        print('##onRtnOrder##')
        self.frontid = data['FrontID']
        self.sessionid = data['SessionID']
        for i,j in data.items():
            print(i,j)
        print('######end#####')

    
    def onRtnTrade(self, data: dict)->None:
        ##data对应CThostFtdcTradeField结构
        print('##onRtnTrade##')
        for i,j in data.items():
            print(i,j)
        print('######end#####')


    def onRspQryInvestorPosition(self, data: dict, error: dict, reqid: int, last: bool)->None:
        ##data对应CThostFtdcInvestorPositionField结构, error对应CThostFtdcRspInfoField
        print('##onRspQryInvestorPosition##')
        for i,j in data.items():
            print(i,j)
        print('######end#####')


    def onRspQryTradingAccount(self, data: dict, error: dict, reqid: int, last: bool)->None:
        ##data对应CThostFtdcTradingAccountField结构, error对应CThostFtdcRspInfoField
        print('##onRspQryTradingAccount##')
        for i,j in data.items():
            print(i,j)
        print('######end#####')



if __name__ == '__main__':
    ##填写自己账号信息
    investorid = ""
    brokerid=""
    password= ""
    md_ip= "tcp://demo9.atplatform.cn:41213"
    trader_ip= "tcp://demo9.atplatform.cn:40905"

    
    ##行情Api，连接成功后会根据用户信息自动登录，通过订阅具体的InstrumentID获取相应的行情信息，关于合约信息可以通过交易接口查询
    ''' 
    temp_MdApi = AtpMdApi()
    temp_MdApi.connect(md_ip,investorid,password,brokerid)
    ##temp_MdApi.subscribe("CU2406-SH")
    temp_MdApi.subscribe("HC2411-SH")
    '''

    ##交易Api
    temp_TdApi = AtpTdApi()
    temp_TdApi.connect(trader_ip,investorid,password,brokerid)

    #time.sleep(8)
    ##下单
    ##Atp下单成功，OnRtnOrder会被回调，onRspOrderInsert不会被回调，如果有成交OnRtnTrade会被回调
    ##temp_TdApi.orderInsert()


    #time.sleep(8)
    ##撤单
    ##temp_TdApi.orderCancel()

    ##time.sleep(8)
    ##查询持仓
    ##temp_TdApi.qryInvestorPosition()

    time.sleep(8)
    ##查询资金
    temp_TdApi.qryTradingAccount()


    input()
    #sys.exit()


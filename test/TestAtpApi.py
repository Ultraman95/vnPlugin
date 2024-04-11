import os
import sys

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
        print("MdApi RspUserLogin")
        if not error['ErrorID']:
            self.login_status = True
            for symbol in self.subscribed:
                print("InstrumentID Subscribe:",symbol)
                self.subscribeMarketData(symbol)
        else:
            print(f"行情服务器登录失败。{error['ErrorID']}.{error['ErrorMsg']}")

    
    def onRspError(self, error: dict, reqid: int, last: bool)->None:
        print('行情接口报错。',error['ErrorID'],error['ErrorMsg'])
    
    
    def onRspSubMarketData(self, data: dict, error: dict, reqid: int, last: bool)->None:
        if not error or not error['ErrorID']:
            return
        print('行情订阅失败。',error['ErrorID'],error['ErrorMsg'])
    

    def onRtnDepthMarketData(self,data:dict)->None:
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
        self.auth_status: bool = False
        self.login_failed: bool = False
        self.auth_failed: bool = False
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
        else:
            self.authenticate()
        

    def authenticate(self)->None:
        if self.auth_failed:
            return
        ctp_req: dict = {
            "UserID": self.userid,
            "BrokerID": self.brokerid,
            "AuthCode": self.auth_code,
            "AppID": self.appid
        }

        self.reqid += 1
        self.reqAuthenticate(ctp_req, self.reqid)
    
    
    def login(self)->None:
        if self.login_failed:
            return
        ctp_req: dict = {
            "UserID": self.userid,
            "Password": self.password,
            "BrokerID": self.brokerid,
            "AppID": self.appid
        }

        self.reqid += 1
        self.reqUserLogin(ctp_req, self.reqid)
        

    def close(self)->None:
        if self.connect_status:
            self.exit()


    def onFrontConnected(self)->None:
        print('TdApi Connecte, Start Login')
        if self.auth_code:
            self.authenticate()
        else:
            self.login()
    
    
    def onFrontDisconnected(self,reason:int)->None:
        self.login_status = False
        print('onFrontDisconnected',reason)
    
    
    def onRspAuthenticate(self, data: dict, error: dict, reqid: int, last: bool)->None:
        print('onRspAuthenticate')
        if not error['ErrorID']:
            self.auth_status = True
            self.login()
        else:
            self.auth_failed = True
            print('交易服务器验证失败。',error['ErrorID'],error['ErrorMsg'])


    def onRspUserLogin(self, data: dict, error: dict, reqid: int, last: bool) -> None:
        print('onRspUserLogin')
        if not error["ErrorID"]:
            self.frontid = data["FrontID"]
            self.sessionid = data["SessionID"]
            self.login_status = True

            # 自动确认结算单
            ctp_req: dict = {
                "BrokerID": self.brokerid,
                "InvestorID": self.userid
            }
            self.reqid += 1
            self.reqSettlementInfoConfirm(ctp_req, self.reqid)
        else:
            self.login_failed = True
            print("交易服务器登录失败", error['ErrorID'],error['ErrorMsg'])


    def onRspSettlementInfoConfirm(self, data: dict, error: dict, reqid: int, last: bool) -> None:
        print('onRspSettlementInfoConfirm')
        print('开始合约信息查询')
        while True:
            self.reqid += 1
            n: int = self.reqQryInstrument({}, self.reqid)
            if not n:
                break
            else:
                time.sleep(1)
    

    def onRspQryInstrument(self, data: dict, error: dict, reqid: int, last: bool) -> None:
        print(data['ProductClass'],data['InstrumentID'],data['ProductID'],reqid,last)
        if last:
            self.contract_inited = True
            print('合约信息查询完毕')
    



if __name__ == '__main__':
    investorid = "sfuser10"
    brokerid="SF010"
    password= "!6AW)7zA"
    md_ip= "tcp://demo9.atplatform.cn:41213"
    trader_ip= "tcp://demo9.atplatform.cn:40905"

    
    ##行情Api，连接成功后会根据用户信息自动登录，通过订阅具体的InstrumentID获取相应的行情信息，关于合约信息可以通过交易接口查询
    '''
    temp_MdApi = AtpMdApi()
    temp_MdApi.connect(md_ip,investorid,password,brokerid)
    temp_MdApi.subscribe("CU2406-SH")
    temp_MdApi.subscribe("ZC2406-ZC")
    '''

    ##交易Api
    temp_TdApi = AtpTdApi()
    temp_TdApi.connect(trader_ip,investorid,password,brokerid)


    input()
    #sys.exit()


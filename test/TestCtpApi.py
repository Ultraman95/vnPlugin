import os
import sys

from vnctpmd import MdApi
from vnctptd import TdApi

##Pythn CtpMdApi###################################################################
class CtpMdApi(MdApi):
    def __init__(self)->None:
        super().__init__()

        self.reqid: int = 0
        self.connect_status:bool = False
        self.login_status:bool = False
        self.subscribed: set = set()

        self.userid: str = ""
        self.password: str = ""
        self.brokerid: str = ""
        pass
    def connect(self, address: str, userid: str, password: str, brokerid: str)->None:
        self.userid = userid
        self.password = password
        self.brokerid = brokerid

        if not self.connect_status:
            path = os.path.dirname(os.path.abspath(__file__))
            print(path)
            # path: Path = get_folder_path(self.gateway_name.lower())
            self.createFtdcMdApi((str(path) + "\\Md").encode("GBK"))
            # self.createFtdcMdApi((str("") + "\\Md").encode("GBK"))
            self.registerFront(address)
            self.init()

            self.connect_status = True
            pass

    def login(self) -> None:
        ctp_req:dict = {
            "UserProductInfo": "TestCTP",
            "UserID": self.userid,
            "Password": self.password,
            "BrokerID": self.brokerid
        }

        self.reqid += 1
        self.reqUserLogin(ctp_req,self.reqid)
        pass

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
        print("MdApi Login Ok")
        pass
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
        pass
    def onRspError(self, error: dict, reqid: int, last: bool)->None:
        print('行情接口报错。',error['ErrorID'],error['ErrorMsg'])
        pass
    def onRspSubMarketData(self, data: dict, error: dict, reqid: int, last: bool)->None:
        if not error or not error['ErrorID']:
            return
        print('行情订阅失败。',error['ErrorID'],error['ErrorMsg'])
    def onRtnDepthMarketData(self,data:dict)->None:
        if not data['UpdateTime']:
            return
        print('tick返回',data['InstrumentID'],data['LastPrice'])
        pass



##Pythn CtpTdApi###################################################################
class CtpTdApi(TdApi):
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
        pass
    def connect(self,address:str,userid:str,password:str,brokerid:str,auth_code:str,appid:str)->None:
        self.userid = userid
        self.password = password
        self.brokerid = brokerid
        self.auth_code = auth_code
        self.appid = appid

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
        pass
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
        pass
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
        pass
    def orderInsert(self)->None:
        if self.login_failed:
            return
        ctp_req: dict = {

        }
        self.reqid += 1
        self.reqOrderInsert(ctp_req, self.reqid)


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
        pass

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
        pass

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
        pass

    def onRspQryInstrument(self, data: dict, error: dict, reqid: int, last: bool) -> None:
        print(data['ProductClass'],data['InstrumentID'],data['ProductID'],reqid,last)
        if last:
            self.contract_inited = True
            print('合约信息查询完毕')
        pass
    pass



if __name__ == '__main__':
    investorid = "047934"
    brokerid="9999"
    password= "7228802sH@"
    appid= "simnow_client_test"
    auth_code= "0000000000000000"
    md_ip= "tcp://180.168.146.187:10211"
    trader_ip= "tcp://180.168.146.187:10201"

    '''temp_MdApi = CtpMdApi()
    temp_MdApi.connect(md_ip,investorid,password,brokerid)
    temp_MdApi.subscribe("IF2404")
    temp_MdApi.subscribe("IF2405")'''


    temp_TdApi = CtpTdApi()
    temp_TdApi.connect(trader_ip,investorid,password,brokerid,auth_code,appid)

    input()
    pass

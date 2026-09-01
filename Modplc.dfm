object Mod_PLC: TMod_PLC
  OldCreateOrder = False
  Height = 194
  Width = 498
  object Timer_Read: TTimer
    Interval = 500
    Left = 56
    Top = 72
  end
  object ClientSocket_PC: TClientSocket
    Active = False
    ClientType = ctNonBlocking
    Port = 0
    OnConnect = ClientSocket_PCConnect
    OnDisconnect = ClientSocket_PCDisconnect
    OnRead = ClientSocket_PCRead
    OnError = ClientSocket_PCError
    Left = 144
    Top = 32
  end
  object Timer_PC_AutoConnect: TTimer
    Enabled = False
    Interval = 100
    OnTimer = Timer_PC_AutoConnectTimer
    Left = 248
    Top = 32
  end
  object Timer_PC_WriteMsg: TTimer
    Enabled = False
    Interval = 300
    OnTimer = Timer_PC_WriteMsgTimer
    Left = 368
    Top = 32
  end
  object ClientSocket_PLC: TClientSocket
    Active = False
    ClientType = ctNonBlocking
    Port = 0
    OnConnect = ClientSocket_PLCConnect
    OnDisconnect = ClientSocket_PLCDisconnect
    OnRead = ClientSocket_PLCRead
    OnError = ClientSocket_PLCError
    Left = 144
    Top = 104
  end
  object Timer_PLC_AutoConnect: TTimer
    Enabled = False
    Interval = 100
    OnTimer = Timer_PLC_AutoConnectTimer
    Left = 248
    Top = 104
  end
  object Timer_PLC_WriteMsg: TTimer
    Enabled = False
    Interval = 200
    OnTimer = Timer_PLC_WriteMsgTimer
    Left = 368
    Top = 104
  end
end

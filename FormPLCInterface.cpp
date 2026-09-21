#pragma link "AdvSmoothButton"
//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "RVMO_main.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
TForm_PLCInterface *Form_PLCInterface;
//---------------------------------------------------------------------------
namespace
{
	const int PLC_MONITOR_CLIENT_WIDTH = 1082;
	const int PLC_TEST_CLIENT_WIDTH = 1506;

	int ParseDeviceAddress(AnsiString text)
	{
		text = text.Trim().UpperCase();
		if(text.Length() > 0 && text[1] == 'D')
			text = text.SubString(2, text.Length() - 1);

		AnsiString number = "";
		for(int i = 1; i <= text.Length(); i++)
		{
			if(text[i] >= '0' && text[i] <= '9')
				number += text[i];
			else if(number.Length() > 0)
				break;
		}

		return number.ToIntDef(-1);
	}
}
//---------------------------------------------------------------------------
__fastcall TForm_PLCInterface::TForm_PLCInterface(TComponent* Owner)
	: TForm(Owner)
{
	SetListViewPLC();
	SetListViewPC();

	heart_bit_plc = 0;
	heart_bit_pc = 0;

	heart_bit_plc_old = 0;
	heart_bit_pc_old = 0;

	heart_bit_plc_count = 0;
	heart_bit_pc_count = 0;

	for(int nIndex = 0; nIndex < 1; nIndex++){
		auto_manual_plc[nIndex] = 0;
		auto_manual_plc_old[nIndex] = 0;
	}
}
//---------------------------------------------------------------------------
void __fastcall TForm_PLCInterface::SetListViewPLC()
{
	ListView_PLC->Items->Clear();
	const int channelStep = GetDisplayChannelStep();
	// PLC - IR/OCV
	AddListView(ListView_PLC, "D" + IntToStr(PLC_D_INTERFACE_START_DEV_NUM + PLC_D_HEART_BEAT), "PLC HEART BEAT");
	AddListView(ListView_PLC, "D" + IntToStr(PLC_D_INTERFACE_START_DEV_NUM + PLC_D_IROCV_AUTO_MANUAL), "PLC AUTO MANUAL");
	AddListView(ListView_PLC, "D" + IntToStr(PLC_D_INTERFACE_START_DEV_NUM + PLC_D_IROCV_ERROR), "PLC ERROR");

	AddListView(ListView_PLC, "D" + IntToStr(PLC_D_INTERFACE_START_DEV_NUM + PLC_D_IROCV_TRAY_IN), "TRAY IN");
	AddListView(ListView_PLC, "D" + IntToStr(PLC_D_INTERFACE_START_DEV_NUM + PLC_D_IROCV_PROB_OPEN), "PROB OPEN");
	AddListView(ListView_PLC, "D" + IntToStr(PLC_D_INTERFACE_START_DEV_NUM + PLC_D_IROCV_PROB_CLOSE), "PROB CLOSE");
    AddListView(ListView_PLC, "D" + IntToStr(PLC_D_INTERFACE_START_DEV_NUM + PLC_D_IROCV_COMPLETE), "READ COMPLETE");
	AddListView(ListView_PLC, "D" + IntToStr(PLC_D_INTERFACE_START_DEV_NUM + PLC_D_IROCV_TRAY_ID), "TRAY ID");

	// CELL INFO => 1 : YES, 0 : NO
	for(int i = 0; i < 25; i++)
	{
		AddListView(ListView_PLC, "D" + IntToStr(PLC_D_INTERFACE_START_DEV_NUM + PLC_D_IROCV_TRAY_CELL_DATA + i), "TRAY CELL DATA #" + IntToStr(i + 1));
	}

    //* CELL SERIAL DATA
    AddListView(ListView_PLC, "D" + IntToStr(PLC_D_CELL_SERIAL_NUM + PLC_D_IROCV_CELL_SERIAL_TRAYID), "CELL SERIAL TRAY ID");

    // 시리얼은 채널당 10워드. 요약/전체 모드 모두 실제 채널의 주소를 표시한다.
    for(int channel = 0; channel < MAXCHANNEL; channel += channelStep)
       AddListView(ListView_PLC, "D" + IntToStr(PLC_D_CELL_SERIAL_NUM + PLC_D_IROCV_CELL_SERIAL + channel * PLC_D_CELL_SERIAL_WORDS_PER_CHANNEL), "CELL SERIAL #" + IntToStr(channel + 1));
}
//---------------------------------------------------------------------------
void __fastcall TForm_PLCInterface::SetListViewPC()
{
	ListView_PC->Items->Clear();
	const int channelStep = GetDisplayChannelStep();
	// PC - IR/OCV
	AddListView(ListView_PC, "D" + IntToStr(PC_D_INTERFACE_START_DEV_NUM1 + PC_D_HEART_BEAT), "PC HEART BEAT");
	AddListView(ListView_PC, "D" + IntToStr(PC_D_INTERFACE_START_DEV_NUM1 + PC_D_IROCV_ERROR), "PC ERROR");
	AddListView(ListView_PC, "D" + IntToStr(PC_D_INTERFACE_START_DEV_NUM1 + PC_D_IROCV_STAGE_AUTO_READY), "STAGE AUTO READY");

	AddListView(ListView_PC, "D" + IntToStr(PC_D_INTERFACE_START_DEV_NUM1 + PC_D_IROCV_TRAY_OUT), "TRAY OUT");
	AddListView(ListView_PC, "D" + IntToStr(PC_D_INTERFACE_START_DEV_NUM1 + PC_D_IROCV_PROB_OPEN), "PROB OPEN");
	AddListView(ListView_PC, "D" + IntToStr(PC_D_INTERFACE_START_DEV_NUM1 + PC_D_IROCV_PROB_CLOSE), "PROB CLOSE");
	AddListView(ListView_PC, "D" + IntToStr(PC_D_INTERFACE_START_DEV_NUM1 + PC_D_IROCV_MEASURING), "MEASURING");
    AddListView(ListView_PC, "D" + IntToStr(PC_D_INTERFACE_START_DEV_NUM1 + PC_D_IROCV_NG_ALARM), "NG ALARM");
	AddListView(ListView_PC, "D" + IntToStr(PC_D_INTERFACE_START_DEV_NUM1 + PC_D_IROCV_COMPLETE), "WRITE COMPLETE");
    AddListView(ListView_PC, "D" + IntToStr(PC_D_INTERFACE_START_DEV_NUM1 + PC_D_IROCV_REMEASURE), "REMEASURE");

	AddListView(ListView_PC, "D" + IntToStr(PC_D_INTERFACE_START_DEV_NUM1 + PC_D_IROCV_NG_COUNT), "IROCV NG COUNT");
	AddListView(ListView_PC, "D" + IntToStr(PC_D_INTERFACE_START_DEV_NUM1 + PC_D_IROCV_IR_MIN), "IROCV IR MIN.");
	AddListView(ListView_PC, "D" + IntToStr(PC_D_INTERFACE_START_DEV_NUM1 + PC_D_IROCV_IR_MAX), "IROCV IR MAX.");
	AddListView(ListView_PC, "D" + IntToStr(PC_D_INTERFACE_START_DEV_NUM1 + PC_D_IROCV_OCV_MIN), "IROCV OCV MIN.");
	AddListView(ListView_PC, "D" + IntToStr(PC_D_INTERFACE_START_DEV_NUM1 + PC_D_IROCV_OCV_MAX), "IROCV OCV MAX.");

	for(int i = 0; i < 25; i++)
		AddListView(ListView_PC, "D" + IntToStr(PC_D_INTERFACE_START_DEV_NUM1 + PC_D_IROCV_MEASURE_OK_NG + i), "IR/OCV OK/NG DATA #" + IntToStr(i + 1));

    for(int channel = 0; channel < MAXCHANNEL; channel += channelStep){
        AddListView(ListView_PC, "D" + IntToStr(PC_D_INTERFACE_IR_RESULT + PC_D_IROCV_RESULT_CODE + channel), "IR/OCV NG CODE #" + IntToStr(channel + 1));
    }

    for(int channel = 0; channel < MAXCHANNEL; channel += channelStep)
		AddListView(ListView_PC, "D" + IntToStr(PC_D_INTERFACE_IR + PC_D_IROCV_IR_VALUE + channel * 2), "IR VALUE #" + IntToStr(channel + 1));

	for(int channel = 0; channel < MAXCHANNEL; channel += channelStep)
		AddListView(ListView_PC, "D" + IntToStr(PC_D_INTERFACE_OCV + PC_D_IROCV_OCV_VALUE + channel * 2), "OCV VALUE #" + IntToStr(channel + 1));
}
//---------------------------------------------------------------------------
// 표시할 채널 간격. PLC 데이터 자체나 읽기/쓰기 통신 범위는 변경하지 않는다.
int __fastcall TForm_PLCInterface::GetDisplayChannelStep()
{
    return chkShowAll->Checked ? 1 : 20;
}
//---------------------------------------------------------------------------
// Show all 전환: 목록과 값의 행 순서를 함께 다시 만든다. 테스트 패널 표시 상태는 유지한다.
void __fastcall TForm_PLCInterface::chkShowAllClick(TObject *Sender)
{
    const bool timerEnabled = Timer_Update->Enabled;
    Timer_Update->Enabled = false;
    ListView_PLC->Items->BeginUpdate();
    ListView_PC->Items->BeginUpdate();
    try
    {
        SetListViewPLC();
        SetListViewPC();
        Timer_UpdateTimer(Sender);
    }
    __finally
    {
        ListView_PC->Items->EndUpdate();
        ListView_PLC->Items->EndUpdate();
        Timer_Update->Enabled = timerEnabled;
    }
}
//---------------------------------------------------------------------------
void __fastcall TForm_PLCInterface::AddListView(TListView *list, AnsiString address, AnsiString name)
{
	tempListItem = list->Items->Add();
	tempListItem->Caption = address;
	tempListItem->SubItems->Add(name);
	tempListItem->SubItems->Add("");
}
//---------------------------------------------------------------------------
void __fastcall TForm_PLCInterface::FormShow(TObject *Sender)
{
	SetTestPanelVisible(false);
	Timer_Update->Enabled = true;
}
//---------------------------------------------------------------------------
void __fastcall TForm_PLCInterface::FormClose(TObject *Sender, TCloseAction &Action)
{
	Timer_Update->Enabled = false;
}
//---------------------------------------------------------------------------
//---------------------------------------------------------------------------
void __fastcall TForm_PLCInterface::Timer_UpdateTimer(TObject *Sender)
{
	const int channelStep = GetDisplayChannelStep();
	// 전체 표시 시에도 행별 재그리기를 모아서 스크롤 중 깜빡임을 줄인다.
	ListView_PLC->Items->BeginUpdate();
	ListView_PC->Items->BeginUpdate();
	try
	{
        int index;
        if(Mod_PLC->ClientSocket_PC->Active)
        {
            lblConnection->Caption = "PC PLC : CONNECTED";
            lblConnection->Font->Color = clGreen;
        }
        else
        {
            lblConnection->Caption = "PC PLC : DISCONNECTED";
            lblConnection->Font->Color = clRed;
        }

        Label4->Caption = "CELL INFO. : ";
        if(Mod_PLC->ClientSocket_PLC->Active)    //    PLC 상태
        {
            // PLC - IR/OCV
            index = 0;
            ListView_PLC->Items->Item[index++]->SubItems->Strings[1] = Mod_PLC->GetDouble(Mod_PLC->plc_Interface_Data, PLC_D_HEART_BEAT);
            ListView_PLC->Items->Item[index++]->SubItems->Strings[1] = Mod_PLC->GetDouble(Mod_PLC->plc_Interface_Data, PLC_D_IROCV_AUTO_MANUAL);
            ListView_PLC->Items->Item[index++]->SubItems->Strings[1] = Mod_PLC->GetDouble(Mod_PLC->plc_Interface_Data, PLC_D_IROCV_ERROR);
            ListView_PLC->Items->Item[index++]->SubItems->Strings[1] = Mod_PLC->GetDouble(Mod_PLC->plc_Interface_Data, PLC_D_IROCV_TRAY_IN);
            ListView_PLC->Items->Item[index++]->SubItems->Strings[1] = Mod_PLC->GetDouble(Mod_PLC->plc_Interface_Data, PLC_D_IROCV_PROB_OPEN);
            ListView_PLC->Items->Item[index++]->SubItems->Strings[1] = Mod_PLC->GetDouble(Mod_PLC->plc_Interface_Data, PLC_D_IROCV_PROB_CLOSE);
            ListView_PLC->Items->Item[index++]->SubItems->Strings[1] = Mod_PLC->GetDouble(Mod_PLC->plc_Interface_Data, PLC_D_IROCV_COMPLETE);
            ListView_PLC->Items->Item[index++]->SubItems->Strings[1] = Mod_PLC->GetString(Mod_PLC->plc_Interface_Data, PLC_D_IROCV_TRAY_ID, 10);

            AnsiString cell_info;
            for(int i = 0; i < 25; i++)
            {
                cell_info = "";
                for(int j = 0; j < 16; j++)
                {
                    cell_info += Mod_PLC->GetData(Mod_PLC->plc_Interface_Data, PLC_D_IROCV_TRAY_CELL_DATA + i, j);
                }
                ListView_PLC->Items->Item[index++]->SubItems->Strings[1] = cell_info;
                Label4->Caption += Mod_PLC->GetDouble(Mod_PLC->plc_Interface_Data, PLC_D_IROCV_TRAY_CELL_DATA + i);
            }

            //* CELL SERIAL
            ListView_PLC->Items->Item[index++]->SubItems->Strings[1] = Mod_PLC->GetCellSrialTrayId(PLC_D_IROCV_CELL_SERIAL_TRAYID, 10);
            for(int channel = 0; channel < MAXCHANNEL; channel += channelStep)
                ListView_PLC->Items->Item[index++]->SubItems->Strings[1] = Mod_PLC->GetCellSrial(PLC_D_IROCV_CELL_SERIAL, channel, PLC_D_CELL_SERIAL_WORDS_PER_CHANNEL);
        }

        if(Mod_PLC->ClientSocket_PC->Active)    //    PC 상태
        {
            // PC - IR/OCV
            index = 0;
            ListView_PC->Items->Item[index++]->SubItems->Strings[1] = Mod_PLC->GetDouble(Mod_PLC->pc_Interface_Data, PC_D_HEART_BEAT);
            ListView_PC->Items->Item[index++]->SubItems->Strings[1] = Mod_PLC->GetDouble(Mod_PLC->pc_Interface_Data, PC_D_IROCV_ERROR);
            ListView_PC->Items->Item[index++]->SubItems->Strings[1] = Mod_PLC->GetDouble(Mod_PLC->pc_Interface_Data, PC_D_IROCV_STAGE_AUTO_READY);
            ListView_PC->Items->Item[index++]->SubItems->Strings[1] = Mod_PLC->GetDouble(Mod_PLC->pc_Interface_Data, PC_D_IROCV_TRAY_OUT);
            ListView_PC->Items->Item[index++]->SubItems->Strings[1] = Mod_PLC->GetDouble(Mod_PLC->pc_Interface_Data, PC_D_IROCV_PROB_OPEN);
            ListView_PC->Items->Item[index++]->SubItems->Strings[1] = Mod_PLC->GetDouble(Mod_PLC->pc_Interface_Data, PC_D_IROCV_PROB_CLOSE);
            ListView_PC->Items->Item[index++]->SubItems->Strings[1] = Mod_PLC->GetDouble(Mod_PLC->pc_Interface_Data, PC_D_IROCV_MEASURING);
            ListView_PC->Items->Item[index++]->SubItems->Strings[1] = Mod_PLC->GetDouble(Mod_PLC->pc_Interface_Data, PC_D_IROCV_NG_ALARM);
            ListView_PC->Items->Item[index++]->SubItems->Strings[1] = Mod_PLC->GetDouble(Mod_PLC->pc_Interface_Data, PC_D_IROCV_COMPLETE);
            ListView_PC->Items->Item[index++]->SubItems->Strings[1] = Mod_PLC->GetDouble(Mod_PLC->pc_Interface_Data, PC_D_IROCV_REMEASURE);

            ListView_PC->Items->Item[index++]->SubItems->Strings[1] = Mod_PLC->GetDouble(Mod_PLC->pc_Interface_Data, PC_D_IROCV_NG_COUNT);
            ListView_PC->Items->Item[index++]->SubItems->Strings[1] = Mod_PLC->GetDouble(Mod_PLC->pc_Interface_Data, PC_D_IROCV_IR_MIN);
            ListView_PC->Items->Item[index++]->SubItems->Strings[1] = Mod_PLC->GetDouble(Mod_PLC->pc_Interface_Data, PC_D_IROCV_IR_MAX);
            ListView_PC->Items->Item[index++]->SubItems->Strings[1] = Mod_PLC->GetDouble(Mod_PLC->pc_Interface_Data, PC_D_IROCV_OCV_MIN);
            ListView_PC->Items->Item[index++]->SubItems->Strings[1] = Mod_PLC->GetDouble(Mod_PLC->pc_Interface_Data, PC_D_IROCV_OCV_MAX);

            AnsiString okng_bin;
            for(int i = 0; i < 25; i++)
            {
                okng_bin = "";
                for(int j = 0; j < 16; j++)
                    okng_bin += Mod_PLC->GetData(Mod_PLC->pc_Interface_Data, PC_D_IROCV_MEASURE_OK_NG + i, j);

                ListView_PC->Items->Item[index++]->SubItems->Strings[1] = okng_bin;
            }

            for(int channel = 0; channel < MAXCHANNEL; channel += channelStep)
                ListView_PC->Items->Item[index++]->SubItems->Strings[1] = Mod_PLC->GetResultCode(PC_D_IROCV_RESULT_CODE, channel);

            for(int channel = 0; channel < MAXCHANNEL; channel += channelStep)
                ListView_PC->Items->Item[index++]->SubItems->Strings[1] = Mod_PLC->GetIrValue(PC_D_IROCV_IR_VALUE, channel);

            for(int channel = 0; channel < MAXCHANNEL; channel += channelStep)
                ListView_PC->Items->Item[index++]->SubItems->Strings[1] = Mod_PLC->GetOcvValue(PC_D_IROCV_OCV_VALUE, channel);
        }
	}
	__finally
	{
		ListView_PC->Items->EndUpdate();
		ListView_PLC->Items->EndUpdate();
	}
}
//---------------------------------------------------------------------------

void __fastcall TForm_PLCInterface::AdvSmoothButton_CloseClick(TObject *Sender)
{
    Timer_Update->Enabled = false;
	this->Close();
}
//---------------------------------------------------------------------------
void __fastcall TForm_PLCInterface::GroupBox_PLC_PCClick(TObject *Sender)
{
	SetTestPanelVisible(!Panel1->Visible);
}
//---------------------------------------------------------------------------
void __fastcall TForm_PLCInterface::SetTestPanelVisible(bool visible)
{
	Panel1->Visible = visible;
	ClientWidth = visible ? PLC_TEST_CLIENT_WIDTH : PLC_MONITOR_CLIENT_WIDTH;
}
//---------------------------------------------------------------------------
void __fastcall TForm_PLCInterface::SetTestMessage(AnsiString message, TColor color)
{
	lblTestStatus->Caption = message;
	lblTestStatus->Font->Color = color;
}
//---------------------------------------------------------------------------
int __fastcall TForm_PLCInterface::GetTestAddress()
{
	return ParseDeviceAddress(cbAddress->Text);
}
//---------------------------------------------------------------------------
bool __fastcall TForm_PLCInterface::TryReadTestWord(int address, int &value, AnsiString &area)
{
	if(address >= PC_D_INTERFACE_START_DEV_NUM1
		&& address < PC_D_INTERFACE_START_DEV_NUM1 + PC_D_INTERFACE_LEN1)
	{
		area = "PC INTERFACE";
		value = static_cast<int>(Mod_PLC->GetDouble(Mod_PLC->pc_Interface_Data,
			address - PC_D_INTERFACE_START_DEV_NUM1));
		return true;
	}

	if(address >= PC_D_INTERFACE_IR
		&& address < PC_D_INTERFACE_IR + PC_D_INTERFACE_IR_LEN)
	{
		area = "IR DATA";
		value = static_cast<int>(Mod_PLC->GetDouble(Mod_PLC->pc_Interface_Ir_Data,
			address - PC_D_INTERFACE_IR));
		return true;
	}

	if(address >= PC_D_INTERFACE_OCV
		&& address < PC_D_INTERFACE_OCV + PC_D_INTERFACE_OCV_LEN)
	{
		area = "OCV DATA";
		value = static_cast<int>(Mod_PLC->GetDouble(Mod_PLC->pc_Interface_Ocv_Data,
			address - PC_D_INTERFACE_OCV));
		return true;
	}

	if(address >= PC_D_INTERFACE_IR_RESULT
		&& address < PC_D_INTERFACE_IR_RESULT + PC_D_INTERFACE_IR_RESULT_LEN)
	{
		area = "RESULT CODE";
		value = static_cast<int>(Mod_PLC->GetDouble(Mod_PLC->pc_Interface_Result_Code,
			address - PC_D_INTERFACE_IR_RESULT));
		return true;
	}

	area = "VALID: D45000-45069 / D45070-45869 / D46000-46799 / D47000-47399";
	return false;
}
//---------------------------------------------------------------------------
bool __fastcall TForm_PLCInterface::TryWriteTestWord(int address, int value, AnsiString &area)
{
	if(address >= PC_D_INTERFACE_START_DEV_NUM1
		&& address < PC_D_INTERFACE_START_DEV_NUM1 + PC_D_INTERFACE_LEN1)
	{
		area = "PC INTERFACE";
		Mod_PLC->SetDouble(Mod_PLC->pc_Interface_Data,
			address - PC_D_INTERFACE_START_DEV_NUM1, value);
		return true;
	}

	if(address >= PC_D_INTERFACE_IR
		&& address < PC_D_INTERFACE_IR + PC_D_INTERFACE_IR_LEN)
	{
		area = "IR DATA";
		Mod_PLC->SetDouble(Mod_PLC->pc_Interface_Ir_Data,
			address - PC_D_INTERFACE_IR, value);
		return true;
	}

	if(address >= PC_D_INTERFACE_OCV
		&& address < PC_D_INTERFACE_OCV + PC_D_INTERFACE_OCV_LEN)
	{
		area = "OCV DATA";
		Mod_PLC->SetDouble(Mod_PLC->pc_Interface_Ocv_Data,
			address - PC_D_INTERFACE_OCV, value);
		return true;
	}

	if(address >= PC_D_INTERFACE_IR_RESULT
		&& address < PC_D_INTERFACE_IR_RESULT + PC_D_INTERFACE_IR_RESULT_LEN)
	{
		area = "RESULT CODE";
		Mod_PLC->SetDouble(Mod_PLC->pc_Interface_Result_Code,
			address - PC_D_INTERFACE_IR_RESULT, value);
		return true;
	}

	area = "VALID: D45000-45069 / D45070-45869 / D46000-46799 / D47000-47399";
	return false;
}
//---------------------------------------------------------------------------
void __fastcall TForm_PLCInterface::btnWriteValueClick(TObject *Sender)
{
	int address = GetTestAddress();
	int value = editValue->Text.Trim().ToIntDef(1000000);
	AnsiString area;

	if(value < -32768 || value > 65535)
	{
		SetTestMessage("WRITE ERROR : value must be -32768 .. 65535", clRed);
		return;
	}

	if(!TryWriteTestWord(address, value, area))
	{
		lblWordArea->Caption = area;
		SetTestMessage("WRITE ERROR : invalid device address", clRed);
		return;
	}

	lblWordArea->Caption = area + " / D" + IntToStr(address);
	SetTestMessage("WRITE OK : D" + IntToStr(address) + " = " + IntToStr(value), clGreen);
}
//---------------------------------------------------------------------------
void __fastcall TForm_PLCInterface::btnReadValueClick(TObject *Sender)
{
	int address = GetTestAddress();
	int value = 0;
	AnsiString area;

	if(!TryReadTestWord(address, value, area))
	{
		lblWordArea->Caption = area;
		SetTestMessage("READ ERROR : invalid device address", clRed);
		return;
	}

	editValue->Text = IntToStr(value);
	lblWordArea->Caption = area + " / D" + IntToStr(address);
	SetTestMessage("READ OK : D" + IntToStr(address) + " = " + IntToStr(value), clNavy);
}
//---------------------------------------------------------------------------
void __fastcall TForm_PLCInterface::btnSetPresetClick(TObject *Sender)
{
	TButton *button = dynamic_cast<TButton *>(Sender);
	if(button == NULL)
		return;

	editValue->Text = IntToStr(button->Tag);
	btnWriteValueClick(Sender);
}
//---------------------------------------------------------------------------
void __fastcall TForm_PLCInterface::btnWriteNgValueClick(TObject *Sender)
{
	ApplyNgChannels(editIrOcvNg->Text);
}
//---------------------------------------------------------------------------
bool __fastcall TForm_PLCInterface::ApplyNgChannels(AnsiString channelText)
{
	bool selected[MAXCHANNEL];
	memset(selected, 0, sizeof(selected));
	int ngCount = 0;
	TStringList *tokens = new TStringList;

	try
	{
		tokens->StrictDelimiter = true;
		tokens->Delimiter = ',';
		tokens->DelimitedText = channelText;

		for(int tokenIndex = 0; tokenIndex < tokens->Count; tokenIndex++)
		{
			AnsiString token = tokens->Strings[tokenIndex].Trim();
			if(token.Length() == 0)
				continue;

			int first = -1;
			int last = -1;
			int dash = token.Pos("-");
			if(dash > 0)
			{
				first = token.SubString(1, dash - 1).Trim().ToIntDef(-1);
				last = token.SubString(dash + 1, token.Length() - dash).Trim().ToIntDef(-1);
			}
			else
			{
				first = token.ToIntDef(-1);
				last = first;
			}

			if(first < 1 || last > MAXCHANNEL || first > last)
			{
				lblNgStatus->Caption = "INPUT ERROR : " + token + "  (valid 1-" + IntToStr(MAXCHANNEL) + ")";
				lblNgStatus->Font->Color = clRed;
				SetTestMessage("NG DATA NOT CHANGED", clRed);
				return false;
			}

			for(int channel = first; channel <= last; channel++)
				selected[channel - 1] = true;
		}
	}
	__finally
	{
		delete tokens;
	}

	for(int i = 0; i < 25; ++i)
	{
		for(int j = 0; j < 16; j++)
		{
			int nChannel = i * 16 + j + 1;
			if(selected[nChannel - 1])
			{
				Mod_PLC->SetData(Mod_PLC->pc_Interface_Data, PC_D_IROCV_MEASURE_OK_NG + i, j, true);
				ngCount++;
			}
			else
			{
				Mod_PLC->SetData(Mod_PLC->pc_Interface_Data, PC_D_IROCV_MEASURE_OK_NG + i, j, false);
			}
		}
	}

	Mod_PLC->SetDouble(Mod_PLC->pc_Interface_Data, PC_D_IROCV_NG_COUNT, ngCount);
	lblNgStatus->Caption = "APPLIED : " + IntToStr(ngCount) + " NG / " + IntToStr(MAXCHANNEL) + " CH";
	lblNgStatus->Font->Color = clGreen;
	SetTestMessage("NG CHANNEL DATA UPDATED", clGreen);
	return true;
}
//---------------------------------------------------------------------------
void __fastcall TForm_PLCInterface::btnClearNgClick(TObject *Sender)
{
	editIrOcvNg->Text = "";
	ApplyNgChannels("");
}
//---------------------------------------------------------------------------
void __fastcall TForm_PLCInterface::btnAllNgClick(TObject *Sender)
{
	editIrOcvNg->Text = "1-" + IntToStr(MAXCHANNEL);
	ApplyNgChannels(editIrOcvNg->Text);
}
//---------------------------------------------------------------------------

void __fastcall TForm_PLCInterface::btnWriteIrOcvValueClick(TObject *Sender)
{
    Mod_PLC->PLC_Write_Result = true;
	double ir_base = BaseForm->StringToDouble(editIR->Text, 1);
	double ocv_base = BaseForm->StringToDouble(editOCV->Text, 1);
	int channelIncrement = chkChannelIncrement->Checked
		? editIncrement->Text.Trim().ToIntDef(1) : 0;

	// ir value 2 Word
	// 2 Word :  value / (65536 / 2) => 윗 주소에 쓰기, value % (65536 /2 ) => 아래 주소에 쓰기 // herald 2017 11 30
	for(int i = 0; i < MAXCHANNEL; i++)
	{
		int32_t ir_int = static_cast<int32_t>(ir_base * 100.0)
			+ (i * channelIncrement);  // signed 32-bit int
        Mod_PLC->SetIrValue(PC_D_IROCV_IR_VALUE, i, ir_int);
	}

	for(int i = 0; i < MAXCHANNEL; i++)
	{
		int32_t ocv_int = static_cast<int32_t>(ocv_base * 10.0)
			+ (i * channelIncrement);  // signed 32-bit int
        Mod_PLC->SetOcvValue(PC_D_IROCV_OCV_VALUE, i, ocv_int);
	}

	SetTestMessage("RESULT DATA UPDATED : " + IntToStr(MAXCHANNEL)
		+ " CH / increment " + IntToStr(channelIncrement), clGreen);
}
//---------------------------------------------------------------------------



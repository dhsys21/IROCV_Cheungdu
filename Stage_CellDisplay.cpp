// [채널 화면] 400채널 패널 생성, 번호/측정값 표시, 판정 색상. 판정 로직은 Stage_Measurement.cpp.
// 전체 구조 및 오류 추적 위치: CODE_STRUCTURE.md

#include <vcl.h>
#pragma hdrstop

#include "FormTotal.h"
#include "RVMO_main.h"


//---------------------------------------------------------------------------
// 모든 채널의 수신 표시를 해제한다. 시작 안내는 번호, 트레이 투입/측정 이후 초기화는 공란이다.
void __fastcall TTotalForm::InitCellDisplay()
{
	for(int i=0; i<MAXCHANNEL; ++i){
        irValueReceived[i] = false;
        ocvValueReceived[i] = false;
		panel[i]->Color = clLine;
		panel[i]->ParentBackground = false;
		if(MeasureInfoForm->stage == this->Tag){
            AnsiString irCaption = "", ocvCaption = "";
            if(showStartupChannelNumbers)
            {
                irCaption = IntToStr(i + 1);
                ocvCaption = IntToStr(i / LINECOUNT + 1) + "-" + IntToStr(i % LINECOUNT + 1);
            }
            MeasureInfoForm->DisplayIrValue(i, clLine, irCaption, false);
            MeasureInfoForm->DisplayOcvValue(i, clLine, ocvCaption, false);
		}
	}

    MeasureInfoForm->initChart(10, 40, 1600, 4000);
}

//---------------------------------------------------------------------------
// 현재 트레이를 측정정보 창에 연결한다. 창을 다시 열어도 수신값/미수신 공란/시작 안내 상태를 유지한다.
void __fastcall TTotalForm::InitMeasureForm()
{

	MeasureInfoForm->InitStruct();
	MeasureInfoForm->stage = this->Tag;
	MeasureInfoForm->display.cell = tray.cell;	// cell 정보
	MeasureInfoForm->display.orginal_value = tray.orginal_value;	// 보정전 값 - ir
	MeasureInfoForm->display.after_value = tray.after_value;		// 보정후 값 - ir
	MeasureInfoForm->display.ocv_value = tray.ocv_value;			// ocv
	MeasureInfoForm->display.measure_result = tray.measure_result;	// ir 결과
	MeasureInfoForm->pstage->Caption = lblTitle->Caption;
    for(int i = 0; i < MAXCHANNEL; ++i)
        SetProcessColor(i, GetColorIndex(panel[i]->Color));

//	MeasureInfoForm->pLocal->Visible = false;
//	MeasureInfoForm->grpRemeasure->Visible = false;
	MeasureInfoForm->grbChannelInfo->Visible = true;
	MeasureInfoForm->BringToFront();
	MeasureInfoForm->Visible = true;
}

//---------------------------------------------------------------------------
// 설비 배치 타입에 맞춰 메인 화면의 400채널 패널을 생성한다.
void __fastcall TTotalForm::MakePanel(AnsiString type)
{
	int nx, ny, nw, nh;

	if(type == "3" || type == "4")
	{
    	nh = (pBase->Height-21)/LINECOUNT;
		nw = (pBase->Width-21)/LINECOUNT;
		nx = pBase->Width - nw - 1;
//		nx = 1;
//		ny = pBase->Height - nh - 1;
		ny = 1;

//		nx = 2;
//		ny = 308;
//		nw = 26;
//		nh = 19;

		for(int index=0; index<MAXCHANNEL;){
			panel[index] = new TPanel(this);
			panel[index]->Parent = pBase;
			panel[index]->Left =  nx;
			panel[index]->Top = ny;
			panel[index]->Width = nw;
			panel[index]->Height = nh;

			panel[index]->Color = pnormal1->Color;

			panel[index]->BevelInner = bvNone;
			panel[index]->BevelKind = bkNone;
			panel[index]->BevelOuter = bvNone;
			panel[index]->Tag = index;
	//		panel[index]->Caption = index;

			panel[index]->Hint = IntToStr(index+1) + " (" + IntToStr((index/LINECOUNT)+1) + "-" + IntToStr((index%LINECOUNT)+1) + ")";
			panel[index]->ShowHint = true;

			panel[index]->OnMouseEnter =  ChInfoMouseEnter;
			panel[index]->OnMouseLeave =  ChInfoMouseLeave;

			index += 1;
//			nx = nx + nw + 1;
			nx = nx - nw - 1;
//			if(index % 2 == 0) nx += 1;
			if(index % 2 == 0) nx -= 1;
//			if(index % 10 == 0) nx += 1;
			if(index % (LINECOUNT / 2) == 0) nx -= 1;
			if(index % LINECOUNT == 0)
			{
//				ny = ny - nh - 1;
				ny = ny + nh + 1;
//				nx = 1;
				nx = pBase->Width - nw - 1;
//				if( (index / 20) % 10 == 0) ny -= 2;
				if( (index / LINECOUNT) % (LINECOUNT / 2) == 0) ny += 2;
			}
		}
	}
	else if(type == "1")
	{
        nh = (pBase->Height-21)/LINECOUNT;
		nw = (pBase->Width-21)/LINECOUNT;
//		nx = pBase->Width - nw - 1;
		nx = 1;
		ny = pBase->Height - nh - 1;

//		nh = 13;
//		nw = 27;
//		//nx = 421;
//		nx = 2;
//		ny = 225;

		for(int index=0; index<MAXCHANNEL;){
			panel[index] = new TPanel(this);
			panel[index]->Parent = pBase;
			panel[index]->Left =  nx;
			panel[index]->Top = ny;
			panel[index]->Width = nw;
			panel[index]->Height = nh;

			panel[index]->Color = pnormal1->Color;
			panel[index]->ParentBackground = false;

			panel[index]->BevelInner = bvNone;
			panel[index]->BevelKind = bkNone;
			panel[index]->BevelOuter = bvNone;
			panel[index]->Tag = index;
	//		panel[index]->Caption = index;

			panel[index]->Hint = IntToStr(index+1) + " (" + IntToStr((index/LINECOUNT)+1) + "-" + IntToStr((index%LINECOUNT)+1) + ")";
			panel[index]->ShowHint = true;

			panel[index]->OnMouseEnter =  ChInfoMouseEnter;
			panel[index]->OnMouseLeave =  ChInfoMouseLeave;

			index += 1;
			nx = nx + nw + 1;
			if(index % 2 == 0) nx += 1;
			if(index % (LINECOUNT / 2) == 0) nx += 1;
			if(index % LINECOUNT == 0)
			{
				ny = ny - nh - 1;
				nx = 1;
				if( (index / LINECOUNT) % (LINECOUNT / 2) == 0) ny -= 2;
			}
		}
	}
    else if(type == "2")
	{
        nh = (pBase->Height-21)/LINECOUNT;
		nw = (pBase->Width-21)/LINECOUNT;
		nx = pBase->Width - nw - 1;
		ny = pBase->Height - nh - 1;

		for(int index = 0; index < MAXCHANNEL;){
			panel[index] = new TPanel(this);
			panel[index]->Parent = pBase;
			panel[index]->Left =  nx;
			panel[index]->Top = ny;
			panel[index]->Width = nw;
			panel[index]->Height = nh;

			panel[index]->Color = pnormal1->Color;
			panel[index]->ParentBackground = false;

			panel[index]->BevelInner = bvNone;
			panel[index]->BevelKind = bkNone;
			panel[index]->BevelOuter = bvNone;
			panel[index]->Tag = index;
	//		panel[index]->Caption = index;

			panel[index]->Hint = IntToStr(index+1) + " (" + IntToStr((index/LINECOUNT)+1) + "-" + IntToStr((index%LINECOUNT)+1) + ")";
			panel[index]->ShowHint = true;

			panel[index]->OnMouseEnter =  ChInfoMouseEnter;
			panel[index]->OnMouseLeave =  ChInfoMouseLeave;

			index += 1;
			nx = nx - (nw + 1);
			if(index % 2 == 0) nx -= 1;
			if(index % (LINECOUNT / 2) == 0) nx -= 1;
			if(index % LINECOUNT == 0)
			{
				ny = ny - nh - 1;
				nx = pBase->Width - nw - 1;
				if( (index / LINECOUNT) % (LINECOUNT / 2) == 0) ny -= 2;
			}
		}
	}
    else if(type == "5")
	{
        nh = (pBase->Height-21)/LINECOUNT;
		nw = (pBase->Width-21)/LINECOUNT;
		nx = pBase->Width - nw - 1;
		ny = pBase->Height - nh - 1;

		for(int index=0; index<MAXCHANNEL;){
			panel[index] = new TPanel(this);
			panel[index]->Parent = pBase;
			panel[index]->Left =  nx;
			panel[index]->Top = ny;
			panel[index]->Width = nw;
			panel[index]->Height = nh;

			panel[index]->Color = pnormal1->Color;
			panel[index]->ParentBackground = false;

			panel[index]->BevelInner = bvNone;
			panel[index]->BevelKind = bkNone;
			panel[index]->BevelOuter = bvNone;
			panel[index]->Tag = index;
	//		panel[index]->Caption = index;

			panel[index]->Hint = IntToStr(index+1) + " (" + IntToStr((index/LINECOUNT)+1) + "-" + IntToStr((index%LINECOUNT)+1) + ")";
			panel[index]->ShowHint = true;

			panel[index]->OnMouseEnter =  ChInfoMouseEnter;
			panel[index]->OnMouseLeave =  ChInfoMouseLeave;

			index += 1;
            ny = ny - nh - 1;

			if(index % 40 == 0) nx -= 1;
			if(index % 200 == 0) nx -= 1;
            if(index % 10 == 0) ny -= 2;
			if(index % LINECOUNT == 0)
			{
				ny = pBase->Height - nh - 1;
                nx = nx - (nw + 1);
				//nx = pBase->Width - nw - 1;
			}
		}
	}
}

//---------------------------------------------------------------------------
// 셀 유무/판정 색상 갱신. IR·OCV 수신 여부를 각각 확인하여 실제 값 또는 미수신 공란을 표시한다.
void __fastcall TTotalForm::SetProcessColor(int index, int clr)
{
	TColor basic;

	TColor irColor = cl_line->Color;
	TColor ocvColor = cl_line->Color;
	AnsiString sir, socv;
	basic = panel[index]->Color;

    // IR과 OCV는 따로 도착한다. 수신 전 숫자를 측정값으로 표시하지 않는다.
    sir = "";
    socv = "";
    if(showStartupChannelNumbers)
    {
        sir = IntToStr(index + 1);
        socv = IntToStr(index / LINECOUNT + 1) + "-" + IntToStr(index % LINECOUNT + 1);
    }

	if(tray.cell[index] == 1){

        if(irValueReceived[index])
			sir = FormatFloat("0.00", tray.after_value[index]);
        if(ocvValueReceived[index])
			socv = FormatFloat("0.0", tray.ocv_value[index]);

		switch(clr){
			case Line:
				basic = clLine;
				break;
			case BadIr:
				basic = clBadIr;
				irColor = clBadIr;
				break;
			case AverageOver:
				basic = clAverageOver;
                irColor = clAverageOver;
                break;
			case BadOcv:
				if(basic == clMeasureFail)
				{
					irColor = clMeasureFail;
				}
				else
				{
					basic = pocv->Color;
					ocvColor = pocv->Color;
                }
				break;
			case IrCheck:
				if(basic != clMeasureFail){
					if(basic == clOcvCheck)basic = clBothCheck;
					else basic = clIrCheck;
				}else{
					basic = clIrCheck;
				}
				break;
			case OcvCheck:
				if(basic == clMeasureFail){
					irColor = clMeasureFail;
				}else{
					if(basic == clIrCheck)basic = clBothCheck;
					else basic = clOcvCheck;
				}
				break;
			case MeasureFail:
				basic = clMeasureFail;
				irColor = clMeasureFail;
				break;
		}
	}
	else{
        if(irValueReceived[index] || ocvValueReceived[index])
        {
            sir = "NO";
            socv = "CELL";
        }

		if(clr == CellError){
			WriteCommLog("ETC", "CellError");
			basic = clCellError;
		}else{
			if(basic == clLine)basic = clNoCell;
		}
		irColor = basic;
		ocvColor = basic;
	}

	panel[index]->Color = basic;

	if(MeasureInfoForm->stage == this->Tag){
        MeasureInfoForm->DisplayIrValue(index, irColor, sir, irValueReceived[index]);
        MeasureInfoForm->DisplayOcvValue(index, ocvColor, socv, ocvValueReceived[index]);
	}

}

//---------------------------------------------------------------------------
// 현재 채널 패널 색상을 표시용 상태 번호로 변환한다.
int __fastcall TTotalForm::GetColorIndex(TColor clr)
{
	if(clr == clNoCell)		return 1;
	if(clr == clBadIr )		return 2;
	if(clr == clCellError )	return 3;
	if(clr == clLine )		return 4;
	if(clr == clIrCheck )	return 5;
	if(clr == clOcvCheck )	return 6;
	if(clr == clBothCheck)	return 7;
	if(clr==clMeasureFail)	return 8;
	if(clr == pocv->Color) 	return 9;
	return 100;
}

//---------------------------------------------------------------------------
// CELL DATA의 셀 유무를 채널 화면에 반영한다. 측정값 수신 여부는 변경하지 않는다.
void __fastcall TTotalForm::DisplayTrayInfo()
{
	
	for(int i=0; i<MAXCHANNEL; ++i){
		if(tray.cell[i] == 1){
			SetProcessColor(i, Line);
		}
		else{
			SetProcessColor(i, NoCell);
		}
	}
}


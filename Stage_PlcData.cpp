// [PLC 결과 작성] 검사 출력 초기화, NG 비트/수량, IR/OCV 값, 결과 코드, 규격값.
// 전체 구조 및 오류 추적 위치: CODE_STRUCTURE.md

#include <vcl.h>
#include <math.h>
#pragma hdrstop

#include "FormTotal.h"
#include "RVMO_main.h"
#include "FormCalibration.h"

//---------------------------------------------------------------------------
// PC→PLC 검사 출력과 결과 버퍼 초기화. 기존 주소·초기값·출력 순서를 유지한다.
void __fastcall TTotalForm::PLCInitialization()
{
    Mod_PLC->SetValue(PC_D_IROCV_MEASURING, 0);
	Mod_PLC->SetValue(PC_D_IROCV_TRAY_OUT, 0);
	Mod_PLC->SetValue(PC_D_IROCV_PROB_OPEN, 0);
	Mod_PLC->SetValue(PC_D_IROCV_PROB_CLOSE, 0);
	Mod_PLC->SetValue(PC_D_IROCV_ERROR, 0);

	Mod_PLC->SetValue(PC_D_IROCV_NG_ALARM, 0);
    Mod_PLC->SetValue(PC_D_IROCV_COMPLETE, 0);
    Mod_PLC->SetValue(PC_D_IROCV_REMEASURE, 0);
	Mod_PLC->SetValue(PC_D_IROCV_NG_COUNT, 0);

	for(int i = 0; i < 25; i++)
	{
		for(int j = 0; j < 16; j++)
		{
			Mod_PLC->SetData(Mod_PLC->pc_Interface_Data, PC_D_IROCV_MEASURE_OK_NG + i, j, false);
		}
	}

    WriteIROCVValue(0);
	WriteIRMINMAX();

	WritePLCLog("PLCInitialization", "IROCV TRAY OUT, IROCV PROBE OPEN, IROCV PROBE CLOSE = 0");
	OldPLCStatus = "";
}

//---------------------------------------------------------------------------
// IR/OCV 값을 PLC 결과 버퍼에 쓴다. 인자 없는 함수는 측정값, int 인자는 초기화 값이다.
void __fastcall TTotalForm::WriteIROCVValue()
{
    Mod_PLC->PLC_Write_Result = true;
	for(int i = 0; i < 400; i++)
	{
        //int32_t ir_int = static_cast<int32_t>(BaseForm->StringToDouble(tray.after_value[i], 0) * 100.0);
        int32_t ir_int = static_cast<int32_t>(std::floor(tray.after_value[i] * 100.0 + 0.5));
        Mod_PLC->SetIrValue(PC_D_IROCV_IR_VALUE, i, ir_int);
	}

	for(int i = 0; i < 400; i++)
	{
        //int32_t ocv_int = static_cast<int32_t>(BaseForm->StringToDouble(tray.ocv_value[i], 0) * 10.0);
        int32_t ocv_int = static_cast<int32_t>(std::floor(tray.ocv_value[i] * 10.0 + 0.5));
        Mod_PLC->SetOcvValue(PC_D_IROCV_OCV_VALUE, i, ocv_int);
	}
}

//---------------------------------------------------------------------------
// IR/OCV 값을 PLC 결과 버퍼에 쓴다. 인자 없는 함수는 측정값, int 인자는 초기화 값이다.
void __fastcall TTotalForm::WriteIROCVValue(int initValue)
{
    Mod_PLC->PLC_Write_Result = true;
	for(int i = 0; i < 400; i++)
        Mod_PLC->SetIrValue(PC_D_IROCV_IR_VALUE, i, initValue);

	for(int i = 0; i < 400; i++)
        Mod_PLC->SetOcvValue(PC_D_IROCV_OCV_VALUE, i, initValue);
}

//---------------------------------------------------------------------------
// PLC 셀별 결과 코드 작성: OK=0, NG=1. BadInfomation()으로 최종 NG 비트를 만든 뒤 호출한다.
// 내부 재측정 사유(2/3/4)를 전송하지 않고, PLC OK/NG 비트와 같은 판정을 사용한다.
void __fastcall TTotalForm::WriteResultCode()
{
	for(int i = 0; i < 400; i++)
	{
        // 16셀당 1워드: 셀마다 값을 다시 읽어 이전 셀의 NG 결과가 남지 않게 한다.
        const int resultCode = Mod_PLC->GetData(Mod_PLC->pc_Interface_Data,
            PC_D_IROCV_MEASURE_OK_NG + i / 16, i % 16) ? 1 : 0;
        Mod_PLC->SetResultCode(PC_D_IROCV_RESULT_CODE + i, resultCode);
	}
}

//---------------------------------------------------------------------------
// PLC용 NG 비트/수량과 오류창용 NgCount 집계. NgCount는 존재하는 IR/OCV/접촉 불량 셀만 센다.
void __fastcall TTotalForm::BadInfomation()
{
	int ngCount = 0;
    NgCount = 0;
    int iCell = 0;
    int iRetest = 0;
    TColor clr;
    acc_totaltray = acc_totaltray + 1;
	for(int i = 0; i < 25; ++i){
		for(int j = 0; j < 16; j++)
		{
            iCell = tray.cell[i * 16 + j];
            iRetest = retest.cell[i * 16 + j];
            clr = panel[i * 16 + j]->Color;
			if(iCell == 1 && (clr == cl_badir->Color || clr == cl_ce->Color || clr == pocv->Color))
			{
				Mod_PLC->SetData(Mod_PLC->pc_Interface_Data, PC_D_IROCV_MEASURE_OK_NG + i, j, true);
				ngCount++;
				NgCount++;
			}
			else if(iCell == 1 && iRetest == 0)
			{
				Mod_PLC->SetData(Mod_PLC->pc_Interface_Data, PC_D_IROCV_MEASURE_OK_NG + i, j, false);
			}
			else
			{
				Mod_PLC->SetData(Mod_PLC->pc_Interface_Data, PC_D_IROCV_MEASURE_OK_NG + i, j, true);
				ngCount++;
			}

            if(iCell == 1 && (clr == cl_badir->Color || clr == cl_ce->Color))
			{
                acc_finalng++;
			}
		}
	}

	Mod_PLC->SetValue(PC_D_IROCV_NG_COUNT, ngCount);
}

//---------------------------------------------------------------------------
// 현재 IR/OCV 규격 상·하한을 기존 배율로 PLC 설정 버퍼에 기록한다.
void __fastcall TTotalForm::WriteIRMINMAX()
{
	int32_t irMin = static_cast<int32_t>(BaseForm->StringToDouble(irEdit1->Text, 0) * 10.0);
	int32_t irMax = static_cast<int32_t>(BaseForm->StringToDouble(irEdit2->Text, 0) * 10.0);
	int32_t ocvMin = static_cast<int32_t>(BaseForm->StringToDouble(ocvEdit1->Text, 0) * 10.0);
	int32_t ocvMax = static_cast<int32_t>(BaseForm->StringToDouble(ocvEdit2->Text, 0) * 10.0);

    Mod_PLC->SetSpecValue(PC_D_IROCV_IR_MIN, irMin);
    Mod_PLC->SetSpecValue(PC_D_IROCV_IR_MAX, irMax);
    Mod_PLC->SetSpecValue(PC_D_IROCV_OCV_MIN, ocvMin);
    Mod_PLC->SetSpecValue(PC_D_IROCV_OCV_MAX, ocvMax);

//	Mod_PLC->SetValue(PC_D_IROCV_IR_MIN, irMin);
//	Mod_PLC->SetValue(PC_D_IROCV_IR_MAX, irMax);
//	Mod_PLC->SetValue(PC_D_IROCV_OCV_MIN, ocvMin);
//	Mod_PLC->SetValue(PC_D_IROCV_OCV_MAX, ocvMax);
}


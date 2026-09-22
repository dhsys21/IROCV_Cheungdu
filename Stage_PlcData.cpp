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

	for(int i = 0; i < CELL_DATA_WORD_COUNT; i++)
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
	for(int i = 0; i < MAXCHANNEL; i++)
	{
        //int32_t ir_int = static_cast<int32_t>(BaseForm->StringToDouble(tray.after_value[i], 0) * 100.0);
        int32_t ir_int = static_cast<int32_t>(std::floor(tray.after_value[i] * 100.0 + 0.5));
        Mod_PLC->SetIrValue(PC_D_IROCV_IR_VALUE, i, ir_int);
	}

	for(int i = 0; i < MAXCHANNEL; i++)
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
	for(int i = 0; i < MAXCHANNEL; i++)
        Mod_PLC->SetIrValue(PC_D_IROCV_IR_VALUE, i, initValue);

	for(int i = 0; i < MAXCHANNEL; i++)
        Mod_PLC->SetOcvValue(PC_D_IROCV_OCV_VALUE, i, initValue);
}

//---------------------------------------------------------------------------
// 최종 판정으로 PLC NG 비트·결과 코드·수량을 한 번에 작성한다(OK=0, NG=1).
// measNgCount는 실제 셀의 불량만 센다. PLC 결과 버퍼를 다시 읽어 판정하지 않는다.
void __fastcall TTotalForm::BadInformation()
{
    int plcNgCount = 0;
    int finalIrNg = 0;
    measNgCount = 0;
    for(int i = 0; i < MAXCHANNEL; ++i)
    {
        const bool occupied = tray.cell[i] == 1;
        const int result = retest.cell[i];
        const bool measurementNg = occupied && result != CELL_OK;
        const bool plcNg = !occupied || measurementNg; // 기존 정책: 빈 채널도 PLC에는 NG.
        Mod_PLC->SetData(Mod_PLC->pc_Interface_Data, PC_D_IROCV_MEASURE_OK_NG + i / 16, i % 16, plcNg);
        Mod_PLC->SetResultCode(PC_D_IROCV_RESULT_CODE + i, plcNg ? 1 : 0);
        if(plcNg) ++plcNgCount;
        if(measurementNg) ++measNgCount;
        // 기존 IR/접촉 불량 누계 의미 유지(OCV 제외). 재측정 시 최종값 차이만 반영한다.
        if(occupied && (result == CELL_IR_NG || result == CELL_CONTACT_NG)) ++finalIrNg;
    }
    if(!trayResultCounted) { ++acc_totaltray; trayResultCounted = true; }
    acc_finalng += finalIrNg - countedFinalIrNg;
    countedFinalIrNg = finalIrNg;
    Mod_PLC->SetValue(PC_D_IROCV_NG_COUNT, plcNgCount);
}

//---------------------------------------------------------------------------
// 현재 IR/OCV 규격 상·하한을 기존 배율로 PLC 설정 버퍼에 기록한다.
void __fastcall TTotalForm::WriteIRMINMAX()
{
    // 저장/읽기에서 확정한 검사 규격 사용. PLC 전송 배율은 기존대로 유지한다.
    int32_t irMin = static_cast<int32_t>(config.ir_min * 10.0);
    int32_t irMax = static_cast<int32_t>(config.ir_max * 10.0);
    int32_t ocvMin = static_cast<int32_t>(config.ocv_min * 10.0);
    int32_t ocvMax = static_cast<int32_t>(config.ocv_max * 10.0);

    Mod_PLC->SetSpecValue(PC_D_IROCV_IR_MIN, irMin);
    Mod_PLC->SetSpecValue(PC_D_IROCV_IR_MAX, irMax);
    Mod_PLC->SetSpecValue(PC_D_IROCV_OCV_MIN, ocvMin);
    Mod_PLC->SetSpecValue(PC_D_IROCV_OCV_MAX, ocvMax);

//	Mod_PLC->SetValue(PC_D_IROCV_IR_MIN, irMin);
//	Mod_PLC->SetValue(PC_D_IROCV_IR_MAX, irMax);
//	Mod_PLC->SetValue(PC_D_IROCV_OCV_MIN, ocvMin);
//	Mod_PLC->SetValue(PC_D_IROCV_OCV_MAX, ocvMax);
}

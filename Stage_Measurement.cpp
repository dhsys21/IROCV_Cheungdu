// [측정·재측정] AMS/AMF 및 IR/OCV 처리, 재측정 목록, 결과 마감. 통신 프레임은 Stage_comm.cpp.
// 전체 구조 및 오류 추적 위치: CODE_STRUCTURE.md

#include <vcl.h>
#pragma hdrstop

#include "FormTotal.h"
#include "RVMO_main.h"
#include "FormCalibration.h"

//---------------------------------------------------------------------------
// 수동 측정 초기화: 내부 값은 0으로 지우고 화면은 수신 전까지 공란으로 표시한다.
void __fastcall TTotalForm::OnInit()
{
    CancelResultCellSerialRead(); // [CELL SERIAL 공통] 운영자 초기화 이후 지연 저장 방지.
    showStartupChannelNumbers = false;
    for(int i = 0; i < MAXCHANNEL; ++i)
    {
        tray.ocv_value[i] = 0;
        tray.after_value[i] = 0;
        tray.orginal_value[i] = 0;
    }
    InitCellDisplay();
}

//---------------------------------------------------------------------------
// 전체 측정 시작: 표시·수신 플래그·평균 누계를 초기화하고 AMS 명령을 예약한다.
void __fastcall TTotalForm::CmdAutoTest()
{
    if(resultCellSerialPending) return; // [CELL SERIAL 공통] 이전 결과를 저장하기 전 측정값 덮어쓰기 방지.
    showStartupChannelNumbers = false;
    InitCellDisplay(); // 새 전체 측정: IR/OCV 각각 수신할 때까지 공란으로 표시한다.
    tray.ams = false;
    tray.amf = false;
    for(int i = 0; i < MAXCHANNEL; i++)
	{
		tray.ir_flag[i] = false;
		tray.ocv_flag[i] = false;
	}

	tray.ir_avgAll = 0;
	tray.ir_avgAll_count = 0;

	tray.ocv_avgAll = 0;
    tray.ocv_avgAll_count = 0;

	// 자동검사 4. 검사시작
	MakeData(3, "AMS");
}

//---------------------------------------------------------------------------
// AMF 수신 후 처리: 운전 모드에 따라 결과 마감 또는 기존 자동 개별 재측정을 수행한다.
void __fastcall TTotalForm::ResponseAutoTestFinish()
{
//*
//    if(config.average_use == true) SetRemeasureList();
//	else SetRemeasureList2();

	if(bLocal == true){
		CmdForceStop();
        DisplayProcess(sFinish, "AutoInspection_Measure", " AMF - Measure finished ... ");
		WriteCommLog("IR/OCV STOP", "AMF - ResponseautoTestfinish()");
	}
	else
	{
//		SendData("AMF");    //kedison
		SendData("SEN");
//		CmdForceStop();
    	//* 마련 EVE는 Average(SetRemeasureList2())를 사용하지 않음.
		if(config.average_use == true) SetRemeasureList();
		else SetRemeasureList();
	}
}

//---------------------------------------------------------------------------
// IR 응답 문자열을 값/채널로 해석하고 일반 측정 또는 교정 화면에 전달한다.
void __fastcall TTotalForm::ProcessIr(AnsiString param)
{
	AnsiString result;
	int channel = 0;
	channel = chMap[param.SubString(1, 3).ToInt()];

	param.Delete(1,3);
	int pos = param.Pos("E");

	float value = (float)param.SubString(1, pos-1).ToDouble() * 1000;
	int count = param.SubString(pos + 2, param.Pos(",") - pos - 2).ToInt();

	if(count > 10) value = 0;
	else
	{
		if(param.SubString(pos + 1, 1) == "+")
		{
			for(int i = 0; i < count; i++) {
				value *= 10.0;
			}
		}
		else if(param.SubString(pos + 1, 1) == "-")
		{
			for(int i = 0; i < count; i++) {
				value /= 10.0;
			}
		}
	}

	if(value <= 0 || value > 900)result = "CE";
	else result = "GO";

    int index = channel - 1;

	if(CaliForm->stage != this->Tag)
	{
		InsertIrValue(channel, value, result); //일반계측
	}
	else
	{
		if(result == "GO")
		{
			CaliForm->pmeasure[index]->Caption = FormatFloat("0.000", value);
			CaliForm->poffset[index]->Caption = FormatFloat("0.00", StrToFloat(CaliForm->pstandard[index]->Text) -  value);
		}
	}

	if(tray.rem_mode == 1){
		send.tx_mode = 200;
		this->RemeasureExcute();
	}

}

//---------------------------------------------------------------------------
// 채널 IR 수신 처리: 보정·판정·수신 표시를 갱신한다. 평균 계산 플래그와 표시용 수신 여부는 별개다.
void __fastcall TTotalForm::InsertIrValue(int pos, float value, AnsiString result)
{
	int index = pos-1;
    if(index < 0 || index >= MAXCHANNEL) return;
    irValueReceived[index] = true;

	bool cell = false;

	if(tray.cell[index] == 1)cell = true;
	tray.measure_result[index] = GetReslut(result);


	if(cell)   // 셀이 있을때
	{
        tray.orginal_value[index] = value;
		tray.after_value[index] = tray.orginal_value[index] + BaseForm->DefaultOffset[this->Tag];
		tray.after_value[index] = tray.after_value[index] + stage.ir_offset[index];    //개별보정

		if(tray.measure_result[index] == GO)
		{
			if(tray.after_value[index] >= config.ir_min && tray.after_value[index] <= config.ir_max)
			{
				SetProcessColor(index, IrCheck);

                tray.ir_avgAll_count++;
				tray.ir_avgAll += tray.after_value[index];
                tray.ir_flag[index] = true;
			}
			else
			{
				SetProcessColor(index, MeasureFail);
            }
		}
		else
		{
			tray.orginal_value[index] = 999;
			tray.after_value[index] = 999;
			SetProcessColor(index, MeasureFail);
		}

	}
	else{     // 셀이 없을때
		if(tray.measure_result[index] == GO)
		{
			WriteCommLog("ETC", "OUTFLOW");
			SetProcessColor(index, CellError);
		}

		tray.orginal_value[index] = 0;
		tray.after_value[index] = 0;
	}
}

//---------------------------------------------------------------------------
// 장비의 GO/HI/LO/CE 등 판정 문자를 기존 내부 결과 코드로 변환한다.
int __fastcall TTotalForm::GetReslut(AnsiString result)
{
	if(result == "GO") return GO;
	if(result == "HI") return HI;
	if(result == "LO") return LO;
	if(result == "OV") return OV;
	if(result == "UN") return UN;
	if(result == "CE") return CE;
	if(result == "NA") return NA;
	if(result == "NO") return NO;
	else return 100;
}

//---------------------------------------------------------------------------
// OCV 응답 문자열을 값/채널로 해석하고 채널 판정 및 필요 시 다음 재측정을 진행한다.
void __fastcall TTotalForm::ProcessOcv(AnsiString param)
{
	int channel = 0;
	channel = chMap[param.SubString(1, 3).ToInt()];

	param.Delete(1,3);
	int pos = param.Pos("E");

	float value = (float)param.SubString(1, pos-1).ToDouble() * 1000;
	int count = param.SubString(pos + 2, param.Length()).ToInt();

	if(count > 10) value = 0.0;
	else
	{
		if(param.SubString(pos + 1, 1) == "+")
		{
			for(int i = 0; i < count; i++) {
				value *= 10.0;
			}
		}
		else if(param.SubString(pos + 1, 1) == "-")
		{
			for(int i = 0; i < count; i++) {
				value /= 10.0;
			}
		}
	}

	if(value <= 10 || value > 7000) value = 0.0;

	InsertOcvValue(channel, value);
//	}else{
//    }

	if(tray.rem_mode == 1){
		send.tx_mode = 200;
		this->RemeasureExcute();
	}
}

//---------------------------------------------------------------------------
// 채널 OCV 수신 처리: 규격 판정·평균 집계·화면을 갱신한다.
void __fastcall TTotalForm::InsertOcvValue(int pos, float value)
{
	// 자동검사 5.2 검사 결과 수신 - OCV
	int index = pos-1;
    if(index < 0 || index >= MAXCHANNEL) return;
    ocvValueReceived[index] = true;
	bool cell = false;

	if(tray.cell[index] == 1)cell = true;

	if(cell)
	{
		tray.ocv_value[index] = value;

//		if(config.average_use == true && tray.ocv_value[index] >= 100 && tray.ocv_value[index] <= 4200)
//		{
//            SetProcessColor(index, OcvCheck);
//
//			tray.ocv_avgAll_count++;
//			tray.ocv_avgAll += tray.ocv_value[index];
//			tray.ocv_flag[index] = true;
//		}
//		else if(config.average_use == false && tray.ocv_value[index] >= config.ocv_min && tray.ocv_value[index] <= config.ocv_max)
//		{
//			SetProcessColor(index, OcvCheck);
//
//			tray.ocv_avgAll_count++;
//			tray.ocv_avgAll += tray.ocv_value[index];
//			tray.ocv_flag[index] = true;
//		}
//		else
//		{
//			SetProcessColor(index, BadOcv);
//		}
        if(tray.ocv_value[index] >= config.ocv_min && tray.ocv_value[index] <= config.ocv_max)
		{
			SetProcessColor(index, OcvCheck);

			tray.ocv_avgAll_count++;
			tray.ocv_avgAll += tray.ocv_value[index];
			tray.ocv_flag[index] = true;
		}
		else
		{
			SetProcessColor(index, BadOcv);
		}
	}
	else
	{
		if(value > 1500)
		{
			WriteCommLog("ETC", "OUTFLOW");
			SetProcessColor(index, CellError);
		}
//		tray.ocv_value[index] = 0;
        tray.ocv_value[index] = value;
	}
}

//---------------------------------------------------------------------------
// 전체 측정 후 재측정 대상 집계. 기존 remLimit 조건에 따라 개별 재측정 또는 결과 마감한다.
void __fastcall TTotalForm::SetRemeasureList()
{
	bool brem = false;
	int remeasure_cnt = 0;

	if(stage.arl == nAuto){
		retest.cnt_error = 0;

		for(int index = 0;index < MAXCHANNEL;++index){
			if(tray.cell[index] == 1){
                if(tray.first) acc_totaluse[index] += 1;
                if(tray.after_value[index] == 999){                 //* 4 => 접촉불량(CE)
                    retest.cell[index] = 4;
                    retest.cnt_error += 1;
                    remeasure_cnt += 1;
                    if(tray.first) acc_remeasure[index] += 1;
                }
				else if(tray.after_value[index] < config.ir_min || tray.after_value[index] > config.ir_max){
                    if(retest.cell[index] != 4){
                        retest.cell[index] = 2;
                        retest.cnt_error += 1;
                        remeasure_cnt += 1;
                        if(tray.first) acc_remeasure[index] += 1;	//* 2 => ir spec 불량
                    }
				}
				else if(tray.ocv_value[index] < config.ocv_min || tray.ocv_value[index] > config.ocv_max){
					if(retest.cell[index] != 2 || retest.cell[index] != 4){
						retest.cell[index] = 3;
						retest.cnt_error += 1;
						remeasure_cnt += 1;
						if(tray.first) acc_remeasure[index] += 1;   //* 3 => ocv spec 불량
					}
				}else{
					retest.cell[index] = 0;
				}
			}
			else retest.cell[index] = 0;
		}

        tray.first = false;

		if((remeasure_cnt < remLimit) && (remeasure_cnt > 0)) brem = true;
		else brem= false;

		if(brem == false){
			CmdForceStop();     // Probe Open
		}
		else{
			tray.rem_mode = 1;
			retest.re_index = 0;
			RemeasureExcute();
		}
	} else {
		CmdForceStop();
	}

	WriteCommLog("IR/OCV STOP", "SetRemeasureList()");
}

//---------------------------------------------------------------------------
// 개별 재측정 후 최종 불량 목록을 다시 집계한다. 측정 명령은 보내지 않는다.
void __fastcall TTotalForm::SetRemeasureListAfter()
{
	retest.cnt_error = 0;

    for(int index = 0;index < MAXCHANNEL;++index){
        if(tray.cell[index] == 1){
            if(tray.first) acc_totaluse[index] += 1;
            if(tray.after_value[index] == 999){                 //* 4 => 접촉불량(CE)
                retest.cell[index] = 4;
                retest.cnt_error += 1;
                if(tray.first) acc_remeasure[index] += 1;
            }
            else if(tray.after_value[index] < config.ir_min || tray.after_value[index] > config.ir_max){
                if(retest.cell[index] != 4){
                    retest.cell[index] = 2;
                    retest.cnt_error += 1;
                    if(tray.first) acc_remeasure[index] += 1;	//* 2 => ir spec 불량
                }
            }
            else if(tray.ocv_value[index] < config.ocv_min || tray.ocv_value[index] > config.ocv_max){
                if(retest.cell[index] != 2 || retest.cell[index] != 4){
                    retest.cell[index] = 3;
                    retest.cnt_error += 1;
                    if(tray.first) acc_remeasure[index] += 1;   //* 3 => ocv spec 불량
                }
            }else{
                retest.cell[index] = 0;
            }
        }
        else retest.cell[index] = 0;
    }

	WriteCommLog("IR/OCV STOP", "SetRemeasureListAfter()");
}

//---------------------------------------------------------------------------
// 재측정 목록의 다음 IR/OCV를 요청한다. 더 없으면 최종 판정과 결과 마감을 수행한다.
void __fastcall TTotalForm::RemeasureExcute()
{
	int i = retest.re_index;
	int value = 0;
	for(;i<MAXCHANNEL;++i){
		value = i + 1;
		value = chReverseMap[value];
		switch(retest.cell[i]){
			case 2:	// IR 불량
				this->MakeData(3, "IR*", FormatFloat("000", value));
				if(tray.ocv_value[i] < config.ocv_min || tray.ocv_value[i] > config.ocv_max){
					retest.cell[i] = 3;
				}else{
					retest.re_index = ++i;
				}
				return;
            case 4:	// 접촉 불량
				this->MakeData(3, "IR*", FormatFloat("000", value));
				if(tray.ocv_value[i] < config.ocv_min || tray.ocv_value[i] > config.ocv_max){
					retest.cell[i] = 3;
				}
                else{
					retest.re_index = ++i;
				}
				return;
			case 3:	// OCV 불량
				this->MakeData(3, "OCV", FormatFloat("000", value));
                if(tray.after_value[i] == 999){
                    retest.cell[i] = 4;
                } else if(tray.after_value[i] < config.ir_min || tray.after_value[i] > config.ir_max){
					retest.cell[i] = 2;
				}
                retest.re_index = ++i;
				return;
			default:
				break;
		}
	}
    retest.re_excute = false;
    tray.rem_mode = 0; // Late IR/OCV replies must not publish the same result again.
    //* 2025 11 28 주석 처리 - SetRemeasureList를 2번 처리함.
	SetRemeasureListAfter();
	CmdForceStop();
	WriteCommLog("IR/OCV STOP", "RemeasureExcute()");
}

//---------------------------------------------------------------------------
// 결과 마감: STP/프로브 열림 요청 → NG·결과 코드·값·파일 작성 → COMPLETE → 자동 단계 완료 통지.
void __fastcall TTotalForm::CmdForceStop()
{
    if(resultCellSerialPending) return; // [CELL SERIAL 공통] AMF/정지 중복 통지 방지.
	// 검사종료	- Probe 해제 및 Tray 검사 대기
    MakeData(1, "STP");
    Panel_State->Caption = " IR/OCV Complete ... ";

	Mod_PLC->SetValue(PC_D_IROCV_PROB_OPEN, 1);
    WritePLCLog("CmdForceStop", "IROCV PROBE OPEN = 1");

    // [CELL SERIAL 공통] 상시 방식은 결과 저장 시점의 새 전체 수신 완료까지 기다린다.
    if(cellSerialContinuousReadForTray)
    {
        StartResultCellSerialRead();
        return;
    }
    SaveMeasurementResult();
}

//---------------------------------------------------------------------------
// [CELL SERIAL 공통] 시리얼 준비 이후의 공통 결과 마감. 저장 완료 후에만 COMPLETE를 출력한다.
void __fastcall TTotalForm::SaveMeasurementResult()
{
    BadInfomation();
    WritePLCLog("CmdForceStop", "Write BadInfomation");
    Sleep(50);
    WriteResultCode();
    WritePLCLog("CmdForceStop", "Write ResultCode");
    ReadCellInfo();

    Sleep(50);
    WriteIROCVValue();
    WritePLCLog("CmdForceStop", "Write IR, OCV Value");
    // [CELL SERIAL 공통] TRAY IN 방식은 보관본, 상시 방식은 직전 수신본을 사용한다.
    if(!cellSerialContinuousReadForTray && LoadTrayInfo(tray.trayid) == false)
        ReadCellSerial();
    // Write Result File
    WriteResultFile();
    Mod_PLC->SetValue(PC_D_IROCV_COMPLETE, 1);
    WritePLCLog("CmdForceStop", "PC_D_IROCV_COMPLETE = 1");
    SetAutoMeasureComplete();
}

//---------------------------------------------------------------------------
// 전체 재측정 요청: 트레이 ID를 유지하고 데이터 초기화·CELL DATA 재읽기 후 프로브 닫힘을 기다린다.
void __fastcall TTotalForm::StartFullRemeasure()
{
    if(!PrepareAutoRemeasure()) return;
    AnsiString trayId = tray.trayid;
    InitTrayStruct();
    tray.trayid = trayId;
    ReadAutoCellData();
    Mod_PLC->SetValue(PC_D_IROCV_PROB_CLOSE, 1);
    WritePLCLog("RemeasureAllBtnClick", "IROCV PROBE CLOSE = 1");
    retest.re_excute = false;
    VisibleBox(GrpMain);
}

//---------------------------------------------------------------------------
// 선택 재측정 요청: 기존 불량 목록을 사용하고 프로브 닫힘 확인 후 채널별 재측정을 시작한다.
void __fastcall TTotalForm::StartSelectedRemeasure()
{
    if(!PrepareAutoRemeasure()) return;
    tray.rem_mode = 1;
    retest.re_index = 0;
    retest.re_excute = true;
    Mod_PLC->SetValue(PC_D_IROCV_PROB_CLOSE, 1);
    WritePLCLog("RemeasureBtnClick", "IROCV PROBE CLOSE = 1");
    VisibleBox(GrpMain);
}


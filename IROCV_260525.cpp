//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop
#include <tchar.h>
//---------------------------------------------------------------------------
USEFORM("Modplc.cpp", Mod_PLC); /* TDataModule: File Type */
USEFORM("RVMO_main.cpp", BaseForm);
USEFORM("FormTotal.cpp", TotalForm);
USEFORM("FormCellIdError.cpp", Form_CellIdError);
USEFORM("FormError.cpp", Form_Error);
USEFORM("FormCalibration.cpp", CaliForm);
USEFORM("FormLanguage.cpp", Form_Language);
USEFORM("FormPLCInterface.cpp", Form_PLCInterface);
USEFORM("FormRemeasure.cpp", RemeasureForm);
USEFORM("FormMeasureInfo.cpp", MeasureInfoForm);
USEFORM("FormNgCountError.cpp", Form_NgCountError);
//---------------------------------------------------------------------------
int WINAPI _tWinMain(HINSTANCE, HINSTANCE, LPTSTR, int)
{
	HANDLE Mutex;
	try
	{
		const char ProgMutex[] = "IROCV";

		if((Mutex = OpenMutexA(MUTEX_ALL_ACCESS, false, ProgMutex)) == NULL)
			Mutex = CreateMutexA(NULL, true, ProgMutex);
		else
		{
			ShowMessage("The program is already running.");
			return 0;
		}

		Application->Initialize();
		Application->CreateForm(__classid(TBaseForm), &BaseForm);
		Application->CreateForm(__classid(TMeasureInfoForm), &MeasureInfoForm);
		Application->CreateForm(__classid(TRemeasureForm), &RemeasureForm);
		Application->CreateForm(__classid(TForm_PLCInterface), &Form_PLCInterface);
		Application->CreateForm(__classid(TMod_PLC), &Mod_PLC);
		Application->CreateForm(__classid(TCaliForm), &CaliForm);
		Application->CreateForm(__classid(TForm_Error), &Form_Error);
		Application->CreateForm(__classid(TForm_Language), &Form_Language);
		Application->CreateForm(__classid(TForm_NgCountError), &Form_NgCountError);
		Application->CreateForm(__classid(TForm_CellIdError), &Form_CellIdError);
		Application->Run();
	}
	catch (Exception &exception)
	{
		Application->ShowException(&exception);
	}
	catch (...)
	{
		try
		{
			throw Exception("");
		}
		catch (Exception &exception)
		{
			Application->ShowException(&exception);
		}
	}
	ReleaseMutex(Mutex);
	return 0;
}
//---------------------------------------------------------------------------

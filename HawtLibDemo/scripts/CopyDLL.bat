@echo off


IF exist ..\Build\Debug_DLL_Exe\Win32\Output ( echo Debug_DLL_Exe directory exists ) ELSE ( echo Creating Debug_DLL_Exe Dir && mkdir ..\Build\Debug_DLL_Exe\Win32\Output )
IF exist ..\Build\Release_DLL_Exe\Win32\Output ( echo Release_DLL_Exe directory exists ) ELSE ( echo Creating Release_DLL_Exe Dir && mkdir ..\Build\Release_DLL_Exe\Win32\Output )

IF exist ..\Build\Debug_DLL_Exe\x64\Output ( echo Debug_DLL_Exe directory exists ) ELSE ( echo Creating Debug_DLL_Exe Dir && mkdir ..\Build\Debug_DLL_Exe\x64\Output )
IF exist ..\Build\Release_DLL_Exe\x64\Output ( echo Release_DLL_Exe directory exists ) ELSE ( echo Creating Release_DLL_Exe Dir && mkdir ..\Build\Release_DLL_Exe\x64\Output )

echo Adding DLL Files...

xcopy ..\..\HawtLib\Build\Debug_DLL\Win32\Output\HawtLib.dll ..\Build\Debug_DLL_Exe\Win32\Output\ /Y
xcopy ..\..\HawtLib\Build\Release_DLL\Win32\Output\HawtLib.dll ..\Build\Release_DLL_Exe\Win32\Output\ /Y

xcopy ..\..\HawtLib\Build\Debug_DLL\x64\Output\HawtLib.dll ..\Build\Debug_DLL_Exe\x64\Output\ /Y
xcopy ..\..\HawtLib\Build\Release_DLL\x64\Output\HawtLib.dll ..\Build\Release_DLL_Exe\x64\Output\ /Y 

echo Done!

pause
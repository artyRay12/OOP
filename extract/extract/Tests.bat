@echo off

SET MyProgram="%~1"

REM Защита от запуска без аргумента
if %MyProgram%=="" (
	echo Please specify path to program
	exit /B 1
)

REM copy non empty file
%MyProgram% nonEmpty.txt "%TEMP%\output.txt" 0 13 || goto err
fc nonEmptyOutput.txt "%TEMP%\output.txt" > nul || goto err
echo test 2 passed

REM copy wrong name file
%MyProgram% wrongName.txt "%TEMP%\output.txt" 5 10 && goto err
echo test 3 passed

REM without some args
%MyProgram% "%TEMP%\output.txt" && goto err
echo test 4 passed

REM without args
%MyProgram% && goto err
echo test 5 passed

REM with zero fragment length
%MyProgram% input.txt "%TEMP%\output.txt" 10 0 ||goto err
echo test 6 passed

REM with zero fragment length < 0
%MyProgram% input.txt "%TEMP%\output.txt" 10 -5 || goto err
echo test 7 passed

REM without zero fragment start < 0
%MyProgram% input.txt "%TEMP%\output.txt" -10 5 || goto err
echo test 8 passed

REM Успешно
echo tests passed succesfull
exit /B 0

REM Ошибка
:err
echo error here
exit /B 1

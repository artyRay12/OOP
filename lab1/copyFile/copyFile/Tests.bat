@echo off

SET MyProgram="%~1"

REM Защита от запуска без аргумента
if %MyProgram%=="" (
	echo Please specify path to program
	exit /B 1
)

REM copy empty file
%MyProgram% Empty.txt "%TEMP%\output.txt" || goto err
fc Empty.txt "%TEMP%\output.txt" > nul || goto err
echo test 1 passed

REM copy non empty file
%MyProgram% nonEmpty.txt "%TEMP%\output.txt" || goto err
fc nonEmpty.txt "%TEMP%\output.txt" > nul || goto err
echo test 2 passed

REM copy wrong name file
%MyProgram% wrongName.txt "%TEMP%\output.txt" && goto err
echo test 3 passed

REM without some args
%MyProgram% "%TEMP%\output.txt" && goto err
echo test 4 passed

REM without args
%MyProgram% && goto err
echo test 5 passed

REM Успешно
echo tests passed succesfull
exit /B 0

REM Ошибка
:err
echo error here
exit /B 1

@echo off

SET MyProgram="%~1"

REM check arguments for bat
if %MyProgram%=="" (
	echo Please specify path to program
	exit /B 1
)
echo test 1 passed

REM all good
%MyProgram% 100 > "%TEMP%\output.txt" || goto err
fc nonEmptyOutput.txt "%TEMP%\output.txt" > nul || goto err
echo test 2 passed

REM so much args
%MyProgram% 1 4 && goto err
echo test 3 passed

REM without args
%MyProgram% && goto err
echo test 4 passed

REM arg > 250
%MyProgram% 300 && goto err
echo test 6 passed

REM arg < 0
%MyProgram% -50 && goto err
echo test 7 passed

REM arg is not digits
%MyProgram% notDigit && goto err
echo test 8 passed

REM =)
echo tests passed succesfull
exit /B 0

REM =(
:err
echo error here
exit /B 1
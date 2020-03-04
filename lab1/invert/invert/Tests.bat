@echo off

SET MyProgram="%~1"

REM check arguments for bat
if %MyProgram%=="" (
	echo Please specify path to program
	exit /B 1
)
echo test 1 passed

REM so much args
%MyProgram% "input.txt" "secondArgument.txt" && goto err
echo test 2 passed

REM matrix 3x4
%MyProgram% matrix3x4.txt && goto err
echo test 3 passed

REM =)
echo tests passed succesfull
exit /B 0

REM =(
:err
echo error here
exit /B 1
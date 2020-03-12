@echo off

SET MyProgram="%~1"
SET InputDir="%~2"
SET OutputDir="%~3"
SET IsArgsCorrect=T

REM check arguments for bat
if %MyProgram%=="" set IsArgsCorrect=F
if %OutputDir%=="" set IsArgsCorrect=F
if %InputDir%=="" set IsArgsCorrect=F

if %IsArgsCorrect%==F (
	echo Please specify path to program
	exit /B 1
)
echo test 1 passed

REM all is good
%MyProgram% %InputDir%\normal_map.txt > "%TEMP%\output.txt" || goto err
fc %OutputDir%\normal_map.txt "%TEMP%\output.txt" > nul || goto err
echo test 2 passed

REM so much args
%MyProgram% "input.txt" "secondArgument.txt" "another_argument" && goto err
echo test 3 passed

REM no args
%MyProgram% && goto err
echo test 4 passed

REM empty file
 %MyProgram% %InputDir%\empty_file && goto err
 echo test 5 passed

REM map 2x2
%MyProgram% %InputDir%\small_map.txt && goto err
echo test 6 passed

REM map bigger than 256
%MyProgram% %InputDir%\big_map.txt && goto err
echo test 7 passed

REM border with wrong letter
%MyProgram% %InputDir%\border_with_wrong_letter.txt && goto err
echo test 8 passed

REM map with different lines length
%MyProgram% %InputDir%\diffrent_lines_length.txt && goto err
echo test 9 passed


REM =)
echo tests passed succesfull
exit /B 0

REM =(
:err
echo error here
exit /B 1
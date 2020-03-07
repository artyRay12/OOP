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
%MyProgram% %InputDir%\input_matrix_3x3.txt > "%TEMP%\output.txt" || goto err
fc %OutputDir%\output_matrix_3x3.txt "%TEMP%\output.txt" > nul || goto err
echo test 2 passed

REM so much args
%MyProgram% "input.txt" "secondArgument.txt" && goto err
echo test 3 passed

REM no args
%MyProgram% && goto err
echo test 4 passed

REM matrix size != 3x3
%MyProgram% %InputDir%\input_matrix_3x4.txt && goto err
echo test 5 passed

REM empty file
 %MyProgram% %InputDir%\input_empty_file.txt && goto err
 echo test 6 passed

REM matrix with letters
%MyProgram% %InputDir%\input_matrix_with_letters.txt && goto err
echo test 7 passed


REM matrix with "digit + letter" instead digits
%MyProgram% %InputDir%\input_matrix_with_digit+letter.txt && goto err
echo test 8 passed

REM matrix with "digit + spaces" instead digits
%MyProgram% %InputDir%\input_matrix_with_digit+spaces.txt && goto err
echo test 9 passed

REM determinant = 0
%MyProgram% %InputDir%\input_matrix_where_det_is_zero.txt && goto err
echo test 10 passed



REM =)
echo tests passed succesfull
exit /B 0

REM =(
:err
echo error here
exit /B 1
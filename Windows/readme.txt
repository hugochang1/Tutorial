@echo off

REM ---------- sleep in second ---------- 
timeout 1 /nobreak > NUL


REM ---------- file exist ---------- 
IF EXIST test.bat echo file exist


REM ---------- file not exist ---------- 
IF NOT EXIST test.bat echo file not exist


REM ---------- for loop ---------- 
for /l %%x in (1, 1, 5) do (
   echo %%x
)

REM 1
REM 2
REM 3
REM 4
REM 5


REM ---------- for loop with break condition ---------- 
for /l %%x in (1, 1, 5) do (
   echo %%x
   if %%x==3 goto :tag1
)

:tag1
echo tag1

REM 1
REM 2
REM 3
REM tag1


REM ---------- goto loop with condition ---------- 
set i=1
:loop
if %i%==3 goto :tag2
echo %i%
set /a i += 1
goto :loop

:tag2
echo tag2

REM 1
REM 2
REM tag2

pause

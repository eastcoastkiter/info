@echo off
mkdir c:\MuB\info
copy info.exe c:\MuB\info\
xcopy scripts\*.* c:\MuB\info\scripts\

:choice
set /P c=Should I add info.exe to Autostart [y/n]?:
if /I "%c%" EQU "Y" goto :creg
if /I "%c%" EQU "N" goto :cexit
goto :choice


:creg
reg add HKEY_CURRENT_USER\Software\Microsoft\Windows\CurrentVersion\Run /v Info /d c:\Mub\info\info.exe


:cexit
echo Finished
pause


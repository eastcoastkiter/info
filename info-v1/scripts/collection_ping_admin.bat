@echo off
rem displayname: ping admin
rem tree: collection net 
rem author: Rene Storm
rem version: 1.0
echo Ping Hamburg
call scripts\network_ping_ger-ham-admin.bat
echo Ping Antwerp
call scripts\network_ping_bel-ant-admin.bat
echo Ping Singpore
call scripts\network_ping_sg-dcr-admin.bat
echo Ping Houston
call scripts\network_ping_us-hou-admin.bat
echo Ping Mumbai
call scripts\network_ping_in-mum-admin.bat

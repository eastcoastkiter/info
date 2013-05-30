@echo off
rem displayname: net info
rem tree: collection net 
rem author: Rene Storm
rem version: 1.0
call scripts\network_ipconfig_all.bat
call scripts\network_netsh_config.bat

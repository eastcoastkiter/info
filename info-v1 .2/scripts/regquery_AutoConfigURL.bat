@echo off
rem displayname: show AutoConfigURL
rem tree: system proxy
rem author: Rene Storm
rem version: 1.0
reg query "HKEY_CURRENT_USER\Software\Microsoft\Windows\CurrentVersion\Internet Settings" /v AutoConfigURL

@echo off
rem displayname: show language
rem tree: system
rem author: Rene Storm
rem version: 1.0
echo "0409 --> English"
echo "0407 --> German"
reg query "hklm\system\controlset001\control\nls\language" /v Installlanguage

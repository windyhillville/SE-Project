@echo off
cd /d %~dp0\backend\src  
start "" Elysium_server.exe
timeout /t 2 > nul
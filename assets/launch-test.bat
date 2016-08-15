@echo off

set SERVERIP=192.168.88.209
set COMPANYID=1d8ebcd5-780d-49dc-bc2a-e8f19e8f8ac6
set DEVICEID=0811a6a0-f447-4088-aa75-932ade89434d
set USERID=450f940a-8c00-11e8-9eb6-529269fb1459
set SESSIONTYPE=CSS
set BINPATH="%PROGRAMFILES(x86)%\\Quicktech\\Quicktech Viewer\\QuicktechViewer.exe"

call .\launch.bat %SERVERIP% %COMPANYID% %DEVICEID% %USERID% %SESSIONTYPE% %BINPATH%
goto :eof
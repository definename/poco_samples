@echo off

rem *****************
rem Parses arguments
rem *****************

set SERVER_IP=%1
if "%SERVER_IP%"=="" goto invalid_server_ip
set COMPNAY_ID=%2
if "%COMPNAY_ID%"=="" goto invalid_company_id
set DEVICE_ID=%3
if "%DEVICE_ID%"=="" goto invalid_device_id
set USER_ID=%4
if "%USER_ID%"=="" goto invalid_user_id
set SESSION_TYPE=%5
if "%SESSION_TYPE%"=="" goto invalid_session_type
set BIN_PATH=%6
if not exist %BIN_PATH% goto invalid_bin_path

rem *******************
rem Starts qt-launcher
rem *******************

set ARGS=/serverIp=%SERVER_IP% /companyId=%COMPNAY_ID% /deviceId=%DEVICE_ID% /userId=%USER_ID% /sessionType=%SESSION_TYPE% /binPath=%BIN_PATH%
echo [*] qt-launcher is being started
echo [*] Command line arguments are: %ARGS%

start "Quicktech viewer" /d . /b /wait qt-launcher.exe %ARGS%

goto :eof

rem ***********************
rem Error processing block
rem ***********************

:invalid_server_ip
echo [-] Invalid server ip address
goto exit_error

:invalid_company_id
echo [-] Invalid compnay id
goto exit_error

:invalid_device_id
echo [-] Invalid device id
goto exit_error

:invalid_user_id
echo [-] Invalid user id
goto exit_error

:invalid_session_type
echo [-] Invalid session type
goto exit_error

:invalid_bin_path
echo [-] Invalid binary path
goto exit_error

:exit_error
echo [-] Unable to execute command file, see above and correct
exit /b

@echo off

if [%1] == [client] (
    call:client
) else if [%1] == [clean] (
    call:clean
) else (
    call:error
)

goto done



:client
cl /c /EHsc /Foclient.obj client.cpp
link /out:client.exe client.obj Ws2_32.lib
goto:eof

:clean
set del_list=client.obj client.exe
for %%i in (%del_list%) do (
    if exist %%i (
        del %%i
    )
)
goto:eof

:error
echo Invalid arguments
goto:eof


:done
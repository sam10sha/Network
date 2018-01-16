@echo off

if [%1] == [clean] (
	call:clean
) else if [%1] == [network] (
	call:network
) else if [%1] == [client] (
	call:client
) else if [%1] == [temp] (
	call:temp
) else (
	call:error
)

goto done

:clean
del *.obj *.exe
goto:eof

:network
cl /EHsc network.cpp Ws2_32.lib
goto:eof

:client
cl /EHsc client.cpp Ws2_32.lib
goto:eof

:temp
cl /EHsc temp.cpp Ws2_32.lib /Fotemp.obj
link /out:temp.exe temp.obj
goto:eof

:error
echo Invalid argument provided
goto:eof

:done
@echo off

if [%1] == [clean] (
	goto clean
) else if [%1] == [network] (
	goto network
) else if [%1] == [client] (
	goto client
) else (
	goto error
)

:clean
del *.obj *.exe
goto done

:network
cl /EHsc network.cpp Ws2_32.lib
goto done

:client
cl /EHsc client.cpp Ws2_32.lib
goto done

:error
echo Invalid argument provided
goto done

:done
@rem mexmake.bat %1 %2 %3
@rem
@rem %1 -- cpp file to build
@rem %2 -- destination folder for mex
@rem %3 -- additional libraries
@rem

@echo %~n1

@call kill %2/%~n1.dll

@if exist %2/%~n1.dll goto error1

@call "%matlab%\bin\win32\mex.bat" -v -g -f msvc80opts.bat -I../../code -L../../lib -lmaxplus -lexttype -outdir %2 -output %~n1 %1 ../../code/mex/mexargs.cpp >%~n1.log

@fsutil hardlink create %2/%~n1.dll %2/%~n1.mexw32
goto end
:error1
@echo ACSESS ERROR
:end
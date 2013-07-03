
set FROMPATH=..\projects\LibraryMakeProject\debug\

copy %FROMPATH%*.exe .

ping -n 8 127.0.0.1 > nul

end
if not exist ..\..\out mkdir ..\..\out
if not exist ..\..\out\builtins mkdir ..\..\out\builtins
if not exist ..\..\out\scaffold mkdir ..\..\out\scaffold
xcopy /Y ..\..\deps\SDL\VisualC\SDL\Win32\%1\*.dll ..\..\out
xcopy /Y ..\..\src\lib\*.js ..\..\out\builtins
xcopy /Y ..\..\src\scaffold\* ..\..\out\scaffold
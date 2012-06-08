if not exist ..\..\out mkdir ..\..\out
if not exist ..\..\out\builtins mkdir ..\..\out\builtins
xcopy /Y ..\..\deps\SDL\VisualC\SDL\Win32\%1\*.dll ..\..\out
xcopy /Y ..\..\src\lib\*.js ..\..\out\builtins
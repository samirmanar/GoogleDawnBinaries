
:: Extract date parts (locale-dependent)
for /f "tokens=2-4 delims=/ " %%a in ('date /t') do (
  set mm=%%a
  set dd=%%b
  set yyyy=%%c
)
set Date=%yyyy%-%mm%-%dd%


xcopy "dawn\include\webgpu" "releases\Debug\include\webgpu" /E /I /Y
xcopy "dawn\out\Debug\gen\include\dawn" "releases\Debug\include\dawn" /E /I /Y
xcopy "dawn\out\Debug\gen\include\webgpu" "releases\Debug\include\webgpu" /E /I /Y

xcopy "dawn\out\Debug\src\dawn\native\webgpu_dawn.lib" "releases\Debug\lib\" /Y /I

xcopy "dawn\out\Debug\webgpu_dawn.dll" "releases\Debug\bin\" /Y /I


:: Zip the Debug build
"C:\Program Files\7-Zip\7z.exe" a releases\dawn_debug_%Date%_win_x64.zip .\releases\Debug\*


xcopy "dawn\include\webgpu" "releases\Release\include\webgpu" /E /I /Y
xcopy "dawn\out\Release\gen\include\dawn" "releases\Release\include\dawn" /E /I /Y
xcopy "dawn\out\Release\gen\include\webgpu" "releases\Release\include\webgpu" /E /I /Y

xcopy "dawn\out\Release\src\dawn\native\webgpu_dawn.lib" "releases\Release\lib\" /Y /I

xcopy "dawn\out\Release\webgpu_dawn.dll" "releases\Release\bin\" /Y /I

:: Zip the Release build
"C:\Program Files\7-Zip\7z.exe" a releases\dawn_release_%Date%_win_x64.zip .\releases\Release\*


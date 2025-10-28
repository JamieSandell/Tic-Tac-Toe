@echo off

pushd build
cl ..\code\win32_ttt.c /MTd /nologo /Od /std:c17 /TC /W4 /WX /wd4100 /wd4189 /ZI /link gdi32.lib user32.lib /INCREMENTAL:NO
popd
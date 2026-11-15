echo off

rem     BUILD.BAT
rem     Written by Sarin/!ArisE!

cls
echo ONYX 3D system v2 (dos+watcom version)
echo ÿ
echo The system is about to compile.
rem @pause
cls
echo ONYX 3D system v2 (dos+watcom version)
echo ÿ
echo ------------------------------------------------------------
echo Making ONYX 3D system library
echo ------------------------------------------------------------

echo    .math           Math engine
cd source\math
if exist math.lib del math.lib >>err
wmake >err
copy math.lib ..\..\lib\math.lib >err
del math.lib >err
if exist err del err

echo    .low-lev        VESA 1.2 driver
cd ..\low-lev
if exist low-lev.lib delete low-lev.lib
wmake >err
copy low-lev.lib ..\..\lib\low-lev.lib >err
del low-lev.lib >err
if exist err del err

echo    .video          Video procedures
cd ..\video
if exist video.lib del video.lib >>err
wmake >>err
copy video.lib ..\..\lib\video.lib >err
rem del video.lib >err
del err

echo    .engine3d       3d engine
cd ..\engine3d
if exist engine3d.lib del engine3d.lib
wmake >err
copy engine3d.lib ..\..\lib\engine3d.lib >err
rem del engine3d.lib >err
if exist err del err

echo    .misc           Other stuff
cd ..\misc
if exist misc.lib del misc.lib
wmake >err
copy misc.lib ..\..\lib\misc.lib >err
rem del misc.lib >err
if exist err del err

echo ÿ
echo            Linking onyx3d lib
cd ..\..\lib
if exist onyx3d.lib del onyx3d.lib
wlib -n onyx3d +low-lev.lib +math.lib +video.lib +engine3d.lib +misc.lib >err

del low-lev.lib
del math.lib
del video.lib
del engine3d.lib
del misc.lib
if exist err del err

echo ÿ
echo    .examples       Examples
echo        .cubes      Two rotated, textured, shaded and z-buffered cubes
cd ..\examples\cubes
wmake >err
if exist err del err
cd ..
echo        .a0         Simple object loading & rotating (EOS needed)
cd a0
wmake >err
if exist err del err
cd ..
echo        .onx        ONX file loading
cd onx
wmake >err
if exist err del err
cd ..
echo        .rotor      Playboy's(r) girl
cd rotor
call rotor.bat
if exist err del err
cd ..

echo        .rotor      Playboy's(r) girl
cd loadtst
wmake >err
if exist err del err
cd ..\..


echo ÿ
echo ------------------------------------------------------------

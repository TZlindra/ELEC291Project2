@echo off
::This file was created automatically by CrossIDE to compile with C51.
C:
cd "\UBC\SECOND YEAR\ELEC 291\Project 2\ELEC291Project2\STM32\Controller\"
"C:\CrossIDE\Call51\Bin\c51.exe" --use-stdout  "C:\UBC\SECOND YEAR\ELEC 291\Project 2\ELEC291Project2\STM32\Controller\testmovement.c"
if not exist hex2mif.exe goto done
if exist testmovement.ihx hex2mif testmovement.ihx
if exist testmovement.hex hex2mif testmovement.hex
:done
echo done
echo Crosside_Action Set_Hex_File C:\UBC\SECOND YEAR\ELEC 291\Project 2\ELEC291Project2\STM32\Controller\testmovement.hex

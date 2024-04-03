@echo off
::This file was created automatically by CrossIDE to compile with C51.
C:
cd "\UBC\SECOND YEAR\ELEC 291\Project 2\ELEC291Project2\EFM8\Examples\All_timers\"
"C:\CrossIDE\Call51\Bin\c51.exe" --use-stdout  "C:\UBC\SECOND YEAR\ELEC 291\Project 2\ELEC291Project2\EFM8\Examples\All_timers\All_timers.c"
if not exist hex2mif.exe goto done
if exist All_timers.ihx hex2mif All_timers.ihx
if exist All_timers.hex hex2mif All_timers.hex
:done
echo done
echo Crosside_Action Set_Hex_File C:\UBC\SECOND YEAR\ELEC 291\Project 2\ELEC291Project2\EFM8\Examples\All_timers\All_timers.hex

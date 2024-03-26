@echo off
::This file was created automatically by CrossIDE to compile with C51.
C:
cd "\UBC\SECOND YEAR\ELEC 291\Project 2\ELEC291Project2\EFM8\Robot\"
"C:\CrossIDE\Call51\Bin\c51.exe" --use-stdout  "C:\UBC\SECOND YEAR\ELEC 291\Project 2\ELEC291Project2\EFM8\Robot\movement_new.c"
if not exist hex2mif.exe goto done
if exist movement_new.ihx hex2mif movement_new.ihx
if exist movement_new.hex hex2mif movement_new.hex
:done
echo done
echo Crosside_Action Set_Hex_File C:\UBC\SECOND YEAR\ELEC 291\Project 2\ELEC291Project2\EFM8\Robot\movement_new.hex

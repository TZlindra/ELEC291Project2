@echo off
::This file was created automatically by CrossIDE to compile with C51.
C:
cd "\Muntakim_Files\School\School_Work\Engineering_Bachelors\2023\ELEC_291\Projects\Project_2\ELEC291Project2\EFM8\Robot\Source_Code\"
"C:\CrossIDE\Call51\Bin\c51.exe" --use-stdout  "C:\Muntakim_Files\School\School_Work\Engineering_Bachelors\2023\ELEC_291\Projects\Project_2\ELEC291Project2\EFM8\Robot\Source_Code\movement_new_new.c"
if not exist hex2mif.exe goto done
if exist movement_new_new.ihx hex2mif movement_new_new.ihx
if exist movement_new_new.hex hex2mif movement_new_new.hex
:done
echo done
echo Crosside_Action Set_Hex_File C:\Muntakim_Files\School\School_Work\Engineering_Bachelors\2023\ELEC_291\Projects\Project_2\ELEC291Project2\EFM8\Robot\Source_Code\movement_new_new.hex

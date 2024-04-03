@echo off
::This file was created automatically by CrossIDE to compile with C51.
C:
cd "\Muntakim_Files\School\School_Work\Engineering_Bachelors\2023\ELEC_291\Projects\Project_2\ELEC291Project2\EFM8\Examples\Robot_Base\"
"C:\CrossIDE\Call51\Bin\c51.exe" --use-stdout  "C:\Muntakim_Files\School\School_Work\Engineering_Bachelors\2023\ELEC_291\Projects\Project_2\ELEC291Project2\EFM8\Examples\Robot_Base\Robot_Base.c"
if not exist hex2mif.exe goto done
if exist Robot_Base.ihx hex2mif Robot_Base.ihx
if exist Robot_Base.hex hex2mif Robot_Base.hex
:done
echo done
echo Crosside_Action Set_Hex_File C:\Muntakim_Files\School\School_Work\Engineering_Bachelors\2023\ELEC_291\Projects\Project_2\ELEC291Project2\EFM8\Examples\Robot_Base\Robot_Base.hex

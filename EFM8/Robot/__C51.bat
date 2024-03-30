@echo off
::This file was created automatically by CrossIDE to compile with C51.
C:
cd "\Muntakim_Files\School\School_Work\Engineering_Bachelors\2023\ELEC_291\Projects\Project_2\ELEC291Project2\EFM8\Robot\"
"C:\CrossIDE\Call51\Bin\c51.exe" --use-stdout  "C:\Muntakim_Files\School\School_Work\Engineering_Bachelors\2023\ELEC_291\Projects\Project_2\ELEC291Project2\EFM8\Robot\test_timers.c"
if not exist hex2mif.exe goto done
if exist test_timers.ihx hex2mif test_timers.ihx
if exist test_timers.hex hex2mif test_timers.hex
:done
echo done
echo Crosside_Action Set_Hex_File C:\Muntakim_Files\School\School_Work\Engineering_Bachelors\2023\ELEC_291\Projects\Project_2\ELEC291Project2\EFM8\Robot\test_timers.hex

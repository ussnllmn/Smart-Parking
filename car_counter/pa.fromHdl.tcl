
# PlanAhead Launch Script for Pre-Synthesis Floorplanning, created by Project Navigator

create_project -name car_counter -dir "C:/xilinx_workspace/car_counter/planAhead_run_1" -part xc6slx9tqg144-3
set_param project.pinAheadLayout yes
set srcset [get_property srcset [current_run -impl]]
set_property target_constrs_file "counter_4bit.ucf" [current_fileset -constrset]
set hdlfile [add_files [list {counter_4bit.vhd}]]
set_property file_type VHDL $hdlfile
set_property library work $hdlfile
set_property top counter_4bit $srcset
add_files [list {counter_4bit.ucf}] -fileset [get_property constrset [current_run]]
open_rtl_design -part xc6slx9tqg144-3

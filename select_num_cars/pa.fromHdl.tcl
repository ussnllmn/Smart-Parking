
# PlanAhead Launch Script for Pre-Synthesis Floorplanning, created by Project Navigator

create_project -name select_num_cars -dir "C:/xilinx_workspace/select_num_cars/planAhead_run_1" -part xc6slx9tqg144-2
set_param project.pinAheadLayout yes
set srcset [get_property srcset [current_run -impl]]
set_property target_constrs_file "select_num_cars.ucf" [current_fileset -constrset]
set hdlfile [add_files [list {select_num_cars.vhd}]]
set_property file_type VHDL $hdlfile
set_property library work $hdlfile
set_property top select_num_cars $srcset
add_files [list {select_num_cars.ucf}] -fileset [get_property constrset [current_run]]
open_rtl_design -part xc6slx9tqg144-2


# PlanAhead Launch Script for Pre-Synthesis Floorplanning, created by Project Navigator

create_project -name parking_fpga -dir "C:/xilinx_workspace/parking_fpga/planAhead_run_1" -part xc6slx9tqg144-3
set_param project.pinAheadLayout yes
set srcset [get_property srcset [current_run -impl]]
set_property target_constrs_file "parkingEncoder.ucf" [current_fileset -constrset]
set hdlfile [add_files [list {parkingEncoder.vhd}]]
set_property file_type VHDL $hdlfile
set_property library work $hdlfile
set_property top parkingEncoder $srcset
add_files [list {parkingEncoder.ucf}] -fileset [get_property constrset [current_run]]
open_rtl_design -part xc6slx9tqg144-3

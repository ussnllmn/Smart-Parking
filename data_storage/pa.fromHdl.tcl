
# PlanAhead Launch Script for Pre-Synthesis Floorplanning, created by Project Navigator

create_project -name data_storage -dir "C:/xilinx_workspace/data_storage/planAhead_run_1" -part xc6slx9tqg144-2
set_param project.pinAheadLayout yes
set srcset [get_property srcset [current_run -impl]]
set_property target_constrs_file "d_flipflop_4outbit.ucf" [current_fileset -constrset]
set hdlfile [add_files [list {d_flipflop_4outbit.vhd}]]
set_property file_type VHDL $hdlfile
set_property library work $hdlfile
set_property top d_flipflop_4outbit $srcset
add_files [list {d_flipflop_4outbit.ucf}] -fileset [get_property constrset [current_run]]
open_rtl_design -part xc6slx9tqg144-2

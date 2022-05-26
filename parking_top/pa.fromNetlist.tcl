
# PlanAhead Launch Script for Post-Synthesis pin planning, created by Project Navigator

create_project -name parking_top -dir "C:/xilinx_workspace/parking_top/planAhead_run_1" -part xc6slx9tqg144-2
set_property design_mode GateLvl [get_property srcset [current_run -impl]]
set_property edif_top_file "C:/xilinx_workspace/parking_top/parking_top.ngc" [ get_property srcset [ current_run ] ]
add_files -norecurse { {C:/xilinx_workspace/parking_top} }
set_param project.pinAheadLayout  yes
set_property target_constrs_file "parking_top.ucf" [current_fileset -constrset]
add_files [list {parking_top.ucf}] -fileset [get_property constrset [current_run]]
link_design

transcript on
if {[file exists gate_work]} {
	vdel -lib gate_work -all
}
vlib gate_work
vmap work gate_work

vlog -vlog01compat -work work +incdir+. {ALU.vo}

vlog -vlog01compat -work work +incdir+C:/Users/wilso/Documents/courses/1112/Digital\ Circuit/Lab6 {C:/Users/wilso/Documents/courses/1112/Digital Circuit/Lab6/test.v}

vsim -t 1ps +transport_int_delays +transport_path_delays -L altera_ver -L cycloneiii_ver -L gate_work -L work -voptargs="+acc" test

add wave *
view structure
view signals
run 1 us

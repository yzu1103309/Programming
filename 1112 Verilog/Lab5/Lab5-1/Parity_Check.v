module Parity_Check(clk, Din, rst, Qout);

	input clk, rst, Din;
	output reg Qout;
	
	//Declare
	parameter
		S0 = 1'b0,
		S1 = 1'b1;
	
	reg CS; //Current State
	reg NS; //Next state
	
	always @ (posedge clk or posedge rst)
	begin
		if(rst == 1'b1)
			CS = S0;
		else
			CS = NS;
	end
		
	always @ (CS or Din)
	begin
		case (CS)
			S0 : 
			begin
				Qout = 1'b0;
				if(Din == 1'b0)
					NS = S0;
				else
					NS = S1;
			end
			
			S1: 
			begin
				Qout = 1'b1;
				if(Din == 1'b0)
					NS = S1;
				else 
					NS = S0;
			end
		endcase
	end
endmodule 
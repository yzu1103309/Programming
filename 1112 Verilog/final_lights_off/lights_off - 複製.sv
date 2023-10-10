module lights_off(sw, lights);
	reg [9:0] pos_en = 10'b0000000000;
	reg [9:0] neg_en = 10'b0000000000;
	input [9:0] sw;
	reg [9:0] last = 10'b0000000000;
	output reg [9:0] lights = 10'b0000000000;
	parameter [9:0] 
		c9 = 10'b1100000000,
		c8 = 10'b1110000000,
		c7 = 10'b0111000000;
		
	
	always@(posedge sw[9])
	begin 
		pos_en[9] = ~pos_en[9];
	end	
	
	always @(negedge sw[9])
	begin
		neg_en[9] = ~neg_en[9];
	end
	
	wire sel = pos_en[9] ^ neg_en[9];
	
	always @ (pos_en)
	begin
		begin lights = lights ^ c9; end
	end
endmodule

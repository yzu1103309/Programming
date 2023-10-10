	module lights_off(sw, lights, clk, btn_fix, btn_rand);
	input [9:0] sw;
	input clk, btn_fix, btn_rand;
	reg fix_last = 0;
	reg [9:0] change = 10'b0000000000;
	reg [9:0] last = 10'b0000000000;
	reg [9:0] rd = 10'b0000000000;
	reg [9:0] rd_save = 10'b0000000000;
	reg [23:0] fr;
	output reg [9:0] lights = 10'b0000000000;
	parameter [9:0] 
		c9 = 10'b1100000000,
		c8 = 10'b1110000000,
		c7 = 10'b0111000000,
		c6 = 10'b0011100000,
		c5 = 10'b0001110000,
		c4 = 10'b0000111000,
		c3 = 10'b0000011100,
		c2 = 10'b0000001110,
		c1 = 10'b0000000111,
		c0 = 10'b0000000011;
	
	parameter [9:0]
		q1 = 10'b1100000001,
		q2 = 10'b0111111110;
		
	reg[6:0] seg [10:0]; //存盤7段數碼管譯碼資料
	initial 
	begin
		seg[0] = 7'b0000001;   //  0
		seg[1] = 7'b1001111;   //  1
		seg[2] = 7'b0010010;   //  2
		seg[3] = 7'b0000110;   //  3
		seg[4] = 7'b1001100;   //  4
		seg[5] = 7'b0100100;   //  5
		seg[6] = 7'b0100000;   //  6
		seg[7] = 7'b0001111;   //  7
		seg[8] = 7'b0000000;   //  8
		seg[9] = 7'b0000100;   //  9
		seg[10]= 7'b0111000;   //  F
	end

	always @ (posedge clk) 
	begin
	
		rd += 1;
		fr += 1;
		
		if(~btn_fix)
		begin
			lights = q2;
		end
		
		if(~btn_rand)
		begin
			lights = rd[0]*c0 ^ rd[1]*c1 ^ rd[2]*c2 ^ rd[3]*c3 ^ rd[4]*c4 ^ rd[5]*c5 ^ rd[6]*c6 ^ rd[7]*c7 ^ rd[8]*c8 ^ rd[9]*c9;
		end
	
		if(sw[9] != last[9])
		begin
			last[9] = sw[9];
			change[9] = 1;	
		end
		if(sw[8] != last[8])
		begin
			last[8] = sw[8];
			change[8] = 1;	
		end
		if(sw[7] != last[7])
		begin
			last[7] = sw[7];
			change[7] = 1;	
		end
		if(sw[6] != last[6])
		begin
			last[6] = sw[6];
			change[6] = 1;	
		end
		if(sw[5] != last[5])
		begin
			last[5] = sw[5];
			change[5] = 1;	
		end
		if(sw[4] != last[4])
		begin
			last[4] = sw[4];
			change[4] = 1;	
		end
		if(sw[3] != last[3])
		begin
			last[3] = sw[3];
			change[3] = 1;	
		end
		if(sw[2] != last[2])
		begin
			last[2] = sw[2];
			change[2] = 1;	
		end
		if(sw[1] != last[1])
		begin
			last[1] = sw[1];
			change[1] = 1;	
		end
		if(sw[0] != last[0])
		begin
			last[0] = sw[0];
			change[0] = 1;	
		end
		
		if(fr == 24'b111111111111111111111111)
		begin
			lights = lights ^ change[0]*c0 ^ change[1]*c1 ^ change[2]*c2 ^ change[3]*c3 ^ change[4]*c4 ^ change[5]*c5 ^ change[6]*c6 ^ change[7]*c7 ^ change[8]*c8 ^ change[9]*c9;
			change = 10'b0000000000;
		end
	end
endmodule

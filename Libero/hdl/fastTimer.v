// timerInterrupts.v
module fastTimer(
			pclk,
			nreset,
            fabint
            );
	
input pclk, nreset;
output reg fabint;

reg [31:0] counter;
reg [31:0] nextCounter;

always@ (posedge pclk)
begin
	if(~nreset)
	begin
  		fabint = 1'b0;
		counter = 32'd0;
	end
	else
	begin
		nextCounter = nextCounter + 1;
		if(nextCounter == 32'd10000000)
		begin
			fabint = 1'b1;
			nextCounter = 32'd0;
		end
		else
		begin
			fabint = 1'b0;
		end
		counter = nextCounter;
	end
end
  
endmodule
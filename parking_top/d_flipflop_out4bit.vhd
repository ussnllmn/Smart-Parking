----------------------------------------------------------------------------------
-- Company: 
-- Engineer: 
-- 
-- Create Date:    06:30:21 05/25/2022 
-- Design Name: 
-- Module Name:    d_flipflop_out4bit - Behavioral 
-- Project Name: 
-- Target Devices: 
-- Tool versions: 
-- Description: 
--
-- Dependencies: 
--
-- Revision: 
-- Revision 0.01 - File Created
-- Additional Comments: 
--
----------------------------------------------------------------------------------
library IEEE;
use IEEE.STD_LOGIC_1164.ALL;

-- Uncomment the following library declaration if using
-- arithmetic functions with Signed or Unsigned values
--use IEEE.NUMERIC_STD.ALL;

-- Uncomment the following library declaration if instantiating
-- any Xilinx primitives in this code.
--library UNISIM;
--use UNISIM.VComponents.all;

entity d_flipflop_out4bit is
    Port ( D : in  STD_LOGIC_VECTOR (3 downto 0);
           clk : in  STD_LOGIC;
           rst : in  STD_LOGIC;
           Q : out  STD_LOGIC_VECTOR (3 downto 0));
end d_flipflop_out4bit;

architecture Behavioral of d_flipflop_out4bit is

begin
	process(clk, rst)
	begin
		if(rst='1') then 
		Q <= "0000";
		elsif(clk'event and clk = '1') then
		Q <= D;
		end if;
	end process;

end Behavioral;


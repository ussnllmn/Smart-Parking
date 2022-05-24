----------------------------------------------------------------------------------
-- Company: 
-- Engineer: 
-- 
-- Create Date:    02:36:03 05/25/2022 
-- Design Name: 
-- Module Name:    select_num_cars - Behavioral 
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

entity select_num_cars is
    Port ( D0 : in  STD_LOGIC_VECTOR (3 downto 0);
           D1 : in  STD_LOGIC_VECTOR (3 downto 0);
           S0 : in  STD_LOGIC;
           Z : out  STD_LOGIC_VECTOR (3 downto 0));
end select_num_cars;

architecture Behavioral of select_num_cars is

begin
	process (D0, D1, S0) is
	begin
		if (S0 ='0') then
			Z <= D0;
		else
			Z <= D1;
		end if;
	end process;

end Behavioral;


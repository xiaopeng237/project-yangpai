--MB_PAR_NONE,  0              /*!< No parity. */
--MB_PAR_ODD,   1              /*!< Odd parity. */
--MB_PAR_EVEN   2              /*!< Even parity. */

lua_reg_nums        = 130
lua_reg_start       = 0001
lua_slave_id        = 0x13
lua_slave_port      = 1
lua_slave_baudrate  = 9600
lua_slave_parity    = 0

function setShare_rtu(...)
	local args = {...}
	for i=1,#args do
		print(args[i])
	end
end
; Memory
; ===================
:cursor
DAT 0x0000




; Functions
; ====================


:write_hex
SET PUSH, B
SET B, A
SHR A, 0x0C
JSR to_string
SET A, B
SHL A, 0x04
SHR A, 0x0C
JSR to_string
SET A, B
SHL A, 0x08
SHR A, 0x0C
JSR to_string
SET A, B
SHL A, 0x0C
SHR A, 0x0C
JSR to_string
SET B, POP
SET PC, POP

:to_string
SET PUSH, X
SET X, [cursor]
ADD X, screen_data
IFE A, 0x0000
	SET [X], 0xA030
IFE A, 0x0001
	SET [X], 0xA031
IFE A, 0x0002
	SET [X], 0xA032
IFE A, 0x0003
	SET [X], 0xA033
IFE A, 0x0004
	SET [X], 0xA034
IFE A, 0x0005
	SET [X], 0xA035
IFE A, 0x0006
	SET [X], 0xA036
IFE A, 0x0007
	SET [X], 0xA037
IFE A, 0x0008
	SET [X], 0xA038
IFE A, 0x0009
	SET [X], 0xA039
IFE A, 0x000A
	SET [X], 0xA041
IFE A, 0x000B
	SET [X], 0xA042
IFE A, 0x000C
	SET [X], 0xA043
IFE A, 0x000D
	SET [X], 0xA044
IFE A, 0x000E
	SET [X], 0xA045
IFE A, 0x000F
	SET [X], 0xA046

ADD [cursor], 0x0001

SET X, POP
SET PC, POP

:write_string
SET PUSH, I
SET PUSH, J
SET PUSH, B
SET PUSH, X
SET X, [cursor]
ADD X, [video_ram]
SET I, X
SET J, A
:write_string_loop
SET B, [J]
BOR B, Z
SET [I], B
ADD I, 1
ADD J, 1
ADD [cursor], 0x0001
IFN [J], 0
	SET PC, write_string_loop
SET X, POP
SET B, POP
SET J, POP
SET I, POP
SET PC, POP

; New Line function
; Resets cursor to the begining of the next line.
; Moves to top of screen without clearing if used at bottom
; touches no registers.

:newline
SET PUSH, B
SET PUSH, C
SET C, [cursor]
MOD C, 32
SET B, 32
SUB B, C
ADD [cursor], B
IFG [cursor], 0x0179
	SET [cursor], 0x0000
SET C, POP
SET B, POP
SET PC, POP



; Memory
; ===================
:cursor
DAT 0x0000
:termwidth
DAT 0x0020
:termheight
DAT 0x000C
:negative_flag
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
; =========
; End write_hex

:write_decimal
SET PUSH, B
SET PUSH, C
SET PUSH, I
SET PUSH, Y
SET PUSH, X
IFE J, 0
	SET J, 5
IFG J, 5
	SET J, 5
SET Y, 1
SET X, [video_ram]
ADD X, [cursor]

:clear_previous_loop
ADD X, 1
SET [X], 0x0000
ADD Y, 1
IFN Y, J
	SET PC, clear_previous_loop
ADD [cursor], J
SET I, 1
SET C, A
:decimalloop
SET B, C
MOD B, 10
SET A, B
JSR to_string
SUB [cursor], 2
DIV C, 10
ADD I, 1
IFN C, 0
	SET PC, decimalloop
ADD [cursor], I
SET X, POP
SET Y, POP
SET I, POP
SET C, POP
SET B, POP
SET PC, POP
; =========
; End write_decimal


:to_string
SET PUSH, X
SET PUSH, Y
SET X, [cursor]
ADD X, [video_ram]
IFE A, 0x0000
	SET Y, 0x0030
IFE A, 0x0001
	SET Y, 0x0031
IFE A, 0x0002
	SET Y, 0x0032
IFE A, 0x0003
	SET Y, 0x0033
IFE A, 0x0004
	SET Y, 0x0034
IFE A, 0x0005
	SET Y, 0x0035
IFE A, 0x0006
	SET Y, 0x0036
IFE A, 0x0007
	SET Y, 0x0037
IFE A, 0x0008
	SET Y, 0x0038
IFE A, 0x0009
	SET Y, 0x0039
IFE A, 0x000A
	SET Y, 0x0041
IFE A, 0x000B
	SET Y, 0x0042
IFE A, 0x000C
	SET Y, 0x0043
IFE A, 0x000D
	SET Y, 0x0044
IFE A, 0x000E
	SET Y, 0x0045
IFE A, 0x000F
	SET Y, 0x0046
IFE Z, 0x0000
	SET Z, 0xA000
BOR Y, Z
SET [X], Y
ADD [cursor], 0x0001
SET Y, POP
SET X, POP
SET PC, POP
; =========
; End to_string

:write_blank_line
SET A, str_blank_line
JSR write_string
SET PC, POP
; =========
; End write_blank_line

:clear_screen
SET [cursor], 0x0000
SET PUSH, I
SET PUSH, J
SET I, [video_ram]
SET J, 0x180
ADD J, I
:clear_screen_loop
SET [I], 0x20
ADD I, 1
IFN I, J
	SET PC, clear_screen_loop
SET J, POP
SET I, POP
SET PC, POP
; =========
; End clear_screen

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
IFE Z, 0x0000
	BOR B, 0x7000
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
; =========
; End write_string

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
IFE C, 0
	SET B, 0
ADD [cursor], B
IFG [cursor], 0x0179
	SET [cursor], 0x0000
SET C, POP
SET B, POP
SET PC, POP

; =========
; End newline

:mem_copy                           ; copy [X:X+Z+1] -> [Y:Y+Z+1]
    SET I, 0
:mem_copy_loop
    IFE I, Z
        SET PC, POP ; return
    SET [Y], [X]
    ADD X, 1
    ADD Y, 1
    ADD I, 1
    SET PC, mem_copy_loop
; =========
; End mem_copy
	
:scroll
    SET J, 1
    SET Z, [termwidth]
    :scroll_loop
    IFE J, [termheight]
        SET PC, POP ; return
    SET I, J
    MUL I, [termwidth]
    SET X, [video_ram]
    ADD X, I
    SET Y, X
    SUB Y, [termwidth]
    JSR mem_copy
    ADD J, 1
    SET PC, scroll_loop
; =========
; End scroll
	
:get_hex
SET PUSH, Z
SET PUSH, X
SET PUSH, I
SET PUSH, C
SET PUSH, B
SET Z, 0xA000
SET [video_ram], 0x8200
SET A, 0
SET B, [video_ram]
HWI [screen_hwid]
SET [cursor], 0x004E
SET A, 0x0000
JSR write_hex
SET A, 3
SET B, 0
HWI [keyboard_hwid]
SET A, 0
HWI [keyboard_hwid]
SET I, 0
SET B, 0
:digit_loop
SET X, 0xffff
SHL B, 4
:get_hex_loop
SET A, 1
HWI [keyboard_hwid]
IFE C, 0x0000
	SET PC, get_hex_loop
IFE C, 0x0030
	SET X, 0
IFE C, 0x0031
	SET X, 1
IFE C, 0x00320
	SET X, 2
IFE C, 0x0033
	SET X, 3
IFE C, 0x0034
	SET X, 4
IFE C, 0x0035
	SET X, 5
IFE C, 0x0036
	SET X, 6
IFE C, 0x0037
	SET X, 7
IFE C, 0x0038
	SET X, 8
IFE C, 0x0039
	SET X, 9
IFE C, 0x0041
	SET X, 0x000A
IFE C, 0x0042
	SET X, 0x000B
IFE C, 0x0043
	SET X, 0x000C
IFE C, 0x0044
	SET X, 0x000D
IFE C, 0x0045
	SET X, 0x000E
IFE C, 0x0046
	SET X, 0x000F
IFE C, 0x0061
	SET X, 0x000A
IFE C, 0x0062
	SET X, 0x000B
IFE C, 0x0063
	SET X, 0x000C
IFE C, 0x0064
	SET X, 0x000D
IFE C, 0x0065
	SET X, 0x000E
IFE C, 0x0066
	SET X, 0x000F
IFE X, 0xffff
	SET PC, get_hex_loop
BOR B, X
SET [cursor], 0x004E
SET A, B
JSR write_hex
ADD I, 1
IFL I, 4
	SET PC, digit_loop
SET C, B
SET A, 3
SET B, [keyboard_hwid]
HWI [keyboard_hwid]
SET A, 0
HWI [keyboard_hwid]
SET [video_ram], 0x8000
SET A, 0
SET B, [video_ram]
HWI [screen_hwid]
SET A, C
SET B, POP
SET C, POP
SET I, POP
SET X, POP
SET Z, POP
SET PC, POP
; =========
; End get_hex

; Strings AND Constants
; =======================
:str_blank_line
DAT "                                ", 0
:str_gap
DAT ", ", 0
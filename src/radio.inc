; Memory
; =======================
:radio_messagetemp1
DAT 0x7000
:radio_messagetemp2
DAT 0x7100
:radio_message1
DAT 0x7200
:radio_message2
DAT 0x7300
:sending_message
DAT 0x7800
:sending_length
DAT 0x0015
:radio_repeating1
DAT 0x0000
:radio_repeating2
DAT 0x0000
:radio_last_signal1
DAT 0x0000
:radio_last_signal2
DAT 0x0000
:radio_last_angle1
DAT 0x0000
:radio_last_angle2
DAT 0x0000


; Functions
; =======================



:display_radio1
SET [cursor], 0x000E
SET Z, 0x7000
IFE [rcursor1], 0
	SET Z, 0x0700
SET A, str_radio1
JSR write_string
SET A, 2
HWI [radio1_hwid]
SET Z, 0xA000
IFE [rcursor1], 1
	SET Z, 0x0F00
SET [cursor], 0x002B
SET A, B
JSR write_hex
ADD [cursor], 1
SET Z, 0xA000
IFE [rcursor1], 2
	SET Z, 0x0F00
SET A, C
JSR write_hex

SET [cursor], 0x0049
SET A, [radio_last_signal1]
SET Z, 0xA000
JSR write_hex
SET [cursor], 0x0058
SET J, 3
SET A, [radio_last_angle1]
JSR write_angle

SET [cursor], 0x0080
SET Z, 0x9000
SET A, [radio_message1]
JSR write_string

SET PC, POP

:display_radio2
SET [cursor], 0x000E
SET Z, 0x7000
IFE [rcursor2], 0
	SET Z, 0x0700
SET A, str_radio2
JSR write_string
SET A, 2
HWI [radio2_hwid]
SET Z, 0xA000
IFE [rcursor2], 1
	SET Z, 0x0F00
SET [cursor], 0x002B
SET A, B

JSR write_hex
ADD [cursor], 1
SET Z, 0xA000
IFE [rcursor2], 2
	SET Z, 0x0F00
SET A, C
JSR write_hex

SET [cursor], 0x0049
SET A, [radio_last_signal2]
SET Z, 0xA000
JSR write_hex
SET [cursor], 0x0058
SET J, 3
SET A, [radio_last_angle2]
JSR write_angle

SET [cursor], 0x0080
SET Z, 0x9000
SET A, [radio_message2]
JSR write_string

SET PC, POP

:display_radio3
SET [cursor], 0x000D
SET Z, 0x7000
IFE [rcursor3], 0
	SET Z, 0x0700
SET A, str_radio3
JSR write_string
SET A, 2
HWI [radio1_hwid]
SET Z, 0xA000
IFE [rcursor3], 1
	SET Z, 0x0F00
SET [cursor], 0x002B
SET A, B
JSR write_hex
ADD [cursor], 1
SET Z, 0xA000
IFE [rcursor3], 2
	SET Z, 0x0F00
SET A, C
JSR write_hex
SET A, 2
HWI [radio2_hwid]
SET Z, 0xA000
IFE [rcursor3], 5
	SET Z, 0x0F00
SET [cursor], 0x004B
SET A, B
JSR write_hex
ADD [cursor], 1
SET Z, 0xA000
IFE [rcursor3], 6
	SET Z, 0x0F00
SET A, C
JSR write_hex

SET Z, 0x0700
IFE [rcursor3], 3
	SET Z, 0x0F00
SET [cursor], 0x0035
SET A, str_send
JSR write_string
ADD [cursor], 1
SET Z, 0x0700
IFE [rcursor3], 4
	SET Z, 0x0F00
SET A, str_repeat
	IFE [radio_repeating1], 1
		SET A, str_stop
JSR write_string

SET Z, 0x0700
IFE [rcursor3], 7
	SET Z, 0x0F00
SET [cursor], 0x0055
SET A, str_send
JSR write_string
ADD [cursor], 1
SET Z, 0x0700
IFE [rcursor3], 8
	SET Z, 0x0F00
SET A, str_repeat
	IFE [radio_repeating2], 1
		SET A, str_stop
JSR write_string
SET [cursor], 0x0080
SET Z, 0x0700
IFE [rcursor3], 9
	SET Z, 0x0F00
SET A, [sending_message]
JSR write_string

SET PC, POP

:radio_right
IFE [radio_mode], 3
	IFE [rcursor3], 0
		JSR ops_mode_func
IFE [radio_mode], 2
	IFE [rcursor2], 0
		JSR radio3_mode_func
IFE [radio_mode], 1
	IFE [rcursor1], 0
		JSR radio2_mode_func
IFE [radio_mode], 1
	IFE [rcursor1], 1
		SET [rcursor1], 2
IFE [radio_mode], 2
	IFE [rcursor2], 1
		SET [rcursor2], 2
IFE [radio_mode], 3
	IFG [rcursor3], 0
		IFL [rcursor3], 4
			ADD [rcursor3], 1
IFE [radio_mode], 3
	IFG [rcursor3], 4
		IFL [rcursor3], 8
			ADD [rcursor3], 1			
		
SET PC, POP
:radio_left
IFE [radio_mode], 1
	IFE [rcursor1], 0
		JSR helm_mode_func
IFE [radio_mode], 2
	IFE [rcursor2], 0
		JSR radio1_mode_func
IFE [radio_mode], 3
	IFE [rcursor3], 0
		JSR radio2_mode_func


IFE [radio_mode], 1
	IFE [rcursor1], 2
		SET [rcursor1], 1
IFE [radio_mode], 2
	IFE [rcursor2], 2
		SET [rcursor2], 1
IFE [radio_mode], 3
	IFG [rcursor3], 1
		IFL [rcursor3], 5
			SUB [rcursor3], 1
IFE [radio_mode], 3
	IFG [rcursor3], 5
		IFL [rcursor3], 9
			SUB [rcursor3], 1	
SET PC, POP

:change1B
SET PUSH, B
SET PUSH, C
SET A, 2
HWI [radio1_hwid]
JSR get_hex
SET B, A
SET A, 1
HWI [radio1_hwid]
SET C, POP
SET B, POP
SET PC, POP

:change1C
SET PUSH, B
SET PUSH, C
SET A, 2
HWI [radio1_hwid]
JSR get_hex
SET C, A
SET A, 1
HWI [radio1_hwid]
SET C, POP
SET B, POP
SET PC, POP

:change2B
SET PUSH, B
SET PUSH, C
SET A, 2
HWI [radio2_hwid]
JSR get_hex
SET B, A
SET A, 1
HWI [radio2_hwid]
SET C, POP
SET B, POP
SET PC, POP

:change2C
SET PUSH, B
SET PUSH, C
SET A, 2
HWI [radio2_hwid]
JSR get_hex
SET C, A
SET A, 1
HWI [radio2_hwid]
SET C, POP
SET B, POP
SET PC, POP

:change_message
SET PUSH, Z
SET PUSH, X
SET PUSH, I
SET PUSH, C
SET PUSH, B
SET I, 0
:change_message_loop_1
SET X, [sending_message]
ADD X, I
SET [X], 0x0000
ADD I, 1
IFN I, [sending_length]
	SET PC, change_message_loop_1
SET Z, 0xA000
SET [video_ram], 0x8400
SET A, 0
SET B, [video_ram]
HWI [screen_hwid]
SET [cursor], 0x0000
;SET A, [sending_message]
;JSR write_string
SET A, 3
SET B, 0
HWI [keyboard_hwid]
SET A, 0
HWI [keyboard_hwid]
SET I, 0
SET B, 0
:get_char_loop
SET X, [video_ram]
ADD X, I
SET [X], 0xA0DF
SET A, 1
HWI [keyboard_hwid]
IFE C, 0
	SET PC, get_char_loop
IFE C, 0x0010
	IFG I, 0
	SET PC, change_message_backspace
IFE C, 0x0010
	IFE I, 0
		SET PC, get_char_loop
IFE C, 0x0090
	SET PC, get_char_loop
IFE C, 0x0011
	SET PC, exit_change_message
SET X, [sending_message]
ADD X, I
SET [X], C
ADD I, 1
SET [cursor], 0x0000
SET A, [sending_message]
JSR write_string
IFE I, 0x00FF
	SET PC, exit_change_message
SET PC, get_char_loop

:exit_change_message
ADD I, 0
SET X, [sending_message]
ADD X, I
SET [X], 0x0000
SET [sending_length], I
SET A, 3
SET B, [keyboard_hwid]
HWI [keyboard_hwid]
SET A, 0
HWI [keyboard_hwid]
SET [video_ram], 0x8000
SET A, 0
SET B, [video_ram]
HWI [screen_hwid]
SET I, 0
:change_message_loop_2
SET X, 0x8400
ADD X, I
SET [X], 0x0000
ADD I, 1
IFN I, 0x00FF
	SET PC, change_message_loop_2
SET B, POP
SET C, POP
SET I, POP
SET X, POP
SET Z, POP
SET PC, radio3_mode_func
:change_message_backspace
SET X, [video_ram]
ADD X, I
SET [X], 0x0000
SET X, [sending_message]
ADD X, I
SET [X], 0x0020
SUB I, 1
SET PC, get_char_loop

; =========
; End change_message



SET PC, POP

:radio1_send
SET PUSH, I
SET PUSH, B
SET PUSH, A
SET A, 3
SET B, [sending_message]
SET I, [sending_length]
HWI [radio1_hwid]
SET A, POP
SET B, POP
SET I, POP
SET PC, POP

:radio2_send
SET PUSH, I
SET PUSH, B
SET PUSH, A
SET A, 3
SET B, [sending_message]
SET I, [sending_length]
HWI [radio2_hwid]
SET A, POP
SET B, POP
SET I, POP
SET PC, POP



; Strings AND Constants
; =======================

:stationIDB
DAT 0xACF7
:stationIDC
DAT 0x0045

:str_SET
DAT "SET", 0
:str_send
DAT "SEND", 0
:str_stop
DAT " STOP ", 0
:str_repeat
DAT "XXXXXX", 0
:str_sending_message
DAT "SOS Send Help", 0
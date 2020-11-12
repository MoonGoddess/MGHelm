; Memory
; =======================
:radio_messagetemp1
DAT 0x7000
:radio_messagetemp2
DAT 0x7100
:radio1_message
DAT 0x7200
:radio2_message
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
:radio_last_timelo1
DAT 0x0000
:radio_last_timehi1
DAT 0x0000
:radio_last_timelo2
DAT 0x0000
:radio_last_timehi2
DAT 0x0000
:radio_index
DAT 0x0000

; radio format
; Channel Hi, Channel Lo, Signal Strength, Angle, TimeHi, TimeLo, Message Length, Message Content
:radio_message1
DAT 0x6000
:radio_message2
DAT 0x6108
:radio_message3
DAT 0x6210
:radio_message4
DAT 0x6318
:radio_message5
DAT 0x6420
:radio_message6
DAT 0x6528
:radio_message7
DAT 0x6630
:radio_message8
DAT 0x6738
:radio_message9
DAT 0x6840
:radio_message10
DAT 0x6948



; Functions
; =======================



:display_radio1
SET [screen_cursor], 0x000E
SET Z, [fg_light_grey]
IFE [rcursor1], 0
	SET Z, [bg_light_grey]
SET A, str_radio1
JSR write_string
SET A, 2
HWI [radio1_hwid]
SET Z, [fg_light_green]
IFE [rcursor1], 1
	SET Z, [bg_white]
SET [screen_cursor], 0x002B
SET A, B
JSR write_hex
ADD [screen_cursor], 1
SET Z, [fg_light_green]
IFE [rcursor1], 2
	SET Z, [bg_white]
SET A, C
JSR write_hex

SET [screen_cursor], 0x0049
SET A, [radio_last_signal1]
SET Z, [fg_light_green]
JSR write_hex
SET [screen_cursor], 0x0058
SET J, 3
SET A, [radio_last_angle1]
JSR write_angle

SET B, [clocklo]
SET C, [clockhi]
SUB B, [radio_last_timelo1]
SUB C, [radio_last_timehi1]
SET [screen_cursor], 0x0070

IFN [radio_last_timelo1], 0
	JSR write_time
IFG [radio_last_timehi1], 0
	IFE [radio_last_timelo1], 0
		JSR write_time
SET [screen_cursor], 0x0080
SET Z, [fg_white]
SET A, [radio1_message]
JSR write_string

SET PC, POP

:display_radio2
SET [screen_cursor], 0x000E
SET Z, [fg_light_grey]
IFE [rcursor2], 0
	SET Z, [bg_light_grey]
SET A, str_radio2
JSR write_string
SET Z, [fg_light_green]
IFE [rcursor2], 1
	SET Z, [bg_white]
SET [screen_cursor], 0x002B
SET A, [radio_message1 + 0]
JSR write_hex
ADD [screen_cursor], 1
SET Z, [fg_light_green]
IFE [rcursor2], 2
	SET Z, [bg_white]
SET A, [radio_message1 + 1]
JSR write_hex

SET [screen_cursor], 0x0049
SET A, [radio_message1 + 2]
SET Z, [fg_light_green]
JSR write_hex
SET [screen_cursor], 0x0058
SET J, 3
SET A, [radio_message1 + 3]
JSR write_angle

SET B, [clocklo]
SET C, [clockhi]
SUB B, [radio_message1 + 4]
SUB C, [radio_message1 + 5]
SET [screen_cursor], 0x0070

IFN [radio_last_timelo2], 0
	JSR write_time
IFG [radio_last_timehi2], 0
	IFE [radio_last_timelo2], 0
		JSR write_time

SET [screen_cursor], 0x0080

SET [screen_cursor], 0x0080
SET Z, [fg_white]
SET A, [radio_message1 + 8]
JSR write_string

SET PC, POP

:display_radio3
SET [screen_cursor], 0x000D
SET Z, [fg_light_grey]
IFE [rcursor3], 0
	SET Z, [bg_light_grey]
SET A, str_radio3
JSR write_string
SET A, 2
HWI [radio1_hwid]
SET Z, [fg_light_green]
IFE [rcursor3], 1
	SET Z, [bg_white]
SET [screen_cursor], 0x002B
SET A, B
JSR write_hex
ADD [screen_cursor], 1
SET Z, [fg_light_green]
IFE [rcursor3], 2
	SET Z, [bg_white]
SET A, C
JSR write_hex
SET A, 2
HWI [radio2_hwid]
SET Z, [fg_light_green]
IFE [rcursor3], 5
	SET Z, [bg_white]
SET [screen_cursor], 0x004B
SET A, B
JSR write_hex
ADD [screen_cursor], 1
SET Z, [fg_light_green]
IFE [rcursor3], 6
	SET Z, [bg_white]
SET A, C
JSR write_hex

SET Z, [bg_light_grey]
IFE [rcursor3], 3
	SET Z, [bg_white]
SET [screen_cursor], 0x0035
SET A, str_send
JSR write_string
ADD [screen_cursor], 1
SET Z, [bg_light_grey]
IFE [rcursor3], 4
	SET Z, [bg_white]
SET A, str_repeat
	IFE [radio_repeating1], 1
		SET A, str_stop
JSR write_string

SET Z, [bg_light_grey]
IFE [rcursor3], 7
	SET Z, [bg_white]
SET [screen_cursor], 0x0055
SET A, str_send
JSR write_string
ADD [screen_cursor], 1
SET Z, [bg_light_grey]
IFE [rcursor3], 8
	SET Z, [bg_white]
SET A, str_repeat
	IFE [radio_repeating2], 1
		SET A, str_stop
JSR write_string
SET [screen_cursor], 0x0080
SET Z, [bg_light_grey]
IFE [rcursor3], 9
	SET Z, 0x0F00
SET A, [sending_message]
JSR write_string

SET PC, POP

:check_radio1
SET PUSH, A
SET PUSH, B
SET PUSH, X
SET PUSH, Y
SET PUSH, Z
SET PUSH, I

SET A, 4
SET B, [radio_messagetemp1]
HWI [radio1_hwid]
IFN I, 0
	SET [radio_last_signal1], X
IFN I, 0
	SET [radio_last_angle1], Y
SET X, [radio_messagetemp1]
SET Y, [radio1_message]
SET Z, I
IFN I, 0
	JSR mem_copy
IFN I, 0
	SET [radio_last_timelo1], [clocklo]
IFN I, 0
	SET [radio_last_timehi1], [clockhi]
SET I, POP
SET Z, POP
SET Y, POP
SET X, POP
SET B, POP
SET A, POP
SET PC, POP

:check_radio2
SET PUSH, A
SET PUSH, B
SET PUSH, X
SET PUSH, Y
SET PUSH, Z
SET PUSH, I

SET A, 4
SET B, [radio_messagetemp2]
HWI [radio2_hwid]
IFN I, 0
	JSR store_message1
SET I, POP
SET Z, POP
SET Y, POP
SET X, POP
SET B, POP
SET A, POP
SET PC, POP

:store_message1
SET [radio_message1 + 6], I
SET [radio_message1 + 2], X
SET [radio_message1 + 3], Y
SET X, [radio_messagetemp2]
SET Y, [radio_message1 + 7]
SET Z, I
JSR mem_copy
SET [radio_message1 + 4], [clocklo]
SET [radio_message1 + 5], [clockhi]
SET A, 2
HWI [radio2_hwid]
SET [radio_message1 + 0], B
SET [radio_message1 + 1], C
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
SET Z, [fg_light_green]
SET [video_ram], 0x8400
SET A, 0
SET B, [video_ram]
HWI [screen_hwid]
SET [screen_cursor], 0x0000
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
SET [screen_cursor], 0x0000
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

:radio1_repeat
SET PUSH, B
SET B, [clocklo]
MOD B, 20
IFE B, 0
	JSR radio1_send
SET B, POP
SET PC, POP

:radio2_repeat
SET PUSH, B
SET B, [clocklo]
MOD B, 20
IFE B, 0
	JSR radio2_send
SET B, POP
SET PC, POP


:write_time
IFE C, 0x0000
 SET PC, Lo_word_time
:exit_time
SET PC, POP

:lo_word_time
IFG B, 0x0E0F
	SET PC, time_hours
IFG B, 0x0059
	SET PC, time_minutes

SET PC, time_seconds
	
:time_hours
DIV B, 0x0E10
SET J, 2
SET A, B
SET Z, [fg_light_green]
JSR write_decimal
SET Z, [fg_light_grey]
SET A, str_h_ago
JSR write_string
SET PC, exit_time

:time_seconds
SET J, 2
SET A, B
SET Z, [fg_light_green]
JSR write_decimal
SET Z, [fg_light_grey]
SET A, str_s_ago
JSR write_string
SET PC, exit_time

:time_minutes
DIV B, 60
SET J, 2
SET A, B
SET Z, [fg_light_green]
JSR write_decimal
SET Z, [fg_light_grey]
SET A, str_m_ago
JSR write_string
SET PC, exit_time


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
DAT "REPEAT", 0
:str_sending_message
DAT "SOS Send Help", 0
:str_s_ago
DAT "s ago.", 0
:str_m_ago
DAT "m ago.", 0
:str_h_ago
DAT "h ago.", 0

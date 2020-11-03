; Memory
; ==============================

:temp_a
DAT 0x0000
:contact_type
DAT 0x0000
:contact_size
DAT 0x0000
:rear_contact
DAT 0x0000


; Functions
; ====================

:display_sensors
SET PUSH, A
SET PUSH, I
SET PUSH, Z
SET [cursor], 0x0040
SET I, 0
SET J, 0
SET A, 0
HWI [fsensor_hwid]
HWI [rsensor_hwid]
:display_sensors_loop
SET A, 1
HWI [fsensor_hwid]
SET [contact_size], Z
SET [rear_contact], 0x0000
SET Z, 0xA000
IFN A, 0x0000
	JSR display_contact
SET A, 1
HWI [rsensor_hwid]
SET [contact_size], Z
SET [rear_contact], 0x0001
SET Z, 0xA000
IFN A, 0x0000
	JSR display_contact
ADD J, 2
IFE J, 20
	SET PC, display_sensors_exit
IFN I, 10
	SET PC, display_sensors_loop
:display_sensors_exit
SET J, 10
SUB J, I
IFE J, 0
	SET PC, display_sensors_exit2
:display_sensors_loop2
JSR write_blank_line
SUB J, 1
IFN J, 0
	SET PC, display_sensors_loop2
:display_sensors_exit2
SET Z, POP
SET I, POP
SET A, POP
SET PC, POP

:display_contact
SET [contact_type], A
JSR write_type
;ADD [cursor], 1
SET A, B
JSR write_hex
SET A, C
JSR write_hex
ADD [cursor], 1
SET A, Y
DIV A, 0x0021
SET J, 4
JSR write_range
;ADD [cursor], 1
SET J, 2
SET A, X

JSR write_angle

JSR newline
ADD I, 1
SET PC, POP


:write_angle
SET PUSH, X
SET PUSH, Z
SET PUSH, B

SET X, [cursor]
ADD X, [video_ram]
SET B, A
AND B, 0x8000
IFE B, 0x8000
	SET PC, angle_negative
IFE B, 0x0000
	SET PC, angle_positive


:angle_negative
SET [X], 0xA02D
SET B, A
XOR B, 0xFFFF
ADD B, 1
SET PC, exit_angle

:angle_positive
SET [X], 0xA020
SET B, A
:exit_angle
DIV B, 0x00B6

SET A, B
JSR write_decimal

SET B, POP
SET Z, POP
SET X, POP
SET PC, POP

:write_type
SET PUSH, Z
SET A, 0xffff
SET [temp_a], [contact_type]
AND [temp_a], 0x00FF
IFE [temp_a], 0x0001
	SET PC, type_1
IFE [temp_a], 0x0002
	SET PC, type_2
IFE [temp_a], 0x0003
	SET PC, type_3
IFE [temp_a], 0x0008
	SET PC, type_8
IFE [temp_a], 0x000A
	SET A, str_typeA
:exit_type
IFE A, 0xffff
	SET A, str_unknown

JSR write_string
SET Z, POP
SET PC, POP

:type_1
IFE [contact_type], 0x0001
	SET A, str_astblue
IFE [contact_type], 0x0101
	SET A, str_astred
IFE [contact_type], 0x0201
	SET A, str_astgold
IFE [contact_type], 0x0301
	SET A, str_astblack
IFE [contact_type], 0x0401
	SET A, str_astgreen
IFE [contact_type], 0x0501
	SET A, str_astrock
IFE [contact_type], 0x0601
	SET A, str_astrock
IFE [contact_type], 0x0701
	SET A, str_astrock
IFE [contact_type], 0x0801
	SET A, str_astrock
IFE [contact_type], 0x0901
	SET A, str_astrock
IFE A, 0xffff
	SET A, str_astunknown
SET PC, exit_type

:type_2

	SET A, str_astbits
SET PC, exit_type

:type_3
IFE [contact_type], 0x0003
	SET A, str_manmade
IFE [contact_type], 0x0003
	IFE B, 0xACF7
		IFE C, 0x0045
			SET A, str_station
IFE [contact_type], 0x0003
	IFE [contact_size], 0x000C
		SET A, str_ship
IFE [contact_type], 0x0003
	IFE [contact_size], 0x0015
		SET A, str_mystery
SET PC, exit_type

:type_8

SET A, str_buoyunknown
IFE [contact_type], 0x0308
	SET A, str_docking
IFE [contact_type], 0x0108
	SET A, str_type108
IFE [contact_type], 0x0208
	SET A, str_type208
IFE [contact_type], 0x0108
	IFE B, 0x2513
		IFE C, 0x74F4
			SET A, str_outerwall
IFE [contact_type], 0x0208
	IFE B, 0xA503
		IFE C, 0xD2AA
			SET A, str_15NW
IFE [contact_type], 0x0208
	IFE B, 0x41A3
		IFE C, 0x55BB
			SET A, str_15NE
IFE [contact_type], 0x0208
	IFE B, 0x6106
		IFE C, 0x423C
			SET A, str_15SW
IFE [contact_type], 0x0208
	IFE B, 0xAB85
		IFE C, 0x76AD
			SET A, str_15SE
IFE [contact_type], 0x0208
	IFE B, 0x2B1C
		IFE C, 0x6096
			SET A, str_4SE
IFE [contact_type], 0x0208
	IFE B, 0x9C2E
		IFE C, 0xEDE2
			SET A, str_4NE
IFE [contact_type], 0x0208
	IFE B, 0xCB57
		IFE C, 0xF22B
			SET A, str_4NW
IFE [contact_type], 0x0208
	IFE B, 0x68CA
		IFE C, 0xEF38
			SET A, str_4SW
SET PC, exit_type

:write_range
SET PUSH, X
SET PUSH, J
SET J, 4
JSR write_decimal
SET X, [cursor]
ADD X, [video_ram]
SET [X], 0xA06D
ADD X, 1
ADD [cursor], 1
IFE [rear_contact], 0
	SET [X], 0xB05E
IFE [rear_contact], 1
	SET [X], 0xC076
ADD [cursor], 2
SET J, POP
SET X, POP
SET PC, POP

:write_size
SET PUSH, X
SET X, [cursor]
ADD X, [video_ram]
SET [X], 0xA06D
SUB [cursor], 1
JSR write_decimal
ADD [cursor], 1
SET X, POP
SET PC, POP

; Strings AND Constants
; =======================
:str_heading
DAT "  Type:        ID:    Range: Ang", 0
                                     
:str_station
DAT "Station     ", 0
:str_ship
DAT "Player Ship ", 0
:str_mystery
DAT "Relic Ship  ", 0
:str_manmade
DAT "Manmade Obj ", 0
:str_docking
DAT "Dock Buoy   ", 0
:str_type108
DAT "Haz Buoy    ", 0
:str_buoyunknown
DAT "Buoy(Unknwn)", 0
:str_astgreen
DAT "Ast (Green) ", 0
:str_astred
DAT "Ast (Red)   ", 0
:str_astblack
DAT "Ast (Black) ", 0
:str_astblue
DAT "Ast (Blue)  ", 0
:str_astgold
DAT "Ast (Gold)  ", 0
:str_astrock
DAT "Ast (Rock)  ", 0
:str_astbits
DAT "Ast bits    ", 0
:str_astunknown
DAT "Ast(Unknown)", 0
:str_typeA
DAT "Ship Debris ", 0
:str_unknown
DAT "Unknown     ", 0
:str_type208
DAT "Nav Buoy    ", 0
:str_outerwall
DAT "Outer Wall  ", 0



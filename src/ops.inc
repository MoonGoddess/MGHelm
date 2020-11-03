:ocursor
DAT 0x0000
:fuel_level
DAT 0x1600


:display_ops
SET [cursor], 0x000F
SET Z, 0x7000
IFE [ocursor], 0
	SET Z, 0x0700
SET A, str_ops
JSR write_string
SET Z, 0xA000
SET [cursor], 0x0150
SET A, [fuel_level]
JSR write_hex
SET PUSH, I
SET A, 0
SET I, 1
HWI [clamps_hwid]
SHR B, 8
IFE B, 0
	SET A, str_off
IFE B, 1
	SET A, str_pulling
IFE B, 2
	SET A, str_locked
SET [cursor], 0x0050
SET Z, 0xA000
IFE [ocursor], 1
	SET Z, 0xA700
JSR write_string

SET A, 0
SET I, 2
HWI [clamps_hwid]
SHR B, 8
IFE B, 0
	SET A, str_off
IFE B, 1
	SET A, str_pulling
IFE B, 2
	SET A, str_locked
SET [cursor], 0x0070
SET Z, 0xA000
IFE [ocursor], 2
	SET Z, 0xA700
JSR write_string

SET A, 0
SET I, 0
HWI [doors_hwid]
SHR B, 8
IFE B, 0
	SET A, str_locked
IFE B, 1
	SET A, str_oneway
IFE B, 2
	SET A, str_auto
IFE B, 3
	SET A, str_open
SET [cursor], 0x00B0
SET Z, 0xA000
IFE [ocursor], 3
	SET Z, 0xA700
JSR write_string

SET A, 0
SET I, 1
HWI [doors_hwid]
SHR B, 8
IFE B, 0
	SET A, str_locked
IFE B, 1
	SET A, str_oneway
IFE B, 2
	SET A, str_auto
IFE B, 3
	SET A, str_open
SET [cursor], 0x00D0
SET Z, 0xA000
IFE [ocursor], 4
	SET Z, 0xA700
JSR write_string

SET A, 0
SET I, 2
HWI [doors_hwid]
SHR B, 8
IFE B, 0
	SET A, str_locked
IFE B, 1
	SET A, str_oneway
IFE B, 2
	SET A, str_auto
IFE B, 3
	SET A, str_open
SET [cursor], 0x00F0
SET Z, 0xA000
IFE [ocursor], 5
	SET Z, 0xA700
JSR write_string



SET I, POP
SET PC, POP


:ops_left
IFE [ocursor], 0
	JSR radio3_mode_func
IFE [ocursor], 1
	JSR clamps_down
IFE [ocursor], 2
	JSR clamps_down
IFG [ocursor], 2
	JSR doors_down
SET [key_left_down], 0
SET PC, POP

:ops_right
IFE [ocursor], 0
	JSR helm_mode_func
IFE [ocursor], 1
	JSR clamps_up	
IFE [ocursor], 2
	JSR clamps_up
IFG [ocursor], 2
	JSR doors_up
SET [key_right_down], 0
SET PC, POP

:clamps_down
SET PUSH, A 
SET PUSH, B
SET PUSH, I
IFE [ocursor], 1
	SET I, 0
IFE [ocursor], 2
	SET I, 2
SET A, 0
HWI [clamps_hwid]
SHR B, 8
SUB B, 1
IFE B, 0xffff
	SET B, 2
SET A, 1
HWI [clamps_hwid]
ADD I, 1
HWI [clamps_hwid]
SET I, POP
SET B, POP
SET A, POP
SET PC, POP

:clamps_up
SET PUSH, A 
SET PUSH, B
SET PUSH, I
IFE [ocursor], 1
	SET I, 0
IFE [ocursor], 2
	SET I, 2
SET A, 0
HWI [clamps_hwid]
SHR B, 8
ADD B, 1
IFE B, 3
	SET B, 0
SET A, 1
HWI [clamps_hwid]
ADD I, 1
HWI [clamps_hwid]
SET I, POP
SET B, POP
SET A, POP
SET PC, POP

:doors_down
SET PUSH, A 
SET PUSH, B
SET PUSH, I
SET I, [ocursor]
SUB I, 3
SET A, 0
HWI [doors_hwid]
SHR B, 8
SUB B, 1
IFE B, 0xffff
	SET B, 3
SET A, 1
HWI [doors_hwid]
SET I, POP
SET B, POP
SET A, POP
SET PC, POP

:doors_up
SET PUSH, A 
SET PUSH, B
SET PUSH, I
SET I, [ocursor]
SUB I, 3
SET A, 0
HWI [doors_hwid]
SHR B, 8
ADD B, 1
IFE B, 4
	SET B, 0
SET A, 1
HWI [doors_hwid]
SET I, POP
SET B, POP
SET A, POP
SET PC, POP




; Strings AND Constants
; =======================
:str_leftclamp
DAT "Left Clamp:   ", 0
:str_rightclamp
DAT "Right Clamp:  ", 0
:str_cockpitdoor
DAT "Cockpit Door: ", 0
:str_leftdoor
DAT "Left Door:    ", 0
:str_rightdoor
DAT "Right Door:   ", 0
:str_locked
DAT "Locked ", 0
:str_pulling
DAT "Pulling", 0
:str_off
DAT "Off    ", 0
:str_auto
DAT "Auto   ", 0
:str_open
DAT "Open   ", 0
:str_oneway
DAT "One-Way", 0






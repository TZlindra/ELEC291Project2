;--------------------------------------------------------
; File Created by C51
; Version 1.0.0 #1170 (Feb 16 2022) (MSVC)
; This file was generated Mon Apr 01 12:54:44 2024
;--------------------------------------------------------
$name Robot_Base
$optc51 --model-small
	R_DSEG    segment data
	R_CSEG    segment code
	R_BSEG    segment bit
	R_XSEG    segment xdata
	R_PSEG    segment xdata
	R_ISEG    segment idata
	R_OSEG    segment data overlay
	BIT_BANK  segment data overlay
	R_HOME    segment code
	R_GSINIT  segment code
	R_IXSEG   segment xdata
	R_CONST   segment code
	R_XINIT   segment code
	R_DINIT   segment code

;--------------------------------------------------------
; Public variables in this module
;--------------------------------------------------------
	public _InitPinADC_PARM_2
	public _PrintNumber_HexDigit_1_81
	public _main
	public _PrintNumber
	public _eputs
	public _GetPeriod
	public _waitms
	public _Timer3us
	public _Timer5_ISR
	public _ADC_at_Pin
	public _InitPinADC
	public _InitADC
	public __c51_external_startup
	public _PrintNumber_PARM_3
	public _PrintNumber_PARM_2
	public _servo2
	public _servo1
	public _servo_counter
;--------------------------------------------------------
; Special Function Registers
;--------------------------------------------------------
_ACC            DATA 0xe0
_ADC0ASAH       DATA 0xb6
_ADC0ASAL       DATA 0xb5
_ADC0ASCF       DATA 0xa1
_ADC0ASCT       DATA 0xc7
_ADC0CF0        DATA 0xbc
_ADC0CF1        DATA 0xb9
_ADC0CF2        DATA 0xdf
_ADC0CN0        DATA 0xe8
_ADC0CN1        DATA 0xb2
_ADC0CN2        DATA 0xb3
_ADC0GTH        DATA 0xc4
_ADC0GTL        DATA 0xc3
_ADC0H          DATA 0xbe
_ADC0L          DATA 0xbd
_ADC0LTH        DATA 0xc6
_ADC0LTL        DATA 0xc5
_ADC0MX         DATA 0xbb
_B              DATA 0xf0
_CKCON0         DATA 0x8e
_CKCON1         DATA 0xa6
_CLEN0          DATA 0xc6
_CLIE0          DATA 0xc7
_CLIF0          DATA 0xe8
_CLKSEL         DATA 0xa9
_CLOUT0         DATA 0xd1
_CLU0CF         DATA 0xb1
_CLU0FN         DATA 0xaf
_CLU0MX         DATA 0x84
_CLU1CF         DATA 0xb3
_CLU1FN         DATA 0xb2
_CLU1MX         DATA 0x85
_CLU2CF         DATA 0xb6
_CLU2FN         DATA 0xb5
_CLU2MX         DATA 0x91
_CLU3CF         DATA 0xbf
_CLU3FN         DATA 0xbe
_CLU3MX         DATA 0xae
_CMP0CN0        DATA 0x9b
_CMP0CN1        DATA 0x99
_CMP0MD         DATA 0x9d
_CMP0MX         DATA 0x9f
_CMP1CN0        DATA 0xbf
_CMP1CN1        DATA 0xac
_CMP1MD         DATA 0xab
_CMP1MX         DATA 0xaa
_CRC0CN0        DATA 0xce
_CRC0CN1        DATA 0x86
_CRC0CNT        DATA 0xd3
_CRC0DAT        DATA 0xcb
_CRC0FLIP       DATA 0xcf
_CRC0IN         DATA 0xca
_CRC0ST         DATA 0xd2
_DAC0CF0        DATA 0x91
_DAC0CF1        DATA 0x92
_DAC0H          DATA 0x85
_DAC0L          DATA 0x84
_DAC1CF0        DATA 0x93
_DAC1CF1        DATA 0x94
_DAC1H          DATA 0x8a
_DAC1L          DATA 0x89
_DAC2CF0        DATA 0x95
_DAC2CF1        DATA 0x96
_DAC2H          DATA 0x8c
_DAC2L          DATA 0x8b
_DAC3CF0        DATA 0x9a
_DAC3CF1        DATA 0x9c
_DAC3H          DATA 0x8e
_DAC3L          DATA 0x8d
_DACGCF0        DATA 0x88
_DACGCF1        DATA 0x98
_DACGCF2        DATA 0xa2
_DERIVID        DATA 0xad
_DEVICEID       DATA 0xb5
_DPH            DATA 0x83
_DPL            DATA 0x82
_EIE1           DATA 0xe6
_EIE2           DATA 0xf3
_EIP1           DATA 0xbb
_EIP1H          DATA 0xee
_EIP2           DATA 0xed
_EIP2H          DATA 0xf6
_EMI0CN         DATA 0xe7
_FLKEY          DATA 0xb7
_HFO0CAL        DATA 0xc7
_HFO1CAL        DATA 0xd6
_HFOCN          DATA 0xef
_I2C0ADM        DATA 0xff
_I2C0CN0        DATA 0xba
_I2C0DIN        DATA 0xbc
_I2C0DOUT       DATA 0xbb
_I2C0FCN0       DATA 0xad
_I2C0FCN1       DATA 0xab
_I2C0FCT        DATA 0xf5
_I2C0SLAD       DATA 0xbd
_I2C0STAT       DATA 0xb9
_IE             DATA 0xa8
_IP             DATA 0xb8
_IPH            DATA 0xf2
_IT01CF         DATA 0xe4
_LFO0CN         DATA 0xb1
_P0             DATA 0x80
_P0MASK         DATA 0xfe
_P0MAT          DATA 0xfd
_P0MDIN         DATA 0xf1
_P0MDOUT        DATA 0xa4
_P0SKIP         DATA 0xd4
_P1             DATA 0x90
_P1MASK         DATA 0xee
_P1MAT          DATA 0xed
_P1MDIN         DATA 0xf2
_P1MDOUT        DATA 0xa5
_P1SKIP         DATA 0xd5
_P2             DATA 0xa0
_P2MASK         DATA 0xfc
_P2MAT          DATA 0xfb
_P2MDIN         DATA 0xf3
_P2MDOUT        DATA 0xa6
_P2SKIP         DATA 0xcc
_P3             DATA 0xb0
_P3MDIN         DATA 0xf4
_P3MDOUT        DATA 0x9c
_PCA0CENT       DATA 0x9e
_PCA0CLR        DATA 0x9c
_PCA0CN0        DATA 0xd8
_PCA0CPH0       DATA 0xfc
_PCA0CPH1       DATA 0xea
_PCA0CPH2       DATA 0xec
_PCA0CPH3       DATA 0xf5
_PCA0CPH4       DATA 0x85
_PCA0CPH5       DATA 0xde
_PCA0CPL0       DATA 0xfb
_PCA0CPL1       DATA 0xe9
_PCA0CPL2       DATA 0xeb
_PCA0CPL3       DATA 0xf4
_PCA0CPL4       DATA 0x84
_PCA0CPL5       DATA 0xdd
_PCA0CPM0       DATA 0xda
_PCA0CPM1       DATA 0xdb
_PCA0CPM2       DATA 0xdc
_PCA0CPM3       DATA 0xae
_PCA0CPM4       DATA 0xaf
_PCA0CPM5       DATA 0xcc
_PCA0H          DATA 0xfa
_PCA0L          DATA 0xf9
_PCA0MD         DATA 0xd9
_PCA0POL        DATA 0x96
_PCA0PWM        DATA 0xf7
_PCON0          DATA 0x87
_PCON1          DATA 0xcd
_PFE0CN         DATA 0xc1
_PRTDRV         DATA 0xf6
_PSCTL          DATA 0x8f
_PSTAT0         DATA 0xaa
_PSW            DATA 0xd0
_REF0CN         DATA 0xd1
_REG0CN         DATA 0xc9
_REVID          DATA 0xb6
_RSTSRC         DATA 0xef
_SBCON1         DATA 0x94
_SBRLH1         DATA 0x96
_SBRLL1         DATA 0x95
_SBUF           DATA 0x99
_SBUF0          DATA 0x99
_SBUF1          DATA 0x92
_SCON           DATA 0x98
_SCON0          DATA 0x98
_SCON1          DATA 0xc8
_SFRPAGE        DATA 0xa7
_SFRPGCN        DATA 0xbc
_SFRSTACK       DATA 0xd7
_SMB0ADM        DATA 0xd6
_SMB0ADR        DATA 0xd7
_SMB0CF         DATA 0xc1
_SMB0CN0        DATA 0xc0
_SMB0DAT        DATA 0xc2
_SMB0FCN0       DATA 0xc3
_SMB0FCN1       DATA 0xc4
_SMB0FCT        DATA 0xef
_SMB0RXLN       DATA 0xc5
_SMB0TC         DATA 0xac
_SMOD1          DATA 0x93
_SP             DATA 0x81
_SPI0CFG        DATA 0xa1
_SPI0CKR        DATA 0xa2
_SPI0CN0        DATA 0xf8
_SPI0DAT        DATA 0xa3
_SPI0FCN0       DATA 0x9a
_SPI0FCN1       DATA 0x9b
_SPI0FCT        DATA 0xf7
_SPI0PCF        DATA 0xdf
_TCON           DATA 0x88
_TH0            DATA 0x8c
_TH1            DATA 0x8d
_TL0            DATA 0x8a
_TL1            DATA 0x8b
_TMOD           DATA 0x89
_TMR2CN0        DATA 0xc8
_TMR2CN1        DATA 0xfd
_TMR2H          DATA 0xcf
_TMR2L          DATA 0xce
_TMR2RLH        DATA 0xcb
_TMR2RLL        DATA 0xca
_TMR3CN0        DATA 0x91
_TMR3CN1        DATA 0xfe
_TMR3H          DATA 0x95
_TMR3L          DATA 0x94
_TMR3RLH        DATA 0x93
_TMR3RLL        DATA 0x92
_TMR4CN0        DATA 0x98
_TMR4CN1        DATA 0xff
_TMR4H          DATA 0xa5
_TMR4L          DATA 0xa4
_TMR4RLH        DATA 0xa3
_TMR4RLL        DATA 0xa2
_TMR5CN0        DATA 0xc0
_TMR5CN1        DATA 0xf1
_TMR5H          DATA 0xd5
_TMR5L          DATA 0xd4
_TMR5RLH        DATA 0xd3
_TMR5RLL        DATA 0xd2
_UART0PCF       DATA 0xd9
_UART1FCN0      DATA 0x9d
_UART1FCN1      DATA 0xd8
_UART1FCT       DATA 0xfa
_UART1LIN       DATA 0x9e
_UART1PCF       DATA 0xda
_VDM0CN         DATA 0xff
_WDTCN          DATA 0x97
_XBR0           DATA 0xe1
_XBR1           DATA 0xe2
_XBR2           DATA 0xe3
_XOSC0CN        DATA 0x86
_DPTR           DATA 0x8382
_TMR2RL         DATA 0xcbca
_TMR3RL         DATA 0x9392
_TMR4RL         DATA 0xa3a2
_TMR5RL         DATA 0xd3d2
_TMR0           DATA 0x8c8a
_TMR1           DATA 0x8d8b
_TMR2           DATA 0xcfce
_TMR3           DATA 0x9594
_TMR4           DATA 0xa5a4
_TMR5           DATA 0xd5d4
_SBRL1          DATA 0x9695
_PCA0           DATA 0xfaf9
_PCA0CP0        DATA 0xfcfb
_PCA0CP1        DATA 0xeae9
_PCA0CP2        DATA 0xeceb
_PCA0CP3        DATA 0xf5f4
_PCA0CP4        DATA 0x8584
_PCA0CP5        DATA 0xdedd
_ADC0ASA        DATA 0xb6b5
_ADC0GT         DATA 0xc4c3
_ADC0           DATA 0xbebd
_ADC0LT         DATA 0xc6c5
_DAC0           DATA 0x8584
_DAC1           DATA 0x8a89
_DAC2           DATA 0x8c8b
_DAC3           DATA 0x8e8d
;--------------------------------------------------------
; special function bits
;--------------------------------------------------------
_ACC_0          BIT 0xe0
_ACC_1          BIT 0xe1
_ACC_2          BIT 0xe2
_ACC_3          BIT 0xe3
_ACC_4          BIT 0xe4
_ACC_5          BIT 0xe5
_ACC_6          BIT 0xe6
_ACC_7          BIT 0xe7
_TEMPE          BIT 0xe8
_ADGN0          BIT 0xe9
_ADGN1          BIT 0xea
_ADWINT         BIT 0xeb
_ADBUSY         BIT 0xec
_ADINT          BIT 0xed
_IPOEN          BIT 0xee
_ADEN           BIT 0xef
_B_0            BIT 0xf0
_B_1            BIT 0xf1
_B_2            BIT 0xf2
_B_3            BIT 0xf3
_B_4            BIT 0xf4
_B_5            BIT 0xf5
_B_6            BIT 0xf6
_B_7            BIT 0xf7
_C0FIF          BIT 0xe8
_C0RIF          BIT 0xe9
_C1FIF          BIT 0xea
_C1RIF          BIT 0xeb
_C2FIF          BIT 0xec
_C2RIF          BIT 0xed
_C3FIF          BIT 0xee
_C3RIF          BIT 0xef
_D1SRC0         BIT 0x88
_D1SRC1         BIT 0x89
_D1AMEN         BIT 0x8a
_D01REFSL       BIT 0x8b
_D3SRC0         BIT 0x8c
_D3SRC1         BIT 0x8d
_D3AMEN         BIT 0x8e
_D23REFSL       BIT 0x8f
_D0UDIS         BIT 0x98
_D1UDIS         BIT 0x99
_D2UDIS         BIT 0x9a
_D3UDIS         BIT 0x9b
_EX0            BIT 0xa8
_ET0            BIT 0xa9
_EX1            BIT 0xaa
_ET1            BIT 0xab
_ES0            BIT 0xac
_ET2            BIT 0xad
_ESPI0          BIT 0xae
_EA             BIT 0xaf
_PX0            BIT 0xb8
_PT0            BIT 0xb9
_PX1            BIT 0xba
_PT1            BIT 0xbb
_PS0            BIT 0xbc
_PT2            BIT 0xbd
_PSPI0          BIT 0xbe
_P0_0           BIT 0x80
_P0_1           BIT 0x81
_P0_2           BIT 0x82
_P0_3           BIT 0x83
_P0_4           BIT 0x84
_P0_5           BIT 0x85
_P0_6           BIT 0x86
_P0_7           BIT 0x87
_P1_0           BIT 0x90
_P1_1           BIT 0x91
_P1_2           BIT 0x92
_P1_3           BIT 0x93
_P1_4           BIT 0x94
_P1_5           BIT 0x95
_P1_6           BIT 0x96
_P1_7           BIT 0x97
_P2_0           BIT 0xa0
_P2_1           BIT 0xa1
_P2_2           BIT 0xa2
_P2_3           BIT 0xa3
_P2_4           BIT 0xa4
_P2_5           BIT 0xa5
_P2_6           BIT 0xa6
_P3_0           BIT 0xb0
_P3_1           BIT 0xb1
_P3_2           BIT 0xb2
_P3_3           BIT 0xb3
_P3_4           BIT 0xb4
_P3_7           BIT 0xb7
_CCF0           BIT 0xd8
_CCF1           BIT 0xd9
_CCF2           BIT 0xda
_CCF3           BIT 0xdb
_CCF4           BIT 0xdc
_CCF5           BIT 0xdd
_CR             BIT 0xde
_CF             BIT 0xdf
_PARITY         BIT 0xd0
_F1             BIT 0xd1
_OV             BIT 0xd2
_RS0            BIT 0xd3
_RS1            BIT 0xd4
_F0             BIT 0xd5
_AC             BIT 0xd6
_CY             BIT 0xd7
_RI             BIT 0x98
_TI             BIT 0x99
_RB8            BIT 0x9a
_TB8            BIT 0x9b
_REN            BIT 0x9c
_CE             BIT 0x9d
_SMODE          BIT 0x9e
_RI1            BIT 0xc8
_TI1            BIT 0xc9
_RBX1           BIT 0xca
_TBX1           BIT 0xcb
_REN1           BIT 0xcc
_PERR1          BIT 0xcd
_OVR1           BIT 0xce
_SI             BIT 0xc0
_ACK            BIT 0xc1
_ARBLOST        BIT 0xc2
_ACKRQ          BIT 0xc3
_STO            BIT 0xc4
_STA            BIT 0xc5
_TXMODE         BIT 0xc6
_MASTER         BIT 0xc7
_SPIEN          BIT 0xf8
_TXNF           BIT 0xf9
_NSSMD0         BIT 0xfa
_NSSMD1         BIT 0xfb
_RXOVRN         BIT 0xfc
_MODF           BIT 0xfd
_WCOL           BIT 0xfe
_SPIF           BIT 0xff
_IT0            BIT 0x88
_IE0            BIT 0x89
_IT1            BIT 0x8a
_IE1            BIT 0x8b
_TR0            BIT 0x8c
_TF0            BIT 0x8d
_TR1            BIT 0x8e
_TF1            BIT 0x8f
_T2XCLK0        BIT 0xc8
_T2XCLK1        BIT 0xc9
_TR2            BIT 0xca
_T2SPLIT        BIT 0xcb
_TF2CEN         BIT 0xcc
_TF2LEN         BIT 0xcd
_TF2L           BIT 0xce
_TF2H           BIT 0xcf
_T4XCLK0        BIT 0x98
_T4XCLK1        BIT 0x99
_TR4            BIT 0x9a
_T4SPLIT        BIT 0x9b
_TF4CEN         BIT 0x9c
_TF4LEN         BIT 0x9d
_TF4L           BIT 0x9e
_TF4H           BIT 0x9f
_T5XCLK0        BIT 0xc0
_T5XCLK1        BIT 0xc1
_TR5            BIT 0xc2
_T5SPLIT        BIT 0xc3
_TF5CEN         BIT 0xc4
_TF5LEN         BIT 0xc5
_TF5L           BIT 0xc6
_TF5H           BIT 0xc7
_RIE            BIT 0xd8
_RXTO0          BIT 0xd9
_RXTO1          BIT 0xda
_RFRQ           BIT 0xdb
_TIE            BIT 0xdc
_TXHOLD         BIT 0xdd
_TXNF1          BIT 0xde
_TFRQ           BIT 0xdf
;--------------------------------------------------------
; overlayable register banks
;--------------------------------------------------------
	rbank0 segment data overlay
;--------------------------------------------------------
; internal ram data
;--------------------------------------------------------
	rseg R_DSEG
_servo_counter:
	ds 2
_servo1:
	ds 1
_servo2:
	ds 1
_PrintNumber_PARM_2:
	ds 2
_PrintNumber_PARM_3:
	ds 2
_PrintNumber_val_1_80:
	ds 4
_PrintNumber_j_1_81:
	ds 2
_PrintNumber_sloc0_1_0:
	ds 2
_PrintNumber_sloc1_1_0:
	ds 4
;--------------------------------------------------------
; overlayable items in internal ram 
;--------------------------------------------------------
	rseg	R_OSEG
_InitPinADC_PARM_2:
	ds 1
	rseg	R_OSEG
	rseg	R_OSEG
	rseg	R_OSEG
;--------------------------------------------------------
; indirectly addressable internal ram data
;--------------------------------------------------------
	rseg R_ISEG
;--------------------------------------------------------
; absolute internal ram data
;--------------------------------------------------------
	DSEG
;--------------------------------------------------------
; bit data
;--------------------------------------------------------
	rseg R_BSEG
;--------------------------------------------------------
; paged external ram data
;--------------------------------------------------------
	rseg R_PSEG
;--------------------------------------------------------
; external ram data
;--------------------------------------------------------
	rseg R_XSEG
_PrintNumber_buff_1_81:
	ds 33
;--------------------------------------------------------
; absolute external ram data
;--------------------------------------------------------
	XSEG
;--------------------------------------------------------
; external initialized ram data
;--------------------------------------------------------
	rseg R_IXSEG
	rseg R_HOME
	rseg R_GSINIT
	rseg R_CSEG
;--------------------------------------------------------
; Reset entry point and interrupt vectors
;--------------------------------------------------------
	CSEG at 0x0000
	ljmp	_crt0
	CSEG at 0x0093
	ljmp	_Timer5_ISR
;--------------------------------------------------------
; global & static initialisations
;--------------------------------------------------------
	rseg R_HOME
	rseg R_GSINIT
	rseg R_GSINIT
;--------------------------------------------------------
; data variables initialization
;--------------------------------------------------------
	rseg R_DINIT
;	C:\Muntakim_Files\School\School_Work\Engineering_Bachelors\2023\ELEC_291\Projects\Project_2\ELEC291Project2\EFM8\Examples\Robot_Base\Robot_Base.c:5: volatile unsigned int servo_counter=0;
	clr	a
	mov	_servo_counter,a
	mov	(_servo_counter + 1),a
;	C:\Muntakim_Files\School\School_Work\Engineering_Bachelors\2023\ELEC_291\Projects\Project_2\ELEC291Project2\EFM8\Examples\Robot_Base\Robot_Base.c:6: volatile unsigned char servo1=150, servo2=150;
	mov	_servo1,#0x96
;	C:\Muntakim_Files\School\School_Work\Engineering_Bachelors\2023\ELEC_291\Projects\Project_2\ELEC291Project2\EFM8\Examples\Robot_Base\Robot_Base.c:6: 
	mov	_servo2,#0x96
	; The linker places a 'ret' at the end of segment R_DINIT.
;--------------------------------------------------------
; code
;--------------------------------------------------------
	rseg R_CSEG
;------------------------------------------------------------
;Allocation info for local variables in function '_c51_external_startup'
;------------------------------------------------------------
;------------------------------------------------------------
;	C:\Muntakim_Files\School\School_Work\Engineering_Bachelors\2023\ELEC_291\Projects\Project_2\ELEC291Project2\EFM8\Examples\Robot_Base\Robot_Base.c:30: char _c51_external_startup (void)
;	-----------------------------------------
;	 function _c51_external_startup
;	-----------------------------------------
__c51_external_startup:
	using	0
;	C:\Muntakim_Files\School\School_Work\Engineering_Bachelors\2023\ELEC_291\Projects\Project_2\ELEC291Project2\EFM8\Examples\Robot_Base\Robot_Base.c:33: SFRPAGE = 0x00;
	mov	_SFRPAGE,#0x00
;	C:\Muntakim_Files\School\School_Work\Engineering_Bachelors\2023\ELEC_291\Projects\Project_2\ELEC291Project2\EFM8\Examples\Robot_Base\Robot_Base.c:34: WDTCN = 0xDE; //First key
	mov	_WDTCN,#0xDE
;	C:\Muntakim_Files\School\School_Work\Engineering_Bachelors\2023\ELEC_291\Projects\Project_2\ELEC291Project2\EFM8\Examples\Robot_Base\Robot_Base.c:35: WDTCN = 0xAD; //Second key
	mov	_WDTCN,#0xAD
;	C:\Muntakim_Files\School\School_Work\Engineering_Bachelors\2023\ELEC_291\Projects\Project_2\ELEC291Project2\EFM8\Examples\Robot_Base\Robot_Base.c:37: VDM0CN |= 0x80;
	orl	_VDM0CN,#0x80
;	C:\Muntakim_Files\School\School_Work\Engineering_Bachelors\2023\ELEC_291\Projects\Project_2\ELEC291Project2\EFM8\Examples\Robot_Base\Robot_Base.c:38: RSTSRC = 0x02;
	mov	_RSTSRC,#0x02
;	C:\Muntakim_Files\School\School_Work\Engineering_Bachelors\2023\ELEC_291\Projects\Project_2\ELEC291Project2\EFM8\Examples\Robot_Base\Robot_Base.c:45: SFRPAGE = 0x10;
	mov	_SFRPAGE,#0x10
;	C:\Muntakim_Files\School\School_Work\Engineering_Bachelors\2023\ELEC_291\Projects\Project_2\ELEC291Project2\EFM8\Examples\Robot_Base\Robot_Base.c:46: PFE0CN  = 0x20; // SYSCLK < 75 MHz.
	mov	_PFE0CN,#0x20
;	C:\Muntakim_Files\School\School_Work\Engineering_Bachelors\2023\ELEC_291\Projects\Project_2\ELEC291Project2\EFM8\Examples\Robot_Base\Robot_Base.c:47: SFRPAGE = 0x00;
	mov	_SFRPAGE,#0x00
;	C:\Muntakim_Files\School\School_Work\Engineering_Bachelors\2023\ELEC_291\Projects\Project_2\ELEC291Project2\EFM8\Examples\Robot_Base\Robot_Base.c:68: CLKSEL = 0x00;
	mov	_CLKSEL,#0x00
;	C:\Muntakim_Files\School\School_Work\Engineering_Bachelors\2023\ELEC_291\Projects\Project_2\ELEC291Project2\EFM8\Examples\Robot_Base\Robot_Base.c:69: CLKSEL = 0x00;
	mov	_CLKSEL,#0x00
;	C:\Muntakim_Files\School\School_Work\Engineering_Bachelors\2023\ELEC_291\Projects\Project_2\ELEC291Project2\EFM8\Examples\Robot_Base\Robot_Base.c:70: while ((CLKSEL & 0x80) == 0);
L002001?:
	mov	a,_CLKSEL
	jnb	acc.7,L002001?
;	C:\Muntakim_Files\School\School_Work\Engineering_Bachelors\2023\ELEC_291\Projects\Project_2\ELEC291Project2\EFM8\Examples\Robot_Base\Robot_Base.c:71: CLKSEL = 0x03;
	mov	_CLKSEL,#0x03
;	C:\Muntakim_Files\School\School_Work\Engineering_Bachelors\2023\ELEC_291\Projects\Project_2\ELEC291Project2\EFM8\Examples\Robot_Base\Robot_Base.c:72: CLKSEL = 0x03;
	mov	_CLKSEL,#0x03
;	C:\Muntakim_Files\School\School_Work\Engineering_Bachelors\2023\ELEC_291\Projects\Project_2\ELEC291Project2\EFM8\Examples\Robot_Base\Robot_Base.c:73: while ((CLKSEL & 0x80) == 0);
L002004?:
	mov	a,_CLKSEL
	jnb	acc.7,L002004?
;	C:\Muntakim_Files\School\School_Work\Engineering_Bachelors\2023\ELEC_291\Projects\Project_2\ELEC291Project2\EFM8\Examples\Robot_Base\Robot_Base.c:80: P0MDOUT |= 0b_0001_0000; // Configure UART0 TX (P0.4) as push-pull output
	orl	_P0MDOUT,#0x10
;	C:\Muntakim_Files\School\School_Work\Engineering_Bachelors\2023\ELEC_291\Projects\Project_2\ELEC291Project2\EFM8\Examples\Robot_Base\Robot_Base.c:81: XBR0     = 0x01; // Enable UART0 on P0.4(TX) and P0.5(RX)
	mov	_XBR0,#0x01
;	C:\Muntakim_Files\School\School_Work\Engineering_Bachelors\2023\ELEC_291\Projects\Project_2\ELEC291Project2\EFM8\Examples\Robot_Base\Robot_Base.c:82: XBR1     = 0X00; //
	mov	_XBR1,#0x00
;	C:\Muntakim_Files\School\School_Work\Engineering_Bachelors\2023\ELEC_291\Projects\Project_2\ELEC291Project2\EFM8\Examples\Robot_Base\Robot_Base.c:83: XBR2     = 0x40; // Enable crossbar and weak pull-ups
	mov	_XBR2,#0x40
;	C:\Muntakim_Files\School\School_Work\Engineering_Bachelors\2023\ELEC_291\Projects\Project_2\ELEC291Project2\EFM8\Examples\Robot_Base\Robot_Base.c:89: SCON0 = 0x10;
	mov	_SCON0,#0x10
;	C:\Muntakim_Files\School\School_Work\Engineering_Bachelors\2023\ELEC_291\Projects\Project_2\ELEC291Project2\EFM8\Examples\Robot_Base\Robot_Base.c:90: CKCON0 |= 0b_0000_0000 ; // Timer 1 uses the system clock divided by 12.
	mov	_CKCON0,_CKCON0
;	C:\Muntakim_Files\School\School_Work\Engineering_Bachelors\2023\ELEC_291\Projects\Project_2\ELEC291Project2\EFM8\Examples\Robot_Base\Robot_Base.c:91: TH1 = 0x100-((SYSCLK/BAUDRATE)/(2L*12L));
	mov	_TH1,#0xE6
;	C:\Muntakim_Files\School\School_Work\Engineering_Bachelors\2023\ELEC_291\Projects\Project_2\ELEC291Project2\EFM8\Examples\Robot_Base\Robot_Base.c:92: TL1 = TH1;      // Init Timer1
	mov	_TL1,_TH1
;	C:\Muntakim_Files\School\School_Work\Engineering_Bachelors\2023\ELEC_291\Projects\Project_2\ELEC291Project2\EFM8\Examples\Robot_Base\Robot_Base.c:93: TMOD &= ~0xf0;  // TMOD: timer 1 in 8-bit auto-reload
	anl	_TMOD,#0x0F
;	C:\Muntakim_Files\School\School_Work\Engineering_Bachelors\2023\ELEC_291\Projects\Project_2\ELEC291Project2\EFM8\Examples\Robot_Base\Robot_Base.c:94: TMOD |=  0x20;
	orl	_TMOD,#0x20
;	C:\Muntakim_Files\School\School_Work\Engineering_Bachelors\2023\ELEC_291\Projects\Project_2\ELEC291Project2\EFM8\Examples\Robot_Base\Robot_Base.c:95: TR1 = 1; // START Timer1
	setb	_TR1
;	C:\Muntakim_Files\School\School_Work\Engineering_Bachelors\2023\ELEC_291\Projects\Project_2\ELEC291Project2\EFM8\Examples\Robot_Base\Robot_Base.c:96: TI = 1;  // Indicate TX0 ready
	setb	_TI
;	C:\Muntakim_Files\School\School_Work\Engineering_Bachelors\2023\ELEC_291\Projects\Project_2\ELEC291Project2\EFM8\Examples\Robot_Base\Robot_Base.c:99: SFRPAGE=0x10;
	mov	_SFRPAGE,#0x10
;	C:\Muntakim_Files\School\School_Work\Engineering_Bachelors\2023\ELEC_291\Projects\Project_2\ELEC291Project2\EFM8\Examples\Robot_Base\Robot_Base.c:100: TMR5CN0=0x00;
	mov	_TMR5CN0,#0x00
;	C:\Muntakim_Files\School\School_Work\Engineering_Bachelors\2023\ELEC_291\Projects\Project_2\ELEC291Project2\EFM8\Examples\Robot_Base\Robot_Base.c:101: TMR5=0xffff;   // Set to reload immediately
	mov	_TMR5,#0xFF
	mov	(_TMR5 >> 8),#0xFF
;	C:\Muntakim_Files\School\School_Work\Engineering_Bachelors\2023\ELEC_291\Projects\Project_2\ELEC291Project2\EFM8\Examples\Robot_Base\Robot_Base.c:102: EIE2|=0b_0000_1000; // Enable Timer5 interrupts
	orl	_EIE2,#0x08
;	C:\Muntakim_Files\School\School_Work\Engineering_Bachelors\2023\ELEC_291\Projects\Project_2\ELEC291Project2\EFM8\Examples\Robot_Base\Robot_Base.c:103: TR5=1;         // Start Timer5 (TMR5CN0 is bit addressable)
	setb	_TR5
;	C:\Muntakim_Files\School\School_Work\Engineering_Bachelors\2023\ELEC_291\Projects\Project_2\ELEC291Project2\EFM8\Examples\Robot_Base\Robot_Base.c:105: EA=1;
	setb	_EA
;	C:\Muntakim_Files\School\School_Work\Engineering_Bachelors\2023\ELEC_291\Projects\Project_2\ELEC291Project2\EFM8\Examples\Robot_Base\Robot_Base.c:107: SFRPAGE=0x00;
	mov	_SFRPAGE,#0x00
;	C:\Muntakim_Files\School\School_Work\Engineering_Bachelors\2023\ELEC_291\Projects\Project_2\ELEC291Project2\EFM8\Examples\Robot_Base\Robot_Base.c:109: return 0;
	mov	dpl,#0x00
	ret
;------------------------------------------------------------
;Allocation info for local variables in function 'InitADC'
;------------------------------------------------------------
;------------------------------------------------------------
;	C:\Muntakim_Files\School\School_Work\Engineering_Bachelors\2023\ELEC_291\Projects\Project_2\ELEC291Project2\EFM8\Examples\Robot_Base\Robot_Base.c:112: void InitADC (void)
;	-----------------------------------------
;	 function InitADC
;	-----------------------------------------
_InitADC:
;	C:\Muntakim_Files\School\School_Work\Engineering_Bachelors\2023\ELEC_291\Projects\Project_2\ELEC291Project2\EFM8\Examples\Robot_Base\Robot_Base.c:114: SFRPAGE = 0x00;
	mov	_SFRPAGE,#0x00
;	C:\Muntakim_Files\School\School_Work\Engineering_Bachelors\2023\ELEC_291\Projects\Project_2\ELEC291Project2\EFM8\Examples\Robot_Base\Robot_Base.c:115: ADEN=0; // Disable ADC
	clr	_ADEN
;	C:\Muntakim_Files\School\School_Work\Engineering_Bachelors\2023\ELEC_291\Projects\Project_2\ELEC291Project2\EFM8\Examples\Robot_Base\Robot_Base.c:120: (0x0 << 0) ; // Accumulate n conversions: 0x0: 1, 0x1:4, 0x2:8, 0x3:16, 0x4:32
	mov	_ADC0CN1,#0x80
;	C:\Muntakim_Files\School\School_Work\Engineering_Bachelors\2023\ELEC_291\Projects\Project_2\ELEC291Project2\EFM8\Examples\Robot_Base\Robot_Base.c:124: (0x0 << 2); // 0:SYSCLK ADCCLK = SYSCLK. 1:HFOSC0 ADCCLK = HFOSC0.
	mov	_ADC0CF0,#0x20
;	C:\Muntakim_Files\School\School_Work\Engineering_Bachelors\2023\ELEC_291\Projects\Project_2\ELEC291Project2\EFM8\Examples\Robot_Base\Robot_Base.c:128: (0x1E << 0); // Conversion Tracking Time. Tadtk = ADTK / (Fsarclk)
	mov	_ADC0CF1,#0x1E
;	C:\Muntakim_Files\School\School_Work\Engineering_Bachelors\2023\ELEC_291\Projects\Project_2\ELEC291Project2\EFM8\Examples\Robot_Base\Robot_Base.c:137: (0x0 << 0) ; // TEMPE. 0: Disable the Temperature Sensor. 1: Enable the Temperature Sensor.
	mov	_ADC0CN0,#0x00
;	C:\Muntakim_Files\School\School_Work\Engineering_Bachelors\2023\ELEC_291\Projects\Project_2\ELEC291Project2\EFM8\Examples\Robot_Base\Robot_Base.c:142: (0x1F << 0); // ADPWR. Power Up Delay Time. Tpwrtime = ((4 * (ADPWR + 1)) + 2) / (Fadcclk)
	mov	_ADC0CF2,#0x3F
;	C:\Muntakim_Files\School\School_Work\Engineering_Bachelors\2023\ELEC_291\Projects\Project_2\ELEC291Project2\EFM8\Examples\Robot_Base\Robot_Base.c:146: (0x0 << 0) ; // ADCM. 0x0: ADBUSY, 0x1: TIMER0, 0x2: TIMER2, 0x3: TIMER3, 0x4: CNVSTR, 0x5: CEX5, 0x6: TIMER4, 0x7: TIMER5, 0x8: CLU0, 0x9: CLU1, 0xA: CLU2, 0xB: CLU3
	mov	_ADC0CN2,#0x00
;	C:\Muntakim_Files\School\School_Work\Engineering_Bachelors\2023\ELEC_291\Projects\Project_2\ELEC291Project2\EFM8\Examples\Robot_Base\Robot_Base.c:148: ADEN=1; // Enable ADC
	setb	_ADEN
	ret
;------------------------------------------------------------
;Allocation info for local variables in function 'InitPinADC'
;------------------------------------------------------------
;pin_num                   Allocated with name '_InitPinADC_PARM_2'
;portno                    Allocated to registers r2 
;mask                      Allocated to registers r3 
;------------------------------------------------------------
;	C:\Muntakim_Files\School\School_Work\Engineering_Bachelors\2023\ELEC_291\Projects\Project_2\ELEC291Project2\EFM8\Examples\Robot_Base\Robot_Base.c:151: void InitPinADC (unsigned char portno, unsigned char pin_num)
;	-----------------------------------------
;	 function InitPinADC
;	-----------------------------------------
_InitPinADC:
	mov	r2,dpl
;	C:\Muntakim_Files\School\School_Work\Engineering_Bachelors\2023\ELEC_291\Projects\Project_2\ELEC291Project2\EFM8\Examples\Robot_Base\Robot_Base.c:155: mask=1<<pin_num;
	mov	b,_InitPinADC_PARM_2
	inc	b
	mov	a,#0x01
	sjmp	L004013?
L004011?:
	add	a,acc
L004013?:
	djnz	b,L004011?
	mov	r3,a
;	C:\Muntakim_Files\School\School_Work\Engineering_Bachelors\2023\ELEC_291\Projects\Project_2\ELEC291Project2\EFM8\Examples\Robot_Base\Robot_Base.c:157: SFRPAGE = 0x20;
	mov	_SFRPAGE,#0x20
;	C:\Muntakim_Files\School\School_Work\Engineering_Bachelors\2023\ELEC_291\Projects\Project_2\ELEC291Project2\EFM8\Examples\Robot_Base\Robot_Base.c:158: switch (portno)
	cjne	r2,#0x00,L004014?
	sjmp	L004001?
L004014?:
	cjne	r2,#0x01,L004015?
	sjmp	L004002?
L004015?:
;	C:\Muntakim_Files\School\School_Work\Engineering_Bachelors\2023\ELEC_291\Projects\Project_2\ELEC291Project2\EFM8\Examples\Robot_Base\Robot_Base.c:160: case 0:
	cjne	r2,#0x02,L004005?
	sjmp	L004003?
L004001?:
;	C:\Muntakim_Files\School\School_Work\Engineering_Bachelors\2023\ELEC_291\Projects\Project_2\ELEC291Project2\EFM8\Examples\Robot_Base\Robot_Base.c:161: P0MDIN &= (~mask); // Set pin as analog input
	mov	a,r3
	cpl	a
	mov	r2,a
	anl	_P0MDIN,a
;	C:\Muntakim_Files\School\School_Work\Engineering_Bachelors\2023\ELEC_291\Projects\Project_2\ELEC291Project2\EFM8\Examples\Robot_Base\Robot_Base.c:162: P0SKIP |= mask; // Skip Crossbar decoding for this pin
	mov	a,r3
	orl	_P0SKIP,a
;	C:\Muntakim_Files\School\School_Work\Engineering_Bachelors\2023\ELEC_291\Projects\Project_2\ELEC291Project2\EFM8\Examples\Robot_Base\Robot_Base.c:163: break;
;	C:\Muntakim_Files\School\School_Work\Engineering_Bachelors\2023\ELEC_291\Projects\Project_2\ELEC291Project2\EFM8\Examples\Robot_Base\Robot_Base.c:164: case 1:
	sjmp	L004005?
L004002?:
;	C:\Muntakim_Files\School\School_Work\Engineering_Bachelors\2023\ELEC_291\Projects\Project_2\ELEC291Project2\EFM8\Examples\Robot_Base\Robot_Base.c:165: P1MDIN &= (~mask); // Set pin as analog input
	mov	a,r3
	cpl	a
	mov	r2,a
	anl	_P1MDIN,a
;	C:\Muntakim_Files\School\School_Work\Engineering_Bachelors\2023\ELEC_291\Projects\Project_2\ELEC291Project2\EFM8\Examples\Robot_Base\Robot_Base.c:166: P1SKIP |= mask; // Skip Crossbar decoding for this pin
	mov	a,r3
	orl	_P1SKIP,a
;	C:\Muntakim_Files\School\School_Work\Engineering_Bachelors\2023\ELEC_291\Projects\Project_2\ELEC291Project2\EFM8\Examples\Robot_Base\Robot_Base.c:167: break;
;	C:\Muntakim_Files\School\School_Work\Engineering_Bachelors\2023\ELEC_291\Projects\Project_2\ELEC291Project2\EFM8\Examples\Robot_Base\Robot_Base.c:168: case 2:
	sjmp	L004005?
L004003?:
;	C:\Muntakim_Files\School\School_Work\Engineering_Bachelors\2023\ELEC_291\Projects\Project_2\ELEC291Project2\EFM8\Examples\Robot_Base\Robot_Base.c:169: P2MDIN &= (~mask); // Set pin as analog input
	mov	a,r3
	cpl	a
	mov	r2,a
	anl	_P2MDIN,a
;	C:\Muntakim_Files\School\School_Work\Engineering_Bachelors\2023\ELEC_291\Projects\Project_2\ELEC291Project2\EFM8\Examples\Robot_Base\Robot_Base.c:170: P2SKIP |= mask; // Skip Crossbar decoding for this pin
	mov	a,r3
	orl	_P2SKIP,a
;	C:\Muntakim_Files\School\School_Work\Engineering_Bachelors\2023\ELEC_291\Projects\Project_2\ELEC291Project2\EFM8\Examples\Robot_Base\Robot_Base.c:174: }
L004005?:
;	C:\Muntakim_Files\School\School_Work\Engineering_Bachelors\2023\ELEC_291\Projects\Project_2\ELEC291Project2\EFM8\Examples\Robot_Base\Robot_Base.c:175: SFRPAGE = 0x00;
	mov	_SFRPAGE,#0x00
	ret
;------------------------------------------------------------
;Allocation info for local variables in function 'ADC_at_Pin'
;------------------------------------------------------------
;pin                       Allocated to registers 
;------------------------------------------------------------
;	C:\Muntakim_Files\School\School_Work\Engineering_Bachelors\2023\ELEC_291\Projects\Project_2\ELEC291Project2\EFM8\Examples\Robot_Base\Robot_Base.c:178: unsigned int ADC_at_Pin(unsigned char pin)
;	-----------------------------------------
;	 function ADC_at_Pin
;	-----------------------------------------
_ADC_at_Pin:
	mov	_ADC0MX,dpl
;	C:\Muntakim_Files\School\School_Work\Engineering_Bachelors\2023\ELEC_291\Projects\Project_2\ELEC291Project2\EFM8\Examples\Robot_Base\Robot_Base.c:181: ADINT = 0;
	clr	_ADINT
;	C:\Muntakim_Files\School\School_Work\Engineering_Bachelors\2023\ELEC_291\Projects\Project_2\ELEC291Project2\EFM8\Examples\Robot_Base\Robot_Base.c:182: ADBUSY = 1;     // Convert voltage at the pin
	setb	_ADBUSY
;	C:\Muntakim_Files\School\School_Work\Engineering_Bachelors\2023\ELEC_291\Projects\Project_2\ELEC291Project2\EFM8\Examples\Robot_Base\Robot_Base.c:183: while (!ADINT); // Wait for conversion to complete
L005001?:
	jnb	_ADINT,L005001?
;	C:\Muntakim_Files\School\School_Work\Engineering_Bachelors\2023\ELEC_291\Projects\Project_2\ELEC291Project2\EFM8\Examples\Robot_Base\Robot_Base.c:184: return (ADC0);
	mov	dpl,_ADC0
	mov	dph,(_ADC0 >> 8)
	ret
;------------------------------------------------------------
;Allocation info for local variables in function 'Timer5_ISR'
;------------------------------------------------------------
;------------------------------------------------------------
;	C:\Muntakim_Files\School\School_Work\Engineering_Bachelors\2023\ELEC_291\Projects\Project_2\ELEC291Project2\EFM8\Examples\Robot_Base\Robot_Base.c:187: void Timer5_ISR (void) interrupt INTERRUPT_TIMER5
;	-----------------------------------------
;	 function Timer5_ISR
;	-----------------------------------------
_Timer5_ISR:
	push	acc
	push	ar2
	push	ar3
	push	psw
	mov	psw,#0x00
;	C:\Muntakim_Files\School\School_Work\Engineering_Bachelors\2023\ELEC_291\Projects\Project_2\ELEC291Project2\EFM8\Examples\Robot_Base\Robot_Base.c:189: SFRPAGE=0x10;
	mov	_SFRPAGE,#0x10
;	C:\Muntakim_Files\School\School_Work\Engineering_Bachelors\2023\ELEC_291\Projects\Project_2\ELEC291Project2\EFM8\Examples\Robot_Base\Robot_Base.c:190: TF5H = 0; // Clear Timer5 interrupt flag
	clr	_TF5H
;	C:\Muntakim_Files\School\School_Work\Engineering_Bachelors\2023\ELEC_291\Projects\Project_2\ELEC291Project2\EFM8\Examples\Robot_Base\Robot_Base.c:191: TMR5RL=RELOAD_10us;
	mov	_TMR5RL,#0xC4
	mov	(_TMR5RL >> 8),#0xFF
;	C:\Muntakim_Files\School\School_Work\Engineering_Bachelors\2023\ELEC_291\Projects\Project_2\ELEC291Project2\EFM8\Examples\Robot_Base\Robot_Base.c:192: servo_counter++;
	mov	a,#0x01
	add	a,_servo_counter
	mov	_servo_counter,a
	clr	a
	addc	a,(_servo_counter + 1)
	mov	(_servo_counter + 1),a
;	C:\Muntakim_Files\School\School_Work\Engineering_Bachelors\2023\ELEC_291\Projects\Project_2\ELEC291Project2\EFM8\Examples\Robot_Base\Robot_Base.c:193: if(servo_counter==2000)
	mov	a,#0xD0
	cjne	a,_servo_counter,L006002?
	mov	a,#0x07
	cjne	a,(_servo_counter + 1),L006002?
;	C:\Muntakim_Files\School\School_Work\Engineering_Bachelors\2023\ELEC_291\Projects\Project_2\ELEC291Project2\EFM8\Examples\Robot_Base\Robot_Base.c:195: servo_counter=0;
	clr	a
	mov	_servo_counter,a
	mov	(_servo_counter + 1),a
L006002?:
;	C:\Muntakim_Files\School\School_Work\Engineering_Bachelors\2023\ELEC_291\Projects\Project_2\ELEC291Project2\EFM8\Examples\Robot_Base\Robot_Base.c:197: if(servo1>=servo_counter)
	mov	r2,_servo1
	mov	r3,#0x00
	clr	c
	mov	a,r2
	subb	a,_servo_counter
	mov	a,r3
	subb	a,(_servo_counter + 1)
	jc	L006004?
;	C:\Muntakim_Files\School\School_Work\Engineering_Bachelors\2023\ELEC_291\Projects\Project_2\ELEC291Project2\EFM8\Examples\Robot_Base\Robot_Base.c:199: SERVO1=1;
	setb	_P1_4
	sjmp	L006005?
L006004?:
;	C:\Muntakim_Files\School\School_Work\Engineering_Bachelors\2023\ELEC_291\Projects\Project_2\ELEC291Project2\EFM8\Examples\Robot_Base\Robot_Base.c:203: SERVO1=0;
	clr	_P1_4
L006005?:
;	C:\Muntakim_Files\School\School_Work\Engineering_Bachelors\2023\ELEC_291\Projects\Project_2\ELEC291Project2\EFM8\Examples\Robot_Base\Robot_Base.c:205: if(servo2>=servo_counter)
	mov	r2,_servo2
	mov	r3,#0x00
	clr	c
	mov	a,r2
	subb	a,_servo_counter
	mov	a,r3
	subb	a,(_servo_counter + 1)
	jc	L006007?
;	C:\Muntakim_Files\School\School_Work\Engineering_Bachelors\2023\ELEC_291\Projects\Project_2\ELEC291Project2\EFM8\Examples\Robot_Base\Robot_Base.c:207: SERVO2=1;
	setb	_P1_4
	sjmp	L006009?
L006007?:
;	C:\Muntakim_Files\School\School_Work\Engineering_Bachelors\2023\ELEC_291\Projects\Project_2\ELEC291Project2\EFM8\Examples\Robot_Base\Robot_Base.c:211: SERVO2=0;
	clr	_P1_4
L006009?:
	pop	psw
	pop	ar3
	pop	ar2
	pop	acc
	reti
;	eliminated unneeded push/pop dpl
;	eliminated unneeded push/pop dph
;	eliminated unneeded push/pop b
;------------------------------------------------------------
;Allocation info for local variables in function 'Timer3us'
;------------------------------------------------------------
;us                        Allocated to registers r2 
;i                         Allocated to registers r3 
;------------------------------------------------------------
;	C:\Muntakim_Files\School\School_Work\Engineering_Bachelors\2023\ELEC_291\Projects\Project_2\ELEC291Project2\EFM8\Examples\Robot_Base\Robot_Base.c:216: void Timer3us(unsigned char us)
;	-----------------------------------------
;	 function Timer3us
;	-----------------------------------------
_Timer3us:
	mov	r2,dpl
;	C:\Muntakim_Files\School\School_Work\Engineering_Bachelors\2023\ELEC_291\Projects\Project_2\ELEC291Project2\EFM8\Examples\Robot_Base\Robot_Base.c:221: CKCON0|=0b_0100_0000;
	orl	_CKCON0,#0x40
;	C:\Muntakim_Files\School\School_Work\Engineering_Bachelors\2023\ELEC_291\Projects\Project_2\ELEC291Project2\EFM8\Examples\Robot_Base\Robot_Base.c:223: TMR3RL = (-(SYSCLK)/1000000L); // Set Timer3 to overflow in 1us.
	mov	_TMR3RL,#0xB8
	mov	(_TMR3RL >> 8),#0xFF
;	C:\Muntakim_Files\School\School_Work\Engineering_Bachelors\2023\ELEC_291\Projects\Project_2\ELEC291Project2\EFM8\Examples\Robot_Base\Robot_Base.c:224: TMR3 = TMR3RL;                 // Initialize Timer3 for first overflow
	mov	_TMR3,_TMR3RL
	mov	(_TMR3 >> 8),(_TMR3RL >> 8)
;	C:\Muntakim_Files\School\School_Work\Engineering_Bachelors\2023\ELEC_291\Projects\Project_2\ELEC291Project2\EFM8\Examples\Robot_Base\Robot_Base.c:226: TMR3CN0 = 0x04;                 // Sart Timer3 and clear overflow flag
	mov	_TMR3CN0,#0x04
;	C:\Muntakim_Files\School\School_Work\Engineering_Bachelors\2023\ELEC_291\Projects\Project_2\ELEC291Project2\EFM8\Examples\Robot_Base\Robot_Base.c:227: for (i = 0; i < us; i++)       // Count <us> overflows
	mov	r3,#0x00
L007004?:
	clr	c
	mov	a,r3
	subb	a,r2
	jnc	L007007?
;	C:\Muntakim_Files\School\School_Work\Engineering_Bachelors\2023\ELEC_291\Projects\Project_2\ELEC291Project2\EFM8\Examples\Robot_Base\Robot_Base.c:229: while (!(TMR3CN0 & 0x80));  // Wait for overflow
L007001?:
	mov	a,_TMR3CN0
	jnb	acc.7,L007001?
;	C:\Muntakim_Files\School\School_Work\Engineering_Bachelors\2023\ELEC_291\Projects\Project_2\ELEC291Project2\EFM8\Examples\Robot_Base\Robot_Base.c:230: TMR3CN0 &= ~(0x80);         // Clear overflow indicator
	anl	_TMR3CN0,#0x7F
;	C:\Muntakim_Files\School\School_Work\Engineering_Bachelors\2023\ELEC_291\Projects\Project_2\ELEC291Project2\EFM8\Examples\Robot_Base\Robot_Base.c:227: for (i = 0; i < us; i++)       // Count <us> overflows
	inc	r3
	sjmp	L007004?
L007007?:
;	C:\Muntakim_Files\School\School_Work\Engineering_Bachelors\2023\ELEC_291\Projects\Project_2\ELEC291Project2\EFM8\Examples\Robot_Base\Robot_Base.c:232: TMR3CN0 = 0 ;                   // Stop Timer3 and clear overflow flag
	mov	_TMR3CN0,#0x00
	ret
;------------------------------------------------------------
;Allocation info for local variables in function 'waitms'
;------------------------------------------------------------
;ms                        Allocated to registers r2 r3 
;j                         Allocated to registers r2 r3 
;------------------------------------------------------------
;	C:\Muntakim_Files\School\School_Work\Engineering_Bachelors\2023\ELEC_291\Projects\Project_2\ELEC291Project2\EFM8\Examples\Robot_Base\Robot_Base.c:235: void waitms (unsigned int ms)
;	-----------------------------------------
;	 function waitms
;	-----------------------------------------
_waitms:
	mov	r2,dpl
	mov	r3,dph
;	C:\Muntakim_Files\School\School_Work\Engineering_Bachelors\2023\ELEC_291\Projects\Project_2\ELEC291Project2\EFM8\Examples\Robot_Base\Robot_Base.c:238: for(j=ms; j!=0; j--)
L008001?:
	cjne	r2,#0x00,L008010?
	cjne	r3,#0x00,L008010?
	ret
L008010?:
;	C:\Muntakim_Files\School\School_Work\Engineering_Bachelors\2023\ELEC_291\Projects\Project_2\ELEC291Project2\EFM8\Examples\Robot_Base\Robot_Base.c:240: Timer3us(249);
	mov	dpl,#0xF9
	push	ar2
	push	ar3
	lcall	_Timer3us
;	C:\Muntakim_Files\School\School_Work\Engineering_Bachelors\2023\ELEC_291\Projects\Project_2\ELEC291Project2\EFM8\Examples\Robot_Base\Robot_Base.c:241: Timer3us(249);
	mov	dpl,#0xF9
	lcall	_Timer3us
;	C:\Muntakim_Files\School\School_Work\Engineering_Bachelors\2023\ELEC_291\Projects\Project_2\ELEC291Project2\EFM8\Examples\Robot_Base\Robot_Base.c:242: Timer3us(249);
	mov	dpl,#0xF9
	lcall	_Timer3us
;	C:\Muntakim_Files\School\School_Work\Engineering_Bachelors\2023\ELEC_291\Projects\Project_2\ELEC291Project2\EFM8\Examples\Robot_Base\Robot_Base.c:243: Timer3us(250);
	mov	dpl,#0xFA
	lcall	_Timer3us
	pop	ar3
	pop	ar2
;	C:\Muntakim_Files\School\School_Work\Engineering_Bachelors\2023\ELEC_291\Projects\Project_2\ELEC291Project2\EFM8\Examples\Robot_Base\Robot_Base.c:238: for(j=ms; j!=0; j--)
	dec	r2
	cjne	r2,#0xff,L008011?
	dec	r3
L008011?:
	sjmp	L008001?
;------------------------------------------------------------
;Allocation info for local variables in function 'GetPeriod'
;------------------------------------------------------------
;n                         Allocated to registers r2 r3 
;overflow_count            Allocated to registers r4 r5 
;i                         Allocated to registers r6 
;------------------------------------------------------------
;	C:\Muntakim_Files\School\School_Work\Engineering_Bachelors\2023\ELEC_291\Projects\Project_2\ELEC291Project2\EFM8\Examples\Robot_Base\Robot_Base.c:248: unsigned long GetPeriod (int n)
;	-----------------------------------------
;	 function GetPeriod
;	-----------------------------------------
_GetPeriod:
	mov	r2,dpl
	mov	r3,dph
;	C:\Muntakim_Files\School\School_Work\Engineering_Bachelors\2023\ELEC_291\Projects\Project_2\ELEC291Project2\EFM8\Examples\Robot_Base\Robot_Base.c:253: TR0=0; // Stop Timer/Counter 0
	clr	_TR0
;	C:\Muntakim_Files\School\School_Work\Engineering_Bachelors\2023\ELEC_291\Projects\Project_2\ELEC291Project2\EFM8\Examples\Robot_Base\Robot_Base.c:254: TMOD&=0b_1111_0000; // Set the bits of Timer/Counter 0 to zero
	anl	_TMOD,#0xF0
;	C:\Muntakim_Files\School\School_Work\Engineering_Bachelors\2023\ELEC_291\Projects\Project_2\ELEC291Project2\EFM8\Examples\Robot_Base\Robot_Base.c:255: TMOD|=0b_0000_0001; // Timer/Counter 0 used as a 16-bit timer
	orl	_TMOD,#0x01
;	C:\Muntakim_Files\School\School_Work\Engineering_Bachelors\2023\ELEC_291\Projects\Project_2\ELEC291Project2\EFM8\Examples\Robot_Base\Robot_Base.c:258: TR0=0;
	clr	_TR0
;	C:\Muntakim_Files\School\School_Work\Engineering_Bachelors\2023\ELEC_291\Projects\Project_2\ELEC291Project2\EFM8\Examples\Robot_Base\Robot_Base.c:259: TL0=0; TH0=0; TF0=0; overflow_count=0;
	mov	_TL0,#0x00
	mov	_TH0,#0x00
	clr	_TF0
;	C:\Muntakim_Files\School\School_Work\Engineering_Bachelors\2023\ELEC_291\Projects\Project_2\ELEC291Project2\EFM8\Examples\Robot_Base\Robot_Base.c:260: TR0=1;
	setb	_TR0
;	C:\Muntakim_Files\School\School_Work\Engineering_Bachelors\2023\ELEC_291\Projects\Project_2\ELEC291Project2\EFM8\Examples\Robot_Base\Robot_Base.c:261: while(PERIOD_PIN!=0) // Wait for the signal to be zero
	mov	r4,#0x00
	mov	r5,#0x00
L009005?:
	jnb	_P1_0,L009007?
;	C:\Muntakim_Files\School\School_Work\Engineering_Bachelors\2023\ELEC_291\Projects\Project_2\ELEC291Project2\EFM8\Examples\Robot_Base\Robot_Base.c:263: if(TF0==1) // Did the 16-bit timer overflow?
;	C:\Muntakim_Files\School\School_Work\Engineering_Bachelors\2023\ELEC_291\Projects\Project_2\ELEC291Project2\EFM8\Examples\Robot_Base\Robot_Base.c:265: TF0=0;
	jbc	_TF0,L009050?
	sjmp	L009005?
L009050?:
;	C:\Muntakim_Files\School\School_Work\Engineering_Bachelors\2023\ELEC_291\Projects\Project_2\ELEC291Project2\EFM8\Examples\Robot_Base\Robot_Base.c:266: overflow_count++;
	inc	r4
	cjne	r4,#0x00,L009051?
	inc	r5
L009051?:
;	C:\Muntakim_Files\School\School_Work\Engineering_Bachelors\2023\ELEC_291\Projects\Project_2\ELEC291Project2\EFM8\Examples\Robot_Base\Robot_Base.c:267: if(overflow_count==10) // If it overflows too many times assume no signal is present
	cjne	r4,#0x0A,L009005?
	cjne	r5,#0x00,L009005?
;	C:\Muntakim_Files\School\School_Work\Engineering_Bachelors\2023\ELEC_291\Projects\Project_2\ELEC291Project2\EFM8\Examples\Robot_Base\Robot_Base.c:269: TR0=0;
	clr	_TR0
;	C:\Muntakim_Files\School\School_Work\Engineering_Bachelors\2023\ELEC_291\Projects\Project_2\ELEC291Project2\EFM8\Examples\Robot_Base\Robot_Base.c:270: return 0; // No signal
	mov	dptr,#(0x00&0x00ff)
	clr	a
	mov	b,a
	ret
L009007?:
;	C:\Muntakim_Files\School\School_Work\Engineering_Bachelors\2023\ELEC_291\Projects\Project_2\ELEC291Project2\EFM8\Examples\Robot_Base\Robot_Base.c:276: TR0=0;
	clr	_TR0
;	C:\Muntakim_Files\School\School_Work\Engineering_Bachelors\2023\ELEC_291\Projects\Project_2\ELEC291Project2\EFM8\Examples\Robot_Base\Robot_Base.c:277: TL0=0; TH0=0; TF0=0; overflow_count=0;
	mov	_TL0,#0x00
	mov	_TH0,#0x00
	clr	_TF0
;	C:\Muntakim_Files\School\School_Work\Engineering_Bachelors\2023\ELEC_291\Projects\Project_2\ELEC291Project2\EFM8\Examples\Robot_Base\Robot_Base.c:278: TR0=1;
	setb	_TR0
;	C:\Muntakim_Files\School\School_Work\Engineering_Bachelors\2023\ELEC_291\Projects\Project_2\ELEC291Project2\EFM8\Examples\Robot_Base\Robot_Base.c:279: while(PERIOD_PIN!=1) // Wait for the signal to be one
	mov	r4,#0x00
	mov	r5,#0x00
L009012?:
	jb	_P1_0,L009014?
;	C:\Muntakim_Files\School\School_Work\Engineering_Bachelors\2023\ELEC_291\Projects\Project_2\ELEC291Project2\EFM8\Examples\Robot_Base\Robot_Base.c:281: if(TF0==1) // Did the 16-bit timer overflow?
;	C:\Muntakim_Files\School\School_Work\Engineering_Bachelors\2023\ELEC_291\Projects\Project_2\ELEC291Project2\EFM8\Examples\Robot_Base\Robot_Base.c:283: TF0=0;
	jbc	_TF0,L009055?
	sjmp	L009012?
L009055?:
;	C:\Muntakim_Files\School\School_Work\Engineering_Bachelors\2023\ELEC_291\Projects\Project_2\ELEC291Project2\EFM8\Examples\Robot_Base\Robot_Base.c:284: overflow_count++;
	inc	r4
	cjne	r4,#0x00,L009056?
	inc	r5
L009056?:
;	C:\Muntakim_Files\School\School_Work\Engineering_Bachelors\2023\ELEC_291\Projects\Project_2\ELEC291Project2\EFM8\Examples\Robot_Base\Robot_Base.c:285: if(overflow_count==10) // If it overflows too many times assume no signal is present
	cjne	r4,#0x0A,L009012?
	cjne	r5,#0x00,L009012?
;	C:\Muntakim_Files\School\School_Work\Engineering_Bachelors\2023\ELEC_291\Projects\Project_2\ELEC291Project2\EFM8\Examples\Robot_Base\Robot_Base.c:287: TR0=0;
	clr	_TR0
;	C:\Muntakim_Files\School\School_Work\Engineering_Bachelors\2023\ELEC_291\Projects\Project_2\ELEC291Project2\EFM8\Examples\Robot_Base\Robot_Base.c:288: return 0; // No signal
	mov	dptr,#(0x00&0x00ff)
	clr	a
	mov	b,a
	ret
L009014?:
;	C:\Muntakim_Files\School\School_Work\Engineering_Bachelors\2023\ELEC_291\Projects\Project_2\ELEC291Project2\EFM8\Examples\Robot_Base\Robot_Base.c:294: TR0=0;
	clr	_TR0
;	C:\Muntakim_Files\School\School_Work\Engineering_Bachelors\2023\ELEC_291\Projects\Project_2\ELEC291Project2\EFM8\Examples\Robot_Base\Robot_Base.c:295: TL0=0; TH0=0; TF0=0; overflow_count=0;
	mov	_TL0,#0x00
	mov	_TH0,#0x00
	clr	_TF0
	mov	r4,#0x00
	mov	r5,#0x00
;	C:\Muntakim_Files\School\School_Work\Engineering_Bachelors\2023\ELEC_291\Projects\Project_2\ELEC291Project2\EFM8\Examples\Robot_Base\Robot_Base.c:296: TR0=1; // Start the timer
	setb	_TR0
;	C:\Muntakim_Files\School\School_Work\Engineering_Bachelors\2023\ELEC_291\Projects\Project_2\ELEC291Project2\EFM8\Examples\Robot_Base\Robot_Base.c:297: for(i=0; i<n; i++) // Measure the time of 'n' periods
	mov	r6,#0x00
L009025?:
	mov	ar7,r6
	mov	r0,#0x00
	clr	c
	mov	a,r7
	subb	a,r2
	mov	a,r0
	xrl	a,#0x80
	mov	b,r3
	xrl	b,#0x80
	subb	a,b
	jnc	L009028?
;	C:\Muntakim_Files\School\School_Work\Engineering_Bachelors\2023\ELEC_291\Projects\Project_2\ELEC291Project2\EFM8\Examples\Robot_Base\Robot_Base.c:299: while(PERIOD_PIN!=0) // Wait for the signal to be zero
	mov	ar7,r4
	mov	ar0,r5
L009017?:
	jnb	_P1_0,L009043?
;	C:\Muntakim_Files\School\School_Work\Engineering_Bachelors\2023\ELEC_291\Projects\Project_2\ELEC291Project2\EFM8\Examples\Robot_Base\Robot_Base.c:301: if(TF0==1) // Did the 16-bit timer overflow?
;	C:\Muntakim_Files\School\School_Work\Engineering_Bachelors\2023\ELEC_291\Projects\Project_2\ELEC291Project2\EFM8\Examples\Robot_Base\Robot_Base.c:303: TF0=0;
	jbc	_TF0,L009061?
	sjmp	L009017?
L009061?:
;	C:\Muntakim_Files\School\School_Work\Engineering_Bachelors\2023\ELEC_291\Projects\Project_2\ELEC291Project2\EFM8\Examples\Robot_Base\Robot_Base.c:304: overflow_count++;
	inc	r7
	cjne	r7,#0x00,L009017?
	inc	r0
;	C:\Muntakim_Files\School\School_Work\Engineering_Bachelors\2023\ELEC_291\Projects\Project_2\ELEC291Project2\EFM8\Examples\Robot_Base\Robot_Base.c:307: while(PERIOD_PIN!=1) // Wait for the signal to be one
	sjmp	L009017?
L009043?:
L009022?:
	jb	_P1_0,L009047?
;	C:\Muntakim_Files\School\School_Work\Engineering_Bachelors\2023\ELEC_291\Projects\Project_2\ELEC291Project2\EFM8\Examples\Robot_Base\Robot_Base.c:309: if(TF0==1) // Did the 16-bit timer overflow?
;	C:\Muntakim_Files\School\School_Work\Engineering_Bachelors\2023\ELEC_291\Projects\Project_2\ELEC291Project2\EFM8\Examples\Robot_Base\Robot_Base.c:311: TF0=0;
	jbc	_TF0,L009063?
	sjmp	L009022?
L009063?:
;	C:\Muntakim_Files\School\School_Work\Engineering_Bachelors\2023\ELEC_291\Projects\Project_2\ELEC291Project2\EFM8\Examples\Robot_Base\Robot_Base.c:312: overflow_count++;
	inc	r7
	cjne	r7,#0x00,L009022?
	inc	r0
	sjmp	L009022?
L009047?:
	mov	ar4,r7
	mov	ar5,r0
;	C:\Muntakim_Files\School\School_Work\Engineering_Bachelors\2023\ELEC_291\Projects\Project_2\ELEC291Project2\EFM8\Examples\Robot_Base\Robot_Base.c:297: for(i=0; i<n; i++) // Measure the time of 'n' periods
	inc	r6
	sjmp	L009025?
L009028?:
;	C:\Muntakim_Files\School\School_Work\Engineering_Bachelors\2023\ELEC_291\Projects\Project_2\ELEC291Project2\EFM8\Examples\Robot_Base\Robot_Base.c:316: TR0=0; // Stop timer 0, the 24-bit number [overflow_count-TH0-TL0] has the period in clock cycles!
	clr	_TR0
;	C:\Muntakim_Files\School\School_Work\Engineering_Bachelors\2023\ELEC_291\Projects\Project_2\ELEC291Project2\EFM8\Examples\Robot_Base\Robot_Base.c:318: return (overflow_count*65536+TH0*256+TL0);
	mov	ar3,r5
	mov	ar2,r4
	mov	r5,#0x00
	mov	r4,#0x00
	mov	r7,_TH0
	mov	r6,#0x00
	mov	a,r7
	rlc	a
	subb	a,acc
	mov	r0,a
	mov	r1,a
	mov	a,r6
	add	a,r4
	mov	r4,a
	mov	a,r7
	addc	a,r5
	mov	r5,a
	mov	a,r0
	addc	a,r2
	mov	r2,a
	mov	a,r1
	addc	a,r3
	mov	r3,a
	mov	r6,_TL0
	clr	a
	mov	r7,a
	rlc	a
	subb	a,acc
	mov	r0,a
	mov	r1,a
	mov	a,r6
	add	a,r4
	mov	r4,a
	mov	a,r7
	addc	a,r5
	mov	r5,a
	mov	a,r0
	addc	a,r2
	mov	r2,a
	mov	a,r1
	addc	a,r3
	mov	dpl,r4
	mov	dph,r5
	mov	b,r2
	ret
;------------------------------------------------------------
;Allocation info for local variables in function 'eputs'
;------------------------------------------------------------
;String                    Allocated to registers r2 r3 r4 
;------------------------------------------------------------
;	C:\Muntakim_Files\School\School_Work\Engineering_Bachelors\2023\ELEC_291\Projects\Project_2\ELEC291Project2\EFM8\Examples\Robot_Base\Robot_Base.c:321: void eputs(char *String)
;	-----------------------------------------
;	 function eputs
;	-----------------------------------------
_eputs:
	mov	r2,dpl
	mov	r3,dph
	mov	r4,b
;	C:\Muntakim_Files\School\School_Work\Engineering_Bachelors\2023\ELEC_291\Projects\Project_2\ELEC291Project2\EFM8\Examples\Robot_Base\Robot_Base.c:323: while(*String)
L010001?:
	mov	dpl,r2
	mov	dph,r3
	mov	b,r4
	lcall	__gptrget
	mov	r5,a
	jz	L010004?
;	C:\Muntakim_Files\School\School_Work\Engineering_Bachelors\2023\ELEC_291\Projects\Project_2\ELEC291Project2\EFM8\Examples\Robot_Base\Robot_Base.c:325: putchar(*String);
	mov	dpl,r5
	push	ar2
	push	ar3
	push	ar4
	lcall	_putchar
	pop	ar4
	pop	ar3
	pop	ar2
;	C:\Muntakim_Files\School\School_Work\Engineering_Bachelors\2023\ELEC_291\Projects\Project_2\ELEC291Project2\EFM8\Examples\Robot_Base\Robot_Base.c:326: String++;
	inc	r2
	cjne	r2,#0x00,L010001?
	inc	r3
	sjmp	L010001?
L010004?:
	ret
;------------------------------------------------------------
;Allocation info for local variables in function 'PrintNumber'
;------------------------------------------------------------
;Base                      Allocated with name '_PrintNumber_PARM_2'
;digits                    Allocated with name '_PrintNumber_PARM_3'
;val                       Allocated with name '_PrintNumber_val_1_80'
;j                         Allocated with name '_PrintNumber_j_1_81'
;sloc0                     Allocated with name '_PrintNumber_sloc0_1_0'
;sloc1                     Allocated with name '_PrintNumber_sloc1_1_0'
;buff                      Allocated with name '_PrintNumber_buff_1_81'
;------------------------------------------------------------
;	C:\Muntakim_Files\School\School_Work\Engineering_Bachelors\2023\ELEC_291\Projects\Project_2\ELEC291Project2\EFM8\Examples\Robot_Base\Robot_Base.c:330: void PrintNumber(long int val, int Base, int digits)
;	-----------------------------------------
;	 function PrintNumber
;	-----------------------------------------
_PrintNumber:
	mov	_PrintNumber_val_1_80,dpl
	mov	(_PrintNumber_val_1_80 + 1),dph
	mov	(_PrintNumber_val_1_80 + 2),b
	mov	(_PrintNumber_val_1_80 + 3),a
;	C:\Muntakim_Files\School\School_Work\Engineering_Bachelors\2023\ELEC_291\Projects\Project_2\ELEC291Project2\EFM8\Examples\Robot_Base\Robot_Base.c:336: buff[NBITS]=0;
	mov	dptr,#(_PrintNumber_buff_1_81 + 0x0020)
	clr	a
	movx	@dptr,a
;	C:\Muntakim_Files\School\School_Work\Engineering_Bachelors\2023\ELEC_291\Projects\Project_2\ELEC291Project2\EFM8\Examples\Robot_Base\Robot_Base.c:338: if(val<0)
	mov	a,(_PrintNumber_val_1_80 + 3)
	jnb	acc.7,L011012?
;	C:\Muntakim_Files\School\School_Work\Engineering_Bachelors\2023\ELEC_291\Projects\Project_2\ELEC291Project2\EFM8\Examples\Robot_Base\Robot_Base.c:340: putchar('-');
	mov	dpl,#0x2D
	lcall	_putchar
;	C:\Muntakim_Files\School\School_Work\Engineering_Bachelors\2023\ELEC_291\Projects\Project_2\ELEC291Project2\EFM8\Examples\Robot_Base\Robot_Base.c:341: val*=-1;
	clr	c
	clr	a
	subb	a,_PrintNumber_val_1_80
	mov	_PrintNumber_val_1_80,a
	clr	a
	subb	a,(_PrintNumber_val_1_80 + 1)
	mov	(_PrintNumber_val_1_80 + 1),a
	clr	a
	subb	a,(_PrintNumber_val_1_80 + 2)
	mov	(_PrintNumber_val_1_80 + 2),a
	clr	a
	subb	a,(_PrintNumber_val_1_80 + 3)
	mov	(_PrintNumber_val_1_80 + 3),a
;	C:\Muntakim_Files\School\School_Work\Engineering_Bachelors\2023\ELEC_291\Projects\Project_2\ELEC291Project2\EFM8\Examples\Robot_Base\Robot_Base.c:345: while ( (val>0) | (digits>0) )
L011012?:
	mov	_PrintNumber_j_1_81,#0x1F
	clr	a
	mov	(_PrintNumber_j_1_81 + 1),a
	mov	r0,_PrintNumber_PARM_3
	mov	r1,(_PrintNumber_PARM_3 + 1)
L011005?:
	clr	c
	clr	a
	subb	a,_PrintNumber_val_1_80
	clr	a
	subb	a,(_PrintNumber_val_1_80 + 1)
	clr	a
	subb	a,(_PrintNumber_val_1_80 + 2)
	clr	a
	xrl	a,#0x80
	mov	b,(_PrintNumber_val_1_80 + 3)
	xrl	b,#0x80
	subb	a,b
	clr	a
	rlc	a
	mov	r6,a
	clr	c
	clr	a
	subb	a,r0
	clr	a
	xrl	a,#0x80
	mov	b,r1
	xrl	b,#0x80
	subb	a,b
	clr	a
	rlc	a
	mov	r7,a
	orl	a,r6
	jnz	L011016?
	ljmp	L011007?
L011016?:
;	C:\Muntakim_Files\School\School_Work\Engineering_Bachelors\2023\ELEC_291\Projects\Project_2\ELEC291Project2\EFM8\Examples\Robot_Base\Robot_Base.c:347: buff[j--]=HexDigit[val%Base];
	mov	r6,_PrintNumber_j_1_81
	mov	r7,(_PrintNumber_j_1_81 + 1)
	dec	_PrintNumber_j_1_81
	mov	a,#0xff
	cjne	a,_PrintNumber_j_1_81,L011017?
	dec	(_PrintNumber_j_1_81 + 1)
L011017?:
	mov	a,r6
	add	a,#_PrintNumber_buff_1_81
	mov	_PrintNumber_sloc0_1_0,a
	mov	a,r7
	addc	a,#(_PrintNumber_buff_1_81 >> 8)
	mov	(_PrintNumber_sloc0_1_0 + 1),a
	mov	_PrintNumber_sloc1_1_0,_PrintNumber_PARM_2
	mov	a,(_PrintNumber_PARM_2 + 1)
	mov	(_PrintNumber_sloc1_1_0 + 1),a
	rlc	a
	subb	a,acc
	mov	(_PrintNumber_sloc1_1_0 + 2),a
	mov	(_PrintNumber_sloc1_1_0 + 3),a
	mov	__modslong_PARM_2,_PrintNumber_sloc1_1_0
	mov	(__modslong_PARM_2 + 1),(_PrintNumber_sloc1_1_0 + 1)
	mov	(__modslong_PARM_2 + 2),(_PrintNumber_sloc1_1_0 + 2)
	mov	(__modslong_PARM_2 + 3),(_PrintNumber_sloc1_1_0 + 3)
	mov	dpl,_PrintNumber_val_1_80
	mov	dph,(_PrintNumber_val_1_80 + 1)
	mov	b,(_PrintNumber_val_1_80 + 2)
	mov	a,(_PrintNumber_val_1_80 + 3)
	push	ar0
	push	ar1
	lcall	__modslong
	mov	r6,dpl
	mov	r7,dph
	mov	a,r6
	add	a,#_PrintNumber_HexDigit_1_81
	mov	dpl,a
	mov	a,r7
	addc	a,#(_PrintNumber_HexDigit_1_81 >> 8)
	mov	dph,a
	clr	a
	movc	a,@a+dptr
	mov	dpl,_PrintNumber_sloc0_1_0
	mov	dph,(_PrintNumber_sloc0_1_0 + 1)
	movx	@dptr,a
;	C:\Muntakim_Files\School\School_Work\Engineering_Bachelors\2023\ELEC_291\Projects\Project_2\ELEC291Project2\EFM8\Examples\Robot_Base\Robot_Base.c:348: val/=Base;
	mov	__divslong_PARM_2,_PrintNumber_sloc1_1_0
	mov	(__divslong_PARM_2 + 1),(_PrintNumber_sloc1_1_0 + 1)
	mov	(__divslong_PARM_2 + 2),(_PrintNumber_sloc1_1_0 + 2)
	mov	(__divslong_PARM_2 + 3),(_PrintNumber_sloc1_1_0 + 3)
	mov	dpl,_PrintNumber_val_1_80
	mov	dph,(_PrintNumber_val_1_80 + 1)
	mov	b,(_PrintNumber_val_1_80 + 2)
	mov	a,(_PrintNumber_val_1_80 + 3)
	lcall	__divslong
	mov	_PrintNumber_val_1_80,dpl
	mov	(_PrintNumber_val_1_80 + 1),dph
	mov	(_PrintNumber_val_1_80 + 2),b
	mov	(_PrintNumber_val_1_80 + 3),a
	pop	ar1
	pop	ar0
;	C:\Muntakim_Files\School\School_Work\Engineering_Bachelors\2023\ELEC_291\Projects\Project_2\ELEC291Project2\EFM8\Examples\Robot_Base\Robot_Base.c:349: if(digits!=0) digits--;
	mov	a,r0
	orl	a,r1
	jnz	L011018?
	ljmp	L011005?
L011018?:
	dec	r0
	cjne	r0,#0xff,L011019?
	dec	r1
L011019?:
	ljmp	L011005?
L011007?:
;	C:\Muntakim_Files\School\School_Work\Engineering_Bachelors\2023\ELEC_291\Projects\Project_2\ELEC291Project2\EFM8\Examples\Robot_Base\Robot_Base.c:351: eputs(&buff[j+1]);
	mov	a,_PrintNumber_j_1_81
	inc	a
	add	a,#_PrintNumber_buff_1_81
	mov	r2,a
	clr	a
	addc	a,#(_PrintNumber_buff_1_81 >> 8)
	mov	r3,a
	mov	r4,#0x00
	mov	dpl,r2
	mov	dph,r3
	mov	b,r4
	ljmp	_eputs
;------------------------------------------------------------
;Allocation info for local variables in function 'main'
;------------------------------------------------------------
;count                     Allocated to registers r2 r3 r4 r5 
;f                         Allocated to registers r6 r7 r0 r1 
;------------------------------------------------------------
;	C:\Muntakim_Files\School\School_Work\Engineering_Bachelors\2023\ELEC_291\Projects\Project_2\ELEC291Project2\EFM8\Examples\Robot_Base\Robot_Base.c:356: void main (void)
;	-----------------------------------------
;	 function main
;	-----------------------------------------
_main:
;	C:\Muntakim_Files\School\School_Work\Engineering_Bachelors\2023\ELEC_291\Projects\Project_2\ELEC291Project2\EFM8\Examples\Robot_Base\Robot_Base.c:383: while (1)
L012005?:
;	C:\Muntakim_Files\School\School_Work\Engineering_Bachelors\2023\ELEC_291\Projects\Project_2\ELEC291Project2\EFM8\Examples\Robot_Base\Robot_Base.c:417: count=GetPeriod(30);
	mov	dptr,#0x001E
	lcall	_GetPeriod
	mov	r2,dpl
	mov	r3,dph
	mov	r4,b
	mov	r5,a
;	C:\Muntakim_Files\School\School_Work\Engineering_Bachelors\2023\ELEC_291\Projects\Project_2\ELEC291Project2\EFM8\Examples\Robot_Base\Robot_Base.c:419: if(count>0)
	clr	c
	clr	a
	subb	a,r2
	clr	a
	subb	a,r3
	clr	a
	subb	a,r4
	clr	a
	xrl	a,#0x80
	mov	b,r5
	xrl	b,#0x80
	subb	a,b
	jc	L012011?
	ljmp	L012002?
L012011?:
;	C:\Muntakim_Files\School\School_Work\Engineering_Bachelors\2023\ELEC_291\Projects\Project_2\ELEC291Project2\EFM8\Examples\Robot_Base\Robot_Base.c:421: f=(SYSCLK*30.0)/(count*12);
	mov	__mullong_PARM_2,r2
	mov	(__mullong_PARM_2 + 1),r3
	mov	(__mullong_PARM_2 + 2),r4
	mov	(__mullong_PARM_2 + 3),r5
	mov	dptr,#(0x0C&0x00ff)
	clr	a
	mov	b,a
	push	ar2
	push	ar3
	push	ar4
	push	ar5
	lcall	__mullong
	lcall	___slong2fs
	mov	r6,dpl
	mov	r7,dph
	mov	r0,b
	mov	r1,a
	push	ar6
	push	ar7
	push	ar0
	push	ar1
	mov	dptr,#0xBEFC
	mov	b,#0x00
	mov	a,#0x4F
	lcall	___fsdiv
	mov	r6,dpl
	mov	r7,dph
	mov	r0,b
	mov	r1,a
	mov	a,sp
	add	a,#0xfc
	mov	sp,a
	mov	dpl,r6
	mov	dph,r7
	mov	b,r0
	mov	a,r1
	lcall	___fs2slong
	mov	r6,dpl
	mov	r7,dph
	mov	r0,b
	mov	r1,a
;	C:\Muntakim_Files\School\School_Work\Engineering_Bachelors\2023\ELEC_291\Projects\Project_2\ELEC291Project2\EFM8\Examples\Robot_Base\Robot_Base.c:422: printf("f=%ld Hz, count=%ld          \r", f, count);
	push	ar6
	push	ar7
	push	ar0
	push	ar1
	mov	a,#__str_1
	push	acc
	mov	a,#(__str_1 >> 8)
	push	acc
	mov	a,#0x80
	push	acc
	lcall	_printf
	mov	a,sp
	add	a,#0xf5
	mov	sp,a
;	C:\Muntakim_Files\School\School_Work\Engineering_Bachelors\2023\ELEC_291\Projects\Project_2\ELEC291Project2\EFM8\Examples\Robot_Base\Robot_Base.c:423: eputs("Hz, count=");
	mov	dptr,#__str_2
	mov	b,#0x80
	lcall	_eputs
	sjmp	L012003?
L012002?:
;	C:\Muntakim_Files\School\School_Work\Engineering_Bachelors\2023\ELEC_291\Projects\Project_2\ELEC291Project2\EFM8\Examples\Robot_Base\Robot_Base.c:427: printf("NO SIGNAL                     \r");
	mov	a,#__str_3
	push	acc
	mov	a,#(__str_3 >> 8)
	push	acc
	mov	a,#0x80
	push	acc
	lcall	_printf
	dec	sp
	dec	sp
	dec	sp
L012003?:
;	C:\Muntakim_Files\School\School_Work\Engineering_Bachelors\2023\ELEC_291\Projects\Project_2\ELEC291Project2\EFM8\Examples\Robot_Base\Robot_Base.c:491: waitms(200);
	mov	dptr,#0x00C8
	lcall	_waitms
	ljmp	L012005?
	rseg R_CSEG

	rseg R_XINIT

	rseg R_CONST
_PrintNumber_HexDigit_1_81:
	db '0123456789ABCDEF'
	db 0x00
__str_1:
	db 'f=%ld Hz, count=%ld          '
	db 0x0D
	db 0x00
__str_2:
	db 'Hz, count='
	db 0x00
__str_3:
	db 'NO SIGNAL                     '
	db 0x0D
	db 0x00

	CSEG

end

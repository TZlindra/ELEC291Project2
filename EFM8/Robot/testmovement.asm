;--------------------------------------------------------
; File Created by C51
; Version 1.0.0 #1170 (Feb 16 2022) (MSVC)
; This file was generated Fri Mar 22 17:02:50 2024
;--------------------------------------------------------
$name testmovement
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
	R_Gs_0  segment code
	R_IXSEG   segment xdata
	R_CONST   segment code
	R_XINIT   segment code
	R_DINIT   segment code

;--------------------------------------------------------
; Public variables in this module
;--------------------------------------------------------
	public _main
	public _movement_manager
	public _right
	public _left
	public _backward
	public _straight
	public _idle
	public _Timer0_ISR
	public _TIMER0_Init
	public __c51_external_startup
	public _movement_manager_PARM_5
	public _movement_manager_PARM_4
	public _movement_manager_PARM_3
	public _movement_manager_PARM_2
	public _prev_PWM_percent_y
	public _prev_PWM_percent_x
	public _PWM_percent_x
	public _PWM_percent_y
	public _state
	public _count
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
_Rs_1            BIT 0xd4
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
; overlayable bit register bank
;--------------------------------------------------------
	rseg BIT_BANK
bits:
	ds 1
	b0 equ  bits.0
	b1 equ  bits.1
	b2 equ  bits.2
	b3 equ  bits.3
	b4 equ  bits.4
	b5 equ  bits.5
	b6 equ  bits.6
	b7 equ  bits.7
;--------------------------------------------------------
; internal ram data
;--------------------------------------------------------
	rseg R_DSEG
_count:
	ds 2
_state:
	ds 2
_PWM_percent_y:
	ds 4
_PWM_percent_x:
	ds 4
_prev_PWM_percent_x:
	ds 4
_prev_PWM_percent_y:
	ds 4
_movement_manager_PARM_2:
	ds 4
_movement_manager_PARM_3:
	ds 4
_movement_manager_PARM_4:
	ds 4
_movement_manager_PARM_5:
	ds 1
;--------------------------------------------------------
; overlayable items in internal ram
;--------------------------------------------------------
	rseg R_OSEG
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
;--------------------------------------------------------
; absolute external ram data
;--------------------------------------------------------
	XSEG
;--------------------------------------------------------
; external initialized ram data
;--------------------------------------------------------
	rseg R_IXSEG
	rseg R_HOME
	rseg R_Gs_0
	rseg R_CSEG
;--------------------------------------------------------
; Reset entry point and interrupt vectors
;--------------------------------------------------------
	CSEG at 0x0000
	ljmp	_crt0
	CSEG at 0x000b
	ljmp	_Timer0_ISR
;--------------------------------------------------------
; global & static initialisations
;--------------------------------------------------------
	rseg R_HOME
	rseg R_Gs_0
	rseg R_Gs_0
;--------------------------------------------------------
; data variables initialization
;--------------------------------------------------------
	rseg R_DINIT
;	C:\UBC\SECOND YEAR\ELEC 291\Project 2\ELEC291Project2\STM32\Controller\testmovement.c:15: int count = 0;
	clr	a
	mov	_count,a
	mov	(_count + 1),a
;	C:\UBC\SECOND YEAR\ELEC 291\Project 2\ELEC291Project2\STM32\Controller\testmovement.c:17: float PWM_percent_y = 0.5;
	mov	_PWM_percent_y,#0x00
	mov	(_PWM_percent_y + 1),#0x00
	mov	(_PWM_percent_y + 2),#0x00
	mov	(_PWM_percent_y + 3),#0x3F
;	C:\UBC\SECOND YEAR\ELEC 291\Project 2\ELEC291Project2\STM32\Controller\testmovement.c:18: float PWM_percent_x = 0.5;
	mov	_PWM_percent_x,#0x00
	mov	(_PWM_percent_x + 1),#0x00
	mov	(_PWM_percent_x + 2),#0x00
	mov	(_PWM_percent_x + 3),#0x3F
	; The linker places a 'ret' at the end of segment R_DINIT.
;--------------------------------------------------------
; code
;--------------------------------------------------------
	rseg R_CSEG
;------------------------------------------------------------
;Allocation info for local variables in function '_c51_external_startup'
;------------------------------------------------------------
;------------------------------------------------------------
;	C:\UBC\SECOND YEAR\ELEC 291\Project 2\ELEC291Project2\STM32\Controller\testmovement.c:22: char _c51_external_startup (void)
;	-----------------------------------------
;	 function _c51_external_startup
;	-----------------------------------------
__c51_external_startup:
	using	0
;	C:\UBC\SECOND YEAR\ELEC 291\Project 2\ELEC291Project2\STM32\Controller\testmovement.c:25: SFRPAGE = 0x00;
	mov	_SFRPAGE,#0x00
;	C:\UBC\SECOND YEAR\ELEC 291\Project 2\ELEC291Project2\STM32\Controller\testmovement.c:26: WDTCN = 0xDE; //First key
	mov	_WDTCN,#0xDE
;	C:\UBC\SECOND YEAR\ELEC 291\Project 2\ELEC291Project2\STM32\Controller\testmovement.c:27: WDTCN = 0xAD; //Second key
	mov	_WDTCN,#0xAD
;	C:\UBC\SECOND YEAR\ELEC 291\Project 2\ELEC291Project2\STM32\Controller\testmovement.c:29: VDM0CN=0x80;       // enable VDD monitor
	mov	_VDM0CN,#0x80
;	C:\UBC\SECOND YEAR\ELEC 291\Project 2\ELEC291Project2\STM32\Controller\testmovement.c:30: RSTSRC=0x02|0x04;  // Enable reset on missing clock detector and VDD
	mov	_RSTSRC,#0x06
;	C:\UBC\SECOND YEAR\ELEC 291\Project 2\ELEC291Project2\STM32\Controller\testmovement.c:37: SFRPAGE = 0x10;
	mov	_SFRPAGE,#0x10
;	C:\UBC\SECOND YEAR\ELEC 291\Project 2\ELEC291Project2\STM32\Controller\testmovement.c:38: PFE0CN  = 0x20; // SYSCLK < 75 MHz.
	mov	_PFE0CN,#0x20
;	C:\UBC\SECOND YEAR\ELEC 291\Project 2\ELEC291Project2\STM32\Controller\testmovement.c:39: SFRPAGE = 0x00;
	mov	_SFRPAGE,#0x00
;	C:\UBC\SECOND YEAR\ELEC 291\Project 2\ELEC291Project2\STM32\Controller\testmovement.c:60: CLKSEL = 0x00;
	mov	_CLKSEL,#0x00
;	C:\UBC\SECOND YEAR\ELEC 291\Project 2\ELEC291Project2\STM32\Controller\testmovement.c:61: CLKSEL = 0x00;
	mov	_CLKSEL,#0x00
;	C:\UBC\SECOND YEAR\ELEC 291\Project 2\ELEC291Project2\STM32\Controller\testmovement.c:62: while ((CLKSEL & 0x80) == 0);
L002001?:
	mov	a,_CLKSEL
	jnb	acc.7,L002001?
;	C:\UBC\SECOND YEAR\ELEC 291\Project 2\ELEC291Project2\STM32\Controller\testmovement.c:63: CLKSEL = 0x03;
	mov	_CLKSEL,#0x03
;	C:\UBC\SECOND YEAR\ELEC 291\Project 2\ELEC291Project2\STM32\Controller\testmovement.c:64: CLKSEL = 0x03;
	mov	_CLKSEL,#0x03
;	C:\UBC\SECOND YEAR\ELEC 291\Project 2\ELEC291Project2\STM32\Controller\testmovement.c:65: while ((CLKSEL & 0x80) == 0);
L002004?:
	mov	a,_CLKSEL
	jnb	acc.7,L002004?
;	C:\UBC\SECOND YEAR\ELEC 291\Project 2\ELEC291Project2\STM32\Controller\testmovement.c:70: return 0;
	mov	dpl,#0x00
	ret
;------------------------------------------------------------
;Allocation info for local variables in function 'TIMER0_Init'
;------------------------------------------------------------
;------------------------------------------------------------
;	C:\UBC\SECOND YEAR\ELEC 291\Project 2\ELEC291Project2\STM32\Controller\testmovement.c:82: void TIMER0_Init(void)
;	-----------------------------------------
;	 function TIMER0_Init
;	-----------------------------------------
_TIMER0_Init:
;	C:\UBC\SECOND YEAR\ELEC 291\Project 2\ELEC291Project2\STM32\Controller\testmovement.c:85: TR0=0;
	clr	_TR0
;	C:\UBC\SECOND YEAR\ELEC 291\Project 2\ELEC291Project2\STM32\Controller\testmovement.c:86: TF0=0;
	clr	_TF0
;	C:\UBC\SECOND YEAR\ELEC 291\Project 2\ELEC291Project2\STM32\Controller\testmovement.c:87: CKCON0|=0b_0000_0100; // Timer 0 uses the system clock
	orl	_CKCON0,#0x04
;	C:\UBC\SECOND YEAR\ELEC 291\Project 2\ELEC291Project2\STM32\Controller\testmovement.c:88: TMOD&=0xf0;
	anl	_TMOD,#0xF0
;	C:\UBC\SECOND YEAR\ELEC 291\Project 2\ELEC291Project2\STM32\Controller\testmovement.c:89: TMOD|=0x01; // Timer 0 in mode 1: 16-bit timer
	orl	_TMOD,#0x01
;	C:\UBC\SECOND YEAR\ELEC 291\Project 2\ELEC291Project2\STM32\Controller\testmovement.c:91: TMR0=65536L-(SYSCLK/(2*TIMER_0_FREQ));
	mov	_TMR0,#0x60
	mov	(_TMR0 >> 8),#0x73
;	C:\UBC\SECOND YEAR\ELEC 291\Project 2\ELEC291Project2\STM32\Controller\testmovement.c:92: ET0=1;     // Enable Timer0 interrupts
	setb	_ET0
;	C:\UBC\SECOND YEAR\ELEC 291\Project 2\ELEC291Project2\STM32\Controller\testmovement.c:93: TR0=1;     // Start Timer0
	setb	_TR0
	ret
;------------------------------------------------------------
;Allocation info for local variables in function 'Timer0_ISR'
;------------------------------------------------------------
;------------------------------------------------------------
;	C:\UBC\SECOND YEAR\ELEC 291\Project 2\ELEC291Project2\STM32\Controller\testmovement.c:96: void Timer0_ISR (void) interrupt INTERRUPT_TIMER0
;	-----------------------------------------
;	 function Timer0_ISR
;	-----------------------------------------
_Timer0_ISR:
	push	bits
	push	acc
	push	b
	push	dpl
	push	dph
	push	(0+2)
	push	(0+3)
	push	(0+4)
	push	(0+5)
	push	(0+6)
	push	(0+7)
	push	(0+0)
	push	(0+1)
	push	psw
	mov	psw,#0x00
;	C:\UBC\SECOND YEAR\ELEC 291\Project 2\ELEC291Project2\STM32\Controller\testmovement.c:98: SFRPAGE=0x0;
	mov	_SFRPAGE,#0x00
;	C:\UBC\SECOND YEAR\ELEC 291\Project 2\ELEC291Project2\STM32\Controller\testmovement.c:99: TR0 = 0;
	clr	_TR0
;	C:\UBC\SECOND YEAR\ELEC 291\Project 2\ELEC291Project2\STM32\Controller\testmovement.c:101: TMR0=0x10000L-(SYSCLK/(2*TIMER_0_FREQ));
	mov	_TMR0,#0x60
	mov	(_TMR0 >> 8),#0x73
;	C:\UBC\SECOND YEAR\ELEC 291\Project 2\ELEC291Project2\STM32\Controller\testmovement.c:103: P1_2 = !P1_2;
	cpl	_P1_2
;	C:\UBC\SECOND YEAR\ELEC 291\Project 2\ELEC291Project2\STM32\Controller\testmovement.c:105: if (state != idle_enum)
	mov	a,_state
	orl	a,(_state + 1)
	jnz	L004029?
	ljmp	L004019?
L004029?:
;	C:\UBC\SECOND YEAR\ELEC 291\Project 2\ELEC291Project2\STM32\Controller\testmovement.c:107: if (count > 100)
	clr	c
	mov	a,#0x64
	subb	a,_count
	clr	a
	xrl	a,#0x80
	mov	b,(_count + 1)
	xrl	b,#0x80
	subb	a,b
	jnc	L004016?
;	C:\UBC\SECOND YEAR\ELEC 291\Project 2\ELEC291Project2\STM32\Controller\testmovement.c:110: if (state == left_enum)
	mov	a,#0x01
	cjne	a,_state,L004031?
	clr	a
	cjne	a,(_state + 1),L004031?
	sjmp	L004032?
L004031?:
	sjmp	L004005?
L004032?:
;	C:\UBC\SECOND YEAR\ELEC 291\Project 2\ELEC291Project2\STM32\Controller\testmovement.c:112: RIGHT_MOTOR_LHS = 1;
	setb	_P2_2
	sjmp	L004006?
L004005?:
;	C:\UBC\SECOND YEAR\ELEC 291\Project 2\ELEC291Project2\STM32\Controller\testmovement.c:114: else if (state == right_enum)
	mov	a,#0x02
	cjne	a,_state,L004033?
	clr	a
	cjne	a,(_state + 1),L004033?
	sjmp	L004034?
L004033?:
	sjmp	L004002?
L004034?:
;	C:\UBC\SECOND YEAR\ELEC 291\Project 2\ELEC291Project2\STM32\Controller\testmovement.c:116: LEFT_MOTOR_LHS = 1;
	setb	_P2_4
	sjmp	L004006?
L004002?:
;	C:\UBC\SECOND YEAR\ELEC 291\Project 2\ELEC291Project2\STM32\Controller\testmovement.c:120: LEFT_MOTOR_LHS = 1;
	setb	_P2_4
;	C:\UBC\SECOND YEAR\ELEC 291\Project 2\ELEC291Project2\STM32\Controller\testmovement.c:121: RIGHT_MOTOR_LHS = 1;
	setb	_P2_2
L004006?:
;	C:\UBC\SECOND YEAR\ELEC 291\Project 2\ELEC291Project2\STM32\Controller\testmovement.c:123: count = 0;
	clr	a
	mov	_count,a
	mov	(_count + 1),a
	sjmp	L004017?
L004016?:
;	C:\UBC\SECOND YEAR\ELEC 291\Project 2\ELEC291Project2\STM32\Controller\testmovement.c:125: else if (count > PWM_percent_y*100)
	push	_PWM_percent_y
	push	(_PWM_percent_y + 1)
	push	(_PWM_percent_y + 2)
	push	(_PWM_percent_y + 3)
	mov	dptr,#0x0000
	mov	b,#0xC8
	mov	a,#0x42
	lcall	___fsmul
	mov	r2,dpl
	mov	r3,dph
	mov	r4,b
	mov	r5,a
	mov	a,sp
	add	a,#0xfc
	mov	sp,a
	mov	dpl,_count
	mov	dph,(_count + 1)
	push	ar2
	push	ar3
	push	ar4
	push	ar5
	lcall	___sint2fs
	lcall	___fsgt
	mov	r2,dpl
	mov	a,sp
	add	a,#0xfc
	mov	sp,a
	mov	a,r2
	jz	L004017?
;	C:\UBC\SECOND YEAR\ELEC 291\Project 2\ELEC291Project2\STM32\Controller\testmovement.c:128: if (state == left_enum)
	mov	a,#0x01
	cjne	a,_state,L004036?
	clr	a
	cjne	a,(_state + 1),L004036?
	sjmp	L004037?
L004036?:
	sjmp	L004011?
L004037?:
;	C:\UBC\SECOND YEAR\ELEC 291\Project 2\ELEC291Project2\STM32\Controller\testmovement.c:130: RIGHT_MOTOR_LHS = 0;
	clr	_P2_2
	sjmp	L004017?
L004011?:
;	C:\UBC\SECOND YEAR\ELEC 291\Project 2\ELEC291Project2\STM32\Controller\testmovement.c:132: else if (state == right_enum)
	mov	a,#0x02
	cjne	a,_state,L004038?
	clr	a
	cjne	a,(_state + 1),L004038?
	sjmp	L004039?
L004038?:
	sjmp	L004008?
L004039?:
;	C:\UBC\SECOND YEAR\ELEC 291\Project 2\ELEC291Project2\STM32\Controller\testmovement.c:134: LEFT_MOTOR_LHS = 0;
	clr	_P2_4
	sjmp	L004017?
L004008?:
;	C:\UBC\SECOND YEAR\ELEC 291\Project 2\ELEC291Project2\STM32\Controller\testmovement.c:138: LEFT_MOTOR_LHS = 0;
	clr	_P2_4
;	C:\UBC\SECOND YEAR\ELEC 291\Project 2\ELEC291Project2\STM32\Controller\testmovement.c:139: RIGHT_MOTOR_LHS = 0;
	clr	_P2_2
L004017?:
;	C:\UBC\SECOND YEAR\ELEC 291\Project 2\ELEC291Project2\STM32\Controller\testmovement.c:142: count++;
	inc	_count
	clr	a
	cjne	a,_count,L004040?
	inc	(_count + 1)
L004040?:
L004019?:
;	C:\UBC\SECOND YEAR\ELEC 291\Project 2\ELEC291Project2\STM32\Controller\testmovement.c:146: TR0 = 1;
	setb	_TR0
	pop	psw
	pop	(0+1)
	pop	(0+0)
	pop	(0+7)
	pop	(0+6)
	pop	(0+5)
	pop	(0+4)
	pop	(0+3)
	pop	(0+2)
	pop	dph
	pop	dpl
	pop	b
	pop	acc
	pop	bits
	reti
;------------------------------------------------------------
;Allocation info for local variables in function 'idle'
;------------------------------------------------------------
;------------------------------------------------------------
;	C:\UBC\SECOND YEAR\ELEC 291\Project 2\ELEC291Project2\STM32\Controller\testmovement.c:150: void idle(void)
;	-----------------------------------------
;	 function idle
;	-----------------------------------------
_idle:
;	C:\UBC\SECOND YEAR\ELEC 291\Project 2\ELEC291Project2\STM32\Controller\testmovement.c:152: LEFT_MOTOR_LHS = 0;
	clr	_P2_4
;	C:\UBC\SECOND YEAR\ELEC 291\Project 2\ELEC291Project2\STM32\Controller\testmovement.c:153: LEFT_MOTOR_RHS = 0;
	clr	_P2_3
;	C:\UBC\SECOND YEAR\ELEC 291\Project 2\ELEC291Project2\STM32\Controller\testmovement.c:154: RIGHT_MOTOR_LHS = 0;
	clr	_P2_2
;	C:\UBC\SECOND YEAR\ELEC 291\Project 2\ELEC291Project2\STM32\Controller\testmovement.c:155: RIGHT_MOTOR_RHS = 0;
	clr	_P2_1
	ret
;------------------------------------------------------------
;Allocation info for local variables in function 'straight'
;------------------------------------------------------------
;------------------------------------------------------------
;	C:\UBC\SECOND YEAR\ELEC 291\Project 2\ELEC291Project2\STM32\Controller\testmovement.c:158: void straight(void)
;	-----------------------------------------
;	 function straight
;	-----------------------------------------
_straight:
;	C:\UBC\SECOND YEAR\ELEC 291\Project 2\ELEC291Project2\STM32\Controller\testmovement.c:160: LEFT_MOTOR_LHS = 1;
	setb	_P2_4
;	C:\UBC\SECOND YEAR\ELEC 291\Project 2\ELEC291Project2\STM32\Controller\testmovement.c:161: LEFT_MOTOR_RHS = 0;
	clr	_P2_3
;	C:\UBC\SECOND YEAR\ELEC 291\Project 2\ELEC291Project2\STM32\Controller\testmovement.c:162: RIGHT_MOTOR_LHS = 1;
	setb	_P2_2
;	C:\UBC\SECOND YEAR\ELEC 291\Project 2\ELEC291Project2\STM32\Controller\testmovement.c:163: RIGHT_MOTOR_RHS = 0;
	clr	_P2_1
	ret
;------------------------------------------------------------
;Allocation info for local variables in function 'backward'
;------------------------------------------------------------
;------------------------------------------------------------
;	C:\UBC\SECOND YEAR\ELEC 291\Project 2\ELEC291Project2\STM32\Controller\testmovement.c:166: void backward(void)
;	-----------------------------------------
;	 function backward
;	-----------------------------------------
_backward:
;	C:\UBC\SECOND YEAR\ELEC 291\Project 2\ELEC291Project2\STM32\Controller\testmovement.c:168: LEFT_MOTOR_LHS = 0;
	clr	_P2_4
;	C:\UBC\SECOND YEAR\ELEC 291\Project 2\ELEC291Project2\STM32\Controller\testmovement.c:169: LEFT_MOTOR_RHS = 1;
	setb	_P2_3
;	C:\UBC\SECOND YEAR\ELEC 291\Project 2\ELEC291Project2\STM32\Controller\testmovement.c:170: RIGHT_MOTOR_LHS = 0;
	clr	_P2_2
;	C:\UBC\SECOND YEAR\ELEC 291\Project 2\ELEC291Project2\STM32\Controller\testmovement.c:171: RIGHT_MOTOR_RHS = 1;
	setb	_P2_1
	ret
;------------------------------------------------------------
;Allocation info for local variables in function 'left'
;------------------------------------------------------------
;PWM_percent_y             Allocated to registers r2 r3 r4 r5
;------------------------------------------------------------
;	C:\UBC\SECOND YEAR\ELEC 291\Project 2\ELEC291Project2\STM32\Controller\testmovement.c:174: void left(float PWM_percent_y)
;	-----------------------------------------
;	 function left
;	-----------------------------------------
_left:
	mov	r2,dpl
	mov	r3,dph
	mov	r4,b
	mov	r5,a
;	C:\UBC\SECOND YEAR\ELEC 291\Project 2\ELEC291Project2\STM32\Controller\testmovement.c:177: LEFT_MOTOR_LHS = 0;
	clr	_P2_4
;	C:\UBC\SECOND YEAR\ELEC 291\Project 2\ELEC291Project2\STM32\Controller\testmovement.c:178: LEFT_MOTOR_RHS = 0;
	clr	_P2_3
;	C:\UBC\SECOND YEAR\ELEC 291\Project 2\ELEC291Project2\STM32\Controller\testmovement.c:180: if (PWM_percent_y > 0)
	clr	a
	push	acc
	push	acc
	push	acc
	push	acc
	mov	dpl,r2
	mov	dph,r3
	mov	b,r4
	mov	a,r5
	lcall	___fsgt
	mov	r2,dpl
	mov	a,sp
	add	a,#0xfc
	mov	sp,a
	mov	a,r2
	jz	L008002?
;	C:\UBC\SECOND YEAR\ELEC 291\Project 2\ELEC291Project2\STM32\Controller\testmovement.c:182: RIGHT_MOTOR_LHS = 1;
	setb	_P2_2
;	C:\UBC\SECOND YEAR\ELEC 291\Project 2\ELEC291Project2\STM32\Controller\testmovement.c:183: RIGHT_MOTOR_RHS = 0;
	clr	_P2_1
	ret
L008002?:
;	C:\UBC\SECOND YEAR\ELEC 291\Project 2\ELEC291Project2\STM32\Controller\testmovement.c:187: RIGHT_MOTOR_LHS = 0;
	clr	_P2_2
;	C:\UBC\SECOND YEAR\ELEC 291\Project 2\ELEC291Project2\STM32\Controller\testmovement.c:188: RIGHT_MOTOR_RHS = 1;
	setb	_P2_1
	ret
;------------------------------------------------------------
;Allocation info for local variables in function 'right'
;------------------------------------------------------------
;PWM_percent_y             Allocated to registers r2 r3 r4 r5
;------------------------------------------------------------
;	C:\UBC\SECOND YEAR\ELEC 291\Project 2\ELEC291Project2\STM32\Controller\testmovement.c:193: void right(float PWM_percent_y)
;	-----------------------------------------
;	 function right
;	-----------------------------------------
_right:
	mov	r2,dpl
	mov	r3,dph
	mov	r4,b
	mov	r5,a
;	C:\UBC\SECOND YEAR\ELEC 291\Project 2\ELEC291Project2\STM32\Controller\testmovement.c:196: RIGHT_MOTOR_LHS = 0;
	clr	_P2_2
;	C:\UBC\SECOND YEAR\ELEC 291\Project 2\ELEC291Project2\STM32\Controller\testmovement.c:197: RIGHT_MOTOR_RHS = 0;
	clr	_P2_1
;	C:\UBC\SECOND YEAR\ELEC 291\Project 2\ELEC291Project2\STM32\Controller\testmovement.c:199: if (PWM_percent_y > 0)
	clr	a
	push	acc
	push	acc
	push	acc
	push	acc
	mov	dpl,r2
	mov	dph,r3
	mov	b,r4
	mov	a,r5
	lcall	___fsgt
	mov	r2,dpl
	mov	a,sp
	add	a,#0xfc
	mov	sp,a
	mov	a,r2
	jz	L009002?
;	C:\UBC\SECOND YEAR\ELEC 291\Project 2\ELEC291Project2\STM32\Controller\testmovement.c:201: LEFT_MOTOR_LHS = 1;
	setb	_P2_4
;	C:\UBC\SECOND YEAR\ELEC 291\Project 2\ELEC291Project2\STM32\Controller\testmovement.c:202: LEFT_MOTOR_RHS = 0;
	clr	_P2_3
	ret
L009002?:
;	C:\UBC\SECOND YEAR\ELEC 291\Project 2\ELEC291Project2\STM32\Controller\testmovement.c:206: LEFT_MOTOR_LHS = 0;
	clr	_P2_4
;	C:\UBC\SECOND YEAR\ELEC 291\Project 2\ELEC291Project2\STM32\Controller\testmovement.c:207: LEFT_MOTOR_RHS = 1;
	setb	_P2_3
	ret
;------------------------------------------------------------
;Allocation info for local variables in function 'movement_manager'
;------------------------------------------------------------
;PWM_percent_y             Allocated with name '_movement_manager_PARM_2'
;prev_PWM_percent_x        Allocated with name '_movement_manager_PARM_3'
;prev_PWM_percent_y        Allocated with name '_movement_manager_PARM_4'
;state                     Allocated with name '_movement_manager_PARM_5'
;PWM_percent_x             Allocated to registers r2 r3 r4 r5
;------------------------------------------------------------
;	C:\UBC\SECOND YEAR\ELEC 291\Project 2\ELEC291Project2\STM32\Controller\testmovement.c:212: enum State movement_manager(float PWM_percent_x, float PWM_percent_y, float prev_PWM_percent_x, float prev_PWM_percent_y, enum State state)
;	-----------------------------------------
;	 function movement_manager
;	-----------------------------------------
_movement_manager:
	mov	r2,dpl
	mov	r3,dph
	mov	r4,b
	mov	r5,a
;	C:\UBC\SECOND YEAR\ELEC 291\Project 2\ELEC291Project2\STM32\Controller\testmovement.c:214: if (prev_PWM_percent_x != PWM_percent_x && prev_PWM_percent_y != PWM_percent_y){
	push	ar2
	push	ar3
	push	ar4
	push	ar5
	push	ar2
	push	ar3
	push	ar4
	push	ar5
	mov	dpl,_movement_manager_PARM_3
	mov	dph,(_movement_manager_PARM_3 + 1)
	mov	b,(_movement_manager_PARM_3 + 2)
	mov	a,(_movement_manager_PARM_3 + 3)
	lcall	___fseq
	mov	r6,dpl
	mov	a,sp
	add	a,#0xfc
	mov	sp,a
	pop	ar5
	pop	ar4
	pop	ar3
	pop	ar2
	mov	a,r6
	jz	L010026?
	ljmp	L010015?
L010026?:
	push	ar2
	push	ar3
	push	ar4
	push	ar5
	push	_movement_manager_PARM_2
	push	(_movement_manager_PARM_2 + 1)
	push	(_movement_manager_PARM_2 + 2)
	push	(_movement_manager_PARM_2 + 3)
	mov	dpl,_movement_manager_PARM_4
	mov	dph,(_movement_manager_PARM_4 + 1)
	mov	b,(_movement_manager_PARM_4 + 2)
	mov	a,(_movement_manager_PARM_4 + 3)
	lcall	___fseq
	mov	r6,dpl
	mov	a,sp
	add	a,#0xfc
	mov	sp,a
	pop	ar5
	pop	ar4
	pop	ar3
	pop	ar2
	mov	a,r6
	jz	L010027?
	ljmp	L010015?
L010027?:
;	C:\UBC\SECOND YEAR\ELEC 291\Project 2\ELEC291Project2\STM32\Controller\testmovement.c:215: if (PWM_percent_y == 0 && PWM_percent_x == 0)
	mov	a,_movement_manager_PARM_2
	orl	a,(_movement_manager_PARM_2 + 1)
	orl	a,(_movement_manager_PARM_2 + 2)
	mov	b,(_movement_manager_PARM_2 + 3)
	clr	b.7 ; Clear the sign bit
	orl	a,b
	jnz	L010011?
	mov	a,r2
	orl	a,r3
	orl	a,r4
	mov	b,r5
	clr	b.7 ; Clear the sign bit
	orl	a,b
;	C:\UBC\SECOND YEAR\ELEC 291\Project 2\ELEC291Project2\STM32\Controller\testmovement.c:217: state = idle_enum;
	jnz	L010011?
	mov	_movement_manager_PARM_5,a
;	C:\UBC\SECOND YEAR\ELEC 291\Project 2\ELEC291Project2\STM32\Controller\testmovement.c:218: idle();
	lcall	_idle
	ljmp	L010015?
L010011?:
;	C:\UBC\SECOND YEAR\ELEC 291\Project 2\ELEC291Project2\STM32\Controller\testmovement.c:220: else if (PWM_percent_x < 0)
	push	ar2
	push	ar3
	push	ar4
	push	ar5
	clr	a
	push	acc
	push	acc
	push	acc
	push	acc
	mov	dpl,r2
	mov	dph,r3
	mov	b,r4
	mov	a,r5
	lcall	___fslt
	mov	r6,dpl
	mov	a,sp
	add	a,#0xfc
	mov	sp,a
	pop	ar5
	pop	ar4
	pop	ar3
	pop	ar2
	mov	a,r6
	jz	L010008?
;	C:\UBC\SECOND YEAR\ELEC 291\Project 2\ELEC291Project2\STM32\Controller\testmovement.c:222: state = left_enum;
	mov	_movement_manager_PARM_5,#0x01
;	C:\UBC\SECOND YEAR\ELEC 291\Project 2\ELEC291Project2\STM32\Controller\testmovement.c:223: left(PWM_percent_y);
	mov	dpl,_movement_manager_PARM_2
	mov	dph,(_movement_manager_PARM_2 + 1)
	mov	b,(_movement_manager_PARM_2 + 2)
	mov	a,(_movement_manager_PARM_2 + 3)
	lcall	_left
	sjmp	L010015?
L010008?:
;	C:\UBC\SECOND YEAR\ELEC 291\Project 2\ELEC291Project2\STM32\Controller\testmovement.c:225: else if (PWM_percent_x > 0)
	clr	a
	push	acc
	push	acc
	push	acc
	push	acc
	mov	dpl,r2
	mov	dph,r3
	mov	b,r4
	mov	a,r5
	lcall	___fsgt
	mov	r2,dpl
	mov	a,sp
	add	a,#0xfc
	mov	sp,a
	mov	a,r2
	jz	L010005?
;	C:\UBC\SECOND YEAR\ELEC 291\Project 2\ELEC291Project2\STM32\Controller\testmovement.c:227: state = right_enum;
	mov	_movement_manager_PARM_5,#0x02
;	C:\UBC\SECOND YEAR\ELEC 291\Project 2\ELEC291Project2\STM32\Controller\testmovement.c:228: right(PWM_percent_y);
	mov	dpl,_movement_manager_PARM_2
	mov	dph,(_movement_manager_PARM_2 + 1)
	mov	b,(_movement_manager_PARM_2 + 2)
	mov	a,(_movement_manager_PARM_2 + 3)
	lcall	_right
	sjmp	L010015?
L010005?:
;	C:\UBC\SECOND YEAR\ELEC 291\Project 2\ELEC291Project2\STM32\Controller\testmovement.c:230: else if (PWM_percent_y > 0)
	clr	a
	push	acc
	push	acc
	push	acc
	push	acc
	mov	dpl,_movement_manager_PARM_2
	mov	dph,(_movement_manager_PARM_2 + 1)
	mov	b,(_movement_manager_PARM_2 + 2)
	mov	a,(_movement_manager_PARM_2 + 3)
	lcall	___fsgt
	mov	r2,dpl
	mov	a,sp
	add	a,#0xfc
	mov	sp,a
	mov	a,r2
	jz	L010002?
;	C:\UBC\SECOND YEAR\ELEC 291\Project 2\ELEC291Project2\STM32\Controller\testmovement.c:232: state = straight_enum;
	mov	_movement_manager_PARM_5,#0x03
;	C:\UBC\SECOND YEAR\ELEC 291\Project 2\ELEC291Project2\STM32\Controller\testmovement.c:233: straight();
	lcall	_straight
	sjmp	L010015?
L010002?:
;	C:\UBC\SECOND YEAR\ELEC 291\Project 2\ELEC291Project2\STM32\Controller\testmovement.c:237: state = backward_enum;
	mov	_movement_manager_PARM_5,#0x04
;	C:\UBC\SECOND YEAR\ELEC 291\Project 2\ELEC291Project2\STM32\Controller\testmovement.c:238: backward();
	lcall	_backward
L010015?:
;	C:\UBC\SECOND YEAR\ELEC 291\Project 2\ELEC291Project2\STM32\Controller\testmovement.c:241: return state;
	mov	dpl,_movement_manager_PARM_5
	ret
;------------------------------------------------------------
;Allocation info for local variables in function 'main'
;------------------------------------------------------------
;------------------------------------------------------------
;	C:\UBC\SECOND YEAR\ELEC 291\Project 2\ELEC291Project2\STM32\Controller\testmovement.c:245: int main(void)
;	-----------------------------------------
;	 function main
;	-----------------------------------------
_main:
;	C:\UBC\SECOND YEAR\ELEC 291\Project 2\ELEC291Project2\STM32\Controller\testmovement.c:247: TIMER0_Init();
	lcall	_TIMER0_Init
;	C:\UBC\SECOND YEAR\ELEC 291\Project 2\ELEC291Project2\STM32\Controller\testmovement.c:248: while(1)
L011002?:
;	C:\UBC\SECOND YEAR\ELEC 291\Project 2\ELEC291Project2\STM32\Controller\testmovement.c:250: state = movement_manager(PWM_percent_x, PWM_percent_y, prev_PWM_percent_x, prev_PWM_percent_y, state);
	mov	_movement_manager_PARM_5,_state
	mov	_movement_manager_PARM_2,_PWM_percent_y
	mov	(_movement_manager_PARM_2 + 1),(_PWM_percent_y + 1)
	mov	(_movement_manager_PARM_2 + 2),(_PWM_percent_y + 2)
	mov	(_movement_manager_PARM_2 + 3),(_PWM_percent_y + 3)
	mov	_movement_manager_PARM_3,_prev_PWM_percent_x
	mov	(_movement_manager_PARM_3 + 1),(_prev_PWM_percent_x + 1)
	mov	(_movement_manager_PARM_3 + 2),(_prev_PWM_percent_x + 2)
	mov	(_movement_manager_PARM_3 + 3),(_prev_PWM_percent_x + 3)
	mov	_movement_manager_PARM_4,_prev_PWM_percent_y
	mov	(_movement_manager_PARM_4 + 1),(_prev_PWM_percent_y + 1)
	mov	(_movement_manager_PARM_4 + 2),(_prev_PWM_percent_y + 2)
	mov	(_movement_manager_PARM_4 + 3),(_prev_PWM_percent_y + 3)
	mov	dpl,_PWM_percent_x
	mov	dph,(_PWM_percent_x + 1)
	mov	b,(_PWM_percent_x + 2)
	mov	a,(_PWM_percent_x + 3)
	lcall	_movement_manager
	mov	r2,dpl
	mov	_state,r2
	mov	(_state + 1),#0x00
;	C:\UBC\SECOND YEAR\ELEC 291\Project 2\ELEC291Project2\STM32\Controller\testmovement.c:251: prev_PWM_percent_x = PWM_percent_x;
	mov	_prev_PWM_percent_x,_PWM_percent_x
	mov	(_prev_PWM_percent_x + 1),(_PWM_percent_x + 1)
	mov	(_prev_PWM_percent_x + 2),(_PWM_percent_x + 2)
	mov	(_prev_PWM_percent_x + 3),(_PWM_percent_x + 3)
;	C:\UBC\SECOND YEAR\ELEC 291\Project 2\ELEC291Project2\STM32\Controller\testmovement.c:252: prev_PWM_percent_y = PWM_percent_y;
	mov	_prev_PWM_percent_y,_PWM_percent_y
	mov	(_prev_PWM_percent_y + 1),(_PWM_percent_y + 1)
	mov	(_prev_PWM_percent_y + 2),(_PWM_percent_y + 2)
	mov	(_prev_PWM_percent_y + 3),(_PWM_percent_y + 3)
	sjmp	L011002?
	rseg R_CSEG

	rseg R_XINIT

	rseg R_CONST

	CSEG

end

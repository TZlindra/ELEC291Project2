;--------------------------------------------------------
; File Created by C51
; Version 1.0.0 #1170 (Feb 16 2022) (MSVC)
; This file was generated Wed Mar 27 16:38:32 2024
;--------------------------------------------------------
$name main
$optc51 --model-small
$printf_float
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
	public _main
	public _RXData
	public _GetData
	public _SendFreq
	public _GetFreq
	public _calculate_freq_Hz
	public _calculate_period_s
	public _JDYInit
	public _SendATCommand
	public _waitms_or_RI1
	public _RXU1
	public _getstr1
	public _getchar1_with_timeout
	public _getchar1
	public _sendstr1
	public _putchar1
	public _UART1_Init
	public _Serial_Init
	public _waitms
	public _Timer3us
	public _TIMER0_Init
	public __c51_external_startup
	public _TX_BUFF
	public _RX_BUFF
	public _calculate_period_s_PARM_3
	public _calculate_period_s_PARM_2
	public _inductance
	public _TXInductance
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
_inductance:
	ds 2
_calculate_period_s_PARM_2:
	ds 2
_calculate_period_s_PARM_3:
	ds 2
;--------------------------------------------------------
; overlayable items in internal ram 
;--------------------------------------------------------
	rseg	R_OSEG
	rseg	R_OSEG
	rseg	R_OSEG
;--------------------------------------------------------
; indirectly addressable internal ram data
;--------------------------------------------------------
	rseg R_ISEG
_RX_BUFF:
	ds 80
_TX_BUFF:
	ds 80
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
	rseg R_GSINIT
	rseg R_CSEG
;--------------------------------------------------------
; Reset entry point and interrupt vectors
;--------------------------------------------------------
	CSEG at 0x0000
	ljmp	_crt0
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
;	C:\UBC\SECOND YEAR\ELEC 291\Project 2\ELEC291Project2\EFM8\Robot\main.c:25: volatile int inductance = 0;
	clr	a
	mov	_inductance,a
	mov	(_inductance + 1),a
	; The linker places a 'ret' at the end of segment R_DINIT.
;--------------------------------------------------------
; code
;--------------------------------------------------------
	rseg R_CSEG
;------------------------------------------------------------
;Allocation info for local variables in function '_c51_external_startup'
;------------------------------------------------------------
;------------------------------------------------------------
;	C:\UBC\SECOND YEAR\ELEC 291\Project 2\ELEC291Project2\EFM8\Robot\main.c:29: char _c51_external_startup (void) {
;	-----------------------------------------
;	 function _c51_external_startup
;	-----------------------------------------
__c51_external_startup:
	using	0
;	C:\UBC\SECOND YEAR\ELEC 291\Project 2\ELEC291Project2\EFM8\Robot\main.c:31: SFRPAGE = 0x00;
	mov	_SFRPAGE,#0x00
;	C:\UBC\SECOND YEAR\ELEC 291\Project 2\ELEC291Project2\EFM8\Robot\main.c:32: WDTCN = 0xDE; //First key
	mov	_WDTCN,#0xDE
;	C:\UBC\SECOND YEAR\ELEC 291\Project 2\ELEC291Project2\EFM8\Robot\main.c:33: WDTCN = 0xAD; //Second key
	mov	_WDTCN,#0xAD
;	C:\UBC\SECOND YEAR\ELEC 291\Project 2\ELEC291Project2\EFM8\Robot\main.c:35: VDM0CN=0x80;       // enable VDD monitor
	mov	_VDM0CN,#0x80
;	C:\UBC\SECOND YEAR\ELEC 291\Project 2\ELEC291Project2\EFM8\Robot\main.c:36: RSTSRC=0x02|0x04;  // Enable reset on missing clock detector and VDD
	mov	_RSTSRC,#0x06
;	C:\UBC\SECOND YEAR\ELEC 291\Project 2\ELEC291Project2\EFM8\Robot\main.c:43: SFRPAGE = 0x10;
	mov	_SFRPAGE,#0x10
;	C:\UBC\SECOND YEAR\ELEC 291\Project 2\ELEC291Project2\EFM8\Robot\main.c:44: PFE0CN  = 0x20; // SYSCLK < 75 MHz.
	mov	_PFE0CN,#0x20
;	C:\UBC\SECOND YEAR\ELEC 291\Project 2\ELEC291Project2\EFM8\Robot\main.c:45: SFRPAGE = 0x00;
	mov	_SFRPAGE,#0x00
;	C:\UBC\SECOND YEAR\ELEC 291\Project 2\ELEC291Project2\EFM8\Robot\main.c:66: CLKSEL = 0x00;
	mov	_CLKSEL,#0x00
;	C:\UBC\SECOND YEAR\ELEC 291\Project 2\ELEC291Project2\EFM8\Robot\main.c:67: CLKSEL = 0x00;
	mov	_CLKSEL,#0x00
;	C:\UBC\SECOND YEAR\ELEC 291\Project 2\ELEC291Project2\EFM8\Robot\main.c:68: while ((CLKSEL & 0x80) == 0);
L002001?:
	mov	a,_CLKSEL
	jnb	acc.7,L002001?
;	C:\UBC\SECOND YEAR\ELEC 291\Project 2\ELEC291Project2\EFM8\Robot\main.c:69: CLKSEL = 0x03;
	mov	_CLKSEL,#0x03
;	C:\UBC\SECOND YEAR\ELEC 291\Project 2\ELEC291Project2\EFM8\Robot\main.c:70: CLKSEL = 0x03;
	mov	_CLKSEL,#0x03
;	C:\UBC\SECOND YEAR\ELEC 291\Project 2\ELEC291Project2\EFM8\Robot\main.c:71: while ((CLKSEL & 0x80) == 0);
L002004?:
	mov	a,_CLKSEL
	jnb	acc.7,L002004?
;	C:\UBC\SECOND YEAR\ELEC 291\Project 2\ELEC291Project2\EFM8\Robot\main.c:76: P0MDOUT |= 0x11; // Enable UART0 TX (P0.4) and UART1 TX (P0.0) as push-pull outputs
	orl	_P0MDOUT,#0x11
;	C:\UBC\SECOND YEAR\ELEC 291\Project 2\ELEC291Project2\EFM8\Robot\main.c:77: P2MDOUT |= 0x01; // P2.0 in push-pull mode
	orl	_P2MDOUT,#0x01
;	C:\UBC\SECOND YEAR\ELEC 291\Project 2\ELEC291Project2\EFM8\Robot\main.c:78: XBR0     = 0x01; // Enable UART0 on P0.4(TX) and P0.5(RX)
	mov	_XBR0,#0x01
;	C:\UBC\SECOND YEAR\ELEC 291\Project 2\ELEC291Project2\EFM8\Robot\main.c:79: XBR1     = 0X00;
	mov	_XBR1,#0x00
;	C:\UBC\SECOND YEAR\ELEC 291\Project 2\ELEC291Project2\EFM8\Robot\main.c:80: XBR2     = 0x41; // Enable crossbar and uart 1
	mov	_XBR2,#0x41
;	C:\UBC\SECOND YEAR\ELEC 291\Project 2\ELEC291Project2\EFM8\Robot\main.c:86: SCON0 = 0x10;
	mov	_SCON0,#0x10
;	C:\UBC\SECOND YEAR\ELEC 291\Project 2\ELEC291Project2\EFM8\Robot\main.c:87: TH1 = 0x100-((SYSCLK/BAUDRATE)/(2L*12L));
	mov	_TH1,#0xE6
;	C:\UBC\SECOND YEAR\ELEC 291\Project 2\ELEC291Project2\EFM8\Robot\main.c:88: TL1 = TH1;      // Init Timer1
	mov	_TL1,_TH1
;	C:\UBC\SECOND YEAR\ELEC 291\Project 2\ELEC291Project2\EFM8\Robot\main.c:89: TMOD &= ~0xf0;  // TMOD: timer 1 in 8-bit auto-reload
	anl	_TMOD,#0x0F
;	C:\UBC\SECOND YEAR\ELEC 291\Project 2\ELEC291Project2\EFM8\Robot\main.c:90: TMOD |=  0x20;
	orl	_TMOD,#0x20
;	C:\UBC\SECOND YEAR\ELEC 291\Project 2\ELEC291Project2\EFM8\Robot\main.c:91: TR1 = 1; // START Timer1
	setb	_TR1
;	C:\UBC\SECOND YEAR\ELEC 291\Project 2\ELEC291Project2\EFM8\Robot\main.c:92: TI = 1;  // Indicate TX0 ready
	setb	_TI
;	C:\UBC\SECOND YEAR\ELEC 291\Project 2\ELEC291Project2\EFM8\Robot\main.c:94: return 0;
	mov	dpl,#0x00
	ret
;------------------------------------------------------------
;Allocation info for local variables in function 'TIMER0_Init'
;------------------------------------------------------------
;------------------------------------------------------------
;	C:\UBC\SECOND YEAR\ELEC 291\Project 2\ELEC291Project2\EFM8\Robot\main.c:96: void TIMER0_Init(void) {
;	-----------------------------------------
;	 function TIMER0_Init
;	-----------------------------------------
_TIMER0_Init:
;	C:\UBC\SECOND YEAR\ELEC 291\Project 2\ELEC291Project2\EFM8\Robot\main.c:97: TMOD &= 0b_1111_0000; // Set the Bits of Timer/Counter 0 to 0
	anl	_TMOD,#0xF0
;	C:\UBC\SECOND YEAR\ELEC 291\Project 2\ELEC291Project2\EFM8\Robot\main.c:98: TMOD |= 0b_0000_0001; // Timer/Counter 0 Used As 16-Bit Timer
	orl	_TMOD,#0x01
;	C:\UBC\SECOND YEAR\ELEC 291\Project 2\ELEC291Project2\EFM8\Robot\main.c:99: TR0 = 0; // Stop Timer/Counter 0
	clr	_TR0
	ret
;------------------------------------------------------------
;Allocation info for local variables in function 'Timer3us'
;------------------------------------------------------------
;us                        Allocated to registers r2 
;i                         Allocated to registers r3 
;------------------------------------------------------------
;	C:\UBC\SECOND YEAR\ELEC 291\Project 2\ELEC291Project2\EFM8\Robot\main.c:108: void Timer3us(unsigned char us)
;	-----------------------------------------
;	 function Timer3us
;	-----------------------------------------
_Timer3us:
	mov	r2,dpl
;	C:\UBC\SECOND YEAR\ELEC 291\Project 2\ELEC291Project2\EFM8\Robot\main.c:113: CKCON0|=0b_0100_0000;
	orl	_CKCON0,#0x40
;	C:\UBC\SECOND YEAR\ELEC 291\Project 2\ELEC291Project2\EFM8\Robot\main.c:115: TMR3RL = (-(SYSCLK)/1000000L); // Set Timer3 to overflow in 1us.
	mov	_TMR3RL,#0xB8
	mov	(_TMR3RL >> 8),#0xFF
;	C:\UBC\SECOND YEAR\ELEC 291\Project 2\ELEC291Project2\EFM8\Robot\main.c:116: TMR3 = TMR3RL;                 // Initialize Timer3 for first overflow
	mov	_TMR3,_TMR3RL
	mov	(_TMR3 >> 8),(_TMR3RL >> 8)
;	C:\UBC\SECOND YEAR\ELEC 291\Project 2\ELEC291Project2\EFM8\Robot\main.c:118: TMR3CN0 = 0x04;                 // Sart Timer3 and clear overflow flag
	mov	_TMR3CN0,#0x04
;	C:\UBC\SECOND YEAR\ELEC 291\Project 2\ELEC291Project2\EFM8\Robot\main.c:119: for (i = 0; i < us; i++)       // Count <us> overflows
	mov	r3,#0x00
L004004?:
	clr	c
	mov	a,r3
	subb	a,r2
	jnc	L004007?
;	C:\UBC\SECOND YEAR\ELEC 291\Project 2\ELEC291Project2\EFM8\Robot\main.c:121: while (!(TMR3CN0 & 0x80));  // Wait for overflow
L004001?:
	mov	a,_TMR3CN0
	jnb	acc.7,L004001?
;	C:\UBC\SECOND YEAR\ELEC 291\Project 2\ELEC291Project2\EFM8\Robot\main.c:122: TMR3CN0 &= ~(0x80);         // Clear overflow indicator
	anl	_TMR3CN0,#0x7F
;	C:\UBC\SECOND YEAR\ELEC 291\Project 2\ELEC291Project2\EFM8\Robot\main.c:119: for (i = 0; i < us; i++)       // Count <us> overflows
	inc	r3
	sjmp	L004004?
L004007?:
;	C:\UBC\SECOND YEAR\ELEC 291\Project 2\ELEC291Project2\EFM8\Robot\main.c:124: TMR3CN0 = 0 ;                   // Stop Timer3 and clear overflow flag
	mov	_TMR3CN0,#0x00
	ret
;------------------------------------------------------------
;Allocation info for local variables in function 'waitms'
;------------------------------------------------------------
;ms                        Allocated to registers r2 r3 
;j                         Allocated to registers r4 r5 
;k                         Allocated to registers r6 
;------------------------------------------------------------
;	C:\UBC\SECOND YEAR\ELEC 291\Project 2\ELEC291Project2\EFM8\Robot\main.c:127: void waitms (unsigned int ms)
;	-----------------------------------------
;	 function waitms
;	-----------------------------------------
_waitms:
	mov	r2,dpl
	mov	r3,dph
;	C:\UBC\SECOND YEAR\ELEC 291\Project 2\ELEC291Project2\EFM8\Robot\main.c:131: for(j=0; j<ms; j++)
	mov	r4,#0x00
	mov	r5,#0x00
L005005?:
	clr	c
	mov	a,r4
	subb	a,r2
	mov	a,r5
	subb	a,r3
	jnc	L005009?
;	C:\UBC\SECOND YEAR\ELEC 291\Project 2\ELEC291Project2\EFM8\Robot\main.c:132: for (k=0; k<4; k++) Timer3us(250);
	mov	r6,#0x00
L005001?:
	cjne	r6,#0x04,L005018?
L005018?:
	jnc	L005007?
	mov	dpl,#0xFA
	push	ar2
	push	ar3
	push	ar4
	push	ar5
	push	ar6
	lcall	_Timer3us
	pop	ar6
	pop	ar5
	pop	ar4
	pop	ar3
	pop	ar2
	inc	r6
	sjmp	L005001?
L005007?:
;	C:\UBC\SECOND YEAR\ELEC 291\Project 2\ELEC291Project2\EFM8\Robot\main.c:131: for(j=0; j<ms; j++)
	inc	r4
	cjne	r4,#0x00,L005005?
	inc	r5
	sjmp	L005005?
L005009?:
	ret
;------------------------------------------------------------
;Allocation info for local variables in function 'Serial_Init'
;------------------------------------------------------------
;------------------------------------------------------------
;	C:\UBC\SECOND YEAR\ELEC 291\Project 2\ELEC291Project2\EFM8\Robot\main.c:135: void Serial_Init(void) {
;	-----------------------------------------
;	 function Serial_Init
;	-----------------------------------------
_Serial_Init:
;	C:\UBC\SECOND YEAR\ELEC 291\Project 2\ELEC291Project2\EFM8\Robot\main.c:136: waitms(500); // Give Putty a chance to start.
	mov	dptr,#0x01F4
	lcall	_waitms
;	C:\UBC\SECOND YEAR\ELEC 291\Project 2\ELEC291Project2\EFM8\Robot\main.c:137: printf("\x1b[2J"); // Clear screen using ANSI escape sequence.
	mov	a,#__str_0
	push	acc
	mov	a,#(__str_0 >> 8)
	push	acc
	mov	a,#0x80
	push	acc
	lcall	_printf
	dec	sp
	dec	sp
	dec	sp
	ret
;------------------------------------------------------------
;Allocation info for local variables in function 'UART1_Init'
;------------------------------------------------------------
;baudrate                  Allocated to registers r2 r3 r4 r5 
;------------------------------------------------------------
;	C:\UBC\SECOND YEAR\ELEC 291\Project 2\ELEC291Project2\EFM8\Robot\main.c:140: void UART1_Init (unsigned long baudrate)
;	-----------------------------------------
;	 function UART1_Init
;	-----------------------------------------
_UART1_Init:
	mov	r2,dpl
	mov	r3,dph
	mov	r4,b
	mov	r5,a
;	C:\UBC\SECOND YEAR\ELEC 291\Project 2\ELEC291Project2\EFM8\Robot\main.c:142: SFRPAGE = 0x20;
	mov	_SFRPAGE,#0x20
;	C:\UBC\SECOND YEAR\ELEC 291\Project 2\ELEC291Project2\EFM8\Robot\main.c:143: SMOD1 = 0x0C; // no parity, 8 data bits, 1 stop bit
	mov	_SMOD1,#0x0C
;	C:\UBC\SECOND YEAR\ELEC 291\Project 2\ELEC291Project2\EFM8\Robot\main.c:144: SCON1 = 0x10;
	mov	_SCON1,#0x10
;	C:\UBC\SECOND YEAR\ELEC 291\Project 2\ELEC291Project2\EFM8\Robot\main.c:145: SBCON1 =0x00;   // disable baud rate generator
	mov	_SBCON1,#0x00
;	C:\UBC\SECOND YEAR\ELEC 291\Project 2\ELEC291Project2\EFM8\Robot\main.c:146: SBRL1 = 0x10000L-((SYSCLK/baudrate)/(12L*2L));
	mov	__divulong_PARM_2,r2
	mov	(__divulong_PARM_2 + 1),r3
	mov	(__divulong_PARM_2 + 2),r4
	mov	(__divulong_PARM_2 + 3),r5
	mov	dptr,#0xA200
	mov	b,#0x4A
	mov	a,#0x04
	lcall	__divulong
	mov	r2,dpl
	mov	r3,dph
	mov	r4,b
	mov	r5,a
	mov	__divulong_PARM_2,#0x18
	clr	a
	mov	(__divulong_PARM_2 + 1),a
	mov	(__divulong_PARM_2 + 2),a
	mov	(__divulong_PARM_2 + 3),a
	mov	dpl,r2
	mov	dph,r3
	mov	b,r4
	mov	a,r5
	lcall	__divulong
	mov	r2,dpl
	mov	r3,dph
	mov	r4,b
	mov	r5,a
	clr	a
	clr	c
	subb	a,r2
	mov	r2,a
	clr	a
	subb	a,r3
	mov	r3,a
	mov	a,#0x01
	subb	a,r4
	clr	a
	subb	a,r5
	mov	_SBRL1,r2
	mov	(_SBRL1 >> 8),r3
;	C:\UBC\SECOND YEAR\ELEC 291\Project 2\ELEC291Project2\EFM8\Robot\main.c:147: TI1 = 1; // indicate ready for TX
	setb	_TI1
;	C:\UBC\SECOND YEAR\ELEC 291\Project 2\ELEC291Project2\EFM8\Robot\main.c:148: SBCON1 |= 0x40;   // enable baud rate generator
	orl	_SBCON1,#0x40
;	C:\UBC\SECOND YEAR\ELEC 291\Project 2\ELEC291Project2\EFM8\Robot\main.c:149: SFRPAGE = 0x00;
	mov	_SFRPAGE,#0x00
	ret
;------------------------------------------------------------
;Allocation info for local variables in function 'putchar1'
;------------------------------------------------------------
;c                         Allocated to registers r2 
;------------------------------------------------------------
;	C:\UBC\SECOND YEAR\ELEC 291\Project 2\ELEC291Project2\EFM8\Robot\main.c:152: void putchar1 (char c)
;	-----------------------------------------
;	 function putchar1
;	-----------------------------------------
_putchar1:
	mov	r2,dpl
;	C:\UBC\SECOND YEAR\ELEC 291\Project 2\ELEC291Project2\EFM8\Robot\main.c:154: SFRPAGE = 0x20;
	mov	_SFRPAGE,#0x20
;	C:\UBC\SECOND YEAR\ELEC 291\Project 2\ELEC291Project2\EFM8\Robot\main.c:155: while (!TI1);
L008001?:
;	C:\UBC\SECOND YEAR\ELEC 291\Project 2\ELEC291Project2\EFM8\Robot\main.c:156: TI1=0;
	jbc	_TI1,L008008?
	sjmp	L008001?
L008008?:
;	C:\UBC\SECOND YEAR\ELEC 291\Project 2\ELEC291Project2\EFM8\Robot\main.c:157: SBUF1 = c;
	mov	_SBUF1,r2
;	C:\UBC\SECOND YEAR\ELEC 291\Project 2\ELEC291Project2\EFM8\Robot\main.c:158: SFRPAGE = 0x00;
	mov	_SFRPAGE,#0x00
	ret
;------------------------------------------------------------
;Allocation info for local variables in function 'sendstr1'
;------------------------------------------------------------
;s                         Allocated to registers r2 r3 r4 
;------------------------------------------------------------
;	C:\UBC\SECOND YEAR\ELEC 291\Project 2\ELEC291Project2\EFM8\Robot\main.c:161: void sendstr1 (char * s)
;	-----------------------------------------
;	 function sendstr1
;	-----------------------------------------
_sendstr1:
	mov	r2,dpl
	mov	r3,dph
	mov	r4,b
;	C:\UBC\SECOND YEAR\ELEC 291\Project 2\ELEC291Project2\EFM8\Robot\main.c:163: while(*s)
L009001?:
	mov	dpl,r2
	mov	dph,r3
	mov	b,r4
	lcall	__gptrget
	mov	r5,a
	jz	L009004?
;	C:\UBC\SECOND YEAR\ELEC 291\Project 2\ELEC291Project2\EFM8\Robot\main.c:165: putchar1(*s);
	mov	dpl,r5
	push	ar2
	push	ar3
	push	ar4
	lcall	_putchar1
	pop	ar4
	pop	ar3
	pop	ar2
;	C:\UBC\SECOND YEAR\ELEC 291\Project 2\ELEC291Project2\EFM8\Robot\main.c:166: s++;
	inc	r2
	cjne	r2,#0x00,L009001?
	inc	r3
	sjmp	L009001?
L009004?:
	ret
;------------------------------------------------------------
;Allocation info for local variables in function 'getchar1'
;------------------------------------------------------------
;c                         Allocated to registers 
;------------------------------------------------------------
;	C:\UBC\SECOND YEAR\ELEC 291\Project 2\ELEC291Project2\EFM8\Robot\main.c:170: char getchar1 (void)
;	-----------------------------------------
;	 function getchar1
;	-----------------------------------------
_getchar1:
;	C:\UBC\SECOND YEAR\ELEC 291\Project 2\ELEC291Project2\EFM8\Robot\main.c:173: SFRPAGE = 0x20;
	mov	_SFRPAGE,#0x20
;	C:\UBC\SECOND YEAR\ELEC 291\Project 2\ELEC291Project2\EFM8\Robot\main.c:174: while (!RI1);
L010001?:
;	C:\UBC\SECOND YEAR\ELEC 291\Project 2\ELEC291Project2\EFM8\Robot\main.c:175: RI1=0;
	jbc	_RI1,L010008?
	sjmp	L010001?
L010008?:
;	C:\UBC\SECOND YEAR\ELEC 291\Project 2\ELEC291Project2\EFM8\Robot\main.c:177: SCON1&=0b_0011_1111;
	anl	_SCON1,#0x3F
;	C:\UBC\SECOND YEAR\ELEC 291\Project 2\ELEC291Project2\EFM8\Robot\main.c:178: c = SBUF1;
	mov	dpl,_SBUF1
;	C:\UBC\SECOND YEAR\ELEC 291\Project 2\ELEC291Project2\EFM8\Robot\main.c:179: SFRPAGE = 0x00;
	mov	_SFRPAGE,#0x00
;	C:\UBC\SECOND YEAR\ELEC 291\Project 2\ELEC291Project2\EFM8\Robot\main.c:180: return (c);
	ret
;------------------------------------------------------------
;Allocation info for local variables in function 'getchar1_with_timeout'
;------------------------------------------------------------
;c                         Allocated to registers 
;timeout                   Allocated to registers r2 r3 
;------------------------------------------------------------
;	C:\UBC\SECOND YEAR\ELEC 291\Project 2\ELEC291Project2\EFM8\Robot\main.c:183: char getchar1_with_timeout (void)
;	-----------------------------------------
;	 function getchar1_with_timeout
;	-----------------------------------------
_getchar1_with_timeout:
;	C:\UBC\SECOND YEAR\ELEC 291\Project 2\ELEC291Project2\EFM8\Robot\main.c:187: SFRPAGE = 0x20;
	mov	_SFRPAGE,#0x20
;	C:\UBC\SECOND YEAR\ELEC 291\Project 2\ELEC291Project2\EFM8\Robot\main.c:189: while (!RI1)
	mov	r2,#0x00
	mov	r3,#0x00
L011003?:
	jb	_RI1,L011005?
;	C:\UBC\SECOND YEAR\ELEC 291\Project 2\ELEC291Project2\EFM8\Robot\main.c:191: SFRPAGE = 0x00;
	mov	_SFRPAGE,#0x00
;	C:\UBC\SECOND YEAR\ELEC 291\Project 2\ELEC291Project2\EFM8\Robot\main.c:192: Timer3us(20);
	mov	dpl,#0x14
	push	ar2
	push	ar3
	lcall	_Timer3us
	pop	ar3
	pop	ar2
;	C:\UBC\SECOND YEAR\ELEC 291\Project 2\ELEC291Project2\EFM8\Robot\main.c:193: SFRPAGE = 0x20;
	mov	_SFRPAGE,#0x20
;	C:\UBC\SECOND YEAR\ELEC 291\Project 2\ELEC291Project2\EFM8\Robot\main.c:194: timeout++;
	inc	r2
	cjne	r2,#0x00,L011012?
	inc	r3
L011012?:
;	C:\UBC\SECOND YEAR\ELEC 291\Project 2\ELEC291Project2\EFM8\Robot\main.c:195: if(timeout==25000)
	cjne	r2,#0xA8,L011003?
	cjne	r3,#0x61,L011003?
;	C:\UBC\SECOND YEAR\ELEC 291\Project 2\ELEC291Project2\EFM8\Robot\main.c:197: SFRPAGE = 0x00;
	mov	_SFRPAGE,#0x00
;	C:\UBC\SECOND YEAR\ELEC 291\Project 2\ELEC291Project2\EFM8\Robot\main.c:198: return ('\n'); // Timeout after half second
	mov	dpl,#0x0A
	ret
L011005?:
;	C:\UBC\SECOND YEAR\ELEC 291\Project 2\ELEC291Project2\EFM8\Robot\main.c:201: RI1=0;
	clr	_RI1
;	C:\UBC\SECOND YEAR\ELEC 291\Project 2\ELEC291Project2\EFM8\Robot\main.c:203: SCON1&=0b_0011_1111;
	anl	_SCON1,#0x3F
;	C:\UBC\SECOND YEAR\ELEC 291\Project 2\ELEC291Project2\EFM8\Robot\main.c:204: c = SBUF1;
	mov	dpl,_SBUF1
;	C:\UBC\SECOND YEAR\ELEC 291\Project 2\ELEC291Project2\EFM8\Robot\main.c:205: SFRPAGE = 0x00;
	mov	_SFRPAGE,#0x00
;	C:\UBC\SECOND YEAR\ELEC 291\Project 2\ELEC291Project2\EFM8\Robot\main.c:206: return (c);
	ret
;------------------------------------------------------------
;Allocation info for local variables in function 'getstr1'
;------------------------------------------------------------
;s                         Allocated to registers r2 r3 r4 
;c                         Allocated to registers r5 
;------------------------------------------------------------
;	C:\UBC\SECOND YEAR\ELEC 291\Project 2\ELEC291Project2\EFM8\Robot\main.c:209: void getstr1 (char * s)
;	-----------------------------------------
;	 function getstr1
;	-----------------------------------------
_getstr1:
	mov	r2,dpl
	mov	r3,dph
	mov	r4,b
;	C:\UBC\SECOND YEAR\ELEC 291\Project 2\ELEC291Project2\EFM8\Robot\main.c:213: while(1)
L012004?:
;	C:\UBC\SECOND YEAR\ELEC 291\Project 2\ELEC291Project2\EFM8\Robot\main.c:215: c=getchar1_with_timeout();
	push	ar2
	push	ar3
	push	ar4
	lcall	_getchar1_with_timeout
	mov	r5,dpl
	pop	ar4
	pop	ar3
	pop	ar2
;	C:\UBC\SECOND YEAR\ELEC 291\Project 2\ELEC291Project2\EFM8\Robot\main.c:216: if(c=='\n')
	cjne	r5,#0x0A,L012002?
;	C:\UBC\SECOND YEAR\ELEC 291\Project 2\ELEC291Project2\EFM8\Robot\main.c:218: *s=0;
	mov	dpl,r2
	mov	dph,r3
	mov	b,r4
	clr	a
;	C:\UBC\SECOND YEAR\ELEC 291\Project 2\ELEC291Project2\EFM8\Robot\main.c:219: return;
	ljmp	__gptrput
L012002?:
;	C:\UBC\SECOND YEAR\ELEC 291\Project 2\ELEC291Project2\EFM8\Robot\main.c:221: *s=c;
	mov	dpl,r2
	mov	dph,r3
	mov	b,r4
	mov	a,r5
	lcall	__gptrput
	inc	dptr
	mov	r2,dpl
	mov	r3,dph
;	C:\UBC\SECOND YEAR\ELEC 291\Project 2\ELEC291Project2\EFM8\Robot\main.c:222: s++;
	sjmp	L012004?
;------------------------------------------------------------
;Allocation info for local variables in function 'RXU1'
;------------------------------------------------------------
;------------------------------------------------------------
;	C:\UBC\SECOND YEAR\ELEC 291\Project 2\ELEC291Project2\EFM8\Robot\main.c:227: bit RXU1 (void)
;	-----------------------------------------
;	 function RXU1
;	-----------------------------------------
_RXU1:
;	C:\UBC\SECOND YEAR\ELEC 291\Project 2\ELEC291Project2\EFM8\Robot\main.c:230: SFRPAGE = 0x20;
	mov	_SFRPAGE,#0x20
;	C:\UBC\SECOND YEAR\ELEC 291\Project 2\ELEC291Project2\EFM8\Robot\main.c:231: mybit=RI1;
	mov	c,_RI1
;	C:\UBC\SECOND YEAR\ELEC 291\Project 2\ELEC291Project2\EFM8\Robot\main.c:232: SFRPAGE = 0x00;
	mov	_SFRPAGE,#0x00
;	C:\UBC\SECOND YEAR\ELEC 291\Project 2\ELEC291Project2\EFM8\Robot\main.c:233: return mybit;
	ret
;------------------------------------------------------------
;Allocation info for local variables in function 'waitms_or_RI1'
;------------------------------------------------------------
;ms                        Allocated to registers r2 r3 
;j                         Allocated to registers r4 r5 
;k                         Allocated to registers r6 
;------------------------------------------------------------
;	C:\UBC\SECOND YEAR\ELEC 291\Project 2\ELEC291Project2\EFM8\Robot\main.c:236: void waitms_or_RI1 (unsigned int ms)
;	-----------------------------------------
;	 function waitms_or_RI1
;	-----------------------------------------
_waitms_or_RI1:
	mov	r2,dpl
	mov	r3,dph
;	C:\UBC\SECOND YEAR\ELEC 291\Project 2\ELEC291Project2\EFM8\Robot\main.c:240: for(j=0; j<ms; j++)
	mov	r4,#0x00
	mov	r5,#0x00
L014007?:
	clr	c
	mov	a,r4
	subb	a,r2
	mov	a,r5
	subb	a,r3
	jnc	L014011?
;	C:\UBC\SECOND YEAR\ELEC 291\Project 2\ELEC291Project2\EFM8\Robot\main.c:242: for (k=0; k<4; k++)
	mov	r6,#0x00
L014003?:
	cjne	r6,#0x04,L014019?
L014019?:
	jnc	L014009?
;	C:\UBC\SECOND YEAR\ELEC 291\Project 2\ELEC291Project2\EFM8\Robot\main.c:244: if(RXU1()) return;
	push	ar2
	push	ar3
	push	ar4
	push	ar5
	push	ar6
	lcall	_RXU1
	clr	a
	rlc	a
	pop	ar6
	pop	ar5
	pop	ar4
	pop	ar3
	pop	ar2
	jz	L014002?
	ret
L014002?:
;	C:\UBC\SECOND YEAR\ELEC 291\Project 2\ELEC291Project2\EFM8\Robot\main.c:245: Timer3us(250);
	mov	dpl,#0xFA
	push	ar2
	push	ar3
	push	ar4
	push	ar5
	push	ar6
	lcall	_Timer3us
	pop	ar6
	pop	ar5
	pop	ar4
	pop	ar3
	pop	ar2
;	C:\UBC\SECOND YEAR\ELEC 291\Project 2\ELEC291Project2\EFM8\Robot\main.c:242: for (k=0; k<4; k++)
	inc	r6
	sjmp	L014003?
L014009?:
;	C:\UBC\SECOND YEAR\ELEC 291\Project 2\ELEC291Project2\EFM8\Robot\main.c:240: for(j=0; j<ms; j++)
	inc	r4
	cjne	r4,#0x00,L014007?
	inc	r5
	sjmp	L014007?
L014011?:
	ret
;------------------------------------------------------------
;Allocation info for local variables in function 'SendATCommand'
;------------------------------------------------------------
;s                         Allocated to registers r2 r3 r4 
;------------------------------------------------------------
;	C:\UBC\SECOND YEAR\ELEC 291\Project 2\ELEC291Project2\EFM8\Robot\main.c:250: void SendATCommand (char * s)
;	-----------------------------------------
;	 function SendATCommand
;	-----------------------------------------
_SendATCommand:
	mov	r2,dpl
	mov	r3,dph
	mov	r4,b
;	C:\UBC\SECOND YEAR\ELEC 291\Project 2\ELEC291Project2\EFM8\Robot\main.c:252: printf("Command: %s", s);
	push	ar2
	push	ar3
	push	ar4
	push	ar2
	push	ar3
	push	ar4
	mov	a,#__str_1
	push	acc
	mov	a,#(__str_1 >> 8)
	push	acc
	mov	a,#0x80
	push	acc
	lcall	_printf
	mov	a,sp
	add	a,#0xfa
	mov	sp,a
;	C:\UBC\SECOND YEAR\ELEC 291\Project 2\ELEC291Project2\EFM8\Robot\main.c:253: P2_0=0; // 'set' pin to 0 is 'AT' mode.
	clr	_P2_0
;	C:\UBC\SECOND YEAR\ELEC 291\Project 2\ELEC291Project2\EFM8\Robot\main.c:254: waitms(5);
	mov	dptr,#0x0005
	lcall	_waitms
	pop	ar4
	pop	ar3
	pop	ar2
;	C:\UBC\SECOND YEAR\ELEC 291\Project 2\ELEC291Project2\EFM8\Robot\main.c:255: sendstr1(s);
	mov	dpl,r2
	mov	dph,r3
	mov	b,r4
	lcall	_sendstr1
;	C:\UBC\SECOND YEAR\ELEC 291\Project 2\ELEC291Project2\EFM8\Robot\main.c:256: getstr1(TX_BUFF);
	mov	dptr,#_TX_BUFF
	mov	b,#0x40
	lcall	_getstr1
;	C:\UBC\SECOND YEAR\ELEC 291\Project 2\ELEC291Project2\EFM8\Robot\main.c:257: waitms(10);
	mov	dptr,#0x000A
	lcall	_waitms
;	C:\UBC\SECOND YEAR\ELEC 291\Project 2\ELEC291Project2\EFM8\Robot\main.c:258: P2_0=1; // 'set' pin to 1 is normal operation mode.
	setb	_P2_0
;	C:\UBC\SECOND YEAR\ELEC 291\Project 2\ELEC291Project2\EFM8\Robot\main.c:259: printf("Response: %s\r\n", TX_BUFF);
	mov	a,#_TX_BUFF
	push	acc
	mov	a,#(_TX_BUFF >> 8)
	push	acc
	mov	a,#0x40
	push	acc
	mov	a,#__str_2
	push	acc
	mov	a,#(__str_2 >> 8)
	push	acc
	mov	a,#0x80
	push	acc
	lcall	_printf
	mov	a,sp
	add	a,#0xfa
	mov	sp,a
	ret
;------------------------------------------------------------
;Allocation info for local variables in function 'JDYInit'
;------------------------------------------------------------
;------------------------------------------------------------
;	C:\UBC\SECOND YEAR\ELEC 291\Project 2\ELEC291Project2\EFM8\Robot\main.c:262: void JDYInit (void){
;	-----------------------------------------
;	 function JDYInit
;	-----------------------------------------
_JDYInit:
;	C:\UBC\SECOND YEAR\ELEC 291\Project 2\ELEC291Project2\EFM8\Robot\main.c:263: SendATCommand("AT+DVIDAFAF\r\n");
	mov	dptr,#__str_3
	mov	b,#0x80
	lcall	_SendATCommand
;	C:\UBC\SECOND YEAR\ELEC 291\Project 2\ELEC291Project2\EFM8\Robot\main.c:264: SendATCommand("AT+RFIDFFBB\r\n");
	mov	dptr,#__str_4
	mov	b,#0x80
	lcall	_SendATCommand
;	C:\UBC\SECOND YEAR\ELEC 291\Project 2\ELEC291Project2\EFM8\Robot\main.c:266: SendATCommand("AT+VER\r\n");
	mov	dptr,#__str_5
	mov	b,#0x80
	lcall	_SendATCommand
;	C:\UBC\SECOND YEAR\ELEC 291\Project 2\ELEC291Project2\EFM8\Robot\main.c:267: SendATCommand("AT+BAUD\r\n");
	mov	dptr,#__str_6
	mov	b,#0x80
	lcall	_SendATCommand
;	C:\UBC\SECOND YEAR\ELEC 291\Project 2\ELEC291Project2\EFM8\Robot\main.c:268: SendATCommand("AT+RFID\r\n");
	mov	dptr,#__str_7
	mov	b,#0x80
	lcall	_SendATCommand
;	C:\UBC\SECOND YEAR\ELEC 291\Project 2\ELEC291Project2\EFM8\Robot\main.c:269: SendATCommand("AT+DVID\r\n");
	mov	dptr,#__str_8
	mov	b,#0x80
	lcall	_SendATCommand
;	C:\UBC\SECOND YEAR\ELEC 291\Project 2\ELEC291Project2\EFM8\Robot\main.c:270: SendATCommand("AT+RFC\r\n");
	mov	dptr,#__str_9
	mov	b,#0x80
	lcall	_SendATCommand
;	C:\UBC\SECOND YEAR\ELEC 291\Project 2\ELEC291Project2\EFM8\Robot\main.c:271: SendATCommand("AT+POWE\r\n");
	mov	dptr,#__str_10
	mov	b,#0x80
	lcall	_SendATCommand
;	C:\UBC\SECOND YEAR\ELEC 291\Project 2\ELEC291Project2\EFM8\Robot\main.c:272: SendATCommand("AT+CLSS\r\n");
	mov	dptr,#__str_11
	mov	b,#0x80
	ljmp	_SendATCommand
;------------------------------------------------------------
;Allocation info for local variables in function 'calculate_period_s'
;------------------------------------------------------------
;TH0                       Allocated with name '_calculate_period_s_PARM_2'
;TL0                       Allocated with name '_calculate_period_s_PARM_3'
;overflow_count            Allocated to registers r2 r3 
;------------------------------------------------------------
;	C:\UBC\SECOND YEAR\ELEC 291\Project 2\ELEC291Project2\EFM8\Robot\main.c:275: float calculate_period_s(int overflow_count, int TH0, int TL0) {
;	-----------------------------------------
;	 function calculate_period_s
;	-----------------------------------------
_calculate_period_s:
;	C:\UBC\SECOND YEAR\ELEC 291\Project 2\ELEC291Project2\EFM8\Robot\main.c:276: return ((overflow_count * MAX_16_BIT)  + (TH0 * MAX_8_BIT) + TL0) * (12.0 / SYSCLK);
	lcall	___sint2fs
	mov	r2,dpl
	mov	r3,dph
	mov	r4,b
	mov	r5,a
	push	ar2
	push	ar3
	push	ar4
	push	ar5
	mov	dptr,#0x0000
	mov	b,#0x80
	mov	a,#0x47
	lcall	___fsmul
	mov	r2,dpl
	mov	r3,dph
	mov	r4,b
	mov	r5,a
	mov	a,sp
	add	a,#0xfc
	mov	sp,a
	mov	dpl,_calculate_period_s_PARM_2
	mov	dph,(_calculate_period_s_PARM_2 + 1)
	push	ar2
	push	ar3
	push	ar4
	push	ar5
	lcall	___sint2fs
	mov	r6,dpl
	mov	r7,dph
	mov	r0,b
	mov	r1,a
	push	ar6
	push	ar7
	push	ar0
	push	ar1
	mov	dptr,#0x0000
	mov	b,#0x80
	mov	a,#0x43
	lcall	___fsmul
	mov	r6,dpl
	mov	r7,dph
	mov	r0,b
	mov	r1,a
	mov	a,sp
	add	a,#0xfc
	mov	sp,a
	pop	ar5
	pop	ar4
	pop	ar3
	pop	ar2
	push	ar6
	push	ar7
	push	ar0
	push	ar1
	mov	dpl,r2
	mov	dph,r3
	mov	b,r4
	mov	a,r5
	lcall	___fsadd
	mov	r2,dpl
	mov	r3,dph
	mov	r4,b
	mov	r5,a
	mov	a,sp
	add	a,#0xfc
	mov	sp,a
	mov	dpl,_calculate_period_s_PARM_3
	mov	dph,(_calculate_period_s_PARM_3 + 1)
	push	ar2
	push	ar3
	push	ar4
	push	ar5
	lcall	___sint2fs
	mov	r6,dpl
	mov	r7,dph
	mov	r0,b
	mov	r1,a
	pop	ar5
	pop	ar4
	pop	ar3
	pop	ar2
	push	ar6
	push	ar7
	push	ar0
	push	ar1
	mov	dpl,r2
	mov	dph,r3
	mov	b,r4
	mov	a,r5
	lcall	___fsadd
	mov	r2,dpl
	mov	r3,dph
	mov	r4,b
	mov	r5,a
	mov	a,sp
	add	a,#0xfc
	mov	sp,a
	push	ar2
	push	ar3
	push	ar4
	push	ar5
	mov	dptr,#0xF4FC
	mov	b,#0x32
	mov	a,#0x34
	lcall	___fsmul
	mov	r2,dpl
	mov	r3,dph
	mov	r4,b
	mov	r5,a
	mov	a,sp
	add	a,#0xfc
	mov	sp,a
	mov	dpl,r2
	mov	dph,r3
	mov	b,r4
	mov	a,r5
	ret
;------------------------------------------------------------
;Allocation info for local variables in function 'calculate_freq_Hz'
;------------------------------------------------------------
;period_s                  Allocated to registers r2 r3 r4 r5 
;------------------------------------------------------------
;	C:\UBC\SECOND YEAR\ELEC 291\Project 2\ELEC291Project2\EFM8\Robot\main.c:279: float calculate_freq_Hz(float period_s) {
;	-----------------------------------------
;	 function calculate_freq_Hz
;	-----------------------------------------
_calculate_freq_Hz:
	mov	r2,dpl
	mov	r3,dph
	mov	r4,b
	mov	r5,a
;	C:\UBC\SECOND YEAR\ELEC 291\Project 2\ELEC291Project2\EFM8\Robot\main.c:280: return (1.0 / period_s);
	push	ar2
	push	ar3
	push	ar4
	push	ar5
	mov	dptr,#0x0000
	mov	b,#0x80
	mov	a,#0x3F
	lcall	___fsdiv
	mov	r2,dpl
	mov	r3,dph
	mov	r4,b
	mov	r5,a
	mov	a,sp
	add	a,#0xfc
	mov	sp,a
	mov	dpl,r2
	mov	dph,r3
	mov	b,r4
	mov	a,r5
	ret
;------------------------------------------------------------
;Allocation info for local variables in function 'GetFreq'
;------------------------------------------------------------
;period_s                  Allocated to registers r2 r3 r4 r5 
;freq_Hz                   Allocated to registers r2 r3 r4 r5 
;overflow_count            Allocated to registers r2 r3 
;------------------------------------------------------------
;	C:\UBC\SECOND YEAR\ELEC 291\Project 2\ELEC291Project2\EFM8\Robot\main.c:283: float GetFreq(void) {
;	-----------------------------------------
;	 function GetFreq
;	-----------------------------------------
_GetFreq:
;	C:\UBC\SECOND YEAR\ELEC 291\Project 2\ELEC291Project2\EFM8\Robot\main.c:286: TL0 = 0;
	mov	_TL0,#0x00
;	C:\UBC\SECOND YEAR\ELEC 291\Project 2\ELEC291Project2\EFM8\Robot\main.c:287: TH0 = 0;
	mov	_TH0,#0x00
;	C:\UBC\SECOND YEAR\ELEC 291\Project 2\ELEC291Project2\EFM8\Robot\main.c:288: TF0 = 0;
	clr	_TF0
;	C:\UBC\SECOND YEAR\ELEC 291\Project 2\ELEC291Project2\EFM8\Robot\main.c:291: while (EFM8_SIGNAL != 0); // Wait for Signal == 0
L019001?:
	jb	_P1_0,L019001?
;	C:\UBC\SECOND YEAR\ELEC 291\Project 2\ELEC291Project2\EFM8\Robot\main.c:292: while (EFM8_SIGNAL != 1); // Wait for Signal == 1
L019004?:
	jnb	_P1_0,L019004?
;	C:\UBC\SECOND YEAR\ELEC 291\Project 2\ELEC291Project2\EFM8\Robot\main.c:294: TR0 = 1; // Start Timer
	setb	_TR0
;	C:\UBC\SECOND YEAR\ELEC 291\Project 2\ELEC291Project2\EFM8\Robot\main.c:296: while (EFM8_SIGNAL != 0) { // Wait for Signal == 0
	mov	r2,#0x00
	mov	r3,#0x00
L019009?:
	jnb	_P1_0,L019026?
;	C:\UBC\SECOND YEAR\ELEC 291\Project 2\ELEC291Project2\EFM8\Robot\main.c:297: if (TF0 == 1) { // Did 16-Bit Timer Overflow?
;	C:\UBC\SECOND YEAR\ELEC 291\Project 2\ELEC291Project2\EFM8\Robot\main.c:298: TF0 = 0;
	jbc	_TF0,L019033?
	sjmp	L019009?
L019033?:
;	C:\UBC\SECOND YEAR\ELEC 291\Project 2\ELEC291Project2\EFM8\Robot\main.c:299: overflow_count++;
	inc	r2
	cjne	r2,#0x00,L019009?
	inc	r3
;	C:\UBC\SECOND YEAR\ELEC 291\Project 2\ELEC291Project2\EFM8\Robot\main.c:302: while (EFM8_SIGNAL != 1) { // Wait for Signal == 1
	sjmp	L019009?
L019026?:
L019014?:
	jb	_P1_0,L019016?
;	C:\UBC\SECOND YEAR\ELEC 291\Project 2\ELEC291Project2\EFM8\Robot\main.c:303: if (TF0 == 1) { // Did 16-Bit Timer Overflow?
;	C:\UBC\SECOND YEAR\ELEC 291\Project 2\ELEC291Project2\EFM8\Robot\main.c:304: TF0 = 0;
	jbc	_TF0,L019035?
	sjmp	L019014?
L019035?:
;	C:\UBC\SECOND YEAR\ELEC 291\Project 2\ELEC291Project2\EFM8\Robot\main.c:305: overflow_count++;
	inc	r2
	cjne	r2,#0x00,L019014?
	inc	r3
	sjmp	L019014?
L019016?:
;	C:\UBC\SECOND YEAR\ELEC 291\Project 2\ELEC291Project2\EFM8\Robot\main.c:309: TR0 = 0; // Stop Timer 0. The 24-bit number [overflow_count-TH0-TL0] has the period!
	clr	_TR0
;	C:\UBC\SECOND YEAR\ELEC 291\Project 2\ELEC291Project2\EFM8\Robot\main.c:310: period_s = calculate_period_s(overflow_count, TH0, TL0);
	mov	_calculate_period_s_PARM_2,_TH0
	mov	(_calculate_period_s_PARM_2 + 1),#0x00
	mov	_calculate_period_s_PARM_3,_TL0
	mov	(_calculate_period_s_PARM_3 + 1),#0x00
	mov	dpl,r2
	mov	dph,r3
	lcall	_calculate_period_s
;	C:\UBC\SECOND YEAR\ELEC 291\Project 2\ELEC291Project2\EFM8\Robot\main.c:311: freq_Hz = calculate_freq_Hz(period_s);
;	C:\UBC\SECOND YEAR\ELEC 291\Project 2\ELEC291Project2\EFM8\Robot\main.c:312: return freq_Hz;
	ljmp	_calculate_freq_Hz
;------------------------------------------------------------
;Allocation info for local variables in function 'SendFreq'
;------------------------------------------------------------
;freq                      Allocated to registers r2 r3 r4 r5 
;------------------------------------------------------------
;	C:\UBC\SECOND YEAR\ELEC 291\Project 2\ELEC291Project2\EFM8\Robot\main.c:315: void SendFreq(float freq){
;	-----------------------------------------
;	 function SendFreq
;	-----------------------------------------
_SendFreq:
	mov	r2,dpl
	mov	r3,dph
	mov	r4,b
	mov	r5,a
;	C:\UBC\SECOND YEAR\ELEC 291\Project 2\ELEC291Project2\EFM8\Robot\main.c:316: sprintf(TX_BUFF,"%.3f",freq);
	push	ar2
	push	ar3
	push	ar4
	push	ar5
	mov	a,#__str_12
	push	acc
	mov	a,#(__str_12 >> 8)
	push	acc
	mov	a,#0x80
	push	acc
	mov	a,#_TX_BUFF
	push	acc
	mov	a,#(_TX_BUFF >> 8)
	push	acc
	mov	a,#0x40
	push	acc
	lcall	_sprintf
	mov	a,sp
	add	a,#0xf6
	mov	sp,a
;	C:\UBC\SECOND YEAR\ELEC 291\Project 2\ELEC291Project2\EFM8\Robot\main.c:317: sendstr1(TX_BUFF);
	mov	dptr,#_TX_BUFF
	mov	b,#0x40
	lcall	_sendstr1
;	C:\UBC\SECOND YEAR\ELEC 291\Project 2\ELEC291Project2\EFM8\Robot\main.c:318: waitms_or_RI1(100);
	mov	dptr,#0x0064
	ljmp	_waitms_or_RI1
;------------------------------------------------------------
;Allocation info for local variables in function 'GetData'
;------------------------------------------------------------
;------------------------------------------------------------
;	C:\UBC\SECOND YEAR\ELEC 291\Project 2\ELEC291Project2\EFM8\Robot\main.c:321: void GetData(void){
;	-----------------------------------------
;	 function GetData
;	-----------------------------------------
_GetData:
;	C:\UBC\SECOND YEAR\ELEC 291\Project 2\ELEC291Project2\EFM8\Robot\main.c:322: if (RXU1()){
	lcall	_RXU1
	jnc	L021003?
;	C:\UBC\SECOND YEAR\ELEC 291\Project 2\ELEC291Project2\EFM8\Robot\main.c:323: getstr1(RX_BUFF);
	mov	dptr,#_RX_BUFF
	mov	b,#0x40
	lcall	_getstr1
;	C:\UBC\SECOND YEAR\ELEC 291\Project 2\ELEC291Project2\EFM8\Robot\main.c:324: printf("%s \r\n",RX_BUFF);
	mov	a,#_RX_BUFF
	push	acc
	mov	a,#(_RX_BUFF >> 8)
	push	acc
	mov	a,#0x40
	push	acc
	mov	a,#__str_13
	push	acc
	mov	a,#(__str_13 >> 8)
	push	acc
	mov	a,#0x80
	push	acc
	lcall	_printf
	mov	a,sp
	add	a,#0xfa
	mov	sp,a
L021003?:
	ret
;------------------------------------------------------------
;Allocation info for local variables in function 'RXData'
;------------------------------------------------------------
;------------------------------------------------------------
;	C:\UBC\SECOND YEAR\ELEC 291\Project 2\ELEC291Project2\EFM8\Robot\main.c:328: void RXData(void){
;	-----------------------------------------
;	 function RXData
;	-----------------------------------------
_RXData:
;	C:\UBC\SECOND YEAR\ELEC 291\Project 2\ELEC291Project2\EFM8\Robot\main.c:329: if (RXU1()){
	lcall	_RXU1
	jnc	L022003?
;	C:\UBC\SECOND YEAR\ELEC 291\Project 2\ELEC291Project2\EFM8\Robot\main.c:330: getstr1(RX_BUFF);
	mov	dptr,#_RX_BUFF
	mov	b,#0x40
	lcall	_getstr1
;	C:\UBC\SECOND YEAR\ELEC 291\Project 2\ELEC291Project2\EFM8\Robot\main.c:331: printf("%s\r\n",RX_BUFF);
	mov	a,#_RX_BUFF
	push	acc
	mov	a,#(_RX_BUFF >> 8)
	push	acc
	mov	a,#0x40
	push	acc
	mov	a,#__str_14
	push	acc
	mov	a,#(__str_14 >> 8)
	push	acc
	mov	a,#0x80
	push	acc
	lcall	_printf
	mov	a,sp
	add	a,#0xfa
	mov	sp,a
L022003?:
	ret
;------------------------------------------------------------
;Allocation info for local variables in function 'TXInductance'
;------------------------------------------------------------
;------------------------------------------------------------
;	C:\UBC\SECOND YEAR\ELEC 291\Project 2\ELEC291Project2\EFM8\Robot\main.c:337: void TXInductance(void){
;	-----------------------------------------
;	 function TXInductance
;	-----------------------------------------
_TXInductance:
;	C:\UBC\SECOND YEAR\ELEC 291\Project 2\ELEC291Project2\EFM8\Robot\main.c:338: sprintf(TX_BUFF,"%d",inductance);
	push	_inductance
	push	(_inductance + 1)
	mov	a,#__str_15
	push	acc
	mov	a,#(__str_15 >> 8)
	push	acc
	mov	a,#0x80
	push	acc
	mov	a,#_TX_BUFF
	push	acc
	mov	a,#(_TX_BUFF >> 8)
	push	acc
	mov	a,#0x40
	push	acc
	lcall	_sprintf
	mov	a,sp
	add	a,#0xf8
	mov	sp,a
;	C:\UBC\SECOND YEAR\ELEC 291\Project 2\ELEC291Project2\EFM8\Robot\main.c:339: sendstr1(TX_BUFF);
	mov	dptr,#_TX_BUFF
	mov	b,#0x40
	lcall	_sendstr1
;	C:\UBC\SECOND YEAR\ELEC 291\Project 2\ELEC291Project2\EFM8\Robot\main.c:340: waitms_or_RI1(500);
	mov	dptr,#0x01F4
	ljmp	_waitms_or_RI1
;------------------------------------------------------------
;Allocation info for local variables in function 'main'
;------------------------------------------------------------
;freq                      Allocated with name '_main_freq_1_121'
;------------------------------------------------------------
;	C:\UBC\SECOND YEAR\ELEC 291\Project 2\ELEC291Project2\EFM8\Robot\main.c:343: void main (void)
;	-----------------------------------------
;	 function main
;	-----------------------------------------
_main:
;	C:\UBC\SECOND YEAR\ELEC 291\Project 2\ELEC291Project2\EFM8\Robot\main.c:346: TIMER0_Init();
	lcall	_TIMER0_Init
;	C:\UBC\SECOND YEAR\ELEC 291\Project 2\ELEC291Project2\EFM8\Robot\main.c:347: Serial_Init();
	lcall	_Serial_Init
;	C:\UBC\SECOND YEAR\ELEC 291\Project 2\ELEC291Project2\EFM8\Robot\main.c:348: UART1_Init(9600);
	mov	dptr,#0x2580
	clr	a
	mov	b,a
	lcall	_UART1_Init
;	C:\UBC\SECOND YEAR\ELEC 291\Project 2\ELEC291Project2\EFM8\Robot\main.c:349: JDYInit();
	lcall	_JDYInit
;	C:\UBC\SECOND YEAR\ELEC 291\Project 2\ELEC291Project2\EFM8\Robot\main.c:359: while(1){
L024002?:
;	C:\UBC\SECOND YEAR\ELEC 291\Project 2\ELEC291Project2\EFM8\Robot\main.c:361: RXData();
	lcall	_RXData
;	C:\UBC\SECOND YEAR\ELEC 291\Project 2\ELEC291Project2\EFM8\Robot\main.c:362: SBUF1 = 0;
	mov	_SBUF1,#0x00
;	C:\UBC\SECOND YEAR\ELEC 291\Project 2\ELEC291Project2\EFM8\Robot\main.c:364: inductance++;
	mov	a,#0x01
	add	a,_inductance
	mov	_inductance,a
	clr	a
	addc	a,(_inductance + 1)
	mov	(_inductance + 1),a
	sjmp	L024002?
	rseg R_CSEG

	rseg R_XINIT

	rseg R_CONST
__str_0:
	db 0x1B
	db '[2J'
	db 0x00
__str_1:
	db 'Command: %s'
	db 0x00
__str_2:
	db 'Response: %s'
	db 0x0D
	db 0x0A
	db 0x00
__str_3:
	db 'AT+DVIDAFAF'
	db 0x0D
	db 0x0A
	db 0x00
__str_4:
	db 'AT+RFIDFFBB'
	db 0x0D
	db 0x0A
	db 0x00
__str_5:
	db 'AT+VER'
	db 0x0D
	db 0x0A
	db 0x00
__str_6:
	db 'AT+BAUD'
	db 0x0D
	db 0x0A
	db 0x00
__str_7:
	db 'AT+RFID'
	db 0x0D
	db 0x0A
	db 0x00
__str_8:
	db 'AT+DVID'
	db 0x0D
	db 0x0A
	db 0x00
__str_9:
	db 'AT+RFC'
	db 0x0D
	db 0x0A
	db 0x00
__str_10:
	db 'AT+POWE'
	db 0x0D
	db 0x0A
	db 0x00
__str_11:
	db 'AT+CLSS'
	db 0x0D
	db 0x0A
	db 0x00
__str_12:
	db '%.3f'
	db 0x00
__str_13:
	db '%s '
	db 0x0D
	db 0x0A
	db 0x00
__str_14:
	db '%s'
	db 0x0D
	db 0x0A
	db 0x00
__str_15:
	db '%d'
	db 0x00

	CSEG

end

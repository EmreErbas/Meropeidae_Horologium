#ifndef NIXIE_H_
#define NIXIE_H_

#include "main.h"

#ifdef superUserMode
#include "usbd_cdc_if.h"
static USBD_HandleTypeDef *superUserBus;
static uint8_t BOOL_PORT_OPEN = 0;
#endif  //superUserMode

static I2C_HandleTypeDef NixieBus;
static uint8_t I2C_Buffer[255];


/*******************************************************************************
 *******************************************************************************
							FUNCTIONS PROTOTYPES
 *******************************************************************************
 *******************************************************************************/

static inline uint8_t ScanNixieNodes(uint8_t* ID_Buffer, uint8_t MaxNode);



/*******************************************************************************
 *******************************************************************************
								DEFINITIONS
 *******************************************************************************
 *******************************************************************************/
#define CommandRegisterWriteLock 				0xFE
#define CommandRegister 						0xFD
#define IDRegister 								0xFC

// FDh Command Register
#define PWMRegister								0x00 // Page-0
#define ScalingRegister							0x01 // Page-1
#define FunctionRegister						0x02 // Page-2

// FEh Command Register Write Lock (Read/Write)
/* To select the PG0~PG2, need to unlock this register first, with the purpose
 * to avoid mis-operation of this register. When FEh is written with 0xC5, FDh
 * is allowed to modify once, after the FDh is modified the FEh will reset to be
 * 0x00 at once. */
#define CommandRegisterWriteUnlock				0xC5

// Function Register
#define FR_ConfigurationRegister				0x00 // Configure the Op mode
#define FR_GlobalCurrentControlRegister			0x01 // Set the global current
#define FR_PullDownUpResistorSelectionRegister	0x02 // Set the pull-down
								// resistor for SWx and pull up resistor for CSy
#define FR_OpenShortRegister_First				0x03 // Store the open-short info
#define FR_OpenShortRegister_Last				0x23 //
#define FR_TemperatureStatus					0x24 // Store the temp of the IC
#define FR_SpreadSpectrumRegister				0x25 // Spread spectrum
													 // funcion enable
#define FR_ResetRegister						0x2F // Reset all register to
 	 	 	 	 	 	 	 	 	 	 	 	 	 // POR state

// Page 0 (PG0, FDh = 0x00): PWM Register
#define PG0_PWMRegister_First					0x01
#define PG0_PWMRegister_Last					0xC6 // C6 = 198 = 18 x 11
// Each dot has a byte to modulate the PWM duty in 256 steps.


// Page 1 (PG1, FDh = 0x01): Scaling Register
#define PG1_ScalingRegister_First				0x01
#define PG1_ScalingRegister_Last				0xC6 // C6 = 198 = 18 x 11
// Scaling register control the DC output current of each dot. Each dot has a
// byte to modulate the scaling in 256 steps
// The value of the Scaling Register decides the peak current of each LED


// Page 2 (PG2, FDh = 0x02): Function Register

//		00h Configuration Register
typedef enum // D0 | Default 0
{
	SoftwareShutdown	= 0U,
	NormalOperation		= 1U
} CR_SSDTypeDef;

typedef enum // D3 | Default 1
{
	Logic_1V4_0V4		= 0U,
	Logic_2V4_0V6		= 1U
} CR_LGCTypeDef;

typedef enum // D2:D1 | Default 00
{
	DisableOpenShortDetection	= 0U, // <--.
	EnableOpenDetection			= 1U, //    |Both the same
	EnableShortDetection		= 2U, //    |
	DisableDetection			= 3U  // <--'
} CR_OSDETypeDef;

typedef enum // D2:D1 | Default = 0000
{
	SW1_SW11 = 0U, // 1/11                          0000
	SW1_SW10 = 1U, // 1/10, SW11 no-active          0001
	SW1_SW9  = 2U, // 1/9, SW10~SW11 no-active      0010
	SW1_SW8  = 3U, // 1/8, SW9~SW11 no-active       0011
	SW1_SW7  = 4U, // 1/7, SW8~SW11 no-active       0100
	SW1_SW6  = 5U, // 1/6, SW7~SW11 no-active       0101
	SW1_SW5  = 6U, // 1/5, SW6~SW11 no-active       0110
	SW1_SW4  = 7U, // 1/4, SW5~SW11 no-active       0111
	SW1_SW3  = 8U, // 1/3, SW4~SW11 no-active       1000
	SW1_SW2  = 9U, // 1/2, SW3~SW11 no-active       1001
	SWnone   = 10U // All CSy work as current sinks only,
				   // no scan Others    			1010
} CR_SWSTypeDef;

//		01h Global Current Control Register
// The Global Current Control Register modulates all CSy (y=1~18) DC current
// which is noted as IOUT in 256 steps.
//
// Default = 0000 0000
// !!! TODO: You need to change this value to see any light on the LEDs

//		 02h Pull Down/Up Resistor Selection Register

// Default = 0011 0011
// TODO: Default looks good. Then, I didn't add all the parameters to here
//       Maybe later, I should add PHC, SWPDR, and CSPUR bits to the library


#define Nixie_ID_LeftLeft					70  // 0x46
#define Nixie_ID_LeftRight					94  // 0x5E
#define Nixie_ID_RightLeft					64  // 0x40
#define Nixie_ID_RightRight					88	// 0x58




/*******************************************************************************
 *******************************************************************************
							INTEGRATION FUNCTIONS
 *******************************************************************************
 *******************************************************************************/

static inline void NixiBusInit( I2C_HandleTypeDef I2C_Handle,
								USBD_HandleTypeDef *pdev)
{
	NixieBus = I2C_Handle;



#ifdef superUserMode
	superUserBus = pdev;
#endif  //superUserMode

	I2C_Buffer[0] = CommandRegisterWriteLock;
	I2C_Buffer[1] = CommandRegisterWriteUnlock;
	HAL_I2C_Master_Transmit(&NixieBus, Nixie_ID_LeftLeft, I2C_Buffer, 2, 1000);
	HAL_I2C_Master_Transmit(&NixieBus, Nixie_ID_LeftRight, I2C_Buffer, 2, 1000);
	HAL_I2C_Master_Transmit(&NixieBus, Nixie_ID_RightLeft, I2C_Buffer, 2, 1000);
	HAL_I2C_Master_Transmit(&NixieBus, Nixie_ID_RightRight, I2C_Buffer, 2, 1000);

	I2C_Buffer[0] = CommandRegister;
	I2C_Buffer[1] = PWMRegister;
	HAL_I2C_Master_Transmit(&NixieBus, Nixie_ID_LeftLeft, I2C_Buffer, 2, 1000);
	HAL_I2C_Master_Transmit(&NixieBus, Nixie_ID_LeftRight, I2C_Buffer, 2, 1000);
	HAL_I2C_Master_Transmit(&NixieBus, Nixie_ID_RightLeft, I2C_Buffer, 2, 1000);
	HAL_I2C_Master_Transmit(&NixieBus, Nixie_ID_RightRight, I2C_Buffer, 2, 1000);

	for(uint8_t loop = 1; loop < 0xC7 ; loop ++)
	{
		I2C_Buffer[0] = loop;
		I2C_Buffer[1] = 0x00;
		HAL_I2C_Master_Transmit(&NixieBus, Nixie_ID_LeftLeft, I2C_Buffer, 2, 1000);
		HAL_I2C_Master_Transmit(&NixieBus, Nixie_ID_LeftRight, I2C_Buffer, 2, 1000);
		HAL_I2C_Master_Transmit(&NixieBus, Nixie_ID_RightLeft, I2C_Buffer, 2, 1000);
		HAL_I2C_Master_Transmit(&NixieBus, Nixie_ID_RightRight, I2C_Buffer, 2, 1000);
	}
//
//	I2C_Buffer[0] = PG0_PWMRegister_First;
//	HAL_I2C_Master_Transmit(&NixieBus, Nixie_ID_LeftLeft, I2C_Buffer, 1, 1000);
//	HAL_I2C_Master_Receive(&NixieBus, Nixie_ID_LeftLeft, I2C_Buffer, 10, 1000);




	I2C_Buffer[0] = CommandRegisterWriteLock;
	I2C_Buffer[1] = CommandRegisterWriteUnlock;
	HAL_I2C_Master_Transmit(&NixieBus, Nixie_ID_LeftLeft, I2C_Buffer, 2, 1000);
	HAL_I2C_Master_Transmit(&NixieBus, Nixie_ID_LeftRight, I2C_Buffer, 2, 1000);
	HAL_I2C_Master_Transmit(&NixieBus, Nixie_ID_RightLeft, I2C_Buffer, 2, 1000);
	HAL_I2C_Master_Transmit(&NixieBus, Nixie_ID_RightRight, I2C_Buffer, 2, 1000);
	I2C_Buffer[0] = CommandRegister;
	I2C_Buffer[1] = ScalingRegister;
	HAL_I2C_Master_Transmit(&NixieBus, Nixie_ID_LeftLeft, I2C_Buffer, 2, 1000);
	HAL_I2C_Master_Transmit(&NixieBus, Nixie_ID_LeftRight, I2C_Buffer, 2, 1000);
	HAL_I2C_Master_Transmit(&NixieBus, Nixie_ID_RightLeft, I2C_Buffer, 2, 1000);
	HAL_I2C_Master_Transmit(&NixieBus, Nixie_ID_RightRight, I2C_Buffer, 2, 1000);

	for(uint8_t loop = 1; loop < 0xC7 ; loop ++)
	{
		I2C_Buffer[0] = loop;
		I2C_Buffer[1] = 0xFF;
		HAL_I2C_Master_Transmit(&NixieBus, Nixie_ID_LeftLeft, I2C_Buffer, 2, 1000);
		HAL_I2C_Master_Transmit(&NixieBus, Nixie_ID_LeftRight, I2C_Buffer, 2, 1000);
		HAL_I2C_Master_Transmit(&NixieBus, Nixie_ID_RightLeft, I2C_Buffer, 2, 1000);
		HAL_I2C_Master_Transmit(&NixieBus, Nixie_ID_RightRight, I2C_Buffer, 2, 1000);
	}

//	I2C_Buffer[0] = PG1_ScalingRegister_First;
//	HAL_I2C_Master_Transmit(&NixieBus, Nixie_ID_LeftLeft, I2C_Buffer, 1, 1000);
//	HAL_I2C_Master_Receive(&NixieBus, Nixie_ID_LeftLeft, I2C_Buffer, 10, 1000);




	I2C_Buffer[0] = CommandRegisterWriteLock;
	I2C_Buffer[1] = CommandRegisterWriteUnlock;
	HAL_I2C_Master_Transmit(&NixieBus, Nixie_ID_LeftLeft, I2C_Buffer, 2, 1000);
	HAL_I2C_Master_Transmit(&NixieBus, Nixie_ID_LeftRight, I2C_Buffer, 2, 1000);
	HAL_I2C_Master_Transmit(&NixieBus, Nixie_ID_RightLeft, I2C_Buffer, 2, 1000);
	HAL_I2C_Master_Transmit(&NixieBus, Nixie_ID_RightRight, I2C_Buffer, 2, 1000);
	I2C_Buffer[0] = CommandRegister;
	I2C_Buffer[1] = FunctionRegister;
	HAL_I2C_Master_Transmit(&NixieBus, Nixie_ID_LeftLeft, I2C_Buffer, 2, 1000);
	HAL_I2C_Master_Transmit(&NixieBus, Nixie_ID_LeftRight, I2C_Buffer, 2, 1000);
	HAL_I2C_Master_Transmit(&NixieBus, Nixie_ID_RightLeft, I2C_Buffer, 2, 1000);
	HAL_I2C_Master_Transmit(&NixieBus, Nixie_ID_RightRight, I2C_Buffer, 2, 1000);





	I2C_Buffer[0] = FR_PullDownUpResistorSelectionRegister;
	I2C_Buffer[1] = 0x70;
	HAL_I2C_Master_Transmit(&NixieBus, Nixie_ID_LeftLeft, I2C_Buffer, 2, 1000);
	HAL_I2C_Master_Transmit(&NixieBus, Nixie_ID_LeftRight, I2C_Buffer, 2, 1000);
	HAL_I2C_Master_Transmit(&NixieBus, Nixie_ID_RightLeft, I2C_Buffer, 2, 1000);
	HAL_I2C_Master_Transmit(&NixieBus, Nixie_ID_RightRight, I2C_Buffer, 2, 1000);

//	I2C_Buffer[0] = FR_PullDownUpResistorSelectionRegister;
//	HAL_I2C_Master_Transmit(&NixieBus, Nixie_ID_LeftLeft, I2C_Buffer, 1, 1000);
//	HAL_I2C_Master_Receive(&NixieBus, Nixie_ID_LeftLeft, I2C_Buffer, 1, 1000);




	I2C_Buffer[0] = FR_GlobalCurrentControlRegister;
	I2C_Buffer[1] = 0xFF;
	HAL_I2C_Master_Transmit(&NixieBus, Nixie_ID_LeftLeft, I2C_Buffer, 2, 1000);
	HAL_I2C_Master_Transmit(&NixieBus, Nixie_ID_LeftRight, I2C_Buffer, 2, 1000);
	HAL_I2C_Master_Transmit(&NixieBus, Nixie_ID_RightLeft, I2C_Buffer, 2, 1000);
	HAL_I2C_Master_Transmit(&NixieBus, Nixie_ID_RightRight, I2C_Buffer, 2, 1000);

//	I2C_Buffer[0] = FR_GlobalCurrentControlRegister;
//	HAL_I2C_Master_Transmit(&NixieBus, Nixie_ID_LeftLeft, I2C_Buffer, 1, 1000);
//	HAL_I2C_Master_Receive(&NixieBus, Nixie_ID_LeftLeft, I2C_Buffer, 1, 1000);




	I2C_Buffer[0] = FR_ConfigurationRegister;
	I2C_Buffer[1] = 0x01;
	HAL_I2C_Master_Transmit(&NixieBus, Nixie_ID_LeftLeft, I2C_Buffer, 2, 1000);
	HAL_I2C_Master_Transmit(&NixieBus, Nixie_ID_LeftRight, I2C_Buffer, 2, 1000);
	HAL_I2C_Master_Transmit(&NixieBus, Nixie_ID_RightLeft, I2C_Buffer, 2, 1000);
	HAL_I2C_Master_Transmit(&NixieBus, Nixie_ID_RightRight, I2C_Buffer, 2, 1000);

//	I2C_Buffer[0] = FR_ConfigurationRegister;
//	HAL_I2C_Master_Transmit(&NixieBus, Nixie_ID_LeftLeft, I2C_Buffer, 1, 1000);
//	HAL_I2C_Master_Receive(&NixieBus, Nixie_ID_LeftLeft, I2C_Buffer, 1, 1000);



	HAL_Delay(100);
}


#ifdef superUserMode

static inline void superUserRunForever(uint8_t* CMD_Buffer, uint8_t *CMD_Len)
{
	if(superUserBus->ep0_data_len && !BOOL_PORT_OPEN)
	{
		BOOL_PORT_OPEN = 1;

		CDC_Transmit_FS((uint8_t *)" _  _   ____   _  _   ____   ____ \n", 36);
		CDC_Transmit_FS((uint8_t *)"( \\( ) (_  _) ( \\/ ) (_  _) ( ___)\n", 36);
		CDC_Transmit_FS((uint8_t *)" )  (   _)(_   )  (   _)(_   )__) \n", 36);
		CDC_Transmit_FS((uint8_t *)"(_)\\_) (____) (_/\\_) (____) (____)v0.1\n",41);

		CDC_Transmit_FS((uint8_t *)"\n$superUser:", 12);


	}
	else if(!(superUserBus->ep0_data_len) && BOOL_PORT_OPEN)
	{
		BOOL_PORT_OPEN = 0;
	}
	if(*CMD_Len != 0)
	{
		if( (CMD_Buffer[0] == 'l') &&
			(CMD_Buffer[1] == 's') &&
			(CMD_Buffer[2] == 'h') &&
			(CMD_Buffer[3] == 'w') )
		{
			CDC_Transmit_FS((uint8_t *)"lshw\n", 5);
			uint8_t ID_Buffer[16];
			ScanNixieNodes(ID_Buffer, 16);
		}
		*CMD_Len = 0;
	}

}

#endif  //superUserMode


/*******************************************************************************
 *******************************************************************************
							HIGH-LEVEL FUNCTIONS
 *******************************************************************************
 *******************************************************************************/



/*******************************************************************************
 *******************************************************************************
							LOW-LEVEL FUNCTIONS
 *******************************************************************************
 *******************************************************************************/


/**    ---	IS31FL3743A ---
 *
 * The IS31FL3743A is a general purpose 18×n (n=1~11) LED Matrix programmed via
 * 1MHz I2C compatible interface. Each LED can be dimmed individually with 8-bit
 * PWM data and 8-bit DC scaling data which allowing 256 steps of linear PWM
 * dimming and 256 steps of DC current adjustable level.
 *
 * 			FEATURES
 *	• Supply voltage range: 2.7V to 5.5V
 *	• 18 current sinks
 *	• Support 18×n (n=1~11) LED matrix configurations • Individual 256 PWM
 *	  control steps
 *	• Individual 256 DC current steps
 *	• Global 256 DC current steps
 *	• SDB rising edge reset I2C module
 *	• Programmable H/L logic: 1.4V/0.4V, 2.4V/0.6V
 *	• 24kHz PWM frequency
 *	• 1MHz I2C-compatible interface
 *	• State lookup registers
 *	• Individual open and short error detect function
 *	• 180 degree phase delay operation to reduce power noise
 *	• De-Ghost
 *	• Cascade for synchronization of chips • UQFN-40 (5mm×5mm) package
 */

/**    --	IS31FL3743A | I2C INTERFACE --
 *
 * IS31FL3743A uses a serial bus, which conforms to the I2C protocol, to control
 * the chip’s functions with two wires: SCL and SDA. The IS31FL3743A has a 7-bit
 * slave address (A7:A1), followed by the R/W bit, A0. Set A0 to “0” for a write
 * command and set A0 to “1” for a read command. The value of bits A1 and A2 are
 * decided by the connection of the ADDRx pin.
 *
 *             +=======+=======+=======+=======+=======+=====+
 *             | ADDR1 | ADDR2 | A7:A5 | A4:A3 | A2:A1 | A0  |
 *             +=======+=======+=======+=======+=======+=====+
 *             | GND   | GND   |       | 00    | 00    |     |
 *             +-------+-------+       +-------+-------+     +
 *             | GND   | SCL   |       | 00    | 01    |     |
 *             +-------+-------+       +-------+-------+     +
 *             | GND   | SDA   |       | 00    | 10    |     |
 *             +-------+-------+       +-------+-------+     +
 *             | GND   | VCC   |       | 00    | 11    |     |
 *             +-------+-------+       +-------+-------+     +
 *             | SCL   | GND   |       | 01    | 00    |     |
 *             +-------+-------+       +-------+-------+     +
 *             | SCL   | SCL   |       | 01    | 01    |     |
 *             +-------+-------+       +-------+-------+     +
 *             | SCL   | SDA   |       | 01    | 10    |     |
 *             +-------+-------+       +-------+-------+     +
 *             | SCL   | VCC   | 010   | 01    | 11    | 0/1 |
 *             +-------+-------+       +-------+-------+     +
 *             | SDA   | GND   |       | 10    | 00    |     |
 *             +-------+-------+       +-------+-------+     +
 *             | SDA   | SCL   |       | 10    | 01    |     |
 *             +-------+-------+       +-------+-------+     +
 *             | SDA   | SDA   |       | 10    | 10    |     |
 *             +-------+-------+       +-------+-------+     +
 *             | SDA   | VCC   |       | 10    | 11    |     |
 *             +-------+-------+       +-------+-------+     +
 *             | VCC   | GND   |       | 11    | 00    |     |
 *             +-------+-------+       +-------+-------+     +
 *             | VCC   | SCL   |       | 11    | 01    |     |
 *             +-------+-------+       +-------+-------+     +
 *             | VCC   | SDA   |       | 11    | 10    |     |
 *             +-------+-------+       +-------+-------+     +
 *             | VCC   | VCC   |       | 11    | 11    |     |
 *             +-------+-------+-------+-------+-------+-----+
 *
 * The SCL line is uni-directional. The SDA line is bi- directional (open-drain)
 * with a pull-up resistor (typically 400kHz I2C with 4.7kΩ, 1MHz I2C with 2kΩ).
 * The maximum clock frequency specified by the I2C standard is 1MHz. In this
 * discussion, the master is the microcontroller and the slave is the
 * IS31FL3743A.
 * The timing diagram for the I2C is shown in Figure 4 of the datasheet page8.
 * The SDA is latched in on the stable high level of the SCL. When there is no
 * interface activity, the SDA line should be held high.
 * The “START” signal is generated by lowering the SDA signal while the SCL
 * signal is high. The start signal will alert all devices attached to the I2C
 * bus to check the incoming address against their own chip address.
 *
 *  Addr   Name         Table   R/W          Default
 * ----- ------------- ------- ------------ -----------
 *  FEh   Command Reg   4       R/W          0000 0000
 *  FDh   Command Reg   3       W            xxxx xxxx
 *  FCh   ID Register   -       Slave Addr
 */


static inline uint8_t ScanNixieNodes(uint8_t* ID_Buffer, uint8_t MaxNode)
{
	uint8_t buf_counter = 0;
	for(uint8_t address = 0; address < 254; address += 2)
	{
		if(HAL_I2C_Master_Transmit(&NixieBus, address,
								  (uint8_t *) IDRegister, 1, 100) == HAL_OK)
		{
			ID_Buffer[buf_counter] = address;
			buf_counter ++;
			if(buf_counter >= MaxNode)
			{
				address = 254; // Break the loop
			}
		}
	}
#ifdef superUserMode
	char USB_Buffer[512];
	uint16_t size = 0;

	size = sprintf(USB_Buffer,
			"\nNodes were scanned in the I2C network. "
			"Max detectable node quantity is %d", MaxNode);

	size += sprintf(USB_Buffer + strlen(USB_Buffer),
			"\n%d nodes detected\n", buf_counter);

	if(buf_counter != 0)
	{
		for(uint8_t loop = 0 ; loop < buf_counter; loop ++)
		{
			size += sprintf(USB_Buffer + strlen(USB_Buffer),
					"Node-%d : [0x%02X]\n", loop, ID_Buffer[loop]);
		}
	}
	size += sprintf(USB_Buffer + strlen(USB_Buffer),
			"$superUser:");

	CDC_Transmit_FS((uint8_t *)USB_Buffer, size);
#endif

	return buf_counter;
}





#endif /* NIXIE_H_ */
// This library is written by Emre Erbas
// emre.erbas214@gmail.com
// ------------------------------ END OF FILE -------------------------------


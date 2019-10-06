/*
 * Original code built to Raspberry Pi 3+ and Flir Lepton 3

*******************************************
October 2019
Made by Alexandre Gustavo Burche
*/


#include "LEPTON_SYS.h"
#include "raspi_I2C.h"


#define NUM 1


LEP_UINT8   deviceAddress = 0x2A;
LEP_UINT16  regPowerOnOff = 0x0000;
LEP_UINT16  regStatus = 0x0002;
LEP_UINT16  regComID = 0x0004;
LEP_UINT16  regDataLenght = 0x0006;
LEP_UINT16  regData0 = 0x0008;
LEP_UINT16  readDataPtr[NUM];
LEP_UINT16  writeDataPtr[NUM];
LEP_UINT16  wordsToRead = NUM;
LEP_UINT16  wordsToWrite = NUM;
LEP_UINT16  numWordsRead;
LEP_UINT16  numWordsWritten;
LEP_UINT16  status;
LEP_UINT16	commandID;
LEP_UINT16  PortDescriptor;

LEP_CAMERA_PORT_DESC_T _port;
LEP_SYS_STATUS_E sysStatus;

//LEP_UINT16  writeDataPtr[NUM] = ;
//LEP_UINT16  commandID = ;


/*
    never used...  
    just datasheet reference
*/
void LeptonTransmission(writeDataPtr)
{
	//1. Polling the status register until camera is ready for a new command (BUSY bit clear)
	while(DEV_I2C_MasterReadData(1, deviceAddress, regStatus, readDataPtr, wordsToRead, &numWordsRead, &status) != 0);
	//2. Polling the SYS FFC Status command (see 4.5.18) to verify the system is ready to process a new command (System Ready returned).
	while(sysStatus == LEP_SYS_STATUS_BUSY)
	{
		LEP_GetSysFFCStatus(&_port,&sysStatus);
	}
	//3. Writing data to send to the camera if required into the DATA Registers or block Data buffer.
	DEV_I2C_MasterWriteData(1, deviceAddress, regData0, writeDataPtr, wordsToWrite, &numWordsWritten, &status);
	//4. Writing the number of data words written (16-bit data words) to the Data Length Register.
	DEV_I2C_MasterWriteData(1, deviceAddress, regDataLenght, NUM, wordsToWrite, &numWordsWritten, &status);
	//5. Writing the desired command ID to the Command Register.
	DEV_I2C_MasterWriteData(1, deviceAddress, regComID, commandID, wordsToWrite, &numWordsWritten, &status);
	//6. Polling the Status Register to determine when the command is completed (busy bit cleared).
	DEV_I2C_MasterReadData(1, deviceAddress, regStatus, readDataPtr, wordsToRead, &numWordsRead, &status);
	while((readDataPtr & 0x0001) != 0x0000)
	{
		DEV_I2C_MasterReadData(1, deviceAddress, regStatus, readDataPtr, wordsToRead, &numWordsRead, &status);
	}
	//7. Read the success code from the status register.
	DEV_I2C_MasterReadData(1, deviceAddress, regStatus, readDataPtr, wordsToRead, &numWordsRead, &status);
	//8. Retrieve any responses as required from the Data registers or block Data buffer.
	DEV_I2C_MasterReadData(1, deviceAddress, regData0, readDataPtr, wordsToRead, &numWordsRead, &status);
}

/*  
    Function to read DATA0 register
    Return: data read
    Inputs: 
        -
        -
*/
LEP_RESULT LeptonGet()
{
    //Read the STATUS register (register address 0x0002) bit 0
    DEV_I2C_MasterReadData(1, deviceAddress, regStatus, readDataPtr, wordsToRead, &numWordsRead, &status);
    while((readDataPtr & 0x0001) != 0x0000)
    {
        DEV_I2C_MasterReadData(1, deviceAddress, regStatus, readDataPtr, wordsToRead, &numWordsRead, &status);
    }
    DEV_I2C_MasterWriteData(1, deviceAddress, regDataLenght, NUM, wordsToWrite, &numWordsWritten, &status);
    DEV_I2C_MasterWriteData(1, deviceAddress, regComID, commandID, wordsToWrite, &numWordsWritten, &status);
    //Read the STATUS register (register address 0x0002) bit 0
    DEV_I2C_MasterReadData(1, deviceAddress, regStatus, readDataPtr, wordsToRead, &numWordsRead, &status);
    while((readDataPtr & 0x0001) != 0x0000)
    {
        DEV_I2C_MasterReadData(1, deviceAddress, regStatus, readDataPtr, wordsToRead, &numWordsRead, &status);
    }
    //Possivelmente na linha abaixo, devo fornecer o resultado da leitura a uma função de tratativa de erro
    //Inserir parte do código para tratamento de erro... se resultado for OK sigo adiante, se for um erro processo o erro e saio da função.
    DEV_I2C_MasterReadData(1, deviceAddress, regData0, readDataPtr, wordsToRead, &numWordsRead, &status);

    return readDataPtr;
}

/*  
    Function to write Command ID register
    Return: none
    Inputs: 
        -
        -
*/
void LeptonSet()
{
    //Read the STATUS register (register address 0x0002) bit 0
    DEV_I2C_MasterReadData(1, deviceAddress, regStatus, readDataPtr, wordsToRead, &numWordsRead, &status);
    while((readDataPtr & 0x0001) != 0x0000)
    {
        DEV_I2C_MasterReadData(1, deviceAddress, regStatus, readDataPtr, wordsToRead, &numWordsRead, &status);
    }
    DEV_I2C_MasterWriteData(1, deviceAddress, regData0, writeDataPtr, wordsToWrite, &numWordsWritten, &status);
    DEV_I2C_MasterWriteData(1, deviceAddress, regDataLenght, NUM, wordsToWrite, &numWordsWritten, &status);
    DEV_I2C_MasterWriteData(1, deviceAddress, regComID, commandID, wordsToWrite, &numWordsWritten, &status);
    //Read the STATUS register (register address 0x0002) bit 0
    DEV_I2C_MasterReadData(1, deviceAddress, regStatus, readDataPtr, wordsToRead, &numWordsRead, &status);
    while((readDataPtr & 0x0001) != 0x0000)
    {
        DEV_I2C_MasterReadData(1, deviceAddress, regStatus, readDataPtr, wordsToRead, &numWordsRead, &status);
    }
    //Possivelmente na linha abaixo, devo fornecer o resultado da leitura a uma função de tratativa de erro
    //Inserir parte do código para tratamento de erro... se resultado for OK sigo adiante, se for um erro processo o erro e saio da função.
}

/*  
    Function to run a command
    Return: none
    Inputs: 
        -
        -
*/
void LeptonRun()
{
    //Read the STATUS register (register address 0x0002) bit 0
    DEV_I2C_MasterReadData(1, deviceAddress, regStatus, readDataPtr, wordsToRead, &numWordsRead, &status);
    while((readDataPtr & 0x0001) != 0x0000)
    {
        DEV_I2C_MasterReadData(1, deviceAddress, regStatus, readDataPtr, wordsToRead, &numWordsRead, &status);
    }
    DEV_I2C_MasterWriteData(1, deviceAddress, regComID, commandID, wordsToWrite, &numWordsWritten, &status);
    //Possivelmente na linha abaixo, devo fornecer o resultado da leitura a uma função de tratativa de erro
    //Read the STATUS register (register address 0x0002) bit 0
    DEV_I2C_MasterReadData(1, deviceAddress, regStatus, readDataPtr, wordsToRead, &numWordsRead, &status);
    while((readDataPtr & 0x0001) != 0x0000)
    {
        DEV_I2C_MasterReadData(1, deviceAddress, regStatus, readDataPtr, wordsToRead, &numWordsRead, &status);
    }
    //Possivelmente na linha abaixo, devo fornecer o resultado da leitura a uma função de tratativa de erro
    //Inserir parte do código para tratamento de erro... se resultado for OK sigo adiante, se for um erro processo o erro e saio da função.
}

/*  
    Function to compile startup section
    Return: none
    Inputs: none
*/
void StartUpSequence()
{
	//power to be applied first --> HW
	//clocks applied --> HW
	//then RESET_L de-asserted --> HW (placa de desenvolvimento liga o pino diretamente ao Vcc)
	//wait 5 seconds to allow the camera automatic execution of a flat-field correction (Auto FFC mode)
	wait(5000);
	//Read the STATUS register (register address 0x0002) bit 2
	DEV_I2C_MasterReadData(1, deviceAddress, regStatus, readDataPtr, wordsToRead, &numWordsRead, &status);
	while((readDataPtr & 0x0004) != 0x0000)
	{
		DEV_I2C_MasterReadData(1, deviceAddress, regStatus, readDataPtr, wordsToRead, &numWordsRead, &status);
	}
	//Read the STATUS register (register address 0x0002) bit 0
	DEV_I2C_MasterReadData(1, deviceAddress, regStatus, readDataPtr, wordsToRead, &numWordsRead, &status);
	while((readDataPtr & 0x0001) != 0x0000)
	{
		DEV_I2C_MasterReadData(1, deviceAddress, regStatus, readDataPtr, wordsToRead, &numWordsRead, &status);
	}
	//Poll the SYS FFC Status command (see 4.5.18), to verify the system is ready to process a new command (System Ready returned).
	while(sysStatus == LEP_SYS_STATUS_BUSY)
   {
      LEP_GetSysFFCStatus(&_port,&sysStatus);
   }
}

/*  
    Function to open a comunication port
    Return: result of open port command
    Inputs: none
*/
LEP_RESULT lepton_connect() 
{
    //Possible clocks are: 100Kbaud, 400Kbaud and 1M baud
	LEP_RESULT result = LEP_OpenPort(1, LEP_CCI_TWI, 400, &_port);
	if (result != LEP_OK) printf("LEP_OpenPort(): %i\n", result);
	_connected = true;
	return result;
}

 

int main()
{
    StartUpSequence();
	PortDescriptor = lepton_connect();
	
    
}

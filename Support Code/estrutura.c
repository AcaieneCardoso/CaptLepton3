--------------------------------------------------------------------------------------------

//Declaração da estrutura
typedef struct{
   EnPinsPortA          enPin;                  /*Pin selection.                                                                 */
   EnPinsPwm            enPwm;                  /*PWM output / sensor configuarion.                                              */
   EnPinsInterruption   enInt;                  /*Input interruption configuration.                                              */
   EnPinsDirection      enDir;                  /*Pin direction and configuration (pullup, pulldown, push pull or open drain).   */
   EnPinsStrength       enStr;                  /*Pullup / pulldown strength.                                                    */
   EnPinsThreshold      enThr;                  /*Input threshold.                                                               */
}StrGpioAConfig;


--------------------------------------------------------------------------------------------

//Função que recebe um ponteiro da estrutura
void fnvPinConfigPortA (StrGpioAConfig* strcGpioA)
{
   *(PA0CFG + ((uint8_t)(strcGpioA->enPin))) = ((uint8_t)(strcGpioA->enPwm));    //Quando você trabalha com o ponteiro da estrutura, usa "->" ao invés de ".".
   *(PA0CFG + ((uint8_t)(strcGpioA->enPin))) != ((uint8_t)(strcGpioA->enInt));
   *(PA0CFG + ((uint8_t)(strcGpioA->enPin))) != ((uint8_t)(strcGpioA->enDir));
   *(PA0CFG + ((uint8_t)(strcGpioA->enPin))) != ((uint8_t)(strcGpioA->enStr));
   *(PA0CFG + ((uint8_t)(strcGpioA->enPin))) != ((uint8_t)(strcGpioA->enThr));
}

--------------------------------------------------------------------------------------------

   //Criação de uma variavel do "tipo" da estrutura
   StrGpioAConfig structGpioA;

   //Como a estrutura é alterada
   structGpioA.enPin = PIN_A_CONFIG_HOOD;
   structGpioA.enPwm = PORT_PWM_NOT_AV;
   structGpioA.enInt = PORT_INT_DIS;
   structGpioA.enDir = PORT_INPUT_PULLUP;
   structGpioA.enStr = PORT_STR_100UA;
   structGpioA.enThr = PORT_THRESH_1_65V;
   
   //Como o ponteiro da estrutura é passado como parâmetro de uma função.
   fnvPinConfigPortA (&structGpioA);

--------------------------------------------------------------------------------------------

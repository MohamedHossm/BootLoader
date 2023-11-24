#include "../LIBS/STD_TYPES.h"
#include "../LIBS/STMF103C8_MMAP.h"

#include "../RCC/RCC_Interface.h"
#include "../GPIO/GPIO_Interface.h"
#include "../UART/UART_Interface.h"
#include "../Systick/SYSTICK_Interface.h"
#include "../NVIC/NVIC_Interface.h"
#include "../Flash/FLASH_Interface.h"
#include "../Delay/Delay.h"
#include "../Uart_Service/Uart_Service_Interface.h"
#include "../EXIT/EXTI_Interface.h"
#include "Reset.h"

// Define the pin for checking push button
#define PB_CHECK Pin_A0

// Define the size of options and strings
#define OPTIONS_SIZE 15
#define STRING_SIZE 10

// Constants for car updates
#define CARFANEON 0xAA
#define CARFANEOFF 0xBB
#define CARSPEED 15

// Global arrays for options and car updates
//char Global_u8Options[OPTIONS_SIZE][STRING_SIZE] = { "OP1" };
u8 Global_u8CarUpdate[OPTIONS_SIZE] = { 0x01, CARFANEOFF, 15, CARSPEED };

// Flags for reading data
Bool_t PBreadData = FALSE;
Bool_t UPDATEreadData = FALSE;
Bool_t ERRreadData = FALSE;

/*************************************************/
// Location of Updates
#define BOOT_FLASHMARK 0xAA55
#define BOOT_DDRESSMARK 0x0800F000
/*************************************************/

// Enumeration for application states
APP_StateMach Global_enuAppStates = APP_normal;

/*
 * Function to confirm the update
 */
void Update_voidConfirm(u8 *ptr_u8readData) {
    GPIO_u8GetPinV_ID(PB_CHECK, ptr_u8readData);
}

/*
 * Function to send car updates
 */
void Send_voidCarUpdate() {
    for (u8 index = 0; index < OPTIONS_SIZE; index++) {
        if (Global_u8CarUpdate[index] != 0) {
            UART2_u8SendByteBusyw8(Global_u8CarUpdate[index]);
        } else {
            // Do nothing
        }
    }
}

/*
 * Function to send options
 */
void Send_voidOptions() {
    for (u8 index = 0; index < OPTIONS_SIZE; index++) {
        if (Global_u8CarUpdate[index] != 0) {
            UART2_u8SendByteBusyw8(Global_u8Options[index][1]);
        } else {
            // Do nothing
        }
    }
}

/*
 * Function to send frame request
 */
void SendFrameRequest() {
    UART1_u8SendStringBusyW8("ERR_1_MOTOR_SPEED_V_2");
}

/*
 * Function to send frame request 2
 */
void SendFrameRequest2() {
    UART1_u8SendStringBusyW8("ERR_1_FAN_V_2");
}

/*
 * Function to check and go to reset
 */
void Check_voidGotoReset() {
    if (UPDATEreadData == TRUE && PBreadData == TRUE) {
        Global_enuAppStates = APP_REQ_Update;
    } else {
        // Do nothing
    }

    if (UPDATEreadData == TRUE && ERRreadData == TRUE) {
        Global_enuAppStates = APP_REQ_Update;
    } else {
        // Do nothing
    }
}

/*
 * External interrupt function
 */
void EXIT_FUN() {
    PBreadData = TRUE;
}

int main(void) {
    // Initialization of system, clocks, and peripherals
    RCC_voidInitSystemClock();
    RCC_voidEnablePeriphralCLK(APB2_IOPAEN);
    RCC_voidEnablePeriphralCLK(APB2_IOPBEN);
    RCC_voidEnablePeriphralCLK(APB2_IOPCEN);

    GPIO_u8Init();
    Uart_Service_voidInit();
    GPIO_u8SetPinV_ID(Pin_B1, LOW);
    GPIO_u8SetPinV_ID(Pin_A4, LOW);

    // External interrupt setup
    GPIO_u8SetPinV_ID(PB_CHECK, HIGH);
    NVIC_u8Set_EN_IRQ(INTERRUPT_EXTI0);
    EXTI_u8Set_Inturrupt_latch(EXTI_Line0, EXTI_FAILING);
    EXTI_u8Setter_IRQ(EXTI_Line0, EXIT_FUN);
    EXTI_u8En(EXTI_Line0);

    STK_u8Init();

    // Send initial car updates
    Send_voidCarUpdate();

    while (1) {
        switch (Global_enuAppStates) {
        case APP_normal:
            // Handle flames and check for reset
            App_HandelFlames();
            App_HandelFlames2();
            Check_voidGotoReset();

            // Toggle Pin_A6 for testing
            static u8 data = 1;
            GPIO_u8SetPinV_ID(Pin_A6, data);
            data = !data;
            break;

        case APP_REPORT_ERR1:
            // Send frame request for error 1
            SendFrameRequest();
            ERRreadData = TRUE;
            Global_enuAppStates = APP_normal;
            break;

        case APP_REPORT_ERR2:
            // Send frame request for error 2
            SendFrameRequest2();
            ERRreadData = TRUE;
            Global_enuAppStates = APP_normal;
            break;

        case APP_normal_CHECKPB:
            // Update flag for PB check
            UPDATEreadData = TRUE;
            PBreadData = FALSE;
            GPIO_u8SetPinV_ID(Pin_A4, HIGH);
            Global_enuAppStates = APP_normal;
            break;

        case APP_REPORT_CONF:
            // Send car updates
            Send_voidCarUpdate();
            Global_enuAppStates = APP_normal;
            break;

        case APP_REQ_Update:
            // Check on boot marker and perform reset
            if (*(u16*) BOOT_DDRESSMARK != BOOT_FLASHMARK) {
                FLASH_enWriteData(BOOT_DDRESSMARK, BOOT_FLASHMARK);
            } else {
                // Do nothing
            }
            SoftwareReset();
            break;

        default:
            break;
        }
    }
    return 0;
}

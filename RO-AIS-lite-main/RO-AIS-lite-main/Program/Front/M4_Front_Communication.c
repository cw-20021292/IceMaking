/***********************************************************************************************************************
* Version      : BAS25(STEP_UP)
* File Name    : Remote_Comm.c
* Device(s)    : R5F100MG
* Creation Date: 2015/07/31
* Copyright    : Coway_Electronics Engineering Team (DH,Kim)
* Description  :
***********************************************************************************************************************/
#include    "Macrodriver.h"
#include    "Port_Define.h"
#include    "M4_Front_Communication.h"
#include	"uv_ice_extraction_output.h"

void Front_Communication(void);
void front_rx_communication(void);
void convert_received_data_asc_to_dec(void);
U8 calculate_checksum(void);
void apply_receive_data(U8 *mu8_rx_data);
void front_tx_communication(void);
void make_front_tx_data(void);
void convert_final_asc_data(U8 *mu8_tx_data, U8 mu8_length);
void Uart_ISR2_Front_Panel_Rx(void);
void Uart_ISR2_Front_Panel_Tx ( void );
void front_transmit_error_check(void);
void front_transmit_start(void);
void front_key_transition_check(void);

/*..hui [18-8-9오후 1:10:24] 아스키로 받은 데이터 버퍼..*/
U8 gu8_front_rx_buffer_temp[FRONT_RX_BUFFER_SIZE];

/*..hui [18-8-9오후 1:10:38] 아스키를 10진수로 변환한 최종 데이터 버퍼..*/
U8 gu8_front_rx_buffer[FRONT_RX_BUFFER_SIZE];

U8 gu8_front_tx_buffer_temp[FRONT_TX_BUFFER_SIZE];

U8 gu8_front_tx_buffer[FRONT_TX_BUFFER_SIZE];

U8 gu8_front_rx_receive_cnt;
U8 gu8_front_tx_count;
U8 gu8_front_rx_total_length;
U8 gu8_front_tx_total_length;
BIT F_Front_Rx_Complete;
BIT F_Front_Tx_Request;
U8 gu8_front_tx_retry_cnt;
U8 gu8_tx_error_cnt;

U8 gu8_cs_error_cnt;
U8 gu8_busy_error_cnt;


/***********************************************************************************************************************
* Function Name: System_ini
* Description  :
***********************************************************************************************************************/
void Front_Communication(void)
{
    front_rx_communication();
    front_tx_communication();
}
/***********************************************************************************************************************
* Function Name: System_ini
* Description  :
***********************************************************************************************************************/
void front_rx_communication(void)
{
    U16 mu16_cal_crc = 0;
    U8 mu8_crc_high = 0;
    U8 mu8_crc_low = 0;

    if(F_Front_Rx_Complete == SET)
    {
        mu16_cal_crc = (U16)Rx_CRC_CCITT(gu8_front_rx_buffer, MAIN_CRC_CALC_RANGE);

        mu8_crc_high = (U8)HighByte(mu16_cal_crc);
        mu8_crc_low = (U8)LowByte(mu16_cal_crc);

        if(gu8_front_rx_buffer[MAIN_CRC_HIGH_ROCATION] == mu8_crc_high
           && gu8_front_rx_buffer[MAIN_CRC_LOW_ROCATION] == mu8_crc_low)
        {
            switch( gu8_front_rx_buffer[MAIN_COMMAND_ROCATION] )
            {
                case REQUEST_COMMAND_FRONT_COMM:

                    F_Front_Tx_Request = SET;
                    apply_receive_data(gu8_front_rx_buffer);

                    break;

                case RESPONSE_COMMAND_FRONT_COMM:

                    //

                    break;

                default :

                    break;
            }
        }
        else
        {
            gu8_cs_error_cnt++;
        }

        F_Front_Rx_Complete = CLEAR;
    }
    else{}
}

/***********************************************************************************************************************
* Function Name: System_ini
* Description  :
***********************************************************************************************************************/
void convert_received_data_asc_to_dec(void)
{
#if 0
    gu8_front_rx_buffer[0] = gu8_front_rx_buffer_temp[0];
    gu8_front_rx_buffer[1] = gu8_front_rx_buffer_temp[1];
    gu8_front_rx_buffer[2] = gu8_front_rx_buffer_temp[2];

    gu8_front_rx_buffer[3] = AscToHex(gu8_front_rx_buffer_temp[3], gu8_front_rx_buffer_temp[4]);
    gu8_front_rx_buffer[4] = AscToHex(gu8_front_rx_buffer_temp[5], gu8_front_rx_buffer_temp[6]);
    gu8_front_rx_buffer[5] = AscToHex(gu8_front_rx_buffer_temp[7], gu8_front_rx_buffer_temp[8]);
    gu8_front_rx_buffer[6] = AscToHex(gu8_front_rx_buffer_temp[9], gu8_front_rx_buffer_temp[10]);
    gu8_front_rx_buffer[7] = AscToHex(gu8_front_rx_buffer_temp[11], gu8_front_rx_buffer_temp[12]);
    gu8_front_rx_buffer[8] = AscToHex(gu8_front_rx_buffer_temp[13], gu8_front_rx_buffer_temp[14]);
    gu8_front_rx_buffer[9] = AscToHex(gu8_front_rx_buffer_temp[15], gu8_front_rx_buffer_temp[16]);
    gu8_front_rx_buffer[10] = AscToHex(gu8_front_rx_buffer_temp[17], gu8_front_rx_buffer_temp[18]);
    gu8_front_rx_buffer[11] = AscToHex(gu8_front_rx_buffer_temp[19], gu8_front_rx_buffer_temp[20]);

    gu8_front_rx_buffer[12] = gu8_front_rx_buffer_temp[21];
#endif
}

/***********************************************************************************************************************
* Function Name: System_ini
* Description  :
***********************************************************************************************************************/
U8 calculate_checksum(void)
{
    U8 mu8_temp = 0;
    U8 mu8_cnt = 0;
    U8 mu8_cal_cs = 0;

    for(mu8_temp = 0; mu8_temp < 5; mu8_temp++ )
    {
        mu8_cal_cs += gu8_front_rx_buffer[mu8_temp];
    }

    return mu8_cal_cs;
}

/***********************************************************************************************************************
* Function Name: System_ini
* Description  :
***********************************************************************************************************************/
void apply_receive_data(U8 *mu8_rx_data)
{
    gu8_front_fnd_thousand = mu8_rx_data[3];

    gu8_front_fnd_hundred = mu8_rx_data[4];
    gu8_front_fnd_ten = mu8_rx_data[5];
    gu8_front_fnd_one = mu8_rx_data[6];
    gu8_front_extract_uv_led = mu8_rx_data[7];
    gu8_front_etc_led = mu8_rx_data[8];
    gu8_front_select_led = mu8_rx_data[9];
    gu8_front_temp_led = mu8_rx_data[10];
    gu8_front_setting_led = mu8_rx_data[11];
    gu8_time_wifi_setting_led = mu8_rx_data[12];

    gu8_dimming_set_ice_first = mu8_rx_data[13];
    gu8_dimming_hot_ambient = mu8_rx_data[14];
    gu8_dimming_cold_amount = mu8_rx_data[15];
    gu8_dimming_extract = mu8_rx_data[16];
    gu8_dimming_setting_etc = mu8_rx_data[17];

    gu8_dimming_cont_pot = mu8_rx_data[18];
    gu8_dimming_2cups_1cup = mu8_rx_data[19];
    gu8_dimming_half_cups_colon = mu8_rx_data[20];
    gu8_dimming_Am_Pm = mu8_rx_data[21];
    //gu8_time_setting_led = mu8_rx_data[21];
	
    u8ETCDimmingSel_L = mu8_rx_data[22];
    u8ETCDimmingSel_H = mu8_rx_data[23];

    /*gu8_etc_1 = mu8_rx_data[21];*/
    gu8_dimming_temp = mu8_rx_data[24];
	
    bit_uv_ice_extraction_out = mu8_rx_data[25];
    gu8_dimming_Wifi = mu8_rx_data[26];
	
    gu8_dimming_fnd_2_1 = mu8_rx_data[27];
    gu8_dimming_fnd_4_3 = mu8_rx_data[28];
    gu8_Dimming_seg = mu8_rx_data[29];

    gu8_ota_start = mu8_rx_data[30];
}

/***********************************************************************************************************************
* Function Name: System_ini
* Description  :
***********************************************************************************************************************/
void front_tx_communication(void)
{
    front_transmit_error_check();
    //make_front_tx_data();
    front_transmit_start();
}

/***********************************************************************************************************************
* Function Name: System_ini
* Description  :
***********************************************************************************************************************/
void front_transmit_start(void)
{
    U8 u8Uart2_Busy_Chk;

    if( (U16)((SSR10) & (U16)0x0040) == (U16)0x0040)
    {
        u8Uart2_Busy_Chk = SET;
    }
    else
    {
        u8Uart2_Busy_Chk = CLEAR;
    }

    if(u8Uart2_Busy_Chk == CLEAR)
    {
        if(F_Front_Tx_Request == SET)
        {
            make_front_tx_data();
            TXD2 = gu8_front_tx_buffer[0];
            gu8_front_tx_count = 1;
        }
        else{}
    }
    else
    {
        gu8_busy_error_cnt++;
    }
}




/***********************************************************************************************************************
* Function Name: System_ini
* Description  :
***********************************************************************************************************************/
void front_key_transition_check(void)
{
#if 0
    U8 u8Uart2_Busy_Chk;

    if( (U16)((SSR10) & (U16)0x0040) == (U16)0x0040)
    {
        u8Uart2_Busy_Chk = SET;
    }
    else
    {
        u8Uart2_Busy_Chk = CLEAR;
    }

    if(gu16_Key_Input_Final != gu16_Key_Input_Final_Old)
    {
        gu16_Key_Input_Final_Old = gu16_Key_Input_Final;

        if(u8Uart2_Busy_Chk == CLEAR)
        {
            make_front_tx_data();
            F_Front_Tx_Request = SET;
            front_transmit_start();
        }
        else{}
    }
    else{}
#endif
}







/***********************************************************************************************************************
* Function Name: System_ini
* Description  :
***********************************************************************************************************************/
void front_transmit_error_check(void)
{
    if(F_Front_Tx_Request == CLEAR)
    {
        gu8_front_tx_retry_cnt++;

        if(gu8_front_tx_retry_cnt >= TX_RETRY_COUNT)
        {
            gu8_front_tx_retry_cnt = 0;
            R_UART2_Start();
            gu8_tx_error_cnt++;
        }
        else{}
    }
    else
    {
        gu8_front_tx_retry_cnt = 0;
    }
}

/***********************************************************************************************************************
* Function Name: System_ini
* Description  :
***********************************************************************************************************************/
void make_front_tx_data(void)
{
    U8 mu8_temp = 0;
    U8 mu8_cnt = 0;
    U16 mu16_cal_crc = 0;
    U8 mu8_crc_high = 0;
    U8 mu8_crc_low = 0;
    U8 mu8_buffer[FRONT_TX_BUFFER_SIZE];

    gu8_front_tx_buffer[0] = STX_FRONT_COMM;
    gu8_front_tx_buffer[1] = RESPONSE_COMMAND_FRONT_COMM;
    gu8_front_tx_buffer[2] = FRONT_TO_MAIN_DATA_TOTAL_LENGTH;
    gu8_front_tx_buffer[3] = (U8)(gu16_Key_Input_Final / (U16)256);
    gu8_front_tx_buffer[4] = (U8)(gu16_Key_Input_Final % (U16)256);

    gu8_front_tx_buffer[5] = (U8)Front_FW_Version;
    gu8_front_tx_buffer[6] = (U8)gu16_AD_Result_UV_Ice_Extraction_Current;
	
    mu16_cal_crc = Rx_CRC_CCITT(gu8_front_tx_buffer, FRONT_CRC_CALC_RANGE);

    mu8_crc_high = (U8)HighByte(mu16_cal_crc);
    mu8_crc_low = (U8)LowByte(mu16_cal_crc);

    gu8_front_tx_buffer[7] = mu8_crc_high;
    gu8_front_tx_buffer[8] = mu8_crc_low;

    gu8_front_tx_buffer[9] = ETX_FRONT_COMM;
/*
    mu16_cal_crc = Rx_CRC_CCITT(gu8_front_tx_buffer, FRONT_CRC_CALC_RANGE);

    mu8_crc_high = (U8)HighByte(mu16_cal_crc);
    mu8_crc_low = (U8)LowByte(mu16_cal_crc);

    gu8_front_tx_buffer[6] = mu8_crc_high;
    gu8_front_tx_buffer[7] = mu8_crc_low;

    gu8_front_tx_buffer[8] = ETX_FRONT_COMM;
*/
    /*convert_final_asc_data( gu8_front_tx_buffer_temp, 8 );*/

}


/***********************************************************************************************************************
* Function Name: System_ini
* Description  :
***********************************************************************************************************************/
void convert_final_asc_data(U8 *mu8_tx_data, U8 mu8_length)
{
#if 0
    gu8_front_tx_buffer[0] = mu8_tx_data[0];
    gu8_front_tx_buffer[1] = mu8_tx_data[1];
    gu8_front_tx_buffer[2] = mu8_tx_data[2];

    gu8_front_tx_buffer[3] = (U8)( (HexToAsc(mu8_tx_data[3]) >> 8) & 0xFF );
    gu8_front_tx_buffer[4] = (U8)( (HexToAsc(mu8_tx_data[3])) & 0xFF );

    gu8_front_tx_buffer[5] = (U8)( (HexToAsc(mu8_tx_data[4]) >> 8) & 0xFF );
    gu8_front_tx_buffer[6] = (U8)( (HexToAsc(mu8_tx_data[4])) & 0xFF );

    gu8_front_tx_buffer[7] = (U8)( (HexToAsc(mu8_tx_data[5]) >> 8) & 0xFF );
    gu8_front_tx_buffer[8] = (U8)( (HexToAsc(mu8_tx_data[5])) & 0xFF );

    gu8_front_tx_buffer[9] = (U8)( (HexToAsc(mu8_tx_data[6]) >> 8) & 0xFF );
    gu8_front_tx_buffer[10] = (U8)( (HexToAsc(mu8_tx_data[6])) & 0xFF );

    gu8_front_tx_buffer[11] = mu8_tx_data[7];
#endif
}

/***********************************************************************************************************************
* Function Name: System_ini
* Description  :
***********************************************************************************************************************/
void Uart_ISR2_Front_Panel_Rx(void)
{
    U8 mu8_rx_buffer = RXD2;
    U8 mu8_packet_length = 0;

    if( (F_Front_Rx_Complete == CLEAR) && (F_Front_Tx_Request == CLEAR) )
    {
        gu8_front_rx_buffer[gu8_front_rx_receive_cnt] = mu8_rx_buffer;

        if (gu8_front_rx_buffer[0] == STX_FRONT_COMM)
        {
            switch(gu8_front_rx_receive_cnt)
            {
                case MAIN_COMMAND_ROCATION:

                    if( gu8_front_rx_buffer[MAIN_COMMAND_ROCATION] != REQUEST_COMMAND_FRONT_COMM )
                    {
                        gu8_front_rx_receive_cnt = 0;
                    }
                    else{}

                    break;

                case (MAIN_LENGTH_ROCATION + 1):

                    /*mu8_packet_length = AscToHex(gu8_front_rx_buffer_temp[MAIN_LENGTH_ROCATION], gu8_front_rx_buffer_temp[MAIN_LENGTH_ROCATION + 1]);*/

                    break;

                default :

                    break;
            }

            if(gu8_front_rx_receive_cnt >= (U8)(MAIN_TO_FRONT_DATA_TOTAL_LENGTH - 1))
            {
                if(gu8_front_rx_buffer[gu8_front_rx_receive_cnt] == ETX_FRONT_COMM)
                {
                    gu8_front_rx_receive_cnt = 0;
                    F_Front_Rx_Complete = SET;
                }
                else
                {
                    gu8_front_rx_receive_cnt = 0;
                }
            }
            else
            {
                gu8_front_rx_receive_cnt++;
            }
        }
        else
        {
            gu8_front_rx_receive_cnt = 0;
        }
    }
    else
    {
        gu8_front_rx_receive_cnt = 0;
    }
}



/***********************************************************************************************************************
* Function Name: System_ini
* Description  :
***********************************************************************************************************************/
void Uart_ISR2_Front_Panel_Tx ( void )
{
    if(gu8_front_tx_count < FRONT_TO_MAIN_DATA_TOTAL_LENGTH)
    {
        TXD2 = gu8_front_tx_buffer[gu8_front_tx_count];
        gu8_front_tx_count++;
    }
    else
    {
        F_Front_Tx_Request = CLEAR;
    }
}

/***********************************************************************************************************************
* Function Name: System_ini
* Description  :
***********************************************************************************************************************/




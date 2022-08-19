#include <at89c5131.h>
#include "lcd.h"										//Driver for interfacing lcd 
#include "serial.c"	


void match();
void sets_fun();

char placeholder[6]={0,0,0,0,0,'\0'};			   //string array for saving ascii of input sample


code unsigned char hyphen[]="-";
code unsigned char space[]=" ";
unsigned char disp1[]={0,'\0'};
unsigned char disp2[]={0, 0,'\0'};
code unsigned char disp3[]="Ad - 40";
code unsigned char disp4[]="40 - Ad";
code unsigned char disp5[]="40 - 40";
code unsigned char play1[]="player 1 won";	
code unsigned char play2[]="player 2 won";



unsigned char input = 0;
int i;
int j;
int k;
int l;
int m;
int player1 = 0;
int player2 = 0;
int sets[3][2];
unsigned int set_flag[3] = {0, 0, 0};
int current_set = 0;
unsigned int set_score[2] = {0, 0};
int scores_non[4] = {0, 15, 30, 40};



void main(void)
{
	lcd_init();
	uart_init();
  transmit_string("************tennis***************\r\n");
	transmit_string("**press 1 if player 1 wins point**\r\n");
	transmit_string("**press 2 if player 2 wins point**\r\n");
    msdelay(1000);
	

    for (i = 0; i < 3; i++)
    {
        for (j = 0; j < 2; j++)
        {
            sets[i][j] = 0;
        }
    }
    
    for (l = 0; l < 3; l++)
    {
        while(!set_flag[l])
        {
            if (sets[l][0] < 6 & sets[l][1] < 6)
            {
                match();
            }
            else 
            {
                if (sets[l][0] > sets[l][1])
                {
                    if (sets[l][0] - sets[l][1] > 1)
                    {
                        set_flag[l] = 1;
                        player1++;
                        current_set++;
                    }
                    else
                    {
                        match();
                    }
                }
                else if (sets[l][0] < sets[l][1])
                {
                    if (sets[l][1] - sets[l][0] > 1)
                    {
                        set_flag[l] = 1;
                        player2++;
                        current_set++;
                    }
                    else
                    {
                        match();
                    }
                }
                else
                {
                    match();
                }
            }
        }

        if (player1 == 2)
        {
            lcd_cmd(0xC0);
            lcd_write_string(play1);
            msdelay(5000);
            break;
        }
        else if(player2 == 2)
        {
            lcd_cmd(0xC0);
            lcd_write_string(play2);
            msdelay(5000);
            break;
        }
        else{}
    }
    

}

void sets_fun()
{
    lcd_init();
    lcd_cmd(0x80);
    for (k = 0; k <= current_set; k++)
        {

        	int_to_string(sets[k][0],placeholder);
        	disp1[0] = placeholder[4];
        	lcd_write_string(disp1);

        	lcd_write_string(hyphen);

        	int_to_string(sets[k][1],placeholder);
        	disp1[0] = placeholder[4];
        	lcd_write_string(disp1);

        	lcd_write_string(space);
        }
}

void match()
{
    while(1)
    {
        input = receive_char();
        if (input == '1')
        {
            set_score[0] = set_score[0] + 1;
        }
        else if (input == '2')
        {
            set_score[1] = set_score[1] + 1;
        }
        else{}
        if (set_score[0] <= 3 && set_score[1] <= 3)
        {
            sets_fun();
            lcd_cmd(0xC0);

            int_to_string(scores_non[set_score[0]],placeholder);
            disp2[0] = placeholder[3];
        	disp2[1] = placeholder[4];
        	lcd_write_string(disp2);

        	lcd_write_string(hyphen);

        	int_to_string(scores_non[set_score[1]],placeholder);
            disp2[0] = placeholder[3];
        	disp2[1] = placeholder[4];
        	lcd_write_string(disp2);
        }
        else
        {
            if (set_score[0] > set_score[1])
            {
                if (set_score[0] - set_score[1] > 1)
                {
                    sets[l][0] = sets[l][0] + 1;
                    sets_fun();
                    set_score[0] = 0;
                    set_score[1] = 0;

                    lcd_cmd(0xC0);

                    int_to_string(scores_non[set_score[0]],placeholder);
                    disp2[0] = placeholder[3];
                    disp2[1] = placeholder[4];
                    lcd_write_string(disp2);

                    lcd_write_string(hyphen);

                    int_to_string(scores_non[set_score[1]],placeholder);
                    disp2[0] = placeholder[3];
                    disp2[1] = placeholder[4];
                    lcd_write_string(disp2);
                    break;
                }
                else
                {
                    sets_fun();
                    lcd_cmd(0xC0);
                    lcd_write_string(disp3);
                }
            }
            else if (set_score[1] > set_score[0])
            {
                if (set_score[1] - set_score[0] > 1)
                {

                    sets[l][1] = sets[l][1] + 1;
                    sets_fun();
                    set_score[0] = 0;
                    set_score[1] = 0;

                    lcd_cmd(0xC0);

                    int_to_string(scores_non[set_score[0]],placeholder);
                    disp2[0] = placeholder[3];
                    disp2[1] = placeholder[4];
                    lcd_write_string(disp2);

                    lcd_write_string(hyphen);

                    int_to_string(scores_non[set_score[1]],placeholder);
                    disp2[0] = placeholder[3];
                    disp2[1] = placeholder[4];
                    lcd_write_string(disp2);
                    break;
                }
                else
                {
                    sets_fun();
                    lcd_cmd(0xC0);
                    lcd_write_string(disp4);
                }
            }
            else
            {
                sets_fun();
                lcd_cmd(0xC0);
                lcd_write_string(disp5);
                set_score[0] = set_score[0] - 1;
                set_score[1] = set_score[1] - 1;
            }
        }

    }
		msdelay(100);
}
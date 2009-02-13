// ------------------------------------------------------
// Protrekkr
// Written by Franck Charlet
// Based on the work of Juan Antonio Arguelles Rius 
// ------------------------------------------------------

// ------------------------------------------------------
// Includes
#include "include/editor_303.h"

// ------------------------------------------------------
// Variables
SDL_Surface *SKIN303;

int Current_copy_buffer;
int Copied_Buffer[4];
unsigned char tbEditStep = 0;

flag303 tb303_pattern_buffer[4][16];
unsigned char tb303_buffer_tone[4][16];

// ------------------------------------------------------
// Fucntions
void tb303_copy_pattern(void);
void tb303_paste_pattern(void);
void tb303_notes_up(void);
void tb303_notes_down(void);
void Display_Cur_copy_Buffer(void);

void Draw_303_Ed(void)
{
    Draw_Editors_Bar(USER_SCREEN_TB303_EDIT);

    Gui_Draw_Button_Box(0, 447, fsize, 130, "", BUTTON_NORMAL | BUTTON_DISABLED);
    Gui_Draw_Flat_Box("303s Gear");

    Gui_Draw_Button_Box(8, 466, 64, 16, "Reset Patt.", BUTTON_NORMAL);
    Gui_Draw_Button_Box(8, 484, 64, 16, "Clear Patt.", BUTTON_NORMAL);
    Gui_Draw_Button_Box(8, 502, 64, 16, "Rnd.NoteOn", BUTTON_NORMAL);
    Gui_Draw_Button_Box(8, 520, 64, 16, "Rand.Tones", BUTTON_NORMAL);
    Gui_Draw_Button_Box(8, 538, 64, 16, "Rand.Flags", BUTTON_NORMAL);

    Gui_Draw_Button_Box(600, 502, 64, 16, "All Notes Up", BUTTON_NORMAL);
    Gui_Draw_Button_Box(668, 502, 64, 16, "All Notes Dn", BUTTON_NORMAL);
    Gui_Draw_Button_Box(600, 522, 64, 16, "Copy Patt.", BUTTON_NORMAL);
    Gui_Draw_Button_Box(600, 540, 64, 16, "Paste Patt.", BUTTON_NORMAL);

    Gui_Draw_Button_Box(600, 462, 56, 16, "Patt. Name", BUTTON_NORMAL | BUTTON_DISABLED);
    Gui_Draw_Button_Box(658, 462, 34, 16, "Save", BUTTON_NORMAL);

    Skincopy(80, 460, 0, 0, 510, 114);

    Actualize_303_Ed(0);
}

void Actualize_303_Ed(char gode)
{
    if(userscreen == USER_SCREEN_TB303_EDIT)
    {

        if(gode == 0 || gode == 1) number303(tb303[sl3].patternlength[tb303[sl3].selectedpattern], 118, 556);

        // Selected bassline
        if(gode == 0)
        {
            if(sl3)
            {
                Skincopy(577, 542, 138, 119, 3, 3);
                Skincopy(558, 542, 143, 119, 3, 3);
            }
            else
            {
                Skincopy(558, 542, 138, 119, 3, 3);
                Skincopy(577, 542, 143, 119, 3, 3);
            }
            number303(tbEditStep + 1, 486, 486);
            // Displaying pattern selection leds
            // Bank [A-D]
            int tbank303 = tb303[sl3].selectedpattern / 8;
            tbank303 *= 15;
            // Restoring background
            Skincopy(86, 526, 6, 66, 59, 14);
            // Light the bank
            Skincopy(86 + tbank303, 526, 15 + tbank303, 117, 14, 14);
            // Displaying pattern selection leds
            // Pattern [1-8]
            int tpat303 = tb303[sl3].selectedpattern - (tb303[sl3].selectedpattern / 8) * 8;
            // Restoring background
            Skincopy(86, 484, 6, 24, 59, 30);
            // Light the bank
            if(tpat303 < 4)
            {
                Skincopy(86 + tpat303 * 15, 484, 75 + tpat303 * 15, 117, 14, 14);
            }
            else
            {
                tpat303 -= 4;
                Skincopy(86 + tpat303 * 15, 499, 75 + tpat303 * 15, 132, 14, 14);
            }
        }

        // Displaying waveform switch
        if(gode == 0 || gode == 2)
        {
            if(tb303[sl3].waveform) Skincopy(180, 472, 137, 135, 13, 8);
            else Skincopy(180, 472, 137, 125, 13, 8);
        }

        // Draw 303 Knobs
        if(gode == 0 || gode == 3) knob(229, 476, tb303[sl3].tune / 2);
        if(gode == 0 || gode == 4) knob(262, 476, tb303[sl3].cutoff / 2);
        if(gode == 0 || gode == 5) knob(295, 476, tb303[sl3].resonance / 2);
        if(gode == 0 || gode == 6) knob(328, 476, tb303[sl3].envmod / 2);
        if(gode == 0 || gode == 7) knob(361, 476, tb303[sl3].decay / 2);
        if(gode == 0 || gode == 8) knob(394, 476, tb303[sl3].accent / 2);

        // Restoring Notepad notebackground
        if(gode == 0 || gode == 9)
        {
            Skincopy(200, 515, 120, 55, 162, 34);
    
            // Light Note
            switch(tb303[sl3].tone[tb303[sl3].selectedpattern][tbEditStep])
            {
                case 0: Skincopy(209, 543, 138, 119, 3, 3); break;
                case 1: Skincopy(220, 518, 138, 119, 3, 3); break;
                case 2: Skincopy(230, 543, 138, 119, 3, 3); break;
                case 3: Skincopy(241, 518, 138, 119, 3, 3); break;
                case 4: Skincopy(251, 543, 138, 119, 3, 3); break;
                case 5: Skincopy(272, 543, 138, 119, 3, 3); break;
                case 6: Skincopy(283, 518, 138, 119, 3, 3); break;
                case 7: Skincopy(293, 543, 138, 119, 3, 3); break;
                case 8: Skincopy(304, 518, 138, 119, 3, 3); break;
                case 9: Skincopy(314, 543, 138, 119, 3, 3); break;
                case 10: Skincopy(325, 518, 138, 119, 3, 3); break;
                case 11: Skincopy(335, 543, 138, 119, 3, 3); break;
                case 12: Skincopy(356, 543, 138, 119, 3, 3); break;
            }
        }

        // Light pause/note led
        if(gode == 0 || gode == 10)
        {
            if(tb303[sl3].flag[tb303[sl3].selectedpattern][tbEditStep].pause)
            {
                Skincopy(402, 521, 138, 119, 3, 3);
                Skincopy(439, 521, 143, 119, 3, 3);
            }
            else
            {
                Skincopy(402, 521, 143, 119, 3, 3);
                Skincopy(439, 521, 138, 119, 3, 3);
            }
        }

        // Light slide/off led
        if(gode == 0 || gode == 11)
        {
            if(tb303[sl3].flag[tb303[sl3].selectedpattern][tbEditStep].slide_flag)
            {
                Skincopy(456, 543, 138, 119, 3, 3);
            }
            else
            {
                Skincopy(456, 543, 143, 119, 3, 3);
            }
        }

        // Light accent/off led
        if(gode == 0 || gode == 12)
        {
            if(tb303[sl3].flag[tb303[sl3].selectedpattern][tbEditStep].accent_flag)
            {
                Skincopy(431, 543, 138, 119, 3, 3);
            }
            else
            {
                Skincopy(431, 543, 143, 119, 3, 3);
            }
        }

        // Transpose up flag
        if(gode == 0 || gode == 13)
        {
            if(tb303[sl3].flag[tb303[sl3].selectedpattern][tbEditStep].transposeup_flag)
            {
                Skincopy(406, 543, 138, 119, 3, 3);
            }
            else
            {
                Skincopy(406, 543, 143, 119, 3, 3);
            }
        }

        // Transpose down flag
        if(gode == 0 || gode == 14)
        {
            if(tb303[sl3].flag[tb303[sl3].selectedpattern][tbEditStep].transposedown_flag)
            {
                Skincopy(381, 543, 138, 119, 3, 3);
            }
            else
            {
                Skincopy(381, 543, 143, 119, 3, 3);
            }
        }

        // Volume
        if(gode == 0 || gode == 15)
        {
            // volume background
            Skincopy(529, 485, 449, 25, 19, 88);
            int tb303v = (int) (tb303engine[sl3].tbVolume * 72.0f);
            // Volume slider
            Skincopy(531, 558 - tb303v, 0, 116, 13, 11);
        }

        // Light hpf led
        if(gode == 0 || gode == 16)
        {
            if(tb303engine[sl3].hpf)
            {
                Skincopy(181, 528, 138, 119, 3, 3);
            }
            else
            {
                Skincopy(181, 528, 143, 119, 3, 3);
            }
        }

        if(gode == 0 || gode == 17)
        {
            Display_Cur_copy_Buffer();
        }

        if(gode == 0 || gode == 18)
        {
            char tcp[30];
            sprintf(tcp, "%s_", tb303[sl3].pattern_name[tb303[sl3].selectedpattern]);

            if(snamesel == 6)
            {
                Gui_Draw_Button_Box(600, 480, 164, 16, tcp, BUTTON_PUSHED);
            }
            else
            {
                Gui_Draw_Button_Box(600, 480, 164, 16, tb303[sl3].pattern_name[tb303[sl3].selectedpattern], BUTTON_NORMAL);
            }
        }
    }
}

void number303(unsigned char number, int x, int y)
{
    switch(number)
    {
        case 0: Skincopy(x, y, 156, 118, 7, 14); Skincopy(x + 8, y, 156, 118, 7, 14); break;
        case 1: Skincopy(x, y, 156, 118, 7, 14); Skincopy(x + 8, y, 164, 118, 7, 14); break;
        case 2: Skincopy(x, y, 156, 118, 7, 14); Skincopy(x + 8, y, 172, 118, 7, 14); break;
        case 3: Skincopy(x, y, 156, 118, 7, 14); Skincopy(x + 8, y, 180, 118, 7, 14); break;
        case 4: Skincopy(x, y, 156, 118, 7, 14); Skincopy(x + 8, y, 188, 118, 7, 14); break;
        case 5: Skincopy(x, y, 156, 118, 7, 14); Skincopy(x + 8, y, 196, 118, 7, 14); break;
        case 6: Skincopy(x, y, 156, 118, 7, 14); Skincopy(x + 8, y, 204, 118, 7, 14); break;
        case 7: Skincopy(x, y, 156, 118, 7, 14); Skincopy(x + 8, y, 212, 118, 7, 14); break;
        case 8: Skincopy(x, y, 156, 118, 7, 14); Skincopy(x + 8, y, 220, 118, 7, 14); break;
        case 9: Skincopy(x, y, 156, 118, 7, 14); Skincopy(x + 8, y, 228, 118, 7, 14); break;
        case 10: Skincopy(x, y, 164, 118, 7, 14); Skincopy(x + 8, y, 156, 118, 7, 14); break;
        case 11: Skincopy(x, y, 164, 118, 7, 14); Skincopy(x + 8, y, 164, 118, 7, 14); break;
        case 12: Skincopy(x, y, 164, 118, 7, 14); Skincopy(x + 8, y, 172, 118, 7, 14); break;
        case 13: Skincopy(x, y, 164, 118, 7, 14); Skincopy(x + 8, y, 180, 118, 7, 14); break;
        case 14: Skincopy(x, y, 164, 118, 7, 14); Skincopy(x + 8, y, 188, 118, 7, 14); break;
        case 15: Skincopy(x, y, 164, 118, 7, 14); Skincopy(x + 8, y, 196, 118, 7, 14); break;
        case 16: Skincopy(x, y, 164, 118, 7, 14); Skincopy(x + 8, y, 204, 118, 7, 14); break;
    }
}

void knob(int x, int y, unsigned char number)
{
    if(number > 62) number = 62;
    Skincopy(x, y, number * 25, 147, 24, 24);
}

void Mouse_Right_303_Ed(void )
{
    if(userscreen == USER_SCREEN_TB303_EDIT)
    {
        // Volume Knob
        if(zcheckMouse(529, 485, 19, 88))
        {
            tb303engine[sl3].tbVolume = 43 * 0.01136363636f;
            gui_action = GUI_CMD_REFRESH_TB303_PARAMS;
            teac = 15;
        }

        // Tune Knob
        if(zcheckMouse(229, 476, 24, 24))
        {
            int tempz = 64;
            tb303[sl3].tune = tempz;
            gui_action = GUI_CMD_REFRESH_TB303_PARAMS;
            teac = 3;
            liveparam = LIVE_PARAM_303_1_TUNE + sl3;
            livevalue = tempz << 1;
        }

        // CutOff Knob
        if(zcheckMouse(262, 476, 24, 24))
        {
            int tempz = 64;
            tb303[sl3].cutoff = tempz;
            gui_action = GUI_CMD_REFRESH_TB303_PARAMS;
            teac = 4;
            liveparam = LIVE_PARAM_303_1_CUTOFF + sl3;
            livevalue = tempz << 1;
        }

        // Reso knob
        if(zcheckMouse(295, 476, 24, 24))
        {
            int tempz = 64;
            tb303[sl3].resonance = tempz;
            gui_action = GUI_CMD_REFRESH_TB303_PARAMS;
            teac = 5;
            liveparam = LIVE_PARAM_303_1_RESONANCE + sl3;
            livevalue = tempz << 1;
        }

        // Envmod knob
        if(zcheckMouse(328, 476, 24, 24))
        {
            int tempz = 64;
            tb303[sl3].envmod = tempz;
            gui_action = GUI_CMD_REFRESH_TB303_PARAMS;
            teac = 6;
            liveparam = LIVE_PARAM_303_1_ENVMOD + sl3;
            livevalue = tempz << 1;
        }

        // Decay knob
        if(zcheckMouse(361, 476, 24, 24))
        {
            int tempz = 64;
            tb303[sl3].decay = tempz;
            gui_action = GUI_CMD_REFRESH_TB303_PARAMS;
            teac = 7;
            liveparam = LIVE_PARAM_303_1_DECAY + sl3;
            livevalue = tempz << 1;
        }

        // Accent knob
        if(zcheckMouse(394, 476, 24, 24))
        {
            int tempz = 64;
            tb303[sl3].accent = tempz;
            gui_action = GUI_CMD_REFRESH_TB303_PARAMS;
            teac = 8;
            liveparam = LIVE_PARAM_303_1_ACCENT + sl3;
            livevalue = tempz << 1;
        }
    }
}

void Mouse_Wheel_303_Ed(int roll_amount)
{
    if(userscreen == USER_SCREEN_TB303_EDIT)
    {
        // Volume Knob
        if(zcheckMouse(529, 485, 19, 88))
        {
            float froll = roll_amount / 86.0f;
            float breakvol = tb303engine[sl3].tbVolume + froll;
            if(breakvol < 0.0f) breakvol = 0.0f;
            if(breakvol > 1.0f) breakvol = 1.0f;
            tb303engine[sl3].tbVolume = breakvol;
            gui_action = GUI_CMD_REFRESH_TB303_PARAMS;
            teac = 15;
        }

        // Tune Knob
        if(zcheckMouse(229, 476, 24, 24))
        {
            int tempz = tb303[sl3].tune + roll_amount;
            if(tempz < 0) tempz = 0;
            if(tempz > 127) tempz = 127;
            tb303[sl3].tune = tempz;
            gui_action = GUI_CMD_REFRESH_TB303_PARAMS;
            teac = 3;
            liveparam = LIVE_PARAM_303_1_TUNE + sl3;
            livevalue = tempz << 1;
        }

        // CutOff Knob
        if(zcheckMouse(262, 476, 24, 24))
        {
            int tempz = tb303[sl3].cutoff + roll_amount;
            if(tempz < 0) tempz = 0;
            if(tempz > 127) tempz = 127;
            tb303[sl3].cutoff = tempz;
            gui_action = GUI_CMD_REFRESH_TB303_PARAMS;
            teac = 4;
            liveparam = LIVE_PARAM_303_1_CUTOFF + sl3;
            livevalue = tempz << 1;
        }

        // Reso knob
        if(zcheckMouse(295, 476, 24, 24))
        {
            int tempz = tb303[sl3].resonance + roll_amount;
            if(tempz < 0) tempz = 0;
            if(tempz > 127) tempz = 127;
            tb303[sl3].resonance = tempz;
            gui_action = GUI_CMD_REFRESH_TB303_PARAMS;
            teac = 5;
            liveparam = LIVE_PARAM_303_1_RESONANCE + sl3;
            livevalue = tempz << 1;
        }

        // Envmod knob
        if(zcheckMouse(328, 476, 24, 24))
        {
            int tempz = tb303[sl3].envmod + roll_amount;
            if(tempz < 0) tempz = 0;
            if(tempz > 127) tempz = 127;
            tb303[sl3].envmod = tempz;
            gui_action = GUI_CMD_REFRESH_TB303_PARAMS;
            teac = 6;
            liveparam = LIVE_PARAM_303_1_ENVMOD + sl3;
            livevalue = tempz << 1;
        }

        // Decay knob
        if(zcheckMouse(361, 476, 24, 24))
        {
            int tempz = tb303[sl3].decay + roll_amount;
            if(tempz < 0) tempz = 0;
            if(tempz > 127) tempz = 127;
            tb303[sl3].decay = tempz;
            gui_action = GUI_CMD_REFRESH_TB303_PARAMS;
            teac = 7;
            liveparam = LIVE_PARAM_303_1_DECAY + sl3;
            livevalue = tempz << 1;
        }

        // Accent knob
        if(zcheckMouse(394, 476, 24, 24))
        {
            int tempz = tb303[sl3].accent + roll_amount;
            if(tempz < 0) tempz = 0;
            if(tempz > 127) tempz = 127;
            tb303[sl3].accent = tempz;
            gui_action = GUI_CMD_REFRESH_TB303_PARAMS;
            teac = 8;
            liveparam = LIVE_PARAM_303_1_ACCENT + sl3;
            livevalue = tempz << 1;
        }
    }
}

void Mouse_Left_303_Ed(void)
{
    // 303 handling gui source code
    if(userscreen == USER_SCREEN_TB303_EDIT)
    {
        // Step Forward
        if(zcheckMouse(479, 550, 25, 16))
        {
            tbEditStep++;
            if(tbEditStep > 15) tbEditStep = 0;
            gui_action = GUI_CMD_REFRESH_TB303_PARAMS;
            teac = 0;
        }

        // Step Back
        if(zcheckMouse(484, 522, 15, 10))
        {
            if(tbEditStep == 0) tbEditStep = 15;
            else tbEditStep--;
            teac = 0;
            gui_action = GUI_CMD_REFRESH_TB303_PARAMS;
        }

        // Pattern Steps +1
        if(zcheckMouse(135, 555, 11, 9) &&
           tb303[sl3].patternlength[tb303[sl3].selectedpattern] < 16)
        {
            tb303[sl3].patternlength[tb303[sl3].selectedpattern]++;
            gui_action = GUI_CMD_REFRESH_TB303_PARAMS;
            teac = 1;
        }

        // Pattern Steps -1
        if(zcheckMouse(135, 564, 11, 9) &&
           tb303[sl3].patternlength[tb303[sl3].selectedpattern] > 1)
        {
            tb303[sl3].patternlength[tb303[sl3].selectedpattern]--;
            gui_action = GUI_CMD_REFRESH_TB303_PARAMS;
            teac = 1;
        }

        // Pause/Note button
        if(zcheckMouse(450, 518, 15, 10))
        {
            if(tb303[sl3].flag[tb303[sl3].selectedpattern][tbEditStep].pause)
            {
                tb303[sl3].flag[tb303[sl3].selectedpattern][tbEditStep].pause = 0;
            }
            else
            {
                tb303[sl3].flag[tb303[sl3].selectedpattern][tbEditStep].pause = 1;
            }
            teac = 10;
            gui_action = GUI_CMD_REFRESH_TB303_PARAMS;
        }

        // Glide button
        if(zcheckMouse(454, 550, 10, 15))
        {
            if(tb303[sl3].flag[tb303[sl3].selectedpattern][tbEditStep].slide_flag)
            {
                tb303[sl3].flag[tb303[sl3].selectedpattern][tbEditStep].slide_flag = 0;
            }
            else
            {
                tb303[sl3].flag[tb303[sl3].selectedpattern][tbEditStep].slide_flag = 1;
            }
            teac = 11;
            gui_action = GUI_CMD_REFRESH_TB303_PARAMS;
        }

        // Accent button
        if(zcheckMouse(428, 550, 10, 15))
        {
            if(tb303[sl3].flag[tb303[sl3].selectedpattern][tbEditStep].accent_flag)
            {
                tb303[sl3].flag[tb303[sl3].selectedpattern][tbEditStep].accent_flag = 0;
            }
            else
            {
                tb303[sl3].flag[tb303[sl3].selectedpattern][tbEditStep].accent_flag = 1;
            }
            teac = 12;
            gui_action = GUI_CMD_REFRESH_TB303_PARAMS;
        }

        // Transpose up button
        if(zcheckMouse(403, 550, 10, 15))
        {
            if(tb303[sl3].flag[tb303[sl3].selectedpattern][tbEditStep].transposeup_flag)
            {
                tb303[sl3].flag[tb303[sl3].selectedpattern][tbEditStep].transposeup_flag = 0;
            }
            else
            {
                tb303[sl3].flag[tb303[sl3].selectedpattern][tbEditStep].transposeup_flag = 1;
            }
            teac = 13;
            gui_action = GUI_CMD_REFRESH_TB303_PARAMS;
        }

        // Transpose down button
        if(zcheckMouse(378, 550, 10, 15))
        {
            if(tb303[sl3].flag[tb303[sl3].selectedpattern][tbEditStep].transposedown_flag)
            {
                tb303[sl3].flag[tb303[sl3].selectedpattern][tbEditStep].transposedown_flag = 0;
            }
            else
            {
                tb303[sl3].flag[tb303[sl3].selectedpattern][tbEditStep].transposedown_flag = 1;
            }
            teac = 14;
            gui_action = GUI_CMD_REFRESH_TB303_PARAMS;
        }

        // Sawtooth/Square switching
        if(zcheckMouse(177, 471, 19, 10))
        {
            tb303[sl3].waveform ^= 1;
            gui_action = GUI_CMD_REFRESH_TB303_PARAMS;
            teac = 2;
        }

        // NoteOn/Off buttons
        if(zcheckMouse(206, 550, 12, 15))
        {
            tb303[sl3].tone[tb303[sl3].selectedpattern][tbEditStep] = 0;
            gui_action = GUI_CMD_REFRESH_TB303_PARAMS;
            teac = 9;
        }
        if(zcheckMouse(217, 524, 11, 15))
        {
            tb303[sl3].tone[tb303[sl3].selectedpattern][tbEditStep] = 1;
            gui_action = GUI_CMD_REFRESH_TB303_PARAMS;
            teac = 9;
        }
        if(zcheckMouse(227, 550, 12, 15))
        {
            tb303[sl3].tone[tb303[sl3].selectedpattern][tbEditStep] = 2;
            gui_action = GUI_CMD_REFRESH_TB303_PARAMS;
            teac = 9;
        }
        if(zcheckMouse(238, 524, 11, 15))
        {
            tb303[sl3].tone[tb303[sl3].selectedpattern][tbEditStep] = 3;
            gui_action = GUI_CMD_REFRESH_TB303_PARAMS;
            teac = 9;
        }
        if(zcheckMouse(247, 550, 12, 15))
        {
            tb303[sl3].tone[tb303[sl3].selectedpattern][tbEditStep] = 4;
            gui_action = GUI_CMD_REFRESH_TB303_PARAMS;
            teac = 9;
        }
        if(zcheckMouse(268, 550, 12, 15))
        {
            tb303[sl3].tone[tb303[sl3].selectedpattern][tbEditStep] = 5;
            gui_action = GUI_CMD_REFRESH_TB303_PARAMS;
            teac = 9;
        }
        if(zcheckMouse(280, 524, 11, 15))
        {
            tb303[sl3].tone[tb303[sl3].selectedpattern][tbEditStep] = 6;
            gui_action = GUI_CMD_REFRESH_TB303_PARAMS;
            teac = 9;
        }
        if(zcheckMouse(289, 550, 12, 15))
        {
            tb303[sl3].tone[tb303[sl3].selectedpattern][tbEditStep] = 7;
            gui_action = GUI_CMD_REFRESH_TB303_PARAMS;
            teac = 9;
        }
        if(zcheckMouse(301, 524, 11, 15))
        {
            tb303[sl3].tone[tb303[sl3].selectedpattern][tbEditStep] = 8;
            gui_action = GUI_CMD_REFRESH_TB303_PARAMS;
            teac = 9;
        }
        if(zcheckMouse(310, 550, 12, 15))
        {
            tb303[sl3].tone[tb303[sl3].selectedpattern][tbEditStep] = 9;
            gui_action = GUI_CMD_REFRESH_TB303_PARAMS;
            teac = 9;
        }

        if(zcheckMouse(322, 524, 11, 15))
        {
            tb303[sl3].tone[tb303[sl3].selectedpattern][tbEditStep] = 10;
            gui_action = GUI_CMD_REFRESH_TB303_PARAMS;
            teac = 9;
        }
        if(zcheckMouse(331, 550, 12, 15))
        {
            tb303[sl3].tone[tb303[sl3].selectedpattern][tbEditStep] = 11;
            gui_action = GUI_CMD_REFRESH_TB303_PARAMS;
            teac = 9;
        }
        if(zcheckMouse(352, 550, 12, 15))
        {
            tb303[sl3].tone[tb303[sl3].selectedpattern][tbEditStep] = 12;
            gui_action = GUI_CMD_REFRESH_TB303_PARAMS;
            teac = 9;
        }

        // Pattern selection buttons
        if(zcheckMouse(86, 483, 16, 16))
        {
            char gcp = (tb303[sl3].selectedpattern / 8) * 8;
            tb303[sl3].selectedpattern = gcp;
            gui_action = GUI_CMD_REFRESH_TB303_PARAMS;
            teac = 0;
        }
        if(zcheckMouse(100, 483, 16, 16))
        {
            char gcp = (tb303[sl3].selectedpattern / 8) * 8;
            tb303[sl3].selectedpattern = gcp + 1;
            gui_action = GUI_CMD_REFRESH_TB303_PARAMS;
            teac = 0;
        }
        if(zcheckMouse(114, 483, 16, 16))
        {
            char gcp = (tb303[sl3].selectedpattern / 8) * 8;
            tb303[sl3].selectedpattern = gcp + 2;
            gui_action = GUI_CMD_REFRESH_TB303_PARAMS;
            teac = 0;
        }
        if(zcheckMouse(130, 483, 16, 16))
        {
            char gcp = (tb303[sl3].selectedpattern / 8) * 8;
            tb303[sl3].selectedpattern = gcp + 3;
            gui_action = GUI_CMD_REFRESH_TB303_PARAMS;
            teac = 0;
        }
        if(zcheckMouse(86, 498, 16, 16))
        {
            char gcp = (tb303[sl3].selectedpattern / 8) * 8;
            tb303[sl3].selectedpattern = gcp + 4;
            gui_action = GUI_CMD_REFRESH_TB303_PARAMS;
            teac = 0;
        }
        if(zcheckMouse(100, 498, 16, 16))
        {
            char gcp = (tb303[sl3].selectedpattern / 8) * 8;
            tb303[sl3].selectedpattern = gcp + 5;
            gui_action = GUI_CMD_REFRESH_TB303_PARAMS;
            teac = 0;
        }
        if(zcheckMouse(114, 498, 16, 16))
        {
            char gcp = (tb303[sl3].selectedpattern / 8) * 8;
            tb303[sl3].selectedpattern = gcp + 6;
            gui_action = GUI_CMD_REFRESH_TB303_PARAMS;
            teac = 0;
        }
        if(zcheckMouse(130, 498, 16, 16))
        {
            char gcp = (tb303[sl3].selectedpattern / 8) * 8;
            tb303[sl3].selectedpattern = gcp + 7;
            gui_action = GUI_CMD_REFRESH_TB303_PARAMS;
            teac = 0;
        }

        // Bank selection buttons
        if(zcheckMouse(86, 525, 16, 16))
        {
            tb303[sl3].selectedpattern = (tb303[sl3].selectedpattern - (tb303[sl3].selectedpattern / 8) * 8);
            gui_action = GUI_CMD_REFRESH_TB303_PARAMS;
            teac = 0;
        }
        if(zcheckMouse(100, 525, 16, 16))
        {
            tb303[sl3].selectedpattern = ((tb303[sl3].selectedpattern - (tb303[sl3].selectedpattern / 8) * 8)) + 8;
            gui_action = GUI_CMD_REFRESH_TB303_PARAMS;
            teac = 0;
        }
        if(zcheckMouse(114, 525, 16, 16))
        {
            tb303[sl3].selectedpattern = ((tb303[sl3].selectedpattern - (tb303[sl3].selectedpattern / 8) * 8)) + 16;
            gui_action = GUI_CMD_REFRESH_TB303_PARAMS;
            teac = 0;
        }
        if(zcheckMouse(130, 525, 16, 16))
        {
            tb303[sl3].selectedpattern = ((tb303[sl3].selectedpattern - (tb303[sl3].selectedpattern / 8) * 8)) + 24;
            gui_action = GUI_CMD_REFRESH_TB303_PARAMS;
            teac = 0;
        }

        // 303 #1
        if(zcheckMouse(553, 529, 15, 12))
        {
            sl3 = 0;
            gui_action = GUI_CMD_REFRESH_TB303_PARAMS;
            teac = 0;
        }
        // 303 #2
        if(zcheckMouse(573, 529, 15, 12))
        {
            sl3 = 1;
            gui_action = GUI_CMD_REFRESH_TB303_PARAMS;
            teac = 0;
        }

        // hipass filter on/off
        if(zcheckMouse(176, 536, 15, 10))
        {
            if(tb303engine[sl3].hpf) tb303engine[sl3].hpf = FALSE;
            else tb303engine[sl3].hpf = TRUE;
            teac = 16;
            gui_action = GUI_CMD_REFRESH_TB303_PARAMS;
        }

        // rand tones
        if(zcheckMouse(8, 520, 64, 16))
        {
            for(char alter = 0; alter < 16; alter++)
            {
                tb303[sl3].tone[tb303[sl3].selectedpattern][alter] = rand() / 2731;
            }
            teac = 0;
            gui_action = GUI_CMD_REFRESH_TB303_PARAMS;
        }

        // rand flags
        if(zcheckMouse(8, 538, 64, 16))
        {
            for(char alter = 0; alter < 16; alter++)
            {
                tb303[sl3].flag[tb303[sl3].selectedpattern][alter].slide_flag = rand() / 16384;
                tb303[sl3].flag[tb303[sl3].selectedpattern][alter].transposeup_flag = rand() / 16384;
                tb303[sl3].flag[tb303[sl3].selectedpattern][alter].transposedown_flag = rand() / 16384;
                tb303[sl3].flag[tb303[sl3].selectedpattern][alter].accent_flag = rand() / 16384;
            }
            teac = 0;
            gui_action = GUI_CMD_REFRESH_TB303_PARAMS;
        }

        // rand noteon
        if(zcheckMouse(8, 502, 64, 16))
        {
            for(char alter = 0; alter < 16; alter++)
            {
                tb303[sl3].flag[tb303[sl3].selectedpattern][alter].pause = rand() / 16384;
            }
            teac = 0;
            gui_action = GUI_CMD_REFRESH_TB303_PARAMS;
        }

        // clear pat...
        if(zcheckMouse(8, 484, 64, 16))
        {
            for(char alter = 0; alter < 16; alter++)
            {
                tb303[sl3].tone[tb303[sl3].selectedpattern][alter] = 0;
                tb303[sl3].flag[tb303[sl3].selectedpattern][alter].pause = 0;
                tb303[sl3].flag[tb303[sl3].selectedpattern][alter].slide_flag = 0;
                tb303[sl3].flag[tb303[sl3].selectedpattern][alter].transposeup_flag = 0;
                tb303[sl3].flag[tb303[sl3].selectedpattern][alter].transposedown_flag = 0;
                tb303[sl3].flag[tb303[sl3].selectedpattern][alter].accent_flag = 0;
            }
            teac = 0;
            gui_action = GUI_CMD_REFRESH_TB303_PARAMS;
        }

        // reset pat...
        if(zcheckMouse(8, 466, 64, 16))
        {
            for(char alter = 0; alter < 16; alter++)
            {
                tb303[sl3].tone[tb303[sl3].selectedpattern][alter] = 0;
                tb303[sl3].flag[tb303[sl3].selectedpattern][alter].pause = 1;
                tb303[sl3].flag[tb303[sl3].selectedpattern][alter].slide_flag = 0;
                tb303[sl3].flag[tb303[sl3].selectedpattern][alter].transposeup_flag = 0;
                tb303[sl3].flag[tb303[sl3].selectedpattern][alter].transposedown_flag = 0;
                tb303[sl3].flag[tb303[sl3].selectedpattern][alter].accent_flag = 0;
            }
            teac = 0;
            gui_action = GUI_CMD_REFRESH_TB303_PARAMS;
        }

        // all notes up
        if(zcheckMouse(668, 502, 64, 16))
        {
            tb303_notes_up();
            teac = 0;
            gui_action = GUI_CMD_REFRESH_TB303_PARAMS;
        }

        // all notes down
        if(zcheckMouse(600, 502, 64, 16))
        {
            tb303_notes_down();
            teac = 0;
            gui_action = GUI_CMD_REFRESH_TB303_PARAMS;
        }

        // copy pattern
        if(zcheckMouse(600, 522, 64, 16))
        {
            tb303_copy_pattern();
            teac = 0;
            gui_action = GUI_CMD_REFRESH_TB303_PARAMS;
        }

        // paste pattern
        if(zcheckMouse(600, 540, 64, 16))
        {
            tb303_paste_pattern();
            teac = 0;
            gui_action = GUI_CMD_REFRESH_TB303_PARAMS;
        }

        // Select the copy buffers
        if(zcheckMouse(600, 558, 15, 16))
        {
            Current_copy_buffer = 0;
            teac = 17;
            gui_action = GUI_CMD_REFRESH_TB303_PARAMS;
        }
        if(zcheckMouse(616, 558, 15, 16))
        {
            Current_copy_buffer = 1;
            teac = 17;
            gui_action = GUI_CMD_REFRESH_TB303_PARAMS;
        }
        if(zcheckMouse(633, 558, 15, 16))
        {
            Current_copy_buffer = 2;
            teac = 17;
            gui_action = GUI_CMD_REFRESH_TB303_PARAMS;
        }
        if(zcheckMouse(649, 558, 15, 16))
        {
            Current_copy_buffer = 3;
            teac = 17;
            gui_action = GUI_CMD_REFRESH_TB303_PARAMS;
        }

        if(zcheckMouse(600, 480, 164, 16) && snamesel == 0)
        {
            snamesel = 6;
            strcpy(cur_input_name, tb303[sl3].pattern_name[tb303[sl3].selectedpattern]);
            namesize = 0;
            sprintf(tb303[sl3].pattern_name[tb303[sl3].selectedpattern], "");
            teac = 18;
            gui_action = GUI_CMD_UPDATE_MIDI_303_ED;
        }

        if(zcheckMouse(658, 462, 34, 16))
        {
            gui_action = GUI_CMD_SAVE_303_PATTERN;
        }
    }
}

void Mouse_Sliders_303_Ed(void)
{
    if(userscreen == USER_SCREEN_TB303_EDIT)
    {
        // Volume Knob
        if(zcheckMouse(529, 485, 19, 88))
        {
            float breakvol = (float) (90 - (Mouse.y - 485));
            breakvol /= 86.0f;
            if(breakvol < 0.0f) breakvol = 0.0f;
            if(breakvol > 1.0f) breakvol = 1.0f;
            tb303engine[sl3].tbVolume = breakvol;
            gui_action = GUI_CMD_REFRESH_TB303_PARAMS;
            teac = 15;
        }

        // Tune Knob
        if(zcheckMouse(229, 476, 24, 24))
        {
            if(fluzy == -1) fluzy = Mouse.y + tb303[sl3].tune;

            int tempz = fluzy - Mouse.y;
            if(tempz < 0) tempz = 0;
            if(tempz > 127) tempz = 127;
            tb303[sl3].tune = tempz;
            gui_action = GUI_CMD_REFRESH_TB303_PARAMS;
            teac = 3;
            liveparam = LIVE_PARAM_303_1_TUNE + sl3;
            livevalue = tempz << 1;
        }

        // CutOff Knob
        if(zcheckMouse(262, 476, 24, 24))
        {
            if(fluzy == -1) fluzy = Mouse.y + tb303[sl3].cutoff;

            int tempz = fluzy - Mouse.y;
            if(tempz < 0) tempz = 0;
            if(tempz > 127) tempz = 127;
            tb303[sl3].cutoff = tempz;
            gui_action = GUI_CMD_REFRESH_TB303_PARAMS;
            teac = 4;
            liveparam = LIVE_PARAM_303_1_CUTOFF + sl3;
            livevalue = tempz << 1;
        }

        // Reso knob
        if(zcheckMouse(295, 476, 24, 24))
        {
            if(fluzy == -1) fluzy = Mouse.y + tb303[sl3].resonance;

            int tempz = fluzy - Mouse.y;
            if(tempz < 0) tempz = 0;
            if(tempz > 127) tempz = 127;
            tb303[sl3].resonance = tempz;
            gui_action = GUI_CMD_REFRESH_TB303_PARAMS;
            teac = 5;
            liveparam = LIVE_PARAM_303_1_RESONANCE + sl3;
            livevalue = tempz << 1;
        }

        // Envmod knob
        if(zcheckMouse(328, 476, 24, 24))
        {
            if(fluzy == -1) fluzy = Mouse.y + tb303[sl3].envmod;

            int tempz = fluzy - Mouse.y;
            if(tempz < 0) tempz = 0;
            if(tempz > 127) tempz = 127;
            tb303[sl3].envmod = tempz;
            gui_action = GUI_CMD_REFRESH_TB303_PARAMS;
            teac = 6;
            liveparam = LIVE_PARAM_303_1_ENVMOD + sl3;
            livevalue = tempz << 1;
        }

        // Decay knob
        if(zcheckMouse(361, 476, 24, 24))
        {
            if(fluzy == -1) fluzy = Mouse.y + tb303[sl3].decay;

            int tempz = fluzy - Mouse.y;
            if(tempz < 0) tempz = 0;
            if(tempz > 127) tempz = 127;
            tb303[sl3].decay = tempz;
            gui_action = GUI_CMD_REFRESH_TB303_PARAMS;
            teac = 7;
            liveparam = LIVE_PARAM_303_1_DECAY + sl3;
            livevalue = tempz << 1;
        }

        // Accent knob
        if(zcheckMouse(394, 476, 24, 24))
        {
            if(fluzy == -1) fluzy = Mouse.y + tb303[sl3].accent;

            int tempz = fluzy - Mouse.y;
            if(tempz < 0) tempz = 0;
            if(tempz > 127) tempz = 127;
            tb303[sl3].accent = tempz;
            gui_action = GUI_CMD_REFRESH_TB303_PARAMS;
            teac = 8;
            liveparam = LIVE_PARAM_303_1_ACCENT + sl3;
            livevalue = tempz << 1;
        }
    }
}

void Skincopy(int xd, int yd, int xs, int ys, int w, int h)
{
    Copy(SKIN303, xd, yd, xs, ys, xs + w, ys + h);
}

void tb303_copy_pattern(void)
{

    for(char alter = 0; alter < 16; alter++)
    {
        tb303_buffer_tone[Current_copy_buffer][alter] = tb303[sl3].tone[tb303[sl3].selectedpattern][alter];
        tb303_pattern_buffer[Current_copy_buffer][alter].pause = tb303[sl3].flag[tb303[sl3].selectedpattern][alter].pause;
        tb303_pattern_buffer[Current_copy_buffer][alter].slide_flag = tb303[sl3].flag[tb303[sl3].selectedpattern][alter].slide_flag;
        tb303_pattern_buffer[Current_copy_buffer][alter].transposeup_flag = tb303[sl3].flag[tb303[sl3].selectedpattern][alter].transposeup_flag;
        tb303_pattern_buffer[Current_copy_buffer][alter].transposedown_flag = tb303[sl3].flag[tb303[sl3].selectedpattern][alter].transposedown_flag;
        tb303_pattern_buffer[Current_copy_buffer][alter].accent_flag = tb303[sl3].flag[tb303[sl3].selectedpattern][alter].accent_flag;
    }
    Copied_Buffer[Current_copy_buffer] = TRUE;
}

void tb303_paste_pattern(void)
{
    if(Copied_Buffer[Current_copy_buffer])
    {
        for(char alter = 0; alter < 16; alter++)
        {
            tb303[sl3].tone[tb303[sl3].selectedpattern][alter] = tb303_buffer_tone[Current_copy_buffer][alter];
            tb303[sl3].flag[tb303[sl3].selectedpattern][alter].pause = tb303_pattern_buffer[Current_copy_buffer][alter].pause;
            tb303[sl3].flag[tb303[sl3].selectedpattern][alter].slide_flag = tb303_pattern_buffer[Current_copy_buffer][alter].slide_flag;
            tb303[sl3].flag[tb303[sl3].selectedpattern][alter].transposeup_flag = tb303_pattern_buffer[Current_copy_buffer][alter].transposeup_flag;
            tb303[sl3].flag[tb303[sl3].selectedpattern][alter].transposedown_flag = tb303_pattern_buffer[Current_copy_buffer][alter].transposedown_flag;
            tb303[sl3].flag[tb303[sl3].selectedpattern][alter].accent_flag = tb303_pattern_buffer[Current_copy_buffer][alter].accent_flag;
        }
    }
}

void tb303_notes_up(void)
{
    for(char alter = 0; alter < 16; alter++)
    {
        if(tb303[sl3].tone[tb303[sl3].selectedpattern][alter] != 12)
        {
            tb303[sl3].tone[tb303[sl3].selectedpattern][alter]++;
        }
    }
}

void tb303_notes_down(void)
{
    for(char alter = 0; alter < 16; alter++)
    {
        if(tb303[sl3].tone[tb303[sl3].selectedpattern][alter])
        {
            tb303[sl3].tone[tb303[sl3].selectedpattern][alter]--;
        }
    }
}

void Display_Cur_copy_Buffer(void)
{
    int highlight[4] =
    {
        BUTTON_NORMAL,
        BUTTON_NORMAL,
        BUTTON_NORMAL,
        BUTTON_NORMAL
    };
    highlight[Current_copy_buffer] = BUTTON_PUSHED;
    Gui_Draw_Button_Box(600, 558, 15, 16, "1", highlight[0]);
    Gui_Draw_Button_Box(616, 558, 15, 16, "2", highlight[1]);
    Gui_Draw_Button_Box(633, 558, 15, 16, "3", highlight[2]);
    Gui_Draw_Button_Box(649, 558, 15, 16, "4", highlight[3]);
}

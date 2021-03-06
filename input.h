/*
    input include file
    Copyright (C) 2011 Pavel Semerad

    This program is free software: you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation, either version 3 of the License, or
    (at your option) any later version.

    This program is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/


#ifndef _INPUT_INCLUDED
#define _INPUT_INCLUDED


#include "gt3b.h"


// buttons IDs
#define BTN_TRIM_LEFT	0x0001
#define BTN_TRIM_RIGHT	0x0002
#define BTN_TRIM_1	0x0003
#define BTN_TRIM_FWD	0x0004
#define BTN_TRIM_BCK	0x0008
#define BTN_TRIM_2	0x000c
#define BTN_TRIM_CH3_L	0x0010
#define BTN_TRIM_CH3_R	0x0020
#define BTN_TRIM_3	0x0030
#define BTN_TRIM_ALL	0x003f

#define BTN_DR_L	0x0040
#define BTN_DR_R	0x0080
#define BTN_DR_ALL	0x00c0

#define BTN_ENTER	0x0100
#define BTN_BACK	0x0200
#define BTN_END		0x0400

#define BTN_CH3		0x0800

#define BTN_ROT_L	0x4000
#define BTN_ROT_R	0x8000
#define BTN_ROT_ALL	0xc000

#define BTN_ALL		0xffff


// variables representing pressed buttons
extern volatile u16 buttons_state;	// actual state of buttons
extern volatile u16 buttons;		// pressed buttons (must be cleared by SW)
extern volatile u16 buttons_long;	// >1s presses buttons
#define btn(mask)	(buttons & (mask))
#define btns(mask)	(buttons_state & (mask))
#define btns_all(mask)	((buttons_state & (mask)) == (mask))
#define btnl(mask)	(buttons_long & (mask))
#define btnl_all(mask)  ((buttons_long & (mask)) == (mask))
// variables for ADC values
extern @near volatile u16 adc_all_ovs[3];	// oversampled from 4 samples and is 4* more
#define ADC_OVS_SHIFT 2
#define ADC_OVS_RND   2
#define adc_steering_ovs   adc_all_ovs[0]
#define adc_throttle_ovs   adc_all_ovs[1]
#define adc_ch3_ovs        adc_all_ovs[2]
extern @near volatile u32 adc_battery_filt;	// battery will be filtered more times
#define ADC_BAT_FILT  512
extern @near volatile u16 adc_battery;	// adc_battery_filt >> ADC_BATTERY_SHIFT
extern @near volatile u16 adc_all_last[3];	// last readed value
#define adc_steering_last  adc_all_last[0]
#define adc_throttle_last  adc_all_last[1]
#define adc_ch3_last       adc_all_last[2]
extern @near volatile u16 adc_battery_last;


// reset pressed button(s)
// do it after used that button in code
extern void button_reset(u16 btn);
#define btnr(mask)  button_reset(mask)
#define btnra()     button_reset(BTN_ALL)
extern void button_reset_nolong(u16 btn);
#define btnr_nolong(mask)  button_reset_nolong(mask)


// set autorepeat
extern void button_autorepeat(u8 btn);



// INPUT task
E_TASK(INPUT);
extern _Bool input_initialized;


#endif


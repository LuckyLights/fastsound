#ifndef FAST_SOUND
#define FAST_SOUND

#include <gb/gb.h>
#include <gb/hardware.h>

/* **************** Helpers ***************** */

#define FF30 ((volatile UINT8 *)0xFF30)

/**
 Loops sound if used in SOUND_CHANNEL_*_PLAY as stop_loop
 */
#define SOUND_LOOP 0x00U

/**
 Stops sound at SOUND_CHANNEL_*_PATTERN lenght or SOUND_CHANNEL_*_LEGNTH if used in SOUND_CHANNEL_*_PLAY as stop_loop
 */
#define SOUND_STOP 0x40U

/**
 Used for volume decrease as direction in SOUND_CHANNEL_*_ENVELOPE and SOUND_CHANNEL_1_SWEEP
 */
#define DIRECTION_DECREASE 0x00U

/**
 Used for volume increase as direction in SOUND_CHANNEL_*_ENVELOPE and SOUND_CHANNEL_1_SWEEP
 */
#define DIRECTION_INCREASE 0x04U


/**
 Pattern Duty bits used as duty with SOUND_CHANNEL_*_PATTERN to set duty to 12.5%, 25%, 50% or 75%
 */
#define PATTERN_DUTY_12 0x00U
#define PATTERN_DUTY_25 0x40U
#define PATTERN_DUTY_50 0x80U
#define PATTERN_DUTY_75 0xC0U

/**
 15 bit Counter Step/Width used with SOUND_CHANNEL_4_POLYNOMIAL as width
 */
#define POLYNOMIAL_WIDTH_15BIT 0x00U

/**
 7 bit Counter Step/Width used with SOUND_CHANNEL_4_POLYNOMIAL as width
 */
#define POLYNOMIAL_WIDTH_7BIT 0x04U


/**
 Volume bits used with SOUND_CHANNEL_3_VOLUME as volume
 */
#define VOLUME_MUTE 0x00U
#define VOLUME_100  0x10U
#define VOLUME_50   0x20U
#define VOLUME_25   0x30U


/* **************** Sound Control ***************** */


/** Turns the sound card back on.
 */
#define SOUND_CARD_ON \
  NR52_REG |= 0x80U

/** Turns the sound card off immediatly.
 */
#define SOUND_CARD_OFF \
  NR52_REG &= 0x7FU

/** Sound Channel Status bits
  Logcial OR with SC_* for status of channel
 */
#define SOUND_CHANNEL_STATUS NR52_REG

/** Sound Channel bits.
 A logical OR of these is used in the SOUND_CHANNEL_STATUS value.
*/
#define SC_1 0x01U
#define SC_2 0x02U
#define SC_3 0x04U
#define SC_4 0x08U


#define SOUND_OUT_1_ON(volume) \
  NR50_REG |= 0x08U | volume

#define SOUND_OUT_1_OFF \
  NR50_REG &= 0xF7U

#define SOUND_OUT_2_ON(volume) \
  NR50_REG |= 0x80U | volume << 4

#define SOUND_OUT_2_OFF \
  NR50_REG &= 0x7FU


#define SOUND_CHANNEL_1_OUT(one, two) \
  NR51_REG |= one | two << 4

#define SOUND_CHANNEL_2_OUT(one, two) \
  NR51_REG |= one << 1 | two << 5

#define SOUND_CHANNEL_3_OUT(one, two) \
  NR51_REG |= one << 2 | two << 6

#define SOUND_CHANNEL_4_OUT(one, two) \
  NR51_REG |= one << 3 | two << 7


/* **************** Sound Channel 1 ***************** */

// Sweep time 3 | dir 1 | sweep shift 3
#define SOUND_CHANNEL_1_SWEEP(time, direction, shift) \
  NR10_REG = time << 4 | direction | shift

// Duty 2 | sound length 6
#define SOUND_CHANNEL_1_PATTERN(duty, length) \
  NR11_REG = duty | (63-length)

// volume 4 | dir 1 | sweep 3
#define SOUND_CHANNEL_1_ENVELOPE(volume, direction, sweep) \
  NR12_REG = volume << 4 | direction | sweep

// feq 8
// restart 1 | loop 1 | feq 3
#define SOUND_CHANNEL_1_PLAY(frequency, stop_loop) \
  NR13_REG = frequency; \
  NR14_REG = 0x80U | stop_loop | frequency >> 8

#define SOUND_CHANNEL_1_REPLAY \
  NR14_REG |= 0x80U

/* **************** Sound Channel 2 ***************** */

// Duty 2 | sound length 6
#define SOUND_CHANNEL_2_PATTERN(duty, length) \
  NR12_REG = duty | (63-length)

// volume 4 | dir 1 | sweep 3
#define SOUND_CHANNEL_2_ENVELOPE(volume, direction, sweep) \
  NR22_REG = volume << 4 | direction | sweep

// feq 8
// restart 1 | loop 1 | feq 3
#define SOUND_CHANNEL_2_PLAY(frequency, stop_loop) \
  NR23_REG = frequency; \
  NR24_REG = 0x80U | stop_loop | frequency >> 8

#define SOUND_CHANNEL_2_REPLAY \
  NR24_REG |= 0x80U

/* **************** Sound Channel 3 ***************** */

#define SOUND_CHANNEL_3_ON \
  NR30_REG = 0x80U

#define SOUND_CHANNEL_3_OFF \
  NR30_REG = 0x00U

#define SOUND_CHANNEL_3_LENGTH(length) \
  NR31_REG = 255-length

#define SOUND_CHANNEL_3_VOLUME(volume) \
  NR32_REG = volume

#define SOUND_CHANNEL_3_PLAY(frequency, stop_loop) \
  NR33_REG = frequency; \
  NR34_REG = 0x80U | stop_loop | frequency >> 8

#define SOUND_CHANNEL_3_REPLAY \
  NR34_REG |= 0x80U

/* **************** Sound Channel 4 ***************** */

// Sound length 6
#define SOUND_CHANNEL_4_LENGHT(length) \
  NR41_REG = 63-length

// Volume 4 | dir 1 | sweep 3
#define SOUND_CHANNEL_4_ENVELOPE(volume, direction, sweep) \
  NR42_REG = volume << 4 | direction | sweep

//clock feq 4 | width 1 | div feq 3
#define SOUND_CHANNEL_4_POLYNOMIAL(clock, width, ratio) \
  NR43_REG = clock << 4 | width | ratio

//restart 1 | loop 1
#define SOUND_CHANNEL_4_PLAY(stop_loop) \
  NR44_REG = 0x80U | stop_loop

#define SOUND_CHANNEL_4_REPLAY \
  NR44_REG |= 0x80U


/* ************************************************************ */

enum notes {
	C0, Cd0, D0, Dd0, E0, F0, Fd0, G0, Gd0, A0, Ad0, B0,
	C1, Cd1, D1, Dd1, E1, F1, Fd1, G1, Gd1, A1, Ad1, B1,
	C2, Cd2, D2, Dd2, E2, F2, Fd2, G2, Gd2, A2, Ad2, B2,
	C3, Cd3, D3, Dd3, E3, F3, Fd3, G3, Gd3, A3, Ad3, B3,
	C4, Cd4, D4, Dd4, E4, F4, Fd4, G4, Gd4, A4, Ad4, B4,
	C5, Cd5, D5, Dd5, E5, F5, Fd5, G5, Gd5, A5, Ad5, B5,
	SILENCE, END
};

const UWORD frequencies[] = {
	44, 156, 262, 363, 457, 547, 631, 710, 786, 854, 923, 986,
	1046, 1102, 1155, 1205, 1253, 1297, 1339, 1379, 1417, 1452, 1486, 1517,
	1546, 1575, 1602, 1627, 1650, 1673, 1694, 1714, 1732, 1750, 1767, 1783,
	1798, 1812, 1825, 1837, 1849, 1860, 1871, 1881, 1890, 1899, 1907, 1915,
	1923, 1930, 1936, 1943, 1949, 1954, 1959, 1964, 1969, 1974, 1978, 1982,
	1985, 1988, 1992, 1995, 1998, 2001, 2004, 2006, 2009, 2011, 2013, 2015
};

#endif //end FAST_SOUND

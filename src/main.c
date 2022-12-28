/**
 * @file App to demonstrate PWM-based servomotor control using 2 channels of 1 PWM instance
 */

#include <zephyr/zephyr.h>
#include <zephyr/sys/printk.h>
#include <zephyr/device.h>
#include <zephyr/drivers/pwm.h>

#define STEP PWM_USEC(100)

// Initialise left motor
static const struct pwm_dt_spec motors_l = PWM_DT_SPEC_GET(DT_NODELABEL(motors_l));
static const uint32_t min_pulse_l = DT_PROP(DT_NODELABEL(motors_l), min_pulse);
static const uint32_t max_pulse_l = DT_PROP(DT_NODELABEL(motors_l), max_pulse);
// Initialise right motor
static const struct pwm_dt_spec motors_r = PWM_DT_SPEC_GET(DT_NODELABEL(motors_r));
static const uint32_t min_pulse_r = DT_PROP(DT_NODELABEL(motors_r), min_pulse);
static const uint32_t max_pulse_r = DT_PROP(DT_NODELABEL(motors_r), max_pulse);

#define L_MOTOR_SIGNAL_PIN DT_NODELABEL(pwm0_default);

enum direction {
	DOWN,
	UP,
};

void main(void)
{
	uint32_t pulse_width = max_pulse_l;			
	enum direction dir = UP;
	int ret;

	printk("Servomotor control\n");	// TODO: PRINT PIN NUMBERS FOR L AND R SIGNALS

	if (!device_is_ready(motors_l.dev)) {
		printk("Error: PWM device %s is not ready\n", motors_l.dev->name);
		return;
	}
	if (!device_is_ready(motors_r.dev)) {
		printk("Error: PWM device %s is not ready\n", motors_r.dev->name);
		return;
	}

	while (1) {
		ret = pwm_set_pulse_dt(&motors_l, pulse_width);
		if (ret < 0) {
			printk("Error %d: failed to set pulse width\n", ret);
			return;
		}
		ret = pwm_set_pulse_dt(&motors_r, pulse_width/2);
		if (ret < 0) {
			printk("Error %d: failed to set pulse width\n", ret);
			return;
		}
		
		// Optional variable pulse widths 
		// if (dir == DOWN) {
		// 	if (pulse_width <= min_pulse_l) {
		// 		dir = UP;
		// 		pulse_width = min_pulse_l;
		// 	} else {
		// 		pulse_width -= STEP;
		// 	}
		// } else {
		// 	pulse_width += STEP;
		// 	if (pulse_width >= max_pulse_l) {
		// 		dir = DOWN;
		// 		pulse_width = max_pulse_l;
		// 	}
		// }

		k_sleep(K_MSEC(100));
	}
}

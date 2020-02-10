#include "cy_pdl.h"
#include "cyhal.h"
#include "cybsp.h"
#include "cy_retarget_io.h"

#define INTERRUPT_PRIORITY (7u)
#define CELSIUS (false)
#define FAHRENHEIT (true)
#define TX_PERIOD_30_S (29975100u)  //30 seconds
#define TX_PERIOD_10_S (9991700u)    //10 seconds
#define TX_PERIOD_5_S (499585u)        //5 seconds
#define TX_PERIOD_1_S (999170u)        //1 second
#define LED_INDICATION_TIME (499u)   // milisecond second of LED on

const float multiply_temperature_koefficient = 0.0677568;
const float temperature_offset = 43.65;
const float next_multiply_temperature_koefficient = 1.8;
const float next_temperature_offset = 32.0;

float temp_to_out;

struct cy_stc_rtc_config timeStr;

bool out_config_register = CELSIUS;
bool btn_event = false;
bool tim_event = false;

cyhal_timer_t led_blink_timer;

void handle_error(void) {
	/* Disable all interrupts. */
	__disable_irq();

	CY_ASSERT(0);
}

/*---------------------------------------*/
static float32_t get_temp_data(bool celsius_or_fahrenheit);	                                   //CELSIUS==false, FAHRENHEIT==true
static void timer_init(uint32_t period);		                                                           //timer set configuration data
//parameter [period] the period between transactions
static void gpio_interrupt_handler(void *handler_arg, cyhal_gpio_event_t event);  //Button interrupt handler
static void isr_timer(void *callback_arg, cyhal_timer_event_t event);                       //Timer interrupt handler
static void button_init(void);				                                                                   //Button config and start listener
static void analog_to_digital_hw_init(void);		                                                   //analog to digital hw setup
/*---------------------------------------*/

int main(void) {
	cy_rslt_t result;
	/* Initialize the device and board peripherals */
	result = cybsp_init();
	if (result != CY_RSLT_SUCCESS) {
		CY_ASSERT(0);
	}

	result = cy_retarget_io_init(CYBSP_DEBUG_UART_TX, CYBSP_DEBUG_UART_RX,
	CY_RETARGET_IO_BAUDRATE);
	if (result != CY_RSLT_SUCCESS) {
		handle_error();
	}

	analog_to_digital_hw_init();
	Cy_RTC_Init(&RTC_config);
	timer_init(TX_PERIOD_30_S);
	button_init();

	__enable_irq();

	for (;;) {
		if (btn_event == true) {
			btn_event = false;
			if (out_config_register == CELSIUS) {
				out_config_register = FAHRENHEIT;
				printf("FAHRENHEIT\r\n");
			} else {
				out_config_register = CELSIUS;
				printf("CELSIUS\r\n");
			}
		}

		if (tim_event == true) {
			tim_event = false;
			Cy_RTC_GetDateAndTime(&timeStr);
			temp_to_out = get_temp_data(out_config_register);
			printf("<%02d-%02d-20%02d %02d:%02d:%02d> <%0.1f>\r\n",
					(int) timeStr.date, (int) timeStr.month, (int) timeStr.year,
					(int) timeStr.hour, (int) timeStr.min, (int) timeStr.sec,
					temp_to_out);
			Cy_GPIO_Inv(LED_PORT, LED_PIN);
			Cy_SysLib_Delay(LED_INDICATION_TIME);
			Cy_GPIO_Inv(LED_PORT, LED_PIN);
		}
	}
}

static float32_t get_temp_data(bool celsius_or_fahrenheit) {
	uint16_t adc_data = 0u;
	uint16_t adcstat = 0u;
	float32_t tmp_to_ret = 0.0;

	do {
		adcstat = Cy_SAR_IsEndConversion(ADCT_HW, CY_SAR_SUCCESS);
	} while (CY_SAR_SUCCESS != adcstat);

	adc_data = Cy_SAR_GetResult16(ADCT_HW, CY_SAR_CHAN_POS_PIN_ADDR_1);
	tmp_to_ret = ((float) adc_data) * multiply_temperature_koefficient
			- temperature_offset;
	if (celsius_or_fahrenheit == FAHRENHEIT) {
		tmp_to_ret = tmp_to_ret * next_multiply_temperature_koefficient
				+ next_temperature_offset;
	}
	return tmp_to_ret;
}

static void timer_init(uint32_t period) {
	cy_rslt_t result;
	const cyhal_timer_cfg_t led_blink_timer_cfg = { .compare_value =
	LED_INDICATION_TIME,                       // Timer compare value, not used 
	.period = period,                                      //  Defines the timer period 
	.direction = CYHAL_TIMER_DIR_UP,  // Timer counts up 
	.is_compare = false, 			          //  Don't use compare mode 
	.is_continuous = true, 			          //  Run timer indefinitely 
	.value = 0 						  // Initial value of counter 
	};

	result = cyhal_timer_init(&led_blink_timer, (cyhal_gpio_t) NC, NULL);
	if (result != CY_RSLT_SUCCESS) {
		CY_ASSERT(0);
	}
	cyhal_timer_configure(&led_blink_timer, &led_blink_timer_cfg);
	cyhal_timer_register_callback(&led_blink_timer, isr_timer, NULL);
	cyhal_timer_enable_event(&led_blink_timer, CYHAL_TIMER_IRQ_TERMINAL_COUNT,
			7, true);
	cyhal_timer_start(&led_blink_timer);
}

static void button_init(void) {
	cyhal_gpio_init((cyhal_gpio_t) BTN_HAL_PORT_PIN, BTN_HAL_DIR,
	BTN_HAL_DRIVEMODE, CYBSP_BTN_OFF);					
	cyhal_gpio_register_callback((cyhal_gpio_t) BTN_HAL_PORT_PIN,
			gpio_interrupt_handler, NULL);							
	cyhal_gpio_enable_event((cyhal_gpio_t) BTN_HAL_PORT_PIN,
			CYHAL_GPIO_IRQ_FALL, INTERRUPT_PRIORITY, true);
}

static void gpio_interrupt_handler(void *handler_arg, cyhal_gpio_event_t event) {
	btn_event = true;
}

static void isr_timer(void *callback_arg, cyhal_timer_event_t event) {
	tim_event = true;
}

static void analog_to_digital_hw_init(void) {
	Cy_SysAnalog_Init(&ADC_REF_config);
	Cy_SysAnalog_Enable();
	cy_en_sar_status_t status;
	status = Cy_SAR_Init(ADCT_HW, &ADCT_config);
	if (CY_SAR_SUCCESS == status) {
		Cy_SAR_Enable(ADCT_HW);
		Cy_SAR_StartConvert(ADCT_HW, CY_SAR_START_CONVERT_CONTINUOUS);
	}
}

/* [] END OF FILE */

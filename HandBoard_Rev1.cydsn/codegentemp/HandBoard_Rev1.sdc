# THIS FILE IS AUTOMATICALLY GENERATED
# Project: C:\Users\kratz\OneDrive\Documents\PSoC Creator\Hand_Board_PY2023\HandBoard_Rev1.cydsn\HandBoard_Rev1.cyprj
# Date: Fri, 14 Apr 2023 00:42:40 GMT
#set_units -time ns
create_clock -name {Clock_PWM_1(FFB)} -period 100 -waveform {0 50} [list [get_pins {ClockBlock/ff_div_11}]]
create_clock -name {ADC_SAR_Seq_1_intClock(FFB)} -period 375 -waveform {0 187.5} [list [get_pins {ClockBlock/ff_div_10}]]
create_clock -name {I2C_SCBCLK(FFB)} -period 625 -waveform {0 312.5} [list [get_pins {ClockBlock/ff_div_4}]]
create_clock -name {UART_SCBCLK(FFB)} -period 8675 -waveform {0 4337.5} [list [get_pins {ClockBlock/ff_div_5}]]
create_clock -name {CyRouted1} -period 25 -waveform {0 12.5} [list [get_pins {ClockBlock/dsi_in_0}]]
create_clock -name {CyILO} -period 31250 -waveform {0 15625} [list [get_pins {ClockBlock/ilo}]]
create_clock -name {CyLFClk} -period 31250 -waveform {0 15625} [list [get_pins {ClockBlock/lfclk}]]
create_clock -name {CyExtClk} -period 25 -waveform {0 12.5} [list [get_pins {ClockBlock/ext}]]
create_clock -name {CyIMO} -period 20.833333333333332 -waveform {0 10.4166666666667} [list [get_pins {ClockBlock/imo}]]
create_clock -name {CyHFClk} -period 25 -waveform {0 12.5} [list [get_pins {ClockBlock/hfclk}]]
create_clock -name {CySysClk} -period 25 -waveform {0 12.5} [list [get_pins {ClockBlock/sysclk}]]
create_generated_clock -name {Clock_PWM_1} -source [get_pins {ClockBlock/hfclk}] -edges {1 5 9} [list]
create_generated_clock -name {ADC_SAR_Seq_1_intClock} -source [get_pins {ClockBlock/hfclk}] -edges {1 15 31} [list]
create_generated_clock -name {timer_clock} -source [get_pins {ClockBlock/hfclk}] -edges {1 3 5} [list [get_pins {ClockBlock/udb_div_1}]]
create_generated_clock -name {I2C_SCBCLK} -source [get_pins {ClockBlock/hfclk}] -edges {1 25 51} [list]
create_generated_clock -name {UART_SCBCLK} -source [get_pins {ClockBlock/hfclk}] -edges {1 347 695} [list]
create_generated_clock -name {Clock_2} -source [get_pins {ClockBlock/hfclk}] -edges {1 400001 800001} [list [get_pins {ClockBlock/udb_div_3}]]


# Component constraints for C:\Users\kratz\OneDrive\Documents\PSoC Creator\Hand_Board_PY2023\HandBoard_Rev1.cydsn\TopDesign\TopDesign.cysch
# Project: C:\Users\kratz\OneDrive\Documents\PSoC Creator\Hand_Board_PY2023\HandBoard_Rev1.cydsn\HandBoard_Rev1.cyprj
# Date: Fri, 14 Apr 2023 00:42:31 GMT

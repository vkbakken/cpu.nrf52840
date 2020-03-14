extern int main(void);
extern unsigned int __etext;
extern unsigned int __data_start__;
extern unsigned int __bss_start__;
extern unsigned int __bss_end__;
extern unsigned int __stack;


void _start(void) __attribute__ ((section (".arm.text.start")));


/*CPU EXCEPTIONS*/
void nmi_handler(void);
void hard_fault_handler(void);
void mem_fault_handler(void);
void bus_fault_handler(void);
void usage_fault_handler(void);
void svc_call_handler(void);
void debug_handler(void);
void pend_sv_handler(void);
void systick_handler(void);


/*CPU INTERRUPTS*/
void __attribute__((weak)) power_clock_handler(void);
void __attribute__((weak)) radio_handler(void);
void __attribute__((weak)) uarte0_handler(void);
void __attribute__((weak)) serialbox0_handler(void);
void __attribute__((weak)) serialbox1_handler(void);
void __attribute__((weak)) gpiote_handler(void);
void __attribute__((weak)) saadc_handler(void);
void __attribute__((weak)) timer0_handler(void);
void __attribute__((weak)) timer1_handler(void);
void __attribute__((weak)) timer2_handler(void);
void __attribute__((weak)) rtc0_handler(void);
void __attribute__((weak)) temp_handler(void);
void __attribute__((weak)) rng_handler(void);
void __attribute__((weak)) ecb_handler(void);
void __attribute__((weak)) ccm_aar_handler(void);
void __attribute__((weak)) wdt_handler(void);
void __attribute__((weak)) rtc1_handler(void);
void __attribute__((weak)) qdec_handler(void);
void __attribute__((weak)) lpcomp_handler(void);
void __attribute__((weak)) swi0_egu0_handler(void);
void __attribute__((weak)) swi1_egu1_handler(void);
void __attribute__((weak)) swi2_egu2_handler(void);
void __attribute__((weak)) swi3_egu3_handler(void);
void __attribute__((weak)) swi4_egu4_handler(void);
void __attribute__((weak)) swi5_egu5_handler(void);
void __attribute__((weak)) timer3_handler(void);
void __attribute__((weak)) timer4_handler(void);
void __attribute__((weak)) pwm0_handler(void);
void __attribute__((weak)) pdm_handler(void);
void __attribute__((weak)) mmu_handler(void);
void __attribute__((weak)) pwm1_handler(void);
void __attribute__((weak)) pwm2_handler(void);
void __attribute__((weak)) serialbox2_handler(void);
void __attribute__((weak)) rtc2_handler(void);
void __attribute__((weak)) i2s_handler(void);
void __attribute__((weak)) usbd_handler(void);
void __attribute__((weak)) uarte1_handler(void);
void __attribute__((weak)) qspi_handler(void);
void __attribute__((weak)) cryptocell_handler(void);
void __attribute__((weak)) pwm3_handler(void);
void __attribute__((weak)) spim3_handler(void);



unsigned int __boot_exceptions[] __attribute__ ((section (".arm.text.exception_table"), used)) = {
	[0]=	(unsigned int)&__stack,
    [1]=	(unsigned int)_start,
    [2]=	(unsigned int)nmi_handler,
    [3]=	(unsigned int)hard_fault_handler,
    [4]=	(unsigned int)mem_fault_handler,
    [5]=	(unsigned int)bus_fault_handler,
    [6]=	(unsigned int)usage_fault_handler,
    [7]=	0,
    [8]=	0,
	[9]=	0,
    [10]=	0,
    [11]=	(unsigned int)svc_call_handler,
    [12]=	(unsigned int)debug_handler,
    [13]=	0,
    [14]=	(unsigned int)pend_sv_handler,
    [15]=	(unsigned int)systick_handler,

    [16]=	(unsigned int)power_clock_handler,
	[17]=	(unsigned int)radio_handler,
	[18]=	(unsigned int)uarte0_handler,
	[19]=	(unsigned int)serialbox0_handler,
	[20]=	(unsigned int)serialbox1_handler,
	[21]=	(unsigned int)gpiote_handler,
	[22]=	(unsigned int)saadc_handler,
	[23]=	(unsigned int)timer0_handler,
	[24]=	(unsigned int)timer1_handler,
	[25]=	(unsigned int)timer2_handler,
	[26]=	(unsigned int)rtc0_handler,
	[27]=	(unsigned int)temp_handler,
	[28]=	(unsigned int)rng_handler,
	[29]=	(unsigned int)ecb_handler,
	[30]=	(unsigned int)ccm_aar_handler,
	[31]=	(unsigned int)wdt_handler,
	[32]=	(unsigned int)rtc1_handler,
	[33]=	(unsigned int)qdec_handler,
	[34]=	(unsigned int)lpcomp_handler,
	[35]=	(unsigned int)swi0_egu0_handler,
	[36]=	(unsigned int)swi1_egu1_handler,
	[37]=	(unsigned int)swi2_egu2_handler,
	[38]=	(unsigned int)swi3_egu3_handler,
	[39]=	(unsigned int)swi4_egu4_handler,
	[40]=	(unsigned int)swi5_egu5_handler,
	[41]=	(unsigned int)pwm0_handler,
	[42]=	(unsigned int)pdm_handler,
    [43]=	0,
	[44]=	0,
    [45]=	(unsigned int)mmu_handler,
    [46]=	(unsigned int)pwm1_handler,
    [47]=	(unsigned int)pwm2_handler,
    [48]=	(unsigned int)serialbox2_handler,
    [49]=	(unsigned int)rtc2_handler,
    [50]=	(unsigned int)i2s_handler,
    [51]=	(unsigned int)fpu_handler,
    [52]=	(unsigned int)usbd_handler,
    [53]=	(unsigned int)uarte1_handler,
    [54]=	(unsigned int)qspi_handler,
    [55]=	(unsigned int)cryptocell_handler,
    [56]=	0,
	[57]=	0,
    [58]=	(unsigned int)pwm3_handler,
    [59]=	(unsigned int)spim3_handler,
};


void _start(void)
{
	/*At this point it is assumed that the CPU has been reset, either from power-on
	 * or in some other way. Interrupts and CPU in virgin state assumed.
	 */

	/*Copy initialized data*/
	unsigned int *src = &__etext;
	unsigned int *dst = &__data_start__;
	unsigned int *end = &__bss_start__;

	while (dst != end) {
		*(dst++) = *(src++);
	}

	/*Clear BSS*/
	dst = &__bss_start__;
	end = &__bss_end__;
	while (dst != end) {
		*(dst++) = 0;
	}

	/*Jump to main*/
	main();

	/*If main was ever to return we stop here.*/
	__asm volatile( "cpsid i" ::: "memory" );
	while (1) { ; }
}


void _exit(int status)
{
	while (1) { ; }
}



/********************************************   Exceptions   ********************************/
/********************************************   Exceptions   ********************************/
/********************************************   Exceptions   ********************************/



void __attribute__((weak)) nmi_handler(void)
{
	while (1) {;}
}


void __attribute__((weak)) hard_fault_handler(void)
{
	while (1) {;}
}


void __attribute__((weak)) mem_fault_handler(void)
{
	while (1) {;}
}


void __attribute__((weak)) bus_fault_handler(void)
{
	while (1) {;}
}


void __attribute__((weak)) usage_fault_handler(void)
{
	while (1) {;}
}


void __attribute__((weak)) svc_call_handler(void)
{
	while (1) {;}
}


void __attribute__((weak)) debug_handler(void)
{
	while (1) {;}
}


void __attribute__((weak)) pend_sv_handler(void)
{
	while (1) {;}
}


void __attribute__((weak)) systick_handler(void)
{
	while (1) {;}
}






/********************************************   Interrupts   ********************************/
/********************************************   Interrupts   ********************************/
/********************************************   Interrupts   ********************************/



void __attribute__((weak)) power_clock_handler(void)
{
	while (1) {;}
}


void __attribute__((weak)) radio_handler(void)
{
	while (1) {;}
}


void __attribute__((weak)) uarte0_handler(void)
{
	while (1) {;}
}


void __attribute__((weak)) serialbox0_handler(void)
{
	while (1) {;}
}


void __attribute__((weak)) serialbox1_handler(void)
{
	while (1) {;}
}


void __attribute__((weak)) gpiote_handler(void)
{
	while (1) {;}
}


void __attribute__((weak)) saadc_handler(void)
{
	while (1) {;}
}


void __attribute__((weak)) timer0_handler(void)
{
	while (1) {;}
}


void __attribute__((weak)) timer1_handler(void)
{
	while (1) {;}
}


void __attribute__((weak)) timer2_handler(void)
{
	while (1) {;}
}


void __attribute__((weak)) rtc0_handler(void)
{
	while (1) {;}
}


void __attribute__((weak)) temp_handler(void)
{
	while (1) {;}
}


void __attribute__((weak)) rng_handler(void)
{
	while (1) {;}
}


void __attribute__((weak)) ecb_handler(void)
{
	while (1) {;}
}


void __attribute__((weak)) ccm_aar_handler(void)
{
	while (1) {;}
}


void __attribute__((weak)) wdt_handler(void)
{
	while (1) {;}
}


void __attribute__((weak)) rtc1_handler(void)
{
	while (1) {;}
}


void __attribute__((weak)) qdec_handler(void)
{
	while (1) {;}
}


void __attribute__((weak)) lpcomp_handler(void)
{
	while (1) {;}
}


void __attribute__((weak)) swi0_egu0_handler(void)
{
	while (1) {;}
}


void __attribute__((weak)) swi1_egu1_handler(void)
{
	while (1) {;}
}


void __attribute__((weak)) swi2_egu2_handler(void)
{
	while (1) {;}
}


void __attribute__((weak)) swi3_egu3_handler(void)
{
	while (1) {;}
}


void __attribute__((weak)) swi4_egu4_handler(void)
{
	while (1) {;}
}


void __attribute__((weak)) swi5_egu5_handler(void)
{
	while (1) {;}
}


void __attribute__((weak)) pwm0_handler(void)
{
	while (1) {;}
}


void __attribute__((weak)) pdm_handler(void)
{
	while (1) {;}
}


void __attribute__((weak)) pwm1_handler(void)
{
	while (1) {;}
}


void __attribute__((weak)) pwm2_handler(void)
{
	while (1) {;}
}


void __attribute__((weak)) serialbox2_handler(void)
{
	while (1) {;}
}


void __attribute__((weak)) rtc2_handler(void)
{
	while (1) {;}
}


void __attribute__((weak)) i2s_handler(void)
{
	while (1) {;}
}


void __attribute__((weak)) fpu_handler(void)
{
	while (1) {;}
}


void __attribute__((weak)) usbd_handler(void)
{
	while (1) {;}
}


void __attribute__((weak)) uarte1_handler(void)
{
	while (1) {;}
}


void __attribute__((weak)) qspi_handler(void)
{
	while (1) {;}
}


void __attribute__((weak)) cryptocell_handler(void)
{
	while (1) {;}
}


void __attribute__((weak)) pwm3_handler(void)
{
	while (1) {;}
}


void __attribute__((weak)) spim3_handler(void)
{
	while (1) {;}
}


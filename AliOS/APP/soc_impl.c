/******************************************************************************
 * @file    
 * @author  
 * @version 
 * @date    
 * @brief   ......
 ******************************************************************************
 * @attention
 * 
 * THE EXISTING FIRMWARE IS ONLY FOR REFERENCE, WHICH IS DESIGNED TO PROVIDE
 * CUSTOMERS WITH CODING INFORMATION ABOUT THEIR PRODUCTS SO THEY CAN SAVE
 * TIME. THEREFORE, MINDMOTION SHALL NOT BE LIABLE FOR ANY DIRECT, INDIRECT OR
 * CONSEQUENTIAL DAMAGES ABOUT ANY CLAIMS ARISING OUT OF THE CONTENT OF SUCH
 * HARDWARE AND/OR THE USE OF THE CODING INFORMATION CONTAINED HEREIN IN
 * CONNECTION WITH PRODUCTS MADE BY CUSTOMERS.
******************************************************************************/


/* Define to prevent recursive inclusion ------------------------------------*/
#define __SOC_IMPL_C__


/* Includes -----------------------------------------------------------------*/
#include <k_api.h>
#include <assert.h>
#include <stdio.h>


/* Private typedef ----------------------------------------------------------*/
/* Private define -----------------------------------------------------------*/
/* Private macro ------------------------------------------------------------*/
/* Private variables --------------------------------------------------------*/
/* Private function prototypes ----------------------------------------------*/
/* Private functions --------------------------------------------------------*/
/* Exported variables -------------------------------------------------------*/
/* Exported function prototypes ---------------------------------------------*/


#if (RHINO_CONFIG_MM_TLF > 0)

#if defined (__CC_ARM) /* Keil / armcc */
#define HEAP_BUFFER_SIZE 1024*10
uint8_t g_heap_buf[HEAP_BUFFER_SIZE];
k_mm_region_t g_mm_region[] = {{g_heap_buf, HEAP_BUFFER_SIZE}};
#elif defined (__ICCARM__)/* IAR */
#define HEAP_BUFFER_SIZE 1024*10
uint8_t g_heap_buf[HEAP_BUFFER_SIZE];
k_mm_region_t g_mm_region[] = {{g_heap_buf, HEAP_BUFFER_SIZE}};
#else /* GCC */
extern void         *heap_start;
extern void         *heap_end;
extern void         *heap_len;
/* heap_start and heap_len is set by linkscript(*.ld) */
k_mm_region_t g_mm_region[] = {{(uint8_t*)&heap_start,(size_t)&heap_len}};
#endif

int           g_region_num  = sizeof(g_mm_region)/sizeof(k_mm_region_t);

#endif


/******************************************************************************
 * @brief       
 * @param       
 * @retval      
 * @attention   
******************************************************************************/
size_t soc_get_cur_sp()
{
    size_t sp = 0;
#if defined (__GNUC__)&&!defined(__CC_ARM)
	asm volatile(
        "mov %0,sp\n"
        :"=r"(sp));
#endif
    return sp;
}


/******************************************************************************
 * @brief       
 * @param       
 * @retval      
 * @attention   
******************************************************************************/
static void soc_print_stack()
{
    void    *cur, *end;
    int      i=0;
    int     *p;

    end   = krhino_cur_task_get()->task_stack_base + krhino_cur_task_get()->stack_size;
    cur = (void *)soc_get_cur_sp();
    p = (int*)cur;
    while(p < (int*)end) {
        if(i%4==0) {
            printf("\r\n%08x:",(uint32_t)p);
        }
        printf("%08x ", *p);
        i++;
        p++;
    }
    printf("\r\n");
    return;
}


/******************************************************************************
 * @brief       
 * @param       
 * @retval      
 * @attention   
******************************************************************************/
void soc_err_proc(kstat_t err)
{
    (void)err;
    soc_print_stack();
    assert(0);
}


krhino_err_proc_t g_err_proc = soc_err_proc;

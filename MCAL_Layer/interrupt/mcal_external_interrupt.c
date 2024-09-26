/* 
 * File:   mcal_external_interrupt.c
 * Author: anter
 *
 * Created on August 23, 2024, 1:07 PM
 */

#include "mcal_external_interrupt.h"

static void (*INT0_InterruptHandler)(void) = NULL;
static void (*INT1_InterruptHandler)(void) = NULL;
static void (*INT2_InterruptHandler)(void) = NULL;

static void (*RB4_InterruptHandler_HIGH)(void) = NULL;
static void (*RB4_InterruptHandler_LOW)(void) = NULL;
static void (*RB5_InterruptHandler_HIGH)(void) = NULL;
static void (*RB5_InterruptHandler_LOW)(void) = NULL;
static void (*RB6_InterruptHandler_HIGH)(void) = NULL;
static void (*RB6_InterruptHandler_LOW)(void) = NULL;
static void (*RB7_InterruptHandler_HIGH)(void) = NULL;
static void (*RB7_InterruptHandler_LOW)(void) = NULL;

static Std_ReturnType Interrupt_INTx_Enable(const interrupt_INTx_t *int_obj);
static Std_ReturnType Interrupt_INTx_Disable(const interrupt_INTx_t *int_obj);
static Std_ReturnType Interrupt_INTx_Priority_Init(const interrupt_INTx_t *int_obj);
static Std_ReturnType Interrupt_INTx_Edge_Init(const interrupt_INTx_t *int_obj);
static Std_ReturnType Interrupt_INTx_Pin_Init(const interrupt_INTx_t *int_obj);
static Std_ReturnType Interrupt_INTx_Clear_Flag(const interrupt_INTx_t *int_obj);

static Std_ReturnType INT0_SetInterruptHandler(void(*INT0_InterruptHandler)(void));
static Std_ReturnType INT1_SetInterruptHandler(void(*INT0_InterruptHandler)(void));
static Std_ReturnType INT2_SetInterruptHandler(void(*INT0_InterruptHandler)(void));
static Std_ReturnType Interrupt_INTx_SetInterruptHandler(const interrupt_INTx_t *int_obj);


static Std_ReturnType Interrupt_RBx_Enable(const interrupt_RBx_t *int_obj);
static Std_ReturnType Interrupt_RBx_Disable(const interrupt_RBx_t *int_obj);
static Std_ReturnType Interrupt_RBx_Priority_Init(const interrupt_RBx_t *int_obj);
static Std_ReturnType Interrupt_RBx_Pin_Init(const interrupt_RBx_t *int_obj);

/**
 * 
 * @param int_obj
 * @return 
 */
Std_ReturnType Interrupt_INTx_Init(const interrupt_INTx_t *int_obj){
    Std_ReturnType ret = E_NOT_OK;
    if(NULL == int_obj){
        ret = E_NOT_OK; /* NULL pointer detected */
    }
    else{
        /* Disable the External interrupt */
        ret = Interrupt_INTx_Disable(int_obj);
        /* Clear Interrupt Flag : External interrupt did not occur */
        ret |= Interrupt_INTx_Clear_Flag(int_obj);
        /* Configure External interrupt edge */
        ret |= Interrupt_INTx_Edge_Init(int_obj);
        /* Configure External interrupt  priority */
        #ifdef INTERRUPT_PRIORITY_LEVELS_ENABLE
        ret |= Interrupt_INTx_Priority_Init(int_obj);
        #endif 
        /* Configure External interrupt I/O pin */
        ret |= Interrupt_INTx_Pin_Init(int_obj);
        /* Configure Default Interrupt CallBack */
        ret |= Interrupt_INTx_SetInterruptHandler(int_obj);
        /* Enable the External interrupt */
        ret |= Interrupt_INTx_Enable(int_obj);
    }
    return ret;
}

void INT0_ISR(void){
    /* the INT0 external interrupt occurred (must be cleared in software)*/
    EXT_INT0_InterruptFlagClear();
   
    
    /* code */
    
    /* Callback function gets called every time this ISR executes*/
    if (INT0_InterruptHandler)
    {
        INT0_InterruptHandler();
    }
    
}

void INT1_ISR(void){
    /* the INT1 external interrupt occurred (must be cleared in software)*/
    EXT_INT1_InterruptFlagClear();
    
    /* code */
    
    /* Callback function gets called every time this ISR executes*/
    if (INT1_InterruptHandler)
    {
        INT1_InterruptHandler();
    }
}

void INT2_ISR(void){
    /* the INT2 external interrupt occurred (must be cleared in software)*/
    EXT_INT2_InterruptFlagClear();
    
    /* code */
    
    /* Callback function gets called every time this ISR executes*/
    if (INT2_InterruptHandler)
    {
        INT2_InterruptHandler();
    }
}

void RB4_ISR(uint8 RB4_source){
    /* the RB4 external interrupt occurred (must be cleared in software)*/
    EXT_RBx_InterruptFlagClear();
    /* code */
    
    /* Callback function gets called every time this ISR executes*/
    if (0 == RB4_source)
    {
        if (RB4_InterruptHandler_LOW){ RB4_InterruptHandler_LOW();}
        else { /* Nothing */ }
    }
    else if (1 == RB4_source)
    {
        if (RB4_InterruptHandler_HIGH){ RB4_InterruptHandler_HIGH();}
        else { /* Nothing */ }
    }
}

void RB5_ISR(uint8 RB5_source){
    /* the RB5 external interrupt occurred (must be cleared in software)*/
    EXT_RBx_InterruptFlagClear();
    /* code */
    
    /* Callback function gets called every time this ISR executes*/
    if (0 == RB5_source)
    {
        if (RB5_InterruptHandler_LOW){ RB5_InterruptHandler_LOW();}
        else { /* Nothing */ }
    }
    else if (1 == RB5_source)
    {
        if (RB5_InterruptHandler_HIGH){ RB5_InterruptHandler_HIGH();}
        else { /* Nothing */ }
    }
}

void RB6_ISR(uint8 RB6_source){
    /* the RB6 external interrupt occurred (must be cleared in software)*/
    EXT_RBx_InterruptFlagClear();
    
    /* code */
   
    /* Callback function gets called every time this ISR executes*/
    if (0 == RB6_source)
    {
        if (RB6_InterruptHandler_LOW){ RB6_InterruptHandler_LOW();}
        else { /* Nothing */ }
    }
    else if (1 == RB6_source)
    {
        if (RB6_InterruptHandler_HIGH){ RB6_InterruptHandler_HIGH();}
        else { /* Nothing */ }
    }
}
void RB7_ISR(uint8 RB7_source){
    /* the RB7 external interrupt occurred (must be cleared in software)*/
    EXT_RBx_InterruptFlagClear();
    
    /* code */
    
    /* Callback function gets called every time this ISR executes*/
    if (0 == RB7_source)
    {
        if (RB7_InterruptHandler_LOW){ RB7_InterruptHandler_LOW();}
        else { /* Nothing */ }
    }
    else if (1 == RB7_source)
    {
        if (RB7_InterruptHandler_HIGH){ RB7_InterruptHandler_HIGH();}
        else { /* Nothing */ }
    }
}
    


/**
 * 
 * @param int_obj
 * @return 
 */
Std_ReturnType Interrupt_INTx_DeInit(const interrupt_INTx_t *int_obj){
    Std_ReturnType ret = E_NOT_OK;
    if(NULL == int_obj){
        ret = E_NOT_OK;
    }
    else{
        ret = Interrupt_INTx_Disable(int_obj);
    }
    return ret;
}


/**
 * 
 * @param int_obj
 * @return 
 */
Std_ReturnType Interrupt_RBx_Init(const interrupt_RBx_t *int_obj){
    Std_ReturnType ret = E_OK;
    if (NULL == int_obj)
    {
        ret = E_NOT_OK;
    }
    else
    {
        /* Disable the External interrupt */
        EXT_RBx_InterruptDisable();
        
        /* Clear Interrupt Flag : External interrupt did not occur */
        EXT_RBx_InterruptFlagClear();
        /* Configure External interrupt  priority */
#ifdef INTERRUPT_PRIORITY_LEVELS_ENABLE
        INTERRUPT_PriorityLevelsEnable();
        
        if(INTERRUPT_LOW_PRIORITY == int_obj->priority){
            INTERRUPT_GlobalInterruprLowEnable();
            EXT_RBx_Priority_Low();
        }
        else if(INTERRUPT_HIGH_PRIORITY == int_obj->priority){ 
            INTERRUPT_GlobalInterruprHighEnable();
            EXT_RBx_Priority_High();
        }
        else{ /* Nothing */ }
#else
                INTERRUPT_GlobalInterruprEnable();
                INTERRUPT_PeripheralInterruptEnable();
#endif
        /* Configure External interrupt I/O pin */
        ret = gpio_pin_direction_intialize(&(int_obj->mcu_pin));
        /* Configure Default Interrupt CallBack */
        switch (int_obj->mcu_pin.pin)
        {
            case GPIO_PIN4 :
                RB4_InterruptHandler_LOW = int_obj->EXT_InterruptHandler_LOW;
                RB4_InterruptHandler_HIGH = int_obj->EXT_InterruptHandler_HIGH;
                break;
            case GPIO_PIN5 :
                RB5_InterruptHandler_LOW = int_obj->EXT_InterruptHandler_LOW;
                RB5_InterruptHandler_HIGH = int_obj->EXT_InterruptHandler_HIGH;
                break;
            case GPIO_PIN6 :
                RB6_InterruptHandler_LOW = int_obj->EXT_InterruptHandler_LOW;
                RB6_InterruptHandler_HIGH = int_obj->EXT_InterruptHandler_HIGH;
                break;
            case GPIO_PIN7 :
                RB7_InterruptHandler_LOW = int_obj->EXT_InterruptHandler_LOW;
                RB7_InterruptHandler_HIGH = int_obj->EXT_InterruptHandler_HIGH;
                break;
            default : 
                ret = E_NOT_OK;
                break;
        }
        /* Enable the External interrupt */
        EXT_RBx_InterruptEnable();
        
    }
    return ret;
}

/**
 * 
 * @param int_obj
 * @return 
 */
Std_ReturnType Interrupt_RBx_DeInit(const interrupt_RBx_t *int_obj){
    Std_ReturnType ret = E_OK;
    if (NULL == int_obj)
    {
        ret = E_NOT_OK;
    }
    else
    {
        
    }
    return ret;
}

/**
 * 
 * @param int_obj
 * @return 
 */
static Std_ReturnType Interrupt_INTx_Enable(const interrupt_INTx_t *int_obj){
    Std_ReturnType ret = E_NOT_OK;
    if(NULL == int_obj){
        ret = E_NOT_OK;
    }
    else{
        switch(int_obj->source){
            case INTERRUPT_EXTERNAL_INT0 : 
#ifdef INTERRUPT_PRIORITY_LEVELS_ENABLE
                INTERRUPT_PriorityLevelsEnable();
                INTERRUPT_GlobalInterruprHighEnable();
#else
                INTERRUPT_GlobalInterruprEnable();
                INTERRUPT_PeripheralInterruptEnable();
#endif
                EXT_INT0_InterruptEnable();
                break;
            case INTERRUPT_EXTERNAL_INT1 :
#ifdef INTERRUPT_PRIORITY_LEVELS_ENABLE
                INTERRUPT_PriorityLevelsEnable();
                if(INTERRUPT_LOW_PRIORITY == int_obj->priority){
                    INTERRUPT_GlobalInterruprLowEnable();
                }
                else if(INTERRUPT_HIGH_PRIORITY == int_obj->priority){ 
                    INTERRUPT_GlobalInterruprHighEnable();
                }
                else{ /* Nothing */ }
#else
                INTERRUPT_GlobalInterruprEnable();
                INTERRUPT_PeripheralInterruptEnable();
#endif
                EXT_INT1_InterruptEnable();
                break;
            case INTERRUPT_EXTERNAL_INT2 :
#ifdef INTERRUPT_PRIORITY_LEVELS_ENABLE
                INTERRUPT_PriorityLevelsEnable();
                if(INTERRUPT_LOW_PRIORITY == int_obj->priority){
                    INTERRUPT_GlobalInterruprLowEnable();
                }
                else if(INTERRUPT_HIGH_PRIORITY == int_obj->priority){ 
                    INTERRUPT_GlobalInterruprHighEnable();
                }
                else{ /* Nothing */ }
#else
                INTERRUPT_GlobalInterruprEnable();
                INTERRUPT_PeripheralInterruptEnable();
#endif
                EXT_INT2_InterruptEnable();
                break;
            default : ret = E_NOT_OK;
        }
    }
    return ret;
}

/**
 * 
 * @param int_obj
 * @return 
 */
static Std_ReturnType Interrupt_INTx_Disable(const interrupt_INTx_t *int_obj){
    Std_ReturnType ret = E_NOT_OK;
    if(NULL == int_obj){
        ret = E_NOT_OK;
    }
    else{
        switch(int_obj->source){
            case INTERRUPT_EXTERNAL_INT0 : 
                EXT_INT0_InterruptDisable(); /* Disable the INT0 external interrupt */
                break;
            case INTERRUPT_EXTERNAL_INT1 : 
                EXT_INT1_InterruptDisable(); /* Disable the INT1 external interrupt */
                break;
            case INTERRUPT_EXTERNAL_INT2 : 
                EXT_INT2_InterruptDisable(); /* Disable the INT2 external interrupt */
                break;
            default : ret = E_NOT_OK;
        }
    }
    return ret;
}


/**
 * 
 * @param int_obj
 * @return 
 */
#ifdef INTERRUPT_PRIORITY_LEVELS_ENABLE 
static Std_ReturnType Interrupt_INTx_Priority_Init(const interrupt_INTx_t *int_obj){
    Std_ReturnType ret = E_NOT_OK;
    if(NULL == int_obj){
        ret = E_NOT_OK;
    }
    else{
        switch(int_obj->source){
            case INTERRUPT_EXTERNAL_INT1 : 
                if(INTERRUPT_LOW_PRIORITY == int_obj->priority){ EXT_INT1_LowPrioritySet(); }
                else if(INTERRUPT_HIGH_PRIORITY == int_obj->priority){ EXT_INT1_HighPrioritySet(); }
                else{ /* Nothing */ }
                break;
            case INTERRUPT_EXTERNAL_INT2 : 
                if(INTERRUPT_LOW_PRIORITY == int_obj->priority){ EXT_INT2_LowPrioritySet(); }
                else if(INTERRUPT_HIGH_PRIORITY == int_obj->priority){ EXT_INT2_HighPrioritySet(); }
                else{ /* Nothing */ }
                break;
            default : ret = E_NOT_OK;
        }
    }
    return ret;
}
#endif

/**
 * 
 * @param int_obj
 * @return 
 */
static Std_ReturnType Interrupt_INTx_Edge_Init(const interrupt_INTx_t *int_obj){
    Std_ReturnType ret = E_NOT_OK;
    if(NULL == int_obj){
        ret = E_NOT_OK;
    }
    else{
        switch(int_obj->source){
            case INTERRUPT_EXTERNAL_INT0 : 
                if(INTERRUPT_FALLING_EDGE == int_obj->edge){ EXT_INT0_FallingEdgeSet(); }
                else if(INTERRUPT_RISING_EDGE == int_obj->edge){ EXT_INT0_RisingEdgeSet(); }
                else{ /* Nothing */ } 
                break;
            case INTERRUPT_EXTERNAL_INT1 : 
                if(INTERRUPT_FALLING_EDGE == int_obj->edge){ EXT_INT1_FallingEdgeSet(); }
                else if(INTERRUPT_RISING_EDGE == int_obj->edge){ EXT_INT1_RisingEdgeSet(); }
                else{ /* Nothing */ } 
                break;
            case INTERRUPT_EXTERNAL_INT2 : 
                if(INTERRUPT_FALLING_EDGE == int_obj->edge){ EXT_INT2_FallingEdgeSet(); }
                else if(INTERRUPT_RISING_EDGE == int_obj->edge){ EXT_INT2_RisingEdgeSet(); }
                else{ /* Nothing */ }
                break;
            default : ret = E_NOT_OK;
        }
    }
    return ret;
}


/**
 * 
 * @param int_obj
 * @return 
 */
static Std_ReturnType Interrupt_INTx_Pin_Init(const interrupt_INTx_t *int_obj){
    Std_ReturnType ret = E_NOT_OK;
    if(NULL == int_obj){
        ret = E_NOT_OK;
    }
    else{
        /* Initialize the MCU Pin for INTx with the needed configurations */
        ret = gpio_pin_direction_intialize(&(int_obj->mcu_pin));
    }
    return ret;
}

/**
 * 
 * @param int_obj
 * @return 
 */
static Std_ReturnType Interrupt_INTx_Clear_Flag(const interrupt_INTx_t *int_obj){
    Std_ReturnType ret = E_NOT_OK;
    if(NULL == int_obj){
        ret = E_NOT_OK;
    }
    else{
        switch(int_obj->source){
            case INTERRUPT_EXTERNAL_INT0 : 
                EXT_INT0_InterruptFlagClear(); /* Clears the interrupt flag for the external interrupt, INT0 */
                break;
            case INTERRUPT_EXTERNAL_INT1 : 
                EXT_INT1_InterruptFlagClear(); /* Clears the interrupt flag for the external interrupt, INT1 */ 
                break;
            case INTERRUPT_EXTERNAL_INT2 : 
                EXT_INT2_InterruptFlagClear(); /* Clears the interrupt flag for the external interrupt, INT2 */
                break;
            default : ret = E_NOT_OK;
        }
    }
    return ret;
}

static Std_ReturnType INT0_SetInterruptHandler(void(*InterruptHandler)(void)){
    Std_ReturnType ret = E_OK;
    if (NULL == InterruptHandler)
    {
        ret = E_NOT_OK;
    }
    else
    {
        INT0_InterruptHandler = InterruptHandler;
    }
    return ret;
}
static Std_ReturnType INT1_SetInterruptHandler(void(*InterruptHandler)(void)){
    Std_ReturnType ret = E_OK;
    if (NULL == InterruptHandler)
    {
        ret = E_NOT_OK;
    }
    else
    {
        INT1_InterruptHandler = InterruptHandler;
    }
    return ret;
}
static Std_ReturnType INT2_SetInterruptHandler(void(*InterruptHandler)(void)){
    Std_ReturnType ret = E_OK;
    if (NULL == InterruptHandler)
    {
        ret = E_NOT_OK;
    }
    else
    {
        INT2_InterruptHandler = InterruptHandler;
    }
    return ret;
}
static Std_ReturnType Interrupt_INTx_SetInterruptHandler(const interrupt_INTx_t *int_obj){
    Std_ReturnType ret = E_OK;
    if (NULL == int_obj)
    {
        ret = E_NOT_OK;
    }
    else
    {
        switch(int_obj->source){
            case INTERRUPT_EXTERNAL_INT0 : 
                ret = INT0_SetInterruptHandler(int_obj->EXT_InterruptHandler);
                break;
            case INTERRUPT_EXTERNAL_INT1 : 
                ret = INT1_SetInterruptHandler(int_obj->EXT_InterruptHandler);
                break;
            case INTERRUPT_EXTERNAL_INT2 : 
                ret = INT2_SetInterruptHandler(int_obj->EXT_InterruptHandler);
                break;
            default : ret = E_NOT_OK;
        }
    }
    return ret;
}


ifndef MODULE_STM32F2_LOW_LEVEL_BY_ST_OPTIMIZATION
	MODULE_STM32F2_LOW_LEVEL_BY_ST_OPTIMIZATION = -g3 -O0
endif

MODULE_STM32F2_LOW_LEVEL_BY_ST_C_FILE				:= $(shell find module_stm32f2_low_level_by_st/ -maxdepth 3 -type f -name "*.c" )
MODULE_STM32F2_LOW_LEVEL_BY_ST_DIR					:= $(shell find module_stm32f2_low_level_by_st/ -maxdepth 3 -type d -name "*" )
MODULE_STM32F2_LOW_LEVEL_BY_ST_PATH					:= $(addprefix -I, $(MODULE_STM32F2_LOW_LEVEL_BY_ST_DIR))
MODULE_STM32F2_LOW_LEVEL_BY_ST_OBJ_FILE				:= $(addprefix build/obj/, $(MODULE_STM32F2_LOW_LEVEL_BY_ST_C_FILE))
MODULE_STM32F2_LOW_LEVEL_BY_ST_OBJ_FILE				:= $(patsubst %.c, %.o, $(MODULE_STM32F2_LOW_LEVEL_BY_ST_OBJ_FILE))
MODULE_STM32F2_LOW_LEVEL_BY_ST_OBJ_FILE				+= module_stm32f2_low_level_by_st/CMSIS/Device/Source/startup_stm32f205xx.s

build/obj/module_stm32f2_low_level_by_st/%.o:	module_stm32f2_low_level_by_st/%.c
	@echo [CC] $<
	@mkdir -p $(dir $@)
	@$(CC) $(C_FLAGS) $(DEFINE_PROJ) $(USER_CFG_PATH) $(MODULE_STM32F2_LOW_LEVEL_BY_ST_PATH) $(MODULE_STM32F2_LOW_LEVEL_BY_ST_OPTIMIZATION) -c $< -o $@

build/obj/module_stm32f2_low_level_by_st/%.o:	module_stm32f2_low_level_by_st/%.s
	@echo [AS] $<
	@mkdir -p $(dir $@)
	@$(AS) $(MODULE_STM32F2_LOW_LEVEL_BY_ST_PATH) $(DEFINE_PROJ) $(USER_CFG_PATH) $(MODULE_STM32F2_LOW_LEVEL_BY_ST_OPTIMIZATION) -c $< -o $@


# Добавляем к общим переменным проекта.
PROJECT_PATH			+= $(MODULE_STM32F2_LOW_LEVEL_BY_ST_PATH)
PROJECT_OBJ_FILE		+= $(MODULE_STM32F2_LOW_LEVEL_BY_ST_OBJ_FILE)
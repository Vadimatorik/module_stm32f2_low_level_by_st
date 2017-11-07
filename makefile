ifndef MODULE_STM32F2_LOW_LEVEL_BY_ST_OPTIMIZATION
	MODULE_STM32F2_LOW_LEVEL_BY_ST_OPTIMIZATION = -g3 -O0
endif

MODULE_STM32F2_LOW_LEVEL_BY_ST_C_FILE				:= $(shell find module_stm32f2_low_level_by_st/ -maxdepth 10 -type f -name "*.c" )
MODULE_STM32F2_LOW_LEVEL_BY_ST_CPP_FILE				:= $(shell find module_stm32f2_low_level_by_st/ -maxdepth 10 -type f -name "*.cpp" )
MODULE_STM32F2_LOW_LEVEL_BY_ST_DIR					:= $(shell find module_stm32f2_low_level_by_st/ -maxdepth 10 -type d -name "*" )
MODULE_STM32F2_LOW_LEVEL_BY_ST_DIR					+= $(shell find module_mc_hardware_interfaces/ -maxdepth 10 -type d -name "*" )
MODULE_STM32F2_LOW_LEVEL_BY_ST_DIR					+= $(shell find module_freertos_for_stm32f2/ -maxdepth 10 -type d -name "*" )

MODULE_STM32F2_LOW_LEVEL_BY_ST_PATH					:= $(addprefix -I, $(MODULE_STM32F2_LOW_LEVEL_BY_ST_DIR))

MODULE_STM32F2_LOW_LEVEL_BY_ST_OBJ_FILE				:= $(addprefix build/obj/, $(MODULE_STM32F2_LOW_LEVEL_BY_ST_C_FILE))
MODULE_STM32F2_LOW_LEVEL_BY_ST_OBJ_FILE				+= $(addprefix build/obj/, $(MODULE_STM32F2_LOW_LEVEL_BY_ST_CPP_FILE))
MODULE_STM32F2_LOW_LEVEL_BY_ST_OBJ_FILE				:= $(patsubst %.c, %.o, $(MODULE_STM32F2_LOW_LEVEL_BY_ST_OBJ_FILE))
MODULE_STM32F2_LOW_LEVEL_BY_ST_OBJ_FILE				:= $(patsubst %.cpp, %.o, $(MODULE_STM32F2_LOW_LEVEL_BY_ST_OBJ_FILE))
MODULE_STM32F2_LOW_LEVEL_BY_ST_OBJ_FILE				+= module_stm32f2_low_level_by_st/CMSIS/Device/Source/startup_stm32f205xx.s

build/obj/module_stm32f2_low_level_by_st/%.o:	module_stm32f2_low_level_by_st/%.c
	@echo [CC] $<
	@mkdir -p $(dir $@)
	$(CC) $(C_FLAGS) $(DEFINE_PROJ) $(USER_CFG_PATH) $(MODULE_STM32F2_LOW_LEVEL_BY_ST_PATH) $(MODULE_STM32F2_LOW_LEVEL_BY_ST_OPTIMIZATION) -c $< -o $@


build/obj/module_stm32f2_low_level_by_st/%.o:	module_stm32f2_low_level_by_st/%.cpp
	@echo [CPP] $<
	@mkdir -p $(dir $@)
	@$(CPP) $(CPP_FLAGS) $(DEFINE_PROJ) $(USER_CFG_PATH) $(MODULE_STM32F2_LOW_LEVEL_BY_ST_PATH) $(MODULE_STM32F2_LOW_LEVEL_BY_ST_OPTIMIZATION) -c $< -o $@

build/obj/module_stm32f2_low_level_by_st/%.o:	module_stm32f2_low_level_by_st/%.s
	@echo [AS] $<
	@mkdir -p $(dir $@)
	@$(AS) $(DEFINE_PROJ) $(USER_CFG_PATH) $(MODULE_STM32F2_LOW_LEVEL_BY_ST_PATH)  $(MODULE_STM32F2_LOW_LEVEL_BY_ST_OPTIMIZATION) -c $< -o $@


# Добавляем к общим переменным проекта.
PROJECT_PATH			+= $(MODULE_STM32F2_LOW_LEVEL_BY_ST_PATH)
PROJECT_OBJ_FILE		+= $(MODULE_STM32F2_LOW_LEVEL_BY_ST_OBJ_FILE)
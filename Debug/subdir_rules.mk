################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Each subdirectory must supply rules for building sources it contributes
cal_abcd.obj: ../cal_abcd.sa $(GEN_OPTS) $(GEN_HDRS)
	@echo 'Building file: $<'
	@echo 'Invoking: C6000 Compiler'
	"C:/ti/ccsv5/tools/compiler/c6000_7.4.4/bin/cl6x" -mv6400 --abi=coffabi -O3 -g --include_path="C:/ti/ccsv5/tools/compiler/c6000_7.4.4/include" --define=dm642 --display_error_number --diag_warning=225 --diag_wrap=off --preproc_with_compile --preproc_dependency="cal_abcd.pp" $(GEN_OPTS__FLAG) "$<"
	@echo 'Finished building: $<'
	@echo ' '

cal_bilinear.obj: ../cal_bilinear.sa $(GEN_OPTS) $(GEN_HDRS)
	@echo 'Building file: $<'
	@echo 'Invoking: C6000 Compiler'
	"C:/ti/ccsv5/tools/compiler/c6000_7.4.4/bin/cl6x" -mv6400 --abi=coffabi -O3 -g --include_path="C:/ti/ccsv5/tools/compiler/c6000_7.4.4/include" --define=dm642 --display_error_number --diag_warning=225 --diag_wrap=off --preproc_with_compile --preproc_dependency="cal_bilinear.pp" $(GEN_OPTS__FLAG) "$<"
	@echo 'Finished building: $<'
	@echo ' '

func.obj: ../func.c $(GEN_OPTS) $(GEN_HDRS)
	@echo 'Building file: $<'
	@echo 'Invoking: C6000 Compiler'
	"C:/ti/ccsv5/tools/compiler/c6000_7.4.4/bin/cl6x" -mv6400 --abi=coffabi -O3 -g --include_path="C:/ti/ccsv5/tools/compiler/c6000_7.4.4/include" --define=dm642 --display_error_number --diag_warning=225 --diag_wrap=off --preproc_with_compile --preproc_dependency="func.pp" $(GEN_OPTS__FLAG) "$<"
	@echo 'Finished building: $<'
	@echo ' '

main.obj: ../main.c $(GEN_OPTS) $(GEN_HDRS)
	@echo 'Building file: $<'
	@echo 'Invoking: C6000 Compiler'
	"C:/ti/ccsv5/tools/compiler/c6000_7.4.4/bin/cl6x" -mv6400 --abi=coffabi -O3 -g --include_path="C:/ti/ccsv5/tools/compiler/c6000_7.4.4/include" --define=dm642 --display_error_number --diag_warning=225 --diag_wrap=off --preproc_with_compile --preproc_dependency="main.pp" $(GEN_OPTS__FLAG) "$<"
	@echo 'Finished building: $<'
	@echo ' '

single_test.obj: ../single_test.sa $(GEN_OPTS) $(GEN_HDRS)
	@echo 'Building file: $<'
	@echo 'Invoking: C6000 Compiler'
	"C:/ti/ccsv5/tools/compiler/c6000_7.4.4/bin/cl6x" -mv6400 --abi=coffabi -O3 -g --include_path="C:/ti/ccsv5/tools/compiler/c6000_7.4.4/include" --define=dm642 --display_error_number --diag_warning=225 --diag_wrap=off --preproc_with_compile --preproc_dependency="single_test.pp" $(GEN_OPTS__FLAG) "$<"
	@echo 'Finished building: $<'
	@echo ' '

ufloat2int.obj: ../ufloat2int.sa $(GEN_OPTS) $(GEN_HDRS)
	@echo 'Building file: $<'
	@echo 'Invoking: C6000 Compiler'
	"C:/ti/ccsv5/tools/compiler/c6000_7.4.4/bin/cl6x" -mv6400 --abi=coffabi -O3 -g --include_path="C:/ti/ccsv5/tools/compiler/c6000_7.4.4/include" --define=dm642 --display_error_number --diag_warning=225 --diag_wrap=off --preproc_with_compile --preproc_dependency="ufloat2int.pp" $(GEN_OPTS__FLAG) "$<"
	@echo 'Finished building: $<'
	@echo ' '



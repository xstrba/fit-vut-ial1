OUT=outputs
ADV_OUT=adv_$(OUT)
DLR=$

# basic tests #########################################################
test: t_c202 t_c204 t_c206

t_c202:
	cd c202 && make && ./c202-test

t_c204:
	cd c204 && make && ./c204-test

t_c206:
	cd c206 && make && ./c206-test

compare: $(OUT) cmp_c202 cmp_c204 cmp_c206

$(OUT):
	@mkdir $(OUT)

cmp_c202:
	@make t_c202 | sed -n '/^C202/,$(DLR)p' | sed '1,/The End of Basic Tests/!d' > $(OUT)/c202.output
	@echo Beginning of c202 diff
	@diff $(OUT)/c202.output template-$(OUT)/c202-test.output
	@echo End of c202 diff

cmp_c204:
	@make t_c204 | sed -n '/^C204/,$(DLR)p' | sed '1,/The End of Basic Tests/!d' > $(OUT)/c204.output
	@echo Beginning of c204 diff
	@diff $(OUT)/c204.output template-$(OUT)/c204-test.output
	@echo End of c204 diff

cmp_c206:
	@make t_c206 | sed -n '/^Dvousměrně vázaný/,$(DLR)p' | sed '1,/konec příkladu c206/!d' > $(OUT)/c206.output
	@echo Beginning of c206 diff
	@diff $(OUT)/c206.output template-$(OUT)/c206-test.output
	@echo End of c206 diff

# advanced tests ######################################################

test_adv: tadv_c202 tadv_c204 tadv_c206

tadv_c202:
	cd c202 && make advanced && ./c202-advanced-test

tadv_c204:
	cd c204 && make advanced && ./c204-advanced-test

tadv_c206:
	cd c206 && make advanced && ./c206-advanced-test

compare_adv: $(ADV_OUT) cmpadv_c202 cmpadv_c204 cmpadv_c206

$(ADV_OUT):
	@mkdir $(ADV_OUT)

cmpadv_c202:
	@make tadv_c202 | sed -n '/^C202/,$(DLR)p' | sed '1,/End of Advanced Tests/!d' > $(ADV_OUT)/c202.output
	@echo Beginning of c202 diff
	@diff $(ADV_OUT)/c202.output template-$(ADV_OUT)/c202/c202-advanced-test.output
	@echo End of c202 diff

cmpadv_c204:
	@make tadv_c204 | sed -n '/^C204/,$(DLR)p' | sed '1,/End of Advanced Tests/!d' > $(ADV_OUT)/c204.output
	@echo Beginning of c204 diff
	@diff $(ADV_OUT)/c204.output template-$(ADV_OUT)/c204/c204-advanced-test.output
	@echo End of c204 diff

cmpadv_c206:
	@make tadv_c206 | sed -n '/^Double Linked List/,$(DLR)p' | sed '1,/End of advanced test/!d' > $(ADV_OUT)/c206.output
	@echo Beginning of c206 diff
	@diff $(ADV_OUT)/c206.output template-$(ADV_OUT)/c206/c206-advanced-test.output
	@echo End of c206 diffff

clean:
	rm -rf $(ADV_OUT) $(OUT)
	cd c202 && make clean
	cd c204 && make clean
	cd c206 && make clean
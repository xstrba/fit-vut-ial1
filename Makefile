test: t_c202 t_c204 t_c206

t_c202:
	cd c202 && make && ./c202-test

t_c204:
	cd c204 && make && ./c204-test

t_c206:
	cd c206 && make && ./c206-test
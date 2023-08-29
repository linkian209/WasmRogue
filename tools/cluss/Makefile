Q=@

all:
	$(Q)$(MAKE) --no-print-directory -C mibic
	$(Q)$(MAKE) --no-print-directory -C assembler
	$(Q)cp frontend/cluss cluss

clean:
	$(Q)$(MAKE) --no-print-directory -C mibic     clean
	$(Q)$(MAKE) --no-print-directory -C assembler clean
	$(Q)rm -f cluss
tidy:
	$(Q)$(MAKE) --no-print-directory -C mibic     tidy
	$(Q)$(MAKE) --no-print-directory -C assembler tidy
	$(Q)rm -f cluss


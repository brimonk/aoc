all:
	$(MAKE) -C 2023
	$(MAKE) -C 2024

clean:
	$(MAKE) -C 2023 clean
	$(MAKE) -C 2024 clean

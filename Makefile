CC=gcc
PREFIX=/usr/local
SERVICE_DIR=/etc/systemd/system
all: scanmemd
scanmemd: main.c
	$(CC) main.c -o scanmemd
clean:
	rm -f scanmemd
install:
	make
	sed -i "s|\$$HOME|/home/$(USER)|g" scanmemd.service 
	touch "/home/$(USER)/.cache/scanmem"
	sudo chmod a+rw "/home/$(USER)/.cache/scanmem"
	sudo install -m 755 scanmemd $(PREFIX)/bin
	sudo install -m 644 scanmemd.service $(SERVICE_DIR)
	sudo systemctl enable scanmemd.service
	sudo systemctl start scanmemd.service
	sudo systemctl daemon-reload
	rm -f scanmemd
uninstall:
	sudo systemctl disable scanmemd.service
	sudo rm -f $(PREFIX)/bin/scanmemd
	sudo rm -f $(SERVICE_DIR)/scanmemd.service
	sudo systemctl daemon-reload

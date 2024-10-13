compile:
	gcc -o bosh main.c helpers.c

clean:
	sudo cp ./bosh /usr/bin/
	rm ./bosh

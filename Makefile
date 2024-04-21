build:
	gcc main.c lanPartyLib.c -o lanParty -lm -g
clean:
	rm -f lanParty
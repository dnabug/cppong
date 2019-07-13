CC = clang++
CFLAGS = -std=c++11
HEADERS = pong-client/*.hpp

CLIENTSRCDIR = pong-client
CLIENTSRC = $(CLIENTSRCDIR)/main.cpp $(CLIENTSRCDIR)/display.cpp \
			$(CLIENTSRCDIR)/game.cpp $(CLIENTSRCDIR)/draw.cpp
CLIENTOBJ = $(CLIENTSRC:.cpp=.o)
CLIENTLIB = -lSDL2

%.o: %.cpp $(HEADERS)
	$(CC) -c $(CFLAGS) $< -o $@

pongclient: $(CLIENTOBJ)
	$(CC) $(CFLAGS) $(CLIENTLIB) -o $@ $^

.PHONY = clean

clean:
	rm -f $(CLIENTOBJ)

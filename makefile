CC = g++
CFLAGS = -Iinclude
OBJECTS = src/main.o src/Character.o src/GameWorld.o src/Hero.o src/Monster.o src/NPC.o src/QuestManager.o src/Utility.o
TARGET = AdventureQuest

all: $(TARGET)

$(TARGET): $(OBJECTS)
	$(CC) $(OBJECTS) -o $(TARGET)

src/main.o: src/main.cpp
	$(CC) -c src/main.cpp -o src/main.o $(CFLAGS)

src/Character.o: src/Character.cpp
	$(CC) -c src/Character.cpp -o src/Character.o $(CFLAGS)

src/GameWorld.o: src/GameWorld.cpp
	$(CC) -c src/GameWorld.cpp -o src/GameWorld.o $(CFLAGS)

src/Hero.o: src/Hero.cpp
	$(CC) -c src/Hero.cpp -o src/Hero.o $(CFLAGS)

src/Monster.o: src/Monster.cpp
	$(CC) -c src/Monster.cpp -o src/Monster.o $(CFLAGS)

src/NPC.o: src/NPC.cpp
	$(CC) -c src/NPC.cpp -o src/NPC.o $(CFLAGS)

src/QuestManager.o: src/QuestManager.cpp
	$(CC) -c src/QuestManager.cpp -o src/QuestManager.o $(CFLAGS)

src/Utility.o: src/Utility.cpp
	$(CC) -c src/Utility.cpp -o src/Utility.o $(CFLAGS)

clean:
	rm -f $(OBJECTS) $(TARGET)
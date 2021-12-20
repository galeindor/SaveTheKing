EX02: Game: Save The King

Students info:
name: Michael Basov	ID: 315223156
name: Gal Ein-Dor	ID: 209070671

Task description:
In this task we built a game called save the king. in this game you can add levels as .txt files in reasources directory
and the game will read the levels, there are 3 pre-built levels in the game.
The porpuse of the game is to bring the king to his throne.
The game contains the following characters:
King - needs to go back and sit on his throne, represented by char K
Mage - can put out fires that are on the board, represented by char M
Warrior - can kill orgs that drop keys, represented by char W
Thief - can pick up keys and open gates with them, represented by char T
Besides the characters, there are few objects acrros the board:
Throne - the king needs to sit on it, represented by char @
Fire - blocks the way of any character, the mage can put it out, represented by char *
Org - powerfull creature that can be easilly be killed by the warrior, once dead, drops a key, represented by char !
Key - dropped after an org is killed, can be picked by the Thief, represented by char F
Gate - can be opened with a key, represented by char #
Wall - blocks every character in the game, represented by char =


List of files:
King.cc - contains the functions and the members used to control the King
Mage.cc - contains the functions and the members used to control the Mage
Warrior.cc - contains the functions and the members used to control the Warrior
Thief.cc - contains the functions and the members used to control the Thief
Controller.cc - controls the on-going of the game, controls the characters and the board, every thing happens in the game controlles by this class
Board.cc - writes and displays the board, in charge of every change and update to the board that happens during the game
main.cc - creates a Controller object and luanches the game
io.cpp - in charge of input/output system calls
Location.h - struct that holds row and col of object in the board
// every .cpp file has a .h file with the same name //
levelList.txt - stores the names of the other levels in order to load them when needed
levelOne.txt - stores the first level board
levelTwo.txt - stores the second level board
levelThree.txt - stores the thord level board


Main databases:
We used a 2D vector (vector<vector<char>>) in order to store the board and read the level file and store 
everything in the 2D vector.
We used another vector to store positions of the teleports across the board in order to control
the behavior of the teleports.

Special Algorithems:

Known bugs:

Other:
In this task, we were asked to build the game according to some rules and guidlines of tha course staff,
Things that wern't described by the staff were given us to do as we decide.
In the guildlines about characters interacting with the key(F), the staff told us that every character can go over the key
but only the Thief(T) can collect it, we decided that if a charcter that is not Thief steps on the board, the key will teleport
behind it. we did it in order to prevent a character blocking the Thief from taking the key and rpoceeding the game.

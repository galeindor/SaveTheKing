#include "Board.h"
#include <string>

bool isTp = false, onKey = false;
char playerOnTp;

Board::Board(std::string fileName)
	    :m_matrix(), m_teleport()
{
	// open the level file
	std::ifstream m_file;
	m_file.open(fileName);

	if (!m_file)
	{
		cout << "Error! couldn't open file\n";
		exit(EXIT_FAILURE);
	}

	// read into the board from file
	std::string line;
	int row = 0, col;
	while (std::getline(m_file, line))
	{
		vector<char> rowToRead;
		col = 0;
		for (char& c : line) 
		{
			//read row
			if (c != '\n') 
				rowToRead.push_back(c);
			// save teleport in other vector
			if (c == 'X')
			{
				Location loc(row, col);
				m_teleport.push_back(loc);
			}
			col++;
		}
		row++;
		m_matrix.push_back(rowToRead);
	}
	m_file.close();
}

void Board::clear() const
{
	std::system("cls");
}
void Board::print() const
{
	for (int i = 0; i < m_matrix.size(); ++i)
	{
		for (int j = 0; j < m_matrix[i].size(); ++j)
			cout << m_matrix[i][j];
		cout << std::endl;
	}
}
void Board::updateBoard(Location oldLoc, Location newLoc, char player, char tile)
{
	//save the position of the teleport
	if (isTp)
	{
		m_matrix[oldLoc.row][oldLoc.col] = ' ';
		isTp = false;
	}
	else
		m_matrix[oldLoc.row][oldLoc.col] = tile;

	// flag if stepped on a teleport
	if (getTile(newLoc.row, newLoc.col) == 'X')
		isTp = true;

	// update the new player location
	m_matrix[newLoc.row][newLoc.col] = player;
	printTeleports();
}

Location Board::getLocation(char player)
{
	for (int i = 0; i < m_matrix.size(); ++i)
	{
		for (int j = 0; j < m_matrix[i].size(); ++j)
			if (m_matrix[i][j] == player)
				return Location(i, j);
	}
	return Location(0, 0);
}

int Board::getRowSize() const
{
	return m_matrix.size();
}
int Board::getColSize() const
{
	return m_matrix[0].size();
}

void Board::printStats(char currPlayer, int steps, bool key) const
{
	Screen::resetLocation();
	std::string keyPossesion = "No ";
	if (key)
		keyPossesion = "Yes";
	cout << "Current player: " << currPlayer <<std::endl << "Steps made: " << steps << std::endl
		<< "Thief has key: " << keyPossesion << std::endl << std::endl;
}

char Board::getTile(int row, int col) const
{
	return m_matrix[row][col];
}

bool Board::cmpLocations(Location one, Location two)
{
	return (one.row == two.row && one.col == two.col);
}

Location Board::locateTeleport(Location teleportLoc)
{
	// every teleport built in a vector, the friend of a teleport is hes neighbor in the vecotr,
	// if the position of a teleport in the array is odd hes friend in  index -1
	// if the index is even hes friend in index +1
	for (int i = 0; i < m_teleport.size(); ++i)
	{
		if (cmpLocations(m_teleport[i], teleportLoc))
			if(i % 2 == 0)
				return m_teleport[i + 1];
			else
				return m_teleport[i - 1];
	}
	return Location(0, 0);
}

void Board::printTeleports()
{
	for (int i = 0; i < m_teleport.size(); ++i)
		if(m_matrix[m_teleport[i].row][m_teleport[i].col] == ' ')
			m_matrix[m_teleport[i].row][m_teleport[i].col] = 'X';
}
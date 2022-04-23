#include <cstring>
#include "Game.h"

Game::Game()
: size(10)
{
    board = new Tools*[size];

    for (int i = 0; i < size; i++)
    {
        board[i] = new Tools[size];
        for (int j = 0; j < size; j++)
        {
            if (i > 3 & i < 6)
            {
                if (j < 2 || (j > 3 & j < 6) || (j > 7))
                    board[i][j].id = 'O';

                else
                    board[i][j].id = '-';
            }

        }
    }
}

Game::~Game()
{
    for (int i = 0; i < size; i++)
    {
        delete[] board[i];
    }
    delete[] board;
    board = 0;
}


void Game::set_input(std::string& game_tools1, std::string& game_tools2) const
{
    int* tools = new int[40];
    int count_tools = 0;
    convert_string(game_tools1, tools);

    // set first player
    for (int i = 6; i < size; i++)
    {
        for (int j = 0; j < size; j++)
        {
            if (tools[count_tools] == 10) {
                board[i][j].id = 'A';
                board[i][j].value = 10;
                board[i][j].name = std::to_string(1);
            }
            if (tools[count_tools] == 0)
            {
                board[i][j].id = 'B';
                board[i][j].value = 0;
                board[i][j].name = std::to_string(1);
            }
            if (tools[count_tools] == -1) {
                board[i][j].id = 'F';
                board[i][j].value = -1;
                board[i][j].name = std::to_string(1);
            }
            else if (tools[count_tools] != 10 & tools[count_tools] != 0 & tools[count_tools] != -1) {
                board[i][j].id = '0' + tools[count_tools];
                board[i][j].value = tools[count_tools];
                board[i][j].name = std::to_string(1);
            }
            count_tools++;
        }
    }
    count_tools = 0;
    convert_string(game_tools2, tools);

    // set second player
    for (int i = 3; i > -1; i--)
    {
        for (int j = 0; j < size; j++)
        {
            if (tools[count_tools] == 10) {
                board[i][j].id = 'A';
                board[i][j].value = 10;
                board[i][j].name = std::to_string(2);
            }
            if (tools[count_tools] == 0)
            {
                board[i][j].id = 'B';
                board[i][j].value = 0;
                board[i][j].name = std::to_string(2);;
            }
            if (tools[count_tools] == -1) {
                board[i][j].id = 'F';
                board[i][j].value = -1;
                board[i][j].name = std::to_string(2);;
            }
            else if (tools[count_tools] != 10 & tools[count_tools] != 0 & tools[count_tools] != -1) {
                board[i][j].id = '0' + tools[count_tools];
                board[i][j].value = tools[count_tools];
                board[i][j].name = std::to_string(2);;
            }
            count_tools++;
        }
    }
    delete[] tools;
}

void Game::convert_string(std::string& game_tools, int* tools) const
{
    std::string temp;
    int tools_runner = 0;
    for(std::string::size_type i = 0; i < game_tools.size(); ++i)
    {
        if (game_tools[i] != ',')
        {
            temp += game_tools[i];

            // not end of string?
            if (i < game_tools.size() - 1)
                continue;
        }
        tools[tools_runner++] = std::stoi(temp);

        // clean temp string
        temp = std::string("");
    }

    if (tools_runner != 40)
        tools[0] = -2;
}

bool Game::check_quit(std::string& input, int p) const
{
    char quit[4] = {'q','u','i','t'};
    std::string n;

    if (input.size() != 4)
        return false;

    for (std::string::size_type i = 0; i < input.size(); i++)
    {
        if (input[i] == toupper(quit[i]) || input[i] == tolower(quit[i]))
            n += quit[i];
    }

    if (n == "quit")
    {
        std::cout << std::endl << "P" << p << ": QUIT" << std::endl;
        if (p == 1) {
            std::cout << "P" << p+1 << " wins the game." << std::endl;
            return true;
        }
        std::cout << "P" << p-1 << " wins the game." << std::endl;
        return true;
    }
    return false;
}

bool Game::check_input(std::string& game_tools) const
{
    int tools[40];
    convert_string(game_tools, tools);

    // have to be 40 tools
    if (tools[0] == -2)
        return false;

    if (!check_each_size(tools))
        return false;

    return true;
}

bool Game::check_each_size(int* tools) const
{
    int temp[12] = {0,0,0,0,0,0,0,0,0,0,0,0};
    for (int i = 0; i < 40; i++)
    {
        if (tools[i] == -1)
            temp[11] += 1;

        if (tools[i] == 0)
            temp[0] += 1;

        if (tools[i] == 1)
            temp[1] += 1;

        if (tools[i] == 2)
            temp[2] += 1;

        if (tools[i] == 3)
            temp[3] += 1;

        if (tools[i] == 4)
            temp[4] += 1;

        if (tools[i] == 5)
            temp[5] += 1;

        if (tools[i] == 6)
            temp[6] += 1;

        if (tools[i] == 7)
            temp[7] += 1;

        if (tools[i] == 8)
            temp[8] += 1;

        if (tools[i] == 9)
            temp[9] += 1;

        if (tools[i] == 10)
            temp[10] += 1;
    }
    if (temp[0] != 6 | temp[10] != 1 | temp[11] != 1 | temp[1] != 1 | temp[9] != 1 | temp[2] != 8 | temp[3] != 5 | temp[4] != 4 | temp[5] != 4 | temp[6] != 4 | temp[7] != 3 |temp[8] != 2)
        return false;

    return true;
}

void Game::print_board(std::string& name) const
{
    for (int i = 0; i < size; i++) {
        std::cout << i+1 << '\t';
        for (int j = 0; j < size; j++) {
            if (board[i][j].name == name)
                std::cout << board[i][j].hidden << " ";

            else
                std::cout << board[i][j].id << " ";
        }
        std::cout << std::endl;
    }
    std::cout << std::endl;

    std::cout << '\t';
    // print ABC
    for (char i = 65; i < 75; i++)
    {
        if (i == 74) {
            std::cout << i;
            continue;
        }
        std::cout << i << " ";
    }
    std::cout << std::endl;
}

void Game::convert_to_numbers(std::string& move, int* positions) const
{
    char abc[10] = {'a', 'b', 'c', 'd', 'e', 'f', 'g', 'h', 'i', 'j'};
    std::string temp;
    int space = 0;
    for (int i = 0; i < 10; i++)
    {
        // get prev position col
        if (abc[i] == move[0] || abc[i] == tolower(move[i]))
        {
            positions[1] = i;
            break;
        }
    }
    // get prev position row
    for (std::string::size_type i = 1; i < move.size(); ++i)
    {
        temp += move[i];
        if (move[i] == ' ')
        {
            positions[0] = std::stoi(temp) - 1;
            space = i;
            temp = std::string("");
            break;
        }
    }

    // get next position col
    for (int i = 0; i < 10; i++)
    {
        if (abc[i] == move[space+1] || abc[i] == tolower(move[space+1])) {
            positions[3] = i;
            break;
        }
    }

    // get next position row
    for (std::string::size_type i = space+2; i < move.size(); ++i)
    {
        temp += move[i];

        if (i == move.size() - 1)
            positions[2] = std::stoi(temp) - 1;
    }
}

bool Game::check_move(std::string& move, std::string& name) const {
    int pos[4];
    convert_to_numbers(move, pos);

    // check if it's bomb or flag
    if (board[pos[0]][pos[1]].value == 0 || board[pos[0]][pos[1]].value == -1)
        return false;

    // check if prev position belong to this player
    if (board[pos[0]][pos[1]].name != name)
        return false;

    // check if next position is not my player
    if (board[pos[2]][pos[3]].name == name)
        return false;

    // cant go diagonally
    if (pos[0] != pos[2] & pos[1] != pos[3])
        return false;

    // cant skip on other player
    if (pos[0] == pos[2])
    {
        if (pos[1] > pos[3])
        {
            // not tracker? too much steps
            if (board[pos[0]][pos[1]].value != 2 & pos[1] != pos[3] + 1)
                return false;

            for (int j = pos[1] - 1; j >= pos[3]; j--)
            {
                // cant enter the sea
                if (board[pos[0]][j].id == '-')
                    return false;

                // must be enemy player
                if (board[pos[0]][j].id != 'O')
                    return false;
            }
        }
        else if (pos[1] < pos[3])
        {
            // not tracker? too much steps
            if (board[pos[0]][pos[1]].value != 2 & pos[1] != pos[3] - 1)
                return false;
            for (int j = pos[1] + 1; j <= pos[3]; j++)
            {
                // cant enter the sea
                if (board[pos[0]][j].id == '-')
                    return false;

                // must be enemy player
                if (board[pos[0]][j].id != 'O')
                    return false;
            }
        }
    }

    if (pos[1] == pos[3]) {
        if (pos[0] > pos[2]) {
            // not tracker? too much steps
            if (board[pos[0]][pos[1]].value != 2 & pos[0] != pos[2] + 1)
                return false;
            for (int i = pos[0] - 1; i >= pos[2]; i--) {
                // cant enter the sea
                if (board[i][pos[1]].id == '-')
                    return false;
            }
        } else if (pos[0] < pos[2]) {
            // not tracker? too much steps
            if (board[pos[0]][pos[1]].value != 2 & pos[0] != pos[2] - 1)
                return false;
            for (int i = pos[0] + 1; i <= pos[2]; i++) {
                // cant enter the sea
                if (board[i][pos[1]].id == '-')
                    return false;

            }
        }
    }

    // check if next position is empty
    if (board[pos[1]][pos[3]].id == 'O')
        return true;

    return true;
}

bool Game::check_end(std::string& enemy) const
{
    bool flag = false;
    bool soldier = false;
    for (int i = 0; i < size; i++)
    {
        for (int j = 0; j < size; j++)
        {
            if (board[i][j].name == enemy)
            {
                if (board[i][j].value == -1) {
                    flag = true;
                    continue;
                }

                if (board[i][j].value != -1 & board[i][j].value != 0) {
                    soldier = true;
                    continue;
                }
            }
        }
    }
    // flag was taken
    if (flag == false)
        return true;

    // no more soldiers left
    if (flag == true & soldier == false)
        return true;

    return false;
}

int Game::do_move(std::string& move, std::string& enemy) const
{
    int pos[4];


    convert_to_numbers(move, pos);
    std::string me = board[pos[0]][pos[1]].name;
    // check if fight
    if (board[pos[2]][pos[3]].name == enemy)
    {
        // soldier hit flag
        if (board[pos[2]][pos[3]].value == -1) {
            board[pos[2]][pos[3]].value = -2;
            board[pos[2]][pos[3]].id = 'O';
            board[pos[2]][pos[3]].name = me;
            return 1;
        }

        // spy attack Lieutenant General
        if (board[pos[0]][pos[1]].value == 1 & board[pos[2]][pos[3]].value == 10)
        {
            board[pos[2]][pos[3]].id = board[pos[0]][pos[1]].id;
            board[pos[2]][pos[3]].name = board[pos[0]][pos[1]].name;
            board[pos[2]][pos[3]].value = board[pos[0]][pos[1]].value;
            board[pos[0]][pos[1]].id = 'O';
            board[pos[0]][pos[1]].name = '0';
            board[pos[0]][pos[1]].value = -2;
            std::cout << "STRATEGO!! P" << me <<  " won the fight" << std::endl;
            return 1;
        }

        // any soldier attack bomb
        if (board[pos[2]][pos[3]].value == 0 & board[pos[0]][pos[1]].value != 3)
        {
            board[pos[0]][pos[1]].id = 'O';
            board[pos[0]][pos[1]].name = '0';
            board[pos[0]][pos[1]].value = -2;
            std::cout << "STRATEGO!! P" << enemy <<  " won the fight" << std::endl;
            return 1;
        }

        // sapper attack bomb
        if (board[pos[2]][pos[3]].value == 0 & board[pos[0]][pos[1]].value == 3)
        {
            board[pos[2]][pos[3]].id = board[pos[0]][pos[1]].id;
            board[pos[2]][pos[3]].name = board[pos[0]][pos[1]].name;
            board[pos[2]][pos[3]].value = board[pos[0]][pos[1]].value;
            board[pos[0]][pos[1]].id = 'O';
            board[pos[0]][pos[1]].name = '0';
            board[pos[0]][pos[1]].value = -2;
            std::cout << "STRATEGO!! P" << me <<  " won the fight" << std::endl;
            return 1;
        }

        // if soldiers are equal
        if (board[pos[0]][pos[1]].value == board[pos[2]][pos[3]].value)
        {
            board[pos[0]][pos[1]].id = 'O';
            board[pos[0]][pos[1]].name = '0';
            board[pos[0]][pos[1]].value = -2;
            board[pos[2]][pos[3]].id = 'O';
            board[pos[2]][pos[3]].name = '0';
            board[pos[2]][pos[3]].value = -2;
            return 0;
        }

        // any other fight
        if (board[pos[0]][pos[1]].value < board[pos[2]][pos[3]].value)
        {
            board[pos[0]][pos[1]].id = board[pos[2]][pos[3]].id;
            board[pos[0]][pos[1]].name = board[pos[2]][pos[3]].name;
            board[pos[0]][pos[1]].value = board[pos[2]][pos[3]].value;
            board[pos[2]][pos[3]].id = 'O';
            board[pos[2]][pos[3]].name = '0';
            board[pos[2]][pos[3]].value = -2;
            std::cout << "STRATEGO!! P" << enemy <<  " won the fight" << std::endl;
            return 1;
        }

        board[pos[2]][pos[3]].id = board[pos[0]][pos[1]].id;
        board[pos[2]][pos[3]].name = board[pos[0]][pos[1]].name;
        board[pos[2]][pos[3]].value = board[pos[0]][pos[1]].value;
        board[pos[0]][pos[1]].id = 'O';
        board[pos[0]][pos[1]].name = '0';
        board[pos[0]][pos[1]].value = -2;
        std::cout << "STRATEGO!! P" << me <<  " won the fight" << std::endl;
        return 1;
    }

    // not enemy but legal move
    board[pos[2]][pos[3]].id = board[pos[0]][pos[1]].id;
    board[pos[2]][pos[3]].name = board[pos[0]][pos[1]].name;
    board[pos[2]][pos[3]].value = board[pos[0]][pos[1]].value;
    board[pos[0]][pos[1]].id = 'O';
    board[pos[0]][pos[1]].name = '0';
    board[pos[0]][pos[1]].value = -2;
    return 1;
}
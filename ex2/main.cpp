#include "Game.h"

std::string get_enemy(int p)
{
    if (p == 1)
        return std::to_string(p+1);
    return std::to_string(p-1);
}

void run()
{
    bool input = false;
    int p = 1;
    int quit = 0;

    // create board for the game
    Game* game = new Game();
    std::string pieces1;
    std::string pieces2;

    // check user input
    while (!input) {
        std::cout << "P1: ";
        std::cin >> pieces1;

        if (game->check_quit(pieces1, p))
        {
            quit++;
            input = true;
            continue;
        }

        if (!game->check_input(pieces1)) {
            std::cerr << "Invalid move; the game awaits a valid move." << std::endl;
            std::cout << std::endl;
            continue;
        }

        std::cout << std::endl << "P2: ";
        std::cin >> pieces2;

        if (game->check_quit(pieces1, p+1))
        {
            quit++;
            input = true;
            continue;
        }

        if (!game->check_input(pieces2))
            std::cerr << "Invalid move; the game awaits a valid move." << std::endl;

        else
            input = true;
    }

    if (quit > 0)
    {
        delete game;
        return;
    }

    std::cout << std::endl;
    // set game tools on board
    game->set_input(pieces1, pieces2);

    std::string s = std::to_string(p+1);
    game->print_board(s);

    std::cin.ignore();
    // loop for playing the game
    while (true) {

        std::string player_call;
        std::cout << "P" << p << ":";
        // get user input
        while(true){
            std::getline(std::cin, player_call);
            break;
        }

        // check  if player wants to quit
        if (game->check_quit(player_call, p))
        {
            delete game;
            break;
        }

        std::cout << std::endl;
        // check if legal move
        std::string name = std::to_string(p);
        std::string enemy = get_enemy(p);
        if (!game->check_move(player_call, name)) {
            std::cerr << "Invalid move; the game awaits a valid move." << std::endl;
            game->print_board(enemy);
            continue;
        }

        // make move and fight if needed
        int check = 0;
        if (game->do_move(player_call, enemy) == 0)
        {
            check = 1;
        }

        // check if end game
        if (game->check_end(enemy)) {
            std::cout << "P" << name << " wins the game." << std::endl;
            delete game;
            break;
        }

        // print board for next player
        if (p == 2) {
            p--;
            game->print_board(name);
            if (check == 1)
                std::cout << "STRATEGO!!" << std::endl;
            continue;
        }
        p++;
        game->print_board(name);
        if (check == 1)
            std::cout << "STRATEGO!!" << std::endl;

        player_call = std::string("");
        check = 0;
    }
}

int main() {
    run();
    return 0;
}
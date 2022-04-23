#ifndef EX2_GAME_H
#define EX2_GAME_H

#include <iostream>
#include <cctype>

class Game
{
    public:
        Game();
        ~Game();
        typedef struct {
            int value;
            char id;
            std::string name;
            char hidden = 'S';
        } Tools;
        Tools tools;

        void set_input(std::string&, std::string&) const;
        bool check_input(std::string&) const;
        bool check_each_size(int*) const;
        void print_board(std::string&) const;
        int do_move(std::string&, std::string&) const;
        bool check_move(std::string&, std::string&) const;
        bool check_end(std::string&) const;
        bool check_quit(std::string&, int) const;

    private:
        Tools **board;
        int size;
        void convert_string(std::string&, int*) const;
        void convert_to_numbers(std::string&, int*) const;

};
#endif //EX2_GAME_H

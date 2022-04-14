#ifndef EX1_WEB_H
#define EX1_WEB_H

#include <iostream>

class WebListener
{
    public:
        WebListener(int, int);
        ~WebListener();

        int get_size() const;
        int get_dimension() const;

        bool set_record(const std::string&, std::string);
        std::string get_record(const std::string&);
        bool check_timestamp(const std::string&);
        bool check_index(int) const;
        float calculate(int);
        void print_histogram(const int*) const;

    private:
        int size;
        int max_size;
        int dimension;
        char** timestamps;
        unsigned short** records;
};

#endif //EX1_WEB_H

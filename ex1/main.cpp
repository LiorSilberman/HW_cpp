#include <sstream>
#include <cmath>
#include "WebListener.h"

void print_manu()
{
    std::cout << "[1]\tInsert a web record"   << std::endl
              << "[2]\tRetrieve a web record" << std::endl
              << "[3]\tSite stat"             << std::endl
              << "[4]\tOverall stats"         << std::endl
              << "[5]\tExit"                  << std::endl;
}

void run(int dim, int max)
{
    // create web listener
    WebListener* listener = new WebListener(dim, max);
    // main loop
    bool terminate_request = false;
    while (!terminate_request)
    {
        int choice = 0;
        print_manu();
        std::cin >> choice;

        switch (choice) {
            case 1: {
                // ask for timestamp
                std::cout << "Type the record's timestamp:" << std::endl;
                std::string timestamp;
                std::cin >> timestamp;

                // ask for web record
                std::cout << "Type the record:" << std::endl;
                std::string record;
                std::cin >> record;

                // set record
                if (!listener->set_record(timestamp, record))
                    std::cerr << "Invalid web record." << std::endl;
                break;
            }

            case 2: {
                // get timestamp to check
                std::cout << "Type the timestamp:" <<std::endl;
                std::string timestamp;
                std::cin >> timestamp;

                // check if legal
                if (!listener->check_timestamp(timestamp))
                {
                    std::cerr << "Invalid or nonexistent timestamp." << std::endl;
                    break;
                }

                // print timestamp and normalaized vector
                std::cout << timestamp << " : ";
                std::cout << listener->get_record(timestamp) << std::endl;
                break;
            }

            case 3:
            {
                // check if memory is empty
                if (listener->get_size() == 0) {
                    std::cerr << "No web records in the system." << std::endl;
                    break;
                }
                // ask for index
                std::cout << "Type the site's index:" << std::endl;
                int index;
                std::cin >> index;

                // check if legal
                if (!listener->check_index(index)) {
                    std::cerr << "Invalid site index." << std::endl;
                    break;
                }

                // check if all are zeros
                if (std::isnan(listener->calculate(index))) {
                    std::cerr << "No web records in the system." << std::endl;
                    break;
                }

                // print scalar
                std::cout << listener->calculate(index) << std::endl;
                break;
            }

            case 4:
            {
                // check if memory is empty
                if (listener->get_size() == 0)
                {
                    std::cerr << "No web records in the system." << std::endl;
                    break;
                }

                // calculate total and print to screen
                int* histogram = new int[listener->get_dimension()];
                int var;
                std::stringstream ss;
                std::string total;
                total += "total : {";
                for (int i = 0; i < listener->get_dimension(); i++)
                {
                    var = std::ceil(listener->calculate(i+1)*100);
                    histogram[i] = var;

                    ss << listener->calculate(i+1);
                    total += ss.str();
                    if (i == listener->get_dimension() - 1)
                    {
                        total += '}';
                        continue;
                    }
                    total += ',';
                    ss.str("");
                }
                std::cout << total << std::endl;

                listener->print_histogram(histogram);

                delete[] histogram;
                break;
            }

            case 5:
                terminate_request = true;
                break;
//
            default:
                // print manu wrong input
                break;
        }
    }

    delete listener;
}

int main(int argc, char **argv)
{
    // get arguments
    int max, dim;
    if (argc != 3)
        return 0;


    std::stringstream ss(argv[1]);
    std::stringstream ss2(argv[2]);
    ss >> dim;
    ss2 >> max;

    // check legal arguments
    if (dim > 10 || max > 3000)
        return 0;

    // run program
    run(dim, max);

    // finito
    return 0;
}
